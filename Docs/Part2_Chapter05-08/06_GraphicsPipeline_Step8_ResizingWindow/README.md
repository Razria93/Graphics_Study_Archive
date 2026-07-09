# 06 GraphicsPipeline Step8 ResizingWindow

## 목적

window 크기가 바뀔 때 swap chain buffer, render target view, depth stencil buffer/view, viewport를 함께 갱신하는 예제입니다. Step7이 ImGui 영역을 제외한 viewport 계산에 집중했다면, Step8은 실제 window resize event에 맞춰 D3D11 rendering target을 다시 구성하는 흐름을 다룹니다.

이 archive에서는 실행 가능한 source/project/shader/asset만 포함하고, 원문 학습 주석은 source 밖으로 분리합니다.

## 핵심 키워드

- `WM_SIZE`
- `ResizeBuffers()`
- render target view recreation
- depth stencil buffer recreation
- `D3D11_VIEWPORT`
- viewport resizing
- swap chain back buffer

## 구현 흐름

1. `WM_SIZE` 메시지에서 새 client width/height를 읽습니다.
2. 현재 render target/depth stencil view 참조를 정리합니다.
3. `IDXGISwapChain::ResizeBuffers()`로 back buffer 크기를 갱신합니다.
4. 새 back buffer에서 render target view를 다시 생성합니다.
5. 새 window 크기에 맞춰 depth stencil buffer/view를 다시 생성합니다.
6. ImGui control panel 영역을 제외한 scene viewport를 다시 계산하고 `RSSetViewports()`로 적용합니다.

## 핵심 코드

```cpp
m_screenWidth = int(LOWORD(lParam));
m_screenHeight = int(HIWORD(lParam));

m_renderTargetView.Reset();
m_depthStencilView.Reset();
m_depthStencilBuffer.Reset();
```

window resize 시 새 크기를 저장하고 기존 render target/depth stencil 관련 view와 resource 참조를 정리합니다.

```cpp
m_swapChain->ResizeBuffers(0, (UINT)LOWORD(lParam),
                           (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
CreateRenderTargetView();
SetViewport();
```

swap chain back buffer를 새 크기에 맞게 재생성하고, render target과 viewport도 함께 갱신합니다.

## Archive 반영 메모

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step8_ResizingWindow`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow`
- 원문 학습 주석은 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/source-comments.md`에 분리했습니다.
- `.vs/`, `x64/`, `.user`, `imgui.ini`, `.clang-format`, raw build output은 archive에 포함하지 않았습니다.
- 실행에 필요한 `crate2_diffuse.png`, `wall.jpg`는 private archive asset으로 포함했습니다.
- texture asset은 public 공개 전 license/source 확인이 필요합니다.
- HLSL/HLSLI 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.
- raw project의 Release HLSL 설정에 shader type 누락이 있어 archive project에서 Release용 pixel/vertex shader 설정을 보강했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 이유: private archive 학습 예제이고 texture asset을 포함합니다. public subset으로 분리하기 전 asset license/source, 강의 기반 구조 표현 정도, dependency 재현성을 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
