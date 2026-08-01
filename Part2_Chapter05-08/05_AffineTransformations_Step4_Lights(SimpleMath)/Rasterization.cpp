#include "Rasterization.h"

#include <algorithm>

#include "MyShader.h"

namespace hlab {

using namespace std;

Rasterization::Rasterization(const int &width, const int &height)
    : width(width), height(height) {

    light.strength = Vector3(1.0f);
    light.direction = Vector3(0.0f, -1.0f, 0.0f);


    this->object = make_shared<Mesh>();
    this->object->InitBox();
    this->object->CopyToBuffer();
    this->object->transformation.rotationX = -3.141592f * 30.0f / 180.0f;
    this->object->transformation.rotationY = 0.0f;
    this->object->transformation.scale = Vector3(1.0f, 1.0f, 1.0f);
    this->object->transformation.translation = Vector3(0.0f, -0.8f, 1.0f);
    this->object->material.diffuse = Vector3(0.5f);
    meshes.push_back(this->object);

    depthBuffer.resize(width * height, 0.0f);
}

Vector2 Rasterization::ProjectWorldToRaster(Vector3 pointWorld) {


    Vector2 pointProj = Vector2(pointWorld.x, pointWorld.y);

    if (this->usePerspectiveProjection) {
        const float scale =
            distEyeToScreen / (this->distEyeToScreen + pointWorld.z);
        pointProj = Vector2(pointWorld.x * scale, pointWorld.y * scale);
    }

    const float aspect = float(width) / height;
    const Vector2 pointNDC = Vector2(pointProj.x / aspect, pointProj.y);

    const float xScale = 2.0f / width;
    const float yScale = 2.0f / height;

    return Vector2((pointNDC.x + 1.0f) / xScale - 0.5f,
                   (1.0f - pointNDC.y) / yScale - 0.5f);
}

float Rasterization::EdgeFunction(const Vector2 &v0, const Vector2 &v1,
                                  const Vector2 &point) {
    const Vector2 a = v1 - v0;
    const Vector2 b = point - v0;
    return a.x * b.y - a.y * b.x;
}

void Rasterization::DrawIndexedTriangle(const size_t &startIndex,
                                        vector<Vector4> &pixels) {

    const size_t i0 = this->indexBuffer[startIndex];
    const size_t i1 = this->indexBuffer[startIndex + 1];
    const size_t i2 = this->indexBuffer[startIndex + 2];

    const auto v0 = ProjectWorldToRaster(this->vertexBuffer[i0]);
    const auto v1 = ProjectWorldToRaster(this->vertexBuffer[i1]);
    const auto v2 = ProjectWorldToRaster(this->vertexBuffer[i2]);

    const float area = EdgeFunction(v0, v1, v2);

    if (area == 0.0f || (this->cullBackface && area < 0.0f))
        return;

    const auto &c0 = this->colorBuffer[i0];
    const auto &c1 = this->colorBuffer[i1];
    const auto &c2 = this->colorBuffer[i2];


    const Vector2 bMin = Vector2::Min(Vector2::Min(v0, v1), v2);
    const Vector2 bMax = Vector2::Max(Vector2::Max(v0, v1), v2);


    const auto xMin =
        size_t(std::clamp(std::floor(bMin.x), 0.0f, float(width - 1)));
    const auto yMin =
        size_t(std::clamp(std::floor(bMin.y), 0.0f, float(height - 1)));
    const auto xMax =
        size_t(std::clamp(std::ceil(bMax.x), 0.0f, float(width - 1)));
    const auto yMax =
        size_t(std::clamp(std::ceil(bMax.y), 0.0f, float(height - 1)));

    for (size_t j = yMin; j <= yMax; j++) {
        for (size_t i = xMin; i <= xMax; i++) {

            const Vector2 point = Vector2(float(i), float(j));

            float w0 = EdgeFunction(v1, v2, point) / area;
            float w1 = EdgeFunction(v2, v0, point) / area;
            float w2 = EdgeFunction(v0, v1, point) / area;

            if (w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f) {


                const float z0 = this->vertexBuffer[i0].z + distEyeToScreen;
                const float z1 = this->vertexBuffer[i1].z + distEyeToScreen;
                const float z2 = this->vertexBuffer[i2].z + distEyeToScreen;

                const Vector3 p0 = this->vertexBuffer[i0];
                const Vector3 p1 = this->vertexBuffer[i1];
                const Vector3 p2 = this->vertexBuffer[i2];

                const Vector3 n0 = area < 0.0f ? -this->normalBuffer[i0]
                                               : this->normalBuffer[i0];
                const Vector3 n1 = area < 0.0f ? -this->normalBuffer[i1]
                                               : this->normalBuffer[i1];
                const Vector3 n2 = area < 0.0f ? -this->normalBuffer[i2]
                                               : this->normalBuffer[i2];

                if (this->usePerspectiveProjection &&
                    this->usePerspectiveCorrectInterpolation) {

                    w0 /= z0;
                    w1 /= z1;
                    w2 /= z2;

                    const float wSum = w0 + w1 + w2;

                    w0 /= wSum;
                    w1 /= wSum;
                    w2 /= wSum;
                }

                const float depth = w0 * z0 + w1 * z1 + w2 * z2;

                if (depth < depthBuffer[i + width * j]) {
                    depthBuffer[i + width * j] = depth;

                    PSInput psInput;
                    psInput.position = w0 * p0 + w1 * p1 + w2 * p2;
                    Vector3 normal = w0 * n0 + w1 * n1 + w2 * n2;
                    normal.Normalize();
                    psInput.normal = normal;

                    pixels[i + width * j] = MyPixelShader(psInput);
                }
            }
        }
    }
}

void Rasterization::Render(vector<Vector4> &pixels) {

    this->depthBuffer.resize(pixels.size());
    fill(this->depthBuffer.begin(), this->depthBuffer.end(), 10.0f);

    for (const auto &mesh : this->meshes) {

        const auto &transform = mesh->transformation;
        Matrix scale = Matrix::CreateScale(transform.scale);
        Matrix rotation = Matrix::CreateRotationX(transform.rotationX) *
                          Matrix::CreateRotationY(transform.rotationY) *
                          Matrix::CreateRotationZ(transform.rotationZ);
        Matrix translation = Matrix::CreateTranslation(transform.translation);

        Matrix transMatrix = scale * rotation * translation;

        constants.modelMatrix = transMatrix;
        
        transMatrix.Translation(Vector3(0.0f));
        constants.invTranspose = transMatrix.Invert().Transpose();


        constants.material = mesh->material;
        constants.light = light;
        constants.lightType = this->lightType;

        this->vertexBuffer.resize(mesh->vertexBuffer.size());
        this->normalBuffer.resize(mesh->normalBuffer.size());
        this->colorBuffer.resize(mesh->vertexBuffer.size());

        for (size_t i = 0; i < mesh->vertexBuffer.size(); i++) {

            VSInput vsInput;
            vsInput.position = mesh->vertexBuffer[i];
            vsInput.normal = mesh->normalBuffer[i];

            auto vsOutput = MyVertexShader(vsInput);

            this->vertexBuffer[i] = vsOutput.position;
            this->normalBuffer[i] = vsOutput.normal;
        }

        this->indexBuffer = mesh->indexBuffer;

        for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
            DrawIndexedTriangle(i, pixels);
        }
    }
}

void Rasterization::Update() {
}
}

