# Chapter06 Step8 ResizingWindow

이 예제는 Step7의 ImGui panel·scene viewport 분리를 유지하면서 실제 window client size 변경에 맞춰 swap chain back buffer와 depth resource를 재생성한다. 최소화에서는 0×0 resource 생성을 건너뛰고 복원 후 새 크기의 render target, depth buffer, viewport와 projection을 다시 연결한다.

## 실행 진입점

- Solution: `06_GraphicsPipeline_Step8_ResizingWindow.sln`
- Application entry: `main.cpp`
- 주요 source: `AppBase.cpp`, `AppBase.h`, `ExampleApp.cpp`, `ExampleApp.h`
- Shader: `BasicVertexShader.hlsl`, `BasicPixelShader.hlsl`, `Common.hlsli`
- Runtime input: `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter06 Step8 ResizingWindow`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [최소화와 client size 처리](AppBase.cpp#L132-L151) | `WM_SIZE`에서 0×0을 건너뛰고 유효한 client size만 resource 갱신에 전달 |
| [Resize dependent resource 재생성](AppBase.cpp#L486-L518) | OM unbind, 기존 view 해제, `ResizeBuffers()`, RTV·depth 재생성 |
| [Back buffer와 depth view 생성](AppBase.cpp#L442-L484) | 새 swap chain buffer와 client size에 대응하는 render/depth view 생성 |
| [Panel 기반 viewport 계산](AppBase.cpp#L619-L632) | 새 client width에서 panel 오른쪽 scene rectangle과 최소 크기 구성 |
| [Projection aspect 갱신](ExampleApp.cpp#L223-L234) | 재계산한 scene viewport 비율을 perspective·orthographic projection에 반영 |
| [Viewport binding과 scene draw](ExampleApp.cpp#L254-L292) | resize 이후 viewport, RTV·DSV와 Step7 textured lighting scene 연결 |

## Step7과의 차이

Step7은 고정된 render target 안에서 panel과 scene viewport rectangle만 분리한다. Step8은 실제 window client size 변경으로 swap chain back buffer가 바뀌므로 기존 render target view와 depth resource를 해제하고 새 크기로 다시 만든다.

Viewport와 projection은 resource 재생성 이후의 client size와 현재 panel width를 함께 사용한다. 따라서 wide·compact window에서도 geometry 비율과 depth test를 유지한다.

## 구현 요약

`WM_SIZE`는 최소화 또는 0×0 크기일 때 마지막 유효 resource를 보존한다. 유효한 resize에서는 output-merger target을 unbind하고 RTV, DSV와 depth texture를 해제한 뒤 `ResizeBuffers()`를 호출한다. 새 back buffer의 RTV와 같은 크기의 depth resource를 만든 경우에만 rendering을 재개한다.

Frame에서는 Step7과 같은 panel width 기반 scene viewport를 계산한다. `GetAspectRatio()`는 이 viewport의 실제 너비와 높이를 사용하므로 window 크기가 바뀌어도 box가 stretch되지 않는다. Step5~7에서 검수한 generated 목재 texture와 Directional·Point·Spot lighting 경로는 그대로 유지한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| 반복 resize | 성공 | default·wide·compact와 추가 크기 전환 후 rendering 유지 |
| 최소화·복원 | 성공 | 최소화 중 0×0 생성 생략, 복원 후 rendering 재개 |
| Texture·Lighting 유지 | 성공 | Generated 목재 texture와 Directional Light 기본 결과 확인 |
| Capture/Result | 확보 | 세 크기의 Release 전체 창 screenshot 기술·시각 검수 완료 |

## Capture/Result

Default, wide와 compact 전체 창 screenshot은 같은 camera, geometry와 Light 상태에서 client size만 바뀐 결과를 비교한다. Panel과 scene viewport 경계, box 비율과 depth 결과가 세 크기에서 유지된다.

![Chapter06 Step8 ResizingWindow default](../../Docs/_assets/captures/part2_chapter06_08_resizing_window_default.png)

![Chapter06 Step8 ResizingWindow wide](../../Docs/_assets/captures/part2_chapter06_08_resizing_window_wide.png)

![Chapter06 Step8 ResizingWindow compact](../../Docs/_assets/captures/part2_chapter06_08_resizing_window_compact.png)

Build 중 vcpkg가 먼저 호출하는 `pwsh.exe`는 이 환경에 없지만 Windows PowerShell fallback이 완료되어 MSBuild는 오류 없이 성공했다.

## 구현 범위와 한계

- Windowed swap chain의 client resize와 최소화·복원을 다룬다.
- Device-lost 전체 복구, fullscreen 전환, DPI 변경과 multi-monitor 이동은 포함하지 않는다.
- Panel이 client width에 가까워지면 scene viewport는 최소 1px만 보장한다.
- Runtime shader와 texture load는 project 폴더 CWD에 의존한다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 범위에서 제외한다.
- 기존 recorder는 녹화 중 window bounds 변경을 실패로 처리하므로 resize video는 capture 도구 확장 전까지 보류한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter06 Step7 ResizingViewport](../06_GraphicsPipeline_Step7_ResizingViewport/README.md)
- 다음 단계: Chapter06 Step9 PhongVsBlinnPhong 문서화 대기
- [Swap Chain And Viewport Topic](../../Docs/01_Topics/DirectX11Pipeline/SwapChainAndViewport.md)
- [Step8 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/08_ResizingWindow.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
