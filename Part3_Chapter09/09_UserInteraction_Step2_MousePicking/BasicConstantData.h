#pragma once

#include <directxtk/SimpleMath.h>

#include "Light.h"
#include "Material.h"

namespace hlab {

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector3;

struct BasicVertexConstantData {
    Matrix model;
    Matrix invTranspose;
    Matrix view;
    Matrix projection;
};

static_assert((sizeof(BasicVertexConstantData) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

struct BasicPixelConstantData 
{
    Vector3 eyeWorld;         // 12
    bool useTexture;          // 4
    Material material;        // 48
    Light lights[MAX_LIGHTS]; // 48 * MAX_LIGHTS
	bool isPickingSphere;      // 4
	float padding[3];
};

// C++ 에서 만든 bool = 1바이트
// HLSL에서 해석하는 bool = 4바이트
// 
// 그래서 GPU는 데이터를 잘못 읽고,
// 픽킹용 색상(indexColor) 같은 게 틀어져 버릴 수 있습니다.

static_assert((sizeof(BasicPixelConstantData) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

struct NormalVertexConstantData {
    float scale = 0.1f;
    float dummy[3];
};

} // namespace hlab
