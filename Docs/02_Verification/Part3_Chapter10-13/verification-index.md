# Part3_Chapter10-13 Verification Index

이 문서는 `Part3_Chapter10-13` 예제의 build/run/capture 상태를 기록한다.

## Provenance

- Chapter10 확인 시점: 2026-08-04
- Chapter10 현재 재검증: 완료
- Chapter11 확인 시점: 2026-08-04
- Chapter11 현재 재검증: 완료
- Chapter12 확인 시점: 2026-08-04
- Chapter12 현재 재검증: 완료
- Chapter13 확인 시점: 2026-08-04
- Chapter13 현재 재검증: 완료

| 예제 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `10_GeometryPipeline_Step1_GeometryShader` | `Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/10_GeometryPipeline_Step1_GeometryShader.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · quad strip 교정 |
| `10_GeometryPipeline_Step2_Billboards` | `Part3_Chapter10-13/10_GeometryPipeline_Step2_Billboards/10_GeometryPipeline_Step2_Billboards.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · billboard texture array · CENTER/LEFT/RIGHT storyboard |
| `10_GeometryPipeline_Step3_NormalLines` | `Part3_Chapter10-13/10_GeometryPipeline_Step3_NormalLines/10_GeometryPipeline_Step3_NormalLines.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · normal line 기본 표시 |
| `10_GeometryPipeline_Step4_Fireball` | `Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/10_GeometryPipeline_Step4_Fireball.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · procedural animation storyboard · selected local video frame-rate 재검증 필요 |
| `10_GeometryPipeline_Step5_Tessellation` | `Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/10_GeometryPipeline_Step5_Tessellation.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · Manual factor 2/8/16 · Distance Adaptive |
| `11_TexturingTechniques_Step1_Mipmaps` | `Part3_Chapter10-13/11_TexturingTechniques_Step1_Mipmaps/11_TexturingTechniques_Step1_Mipmaps.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · mip level 3 기본값 |
| `11_TexturingTechniques_Step2_NormalMapping` | `Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/11_TexturingTechniques_Step2_NormalMapping.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · normal mapping 기본 On |
| `11_TexturingTechniques_Step3_HeightMapping` | `Part3_Chapter10-13/11_TexturingTechniques_Step3_HeightMapping/11_TexturingTechniques_Step3_HeightMapping.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · sphere height scale 0.04 |
| `11_TexturingTechniques_Step4_HDRI` | `Part3_Chapter10-13/11_TexturingTechniques_Step4_HDRI/11_TexturingTechniques_Step4_HDRI.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · DirectXTex·OpenEXR runtime |
| `11_TexturingTechniques_Step5_HDRPipeline` | `Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/11_TexturingTechniques_Step5_HDRPipeline.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · bloom strength 0.2 |
| `12_PBR_Step1_UnrealPBR` | `Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/12_PBR_Step1_UnrealPBR.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · PBR map 5종 On |
| `12_PBR_Step2_PBRModels` | `Part3_Chapter10-13/12_PBR_Step2_PBRModels/12_PBR_Step2_PBRModels.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · Assimp model과 material map 5종 |
| `13_LightAndShadow_Step1_Mirror` | `Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror/13_LightAndShadow_Step1_Mirror.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · stencil mirror |
| `13_LightAndShadow_Step2_PipelineStateObject` | `Part3_Chapter10-13/13_LightAndShadow_Step2_PipelineStateObject/13_LightAndShadow_Step2_PipelineStateObject.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · pipeline state abstraction |
| `13_LightAndShadow_Step2_Shadow` | `Part3_Chapter10-13/13_LightAndShadow_Step2_Shadow/13_LightAndShadow_Step2_Shadow.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · 공개 표시 Step2B Shadow Prototype |
| `13_LightAndShadow_Step3_DepthBufferAndFog` | `Part3_Chapter10-13/13_LightAndShadow_Step3_DepthBufferAndFog/13_LightAndShadow_Step3_DepthBufferAndFog.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · depth reconstruction과 fog |
| `13_LightAndShadow_Step4_ShadowMapping` | `Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping/13_LightAndShadow_Step4_ShadowMapping.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · hard shadow |
| `13_LightAndShadow_Step5_SoftShadowPCF` | `Part3_Chapter10-13/13_LightAndShadow_Step5_SoftShadowPCF/13_LightAndShadow_Step5_SoftShadowPCF.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · fixed-kernel PCF |
| `13_LightAndShadow_Step6_SoftShadowPCSS` | `Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/13_LightAndShadow_Step6_SoftShadowPCSS.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · blocker search와 variable penumbra |
| `13_LightAndShadow_Step7_Halo` | `Part3_Chapter10-13/13_LightAndShadow_Step7_Halo/13_LightAndShadow_Step7_Halo.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · depth-aware halo |
| `13_LightAndShadow_Step8_UnrealSphereLight` | `Part3_Chapter10-13/13_LightAndShadow_Step8_UnrealSphereLight/13_LightAndShadow_Step8_UnrealSphereLight.sln` | 성공 | 성공 | 성공 | 성공 | 완료 | 현재 확인 · sphere light approximation |

## 갱신 기준

- 현재 실행 결과 또는 과거 확인 근거가 있을 때 상태를 변경한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
- capture/result는 `../capture-matrix.md`와 `Docs/03_Demos`에 연결한다.
## Chapter11 visual 보강 확인

- `11_TexturingTechniques_Step2_NormalMapping`: normal mapping Off/On 1282×752 comparison capture를 확인한다.
- `11_TexturingTechniques_Step3_HeightMapping`: height mapping Off와 `HeightScale 0.1` On 1282×752 comparison capture를 확인한다.
- `11_TexturingTechniques_Step5_HDRPipeline`: bloom strength 0/0.7 1282×752 comparison capture와 selected video evidence를 확인한다.
- Step5 MP4는 Git history에 포함하지 않는다.

## Chapter12 visual 보강 확인

- `12_PBR_Step1_UnrealPBR`: `part3_chapter12_01_pbr_off.png`와 `part3_chapter12_01_pbr_on_height_0_015.png` 비교 capture를 확인한다.
- `12_PBR_Step2_PBRModels`: `part3_chapter12_02_pbr_models_off.png`와 `part3_chapter12_02_pbr_models_on.png` 비교 capture를 확인한다.
- Chapter12 trackball MP4는 selected local evidence로만 유지하고 Git history에 포함하지 않는다.

## Chapter13 visual 보강 확인

- `13_LightAndShadow_Step1_Mirror`: `part3_chapter13_01_mirror_non_mirror.png`와 `part3_chapter13_01_mirror_reflection.png` 비교 capture를 확인한다.
- `13_LightAndShadow_Step3_DepthBufferAndFog`: `part3_chapter13_03_render_depthscale_0p5.png`와 `part3_chapter13_03_depth_depthscale_0p5.png` 비교 capture를 확인한다.
- `13_LightAndShadow_Step4_ShadowMapping`→`13_LightAndShadow_Step6_SoftShadowPCSS`: `part3_chapter13_04_06_shadow_filtering_storyboard.png`로 hard shadow, PCF와 PCSS를 비교한다.
- `13_LightAndShadow_Step7_Halo`: `part3_chapter13_07_halo_strength_0p0.png`와 `part3_chapter13_07_halo_strength_0p6.png`로 Halo Strength Off/On을 비교한다.
- `13_LightAndShadow_Step8_UnrealSphereLight`: `part3_chapter13_08_sphere_light_radius_0p0.png`, `part3_chapter13_08_sphere_light_radius_0p2.png`, `part3_chapter13_08_sphere_light_radius_0p5.png`와 `part3_chapter13_08_sphere_light_radius_storyboard.png`로 sphere light radius 변화를 비교한다.
- Chapter13 MP4는 selected local evidence 또는 GitHub Issue comment 후보로만 유지한다.
