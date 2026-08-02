# Chapter06 Step2 InitializingD3D

이 예제는 Win32 window와 D3D11 device resource를 초기화하고 shader·buffer·MVP constant buffer를 연결해 회전 color cube를 화면에 표시한다. Chapter06 Step1의 device·context ownership에서 출발해 swap chain, render target, depth buffer, viewport와 frame loop를 연결하는 첫 end-to-end graphics pipeline 단계다.

## 실행 진입점

- Solution: `06_GraphicsPipeline_Step2_InitializingD3D.sln`
- Application entry: `main.cpp`
- 주요 source: `AppBase.cpp`, `ExampleApp.cpp`
- Shader: `ColorVertexShader.hlsl`, `ColorPixelShader.hlsl`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter06 Step2 InitializingD3D`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Frame loop와 Present](AppBase.cpp#L58-L95) | Win32 message 처리, ImGui frame, scene draw와 swap chain presentation |
| [Device와 immediate context 생성](AppBase.cpp#L198-L247) | Hardware device 생성과 feature level 선택 |
| [Swap chain과 back buffer view](AppBase.cpp#L253-L317) | MSAA 수준 선택, swap chain 생성과 render target view 연결 |
| [Viewport와 depth resource](AppBase.cpp#L320-L382) | rasterizer, viewport, depth buffer·view·state 초기화 |
| [Cube resource와 shader 준비](ExampleApp.cpp#L10-L170) | vertex/index/constant buffer와 color shader 구성 |
| [고정 MVP와 projection 선택](ExampleApp.cpp#L173-L204) | 회전 model, 고정 view와 perspective·orthographic projection 계산 |
| [Pipeline binding과 draw](ExampleApp.cpp#L206-L245) | render target clear, pipeline resource binding과 indexed draw |

## 구현 요약

`AppBase`는 window와 device resource를 순서대로 만든 뒤 `ExampleApp`의 scene resource 초기화를 호출한다. 매 frame에는 message queue를 처리하고 scene constant buffer를 갱신한 다음 `DrawIndexed()`로 cube를 그려 `Present(1, 0)`으로 back buffer를 표시한다.

Cube는 position과 face color를 가진 indexed geometry다. Model matrix는 Y축 회전을 누적하고 고정 view·projection과 함께 constant buffer로 전달된다. 기본값은 perspective projection이며 checkbox는 orthographic path의 존재만 확인한다. Projection parameter 조작과 비교는 다음 Step3의 책임으로 둔다.

일반 device·context 역할은 [Device And Context](../../Docs/01_Topics/DirectX11Pipeline/DeviceAndContext.md), presentation surface 관계는 [Swap Chain And Viewport](../../Docs/01_Topics/DirectX11Pipeline/SwapChainAndViewport.md), 실제 구현과 시각 결과는 [Step2 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, exit code 0 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, exit code 0 |
| Graphics output | 성공 | 기본 perspective에서 회전 color cube와 Scene Control 확인 |
| Capture/Result | 확보 | 기본 perspective 전체 창 screenshot, 자동 기술 검수와 사용자 시각 확인 완료 |

## Capture/Result

기본 perspective 상태의 전체 application window 한 장을 확보했다. 다색 cube의 두 면과 모서리, Scene Control과 application title을 함께 확인한다. Orthographic 조정 screenshot과 video는 초기화 결과를 추가로 설명하지 않으므로 제외하고, projection과 camera parameter 비교는 Step3에서 다룬다.

![Chapter06 Step2 InitializingD3D 기본 perspective](../../Docs/_assets/captures/part2_chapter06_02_initializing_d3d.png)

## 구현 범위와 한계

- Device 생성과 `D3D11CreateDeviceAndSwapChain()` 호출이 분리되어 device·context를 두 번 생성한다.
- Back buffer는 raw pointer로 받고 수동 `Release()`하며 이후 단계의 일관된 `ComPtr` ownership은 아직 적용하지 않는다.
- `WM_SIZE`에서 swap chain buffer와 dependent view를 재생성하지 않아 runtime resize를 지원하지 않는다.
- Shader는 project 폴더 기준 상대 경로로 compile하므로 다른 working directory에서 실행하면 실패할 수 있다.
- Shader compile과 일부 resource 생성의 `HRESULT` 검사가 충분하지 않다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 범위에서 제외한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter06 Step1 COM](../06_GraphicsPipeline_Step1_COM/README.md)
- 다음 단계: Chapter06 Step3 ModelViewProj 문서화 대기
- [Device And Context Topic](../../Docs/01_Topics/DirectX11Pipeline/DeviceAndContext.md)
- [Swap Chain And Viewport Topic](../../Docs/01_Topics/DirectX11Pipeline/SwapChainAndViewport.md)
- [Step2 InitializingD3D 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
