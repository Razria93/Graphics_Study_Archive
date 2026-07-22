# 06 GraphicsPipeline Step7 ResizingViewport

## 목적

window 전체 크기와 ImGui control 영역을 기준으로 D3D11 rendering viewport를 다시 계산하는 예제입니다. 이전 lighting 예제의 rendering 흐름은 유지하면서, 화면 일부를 UI 영역으로 남기고 나머지 영역에 scene을 그리도록 `D3D11_VIEWPORT`를 관리합니다.

이 archive에서는 실행 가능한 source/project/shader/asset만 포함하고, 원문 학습 주석은 source 밖으로 분리합니다.

## 핵심 키워드

- `D3D11_VIEWPORT`
- `RSSetViewports()`
- viewport resizing
- ImGui control panel
- aspect ratio
- swap chain buffer size
- depth stencil buffer size

## 구현 흐름

1. `AppBase`가 screen width/height와 `D3D11_VIEWPORT` 상태를 보관합니다.
2. ImGui control panel width를 기준으로 scene viewport의 `TopLeftX`, `Width`, `Height`를 계산합니다.
3. `SetViewport()`에서 viewport 값을 갱신하고 rasterizer stage에 binding합니다.
4. render 직전에 `RSSetViewports()`로 현재 viewport를 적용합니다.
5. camera aspect ratio는 ImGui 영역을 제외한 scene viewport 크기를 기준으로 계산합니다.

## 핵심 코드

```cpp
m_screenViewport.TopLeftX = imGui_Size.x;
m_screenViewport.TopLeftY = 0;
m_screenViewport.Width = float(m_screenWidth - imGui_Size.x);
m_screenViewport.Height = float(m_screenHeight);
m_screenViewport.MinDepth = 0.0f;
m_screenViewport.MaxDepth = 1.0f;
```

UI가 차지하는 영역을 제외하고 scene rendering 영역을 잡습니다.

```cpp
m_context->RSSetViewports(1, &m_screenViewport);
```

rasterizer stage에 viewport를 적용해 이후 draw call이 지정된 영역에 렌더링되도록 합니다.

## Archive 반영 메모

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step7_ResizingViewport`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step7_ResizingViewport`
- 원문 학습 주석은 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step7_ResizingViewport/source-comments.md`에 분리했습니다.
- `.vs/`, `x64/`, `.user`, `imgui.ini`, `.clang-format`, raw build output은 archive에 포함하지 않았습니다.
- 실행에 필요한 `crate2_diffuse.png`, `wall.jpg`는 private archive asset으로 포함했습니다.
- texture asset은 public 공개 전 license/source 확인이 필요합니다.
- HLSL/HLSLI 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.
- raw project의 Release HLSL 설정에 shader type 누락이 있어 archive project에서 Release용 pixel/vertex shader 설정을 보강했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: Debug x64, Release x64 성공
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 이유: private archive 학습 예제이고 texture asset을 포함합니다. public subset으로 분리하기 전 asset license/source, 강의 기반 구조 표현 정도, dependency 재현성을 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../../ImportHistory/Manifests/Part2_Chapter05-08.md)
