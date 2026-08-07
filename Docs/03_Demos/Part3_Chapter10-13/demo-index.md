# Part3_Chapter10-13 Demo Index

이 문서는 `Part3_Chapter10-13`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: PBR, shadow mapping, PCF, PCSS, HDR
- 비고: NormalMapping 기준선과 shadow filtering progression 선별 완료

## Demo 목록

| Demo 후보 | 연결 Example | 연결 Topic | Verification | Capture/Result | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Chapter11 Step2 NormalMapping](../../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/README.md) | [Normal Mapping And Tangent Space](../../01_Topics/TexturingAndMapping/NormalMappingAndTangentSpace.md) | [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Off](../../_assets/captures/part3_chapter11_02_normal_mapping_off.png), [On](../../_assets/captures/part3_chapter11_02_normal_mapping_on.png) | 확보 | [상세 Demo](11_02_NormalMapping.md) · [Chapter11 Demo Issue #26](https://github.com/Razria93/Graphics_Study_Archive/issues/26) |
| 대표 capture | [Step4 ShadowMapping](../../../Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping/README.md), [Step5 SoftShadowPCF](../../../Part3_Chapter10-13/13_LightAndShadow_Step5_SoftShadowPCF/README.md), [Step6 SoftShadowPCSS](../../../Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/README.md) | [Shadow Mapping And Depth Bias](../../01_Topics/Shadows/ShadowMappingAndDepthBias.md), [Percentage Closer Filtering And PCSS](../../01_Topics/Shadows/PercentageCloserFilteringAndPCSS.md) | [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Shadow Filtering Progression](../../_assets/captures/part3_chapter13_04_06_shadow_filtering_storyboard.png) | 확보 | 상세 Demo [Step4](13_04_ShadowMapping.md)·[Step5](13_05_SoftShadowPCF.md)·[Step6](13_06_SoftShadowPCSS.md) · [Issue #28](https://github.com/Razria93/Graphics_Study_Archive/issues/28) |
| video | [Step4 ShadowMapping](../../../Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping/README.md), [Step5 SoftShadowPCF](../../../Part3_Chapter10-13/13_LightAndShadow_Step5_SoftShadowPCF/README.md), [Step6 SoftShadowPCSS](../../../Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/README.md) | [Percentage Closer Filtering And PCSS](../../01_Topics/Shadows/PercentageCloserFilteringAndPCSS.md) | [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | 없음 | 제외 | tracked 정적 비교 sheet로 filtering 차이가 분명해 video를 사용하지 않음 |

## 상세 Demo 문서

- [Chapter10 GeometryShader](10_01_GeometryShader.md)
- [Chapter10 Billboards](10_02_Billboards.md)
- [Chapter10 NormalLines](10_03_NormalLines.md)
- [Chapter10 Fireball](10_04_Fireball.md)
- [Chapter10 Tessellation](10_05_Tessellation.md)
- [Chapter11 Mipmaps](11_01_Mipmaps.md)
- [Chapter11 NormalMapping](11_02_NormalMapping.md)
- [Chapter11 HeightMapping](11_03_HeightMapping.md)
- [Chapter11 HDRI](11_04_HDRI.md)
- [Chapter11 HDRPipeline](11_05_HDRPipeline.md)
- [Chapter12 UnrealPBR](12_01_UnrealPBR.md)
- [Chapter12 PBRModels](12_02_PBRModels.md)
- [Chapter13 Mirror](13_01_Mirror.md)
- [Chapter13 PipelineStateObject](13_02_PipelineStateObject.md)
- [Chapter13 ShadowPrototype](13_02B_ShadowPrototype.md)
- [Chapter13 DepthBufferAndFog](13_03_DepthBufferAndFog.md)
- [Chapter13 ShadowMapping](13_04_ShadowMapping.md)
- [Chapter13 SoftShadowPCF](13_05_SoftShadowPCF.md)
- [Chapter13 SoftShadowPCSS](13_06_SoftShadowPCSS.md)
- [Chapter13 Halo](13_07_Halo.md)
- [Chapter13 UnrealSphereLight](13_08_UnrealSphereLight.md)

## 갱신 기준

- Chapter11 NormalMapping을 최소 visual, Chapter13 shadow filtering progression을 대표 visual로 유지한다.
- HDR pipeline과 Halo는 선택 Demo로 유지한다.
- shadow mapping·PCF·PCSS 차이는 정적 비교 sheet로 설명하고 video는 제외한다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
