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
| Part3 Ch09 | `09_UserInteraction_Step4_QuaternianRotation`-`Step6_MouseDragMove` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | Step4 QuaternianRotation부터 순차 import |
| Part3 Ch10-13 | `10_*`-`13_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | Part2 이후 진행 |
| Part4 Ch14-20 | `14_*`-`20_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | Part2 이후 진행 |
