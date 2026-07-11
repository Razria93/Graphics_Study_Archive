#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "Mesh.h"

namespace hlab {

class Rasterization {
  public:
    Rasterization(const int &width, const int &height);

    void DrawIndexedTriangle(const size_t &startIndex, vector<Vector4> &pixels);

    Vector2 ProjectWorldToRaster(Vector3 point);
    float EdgeFunction(const Vector2 &v0, const Vector2 &v1,
                       const Vector2 &point);
    void Render(vector<Vector4> &pixels);
    void Update();

  public:
    int width;
    int height;

    vector<shared_ptr<Mesh>> meshes;

    shared_ptr<Mesh> object;

    Light light;

    vector<Vector3> vertexBuffer;
    vector<Vector3> normalBuffer;
    vector<size_t> indexBuffer;
    vector<Vector3> colorBuffer;

    vector<float> depthBuffer;

    bool cullBackface = true;

    bool usePerspectiveProjection = true;
    bool usePerspectiveCorrectInterpolation = true;

    float distEyeToScreen = 1.0f;

	int lightType = 0;
};
}

