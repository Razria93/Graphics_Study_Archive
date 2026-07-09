#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
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

    vector<shared_ptr<Mesh>> meshes;

    vector<vec3> vertexBuffer;
    vector<size_t> indexBuffer;
    vector<vec3> colorBuffer;
    vector<vec2> uvBuffer;
    vector<float> depthBuffer;
};

} // namespace hlab
