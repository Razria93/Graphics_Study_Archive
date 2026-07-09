# Import Manifest: Part2 Chapter04

## Source / Target

- Source: `C:\ComputerGraphics\Part2_Chapter04`
- Target: `Part2_Chapter04`
- Scope: software rasterization examples
- Import status: 진행 중
- Public readiness: 검토 필요
- Build/run status: Step1, TriangleToCircle, Step2, Step3, Step4, Step5, Step6, Step7 성공 / Step8 빌드 성공, 실행 미확인 / 이후 미확인

## Step Inventory

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `04_Rasterization_Step1_Triangle` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step1_TriangleToCircle` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step2_Circle` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step3_Transformations2D` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step4_Animation2D` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step5_DepthBuffer` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step6_ShadersConcept` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step7_BackfaceCulling` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인 완료 |
| `04_Rasterization_Step8_PerspectiveProjection` | 반영 완료 | 빌드 성공 / 실행 미확인 | 검토 필요 | perspective projection과 perspective-correct interpolation |
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

- source 안의 장문 학습 메모와 강의 안내성 주석은 archive source에 그대로 유지하지 않습니다.
- 실행 흐름 이해에 필요한 짧은 주석만 새로 남깁니다.
- 원문 메모의 위치와 요지는 `local/Part2_Chapter04/<ExampleName>/` 아래에 기록합니다.

## Current Focus

1. 현재 후보는 `04_Rasterization_Step8_PerspectiveProjection` 실행 확인입니다.
2. 사용자가 Debug/Release 실행 확인을 완료하면 status 문서와 Part2 README를 갱신합니다.
3. 다음 import 후보는 `04_Rasterization_Step9_Shading`입니다.
