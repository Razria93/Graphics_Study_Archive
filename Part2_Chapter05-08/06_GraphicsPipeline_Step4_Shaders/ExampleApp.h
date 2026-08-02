#pragma once

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <iostream>
#include <memory>
#include <vector>

#include "AppBase.h"

namespace hlab {

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector4;


struct Vertex 
{
    Vector3 position;
    Vector3 color;
    Vector2 texcoord;
    
};


struct ModelViewProjectionConstantBuffer 
{
    Matrix model;
    Matrix view;
    Matrix projection;
};


struct PSConstantBuffer
{
    Vector4 leftColor;
    Vector4 rightColor;
    float   xSplitPoint;
    Vector3 padding;
    
};








static_assert((sizeof(ModelViewProjectionConstantBuffer) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");
static_assert((sizeof(PSConstantBuffer) % 16) == 0,
              "Pixel shader constant buffer size must be 16-byte aligned");



class ExampleApp : public AppBase {
  public:
    ExampleApp();

    virtual bool Initialize() override;
    virtual void UpdateGUI() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

  protected:
    ComPtr<ID3D11VertexShader> m_colorVertexShader;
    ComPtr<ID3D11PixelShader> m_colorPixelShader;
    ComPtr<ID3D11InputLayout> m_colorInputLayout;

    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11Buffer> m_indexBuffer;
    ComPtr<ID3D11Buffer> m_constantBuffer;
    UINT m_indexCount;

    
    ComPtr<ID3D11Buffer> p_constantBuffer;

    ModelViewProjectionConstantBuffer m_constantBufferData;

    
    PSConstantBuffer p_constantBufferData;

    bool m_usePerspectiveProjection = true;
    Vector3 m_modelTranslation = Vector3(0.0f);
    Vector3 m_modelRotation = Vector3(0.0f);
    Vector3 m_modelScaling = Vector3(0.5f);
    Vector3 m_viewEyePos = {0.0f, 0.0f, -2.0f};
    Vector3 m_viewEyeDir = {0.0f, 0.0f, 1.0f};
    Vector3 m_viewUp = {0.0f, 1.0f, 0.0f};
    float m_projFovAngleY = 70.0f;
    float m_nearZ = 0.01f;
    float m_farZ = 100.0f;
    float m_aspect = AppBase::GetAspectRatio();

    Vector4 p_leftColor;
    Vector4 p_rightColor;
    float   p_xSplitPoint = 0.5f;
    
};
}
