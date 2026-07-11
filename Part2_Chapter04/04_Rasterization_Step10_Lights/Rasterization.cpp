#include "Rasterization.h"

#include <algorithm>

#include "MyShader.h"

namespace hlab {

using namespace glm;
using namespace std;

Rasterization::Rasterization(const int &width, const int &height)
    : width(width), height(height) {
    light.strength = vec3(1.0f);
    light.direction = vec3(0.0f, -1.0f, 0.0f);

    this->object = make_shared<Mesh>();
    this->object->InitBox();
    this->object->CopyToBuffer();
    this->object->transformation.rotationX = -3.141592f * 30.0f / 180.0f;
    this->object->transformation.rotationY = 0.0f;
    this->object->transformation.scale = vec3(2.0f, 1.0f, 2.0f);
    this->object->transformation.translation = vec3(0.0f, -0.8f, 1.0f);
    this->object->material.diffuse = vec3(0.5f);

    meshes.push_back(this->object);

    depthBuffer.resize(width * height, 0.0f);
}

vec2 Rasterization::ProjectWorldToRaster(vec3 pointWorld) {
    vec2 pointProjected = vec2(pointWorld.x, pointWorld.y);

    if (this->usePerspectiveProjection) {
        const float ratio = distEyeToScreen / (distEyeToScreen + pointWorld.z);
        pointProjected = vec2(ratio * pointWorld.x, ratio * pointWorld.y);
    }

    const float aspect = float(width) / height;
    const vec2 pointNDC = vec2(pointProjected.x / aspect, pointProjected.y);

    const float xScale = 2.0f / width;
    const float yScale = 2.0f / height;

    return vec2((pointNDC.x + 1.0f) / xScale - 0.5f,
                (1.0f - pointNDC.y) / yScale - 0.5f);
}

float Rasterization::EdgeFunction(const vec2 &v0, const vec2 &v1,
                                  const vec2 &point) {
    const vec2 a = v1 - v0;
    const vec2 b = point - v0;
    return a.x * b.y - a.y * b.x;
}

void Rasterization::DrawIndexedTriangle(const size_t &startIndex,
                                        vector<vec4> &pixels) {
    const size_t i0 = this->indexBuffer[startIndex];
    const size_t i1 = this->indexBuffer[startIndex + 1];
    const size_t i2 = this->indexBuffer[startIndex + 2];

    const auto v0 = ProjectWorldToRaster(this->vertexBuffer[i0]);
    const auto v1 = ProjectWorldToRaster(this->vertexBuffer[i1]);
    const auto v2 = ProjectWorldToRaster(this->vertexBuffer[i2]);

    const float area = EdgeFunction(v0, v1, v2);
    if (area == 0.0f || (this->cullBackface && area < 0.0f)) {
        return;
    }

    const auto xMin = size_t(glm::clamp(
        glm::floor(std::min({v0.x, v1.x, v2.x})), 0.0f, float(width - 1)));
    const auto yMin = size_t(glm::clamp(
        glm::floor(std::min({v0.y, v1.y, v2.y})), 0.0f, float(height - 1)));
    const auto xMax = size_t(glm::clamp(glm::ceil(std::max({v0.x, v1.x, v2.x})),
                                        0.0f, float(width - 1)));
    const auto yMax = size_t(glm::clamp(glm::ceil(std::max({v0.y, v1.y, v2.y})),
                                        0.0f, float(height - 1)));

    for (size_t j = yMin; j <= yMax; j++) {
        for (size_t i = xMin; i <= xMax; i++) {
            const vec2 point = vec2(float(i), float(j));
            float w0 = EdgeFunction(v1, v2, point) / area;
            float w1 = EdgeFunction(v2, v0, point) / area;
            float w2 = EdgeFunction(v0, v1, point) / area;

            if (w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f) {
                const float z0 = this->vertexBuffer[i0].z + distEyeToScreen;
                const float z1 = this->vertexBuffer[i1].z + distEyeToScreen;
                const float z2 = this->vertexBuffer[i2].z + distEyeToScreen;

                const vec3 p0 = this->vertexBuffer[i0];
                const vec3 p1 = this->vertexBuffer[i1];
                const vec3 p2 = this->vertexBuffer[i2];

                const vec3 n0 =
                    area < 0.0f ? -this->normalBuffer[i0]
                                 : this->normalBuffer[i0];
                const vec3 n1 =
                    area < 0.0f ? -this->normalBuffer[i1]
                                 : this->normalBuffer[i1];
                const vec3 n2 =
                    area < 0.0f ? -this->normalBuffer[i2]
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
                const size_t pixelIndex = i + width * j;

                if (depth < depthBuffer[pixelIndex]) {
                    depthBuffer[pixelIndex] = depth;

                    PSInput psInput;
                    psInput.position = w0 * p0 + w1 * p1 + w2 * p2;
                    psInput.normal =
                        glm::normalize(w0 * n0 + w1 * n1 + w2 * n2);

                    pixels[pixelIndex] = MyPixelShader(psInput);
                }
            }
        }
    }
}

void Rasterization::Render(vector<vec4> &pixels) {
    this->depthBuffer.resize(pixels.size());
    fill(this->depthBuffer.begin(), this->depthBuffer.end(), 10.0f);

    for (const auto &mesh : this->meshes) {
        constants.transformation = mesh->transformation;
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

            const auto vsOutput = MyVertexShader(vsInput);

            this->vertexBuffer[i] = vsOutput.position;
            this->normalBuffer[i] = vsOutput.normal;
        }

        this->indexBuffer = mesh->indexBuffer;

        for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
            DrawIndexedTriangle(i, pixels);
        }
    }
}

void Rasterization::Update() {}

} // namespace hlab
