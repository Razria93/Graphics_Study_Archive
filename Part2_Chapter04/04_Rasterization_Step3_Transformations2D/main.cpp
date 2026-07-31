#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <iostream>
#include <memory>
#include <windows.h>

#include "Example.h"

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main() {
    const int width = 1280, height = 960;

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

    RegisterClassEx(&wc);

    RECT wr = {0, 0, width, height};

    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindow(wc.lpszClassName,
                             L"ComputerGraphics - Step3 Transformations2D",
                             WS_OVERLAPPEDWINDOW,
                             100,
                             100,
                             wr.right - wr.left,
                             wr.bottom - wr.top,
                             NULL, NULL, wc.hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    auto example = std::make_unique<hlab::Example>(hwnd, width, height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.DisplaySize = ImVec2(width, height);
    ImGui::StyleColorsLight();

    ImGui_ImplDX11_Init(example->device, example->deviceContext);
    ImGui_ImplWin32_Init(hwnd);

    MSG msg = {};
    while (WM_QUIT != msg.message) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            ImGui::Begin("Scene Control");

            // Controls feed the CPU-side transform pipeline in Rasterization::Update().
            ImGui::SliderFloat("Rotation1", &example->rasterization.rotation1,
                               -3.141592f * 2.0f, 3.141592f * 2.0f);
            ImGui::SliderFloat("ScaleX", &example->rasterization.scaleX, -2.0f,
                               2.0f);
            ImGui::SliderFloat("ScaleY", &example->rasterization.scaleY, -2.0f,
                               2.0f);
            ImGui::SliderFloat3("Translation1",
                                &example->rasterization.translation1[0], -1.0f,
                                1.0f);
            ImGui::SliderFloat("Rotation2", &example->rasterization.rotation2,
                               -3.141592f * 2.0f, 3.141592f * 2.0f);
            ImGui::SliderFloat3("Translation2",
                                &example->rasterization.translation2[0], -1.0f,
                                1.0f);

            ImGui::End();
            ImGui::Render();

            example->Update();
            example->Render();

            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            example->swapChain->Present(1, 0);
        }
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    example->Clean();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        return 0;
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

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
