#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

#include "D3D11Utils.h"

namespace hlab {

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector4;
using std::vector;

struct BillboardPointsConstantData {
    Vector3 eyeWorld;
    float width;
    Matrix model; // Vertex shader
    Matrix view;  // Vertex shader
    Matrix proj;  // Pixel shader
};

static_assert((sizeof(BillboardPointsConstantData) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

class BillboardPoints {
  public:
    void Initialize(ComPtr<ID3D11Device> &device,
                    const std::vector<Vector4> &points);

    void Render(ComPtr<ID3D11DeviceContext> &context);

  public:
    BillboardPointsConstantData m_constantData;

    // 편의상 ConstantBuffer를 하나만 사용
    ComPtr<ID3D11Buffer> m_constantBuffer;

  protected:
    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11SamplerState> m_samplerState;
    ComPtr<ID3D11VertexShader> m_vertexShader;
    ComPtr<ID3D11GeometryShader> m_geometryShader;
    ComPtr<ID3D11PixelShader> m_pixelShader;
    ComPtr<ID3D11InputLayout> m_inputLayout;

    uint32_t m_indexCount = 0;

    // HERE : 
    // C++ 인터페이스 상에서 데이터를 구성하는 단계에서는 Array를 별도로 만들지 않고 ID3D11Texture2D를 사용함
    // 그러나 HLSL를 사용하는 쉐이더에서는 2DArray가 별도로 있음
    ComPtr<ID3D11Texture2D> m_texArray;
    ComPtr<ID3D11ShaderResourceView> m_texArraySRV;
};
} // namespace hlab