#include "Mesh.h"

namespace hlab {

void Mesh::InitCircle(const vec3 &center, const float &radius,
                      const int &numTriangles) {
    this->vertices.reserve(numTriangles + 1);
    this->colors.reserve(numTriangles + 1);
    this->indices.reserve(numTriangles * 3);

    this->vertices.push_back(center);
    this->colors.push_back(vec3(1.0f, 0.0f, 0.0f));

    const auto kTwoPi = 2.0f * 3.141592f;
    const auto deltaTheta = kTwoPi / float(numTriangles);

    // Build the outer ring vertices around the center vertex.
    for (float theta = 0.0f; theta < kTwoPi; theta += deltaTheta) {
        this->vertices.push_back(center +
                                 vec3(cos(theta), sin(theta), 0.0f) * radius);
        this->colors.push_back(vec3(0.0f, 0.0f, 1.0f));
    }

    for (size_t i = 0; i < numTriangles; i++) {
        this->indices.push_back(0);
        this->indices.push_back(i == numTriangles - 1 ? 1 : i + 2);
        this->indices.push_back(i + 1);
    }
}

} // namespace hlab
