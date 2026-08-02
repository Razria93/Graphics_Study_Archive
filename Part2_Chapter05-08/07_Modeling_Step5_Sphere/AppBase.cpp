


#include "AppBase.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <dxgi.h>
#include <dxgi1_4.h>
#include <algorithm>



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace hlab {

using namespace std;



AppBase *g_appBase = nullptr;


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {


    return g_appBase ? g_appBase->MsgProc(hWnd, msg, wParam, lParam)
                     : DefWindowProc(hWnd, msg, wParam, lParam);
}


AppBase::AppBase()
    : m_screenWidth(1280), m_screenHeight(960), m_mainWindow(0),
      m_screenViewport(D3D11_VIEWPORT()) {

    g_appBase = this;
}

AppBase::~AppBase() {
    g_appBase = nullptr;


    if (ImGui::GetCurrentContext()) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    if (m_mainWindow)
        DestroyWindow(m_mainWindow);








}

float AppBase::GetAspectRatio() const {
    const float width = (std::max)(m_screenViewport.Width, 1.0f);
    const float height = (std::max)(m_screenViewport.Height, 1.0f);
    return width / height;
}

int AppBase::Run() {


    MSG msg = {0};
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else if (!m_isMinimized && m_renderResourcesReady) {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();

            ImGui::NewFrame();
            ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
            ImGui::SetNextWindowSize(
                ImVec2((std::min)(420.0f, float(m_screenWidth) * 0.45f),
                       float(m_screenHeight)),
                ImGuiCond_Always);
            ImGui::Begin("Scene Control", nullptr,
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoCollapse);


            ImGui::Text("Average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);

            UpdateGUI();

            UpdateSceneViewport(ImGui::GetWindowWidth());

            ImGui::End();
            ImGui::Render();

            Update(ImGui::GetIO().DeltaTime);

            Render();

            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



            m_swapChain->Present(1, 0);
        }
    }

    return 0;
}

bool AppBase::Initialize() {

    if (!InitMainWindow())
        return false;

    if (!InitDirect3D())
        return false;

    if (!InitGUI())
        return false;

    return true;
}

LRESULT AppBase::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:




        if (wParam == SIZE_MINIMIZED || LOWORD(lParam) == 0 ||
            HIWORD(lParam) == 0) {
            m_isMinimized = true;
            m_renderResourcesReady = false;
            break;
        }
        m_isMinimized = false;
        if (m_swapChain && !ResizeClientResources(LOWORD(lParam),
                                                  HIWORD(lParam))) {
            PostQuitMessage(1);
        }

        break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_MOUSEMOVE:

        break;
    case WM_LBUTTONUP:

        break;
    case WM_RBUTTONUP:

        break;
    case WM_KEYDOWN:

        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

bool AppBase::InitMainWindow() {

    WNDCLASSEX wc = {sizeof(WNDCLASSEX),
                     CS_CLASSDC,
                     WndProc,
                     0L,
                     0L,
                     GetModuleHandle(NULL),
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     L"HongLabGraphics",
                     NULL};




    if (!RegisterClassEx(&wc)) {
        cout << "RegisterClassEx() failed." << endl;
        return false;
    }






    RECT wr = {0, 0, m_screenWidth, m_screenHeight};



    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);


    m_mainWindow = CreateWindow(
        wc.lpszClassName,
        L"ComputerGraphics - Chapter07 Step5 Sphere",
                                WS_OVERLAPPEDWINDOW,
                                100,
                                100,
                                wr.right - wr.left,
                                wr.bottom - wr.top,
                                NULL, NULL, wc.hInstance, NULL);

    if (!m_mainWindow) {
        cout << "CreateWindow() failed." << endl;
        return false;
    }

    ShowWindow(m_mainWindow, SW_SHOWDEFAULT);
    UpdateWindow(m_mainWindow);

    return true;
}

bool AppBase::InitDirect3D() {






    const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;







    UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;

    const D3D_FEATURE_LEVEL featureLevels[2] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_9_3};
    D3D_FEATURE_LEVEL featureLevel;

    if (FAILED(D3D11CreateDevice(
            nullptr,
            driverType,
            0,
            createDeviceFlags,
            featureLevels,
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,

            device.GetAddressOf(),
            &featureLevel,
            context.GetAddressOf()
            ))) {
        cout << "D3D11CreateDevice() failed." << endl;
        return false;
    }


    if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
        cout << "D3D Feature Level 11 unsupported." << endl;
        return false;
    }








    device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
                                           &m_msaaQualityLevels);
    if (m_msaaQualityLevels <= 0) {
        cout << "MSAA not supported." << endl;
    }



    if (FAILED(device.As(&m_device))) {
        cout << "device.AS() failed." << endl;
        return false;
    }

    if (FAILED(context.As(&m_context))) {
        cout << "context.As() failed." << endl;
        return false;
    }

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferDesc.Width = m_screenWidth;
    sd.BufferDesc.Height = m_screenHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferCount = 2;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage =
        DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_mainWindow;
    sd.Windowed = TRUE;
    sd.Flags =
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    if (m_msaaQualityLevels > 0) {
        sd.SampleDesc.Count = 4;
        sd.SampleDesc.Quality = m_msaaQualityLevels - 1;
    } else {
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
    }

    if (FAILED(D3D11CreateDeviceAndSwapChain(
            0,
            driverType,
            0,
            createDeviceFlags, featureLevels, 1, D3D11_SDK_VERSION, &sd,
            m_swapChain.GetAddressOf(), m_device.GetAddressOf(), &featureLevel,
            m_context.GetAddressOf()))) {
        cout << "D3D11CreateDeviceAndSwapChain() failed." << endl;
        return false;
    }






    if (!CreateRenderTargetView() || !CreateDepthBuffer())
        return false;
    UpdateSceneViewport(0.0f);


    D3D11_RASTERIZER_DESC rastDesc_Fill;
    ZeroMemory(&rastDesc_Fill, sizeof(D3D11_RASTERIZER_DESC));
    rastDesc_Fill.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

    rastDesc_Fill.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rastDesc_Fill.FrontCounterClockwise = false;
    rastDesc_Fill.DepthClipEnable = true;

    if (FAILED(m_device->CreateRasterizerState(
            &rastDesc_Fill, m_solidRasterizerState.GetAddressOf()))) {
        cout << "Create solid rasterizer state failed." << endl;
        return false;
    }



    D3D11_RASTERIZER_DESC rastDesc_Wire;
    ZeroMemory(&rastDesc_Wire, sizeof(D3D11_RASTERIZER_DESC));
    rastDesc_Wire.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    rastDesc_Wire.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rastDesc_Wire.FrontCounterClockwise = false;
    rastDesc_Wire.DepthClipEnable = true;

    if (FAILED(m_device->CreateRasterizerState(
            &rastDesc_Wire, m_wireRasterizerState.GetAddressOf()))) {
        cout << "Create wire rasterizer state failed." << endl;
        return false;
    }


    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask =
        D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc =
        D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
    if (FAILED(m_device->CreateDepthStencilState(
            &depthStencilDesc, m_depthStencilState.GetAddressOf()))) {
        cout << "CreateDepthStencilState() failed." << endl;
        return false;
    }
    m_renderResourcesReady = true;
    return true;
}

bool AppBase::InitGUI() {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.DisplaySize = ImVec2(float(m_screenWidth), float(m_screenHeight));
    ImGui::StyleColorsLight();


    if (!ImGui_ImplDX11_Init(m_device.Get(), m_context.Get())) {
        return false;
    }

    if (!ImGui_ImplWin32_Init(m_mainWindow)) {
        return false;
    }

    return true;
}

void AppBase::UpdateSceneViewport(float panelWidth) {
    const float safeWidth = (std::max)(float(m_screenWidth) - panelWidth, 1.0f);
    const float safeHeight = (std::max)(float(m_screenHeight), 1.0f);
    m_screenViewport = {};
    m_screenViewport.TopLeftX = panelWidth;
    m_screenViewport.Width = safeWidth;
    m_screenViewport.Height = safeHeight;
    m_screenViewport.MinDepth = 0.0f;
    m_screenViewport.MaxDepth = 1.0f;
}

bool AppBase::CreateRenderTargetView() {

    ComPtr<ID3D11Texture2D> backBuffer;
    if (FAILED(m_swapChain->GetBuffer(
            0, IID_PPV_ARGS(backBuffer.GetAddressOf()))) || !backBuffer) {
        std::cout << "CreateRenderTargetView() failed." << std::endl;
        return false;
    }
    if (FAILED(m_device->CreateRenderTargetView(
            backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf()))) {
        std::cout << "CreateRenderTargetView() failed." << std::endl;
        return false;
    }

    return true;
}

bool AppBase::CreateDepthBuffer() {
    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    depthStencilBufferDesc.Width = m_screenWidth;
    depthStencilBufferDesc.Height = m_screenHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    if (m_msaaQualityLevels > 0) {
        depthStencilBufferDesc.SampleDesc.Count = 4;
        depthStencilBufferDesc.SampleDesc.Quality = m_msaaQualityLevels - 1;
    } else {
        depthStencilBufferDesc.SampleDesc.Count = 1;
        depthStencilBufferDesc.SampleDesc.Quality = 0;
    }
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;

    if (FAILED(m_device->CreateTexture2D(
            &depthStencilBufferDesc, 0, m_depthStencilBuffer.GetAddressOf()))) {
        std::cout << "CreateTexture2D() failed." << std::endl;
        return false;
    }
    if (FAILED(m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0,
                                                &m_depthStencilView))) {
        std::cout << "CreateDepthStencilView() failed." << std::endl;
        return false;
    }
    return true;
}

bool AppBase::ResizeClientResources(UINT width, UINT height) {
    if (!m_swapChain || width == 0 || height == 0)
        return false;

    m_renderResourcesReady = false;
    m_context->OMSetRenderTargets(0, nullptr, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_depthStencilBuffer.Reset();

    const HRESULT hr = m_swapChain->ResizeBuffers(
        0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(hr)) {
        cout << "ResizeBuffers() failed. " << hex << hr << endl;
        return false;
    }

    m_screenWidth = int(width);
    m_screenHeight = int(height);
    if (!CreateRenderTargetView() || !CreateDepthBuffer())
        return false;

    UpdateSceneViewport(0.0f);
    m_renderResourcesReady = true;
    return true;
}













void CheckResult(HRESULT hr, ID3DBlob *errorBlob) {
    if (FAILED(hr)) {

        if ((hr & D3D11_ERROR_FILE_NOT_FOUND) != 0) {
            cout << "File not found." << endl;
        }


        if (errorBlob) {
            cout << "Shader compile error\n"
                 << (char *)errorBlob->GetBufferPointer() << endl;
        }
    }
}

bool AppBase::CreateVertexShaderAndInputLayout(
    const wstring &filename,
    const vector<D3D11_INPUT_ELEMENT_DESC> &inputElements,
    ComPtr<ID3D11VertexShader> &vertexShader,
    ComPtr<ID3D11InputLayout> &inputLayout) {

    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif



    HRESULT hr = D3DCompileFromFile(
        filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
        "vs_5_0", compileFlags, 0, &shaderBlob, &errorBlob);

    CheckResult(hr, errorBlob.Get());
    if (FAILED(hr) || !shaderBlob)
        return false;

    if (FAILED(m_device->CreateVertexShader(shaderBlob->GetBufferPointer(),
                                            shaderBlob->GetBufferSize(), NULL,
                                            &vertexShader)))
        return false;

    return SUCCEEDED(m_device->CreateInputLayout(
        inputElements.data(), UINT(inputElements.size()),
        shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
        &inputLayout));
}

bool AppBase::CreatePixelShader(const wstring &filename,
                                ComPtr<ID3D11PixelShader> &pixelShader) {
    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif



    HRESULT hr = D3DCompileFromFile(
        filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
        "ps_5_0", compileFlags, 0, &shaderBlob, &errorBlob);

    CheckResult(hr, errorBlob.Get());
    if (FAILED(hr) || !shaderBlob)
        return false;

    return SUCCEEDED(m_device->CreatePixelShader(
        shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), NULL,
        &pixelShader));
}

bool AppBase::CreateIndexBuffer(const std::vector<uint16_t> &indices,
                                ComPtr<ID3D11Buffer> &indexBuffer) {
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bufferDesc.ByteWidth = UINT(sizeof(uint16_t) * indices.size());
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.StructureByteStride = sizeof(uint16_t);

    D3D11_SUBRESOURCE_DATA indexBufferData = {0};
    indexBufferData.pSysMem = indices.data();
    indexBufferData.SysMemPitch = 0;
    indexBufferData.SysMemSlicePitch = 0;

    return SUCCEEDED(m_device->CreateBuffer(
        &bufferDesc, &indexBufferData, indexBuffer.GetAddressOf()));
}

bool AppBase::CreateTexture(
    const std::string &filename, ComPtr<ID3D11Texture2D> &texture,
    ComPtr<ID3D11ShaderResourceView> &textureResourceView) {

    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char *img =
        stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (!img) {
        cout << "Texture load failed: " << filename << endl;
        return false;
    }



    std::vector<uint8_t> image;

    image.resize(size_t(width) * size_t(height) * 4);
    memcpy(image.data(), img, image.size() * sizeof(uint8_t));
    stbi_image_free(img);


    D3D11_TEXTURE2D_DESC txtDesc = {};
    txtDesc.Width = width;
    txtDesc.Height = height;
    txtDesc.MipLevels = txtDesc.ArraySize = 1;
    txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    txtDesc.SampleDesc.Count = 1;
    txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
    txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;


    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = image.data();
    InitData.SysMemPitch = txtDesc.Width * sizeof(uint8_t) * 4;


    if (FAILED(m_device->CreateTexture2D(
            &txtDesc, &InitData, texture.GetAddressOf())))
        return false;
    return SUCCEEDED(m_device->CreateShaderResourceView(
        texture.Get(), nullptr, textureResourceView.GetAddressOf()));
}

}
