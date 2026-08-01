#include "Rasterization.h"

#include <algorithm>

namespace hlab {

	using namespace glm;
	using namespace std;

	Rasterization::Rasterization(const int& width, const int& height)
		: width(width), height(height)
	{
		const auto radius = 0.5f;
		const auto center = vec3(0.0f, 0.0f, 1.0f);
		const size_t numTriangles = 32;

		this->vertices.reserve(numTriangles + 1);
		this->colors.reserve(numTriangles + 1);
		this->indices.reserve(numTriangles * 3);
		
		this->vertices.push_back(center);
		this->colors.push_back(vec3(1.0f, 0.0f, 0.0f));
		
		const auto kTwoPi = 2.0f * 3.141592f;
		const auto deltaTheta = kTwoPi / float(numTriangles);
		
		// Build the outer ring vertices around the center vertex.
		for (int i = 0; i < numTriangles; i++)
		{
			glm::vec3 point_i = glm::vec3{ center.x + (radius * glm::cos((kTwoPi / numTriangles) * i)), center.y + (radius * glm::sin((kTwoPi / numTriangles) * i)), center.z };
			glm::vec3 color_i = glm::vec3{ 0.0f, 1.0f , 0.0f };
		
			this->vertices.push_back(point_i);
			this->colors.push_back(color_i);
		}
		
		for (int j = 0; j < numTriangles; j++)
		{
			size_t indice_0 = size_t(0);
			size_t indice_1 = size_t((j + 1) % numTriangles + 1);
			size_t indice_2 = size_t(j + 1);

			this->indices.push_back(indice_0);
			this->indices.push_back(indice_1);
			this->indices.push_back(indice_2);
		}

	}

	vec2 Rasterization::ProjectWorldToRaster(vec3 point)
	{

		// Orthographic projection: world coordinates -> NDC.
		const float aspect = float(width) / height;
		const vec2 pointNDC = vec2(point.x / aspect, point.y);

		const float xScale = 2.0f / width;
		const float yScale = 2.0f / height;

		// NDC -> raster coordinates. The -0.5 offset aligns to pixel centers.
		return vec2((pointNDC.x + 1.0f) / xScale - 0.5f, (1.0f - pointNDC.y) / yScale - 0.5f);
	}

	float Rasterization::EdgeFunction(const vec2& v0, const vec2& v1, const vec2& point)
	{
		const vec2 a = v1 - v0;
		const vec2 b = point - v0;
		
		const vec3 vec3_a = vec3(a, 0.0f);
		const vec3 vec3_b = vec3(b, 0.0f);
		
		return glm::cross(vec3_a, vec3_b).z;
	}

	void Rasterization::DrawIndexedTriangle(const size_t& startIndex, vector<vec4>& pixels)
	{

		const size_t i0 = this->indices[startIndex];
		const size_t i1 = this->indices[startIndex + 1];
		const size_t i2 = this->indices[startIndex + 2];

		const auto v0 = ProjectWorldToRaster(this->vertices[i0]);
		const auto v1 = ProjectWorldToRaster(this->vertices[i1]);
		const auto v2 = ProjectWorldToRaster(this->vertices[i2]);

		const auto& c0 = this->colors[i0];
		const auto& c1 = this->colors[i1];
		const auto& c2 = this->colors[i2];

		const auto xMin = size_t(glm::clamp(glm::floor(std::min({ v0.x, v1.x, v2.x })), 0.0f, float(width - 1)));
		const auto yMin = size_t(glm::clamp(glm::floor(std::min({ v0.y, v1.y, v2.y })), 0.0f, float(height - 1)));
		const auto xMax = size_t(glm::clamp(glm::ceil(std::max({ v0.x, v1.x, v2.x })), 0.0f, float(width - 1)));
		const auto yMax = size_t(glm::clamp(glm::ceil(std::max({ v0.y, v1.y, v2.y })), 0.0f, float(height - 1)));

		for (size_t j = yMin; j <= yMax; j++)
		{
			for (size_t i = xMin; i <= xMax; i++)
			{
				const float totalArea = EdgeFunction(v0, v1, v2);

				const vec2 point = vec2(float(i), float(j));
				const float alpha0 = EdgeFunction(v1, v2, point);
				const float alpha1 = EdgeFunction(v2, v0, point);
				const float alpha2 = EdgeFunction(v0, v1, point);

				if (alpha0 >= 0.0f && alpha1 >= 0.0f && alpha2 >= 0.0f)
				{
					const vec3 color = (alpha0 * c0 + alpha1 * c1 + alpha2 * c2) / totalArea;

					pixels[i + width * j] = vec4(color, 1.0f);
				}
			}
		}
	}

	void Rasterization::Render(vector<vec4>& pixels)
	{
		// Each group of three indices references one triangle.
		for (size_t i = 0; i < this->indices.size(); i += 3)
		{
			DrawIndexedTriangle(i, pixels);
		}
	}

	void Rasterization::Update()
	{
	}
} // namespace hlab
