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

    Mesh circle1;
    Mesh circle2;
    Mesh circle3;

    vec3 center1;
    vec3 center2;
    vec3 center3;

    vector<vec3> vertexBuffer;
    vector<size_t> indexBuffer;
    vector<vec3> colorBuffer;
    vector<float> depthBuffer;
};

} // namespace hlab
