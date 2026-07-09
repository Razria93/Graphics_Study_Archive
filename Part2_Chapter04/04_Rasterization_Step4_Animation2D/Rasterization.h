#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Mesh.h"

namespace hlab {

using namespace glm;
using namespace std;

class Rasterization {
  public:
    Rasterization(const int &width, const int &height);

    void DrawIndexedTriangle(const size_t &startIndex, vector<vec4> &pixels);
    vec2 ProjectWorldToRaster(vec3 point);
    float EdgeFunction(const vec2 &v0, const vec2 &v1, const vec2 &point);
    void Render(vector<vec4> &pixels);
    void Update();

  public:
    int width;
    int height;

    Mesh sun;
    Mesh earth;
    Mesh moon;

    glm::vec3 earthPosition = glm::vec3{0.0f, 0.0f, 0.0f};
    float earthAngle = 0.0f;
    float earthAngularVelocity = 0.3f;

    glm::vec3 moonPosition = glm::vec3{0.0f, 0.0f, 0.0f};
    float moonAngle = 0.0f;
    float moonAngularVelocity = 1.0f;

    float distSunToEarth = 0.5f;
    float distEarthToMoon = 0.1f;

    vector<vec3> vertexBuffer;
    vector<size_t> indexBuffer;
    vector<vec3> colorBuffer;
};

} // namespace hlab
