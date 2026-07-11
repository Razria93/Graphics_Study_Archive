# Part3 Chapter10-13

Geometry pipeline, texturing techniques, PBR, light/shadow 예제를 archive 기준으로 정리하는 문서입니다.

## Scope

- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13`
- Reference-only raw source: `C:\ComputerGraphics\Part3_Chapter10_13_2`
- Archive source: `Part3_Chapter10-13`
- Topic: geometry shader, billboards, tessellation, mipmaps, normal/height mapping, HDR, PBR, mirror, shadow mapping, PCF, PCSS
- Import status: Step1-Step5 and 11-Step1-Step5 imported
- Build/run: Step1-Step5 and 11-Step1-Step4 성공, 11-Step5 미확인
- Capture: 보류
- Public readiness: 검토 필요

## Raw Source Decision

`Part3_Chapter10_13`을 import 기준 primary source로 사용합니다.

`Part3_Chapter10_13_2`는 직접 import 기준이 아닌 reference-only snapshot으로 둡니다. 기본 진행은 primary raw를 archive로 선별 import하고, build/run 실패나 기능 누락 의심이 있을 때만 `_2`와 비교합니다.

## Import Candidates

| Example | Import decision | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `10_GeometryPipeline_Step1_GeometryShader` | 반영 완료 | 성공 | 검토 필요 | primary-only 기본 작업본 selected assets 포함, Release shader setting 보정 |
| `10_GeometryPipeline_Step1_GeometryShader_Solution` | reference solution 후보 | 미확인 | 검토 필요 | 필요 시 `ReferenceSolution` 이름으로 분리 |
| `10_GeometryPipeline_Step2_Billboards` | 반영 완료 | 성공 | 검토 필요 | billboard geometry shader, TreeBillboards selected assets 포함, Release shader setting 보정 |
| `10_GeometryPipeline_Step3_NormalLines` | 반영 완료 | 성공 | 검토 필요 | normal visualization, Release shader setting 보정 |
| `10_GeometryPipeline_Step4_Fireball` | 반영 완료 | 성공 | 검토 필요 | geometry/fireball shader, fireball texture 포함, Release shader setting 보정 |
| `10_GeometryPipeline_Step5_Tessellation` | 반영 완료 | 성공 | 검토 필요 | hull/domain shader, Release shader setting 보정 |
| `11_TexturingTechniques_Step1_Mipmaps` | 반영 완료 | 성공 | 검토 필요 | OriginalExamples 의도 기준 `Mipmaps Level` GUI 복구, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step2_NormalMapping` | 반영 완료 | 성공 | 검토 필요 | primary raw 기준 normal map/TBN 구현, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step3_HeightMapping` | 반영 완료 | 성공 | 검토 필요 | height texture 기반 vertex displacement, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step4_HDRI` | 반영 완료 | 성공 | 검토 필요 | replacement EXR 반영, 사용자 Debug/Release 실행 확인 |
| `11_TexturingTechniques_Step5_HDRPipeline` | 반영 완료 | 미확인 | 검토 필요 | HDR DDS replacement assets 반영, 사용자 Debug/Release 실행 확인 필요 |
| `12_PBR_Step1_UnrealPBR` | archive 후보 | 미확인 | 검토 필요 | Unreal-style PBR shader |
| `12_PBR_Step2_PBRModels` | archive 후보 | 미확인 | 검토 필요 | PBR model assets |
| `13_LightAndShadow_Step1_Mirror` | archive 후보 | 미확인 | 검토 필요 | mirror/stencil |
| `13_LightAndShadow_Step2_PipelineStateObject` | archive 후보 | 미확인 | 검토 필요 | pipeline state abstraction |
| `13_LightAndShadow_Step2_Shadow` | archive 후보 | 미확인 | 검토 필요 | shadow baseline |
| `13_LightAndShadow_Step3_DepthBufferAndFog` | archive 후보 | 미확인 | 검토 필요 | depth/fog |
| `13_LightAndShadow_Step4_ShadowMapping` | archive 후보 | 미확인 | 검토 필요 | shadow mapping |
| `13_LightAndShadow_Step5_SoftShadowPCF` | archive 후보 | 미확인 | 검토 필요 | PCF soft shadow |
| `13_LightAndShadow_Step6_SoftShadowPCSS` | archive 후보 | 미확인 | 검토 필요 | PCSS soft shadow |
| `13_LightAndShadow_Step7_Halo` | archive 후보 | 미확인 | 검토 필요 | halo/post effect |
| `13_LightAndShadow_Step8_UnrealSphereLight` | archive 후보 | 미확인 | 검토 필요 | sphere light |

## Import Rules

- primary raw의 예제 폴더를 기준으로 `.sln`, `.vcxproj`, `.vcxproj.filters`, source, shader, include 파일을 선별합니다.
- `_2`는 문제 원인 비교용이며, 별도 판단 없이 archive에 직접 복사하지 않습니다.
- `_Solution`은 public 후보가 아닌 private archive 비교/reference solution 후보로 둡니다.
- 실행에 필요한 asset만 선별 포함합니다.
- raw zip asset, capture/result image, generated build output은 제외합니다.
- 사용자가 Debug/Release 실행을 확인하기 전까지 build/run은 `미확인`으로 기록합니다.

## Next Action

1. 사용자가 `11_TexturingTechniques_Step5_HDRPipeline` Debug/Release 실행을 확인합니다.
2. 실행 확인 후 status/tracking 문서를 갱신합니다.
