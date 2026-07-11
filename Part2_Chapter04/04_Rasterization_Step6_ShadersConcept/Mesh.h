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
    void InitSquare(const float &width, const float &height,
                    const vec3 &color);
    void CopyToBuffer();

  public:
    vector<vec3> vertices;
    vector<size_t> indices;
    vector<vec3> colors;
    vector<vec2> textureCoords;

    vector<vec3> vertexBuffer;
    vector<size_t> indexBuffer;
    vector<vec3> colorBuffer;
    vector<vec2> uvBuffer;

    vec3 scale = vec3(1.0f);
    vec3 translation = vec3(0.0f);
    float rotationZ = 0.0f;
};

} // namespace hlab
