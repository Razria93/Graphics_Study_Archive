#include "Rasterization.h"

#include <algorithm>

namespace hlab {

	using namespace glm;
	using namespace std;

	Rasterization::Rasterization(const int& width, const int& height)
		: width(width), height(height) {

		circle.InitCircle(vec3(0.0f, 0.0f, 1.0f), 0.3f, 5);

		this->vertexBuffer = circle.vertices;
		this->colorBuffer = circle.colors;
		this->indexBuffer = circle.indices;
	}

	vec2 Rasterization::ProjectWorldToRaster(vec3 point) {

		// Orthographic projection: world coordinates -> NDC.
		const float aspect = float(width) / height;
		const vec2 pointNDC = vec2(point.x / aspect, point.y);

		const float xScale = 2.0f / width;
		const float yScale = 2.0f / height;

		// NDC -> raster coordinates. The -0.5 offset aligns to pixel centers.
		return vec2((pointNDC.x + 1.0f) / xScale - 0.5f,
			(1.0f - pointNDC.y) / yScale - 0.5f);
	}

	float Rasterization::EdgeFunction(const vec2& v0, const vec2& v1,
		const vec2& point) {

		const vec2 a = v1 - v0;
		const vec2 b = point - v0;
		return a.x * b.y - a.y * b.x;
	}

	void Rasterization::DrawIndexedTriangle(const size_t& startIndex, vector<vec4>& pixels)
	{

		const size_t i0 = this->indexBuffer[startIndex];
		const size_t i1 = this->indexBuffer[startIndex + 1];
		const size_t i2 = this->indexBuffer[startIndex + 2];

		const auto v0 = ProjectWorldToRaster(this->vertexBuffer[i0]);
		const auto v1 = ProjectWorldToRaster(this->vertexBuffer[i1]);
		const auto v2 = ProjectWorldToRaster(this->vertexBuffer[i2]);

		const auto& c0 = this->colorBuffer[i0];
		const auto& c1 = this->colorBuffer[i1];
		const auto& c2 = this->colorBuffer[i2];

		const auto xMin = size_t(glm::clamp(
			glm::floor(std::min({ v0.x, v1.x, v2.x })), 0.0f, float(width - 1)));
		const auto yMin = size_t(glm::clamp(
			glm::floor(std::min({ v0.y, v1.y, v2.y })), 0.0f, float(height - 1)));
		const auto xMax = size_t(glm::clamp(glm::ceil(std::max({ v0.x, v1.x, v2.x })),
			0.0f, float(width - 1)));
		const auto yMax = size_t(glm::clamp(glm::ceil(std::max({ v0.y, v1.y, v2.y })),
			0.0f, float(height - 1)));

		for (size_t j = yMin; j <= yMax; j++) {
			for (size_t i = xMin; i <= xMax; i++) {

				const vec2 point = vec2(float(i), float(j));
				const float alpha0 = EdgeFunction(v1, v2, point);
				const float alpha1 = EdgeFunction(v2, v0, point);
				const float alpha2 = EdgeFunction(v0, v1, point);

				if (alpha0 >= 0.0f && alpha1 >= 0.0f && alpha2 >= 0.0f) {
					const float area = alpha0 + alpha1 + alpha2;
					const vec3 color =
						(alpha0 * c0 + alpha1 * c1 + alpha2 * c2) / area;

					pixels[i + width * j] = vec4(color, 1.0f);
				}
			}
		}
	}

	void Rasterization::Render(vector<vec4>& pixels) {
		// Each group of three indices references one triangle.
		for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
			DrawIndexedTriangle(i, pixels);
		}
	}

	vec3 RotateAboutZ(const vec3& v, const float& theta)
	{
		return glm::vec3(v.x * glm::cos(theta) - v.y * glm::sin(theta), v.x * glm::sin(theta) + v.y * cos(theta), 0.0f);
	}

	void Rasterization::Update() {
		// Keep the original mesh intact and update only the transformed vertex buffer.
		for (size_t i = 0; i < circle.vertices.size(); i++)
		{
			vec3 temp{ 0.0f };
			
			temp = RotateAboutZ(circle.vertices[i], this->rotation1);
			temp = temp * vec3(scaleX, scaleY, 1.0f);
			temp = temp + this->translation1;
			temp = RotateAboutZ(temp, this->rotation2);
			temp = temp + this->translation2;

			this->vertexBuffer[i] = temp;
		}
	}
} // namespace hlab
