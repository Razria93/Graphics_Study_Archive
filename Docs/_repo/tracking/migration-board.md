# Migration Board

Part1부터 Part4까지 코드/문서 분리, 실행 확인, diff review, refactor 확인, capture 준비 상태를 추적합니다.

## Status Values

| Field | Values |
| --- | --- |
| Code split | 예정 / 진행 중 / 완료 / 보류 |
| Build/run | 미확인 / 빌드 성공 / 성공 / 실패 |
| Diff review | 미확인 / 진행 중 / 완료 |
| Refactor | 미확인 / 불필요 / 필요 / 완료 |
| Capture ready | 아니오 / 예 / 보류 |

## Current Board

| Part | Example | Code split | Build/run | Diff review | Refactor | Capture ready | Note |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Part2 Ch05-08 | `05_AffineTransformations_*` | 완료 | 성공 | 진행 중 | 완료 | 보류 | Step1-Step4 사용자 Debug/Release 실행 확인 |
| Part2 Ch05-08 | `06_GraphicsPipeline_Step1_COM`-`Step9_PhongVsBlinnPhong` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, texture asset public readiness 검토 필요 |
| Part2 Ch05-08 | `07_Modeling_Step1_DrawingWireFrames` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, procedural box mesh, solid/wireframe rasterizer state |
| Part2 Ch05-08 | `07_Modeling_Step2_DrawingNormals` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, normal line mesh, Draw Normals/Normal scale |
| Part2 Ch05-08 | `07_Modeling_Step3_Grid` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, `Initialize()` 반환 누락 수정 |
| Part2 Ch05-08 | `07_Modeling_Step4_Cylinder` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, procedural cylinder mesh, side indices, normal line mesh |
| Part2 Ch05-08 | `07_Modeling_Step5_Sphere_*` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 풀이와 reference solution 함께 보관, 사용자 Debug/Release 실행 확인 |
| Part2 Ch05-08 | `07_Modeling_Step6_Subdivision` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, subdivision sphere |
| Part2 Ch05-08 | `07_Modeling_Step7_FaceNormals` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, face normal shading |
| Part2 Ch05-08 | `07_Modeling_Step8_SphereMapping_*` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, 사용자 풀이와 reference solution 함께 보관 |
| Part2 Ch05-08 | `07_Modeling_Step9_ModelFiles` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, Assimp model loading, Zelda FBX asset 선별 포함 |
| Part2 Ch05-08 | `08_ShaderToys_Step1_RimLighting` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, rim lighting, `stanford_dragon.stl`, shader/asset integrity 확인 완료 |
| Part2 Ch05-08 | `08_ShaderToys_Step2_Cubemapping` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, cubemap skybox, `skybox.dds`, Zelda model, shader/asset integrity 확인 완료 |
| Part2 Ch05-08 | `08_ShaderToys_Step3_EnvironmentMapping` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, environment mapping, `NightPath.dds`, Zelda model, shader/asset integrity 확인 완료 |
| Part2 Ch05-08 | `08_ShaderToys_Step4_ImageBasedLighting` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, image-based lighting, Atrium diffuse/specular IBL DDS, shader/asset integrity 확인 완료 |
| Part2 Ch05-08 | `08_ShaderToys_Step5_FresnelEffect` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, Fresnel effect, Stonewall diffuse/specular IBL DDS, shader/asset integrity 확인 완료 |
| Part2 Ch05-08 | `08_ShaderToys_Step6_BloomEffect` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, bloom post-processing, threshold/blur/combine filter, shader/asset integrity 확인 완료 |
| Part2 Ch05-08 | `08_ShaderToys_Step7_Shadertoy` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, Shadertoy fullscreen shader, `StarPixelShader`, shader profile 보정 |
| Part3 Ch09 | `09_UserInteraction_Step1_FirstPersonView` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, first-person camera, skybox cubemap, ground texture |
| Part3 Ch09 | `09_UserInteraction_Step2_MousePicking` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, mainline source/project 반영, `_Debug` variant 제외 |
| Part3 Ch09 | `09_UserInteraction_Step3_MousePickingRayCollision` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, `_Solution` 기준 source/project 반영, mainline/`_Debug` 미완성 variant 제외 |
| Part3 Ch09 | `09_UserInteraction_Step4_QuaternianRotation` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, raw spelling 유지, Euler X/Y/Z GUI는 raw에서도 미적용 |
| Part3 Ch09 | `09_UserInteraction_Step5_VirtualTrackball` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, mainline source/project 반영, `_Debug` variant 제외 |
| Part3 Ch09 | `09_UserInteraction_Step6_MouseDragMove` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, mouse drag object movement |
| Part3 Ch10-13 | `10_GeometryPipeline_Step1_GeometryShader` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, Release shader setting 보정 |
| Part3 Ch10-13 | `10_GeometryPipeline_Step2_Billboards` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, Release shader setting 보정, TreeBillboards selected assets 포함 |
| Part3 Ch10-13 | `10_GeometryPipeline_Step3_NormalLines` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, Release shader setting 보정 |
| Part3 Ch10-13 | `10_GeometryPipeline_Step4_Fireball` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, fireball texture 포함, Release shader setting 보정 |
| Part3 Ch10-13 | `10_GeometryPipeline_Step5_Tessellation` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | 사용자 Debug/Release 실행 확인, reference snapshot과 tessellation 핵심 파일 차이 있음, Release shader setting 보정 |
| Part3 Ch10-13 | `11_TexturingTechniques_Step1_Mipmaps` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | OriginalExamples 의도 기준 `Mipmaps Level` GUI 복구, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `11_TexturingTechniques_Step2_NormalMapping` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | primary raw 기준 normal map/TBN 구현, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `11_TexturingTechniques_Step3_HeightMapping` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | height texture 기반 vertex displacement, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `11_TexturingTechniques_Step4_HDRI` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | replacement EXR 반영, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `11_TexturingTechniques_Step5_HDRPipeline` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | HDR DDS replacement assets 반영, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `12_PBR_Step1_UnrealPBR` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | Sample HDRI DDS and worn-painted-metal PBR textures 포함, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `12_PBR_Step2_PBRModels` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | character model asset 반영, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step1_Mirror` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | mirror/stencil, Sample HDRI DDS and UV grid texture reused, character asset enabled, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step2_PipelineStateObject` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | pipeline state abstraction, character asset enabled, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step2_Shadow` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | shadow map baseline, sphere main object, final scene path, point-light position GUI minimal 보완, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step3_DepthBufferAndFog` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | depth buffer/fog post effect, Release shader setting 보정, `PostEffectsPS.hlsl` return 변수 오타 보정, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step4_ShadowMapping` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | shadow mapping, primary raw shadow lookup 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step5_SoftShadowPCF` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | PCF soft shadow, primary raw 64-sample PCF 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step6_SoftShadowPCSS` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | PCSS soft shadow, primary raw PCSS 사용자 메모 포함 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step7_Halo` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | halo post effect, primary raw `PostEffectsPS.hlsl` 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| Part3 Ch10-13 | `13_LightAndShadow_Step8_UnrealSphereLight` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | sphere light, primary raw `BasicPS.hlsl` representative point 구현본 반영, Release shader setting 보정, 사용자 Debug/Release 실행 확인 |
| Part4 Ch14-20 | `Examples` project scaffold | 진행 중 | 성공 | 진행 중 | 미확인 | 보류 | 단일 project 구조 반영, `.clang-format` project reference 제거, Ex1401-Ex1408 Debug/Release 확인, Ex1501 확인 대기 |
| Part4 Ch14 | `Ex1401_Basic` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | compute shader back buffer UAV 예제, 32x32 group checkerboard 출력, `Scale` GUI는 현재 shader path 미사용, command argument `1401` |
| Part4 Ch14 | `Ex1402_Blur` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | compute shader separable blur, SRV/UAV ping-pong, Debug/Release 10 FPS 이하 확인, command argument `1402` |
| Part4 Ch14 | `Ex1403_MatVecMult` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | compute shader matrix-vector multiplication, `Error GPU 0`, CPU/GPU result 일치, command argument `1403` |
| Part4 Ch14 | `Ex1404_StructuredBuffer` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | compute shader particle update, structured buffer rendering, Debug/Release 실행 확인, command argument `1404` |
| Part4 Ch14 | `Ex1405_ConsumeAppendBuffer` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | consume/append structured buffer, Ex1404와 유사한 particle rendering, append count output, command argument `1405` |
| Part4 Ch14 | `Ex1406_DensityField` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | density texture, sprite geometry shader, accumulate blend, Debug/Release 실행 확인, command argument `1406` |
| Part4 Ch14 | `Ex1407_IndirectArguments` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | indirect argument buffer, `DrawInstancedIndirect`, Debug/Release 실행 확인, command argument `1407` |
| Part4 Ch14 | `Ex1408_BitonicSort` | 완료 | 성공 | 진행 중 | 미확인 | 보류 | compute shader bitonic sort, CPU/GPU result compare, Debug/Release `OK`, command argument `1408` |
| Part4 Ch15 | `Ex1501_ParticleSystem` | 완료 | 미확인 | 진행 중 | 미확인 | 아니오 | CPU particle update, structured buffer sprite rendering, command argument `1501` |
