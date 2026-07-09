#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace hlab {

using namespace glm;
using namespace std;

class Mesh {
  public:
    void InitCircle(const float &radius, const int &numTriangles,
                    const vec3 &color);

  public:
    vector<vec3> vertices;
    vector<size_t> indices;
    vector<vec3> colors;

    vector<vec3> vertexBuffer;
    vector<size_t> indexBuffer;
    vector<vec3> colorBuffer;
};

} // namespace hlab
