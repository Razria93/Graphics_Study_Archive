# 01_DX11InitAndImGui

## Overview

이 예제는 Win32 window 위에 DirectX11 device, device context, swap chain, back buffer render target을 만들고, CPU에서 갱신한 작은 canvas texture를 full-screen quad로 출력하는 최소 렌더링 루프를 보여준다. ImGui overlay는 배경색을 조정하는 UI로 사용된다.

핵심은 창을 띄우는 것 자체보다, CPU 메모리의 픽셀 배열이 DirectX11 dynamic texture로 올라가고 shader resource view를 통해 pixel shader에서 읽힌 뒤 back buffer로 출력되는 흐름이다.

## File Map

| 파일 | 역할 |
| --- | --- |
| `main.cpp` | Win32 window 생성, ImGui 초기화, message/render loop 구성 |
| `Example.h::Initialize()` | D3D11 device/swap chain, render target, viewport, texture, quad geometry 생성 |
| `Example.h::InitShaders()` | HLSL compile, shader object, input layout 생성 |
| `Example.h::Update()` | CPU-side pixel buffer 생성과 dynamic texture upload |
| `Example.h::Render()` | shader/resource binding 후 indexed draw 수행 |
| `Example.h::Clean()` | D3D11 resource release |
| `VS.hlsl` | full-screen quad vertex shader |
| `PS.hlsl` | canvas texture sampling pixel shader |

## Rendering Flow

1. `WNDCLASSEX`와 `CreateWindow()`로 Win32 window를 만든다.
2. `D3D11CreateDeviceAndSwapChain()`으로 device, device context, swap chain을 만든다.
3. swap chain back buffer에서 `RenderTargetView`를 만들어 최종 출력 대상으로 사용한다.
4. `VS.hlsl`, `PS.hlsl`을 컴파일하고 input layout을 설정한다.
5. CPU가 쓸 수 있는 `D3D11_USAGE_DYNAMIC` texture를 만들고 `ShaderResourceView`로 노출한다.
6. `Update()`에서 `std::vector<Vec4>` 픽셀 배열을 만들고 `Map` / `memcpy` / `Unmap`으로 texture에 업로드한다.
7. `Render()`에서 full-screen quad를 그리고 pixel shader가 canvas texture를 샘플링한다.
8. ImGui draw data를 렌더링한 뒤 swap chain `Present()`로 화면에 표시한다.

## Core Concepts

### Device / Device Context / Swap Chain

`ID3D11Device`는 GPU resource를 생성하고, `ID3D11DeviceContext`는 render command와 resource binding을 기록한다. `IDXGISwapChain`은 back buffer와 front buffer를 교체해 window에 최종 이미지를 표시한다.

### Render Target View

Back buffer texture는 그대로 output merger stage에 연결할 수 없다. `CreateRenderTargetView()`로 render target view를 만든 뒤 `OMSetRenderTargets()`에 바인딩해야 GPU가 최종 색을 쓸 수 있다.

### Dynamic Texture Upload

`D3D11_USAGE_DYNAMIC`과 `D3D11_CPU_ACCESS_WRITE`를 사용하면 CPU가 매 프레임 texture 내용을 갱신할 수 있다. `Map`으로 CPU write pointer를 얻고, `memcpy`로 픽셀 배열을 복사한 뒤, `Unmap`으로 GPU가 다시 읽을 수 있게 돌려준다.

### Shader Resource View

Texture resource를 pixel shader에서 읽으려면 `ShaderResourceView`가 필요하다. 이 예제에서는 CPU가 갱신한 canvas texture를 `PSSetShaderResources()`로 pixel shader에 전달한다.

### Full-Screen Quad

예제의 vertex/index buffer는 화면 전체를 덮는 quad를 만든다. Pixel shader는 각 fragment에서 canvas texture를 샘플링하므로, 작은 canvas texture가 화면 전체에 확대되어 표시된다.

## Demo Points

- ImGui slider로 `backgroundColor`를 바꾸면 CPU-side pixel buffer의 기본색이 바뀐다.
- 작은 canvas texture가 full-screen quad를 통해 화면 전체에 표시된다.
- 움직이는 RGB 픽셀은 CPU에서 매 프레임 texture 내용을 다시 쓰는 흐름을 보여준다.
- ImGui는 예제 렌더링 이후 overlay로 그려진다.

## Limitations

- 예제 편의상 구현 대부분이 `Example.h`에 들어 있다.
- `Sleep(100)`으로 animation이 의도적으로 느리게 보이도록 되어 있다.
- window resize 시 swap chain과 render target을 다시 만드는 처리는 구현되어 있지 않다.
- shader 파일 경로는 실행 working directory에 의존한다.
- 이 예제는 3D scene 구성보다 DirectX11 초기화와 texture upload 흐름을 설명하기 위한 기반 예제다.

## Verification

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 미확인 | 직접 재검증 필요 |
| Release x64 build/run | 미확인 | 직접 재검증 필요 |
| Capture | 미확인 | 최소 capture 후보로만 유지 |

## Related Docs

- `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`
- `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`
