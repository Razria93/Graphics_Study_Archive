# Import Manifest: Part3 Chapter10-13

## Source / Target

- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13`
- Reference-only raw source: `C:\ComputerGraphics\Part3_Chapter10_13_2`
- Archive target: `Part3_Chapter10-13`
- Docs target: `Docs/Part3_Chapter10-13`
- Branch: `archive/part3`
- Import status: Step1-Step5 and 11-Step1-Step3 imported
- Build/run status: Step1-Step5 and 11-Step1-Step2 성공, 11-Step3 미확인
- Public readiness: 검토 필요

## Raw Source Decision

`Part3_Chapter10_13`을 primary import source로 사용합니다.

`Part3_Chapter10_13_2`는 reference-only snapshot입니다. `_2`에는 `10_GeometryPipeline_Step1_GeometryShader` 기본 폴더가 없고, 일부 폴더의 갱신 시점과 code diff가 primary와 섞여 있습니다. 따라서 `_2`는 build/run 실패, 기능 누락, 원인 비교가 필요할 때만 확인합니다.

## Candidate Table

| Example | Raw basis | Import status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- | --- |
| `10_GeometryPipeline_Step1_GeometryShader` | primary | 반영 완료 | 성공 | 검토 필요 | primary-only 기본 작업본, selected assets 포함, Release shader setting 보정 |
| `10_GeometryPipeline_Step1_GeometryShader_Solution` | primary/reference | reference 후보 | 미확인 | 검토 필요 | 필요 시 `ReferenceSolution`으로 분리 |
| `10_GeometryPipeline_Step2_Billboards` | primary | 반영 완료 | 성공 | 검토 필요 | billboard, TreeBillboards selected assets 포함, Release shader setting 보정 |
| `10_GeometryPipeline_Step3_NormalLines` | primary | 반영 완료 | 성공 | 검토 필요 | normal lines, Release shader setting 보정 |
| `10_GeometryPipeline_Step4_Fireball` | primary | 반영 완료 | 성공 | 검토 필요 | fireball shader, fireball texture 포함, Release shader setting 보정 |
| `10_GeometryPipeline_Step5_Tessellation` | primary | 반영 완료 | 성공 | 검토 필요 | tessellation, Release shader setting 보정 |
| `11_TexturingTechniques_Step1_Mipmaps` | primary + OriginalExamples intent | 반영 완료 | 성공 | 검토 필요 | `Mipmaps Level` GUI 복구, `SampleLevel(..., mipmapLevel)`, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step2_NormalMapping` | primary | 반영 완료 | 성공 | 검토 필요 | normal map/TBN 구현, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step3_HeightMapping` | primary | 반영 완료 | 미확인 | 검토 필요 | height texture 기반 vertex displacement, 새 asset 없음 |
| `11_TexturingTechniques_Step4_HDRI` | primary | planned | 미확인 | 검토 필요 | HDRI |
| `11_TexturingTechniques_Step5_HDRPipeline` | primary | planned | 미확인 | 검토 필요 | HDR pipeline |
| `12_PBR_Step1_UnrealPBR` | primary | planned | 미확인 | 검토 필요 | PBR shader |
| `12_PBR_Step2_PBRModels` | primary | planned | 미확인 | 검토 필요 | PBR models |
| `13_LightAndShadow_Step1_Mirror` | primary | planned | 미확인 | 검토 필요 | mirror/stencil |
| `13_LightAndShadow_Step2_PipelineStateObject` | primary | planned | 미확인 | 검토 필요 | pipeline state |
| `13_LightAndShadow_Step2_Shadow` | primary | planned | 미확인 | 검토 필요 | shadow baseline |
| `13_LightAndShadow_Step3_DepthBufferAndFog` | primary | planned | 미확인 | 검토 필요 | depth/fog |
| `13_LightAndShadow_Step4_ShadowMapping` | primary | planned | 미확인 | 검토 필요 | shadow mapping |
| `13_LightAndShadow_Step5_SoftShadowPCF` | primary | planned | 미확인 | 검토 필요 | PCF |
| `13_LightAndShadow_Step6_SoftShadowPCSS` | primary | planned | 미확인 | 검토 필요 | PCSS |
| `13_LightAndShadow_Step7_Halo` | primary | planned | 미확인 | 검토 필요 | halo |
| `13_LightAndShadow_Step8_UnrealSphereLight` | primary | planned | 미확인 | 검토 필요 | sphere light |

## Exclude Rules

- `.vs/`, `x64/`, `Debug/`, `Release/`
- `*.user`, `*.suo`, `imgui.ini`
- `.clang-format` unless the project explicitly depends on it
- raw capture/result files
- raw zip asset archives
- `_Debug`, `_Backup`, temporary experiment folders

## Finish Check

각 예제 import 후 다음 항목을 확인합니다.

- `.vcxproj` XML namespace
- HLSL/HLSLI BOM
- selected asset hash
- raw/archive source diff
- generated output exclusion
- build/run status 기록

## Next Action

사용자가 `11_TexturingTechniques_Step3_HeightMapping` Debug/Release 실행을 확인하면 status/tracking 문서를 갱신합니다.
