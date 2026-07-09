# Import Manifest: Part2 Chapter04

## Source / Target

- Source: `C:\ComputerGraphics\Part2_Chapter04`
- Target: `Part2_Chapter04`
- Scope: software rasterization examples
- Import status: 진행 중
- Public readiness: 검토 필요
- Build/run status: 미확인

## Step Inventory

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `04_Rasterization_Step1_Triangle` | 반영 중 | 미확인 | 검토 필요 | triangle rasterization 기본 흐름 |
| `04_Rasterization_Step1_TriangleToCircle` | 대기 | 미확인 | 검토 필요 | Step1 변형 후보 |
| `04_Rasterization_Step2_Circle` | 대기 | 미확인 | 검토 필요 | circle rasterization |
| `04_Rasterization_Step3_Transformations2D` | 대기 | 미확인 | 검토 필요 | 2D transform |
| `04_Rasterization_Step4_Animation2D` | 대기 | 미확인 | 검토 필요 | 2D animation |
| `04_Rasterization_Step5_DepthBuffer` | 대기 | 미확인 | 검토 필요 | depth buffer |
| `04_Rasterization_Step6_ShadersConcept` | 대기 | 미확인 | 검토 필요 | shader concept |
| `04_Rasterization_Step7_BackfaceCulling` | 대기 | 미확인 | 검토 필요 | backface culling |
| `04_Rasterization_Step8_PerspectiveProjection` | 대기 | 미확인 | 검토 필요 | perspective projection |
| `04_Rasterization_Step9_Shading` | 대기 | 미확인 | 검토 필요 | rasterization shading |
| `04_Rasterization_Step10_Lights` | 대기 | 미확인 | 검토 필요 | lighting |

## Include Candidates

Step별로 아래 파일만 선별 반영합니다.

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- `*.cpp`
- `*.h`
- `*.hlsl`
- 실행에 필수인 asset이 있는 경우 별도 검토 후 반영

## Exclude Patterns

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- raw result/capture/video
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료

## Comment / Memo Handling

- source 안의 장문 학습 메모와 강의 안내성 주석은 archive source에 그대로 두지 않습니다.
- 실행 흐름 이해에 필요한 짧은 주석만 새로 남깁니다.
- 원문 메모의 위치와 의미는 `local/Part2_Chapter04/<ExampleName>/` 아래에 기록합니다.

## Current Focus

1. `04_Rasterization_Step1_Triangle`을 작은 단위로 먼저 반영합니다.
2. Debug/Release 실행 확인 전까지 build/run status는 `미확인`으로 유지합니다.
3. 사용자가 실행 확인을 완료하면 status 문서와 Part2 README를 갱신합니다.
