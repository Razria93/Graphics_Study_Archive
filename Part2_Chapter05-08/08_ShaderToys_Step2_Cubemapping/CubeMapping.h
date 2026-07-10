#pragma once

#include <wrl.h>

#include "GeometryGenerator.h"
#include "Material.h"
#include "Vertex.h"

namespace hlab {

using Microsoft::WRL::ComPtr;

struct CubeMapping {

    std::shared_ptr<Mesh> cubeMesh;                         // Sphere도 사용가능 -> 만들어보기

    ComPtr<ID3D11ShaderResourceView> cubemapResourceView;   // 텍스처를 Resource로 쓸 수 있게 해주는 View객체

    ComPtr<ID3D11VertexShader> vertexShader;                // 큐브 매핑할 때 사용하는 쉐이더들은 다름. 조금 더 단순함
    ComPtr<ID3D11PixelShader> pixelShader;
    ComPtr<ID3D11InputLayout> inputLayout;
};
} // namespace hlab