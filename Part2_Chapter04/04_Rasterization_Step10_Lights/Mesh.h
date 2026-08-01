#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace hlab {

using namespace glm;
using namespace std;

struct Transformation {
    vec3 scale = vec3(1.0f);
    vec3 translation = vec3(0.0f);
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
};

struct Material {
    vec3 ambient = vec3(0.1f);
    vec3 diffuse = vec3(1.0f);
    vec3 specular = vec3(1.0f);
    float shininess = 10.0f;
};

struct Light {
    vec3 strength = vec3(1.0f);
    vec3 direction = vec3(0.0f, -1.0f, 0.0f);
    vec3 position = vec3(0.0f, 0.5f, 0.5f);
    float fallOffStart = 1.35f;
    float fallOffEnd = 7.5f;
    float spotPower = 400.0f;
};

class Mesh {
  public:
    void InitBox();
    void CopyToBuffer();

  public:
    vector<vec3> vertices;
    vector<size_t> indices;
    vector<vec3> normals;

    vector<vec3> vertexBuffer;
    vector<vec3> normalBuffer;
    vector<size_t> indexBuffer;

    Transformation transformation;
    Material material;
};

} // namespace hlab
