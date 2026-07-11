#pragma once

#include "Rasterization.h"

#include <algorithm>
#include <chrono>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

namespace hlab {
using namespace glm;
using namespace std;

struct Vertex {
    glm::vec4 pos;
    glm::vec2 uv;
};

class Example {

  public:
    Example(HWND window, int width, int height);

    void Update();
    void Render();

    void InitShaders();
    void Initialize(HWND window, int width, int height);
    void Clean();

  public:
    int width, height;
    std::vector<vec4> pixels;
    Rasterization rasterization;

    ID3D11Device *device;
    ID3D11DeviceContext *deviceContext;
    IDXGISwapChain *swapChain;
    D3D11_VIEWPORT viewport;
    ID3D11RenderTargetView *renderTargetView;
    ID3D11VertexShader *vertexShader;
    ID3D11PixelShader *pixelShader;
    ID3D11InputLayout *layout;

    ID3D11Buffer *vertexBuffer = nullptr;
    ID3D11Buffer *indexBuffer = nullptr;
    ID3D11Texture2D *canvasTexture = nullptr;
    ID3D11ShaderResourceView *canvasTextureView = nullptr;
    ID3D11RenderTargetView *canvasRenderTargetView = nullptr;
    ID3D11SamplerState *colorSampler;
    UINT indexCount;
};
} // namespace hlab
