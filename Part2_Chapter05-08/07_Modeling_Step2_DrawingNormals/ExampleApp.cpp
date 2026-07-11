#include "ExampleApp.h"

#include <tuple>
#include <vector>

#include "GeometryGenerator.h"

namespace hlab {

using namespace std;

ExampleApp::ExampleApp() : AppBase(), m_BasicPixelConstantBufferData() {}

bool ExampleApp::Initialize() {

    if (!AppBase::Initialize())
        return false;




    AppBase::CreateTexture("crate2_diffuse.png", m_texture,
                           m_textureResourceView);
    AppBase::CreateTexture("wall.jpg", m_texture2, m_textureResourceView2);


    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;


    m_device->CreateSamplerState(&sampDesc, m_samplerState.GetAddressOf());


    MeshData meshData = GeometryGenerator::MakeBox();

    m_mesh = std::make_shared<Mesh>();

    AppBase::CreateVertexBuffer(meshData.vertices, m_mesh->m_vertexBuffer);
    m_mesh->m_indexCount = UINT(meshData.indices.size());
    AppBase::CreateIndexBuffer(meshData.indices, m_mesh->m_indexBuffer);


    m_BasicVertexConstantBufferData.model = Matrix();
    m_BasicVertexConstantBufferData.view = Matrix();
    m_BasicVertexConstantBufferData.projection = Matrix();

    AppBase::CreateConstantBuffer(m_BasicVertexConstantBufferData,
                                  m_mesh->m_vertexConstantBuffer);

    AppBase::CreateConstantBuffer(m_BasicPixelConstantBufferData,
                                  m_mesh->m_pixelConstantBuffer);

    vector<D3D11_INPUT_ELEMENT_DESC> basicInputElements = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 3 + 4 * 3,
         D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    AppBase::CreateVertexShaderAndInputLayout(
        L"BasicVertexShader.hlsl", basicInputElements, m_basicVertexShader,
        m_basicInputLayout);

    AppBase::CreatePixelShader(L"BasicPixelShader.hlsl", m_basicPixelShader);







    m_normalLines = std::make_shared<Mesh>();


    std::vector<Vertex> normalVertices;
    std::vector<uint16_t> normalIndices;
    for (size_t i = 0; i < meshData.vertices.size(); i++) 
    {
        auto v = meshData.vertices[i];

        v.texcoord.x = 0.0f;
        normalVertices.push_back(v);

        v.texcoord.x = 1.0f;
        normalVertices.push_back(v);

        normalIndices.push_back(uint16_t(2 * i));
        normalIndices.push_back(uint16_t(2 * i + 1));
    }


    AppBase::CreateVertexBuffer(normalVertices, m_normalLines->m_vertexBuffer);
   


    m_normalLines->m_indexCount = UINT(normalIndices.size()); 
    AppBase::CreateIndexBuffer(normalIndices, m_normalLines->m_indexBuffer);



    m_normalVertexConstantBufferData.model = Matrix();
    m_normalVertexConstantBufferData.invTranspose = Matrix();
    m_normalVertexConstantBufferData.view = Matrix();
    m_normalVertexConstantBufferData.projection = Matrix();

    AppBase::CreateConstantBuffer(m_normalVertexConstantBufferData,
        m_normalLines->m_vertexConstantBuffer);
   

    AppBase::CreateVertexShaderAndInputLayout(L"NormalVertexShader.hlsl", basicInputElements, m_normalVertexShader,m_basicInputLayout);

    AppBase::CreatePixelShader(L"NormalPixelShader.hlsl", m_normalPixelShader);


    return true;
}

void ExampleApp::Update(float dt) {

    using namespace DirectX;





    m_BasicVertexConstantBufferData.model =
        Matrix::CreateScale(m_modelScaling) *
        Matrix::CreateRotationY(m_modelRotation.y) *
        Matrix::CreateRotationX(m_modelRotation.x) *
        Matrix::CreateRotationZ(m_modelRotation.z) *
        Matrix::CreateTranslation(m_modelTranslation);

    m_BasicVertexConstantBufferData.model =
        m_BasicVertexConstantBufferData.model.Transpose();


    m_normalVertexConstantBufferData.model =
        m_BasicVertexConstantBufferData.model;




    m_BasicVertexConstantBufferData.invTranspose =
        m_BasicVertexConstantBufferData.model;
    m_BasicVertexConstantBufferData.invTranspose.Translation(Vector3(0.0f));
    m_BasicVertexConstantBufferData.invTranspose =
        m_BasicVertexConstantBufferData.invTranspose.Transpose().Invert();


    m_normalVertexConstantBufferData.invTranspose =
        m_BasicVertexConstantBufferData.invTranspose;




    m_BasicVertexConstantBufferData.view =
        Matrix::CreateRotationY(m_viewRot) *
        Matrix::CreateTranslation(0.0f, 0.0f, 2.0f);

    m_BasicPixelConstantBufferData.eyeWorld = Vector3::Transform(
        Vector3(0.0f), m_BasicVertexConstantBufferData.view.Invert());


    m_BasicVertexConstantBufferData.view =
        m_BasicVertexConstantBufferData.view.Transpose();


    m_normalVertexConstantBufferData.view =
        m_BasicVertexConstantBufferData.view;




    const float aspect = AppBase::GetAspectRatio();
    if (m_usePerspectiveProjection) {
        m_BasicVertexConstantBufferData.projection = XMMatrixPerspectiveFovLH(
            XMConvertToRadians(m_projFovAngleY), aspect, m_nearZ, m_farZ);
    } else {
        m_BasicVertexConstantBufferData.projection =
            XMMatrixOrthographicOffCenterLH(-aspect, aspect, -1.0f, 1.0f,
                                            m_nearZ, m_farZ);
    }


    m_BasicVertexConstantBufferData.projection =
        m_BasicVertexConstantBufferData.projection.Transpose();


    m_normalVertexConstantBufferData.projection =
        m_BasicVertexConstantBufferData.projection;





    AppBase::UpdateBuffer(m_BasicVertexConstantBufferData,
                          m_mesh->m_vertexConstantBuffer);

    m_BasicPixelConstantBufferData.material.diffuse =
        Vector3(m_materialDiffuse);
    m_BasicPixelConstantBufferData.material.specular =
        Vector3(m_materialSpecular);


    for (int i = 0; i < MAX_LIGHTS; i++) {

        if (i != m_lightType) {
            m_BasicPixelConstantBufferData.lights[i].strength *= 0.0f;
        } else {
            m_BasicPixelConstantBufferData.lights[i] = m_lightFromGUI;
        }
    }

    AppBase::UpdateBuffer(m_BasicPixelConstantBufferData,
                          m_mesh->m_pixelConstantBuffer);






    if (!m_drawNormals) 
    {
        m_normalVertexConstantBufferData.scale = 0.0f;
    }
    else
    {
        m_normalVertexConstantBufferData.scale = m_scale;
    }


    AppBase::UpdateBuffer(m_normalVertexConstantBufferData,
        m_normalLines->m_vertexConstantBuffer);


}

void ExampleApp::Render() {







    SetViewport();

    float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};



    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    m_context->ClearDepthStencilView(m_depthStencilView.Get(),
                                     D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                     1.0f, 0);
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(),
                                  m_depthStencilView.Get());
    m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);


    m_context->VSSetShader(m_basicVertexShader.Get(), 0, 0);
    m_context->VSSetConstantBuffers(
        0, 1, m_mesh->m_vertexConstantBuffer.GetAddressOf());

    ID3D11ShaderResourceView *pixelResources[2] = {
        m_textureResourceView.Get(), m_textureResourceView2.Get()};
    m_context->PSSetShaderResources(0, 2, pixelResources);
    m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());

    m_context->PSSetConstantBuffers(
        0, 1, m_mesh->m_pixelConstantBuffer.GetAddressOf());
    m_context->PSSetShader(m_basicPixelShader.Get(), 0, 0);

    if (m_drawAsWire) {
        m_context->RSSetState(m_wireRasterizerSate.Get());
    } else {
        m_context->RSSetState(m_solidRasterizerSate.Get());
    }


    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetInputLayout(m_basicInputLayout.Get());
    m_context->IASetVertexBuffers(0, 1, m_mesh->m_vertexBuffer.GetAddressOf(),
                                  &stride, &offset);
    m_context->IASetIndexBuffer(m_mesh->m_indexBuffer.Get(),
                                DXGI_FORMAT_R16_UINT, 0);
    m_context->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context->DrawIndexed(m_mesh->m_indexCount, 0, 0);



    if (m_drawNormals) 
    {
        m_context->VSSetShader(m_normalVertexShader.Get(), 0, 0);
        m_context->VSSetConstantBuffers(0, 1, m_normalLines->m_vertexConstantBuffer.GetAddressOf());

        m_context->PSSetShader(m_normalPixelShader.Get(), 0, 0);
        m_context->PSSetConstantBuffers(0, 1, m_normalLines->m_pixelConstantBuffer.GetAddressOf());



        m_context->IASetVertexBuffers(0, 1, m_normalLines->m_vertexBuffer.GetAddressOf(), &stride, &offset);
        m_context->IASetIndexBuffer(m_normalLines->m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

        m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        m_context->DrawIndexed(m_normalLines->m_indexCount, 0, 0);
    }
}

void ExampleApp::UpdateGUI() {

    ImGui::Checkbox("Use Texture", &m_BasicPixelConstantBufferData.useTexture);
    ImGui::Checkbox("Wireframe", &m_drawAsWire);
    ImGui::Checkbox("Draw Normals", &m_drawNormals);
    ImGui::SliderFloat("Normal scale", &m_scale, 0.0f, 1.0f);
    ImGui::SliderFloat3("m_modelTranslation", &m_modelTranslation.x, -2.0f,
                        2.0f);
    ImGui::SliderFloat3("m_modelRotation", &m_modelRotation.x, -3.14f, 3.14f);
    ImGui::SliderFloat3("m_modelScaling", &m_modelScaling.x, 0.1f, 2.0f);
    ImGui::SliderFloat("m_viewRot", &m_viewRot, -3.14f, 3.14f);

    ImGui::SliderFloat("Material Shininess",
                       &m_BasicPixelConstantBufferData.material.shininess, 1.0f,
                       256.0f);

    if (ImGui::RadioButton("Directional Light", m_lightType == 0)) {
        m_lightType = 0;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Point Light", m_lightType == 1)) {
        m_lightType = 1;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Spot Light", m_lightType == 2)) {
        m_lightType = 2;
    }

    ImGui::SliderFloat("Material Diffuse", &m_materialDiffuse, 0.0f, 1.0f);
    ImGui::SliderFloat("Material Specular", &m_materialSpecular, 0.0f, 1.0f);

    ImGui::SliderFloat3("Light Position", &m_lightFromGUI.position.x, -5.0f,
                        5.0f);

    ImGui::SliderFloat("Light fallOffStart", &m_lightFromGUI.fallOffStart, 0.0f,
                       5.0f);

    ImGui::SliderFloat("Light fallOffEnd", &m_lightFromGUI.fallOffEnd, 0.0f,
                       10.0f);

    ImGui::SliderFloat("Light spotPower", &m_lightFromGUI.spotPower, 1.0f,
                       512.0f);
}

}
