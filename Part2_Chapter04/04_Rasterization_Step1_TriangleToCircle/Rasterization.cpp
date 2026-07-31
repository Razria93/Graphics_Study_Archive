#define GLM_ENABLE_EXPERIMENTAL

#include "Rasterization.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <algorithm>

constexpr float PI = 3.14159265358979323846f;

namespace hlab
{

	using namespace glm;
	using namespace std;

	Rasterization::Rasterization(const int& width, const int& height)
		: width(width), height(height), triangleNums(0), New_triangleNums(32), radius(0.5f)
	{
	}

	vec2 Rasterization::ProjectWorldToRaster(vec3 point)
	{
		int inputWidth = width;
		int inputHeight = height;

		// Orthographic projection: world coordinates -> NDC.
		const float aspect = float(inputWidth) / inputHeight;
		const vec2 pointNDC = vec2(point.x / aspect, point.y);

		int outputWidth = width;
		int outputHeight = height;

		// NDC -> raster coordinates. The -0.5 offset aligns to pixel centers.
		const float pixelX = (pointNDC.x + 1.0f) * (outputWidth / 2.0f) - 0.5f;
		const float pixelY = (1.0f - pointNDC.y) * (outputHeight / 2.0f) - 0.5f;

		return vec2(pixelX, pixelY);
	}

	float Rasterization::EdgeFunction(const vec2& v0, const vec2& v1, const vec2& point)
	{
		const vec2 a = v1 - v0;
		const vec2 b = point - v0;

		return 0.5f * ((a.x * b.y) - (a.y * b.x));
	}

	void Rasterization::SetTriangleCount(int newCount)
	{
		if (triangleNums == newCount) return;

		triangleNums = newCount;
		circle.triangles.clear();

		// A triangle fan approximates a circle as the segment count increases.
		for (int i = 0; i < triangleNums; i++)
		{
			MyTriangle triangle;

			triangle.v0.pos = vec3(0.0f, 0.0f, 0.0f);
			triangle.v1.pos = vec3(radius * glm::cos((2.0f * PI / triangleNums) * i),
								   radius * glm::sin((2.0f * PI / triangleNums) * i), 0.0f);
			triangle.v2.pos = vec3(radius * glm::cos((2.0f * PI / triangleNums) * (i + 1)),
								   radius * glm::sin((2.0f * PI / triangleNums) * (i + 1)), 0.0f);

			triangle.v0.color = vec3(1.0f, 0.0f, 0.0f);
			triangle.v1.color = vec3(0.0f, 0.0f, 1.0f);
			triangle.v2.color = vec3(0.0f, 0.0f, 1.0f);

			circle.triangles.push_back(triangle);
		}
	}

	void Rasterization::DrawTriangleCount(vector<vec4>& pixels)
	{
		for (int l = 0; l < circle.triangles.size(); l++)
		{
			const vec2 Rast_v0 = ProjectWorldToRaster(circle.triangles[l].v0.pos);
			const vec2 Rast_v1 = ProjectWorldToRaster(circle.triangles[l].v1.pos);
			const vec2 Rast_v2 = ProjectWorldToRaster(circle.triangles[l].v2.pos);

			const size_t xMin = size_t(glm::clamp(glm::floor(std::min({ Rast_v0.x, Rast_v1.x, Rast_v2.x })), 0.0f, float(width - 1)));
			const size_t yMin = size_t(glm::clamp(glm::floor(std::min({ Rast_v0.y, Rast_v1.y, Rast_v2.y })), 0.0f, float(height - 1)));
			const size_t xMax = size_t(glm::clamp(glm::ceil(std::max({ Rast_v0.x, Rast_v1.x, Rast_v2.x })), 0.0f, float(width - 1)));
			const size_t yMax = size_t(glm::clamp(glm::ceil(std::max({ Rast_v0.y, Rast_v1.y, Rast_v2.y })), 0.0f, float(height - 1)));

			for (size_t j = yMin; j <= yMax; j++)
			{
				for (size_t i = xMin; i <= xMax; i++)
				{
					const vec2 point = vec2(float(i), float(j));

					const float area = EdgeFunction(Rast_v0, Rast_v1, Rast_v2);

					const float alpha0 = EdgeFunction(Rast_v1, Rast_v2, point) / area;
					const float alpha1 = EdgeFunction(Rast_v2, Rast_v0, point) / area;
					const float alpha2 = EdgeFunction(Rast_v0, Rast_v1, point) / area;

					if (alpha0 >= 0 && alpha1 >= 0 && alpha2 >= 0)
					{
						// Barycentric coordinates interpolate the vertex colors.
						const float color_R =
							alpha0 * circle.triangles[l].v0.color.r +
							alpha1 * circle.triangles[l].v1.color.r +
							alpha2 * circle.triangles[l].v2.color.r;

						const float color_G =
							alpha0 * circle.triangles[l].v0.color.g +
							alpha1 * circle.triangles[l].v1.color.g +
							alpha2 * circle.triangles[l].v2.color.g;

						const float color_B =
							alpha0 * circle.triangles[l].v0.color.b +
							alpha1 * circle.triangles[l].v1.color.b +
							alpha2 * circle.triangles[l].v2.color.b;

						pixels[i + width * j] = vec4(color_R, color_G, color_B, 1.0f);
					}
				}
			}
		}
	}

	void Rasterization::Render(vector<vec4>& pixels)
	{
		if (triangleNums != New_triangleNums)
		{
			SetTriangleCount(New_triangleNums);
		}

		DrawTriangleCount(pixels);
	}

	void Rasterization::Update()
	{
	}
} // namespace hlab
