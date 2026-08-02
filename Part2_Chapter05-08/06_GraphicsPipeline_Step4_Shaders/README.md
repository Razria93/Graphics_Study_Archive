# Chapter06 Step4 Shaders

이 예제는 Step3의 Model·View·Projection pipeline에 UV와 pixel shader constant buffer를 추가하고, square의 UV 좌표를 `xSplitPoint`와 비교해 네 색상 영역을 만든다. Vertex shader는 position transform과 attribute 전달을 담당하고 pixel shader는 fragment별 색상을 선택한다.

## 실행 진입점

- Solution: `06_GraphicsPipeline_Step4_Shaders.sln`
- Application entry: `main.cpp`
- 주요 source: `AppBase.cpp`, `ExampleApp.cpp`, `ExampleApp.h`
- Shader: `ColorVertexShader.hlsl`, `ColorPixelShader.hlsl`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter06 Step4 Shaders`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Square vertex와 index](ExampleApp.cpp#L10-L53) | Position·color·UV를 가진 indexed square 구성 |
| [Scene resource 초기화](ExampleApp.cpp#L206-L264) | Square buffer, MVP·pixel constant buffer, shader와 input layout 생성 |
| [Constant buffer 갱신](ExampleApp.cpp#L277-L312) | 고정 MVP와 UI의 `xSplitPoint`를 GPU buffer에 기록 |
| [Pipeline binding과 draw](ExampleApp.cpp#L315-L365) | Vertex·pixel shader와 `b0`·`b1` constant buffer를 stage별로 연결 |
| [Split point UI](ExampleApp.cpp#L368-L372) | `xSplitPoint`를 `0.0`부터 `1.0`까지 조정 |
| [Vertex shader contract](ColorVertexShader.hlsl#L13-L54) | MVP transform 뒤 color와 UV 전달 |
| [Pixel shader 분기](ColorPixelShader.hlsl#L3-L39) | UV의 X·Y를 threshold와 비교해 네 색상 선택 |

## 구현 요약

Square vertex는 position, color와 UV를 가진다. Vertex shader는 `b0`의 Model·View·Projection matrix를 position에 적용하고 color와 UV를 pixel stage로 전달한다. Rasterization 이후 pixel shader는 `b1`의 `xSplitPoint`를 UV의 X와 Y에 공통으로 적용해 red, green, blue와 yellow 영역을 선택한다.

CPU는 ImGui slider의 현재값을 매 frame pixel shader constant buffer에 기록한다. 기본값 `0.5`에서는 네 영역이 같은 크기로 나뉘고 `0.25`에서는 왼쪽 영역이 좁아지며 위·아래 경계도 함께 이동한다. 일반 shader stage의 입력·출력 책임은 [Shader Stage](../../Docs/01_Topics/DirectX11Pipeline/ShaderStage.md), 구현 선택과 결과 비교는 [Step4 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_Shaders.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, 정상 종료 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, 정상 종료 |
| Shader·UI 반영 | 성공 | `b0` MVP, `b1` pixel constant buffer와 `xSplitPoint` 반영 확인 |
| Capture/Result | 확보 | 기본 `0.5`와 조정 `0.25` 전체 창 screenshot, 사용자 승인 완료 |

Build 뒤의 `pwsh.exe` 환경 경고는 MSBuild 성공과 분리해 관찰했으며 실행 결과에는 영향을 주지 않았다.

## Capture/Result

기본값 `0.5`에서는 UV의 X·Y 경계가 중앙에서 만나 네 색상 영역이 같은 크기로 나타난다.

![Chapter06 Step4 Shaders 기본 split](../../Docs/_assets/captures/part2_chapter06_04_shaders_default.png)

조정값 `0.25`에서는 X와 Y에 같은 threshold를 적용하므로 왼쪽 열과 위쪽 행의 범위가 함께 좁아진다.

![Chapter06 Step4 Shaders 조정 split](../../Docs/_assets/captures/part2_chapter06_04_shaders_split_adjusted.png)

두 screenshot만으로 정적 분기 전후가 명확하므로 video는 제외한다.

## 구현 범위와 한계

- 실제 draw geometry는 `MakeSquare()`이며 파일에 남은 `MakeBox()`는 사용하지 않는다.
- `leftColor`와 `rightColor`는 CPU·HLSL constant buffer에 존재하지만 현재 pixel shader의 hard-coded 출력에는 사용하지 않는다.
- Vertex color는 stage contract를 따라 전달되지만 현재 pixel shader 결과에는 사용하지 않는다.
- `xSplitPoint` 하나를 UV의 X·Y 비교에 함께 사용하므로 세로 경계만 독립적으로 조절할 수 없다.
- Shader는 project 폴더 기준 상대 경로로 compile하므로 다른 working directory에서 실행하면 실패할 수 있다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 범위에서 제외한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter06 Step3 ModelViewProj](../06_GraphicsPipeline_Step3_ModelViewProj/README.md)
- [다음 단계: Chapter06 Step5 Texturing](../06_GraphicsPipeline_Step5_Texturing/README.md)
- [Shader Stage Topic](../../Docs/01_Topics/DirectX11Pipeline/ShaderStage.md)
- [Step4 Shaders 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_Shaders.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
