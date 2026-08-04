# Part3_Chapter10-13 Demo Index

이 문서는 Chapter10→13의 순차 Demo와 capture 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: Chapter10 Geometry Pipeline, Chapter11 HDR, Chapter12 PBR, Chapter13 shadow quality
- 비고: 각 Example은 독립 상세 Demo를 사용하고 Chapter 대표 선정은 Publication에서 별도로 수행한다.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step1 Demo](10_01_GeometryShader.md) | [Step1 README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/README.md) | [Geometry Shader](../../01_Topics/ModelingAndGeometry/GeometryShaderAndBillboards.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Docs/_assets PNG](../../_assets/captures/part3_chapter10_01_geometry_shader.png) | 미게시 | 확보 | Geometry shader 기준선 |
| 대표 capture | [Step5 Demo](10_05_Tessellation.md) | [Step5 README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/README.md) | [Tessellation](../../01_Topics/ModelingAndGeometry/TessellationPipeline.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Docs/_assets PNG](../../_assets/captures/part3_chapter10_05_tessellation.png) | 미게시 | 후보 | Chapter10 대표 후보 |
| 대표 capture | [Chapter11 Step5 Demo](11_05_HDRPipeline.md) | [Step5 README](../../../Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/README.md) | [HDR Pipeline](../../01_Topics/TexturingAndMapping/HDRRenderingPipeline.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Docs/_assets PNG](../../_assets/captures/part3_chapter11_05_hdr_pipeline.png) | 미게시 | 후보 | Chapter11 대표 후보 |
| 대표 capture | [Chapter12 Step1 Demo](12_01_UnrealPBR.md) | [Step1 README](../../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/README.md) | [PBR Material](../../01_Topics/PBRAndIBL/PBRMaterialModel.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Docs/_assets PNG](../../_assets/captures/part3_chapter12_01_unreal_pbr.png) | 미게시 | 후보 | Chapter12 대표 후보 |
| 대표 capture | [Chapter13 Step6 Demo](13_06_SoftShadowPCSS.md) | [Step6 README](../../../Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/README.md) | [PCF And PCSS](../../01_Topics/Shadows/PercentageCloserFilteringAndPCSS.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Shadow Comparison](../../_assets/captures/part3_chapter13_shadow_comparison.png) | 미게시 | 후보 | Chapter13 대표 비교 visual |
| video | [Step4 Demo](10_04_Fireball.md) | [Step4 README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/README.md) | [Runtime Inputs](../../01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | 없음 | 미게시 | 제외 | 정지 image로 형태와 phase 차이 확인 가능 |

## Chapter10 Geometry Pipeline

| 단계 | 상세 Demo | Capture | 상태 |
| --- | --- | --- | --- |
| Step1 GeometryShader | [Demo](10_01_GeometryShader.md) | [PNG](../../_assets/captures/part3_chapter10_01_geometry_shader.png) | 완료 |
| Step2 Billboards | [Demo](10_02_Billboards.md) | [PNG](../../_assets/captures/part3_chapter10_02_billboards.png) | 완료 |
| Step3 NormalLines | [Demo](10_03_NormalLines.md) | [PNG](../../_assets/captures/part3_chapter10_03_normal_lines.png) | 완료 |
| Step4 Fireball | [Demo](10_04_Fireball.md) | [PNG](../../_assets/captures/part3_chapter10_04_fireball.png) | 완료 |
| Step5 Tessellation | [Demo](10_05_Tessellation.md) | [PNG](../../_assets/captures/part3_chapter10_05_tessellation.png) | 완료 |

Chapter10의 순차 흐름은 point primitive 확장, billboard, diagnostic normal, procedural animation과 tessellation으로 이어진다. Step5는 원래 Manual 경로와 사용자 확장 Distance Adaptive 경로를 하나의 상세 Demo에서 명확히 분리한다.

## Chapter11 Texturing Techniques

| 단계 | 상세 Demo | Capture | 상태 |
| --- | --- | --- | --- |
| Step1 Mipmaps | [Demo](11_01_Mipmaps.md) | [PNG](../../_assets/captures/part3_chapter11_01_mipmaps.png) | 완료 |
| Step2 NormalMapping | [Demo](11_02_NormalMapping.md) | [PNG](../../_assets/captures/part3_chapter11_02_normal_mapping.png) | 완료 |
| Step3 HeightMapping | [Demo](11_03_HeightMapping.md) | [PNG](../../_assets/captures/part3_chapter11_03_height_mapping.png) | 완료 |
| Step4 HDRI | [Demo](11_04_HDRI.md) | [PNG](../../_assets/captures/part3_chapter11_04_hdri.png) | 완료 |
| Step5 HDRPipeline | [Demo](11_05_HDRPipeline.md) | [PNG](../../_assets/captures/part3_chapter11_05_hdr_pipeline.png) | 완료 |

Chapter11의 순차 흐름은 texture LOD, shading normal, vertex displacement, HDR image 표시와 전체 post-process pipeline으로 이어진다. 대표 후보는 여러 stage의 결합과 시각적 차이를 함께 보여주는 Step5 HDRPipeline으로 둔다.

## Chapter12 PBR

| 단계 | 상세 Demo | Capture | 상태 |
| --- | --- | --- | --- |
| Step1 UnrealPBR | [Demo](12_01_UnrealPBR.md) | [PNG](../../_assets/captures/part3_chapter12_01_unreal_pbr.png) | 완료 |
| Step2 PBRModels | [Demo](12_02_PBRModels.md) | [PNG](../../_assets/captures/part3_chapter12_02_pbr_models.png) | 완료 |

Chapter12는 procedural sphere의 metallic-roughness material에서 imported model의 texture binding으로 확장한다. 대표 후보는 PBR 입력과 결과를 한 화면에서 명확히 읽을 수 있는 Step1 UnrealPBR로 둔다.

## Chapter13 Light And Shadow

| 단계 | 상세 Demo | Capture | 상태 |
| --- | --- | --- | --- |
| Step1 Mirror | [Demo](13_01_Mirror.md) | [PNG](../../_assets/captures/part3_chapter13_01_mirror.png) | 완료 |
| Step2 PipelineStateObject | [Demo](13_02_PipelineStateObject.md) | [PNG](../../_assets/captures/part3_chapter13_02_pipeline_state_object.png) | 완료 |
| Step2B Shadow Prototype | [Demo](13_02B_ShadowPrototype.md) | [PNG](../../_assets/captures/part3_chapter13_02b_shadow_prototype.png) | 완료 |
| Step3 DepthBufferAndFog | [Demo](13_03_DepthBufferAndFog.md) | [PNG](../../_assets/captures/part3_chapter13_03_depth_buffer_and_fog.png) | 완료 |
| Step4 ShadowMapping | [Demo](13_04_ShadowMapping.md) | [PNG](../../_assets/captures/part3_chapter13_04_shadow_mapping.png) | 완료 |
| Step5 SoftShadowPCF | [Demo](13_05_SoftShadowPCF.md) | [PNG](../../_assets/captures/part3_chapter13_05_soft_shadow_pcf.png) | 완료 |
| Step6 SoftShadowPCSS | [Demo](13_06_SoftShadowPCSS.md) | [PNG](../../_assets/captures/part3_chapter13_06_soft_shadow_pcss.png) | 완료 |
| Step7 Halo | [Demo](13_07_Halo.md) | [PNG](../../_assets/captures/part3_chapter13_07_halo.png) | 완료 |
| Step8 UnrealSphereLight | [Demo](13_08_UnrealSphereLight.md) | [PNG](../../_assets/captures/part3_chapter13_08_unreal_sphere_light.png) | 완료 |

Chapter13은 stencil mirror와 pipeline state 정리에서 시작해 shadow prototype, depth fog, hard shadow, PCF, PCSS, halo와 sphere light로 확장한다. 대표 visual은 같은 장면의 hard shadow→PCF→PCSS 경계 변화를 한 번에 비교한다.

## Chapter 대표 후보

| Chapter | 순차 범위 | 상태 | 대표 후보 |
| --- | --- | --- | --- |
| Chapter11 | Mipmaps → HDR Pipeline | 현재 확인 완료 | HDR Pipeline |
| Chapter12 | Unreal PBR → PBR Models | 현재 확인 완료 | Unreal PBR |
| Chapter13 | Mirror → Unreal Sphere Light | 현재 확인 완료 | ShadowMapping→PCF→PCSS 비교 |

## Video 판정

- Step4 Fireball animation은 정지 image로 형태와 phase 차이를 확인할 수 있어 video를 필수로 두지 않는다.
- UI 조작이나 시간 변화가 구현 이해에 실질적인 정보를 더할 때만 local selected video를 만든다.
- Tracked 상세 Demo는 안정적인 정적 visual을 유지한다.

## 갱신 기준

- 현재 build/run/capture가 확인된 Example만 `완료`로 기록한다.
- 원본 runtime asset과 rendered evidence의 공개 책임을 구분한다.
- GitHub 게시 상태는 실제 Issue URL을 확보한 뒤 갱신한다.

## 관련 문서

- [Chapter README](../../../Part3_Chapter10-13/README.md)
- [Capture Plan](../../../Part3_Chapter10-13/capture-plan.md)
- [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
- [Publication](../../05_Publication/candidate-list.md)
