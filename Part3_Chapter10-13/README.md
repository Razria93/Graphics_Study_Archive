# Part3 Chapter10-13

Geometry pipeline, texturing, PBR와 light/shadow를 순차적으로 확장하는 advanced rendering 묶음이다.

## 현재 상태

- Chapter10 Step1→5: 현재 Debug/Release x64 build/run과 capture 완료
- Chapter11 Step1→5: 현재 Debug/Release x64 build/run과 capture 완료
- Chapter12 Step1→2: 현재 Debug/Release x64 build/run과 capture 완료
- Chapter13 Step1→8와 Step2B: 현재 Debug/Release x64 build/run과 capture 완료
- Source provenance: [`SRC-P3-C10-13`](../Docs/99_Legacy/source-registry.md)
- Public readiness: Chapter별 rendered evidence와 asset 기록을 확인해 판정

## Chapter10 Geometry Pipeline

| 단계 | 핵심 변화 | 상태 |
| --- | --- | --- |
| [Step1 GeometryShader](10_GeometryPipeline_Step1_GeometryShader/README.md) | Point에서 quad strip 생성 | 현재 확인 완료 |
| [Step2 Billboards](10_GeometryPipeline_Step2_Billboards/README.md) | Camera-facing textured billboard | 현재 확인 완료 |
| [Step3 NormalLines](10_GeometryPipeline_Step3_NormalLines/README.md) | Vertex normal diagnostic line | 현재 확인 완료 |
| [Step4 Fireball](10_GeometryPipeline_Step4_Fireball/README.md) | Procedural animated billboard | 현재 확인 완료 |
| [Step5 Tessellation](10_GeometryPipeline_Step5_Tessellation/README.md) | Manual·Distance Adaptive tessellation | 현재 확인 완료 |

## Chapter11 Texturing Techniques

| 단계 | 핵심 변화 | 상태 |
| --- | --- | --- |
| [Step1 Mipmaps](11_TexturingTechniques_Step1_Mipmaps/README.md) | 명시적 mip level sampling | 현재 확인 완료 |
| [Step2 NormalMapping](11_TexturingTechniques_Step2_NormalMapping/README.md) | Tangent-space normal과 TBN 변환 | 현재 확인 완료 |
| [Step3 HeightMapping](11_TexturingTechniques_Step3_HeightMapping/README.md) | Vertex displacement와 silhouette 변화 | 현재 확인 완료 |
| [Step4 HDRI](11_TexturingTechniques_Step4_HDRI/README.md) | EXR load와 exposure·gamma 표시 | 현재 확인 완료 |
| [Step5 HDRPipeline](11_TexturingTechniques_Step5_HDRPipeline/README.md) | Bloom pyramid와 HDR composite | 현재 확인 완료 |

## Chapter12 PBR

| 단계 | 핵심 변화 | 상태 |
| --- | --- | --- |
| [Step1 UnrealPBR](12_PBR_Step1_UnrealPBR/README.md) | Metallic-roughness PBR와 IBL | 현재 확인 완료 |
| [Step2 PBRModels](12_PBR_Step2_PBRModels/README.md) | Imported model의 PBR material binding | 현재 확인 완료 |

## Chapter13 Light And Shadow

| 단계 | 핵심 변화 | 상태 |
| --- | --- | --- |
| [Step1 Mirror](13_LightAndShadow_Step1_Mirror/README.md) | Stencil mask와 reflected scene | 현재 확인 완료 |
| [Step2 PipelineStateObject](13_LightAndShadow_Step2_PipelineStateObject/README.md) | Pipeline state 묶음과 같은 mirror 결과 | 현재 확인 완료 |
| [Step2B Shadow Prototype](13_LightAndShadow_Step2_Shadow/README.md) | Depth pass와 shadowed main pass prototype | 현재 확인 완료 |
| [Step3 DepthBufferAndFog](13_LightAndShadow_Step3_DepthBufferAndFog/README.md) | Depth reconstruction과 fog | 현재 확인 완료 |
| [Step4 ShadowMapping](13_LightAndShadow_Step4_ShadowMapping/README.md) | Hard shadow와 depth bias | 현재 확인 완료 |
| [Step5 SoftShadowPCF](13_LightAndShadow_Step5_SoftShadowPCF/README.md) | Fixed-kernel PCF | 현재 확인 완료 |
| [Step6 SoftShadowPCSS](13_LightAndShadow_Step6_SoftShadowPCSS/README.md) | Blocker search와 variable penumbra | 현재 확인 완료 |
| [Step7 Halo](13_LightAndShadow_Step7_Halo/README.md) | Depth-aware screen-space halo | 현재 확인 완료 |
| [Step8 UnrealSphereLight](13_LightAndShadow_Step8_UnrealSphereLight/README.md) | Representative-point sphere light | 현재 확인 완료 |

## 문서 진입점

- [Verification](../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [Demo Index](../Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Topics](../Docs/01_Topics/README.md)
- [Publication](../Docs/05_Publication/candidate-list.md)

## Source 기준

- Primary와 reference source 관계는 source registry로 추적한다.
- Reference-only snapshot은 build/run 실패나 기능 누락 의심 시에만 비교한다.
- `_Solution` variant는 private 비교 후보로 유지하고 사용자 작업본과 섞지 않는다.
- 실행에 필요한 asset만 유지하고 raw result, 임시 capture와 build output은 추적하지 않는다.
