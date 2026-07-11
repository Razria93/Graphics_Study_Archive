# Build Verification Table

이 문서는 예제별 build/run 확인 결과를 archive 경로 기준으로 기록합니다. 직접 확인하지 않은 항목은 `미확인`으로 둡니다.

## Status Values

| 값 | 의미 |
| --- | --- |
| 미확인 | 아직 빌드/실행하지 않음 |
| 성공 | 해당 항목 확인 완료 |
| 실패 | 실패 원인과 비고 기록 필요 |
| 보류 | 현재 정리 범위 밖이거나 촬영/사용 여부 확인 대기 |
| 해당 없음 | 해당 검증이 필요하지 않음 |

## Minimum Verification Targets

| Part | Example | Debug x64 | Release x64 | 실행 | 캡처 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| Part2 | `Part2_Chapter05-08/05_AffineTransformations_*` | 성공 | 성공 | 성공 | 보류 | Step1-Step4 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM`-`Step9_PhongVsBlinnPhong` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, solid/wireframe toggle |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, normal line mesh, Draw Normals/Normal scale |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step3_Grid` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, `Initialize()` 반환 누락 수정 |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step4_Cylinder` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, cylinder mesh, Use Texture, Wireframe, Draw Normals/Normal scale |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step5_Sphere_*` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step6_Subdivision` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step7_FaceNormals` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_UserSolution` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, sphere mapping, seam correction |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_ReferenceSolution` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, sphere mapping reference |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step9_ModelFiles` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, Assimp dependency, Zelda model load, texture binding |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, rim lighting, `stanford_dragon.stl` |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, cubemap skybox, DDS load, Zelda model |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, environment mapping, `NightPath.dds`, Zelda model, `Use Reflection` |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, image-based lighting, Atrium diffuse/specular IBL DDS, material slider |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, Fresnel effect, Stonewall diffuse/specular IBL DDS, `Material FresnelR0` |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, bloom post-processing, threshold/blur/combine filter, sphere/character |
| Part2 | `Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, Shadertoy fullscreen shader, `shadertoytexture0.jpg`, `iTime` animation |

## Raw Reference Links

| Archive target | Raw reference | 우선 확인 |
| --- | --- | --- |
| `Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step1_DrawingWireFrames` | `MeshData`, `MakeBox()`, rasterizer solid/wire state, `crate2_diffuse.png`, `wall.jpg` |
| `Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step2_DrawingNormals` | normal line mesh, `Mesh.h`, `NormalVertexShader.hlsl`, `NormalPixelShader.hlsl` |
| `Part2_Chapter05-08/07_Modeling_Step3_Grid` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step3_Grid` | `MakeGrid()`, `ojwD8.jpg`, backup folder 제외 |
| `Part2_Chapter05-08/07_Modeling_Step4_Cylinder` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step4_Cylinder` | `MakeCylinder()`, side indices, normal line mesh, backup folder 제외 |
| `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_UserSolution` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step8-2_SphereMapping_Complete` | sphere mapping, seam correction, `ojwD8.jpg`, `wall.jpg`, `crate2_diffuse.png` |
| `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_ReferenceSolution` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step8_SphereMapping_Lecture` | sphere mapping reference solution, `ojwD8.jpg`, `wall.jpg`, `crate2_diffuse.png` |
| `Part2_Chapter05-08/07_Modeling_Step9_ModelFiles` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step9_ModelFiles` | Assimp model loading, `f3d-data/zelda/zeldaPosed001.fbx`, selected diffuse textures |
| `Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step1_RimLighting` | rim lighting, `stanford_dragon.stl`, texture assets |
| `Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step2_Cubemapping` | cubemap skybox, `skybox/skybox.dds`, Zelda model, DirectXTK DDS loader |
| `Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step3_EnvironmentMapping` | environment mapping, `CubemapTextures/HumusTextures/NightPath.dds`, Zelda model, DirectXTK DDS loader |
| `Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step4_ImageBasedLighting` | image-based lighting, `CubemapTextures/Atrium_diffuseIBL.dds`, `CubemapTextures/Atrium_specularIBL.dds`, DirectXTK DDS loader |
| `Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step5_FresnelEffect` | Fresnel effect, `CubemapTextures/Stonewall_diffuseIBL.dds`, `CubemapTextures/Stonewall_specularIBL.dds`, DirectXTK DDS loader |
| `Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step6_BloomEffect` | bloom post-processing, `ImageFilter`, `Threshold/Blur/Combine` shaders, Zelda model, DirectXTK DDS loader |
| `Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy` | `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step7_Shadertoy` | Shadertoy fullscreen shader, `StarPixelShader`, `SeascapePixelShader`, `shadertoytexture0.jpg` |
