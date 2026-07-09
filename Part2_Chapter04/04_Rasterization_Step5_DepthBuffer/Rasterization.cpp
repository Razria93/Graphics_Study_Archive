#include "Rasterization.h"

#include <algorithm>
#include <cfloat>

namespace hlab {

using namespace glm;
using namespace std;

Rasterization::Rasterization(const int &width, const int &height)
    : width(width), height(height) {
    circle1.InitCircle(0.3f, 30, vec3(1.0f, 0.0f, 0.0f));
    circle2.InitCircle(0.5f, 30, vec3(0.0f, 0.0f, 1.0f));
    circle3.InitCircle(0.5f, 30, vec3(1.0f, 1.0f, 0.0f));

    center1 = vec3(0.0f, 0.0f, 0.1f);
    center2 = vec3(-0.3f, 0.0f, 0.3f);
    center3 = vec3(0.3f, 0.0f, 0.7f);

    circle1.vertexBuffer = circle1.vertices;
    circle1.indexBuffer = circle1.indices;
    circle1.colorBuffer = circle1.colors;

    circle2.vertexBuffer = circle2.vertices;
    circle2.indexBuffer = circle2.indices;
    circle2.colorBuffer = circle2.colors;

    circle3.vertexBuffer = circle3.vertices;
    circle3.indexBuffer = circle3.indices;
    circle3.colorBuffer = circle3.colors;

    circle1.vertices.clear();
    circle1.indices.clear();
    circle1.colors.clear();

    circle2.vertices.clear();
    circle2.indices.clear();
    circle2.colors.clear();

    circle3.vertices.clear();
    circle3.indices.clear();
    circle3.colors.clear();
}

vec2 Rasterization::ProjectWorldToRaster(vec3 point) {
    const float aspect = float(width) / height;
    const vec2 pointNDC = vec2(point.x / aspect, point.y);

    const float xScale = 2.0f / width;
    const float yScale = 2.0f / height;

    return vec2((pointNDC.x + 1.0f) / xScale - 0.5f,
                (1.0f - pointNDC.y) / yScale - 0.5f);
}

float Rasterization::EdgeFunction(const vec2 &v0, const vec2 &v1,
                                  const vec2 &point) {
    const vec2 a = v1 - v0;
    const vec2 b = point - v0;
    return a.x * b.y - a.y * b.x;
}

void Rasterization::DrawIndexedTriangle(const size_t &startIndex,
                                        vector<vec4> &pixels) {
    const size_t i0 = this->indexBuffer[startIndex];
    const size_t i1 = this->indexBuffer[startIndex + 1];
    const size_t i2 = this->indexBuffer[startIndex + 2];

    const auto v0 = ProjectWorldToRaster(this->vertexBuffer[i0]);
    const auto v1 = ProjectWorldToRaster(this->vertexBuffer[i1]);
    const auto v2 = ProjectWorldToRaster(this->vertexBuffer[i2]);

    const auto &c0 = this->colorBuffer[i0];
    const auto &c1 = this->colorBuffer[i1];
    const auto &c2 = this->colorBuffer[i2];

    const auto xMin = size_t(glm::clamp(
        glm::floor(std::min({v0.x, v1.x, v2.x})), 0.0f, float(width - 1)));
    const auto yMin = size_t(glm::clamp(
        glm::floor(std::min({v0.y, v1.y, v2.y})), 0.0f, float(height - 1)));
    const auto xMax = size_t(glm::clamp(glm::ceil(std::max({v0.x, v1.x, v2.x})),
                                        0.0f, float(width - 1)));
    const auto yMax = size_t(glm::clamp(glm::ceil(std::max({v0.y, v1.y, v2.y})),
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
                const float depth =
                    (alpha0 * this->vertexBuffer[i0].z +
                     alpha1 * this->vertexBuffer[i1].z +
                     alpha2 * this->vertexBuffer[i2].z) /
                    area;

                const size_t pixelIndex = i + width * j;
                if (depth >= 0.0f && depth < depthBuffer[pixelIndex]) {
                    depthBuffer[pixelIndex] = depth;
                    pixels[pixelIndex] = vec4(color, 1.0f);
                }
            }
        }
    }
}

void Rasterization::Render(vector<vec4> &pixels) {
    this->depthBuffer.resize(pixels.size());
    std::fill(depthBuffer.begin(), depthBuffer.end(), FLT_MAX);

    this->vertexBuffer.resize(circle1.vertexBuffer.size());
    for (size_t i = 0; i < circle1.vertexBuffer.size(); i++) {
        this->vertexBuffer[i] = circle1.vertexBuffer[i] + center1;
    }

    this->indexBuffer = circle1.indexBuffer;
    this->colorBuffer = circle1.colorBuffer;

    for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
        DrawIndexedTriangle(i, pixels);
    }

    this->vertexBuffer.resize(circle2.vertexBuffer.size());
    for (size_t i = 0; i < circle2.vertexBuffer.size(); i++) {
        this->vertexBuffer[i] = circle2.vertexBuffer[i] + center2;
    }

    this->indexBuffer = circle2.indexBuffer;
    this->colorBuffer = circle2.colorBuffer;

    for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
        DrawIndexedTriangle(i, pixels);
    }

    this->vertexBuffer.resize(circle3.vertexBuffer.size());
    for (size_t i = 0; i < circle3.vertexBuffer.size(); i++) {
        this->vertexBuffer[i] = circle3.vertexBuffer[i] + center3;
    }

    this->indexBuffer = circle3.indexBuffer;
    this->colorBuffer = circle3.colorBuffer;

    for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
        DrawIndexedTriangle(i, pixels);
    }
}

void Rasterization::Update() {}

} // namespace hlab
