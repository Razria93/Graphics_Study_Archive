#include "ExampleApp.h"

#include <tuple>
#include <vector>

namespace hlab {

using namespace std;

auto MakeBox() {

    vector<Vector3> positions;
    vector<Vector3> colors;
    vector<Vector3> normals;

    const float scale = 1.0f;

    
    positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
    positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
    positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
    positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
    colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
    colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
    colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
    colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, 1.0f, 0.0f));

    
    positions.push_back(Vector3(-1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, +1.0f) * scale);
    colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
    colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
    colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
    colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, -1.0f, 0.0f));

    
    positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, -1.0f) * scale);
    colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
    colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
    colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
    colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, -1.0f));

    
    positions.push_back(Vector3(-1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, +1.0f) * scale);
    colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
    colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
    colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
    colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(0.0f, 0.0f, 1.0f));

    
    positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    positions.push_back(Vector3(-1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(-1.0f, +1.0f, -1.0f) * scale);
    colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
    colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
    colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
    colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));

    
    positions.push_back(Vector3(+1.0f, +1.0f, -1.0f) * scale);
    positions.push_back(Vector3(+1.0f, +1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, +1.0f) * scale);
    positions.push_back(Vector3(+1.0f, -1.0f, -1.0f) * scale);
    colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
    colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
    colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
    colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    normals.push_back(Vector3(1.0f, 0.0f, 0.0f));


    vector<Vertex> vertices;
    for (size_t i = 0; i < positions.size(); i++) {
        Vertex v;
        v.position = positions[i];
        v.color = colors[i];
        vertices.push_back(v);
    }

    vector<uint16_t> indices = {
        0,  1,  2,  0,  2,  3,  
        4,  5,  6,  4,  6,  7,  
        8,  9,  10, 8,  10, 11, 
        12, 13, 14, 12, 14, 15, 
        16, 17, 18, 16, 18, 19, 
        20, 21, 22, 20, 22, 23, 
    };

    return tuple{vertices, indices};
}

ExampleApp::ExampleApp() : AppBase(), m_indexCount(0) {}

bool ExampleApp::Initialize() {

    if (!AppBase::Initialize())
        return false;

    
    auto [vertices, indices] = MakeBox();

    
    AppBase::CreateVertexBuffer(vertices, m_vertexBuffer);

    
    m_indexCount = UINT(indices.size());

    AppBase::CreateIndexBuffer(indices, m_indexBuffer);

    
    m_constantBufferData.model = Matrix();
    m_constantBufferData.view = Matrix();
    m_constantBufferData.projection = Matrix();

    AppBase::CreateConstantBuffer(m_constantBufferData, m_constantBuffer);

    

    
    
    

    
    
    
    
    

    vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    AppBase::CreateVertexShaderAndInputLayout(L"ColorVertexShader.hlsl", inputElements,
                                              m_colorVertexShader, m_colorInputLayout);

    AppBase::CreatePixelShader(L"ColorPixelShader.hlsl", m_colorPixelShader);

    return true;
}

void ExampleApp::Update(float dt) {

    static float rot = 0.0f;
    rot += dt;

    
    m_constantBufferData.model = Matrix::CreateScale(0.5f) * Matrix::CreateRotationY(rot) *
                                 Matrix::CreateTranslation(Vector3(0.0f, -0.3f, 1.0f));
    m_constantBufferData.model = m_constantBufferData.model.Transpose();

    using namespace DirectX;

    
    m_constantBufferData.view =
        XMMatrixLookAtLH({0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
    m_constantBufferData.view = m_constantBufferData.view.Transpose();

    
    const float aspect = AppBase::GetAspectRatio();
    if (m_usePerspectiveProjection) {
        const float fovAngleY = 70.0f * XM_PI / 180.0f;
        m_constantBufferData.projection =
            XMMatrixPerspectiveFovLH(fovAngleY, aspect, 0.01f, 100.0f);
    } else {
        m_constantBufferData.projection =
            XMMatrixOrthographicOffCenterLH(-aspect, aspect, -1.0f, 1.0f, 0.1f, 10.0f);
    }
    m_constantBufferData.projection = m_constantBufferData.projection.Transpose();

    
    AppBase::UpdateBuffer(m_constantBufferData, m_constantBuffer);
}

void ExampleApp::Render() {

    
    
    
    
    

    m_context->RSSetViewports(1, &m_screenViewport);

    float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
    m_context->ClearDepthStencilView(m_depthStencilView.Get(),
                                     D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    
    
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

    
    m_context->VSSetShader(m_colorVertexShader.Get(), 0, 0);

    

    m_context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
    m_context->PSSetShader(m_colorPixelShader.Get(), 0, 0);

    m_context->RSSetState(m_rasterizerSate.Get());

    
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetInputLayout(m_colorInputLayout.Get());
    m_context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    m_context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context->DrawIndexed(m_indexCount, 0, 0);
}

void ExampleApp::UpdateGUI() {
    ImGui::Checkbox("usePerspectiveProjection", &m_usePerspectiveProjection);
}

} 
