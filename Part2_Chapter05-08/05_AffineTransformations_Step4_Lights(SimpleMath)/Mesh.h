#pragma once

#include <directxtk/SimpleMath.h>
#include <iostream>
#include <vector>

namespace hlab {

using namespace DirectX::SimpleMath;
using namespace std;

struct Transformation {
    Vector3 scale = Vector3(1.0f);
    Vector3 translation = Vector3(0.0f);
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
};

struct Material {
    Vector3 ambient = Vector3(0.1f);
    Vector3 diffuse = Vector3(1.0f);
    Vector3 specular = Vector3(1.0f);
    float shininess = 10.0f;
};

struct Light {
    Vector3 strength = Vector3(1.0f);
    Vector3 direction = Vector3(0.0f, -1.0f, 0.0f);
    Vector3 position = Vector3(0.0f, 1.0f, 0.5f);
    float fallOffStart = 0.0f;
    float fallOffEnd = 1.8f;
    float spotPower = 0.0f;
};

class Mesh {
  public:
    void InitBox();
    void CopyToBuffer();

  public:
    vector<Vector3> vertices;
    vector<size_t> indices;
    vector<Vector3> normals;

    vector<Vector3> vertexBuffer;
    vector<Vector3> normalBuffer;
    vector<size_t> indexBuffer;

    Transformation transformation;

    Material material;
};
}

