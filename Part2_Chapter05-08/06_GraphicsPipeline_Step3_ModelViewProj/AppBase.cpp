


#include "AppBase.h"

#include <dxgi.h>    
#include <dxgi1_4.h> 



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

namespace hlab {

using namespace std;



AppBase *g_appBase = nullptr;


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    
    return g_appBase->MsgProc(hWnd, msg, wParam, lParam);
}


AppBase::AppBase()
    : m_screenWidth(1280), m_screenHeight(960), m_mainWindow(0),
      m_screenViewport(D3D11_VIEWPORT()) {

    g_appBase = this;
}

AppBase::~AppBase() {
    g_appBase = nullptr;

    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    DestroyWindow(m_mainWindow);
    

    
    
    
    
    
    
}

float AppBase::GetAspectRatio() const { return float(m_screenWidth) / m_screenHeight; }

int AppBase::Run() {

    
    MSG msg = {0};
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            ImGui_ImplDX11_NewFrame(); 
            ImGui_ImplWin32_NewFrame();

            ImGui::NewFrame(); 
            ImGui::Begin("Scene Control");

            
            ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);

            UpdateGUI(); 

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

    
    m_mainWindow = CreateWindow(wc.lpszClassName, L"HongLabGraphics Example", WS_OVERLAPPEDWINDOW,
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

    
    
    
    

    
    UINT numQualityLevels;
    device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &numQualityLevels);
    if (numQualityLevels <= 0) {
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
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  
    sd.OutputWindow = m_mainWindow;                    
    sd.Windowed = TRUE;                                
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; 
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    if (numQualityLevels > 0) {
        sd.SampleDesc.Count = 4; 
        sd.SampleDesc.Quality = numQualityLevels - 1;
    } else {
        sd.SampleDesc.Count = 1; 
        sd.SampleDesc.Quality = 0;
    }

    if (FAILED(D3D11CreateDeviceAndSwapChain(
            0, 
            driverType,
            0, 
            createDeviceFlags, featureLevels, 1, D3D11_SDK_VERSION, &sd, m_swapChain.GetAddressOf(),
            m_device.GetAddressOf(), &featureLevel, m_context.GetAddressOf()))) {
        cout << "D3D11CreateDeviceAndSwapChain() failed." << endl;
        return false;
    }

    
    

    
    

    
    ComPtr<ID3D11Texture2D> backBuffer;
    m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
    if (backBuffer) {
        m_device->CreateRenderTargetView(backBuffer.Get(), NULL, m_renderTargetView.GetAddressOf());
    } else {
        cout << "CreateRenderTargetView() failed." << endl;
        return false;
    }

    
    ZeroMemory(&m_screenViewport, sizeof(D3D11_VIEWPORT));
    m_screenViewport.TopLeftX = 0;
    m_screenViewport.TopLeftY = 0;
    m_screenViewport.Width = float(m_screenWidth);
    m_screenViewport.Height = float(m_screenHeight);
    
    m_screenViewport.MinDepth = 0.0f;
    m_screenViewport.MaxDepth = 1.0f; 

    m_context->RSSetViewports(1, &m_screenViewport);

    
    D3D11_RASTERIZER_DESC rastDesc;
    ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC)); 
    rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    
    rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rastDesc.FrontCounterClockwise = false;
    rastDesc.DepthClipEnable = true; 

    m_device->CreateRasterizerState(&rastDesc, m_rasterizerSate.GetAddressOf());

    

    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    depthStencilBufferDesc.Width = m_screenWidth;
    depthStencilBufferDesc.Height = m_screenHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    if (numQualityLevels > 0) {
        depthStencilBufferDesc.SampleDesc.Count = 4; 
        depthStencilBufferDesc.SampleDesc.Quality = numQualityLevels - 1;
    } else {
        depthStencilBufferDesc.SampleDesc.Count = 1; 
        depthStencilBufferDesc.SampleDesc.Quality = 0;
    }
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;

    if (FAILED(m_device->CreateTexture2D(&depthStencilBufferDesc, 0,
                                         m_depthStencilBuffer.GetAddressOf()))) {
        cout << "CreateTexture2D() failed." << endl;
    }
    if (FAILED(
            m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, &m_depthStencilView))) {
        cout << "CreateDepthStencilView() failed." << endl;
    }

    

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = true; 
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
    if (FAILED(m_device->CreateDepthStencilState(&depthStencilDesc,
                                                 m_depthStencilState.GetAddressOf()))) {
        cout << "CreateDepthStencilState() failed." << endl;
    }

    return true;
}

bool AppBase::InitGUI() {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
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













void CheckResult(HRESULT hr, ID3DBlob *errorBlob) {
    if (FAILED(hr)) {
        
        if ((hr & D3D11_ERROR_FILE_NOT_FOUND) != 0) {
            cout << "File not found." << endl;
        }

        
        if (errorBlob) {
            cout << "Shader compile error\n" << (char *)errorBlob->GetBufferPointer() << endl;
        }
    }
}

void AppBase::CreateVertexShaderAndInputLayout(
    const wstring &filename, const vector<D3D11_INPUT_ELEMENT_DESC> &inputElements,
    ComPtr<ID3D11VertexShader> &vertexShader, ComPtr<ID3D11InputLayout> &inputLayout) {

    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    
    HRESULT hr =
        D3DCompileFromFile(filename.c_str(), 0, 0, "main", "vs_5_0", 0, 0, &shaderBlob, &errorBlob);

    CheckResult(hr, errorBlob.Get());

    m_device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), NULL,
                                 &vertexShader);

    m_device->CreateInputLayout(inputElements.data(), UINT(inputElements.size()),
                                shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
                                &inputLayout);
}

void AppBase::CreatePixelShader(const wstring &filename, ComPtr<ID3D11PixelShader> &pixelShader) {
    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    
    HRESULT hr =
        D3DCompileFromFile(filename.c_str(), 0, 0, "main", "ps_5_0", 0, 0, &shaderBlob, &errorBlob);

    CheckResult(hr, errorBlob.Get());

    m_device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), NULL,
                                &pixelShader);
}

void AppBase::CreateIndexBuffer(const std::vector<uint16_t> &indices,
                                ComPtr<ID3D11Buffer> &m_indexBuffer) {
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

    m_device->CreateBuffer(&bufferDesc, &indexBufferData, m_indexBuffer.GetAddressOf());
}

} 