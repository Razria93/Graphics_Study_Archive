#include "Mesh.h"

namespace hlab {

void Mesh::InitCircle(const float &radius, const int &numTriangles,
                      const vec3 &color) {
    const vec3 center = vec3(0.0f);

    this->vertices.reserve(numTriangles + 1);
    this->colors.reserve(numTriangles + 1);
    this->indices.reserve(numTriangles * 3);

    this->vertices.push_back(center);
    this->colors.push_back(color);

    const auto kTwoPi = 2.0f * 3.141592f;
    const auto deltaTheta = kTwoPi / float(numTriangles);

    for (float theta = 0.0f; theta < kTwoPi; theta += deltaTheta) {
        this->vertices.push_back(center +
                                 vec3(cos(theta), sin(theta), 0.0f) * radius);
        this->colors.push_back(color);
    }

    for (size_t i = 0; i < numTriangles; i++) {
        this->indices.push_back(0);
        this->indices.push_back(i == numTriangles - 1 ? 1 : i + 2);
        this->indices.push_back(i + 1);
    }
}

void Mesh::InitSquare(const float &width, const float &height,
                      const vec3 &color) {
    const auto scale = vec3(width * 0.5f, height * 0.5f, 1.0f);

    this->vertices = {
        vec3(-1.0f, -1.0f, 0.0f) * scale,
        vec3(-1.0f, 1.0f, 0.0f) * scale,
        vec3(1.0f, 1.0f, 0.0f) * scale,
        vec3(1.0f, -1.0f, 0.0f) * scale,
    };

    this->colors.resize(this->vertices.size());
    fill(this->colors.begin(), this->colors.end(), color);

    this->indices = {0, 1, 2, 0, 2, 3};
    this->textureCoords = {
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
    };
}

void Mesh::CopyToBuffer() {
    vertexBuffer = vertices;
    indexBuffer = indices;
    colorBuffer = colors;
    uvBuffer = textureCoords;

    vertices.clear();
    indices.clear();
    colors.clear();
    textureCoords.clear();
}

} // namespace hlab
