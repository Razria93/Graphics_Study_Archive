# Chapter06 Step7 ResizingViewport

이 예제는 Step6의 textured lighting scene을 유지하면서 ImGui control panel과 scene rendering 영역을 하나의 render target 안에서 분리한다. Panel의 현재 너비를 기준으로 scene viewport의 시작점과 너비를 정하고 projection aspect ratio를 남은 영역에 맞춘다.

## 실행 진입점

- Solution: `06_GraphicsPipeline_Step7_ResizingViewport.sln`
- Application entry: `main.cpp`
- 주요 source: `AppBase.cpp`, `AppBase.h`, `ExampleApp.cpp`, `ExampleApp.h`
- Shader: `BasicVertexShader.hlsl`, `BasicPixelShader.hlsl`, `Common.hlsli`
- Runtime input: `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter06 Step7 ResizingViewport`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Panel 기반 viewport 계산](AppBase.cpp#L543-L556) | Panel 너비를 화면 범위로 제한하고 scene viewport rectangle 구성 |
| [Frame별 panel 너비 반영](AppBase.cpp#L71-L81) | ImGui window를 왼쪽에 배치하고 현재 너비를 viewport 계산에 전달 |
| [Projection aspect 갱신](ExampleApp.cpp#L220-L231) | Scene viewport의 실제 너비와 높이로 perspective·orthographic projection 갱신 |
| [Viewport binding과 scene draw](ExampleApp.cpp#L254-L292) | 계산한 viewport를 rasterizer에 binding하고 Step6 scene draw |
| [Texture·Light parameter UI](ExampleApp.cpp#L295-L337) | Texture, transform, projection과 Directional·Point·Spot parameter 유지 |

## Step6와의 차이

Step6는 전체 render target을 scene viewport로 사용하고 ImGui panel을 그 위에 합성한다. Step7은 같은 back buffer와 depth resource를 유지하면서 panel 너비만큼 `TopLeftX`를 옮기고 scene viewport의 `Width`를 줄인다. Scene은 panel 오른쪽에서 시작하므로 UI와 겹치지 않는다.

Viewport는 render target resource가 아니라 rasterization 결과를 배치하는 rectangle이다. Step7은 viewport만 바꾸며 swap chain buffer, render target view와 depth resource를 재생성하지 않는다. 실제 client size 변경과 dependent resource 재생성은 Step8 ResizingWindow의 책임이다.

## 구현 요약

Frame을 시작할 때 ImGui panel을 왼쪽 위에 배치하고 현재 window width를 읽는다. `UpdateSceneViewport()`는 panel width를 `0`부터 `screenWidth - 1` 사이로 제한한 뒤 남은 폭을 최소 1px 이상으로 유지한다.

`GetAspectRatio()`는 고정 window 크기가 아니라 계산된 scene viewport의 `Width / Height`를 반환한다. `ExampleApp::Update()`는 이 값을 projection matrix에 반영하고, `Render()`는 scene draw 직전에 `RSSetViewports()`를 한 번 호출한다. Render target 전체는 검은색으로 clear하므로 panel 아래와 scene 밖 영역은 의도된 검은 배경으로 남는다.

Step6의 generated 목재 texture, box geometry와 Directional·Point·Spot lighting 경로는 유지한다. 출처가 불명확하고 실제로 사용하지 않던 `crate2_diffuse.png`, `wall.jpg`와 두 번째 texture resource는 제거한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Viewport 분리 | 성공 | 420px 기본 panel 오른쪽에서 scene 시작, geometry 왜곡 없음 |
| Texture·Lighting 유지 | 성공 | Generated 목재 texture와 Directional Light 기본 결과 확인 |
| Capture/Result | 확보 | Release 전체 창 screenshot 기술 검수와 사용자 승인 완료 |

## Capture/Result

왼쪽 `Scene Control` panel과 panel 오른쪽에서 시작하는 scene viewport를 하나의 전체 창 screenshot으로 확인한다. Textured box는 줄어든 viewport 비율에 맞춰 표시되며 UI와 겹치지 않는다.

![Chapter06 Step7 ResizingViewport](../../Docs/_assets/captures/part2_chapter06_07_resizing_viewport.png)

Build 중 vcpkg가 먼저 호출하는 `pwsh.exe`는 이 환경에 없지만 Windows PowerShell fallback이 완료되어 MSBuild는 오류 없이 성공했다.

## 구현 범위와 한계

- 하나의 고정 크기 render target 안에서 panel과 scene viewport를 분리한다.
- Panel 너비는 runtime에서 바뀔 수 있지만 window client size는 이 단계에서 바꾸지 않는다.
- `WM_SIZE`, `ResizeBuffers()`, render target view와 depth resource 재생성은 포함하지 않는다.
- Panel이 화면 너비에 가까워져도 scene viewport를 최소 1px로 제한하지만 유용한 화면 크기까지 보장하지 않는다.
- Runtime shader와 texture load는 project 폴더 CWD에 의존한다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 범위에서 제외한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter06 Step6 Lighting](../06_GraphicsPipeline_Step6_Lighting/README.md)
- 다음 단계: Chapter06 Step8 ResizingWindow 문서화 대기
- [Swap Chain And Viewport Topic](../../Docs/01_Topics/DirectX11Pipeline/SwapChainAndViewport.md)
- [Step7 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/07_ResizingViewport.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
