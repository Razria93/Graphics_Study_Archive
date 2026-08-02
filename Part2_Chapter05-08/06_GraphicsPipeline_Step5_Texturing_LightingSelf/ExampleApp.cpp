#include "ExampleApp.h"

#include <tuple>
#include <vector>

namespace hlab {

using namespace std;

auto MakeBox() {

    vector<Vector3> positions;
    vector<Vector3> normals;
    vector<Vector2> texcoords; 

    const float scale = 1.0f;

    positions.push_back(Vector3(-1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, -1.0f) * scale);
    normals.push_back(Vector3(0.0f, +1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, +1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, +1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, +1.0f, 0.0f));
    texcoords.push_back(Vector2(0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 1.0f));

    positions.push_back(Vector3(-1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, +1.0f) * scale);
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    texcoords.push_back(Vector2(0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 1.0f));

    positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    texcoords.push_back(Vector2(0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 1.0f));

    positions.push_back(Vector3(-1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, +1.0f) * scale);
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 1.0f));

    positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(-1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, -1.0f) * scale);
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    texcoords.push_back(Vector2(0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 1.0f));

    positions.push_back(Vector3(+1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, -1.0f) * scale);
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    texcoords.push_back(Vector2(0.0f, 1.0f));
    texcoords.push_back(Vector2(0.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 0.0f));
    texcoords.push_back(Vector2(1.0f, 1.0f));

    vector<Vertex> vertices;
    for (size_t i = 0; i < positions.size(); i++) {
        Vertex v;
        v.position = positions[i];
        v.normal = normals[i];
        v.texcoord = texcoords[i];
        vertices.push_back(v);
    }

    vector<uint16_t> indices = {
        0,  1,  2,  0,  2,  3,  
        4,  5,  6,  4,  6,  7,  
        8,  9,  10, 8,  10, 11, 
        12, 13, 14, 12, 14, 15, 
        16, 17, 18, 16, 18, 19, 
        20, 21, 22, 20, 22, 23  
    };

    return tuple{vertices, indices};
}

ExampleApp::ExampleApp()
    : AppBase(), m_indexCount(0), m_lightConstantBufferData() {}

bool ExampleApp::Initialize() {

    if (!AppBase::Initialize())
        return false;

    if (!AppBase::CreateTexture("generated_dark_wood.png", m_texture_0,
                                m_textureResourceView_0))
        return false;

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_device->CreateSamplerState(&sampDesc,
                                            m_samplerState.GetAddressOf()))) {
        cout << "CreateSamplerState() failed." << endl;
        return false;
    }

    auto [vertices, indices] = MakeBox();

    if (!AppBase::CreateVertexBuffer(vertices, m_vertexBuffer))
        return false;

    m_indexCount = UINT(indices.size());

    if (!AppBase::CreateIndexBuffer(indices, m_indexBuffer))
        return false;

    m_constantBufferData.model = Matrix();
    m_constantBufferData.view = Matrix();
    m_constantBufferData.projection = Matrix();
    m_constantBufferData.normalMatrix = Matrix();

    if (!AppBase::CreateConstantBuffer(m_constantBufferData, m_constantBuffer))
        return false;

    if (!AppBase::CreateConstantBuffer(m_lightConstantBufferData,
                                       m_lightConstantBuffer))
        return false;

    if (!AppBase::CreateConstantBuffer(m_materialConstantBufferData,
                                       m_materialConstantBuffer))
        return false;






    vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 3 + 4 * 3,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    if (!AppBase::CreateVertexShaderAndInputLayout(
            L"ColorVertexShader.hlsl", inputElements, m_colorVertexShader,
            m_colorInputLayout))
        return false;

    if (!AppBase::CreatePixelShader(L"ColorPixelShader.hlsl",
                                    m_colorPixelShader))
        return false;

    return true;
}

void ExampleApp::Update(float dt) {

    using namespace DirectX;

    m_constantBufferData.model = Matrix::CreateScale(m_modelScaling) *
                                 Matrix::CreateRotationY(m_modelRotation.y) *
                                 Matrix::CreateRotationX(m_modelRotation.x) *
                                 Matrix::CreateRotationZ(m_modelRotation.z) *
                                 Matrix::CreateTranslation(m_modelTranslation);

    m_constantBufferData.normalMatrix =
        m_constantBufferData.model.Invert().Transpose();

    m_constantBufferData.model = m_constantBufferData.model.Transpose();
    m_constantBufferData.normalMatrix = m_constantBufferData.normalMatrix.Transpose();

    m_constantBufferData.view =
        XMMatrixLookToLH(m_viewEyePos, m_viewEyeDir, m_viewUp);
    m_constantBufferData.view = m_constantBufferData.view.Transpose();

    if (m_usePerspectiveProjection) 
    {
        m_constantBufferData.projection = XMMatrixPerspectiveFovLH(
            XMConvertToRadians(m_projFovAngleY), m_aspect, m_nearZ, m_farZ);
    } else {
        m_constantBufferData.projection = XMMatrixOrthographicOffCenterLH(
            -m_aspect, m_aspect, -1.0f, 1.0f, m_nearZ, m_farZ);
    }
    m_constantBufferData.projection =
        m_constantBufferData.projection.Transpose();

    m_lightConstantBufferData.viewPos = m_viewEyePos;

    AppBase::UpdateBuffer(m_constantBufferData, m_constantBuffer);
    AppBase::UpdateBuffer(m_lightConstantBufferData, m_lightConstantBuffer);
    AppBase::UpdateBuffer(m_materialConstantBufferData,
                          m_materialConstantBuffer);
}

void ExampleApp::Render() {


    m_context->RSSetViewports(1, &m_screenViewport);

    float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    m_context->ClearDepthStencilView(m_depthStencilView.Get(),
                                     D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                     1.0f, 0);

    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(),
                                  m_depthStencilView.Get());
    m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

    m_context->VSSetShader(m_colorVertexShader.Get(), 0, 0);


    m_context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

    ID3D11ShaderResourceView *pixelResources_0[1] = {
        m_textureResourceView_0.Get()};
    m_context->PSSetShaderResources(0, 1, pixelResources_0);
    m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());

    m_context->PSSetConstantBuffers(0, 1, m_lightConstantBuffer.GetAddressOf());
    m_context->PSSetConstantBuffers(1, 1, m_materialConstantBuffer.GetAddressOf());
    m_context->PSSetShader(m_colorPixelShader.Get(), 0, 0);
    m_context->RSSetState(m_rasterizerSate.Get());

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetInputLayout(m_colorInputLayout.Get());
    m_context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride,
                                  &offset);
    m_context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context->DrawIndexed(m_indexCount, 0, 0);
}

void ExampleApp::UpdateGUI() 
{
    ImGui::Text("Object Settings");
    ImGui::Checkbox("usePerspectiveProjection", &m_usePerspectiveProjection);

    ImGui::SliderFloat3("m_modelTranslation", &m_modelTranslation.x, -2.0f,
                        2.0f);
    ImGui::SliderFloat3("m_modelRotation(Rad)", &m_modelRotation.x, -3.14f,
                        3.14f);
    ImGui::SliderFloat3("m_modelScaling", &m_modelScaling.x, 0.1f, 2.0f);

    ImGui::SliderFloat3("m_viewEyePos", &m_viewEyePos.x, -4.0f, 4.0f);
    ImGui::SliderFloat3("m_viewEyeDir", &m_viewEyeDir.x, -4.0f, 4.0f);
    ImGui::SliderFloat3("m_viewUp", &m_viewUp.x, -2.0f, 2.0f);

    ImGui::SliderFloat("m_projFovAngleY(Deg)", &m_projFovAngleY, 10.0f, 180.0f);
    ImGui::SliderFloat("m_nearZ", &m_nearZ, 0.01f, 10.0f);
    ImGui::SliderFloat("m_farZ", &m_farZ, 0.01f, 10.0f);
    ImGui::SliderFloat("m_aspect", &m_aspect, 1.0f, 3.0f);


    ImGui::Separator();
    ImGui::Text("Light Settings");

    ImGui::SliderFloat3("lightPos", &m_lightConstantBufferData.lightPos.x,
                        -4.0f, 4.0f);
    ImGui::SliderFloat3("lightAmbient",
                        &m_lightConstantBufferData.lightAmbient.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("lightDiffuse",
                        &m_lightConstantBufferData.lightDiffuse.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("lightSpecular",
                        &m_lightConstantBufferData.lightSpecular.x, 0.0f, 1.0f);

    ImGui::SliderFloat("kc", &m_lightConstantBufferData.kc, 0.0f, 1.0f);
    ImGui::SliderFloat("kl", &m_lightConstantBufferData.kl, 0.0f, 1.0f);
    ImGui::SliderFloat("kq", &m_lightConstantBufferData.kq, 0.0f, 1.0f);


    ImGui::Separator();
    ImGui::Text("Material Settings");

    ImGui::SliderFloat3("matAmbient",
                        &m_materialConstantBufferData.matAmbient.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("matDiffuse",
                        &m_materialConstantBufferData.matDiffuse.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("matSpecular",
                        &m_materialConstantBufferData.matSpecular.x, 0.0f, 1.0f);

    ImGui::SliderFloat("shininess", &m_materialConstantBufferData.shininess,
                       1.0f, 100.0f);


}

} 
