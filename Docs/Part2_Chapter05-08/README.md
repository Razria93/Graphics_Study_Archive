# Part2 Chapter05-08

D3D11 graphics pipeline에서 modeling과 shader toy로 넘어가는 예제들을 정리하는 문서 공간입니다.

## 진행 방식

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08`
- archive에는 예제 실행에 필요한 source/project/shader/asset만 선별 반영합니다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`, raw capture/result는 포함하지 않습니다.
- source 내부의 장문 학습 메모는 `local/Part2_Chapter05-08/<ExampleName>/` 아래로 분리합니다.
- archive source에는 실행 흐름 이해에 필요한 짧은 주석만 남깁니다.
- build/run을 직접 확인하지 않은 항목은 `미확인`으로 기록합니다.

## Examples

| Example | Code split | Build/run | Diff review | Capture | Note |
| --- | --- | --- | --- | --- | --- |
| [`05_AffineTransformations_Step1_Matrix(GLM)`](05_AffineTransformations_Step1_Matrix(GLM)/README.md) | 완료 | 성공 | 진행 중 | 보류 | GLM column-major matrix |
| [`05_AffineTransformations_Step2_Lights(GLM)`](05_AffineTransformations_Step2_Lights(GLM)/README.md) | 완료 | 성공 | 진행 중 | 보류 | GLM model/normal matrix |
| [`05_AffineTransformations_Step3_DirectXMath`](05_AffineTransformations_Step3_DirectXMath/README.md) | 완료 | 성공 | 진행 중 | 보류 | DirectXMath/SimpleMath |
| [`05_AffineTransformations_Step4_Lights(SimpleMath)`](05_AffineTransformations_Step4_Lights(SimpleMath)/README.md) | 완료 | 성공 | 진행 중 | 보류 | SimpleMath lighting |
| [`06_GraphicsPipeline_Step1_COM`](06_GraphicsPipeline_Step1_COM/README.md) | 완료 | 성공 | 진행 중 | 보류 | D3D11 device creation, WRL ComPtr |
| [`06_GraphicsPipeline_Step2_InitializingD3D`](06_GraphicsPipeline_Step2_InitializingD3D/README.md) | 완료 | 성공 | 진행 중 | 보류 | D3D11 initialization, swap chain |
| [`06_GraphicsPipeline_Step3_ModelViewProj`](06_GraphicsPipeline_Step3_ModelViewProj/README.md) | 완료 | 성공 | 진행 중 | 보류 | Model/View/Projection matrix |
| [`06_GraphicsPipeline_Step4_Shaders`](06_GraphicsPipeline_Step4_Shaders/README.md) | 완료 | 성공 | 진행 중 | 보류 | shader semantics, pixel shader constant buffer |
| [`06_GraphicsPipeline_Step5_Texturing`](06_GraphicsPipeline_Step5_Texturing/README.md) | 완료 | 성공 | 진행 중 | 보류 | texture sampling |
| [`06_GraphicsPipeline_Step5_Texturing_LightingSelf`](06_GraphicsPipeline_Step5_Texturing_LightingSelf/README.md) | 완료 | 성공 | 진행 중 | 보류 | texture sampling with lighting |
| [`06_GraphicsPipeline_Step6_Lighting`](06_GraphicsPipeline_Step6_Lighting/README.md) | 완료 | 성공 | 진행 중 | 보류 | Blinn-Phong, directional/point/spot light |
| [`06_GraphicsPipeline_Step7_ResizingViewport`](06_GraphicsPipeline_Step7_ResizingViewport/README.md) | 완료 | 성공 | 진행 중 | 보류 | viewport resizing |
| [`06_GraphicsPipeline_Step8_ResizingWindow`](06_GraphicsPipeline_Step8_ResizingWindow/README.md) | 완료 | 성공 | 진행 중 | 보류 | swap chain resize, render target/depth stencil 재생성 |
| [`06_GraphicsPipeline_Step9_PhongVsBlinnPhong`](06_GraphicsPipeline_Step9_PhongVsBlinnPhong/README.md) | 완료 | 성공 | 진행 중 | 보류 | Phong vs Blinn-Phong specular |
| [`07_Modeling_Step1_DrawingWireFrames`](07_Modeling_Step1_DrawingWireFrames/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, procedural box mesh, solid/wireframe rasterizer state |
| [`07_Modeling_Step2_DrawingNormals`](07_Modeling_Step2_DrawingNormals/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, normal line mesh, `Draw Normals`, `Normal scale` |
| [`07_Modeling_Step3_Grid`](07_Modeling_Step3_Grid/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, procedural grid mesh, texture coordinate, normal overlay |
| [`07_Modeling_Step4_Cylinder`](07_Modeling_Step4_Cylinder/README.md) | 완료 | 미확인 | 진행 중 | 보류 | procedural cylinder mesh, side indices, normal overlay |
| [`07_Modeling_Step5_Sphere_UserSolution`](07_Modeling_Step5_Sphere_UserSolution/README.md) | 완료 | 성공 | 진행 중 | 보류 | user solution, top/bottom half sphere composition |
| [`07_Modeling_Step5_Sphere_ReferenceSolution`](07_Modeling_Step5_Sphere_ReferenceSolution/README.md) | 완료 | 성공 | 진행 중 | 보류 | reference solution, stack/slice sphere generation |
| [`07_Modeling_Step6_Subdivision`](07_Modeling_Step6_Subdivision/README.md) | 완료 | 성공 | 진행 중 | 보류 | subdivision sphere, vertex projection |
| [`07_Modeling_Step7_FaceNormals`](07_Modeling_Step7_FaceNormals/README.md) | 완료 | 성공 | 진행 중 | 보류 | face normal, flat shading |
| [`07_Modeling_Step8_SphereMapping_UserSolution`](07_Modeling_Step8_SphereMapping_UserSolution/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, user solution, sphere mapping seam correction |
| [`07_Modeling_Step8_SphereMapping_ReferenceSolution`](07_Modeling_Step8_SphereMapping_ReferenceSolution/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, reference solution, sphere mapping |
| [`07_Modeling_Step9_ModelFiles`](07_Modeling_Step9_ModelFiles/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, Assimp model loading, Zelda FBX asset |
| [`08_ShaderToys_Step1_RimLighting`](08_ShaderToys_Step1_RimLighting/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, rim lighting, `stanford_dragon.stl` |
| [`08_ShaderToys_Step2_Cubemapping`](08_ShaderToys_Step2_Cubemapping/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, cubemap skybox, DDS texture, Zelda model |
| [`08_ShaderToys_Step3_EnvironmentMapping`](08_ShaderToys_Step3_EnvironmentMapping/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, environment mapping, reflection vector, `NightPath.dds` |

## Modeling Variant 기준

- `*_Lecture`: 강의에서 제안한 reference solution으로 보존합니다.
- `*_Complete`: 사용자 풀이 또는 사용자 완성본으로 보존합니다.
- archive 이름은 필요하면 `ReferenceSolution` / `UserSolution`처럼 제출물 관점의 이름으로 조정합니다.
- `*_Backup*`, `*_Debug`, 단순 중간 실험 폴더는 기본 제외 후보입니다.

## Related Docs

- [Import manifest](../_repo/manifests/Part2_Chapter05-08.md)
- [Migration board](../_repo/tracking/migration-board.md)

## Recent Import Notes

| Example | 상태 |
| --- | --- |
| `07_Modeling_Step5_Sphere_UserSolution` | archive 반영 완료, Debug/Release 실행 성공 |
| `07_Modeling_Step5_Sphere_ReferenceSolution` | archive 반영 완료, Debug/Release 실행 성공 |
| `07_Modeling_Step6_Subdivision` | archive 반영 완료, Debug/Release 실행 성공 |
| `07_Modeling_Step7_FaceNormals` | archive 반영 완료, Debug/Release 실행 성공 |
| `07_Modeling_Step8_SphereMapping_UserSolution` | archive 반영 완료, Debug/Release 실행 성공 |
| `07_Modeling_Step8_SphereMapping_ReferenceSolution` | archive 반영 완료, Debug/Release 실행 성공 |
| `07_Modeling_Step9_ModelFiles` | archive 반영 완료, Debug/Release 실행 성공 |
| `08_ShaderToys_Step1_RimLighting` | archive 반영 완료, Debug/Release 실행 성공 |
| `08_ShaderToys_Step2_Cubemapping` | archive 반영 완료, Debug/Release 실행 성공 |
| `08_ShaderToys_Step3_EnvironmentMapping` | archive 반영 완료, Debug/Release 실행 성공 |

Tracking note: [Part2 Step5 Sphere Tracking](../_repo/tracking/part2-step5-sphere.md)
