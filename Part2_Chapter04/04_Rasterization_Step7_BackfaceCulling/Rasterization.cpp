#include "Rasterization.h"

#include <algorithm>

namespace hlab {

using namespace glm;
using namespace std;

vec3 RotateAboutZ(const vec3 &v, const float &theta) {
    return vec3(v.x * cos(theta) - v.y * sin(theta),
                v.x * sin(theta) + v.y * cos(theta), v.z);
}

vec3 RotateAboutX(const vec3 &v, const float &theta) {
    return vec3(v.x, v.y * cos(theta) - v.z * sin(theta),
                v.y * sin(theta) + v.z * cos(theta));
}

struct Constants {
    vec3 scale = vec3(1.0f);
    vec3 translation = vec3(0.0f);
    float rotationX = 0.0f;
    float rotationZ = 0.0f;
} constants;

struct VSInput {
    vec3 position;
    vec3 color;
    vec2 uv;
};

struct VSOutput {
    vec3 position;
    vec3 color;
    vec2 uv;
};

VSOutput MyVertexShader(const VSInput vsInput) {
    VSOutput vsOutput;

    vec3 transformed = vsInput.position * constants.scale;
    transformed = RotateAboutX(transformed, constants.rotationX);
    transformed = RotateAboutZ(transformed, constants.rotationZ);
    transformed += constants.translation;

    vsOutput.position = transformed;
    vsOutput.color = vsInput.color;
    vsOutput.uv = vsInput.uv;

    return vsOutput;
}

struct PSInput {
    vec3 color;
    vec2 uv;
};

vec4 MyPixelShader(const PSInput psInput) {
    const float size = 5.0f;
    const vec2 pos = glm::mod(floor(psInput.uv * size), 2.0f);

    return glm::mod(pos.x + pos.y, 2.0f)
               ? vec4(psInput.color, 1.0f)
               : vec4(1.0f, 0.0f, 0.0f, 1.0f) * psInput.uv.y +
                     vec4(0.0f, 0.0f, 1.0f, 1.0f) * (1.0f - psInput.uv.y);
}

Rasterization::Rasterization(const int &width, const int &height)
    : width(width), height(height) {
    auto square1 = make_shared<Mesh>();
    square1->InitSquare_Normalized(1.0f, 1.0f, vec3(1.0f));
    square1->scale = vec3(1.0f, 1.0f, 1.0f);
    square1->translation = vec3(-0.52f, 0.0f, 0.0f);
    square1->CopyToBuffer();

    meshes.push_back(square1);

    auto square2 = make_shared<Mesh>();
    square2->InitSquare_Normalized(1.0f, 1.0f, vec3(1.0f));
    square2->rotationX = 3.141592f;
    square2->scale = vec3(1.0f, 1.0f, 1.0f);
    square2->translation = vec3(0.52f, 0.0f, 0.0f);
    square2->CopyToBuffer();

    meshes.push_back(square2);

    depthBuffer.resize(width * height, 0.0f);
}

vec2 Rasterization::ProjectWorldToRaster(vec3 point) {
    const float aspect = float(width) / height;
    const vec2 pointNDC = vec2(point.x / aspect, point.y);

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
    if (area == 0.0f || (cullBackface && area <= 0.0f)) {
        return;
    }

    const auto &c0 = this->colorBuffer[i0];
    const auto &c1 = this->colorBuffer[i1];
    const auto &c2 = this->colorBuffer[i2];

    const auto &uv0 = this->uvBuffer[i0];
    const auto &uv1 = this->uvBuffer[i1];
    const auto &uv2 = this->uvBuffer[i2];

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
            const float alpha0 = EdgeFunction(v1, v2, point) / area;
            const float alpha1 = EdgeFunction(v2, v0, point) / area;
            const float alpha2 = EdgeFunction(v0, v1, point) / area;

            if (alpha0 >= 0.0f && alpha1 >= 0.0f && alpha2 >= 0.0f) {
                const vec3 color = alpha0 * c0 + alpha1 * c1 + alpha2 * c2;
                const vec2 uv = alpha0 * uv0 + alpha1 * uv1 + alpha2 * uv2;
                const float depth =
                    alpha0 * this->vertexBuffer[i0].z +
                    alpha1 * this->vertexBuffer[i1].z +
                    alpha2 * this->vertexBuffer[i2].z;

                const size_t pixelIndex = i + width * j;
                if (depth < depthBuffer[pixelIndex]) {
                    depthBuffer[pixelIndex] = depth;

                    PSInput psInput;
                    psInput.color = color;
                    psInput.uv = uv;

                    pixels[pixelIndex] = MyPixelShader(psInput);
                }
            }
        }
    }
}

void Rasterization::Render(vector<vec4> &pixels) {
    this->depthBuffer.resize(pixels.size());
    fill(this->depthBuffer.begin(), this->depthBuffer.end(), 1.0f);

    for (const auto &mesh : this->meshes) {
        constants.rotationX = mesh->rotationX;
        constants.rotationZ = mesh->rotationZ;
        constants.scale = mesh->scale;
        constants.translation = mesh->translation;

        this->vertexBuffer.resize(mesh->vertexBuffer.size());
        this->colorBuffer.resize(mesh->colorBuffer.size());
        this->uvBuffer.resize(mesh->uvBuffer.size());

        for (size_t i = 0; i < mesh->vertexBuffer.size(); i++) {
            VSInput vsInput;
            vsInput.position = mesh->vertexBuffer[i];
            vsInput.color = mesh->colorBuffer[i];
            vsInput.uv = mesh->uvBuffer[i];

            const auto vsOutput = MyVertexShader(vsInput);

            this->vertexBuffer[i] = vsOutput.position;
            this->colorBuffer[i] = vsOutput.color;
            this->uvBuffer[i] = vsOutput.uv;
        }

        this->indexBuffer = mesh->indexBuffer;

        for (size_t i = 0; i < this->indexBuffer.size(); i += 3) {
            DrawIndexedTriangle(i, pixels);
        }
    }
}

void Rasterization::Update() {}

} // namespace hlab
