# Import Manifest: Part3 Chapter10-13

> 이 문서는 import 당시 포함/제외 판단 기록입니다.
> 최신 build/run/capture 상태의 기준 문서가 아닙니다.


## Source / Target

- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13`
- Reference-only raw source: `C:\ComputerGraphics\Part3_Chapter10_13_2`
- Archive target: `Part3_Chapter10-13`
- Docs target: `Docs/Part3_Chapter10-13`
- Branch: `archive/part3`
- Import status: Step1-Step5, 11-Step1-Step5, 12-Step1-Step2, 13-Step1, 13-Step2 PipelineStateObject, 13-Step2 Shadow, 13-Step3, 13-Step4, 13-Step5, 13-Step6, 13-Step7, and 13-Step8 imported
- Build/run status: Step1-Step5, 11-Step1-Step5, 12-Step1-Step2, 13-Step1, 13-Step2 PipelineStateObject, 13-Step2 Shadow, 13-Step3, 13-Step4, 13-Step5, 13-Step6, 13-Step7, and 13-Step8 성공
- Public readiness: 검토 필요

## Raw Source Decision

`Part3_Chapter10_13`을 primary import source로 사용합니다.

`Part3_Chapter10_13_2`는 reference-only snapshot입니다. 자세한 판단 근거는 아래 Reference Snapshot Decision Details에 둡니다.


## Reference Snapshot Decision Details

`Part3_Chapter10_13_2`는 직접 import 기준이 아니라 reference-only snapshot으로 유지합니다.

판단 근거:

- 대부분 코드 파일의 최신 시간이 `2025-09-26 10:33~10:34`에 고정되어 있습니다.
- `Part3_Chapter10_13`은 이후 `2025-10-04`부터 `2025-10-22`까지 계속 갱신된 흔적이 있습니다.
- `_2`에는 `10_GeometryPipeline_Step1_GeometryShader` 기본 폴더가 없고 `10_GeometryPipeline_Step1_GeometryShader_Solution`만 있습니다.
- `_2/Assets`에는 zip asset 4개가 더 있으나, zip 원본 asset은 archive import 기준이 아니라 별도 검토 대상입니다.
- 코드 차이는 대부분 1~8개 파일 수준이며, 일부 항목은 완전히 동일합니다.

운영 기준:

- archive import 기준은 `Part3_Chapter10_13` primary source입니다.
- `_2`는 build/run 문제, 기능 누락 의심, 구현 차이 설명이 필요할 때만 비교합니다.
- `_2`에서 확인한 내용은 해당 예제 manifest note 또는 local-only review note에 근거와 함께 남깁니다.

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
| `11_TexturingTechniques_Step3_HeightMapping` | primary | 반영 완료 | 성공 | 검토 필요 | height texture 기반 vertex displacement, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step4_HDRI` | primary | 반영 완료 | 성공 | 검토 필요 | referenced EXR 미발견 이슈 후 replacement EXR 반영, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step5_HDRPipeline` | primary | 반영 완료 | 성공 | 검토 필요 | HDR DDS replacement assets 반영, 사용자 Debug/Release 실행 확인 |
| `12_PBR_Step1_UnrealPBR` | primary | 반영 완료 | 성공 | 검토 필요 | Unreal-style PBR shader, Sample HDRI DDS and worn-painted-metal PBR textures 포함, 사용자 Debug/Release 실행 확인 |
| `12_PBR_Step2_PBRModels` | primary | 반영 완료 | 성공 | 검토 필요 | PBR model loading, `armored-female-future-soldier` asset 반영, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step1_Mirror` | primary | 반영 완료 | 성공 | 검토 필요 | mirror/stencil, Sample HDRI DDS and UV grid texture reused, character asset enabled |
| `13_LightAndShadow_Step2_PipelineStateObject` | primary + origin character reference | 반영 완료 | 성공 | 검토 필요 | pipeline state, character asset enabled |
| `13_LightAndShadow_Step2_Shadow` | primary + character option reviewed | 반영 완료 | 성공 | 검토 필요 | shadow map baseline, sphere main object, final scene path, point-light position GUI minimal 보완, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step3_DepthBufferAndFog` | primary | 반영 완료 | 성공 | 검토 필요 | depth buffer/fog post effect, Release shader setting 보정, `PostEffectsPS.hlsl` return 변수 오타 보정, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step4_ShadowMapping` | primary | 반영 완료 | 성공 | 검토 필요 | shadow mapping, primary raw shadow lookup 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step5_SoftShadowPCF` | primary | 반영 완료 | 성공 | 검토 필요 | PCF soft shadow, primary raw 64-sample PCF 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step6_SoftShadowPCSS` | primary | 반영 완료 | 성공 | 검토 필요 | PCSS soft shadow, primary raw PCSS 사용자 메모 포함 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step7_Halo` | primary | 반영 완료 | 성공 | 검토 필요 | halo post effect, primary raw `PostEffectsPS.hlsl` 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| `13_LightAndShadow_Step8_UnrealSphereLight` | primary | 반영 완료 | 성공 | 검토 필요 | sphere light, primary raw `BasicPS.hlsl` representative point 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |

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

다음 작업은 Part3 Ch10-13 import 마무리 상태 확인과 브랜치 정리/PR 준비입니다.

