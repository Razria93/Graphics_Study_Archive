# Import Manifest: Part2 Chapter05-08

## Source / Target

- Source: `C:\ComputerGraphics\Part2_Chapter05-08`
- Target: `Part2_Chapter05-08`
- Scope: affine transformations, D3D11 graphics pipeline, modeling, shader toys
- Import status: 진행 중
- Public readiness: 검토 필요
- Build/run status: `05_*`, `06_GraphicsPipeline_Step1`-`Step9`, `07_Modeling_Step1_DrawingWireFrames`-`Step3_Grid`, `07_Modeling_Step5_Sphere_*`, `07_Modeling_Step6_Subdivision`, `07_Modeling_Step7_FaceNormals`, `07_Modeling_Step8_SphereMapping_*`, `07_Modeling_Step9_ModelFiles`, `08_ShaderToys_Step1_RimLighting`-`Step6_BloomEffect` 사용자 Debug/Release 실행 확인 완료. `07_Modeling_Step4_Cylinder`, `08_ShaderToys_Step7_Shadertoy`는 import 완료, build/run 미확인.

## Step Inventory

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `05_AffineTransformations_Step1_Matrix(GLM)` | 반영 완료 | 성공 | 검토 필요 | GLM column-major matrix |
| `05_AffineTransformations_Step2_Lights(GLM)` | 반영 완료 | 성공 | 검토 필요 | GLM model/normal matrix |
| `05_AffineTransformations_Step3_DirectXMath` | 반영 완료 | 성공 | 검토 필요 | DirectXMath/SimpleMath |
| `05_AffineTransformations_Step4_Lights(SimpleMath)` | 반영 완료 | 성공 | 검토 필요 | SimpleMath lighting |
| `06_GraphicsPipeline_Step1_COM` | 반영 완료 | 성공 | 검토 필요 | D3D11 device creation, WRL ComPtr |
| `06_GraphicsPipeline_Step2_InitializingD3D` | 반영 완료 | 성공 | 검토 필요 | D3D11 initialization, swap chain |
| `06_GraphicsPipeline_Step3_ModelViewProj` | 반영 완료 | 성공 | 검토 필요 | Model/View/Projection matrix |
| `06_GraphicsPipeline_Step4_Shaders` | 반영 완료 | 성공 | 검토 필요 | shader semantics and pixel shader constant buffer |
| `06_GraphicsPipeline_Step5_Texturing` | 반영 완료 | 성공 | 검토 필요 | `crate2_diffuse.png`, `wall.jpg` 포함 |
| `06_GraphicsPipeline_Step5_Texturing_LightingSelf` | 반영 완료 | 성공 | 검토 필요 | raw project filename은 `06_GraphicsPipeline_Step5_Texturing.*` 재사용 |
| `06_GraphicsPipeline_Step6_Lighting` | 반영 완료 | 성공 | 검토 필요 | Blinn-Phong, directional/point/spot light |
| `06_GraphicsPipeline_Step7_ResizingViewport` | 반영 완료 | 성공 | 검토 필요 | viewport resizing |
| `06_GraphicsPipeline_Step8_ResizingWindow` | 반영 완료 | 성공 | 검토 필요 | `ResizeBuffers()`, render target/depth stencil 재생성 |
| `06_GraphicsPipeline_Step9_PhongVsBlinnPhong` | 반영 완료 | 성공 | 검토 필요 | Phong vs Blinn-Phong specular |
| `07_Modeling_Step1_DrawingWireFrames` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, `MeshData`, `MakeBox()`, solid/wireframe rasterizer state, texture assets 포함 |
| `07_Modeling_Step2_DrawingNormals` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, normal line mesh, `Mesh`, `NormalVertexShader`, `NormalPixelShader`, texture assets 포함 |
| `07_Modeling_Step3_Grid` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, `MakeGrid()`, procedural grid mesh, `ojwD8.jpg`, backup folder 제외, `Initialize()` 반환 누락 수정 |
| `07_Modeling_Step4_Cylinder` | 반영 완료 | 미확인 | 검토 필요 | `MakeCylinder()`, procedural cylinder mesh, texture assets 포함, backup folder 제외 |
| `07_Modeling_Step5_Sphere_UserSolution` | 반영 완료 | 성공 | 검토 필요 | `07_Modeling_Step5-3_Sphere_Complete` 기반 사용자 풀이 |
| `07_Modeling_Step5_Sphere_ReferenceSolution` | 반영 완료 | 성공 | 검토 필요 | `07_Modeling_Step5_Sphere_Lecture` 기반 reference solution |
| `07_Modeling_Step6_Subdivision` | 반영 완료 | 성공 | 검토 필요 | subdivision sphere, vertex projection |
| `07_Modeling_Step7_FaceNormals` | 반영 완료 | 성공 | 검토 필요 | face normal, flat shading |
| `07_Modeling_Step8_SphereMapping_UserSolution` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, `07_Modeling_Step8-2_SphereMapping_Complete` 기반 사용자 풀이, seam correction |
| `07_Modeling_Step8_SphereMapping_ReferenceSolution` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, `07_Modeling_Step8_SphereMapping_Lecture` 기반 reference solution |
| `07_Modeling_Step9_ModelFiles` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, Assimp model loading, Zelda FBX와 diffuse texture 선별 포함 |
| `08_ShaderToys_Step1_RimLighting` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, rim lighting, `stanford_dragon.stl` 포함 |
| `08_ShaderToys_Step2_Cubemapping` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, cubemap skybox, `skybox.dds`, Zelda model 포함 |
| `08_ShaderToys_Step3_EnvironmentMapping` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, environment mapping, `NightPath.dds`, Zelda model 포함 |
| `08_ShaderToys_Step4_ImageBasedLighting` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, image-based lighting, Atrium diffuse/specular IBL DDS 포함 |
| `08_ShaderToys_Step5_FresnelEffect` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, Schlick Fresnel, Stonewall diffuse/specular IBL DDS 포함 |
| `08_ShaderToys_Step6_BloomEffect` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, bloom post-processing, filter chain, Zelda model 포함 |
| `08_ShaderToys_Step7_Shadertoy` | 반영 완료 | 미확인 | 검토 필요 | Shadertoy fullscreen shader, `shadertoytexture0.jpg`, license/attribution 검토 필요 |
| `07_Modeling_*` | 예정 | 미확인 | 검토 필요 | mesh generation/modeling |
| `08_ShaderToys_*` | 예정 | 미확인 | 검토 필요 | shader toy effects |

## Include Candidates

- `.sln`, `.vcxproj`, `.vcxproj.filters`
- `*.cpp`, `*.h`, `*.hlsl`, `*.hlsli`
- 실행에 필요한 기본 asset. 단, public readiness는 별도 검토합니다.

## Exclude Patterns

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- `.clang-format`
- raw result/capture/video
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료

## Comment / Memo Handling

- source 내부의 장문 학습 메모와 출력 결과 주석은 archive source에 그대로 두지 않습니다.
- 실행 흐름 이해에 필요한 짧은 주석만 새로 남깁니다.
- 원문 메모의 위치와 요약은 `local/Part2_Chapter05-08/<ExampleName>/` 아래에 기록합니다.
- local 문서는 `.gitignore` 대상이므로 commit에 포함하지 않습니다.

## Modeling Variant Import Rule

- `*_Lecture`는 강의에서 제안한 reference solution으로 보고 제외하지 않습니다.
- `*_Complete`는 사용자 풀이 또는 사용자 완성본으로 보고 제외하지 않습니다.
- archive 이름은 제출물 관점에서 `Lecture` / `Complete` 대신 `ReferenceSolution` / `UserSolution`처럼 의미가 드러나는 이름으로 바꿀 수 있습니다.
- backup, debug, 중간 실험 폴더는 기본 제외 후보로 둡니다.
- 현재 확인된 쌍:
  - `07_Modeling_Step5_Sphere_Lecture` -> `07_Modeling_Step5_Sphere_ReferenceSolution`
  - `07_Modeling_Step5-3_Sphere_Complete` -> `07_Modeling_Step5_Sphere_UserSolution`
  - `07_Modeling_Step8_SphereMapping_Lecture` -> `07_Modeling_Step8_SphereMapping_ReferenceSolution`
  - `07_Modeling_Step8-2_SphereMapping_Complete` -> `07_Modeling_Step8_SphereMapping_UserSolution`

## Current Next Action

1. `08_ShaderToys_Step7_Shadertoy` Debug/Release 실행을 확인합니다.
