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

    HWND hwnd = CreateWindow(wc.lpszClassName, L"HongLabGraphics Example",
                             WS_OVERLAPPEDWINDOW, 100, 100, wr.right - wr.left,
                             wr.bottom - wr.top, NULL, NULL, wc.hInstance,
                             NULL);

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
            ImGui::Checkbox("cullBackface",
                            &example->rasterization.cullBackface);
            ImGui::SliderAngle("Object RotationAboutX",
                               &example->rasterization.object->transformation
                                    .rotationX);
            ImGui::SliderAngle("Object RotationAboutY",
                               &example->rasterization.object->transformation
                                    .rotationY);
            ImGui::SliderFloat3(
                "Object Translation",
                &example->rasterization.object->transformation.translation[0],
                -3.0f, 4.0f);
            ImGui::SliderFloat3(
                "Object Scale",
                &example->rasterization.object->transformation.scale[0], 0.1f,
                2.0f);
            ImGui::SliderFloat3(
                "Material Ambient",
                &example->rasterization.object->material.matAmbient[0], 0.0f,
                1.0f);
            ImGui::SliderFloat3(
                "Material Diffuse",
                &example->rasterization.object->material.matDiffuse[0], 0.0f,
                1.0f);
            ImGui::SliderFloat3(
                "Material Specular",
                &example->rasterization.object->material.matSpecular[0], 0.0f,
                1.0f);
            ImGui::SliderFloat("Material shininess",
                               &example->rasterization.object->material
                                    .shininess,
                               0.0f, 256.0f);

            if (ImGui::SliderFloat3("Light Direction",
                                    &example->rasterization.light.direction[0],
                                    -3.0f, 3.0f)) {
                if (glm::length(example->rasterization.light.direction) >
                    1e-5f) {
                    example->rasterization.light.direction = glm::normalize(
                        example->rasterization.light.direction);
                }
            }

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
