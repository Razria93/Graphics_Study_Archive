# Import Manifest: Part2 Chapter05-08

## Source / Target

- Source: `C:\ComputerGraphics\Part2_Chapter05-08`
- Target: `Part2_Chapter05-08`
- Scope: affine transformations, D3D11 graphics pipeline, modeling, shader toys
- Import status: 진행 중
- Public readiness: 검토 필요
- Build/run status: Step1 Matrix(GLM), Step2 Lights(GLM), Step3 DirectXMath, Step4 Lights(SimpleMath), Pipeline Step1 COM 성공

## Step Inventory

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `05_AffineTransformations_Step1_Matrix(GLM)` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, GLM column-major matrix |
| `05_AffineTransformations_Step2_Lights(GLM)` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, GLM model/normal matrix |
| `05_AffineTransformations_Step3_DirectXMath` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, DirectXMath/SimpleMath |
| `05_AffineTransformations_Step4_Lights(SimpleMath)` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, SimpleMath lighting |
| `06_GraphicsPipeline_Step1_COM` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, D3D11 device creation, WRL ComPtr |
| `06_GraphicsPipeline_*` | 예정 | 미확인 | 검토 필요 | Step2 이후 D3D11 pipeline |
| `07_Modeling_*` | 예정 | 미확인 | 검토 필요 | mesh generation/modeling |
| `08_ShaderToys_*` | 예정 | 미확인 | 검토 필요 | shader toy effects |

## Include Candidates

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
- `.clang-format` 예제별 사본
- raw result/capture/video
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료

## Comment / Memo Handling

- source 안의 장문 출력 결과 주석과 학습 메모는 archive source에 그대로 유지하지 않습니다.
- 실행 흐름 이해에 필요한 짧은 주석만 새로 남깁니다.
- 원문 메모의 위치와 요지는 `local/Part2_Chapter05-08/<ExampleName>/` 아래에 기록합니다.

## Current Focus

1. 다음 후보 `06_GraphicsPipeline_Step2_InitializingD3D`의 raw 구조와 dependency를 확인합니다.
2. source/project/shader/asset을 선별 반영하고 장문 주석은 `local/`로 분리합니다.
