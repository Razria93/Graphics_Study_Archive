#include "Rasterization.h"

#include <algorithm>

namespace hlab {

using namespace glm;
using namespace std;

Rasterization::Rasterization(const int &width, const int &height)
    : width(width), height(height) {
    sun.InitCircle(0.1f, 10, vec3(1.0f, 1.0f, 1.0f));
    earth.InitCircle(0.05f, 10, vec3(0.0f, 0.0f, 1.0f));
    moon.InitCircle(0.02f, 10, vec3(1.0f, 1.0f, 0.0f));

    sun.vertexBuffer = sun.vertices;
    sun.indexBuffer = sun.indices;
    sun.colorBuffer = sun.colors;

    earth.vertexBuffer = earth.vertices;
    earth.indexBuffer = earth.indices;
    earth.colorBuffer = earth.colors;

    moon.vertexBuffer = moon.vertices;
    moon.indexBuffer = moon.indices;
    moon.colorBuffer = moon.colors;

    earthPosition = vec3(distSunToEarth, 0.0f, 0.0f);
    moonPosition = vec3(distEarthToMoon, 0.0f, 0.0f);

    sun.vertices.clear();
    sun.indices.clear();
    sun.colors.clear();
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

                pixels[i + width * j] = vec4(color, 1.0f);
            }
        }
    }
}

vec3 RotateAboutZ(const vec3 &v, const float &theta) {
    return vec3(v.x * cos(theta) - v.y * sin(theta),
                v.x * sin(theta) + v.y * cos(theta), v.z);
}

void Rasterization::Render(vector<vec4> &pixels) {
    this->vertexBuffer = sun.vertexBuffer;
    this->indexBuffer = sun.indexBuffer;
    this->colorBuffer = sun.colorBuffer;

    for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
        DrawIndexedTriangle(i, pixels);
    }

    this->vertexBuffer.resize(earth.vertexBuffer.size());
    for (size_t i = 0; i < earth.vertexBuffer.size(); i++) {
        glm::vec3 temp = earth.vertexBuffer[i] + earthPosition;
        temp = RotateAboutZ(temp, earthAngle);
        this->vertexBuffer[i] = temp;
    }

    this->indexBuffer = earth.indexBuffer;
    this->colorBuffer = earth.colorBuffer;

    for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
        DrawIndexedTriangle(i, pixels);
    }

    this->vertexBuffer.resize(moon.vertexBuffer.size());
    for (size_t i = 0; i < moon.vertexBuffer.size(); i++) {
        glm::vec3 temp = moon.vertexBuffer[i] + moonPosition;
        temp = RotateAboutZ(temp, moonAngle);

        // Local moon orbit is composed with earth orbit to create hierarchy.
        temp = temp + earthPosition;
        temp = RotateAboutZ(temp, earthAngle);

        this->vertexBuffer[i] = temp;
    }

    this->indexBuffer = moon.indexBuffer;
    this->colorBuffer = moon.colorBuffer;

    for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
        DrawIndexedTriangle(i, pixels);
    }
}

void Rasterization::Update() {
    const float dt = 1.0f / 30.0f;

    this->earthAngle += this->earthAngularVelocity * dt;
    this->moonAngle += this->moonAngularVelocity * dt;
}

} // namespace hlab
