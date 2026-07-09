#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace hlab {

using namespace glm;
using namespace std;

class Mesh {
  public:
    void InitCircle(const vec3 &center, const float &radius,
                    const int &numTriangles);

  public:
    vector<vec3> vertices;
    vector<vec3> colors;
    vector<size_t> indices;
};
} // namespace hlab
