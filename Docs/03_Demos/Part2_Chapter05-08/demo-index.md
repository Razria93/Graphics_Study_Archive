# Part2_Chapter05-08 Demo Index

이 문서는 `Part2_Chapter05-08`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: pipeline, modeling, cubemap, IBL, bloom
- 비고: Chapter05부터 Chapter08까지 대표 구현 축과 visual 선별 완료

## Demo 목록

| Demo 후보 | 연결 Example | 연결 Topic | Verification | Capture/Result | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Chapter05 Step2 Lights(GLM)](../../../Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md), [Step4 Lights(SimpleMath)](../../../Part2_Chapter05-08/05_AffineTransformations_Step4_Lights%28SimpleMath%29/README.md) | [Matrix And Affine Transformations](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md), [Phong And Blinn-Phong](../../01_Topics/LightingAndShading/PhongAndBlinnPhong.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | [GLM default](../../_assets/captures/part2_chapter05_02_lights_glm_default.png), [GLM adjusted](../../_assets/captures/part2_chapter05_02_lights_glm_adjusted.png), [SimpleMath adjusted](../../_assets/captures/part2_chapter05_04_lights_simplemath_adjusted.png) | 확보 | 상세 Demo [Step2](05_LightsGLM.md)·[Step4](05_LightsSimpleMath.md) · [Demo Issue #17](https://github.com/Razria93/Graphics_Study_Archive/issues/17) |
| 대표 capture | [Chapter06 Step6 Lighting](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/README.md), [Chapter07 Step8 SphereMapping](../../../Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/README.md), [Chapter08 Step6 BloomEffect](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/README.md) | [Light Types](../../01_Topics/LightingAndShading/LightTypes.md), [Spherical Texture Mapping](../../01_Topics/TexturingAndMapping/SphericalTextureMapping.md), [Post Processing And Bloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | [Lighting](../../_assets/captures/part2_chapter06_06_lighting_spot.png), [SphereMapping](../../_assets/captures/part2_chapter07_08_sphere_mapping.png), [Bloom](../../_assets/captures/part2_chapter08_06_bloom_effect.png) | 확보 | 상세 Demo [Lighting](06_Lighting.md)·[SphereMapping](07_08_SphereMapping.md)·[Bloom](08_06_BloomEffect.md) · Issue [#18](https://github.com/Razria93/Graphics_Study_Archive/issues/18), [#19](https://github.com/Razria93/Graphics_Study_Archive/issues/19), [#22](https://github.com/Razria93/Graphics_Study_Archive/issues/22) |
| video | [Chapter06 Step3 ModelViewProj](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj/README.md), [Step8 ResizingWindow](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/README.md), [Chapter08 Step7 Shadertoy](../../../Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/README.md) | [Matrix And Affine Transformations](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md), [Swap Chain And Viewport](../../01_Topics/DirectX11Pipeline/SwapChainAndViewport.md), [Shadertoy Runtime Inputs](../../01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | [ModelViewProj](../../_assets/captures/part2_chapter06_03_model_view_proj_perspective.png), [Resize](../../_assets/captures/part2_chapter06_08_resizing_window_wide.png), [Shadertoy](../../_assets/captures/part2_chapter08_07_shadertoy.png) | 보류 | Step3·Shadertoy video는 local evidence로 유지하고 resize video는 recorder bounds 지원 전까지 보류함 |

## 상세 Demo 문서

- [Chapter05 DirectXMath](05_DirectXMath.md)
- [Chapter05 LightsGLM](05_LightsGLM.md)
- [Chapter05 LightsSimpleMath](05_LightsSimpleMath.md)
- [Chapter05 MatrixGLM](05_MatrixGLM.md)
- [Chapter06 COM](06_COM.md)
- [Chapter06 InitializingD3D](06_InitializingD3D.md)
- [Chapter06 Lighting](06_Lighting.md)
- [Chapter06 ModelViewProj](06_ModelViewProj.md)
- [Chapter06 Shaders](06_Shaders.md)
- [Chapter06 Texturing](06_Texturing.md)
- [Chapter06 TexturingLightingSelf](06_TexturingLightingSelf.md)
- [Chapter07 DrawingWireFrames](07_01_DrawingWireFrames.md)
- [Chapter07 DrawingNormals](07_02_DrawingNormals.md)
- [Chapter07 Grid](07_03_Grid.md)
- [Chapter07 Cylinder](07_04_Cylinder.md)
- [Chapter07 Sphere](07_05_Sphere.md)
- [Chapter07 Subdivision](07_06_Subdivision.md)
- [Chapter07 FaceNormals](07_07_FaceNormals.md)
- [Chapter07 SphereMapping](07_08_SphereMapping.md)
- [Chapter07 ModelFiles](07_09_ModelFiles.md)
- [Chapter07 ResizingViewport](07_ResizingViewport.md)
- [Chapter08 RimLighting](08_01_RimLighting.md)
- [Chapter08 Cubemapping](08_02_Cubemapping.md)
- [Chapter08 EnvironmentMapping](08_03_EnvironmentMapping.md)
- [Chapter08 ImageBasedLighting](08_04_ImageBasedLighting.md)
- [Chapter08 FresnelEffect](08_05_FresnelEffect.md)
- [Chapter08 BloomEffect](08_06_BloomEffect.md)
- [Chapter08 Shadertoy](08_07_Shadertoy.md)
- [Chapter08 ResizingWindow](08_ResizingWindow.md)
- [Chapter09 PhongVsBlinnPhong](09_PhongVsBlinnPhong.md)

## 갱신 기준

- Chapter05 affine 비교를 최소 기준선으로 유지한다.
- Chapter06 pipeline·lighting, Chapter07 modeling·mapping과 Chapter08 shader experiment를 대표 visual로 유지한다.
- selected local video와 recorder 제약이 남은 resize video는 일반 Git history에서 제외하고 `보류`로 기록한다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
