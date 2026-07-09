# Import Manifest: Part2 Chapter05-08

## Source / Target

- Source: `C:\ComputerGraphics\Part2_Chapter05-08`
- Target: `Part2_Chapter05-08`
- Scope: affine transformations, D3D11 graphics pipeline, modeling, shader toys
- Import status: 진행 중
- Public readiness: 검토 필요
- Build/run status: Step1 Matrix(GLM) 빌드 성공, 실행 미확인

## Step Inventory

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `05_AffineTransformations_Step1_Matrix(GLM)` | 반영 완료 | 빌드 성공 / 실행 미확인 | 검토 필요 | GLM column-major matrix, transform composition |
| `05_AffineTransformations_Step2_Lights(GLM)` | 예정 | 미확인 | 검토 필요 | lighting with GLM |
| `05_AffineTransformations_Step3_DirectXMath` | 예정 | 미확인 | 검토 필요 | DirectXMath comparison |
| `05_AffineTransformations_Step4_Lights(SimpleMath)` | 예정 | 미확인 | 검토 필요 | SimpleMath lighting |
| `06_GraphicsPipeline_*` | 예정 | 미확인 | 검토 필요 | D3D11 pipeline |
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

1. `05_AffineTransformations_Step1_Matrix(GLM)` Debug/Release 실행을 확인합니다.
2. 사용자가 Debug/Release 실행 확인을 완료하면 status 문서와 Part2 README를 갱신합니다.
3. 다음 후보는 `05_AffineTransformations_Step2_Lights(GLM)`입니다.
