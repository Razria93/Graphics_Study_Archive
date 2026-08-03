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


struct Vertex {
    Vector3 position;
    Vector3 normal;
    Vector2 texcoord;
};


struct ModelViewProjectionConstantBuffer 
{
    Matrix model;
    Matrix view;
    Matrix projection;
    Matrix normalMatrix;
};








static_assert((sizeof(ModelViewProjectionConstantBuffer) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

struct LightConstantBuffer 
{
    Vector3 lightPos = Vector3(0.0f, 0.0f, -1.0f);       
    float padding_0;
    Vector3 lightAmbient = Vector3(0.5f);   
    float padding_1;
    Vector3 lightDiffuse = Vector3(1.0f);   
    float padding_2;
    Vector3 lightSpecular = Vector3(1.0f);  
    float padding_3;

    float kc = 1.0f; 
    float kl = 0.09f; 
    float kq = 0.032f; 
    float padding_4 = 0.0f;

    Vector3 viewPos = Vector3(0.0f, 0.0f, -2.0f);
    float padding_5 = 0.0f;
};

struct MaterialConstantBuffer 
{
    Vector3 matAmbient = Vector3(0.5f);  
    float padding_0;
    Vector3 matDiffuse = Vector3(1.0f);  
    float padding_1;
    Vector3 matSpecular = Vector3(0.5f); 
    float padding_2;

    float shininess = 32.0f; 
    float padding_3[3] = {};
};

static_assert((sizeof(LightConstantBuffer) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

static_assert((sizeof(MaterialConstantBuffer) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

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
    ComPtr<ID3D11Buffer> m_lightConstantBuffer;
    ComPtr<ID3D11Buffer> m_materialConstantBuffer;
    UINT m_indexCount;

    ComPtr<ID3D11Texture2D> m_texture_0;
    ComPtr<ID3D11ShaderResourceView> m_textureResourceView_0;
    ComPtr<ID3D11SamplerState> m_samplerState;

    ModelViewProjectionConstantBuffer m_constantBufferData;
    LightConstantBuffer m_lightConstantBufferData;
    MaterialConstantBuffer m_materialConstantBufferData;

    bool m_usePerspectiveProjection = true;
    Vector3 m_modelTranslation = Vector3(0.0f);
    Vector3 m_modelRotation = Vector3(-0.35f, 0.55f, 0.0f);
    Vector3 m_modelScaling = Vector3(0.5f);
    Vector3 m_viewEyePos = {0.0f, 0.0f, -2.0f};
    Vector3 m_viewEyeDir = {0.0f, 0.0f, 1.0f};
    Vector3 m_viewUp = {0.0f, 1.0f, 0.0f};
    float m_projFovAngleY = 70.0f;
    float m_nearZ = 0.01f;
    float m_farZ = 100.0f;
    float m_aspect = AppBase::GetAspectRatio();
};
}
