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

    Mesh circle;

    vec3 translation1 = vec3(0.0f);
    vec3 translation2 = vec3(0.0f);
    float rotation1 = 0.0f;
    float rotation2 = 0.0f;
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    vector<vec3> vertexBuffer;
    vector<vec3> colorBuffer;
    vector<size_t> indexBuffer;
};
} // namespace hlab
