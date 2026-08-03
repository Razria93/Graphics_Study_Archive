#pragma once

#include <algorithm>
#include <iostream>
#include <memory>

#include "AppBase.h"
#include "GeometryGenerator.h"

namespace hlab {

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector4;


struct Material {
    Vector3 ambient = Vector3(0.1f);
    float shininess = 1.0f;
    Vector3 diffuse = Vector3(0.5f);
    float dummy1;
    Vector3 specular = Vector3(0.5f);
    float dummy2;
};


struct Light {

    Vector3 strength = Vector3(1.0f);
    float fallOffStart = 0.0f;
    Vector3 direction = Vector3(0.0f, 0.0f, 1.0f);
    float fallOffEnd = 10.0f;
    Vector3 position = Vector3(0.0f, 0.0f, -2.0f);
    float spotPower = 1.0f;
};


struct VertexConstantBuffer {
    Matrix model;
    Matrix invTranspose;
    Matrix view;
    Matrix projection;
};








static_assert((sizeof(VertexConstantBuffer) % 16) == 0,
              "Constant Buffer size must be 16-byte aligned");

#define MAX_LIGHTS 3

struct PixelConstantBuffer {
    Vector3 eyeWorld;
    bool useTexture;
    Material material;
    Light lights[MAX_LIGHTS];
};

static_assert((sizeof(PixelConstantBuffer) % 16) == 0,
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
    ComPtr<ID3D11Buffer> m_vertexConstantBuffer;
    ComPtr<ID3D11Buffer> m_pixelShaderConstantBuffer;
    UINT m_indexCount;


    ComPtr<ID3D11Texture2D> m_texture;
    ComPtr<ID3D11ShaderResourceView> m_textureResourceView;
    ComPtr<ID3D11SamplerState> m_samplerState;

    VertexConstantBuffer m_vertexConstantBufferData;
    PixelConstantBuffer m_pixelConstantBufferData;

    bool m_usePerspectiveProjection = true;
    Vector3 m_modelTranslation = Vector3(0.0f);
    Vector3 m_modelRotation = Vector3(-0.35f, 0.55f, 0.0f);
    Vector3 m_modelScaling = Vector3(0.5f);
    float m_viewRot = 0.0f;

    float m_projFovAngleY = 70.0f;
    float m_nearZ = 0.01f;
    float m_farZ = 100.0f;

    int m_lightType = 0;
    Light m_lightFromGUI;
    float m_materialDiffuse = 0.7f;
    float m_materialSpecular = 0.2f;
};
}
