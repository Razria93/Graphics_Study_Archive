#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <wrl.h>

namespace hlab {

using Microsoft::WRL::ComPtr;
using std::vector;
using std::wstring;

class AppBase {
  public:
    AppBase();
    virtual ~AppBase();

    float GetAspectRatio() const;
    int Run();

    virtual bool Initialize();
    virtual void UpdateGUI() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    virtual void OnMouseDown(WPARAM btnState, int x, int y){};
    virtual void OnMouseUp(WPARAM btnState, int x, int y){};
    virtual void OnMouseMove(WPARAM btnState, int x, int y){};

  protected:
    bool InitMainWindow();
    bool InitDirect3D();
    bool InitGUI();
    bool CreateRenderTargetView();
    bool CreateDepthBuffer();
    bool ResizeClientResources(UINT width, UINT height);
    bool CreateVertexShaderAndInputLayout(
        const wstring &filename,
        const vector<D3D11_INPUT_ELEMENT_DESC> &inputElements,
        ComPtr<ID3D11VertexShader> &vertexShader,
        ComPtr<ID3D11InputLayout> &inputLayout);
    bool CreatePixelShader(const wstring &filename,
                           ComPtr<ID3D11PixelShader> &pixelShader);
    bool CreateIndexBuffer(const vector<uint16_t> &indices,
                           ComPtr<ID3D11Buffer> &indexBuffer);

    template <typename T_VERTEX>
    bool CreateVertexBuffer(const vector<T_VERTEX> &vertices,
                            ComPtr<ID3D11Buffer> &vertexBuffer) {
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.ByteWidth = UINT(sizeof(T_VERTEX) * vertices.size());
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.StructureByteStride = sizeof(T_VERTEX);

        D3D11_SUBRESOURCE_DATA vertexBufferData = {};
        vertexBufferData.pSysMem = vertices.data();

        const HRESULT hr = m_device->CreateBuffer(
            &bufferDesc, &vertexBufferData, vertexBuffer.GetAddressOf());
        if (FAILED(hr)) {
            std::cout << "CreateVertexBuffer() failed. " << std::hex << hr
                      << std::endl;
            return false;
        }
        return true;
    }

    template <typename T_CONSTANT>
    bool CreateConstantBuffer(const T_CONSTANT &constantBufferData,
                              ComPtr<ID3D11Buffer> &constantBuffer) {
        D3D11_BUFFER_DESC cbDesc = {};
        cbDesc.ByteWidth = sizeof(constantBufferData);
        cbDesc.Usage = D3D11_USAGE_DYNAMIC;
        cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = &constantBufferData;

        const HRESULT hr = m_device->CreateBuffer(
            &cbDesc, &initData, constantBuffer.GetAddressOf());
        if (FAILED(hr)) {
            std::cout << "CreateConstantBuffer() failed." << std::endl;
            return false;
        }
        return true;
    }

    template <typename T_DATA>
    bool UpdateBuffer(const T_DATA &bufferData, ComPtr<ID3D11Buffer> &buffer) {
        if (!buffer) {
            std::cout << "UpdateBuffer() buffer was not initialized."
                      << std::endl;
            return false;
        }

        D3D11_MAPPED_SUBRESOURCE mapped = {};
        if (FAILED(m_context->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0,
                                  &mapped))) {
            std::cout << "UpdateBuffer() Map failed." << std::endl;
            return false;
        }
        memcpy(mapped.pData, &bufferData, sizeof(bufferData));
        m_context->Unmap(buffer.Get(), 0);
        return true;
    }

    bool CreateTexture(const std::string &filename,
                       ComPtr<ID3D11Texture2D> &texture,
                       ComPtr<ID3D11ShaderResourceView> &textureResourceView);
    void UpdateSceneViewport(float panelWidth);

  public:
    int m_screenWidth;
    int m_screenHeight;
    HWND m_mainWindow;
    bool m_isMinimized = false;
    bool m_renderResourcesReady = false;
    UINT m_msaaQualityLevels = 0;

    ComPtr<ID3D11Device> m_device;
    ComPtr<ID3D11DeviceContext> m_context;
    ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11RasterizerState> m_solidRasterizerState;
    ComPtr<ID3D11RasterizerState> m_wireRasterizerState;
    bool m_drawAsWire = false;

    ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;
    ComPtr<ID3D11DepthStencilState> m_depthStencilState;

    D3D11_VIEWPORT m_screenViewport;
};
}
