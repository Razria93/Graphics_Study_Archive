# Part2_Chapter05-08 Verification Index

이 문서는 `Part2_Chapter05-08` 예제의 build/run/capture 상태를 기록한다.

## Provenance

- 현재 확인: Chapter05 Step1–4, Chapter06 Step1–9와 Chapter07 Step1 DrawingWireFrames·Step2 DrawingNormals·Step3 Grid, 2026-08-02
- 과거 확인: Chapter07 Step4 Cylinder 이후 예제, 문서화 이전(날짜 미기록)
- 현재 재검증: Chapter05 Step1–4, Chapter06 Step1–9와 Chapter07 Step1–3 완료, 나머지 필요
- 근거: 현재 대상의 Debug/Release x64 직접 실행과 Chapter README의 전체 예제 과거 성공 기록

| 예제 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `05_AffineTransformations_Step1_Matrix(GLM)` | `Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix(GLM)/05_AffineTransformations_Step1_Matrix(GLM).sln` | 성공 | 성공 | 성공 | 성공 | 제외 | 2026-08-02 현재 확인 · exit code 0 · Debug/Release stdout 54줄 일치 |
| `05_AffineTransformations_Step2_Lights(GLM)` | `Part2_Chapter05-08/05_AffineTransformations_Step2_Lights(GLM)/05_AffineTransformations_Step2_Lights(GLM).sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · 기본/조정 전체 창 screenshot |
| `05_AffineTransformations_Step3_DirectXMath` | `Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/05_AffineTransformations_Step3_DirectXMath.sln` | 성공 | 성공 | 성공 | 성공 | 제외 | 2026-08-02 현재 확인 · exit code 0 · Debug/Release stdout 24줄 일치 |
| `05_AffineTransformations_Step4_Lights(SimpleMath)` | `Part2_Chapter05-08/05_AffineTransformations_Step4_Lights(SimpleMath)/05_AffineTransformations_Step4_Lights(SimpleMath).sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · 전체 창 screenshot · 사용자 시각 확인 완료 |
| `06_GraphicsPipeline_Step1_COM` | `Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/06_D3D11GraphicsPipeline_Step1_COM.sln` | 성공 | 성공 | 성공 | 성공 | 제외 | 2026-08-02 현재 확인 · exit code 0 · feature level `0xc100` · raw pointer 주소 외 Debug/Release 출력 의미 일치 |
| `06_GraphicsPipeline_Step2_InitializingD3D` | `Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/06_GraphicsPipeline_Step2_InitializingD3D.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · exit code 0 · 기본 perspective 전체 창 screenshot · 자동 기술 검수와 사용자 시각 확인 완료 |
| `06_GraphicsPipeline_Step3_ModelViewProj` | `Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj/06_GraphicsPipeline_Step3_ModelViewProj.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · Model·View·FOV·aspect와 projection 전환 확인 · screenshot 2장과 selected local video 사용자 승인 완료 |
| `06_GraphicsPipeline_Step4_Shaders` | `Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders/06_GraphicsPipeline_Step4_Shaders.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · title·shader compile·`xSplitPoint` UI 반영 확인 · screenshot 2장 사용자 승인 완료 · video 제외 |
| `06_GraphicsPipeline_Step5_Texturing` | `Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing/06_GraphicsPipeline_Step5_Texturing.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · generated texture 2개와 `xSplit` 반영 · 기본/조정 전체 창 screenshot · 사용자 승인 완료 · video 제외 |
| `06_GraphicsPipeline_Step5_Texturing_LightingSelf` | `Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing_LightingSelf/06_GraphicsPipeline_Step5_Texturing.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · generated 목재 texture와 point-light shading 반영 · 기본/조정 전체 창 screenshot · 사용자 승인 완료 · video 제외 |
| `06_GraphicsPipeline_Step6_Lighting` | `Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/06_GraphicsPipeline_Step6_Lighting.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · Directional·Point·Spot 전환과 generated 목재 texture 반영 · 전체 창 screenshot 3장 · 사용자 승인 완료 · video 제외 · 잘못된 CWD exit code `-1` |
| `06_GraphicsPipeline_Step7_ResizingViewport` | `Part2_Chapter05-08/06_GraphicsPipeline_Step7_ResizingViewport/06_GraphicsPipeline_Step7_ResizingViewport.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · ImGui panel과 scene viewport 분리 · exact title과 generated 목재 texture load · Release 전체 창 screenshot 사용자 승인 완료 |
| `06_GraphicsPipeline_Step8_ResizingWindow` | `Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/06_GraphicsPipeline_Step8_ResizingWindow.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · 반복 resize와 minimize/restore · default·wide·compact screenshot 기술·시각 검수 완료 · 기존 recorder 고정 bounds 계약으로 resize video 보류 |
| `06_GraphicsPipeline_Step9_PhongVsBlinnPhong` | `Part2_Chapter05-08/06_GraphicsPipeline_Step9_PhongVsBlinnPhong/06_GraphicsPipeline_Step9_PhongVsBlinnPhong.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · 동일 scene·material·shininess 32의 Phong·Blinn-Phong 전환 · 반복 resize와 minimize/restore · 전체 창 screenshot 2장 기술·시각 검수 완료 · video 제외 |
| `07_Modeling_Step1_DrawingWireFrames` | `Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/07_Modeling_Step1_DrawingWireFrames.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · triangle-list box와 solid·wireframe rasterizer state 전환 · 반복 resize와 minimize/restore · 전체 창 screenshot 기술·시각 검수 완료 · video 제외 |
| `07_Modeling_Step2_DrawingNormals` | `Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/07_Modeling_Step2_DrawingNormals.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · surface `TRIANGLELIST`와 normal `LINELIST` 분리 · Shader Model 5.0 · wide·compact·minimize/restore · 전체 창 screenshot 검수 완료 · video 제외 |
| `07_Modeling_Step3_Grid` | `Part2_Chapter05-08/07_Modeling_Step3_Grid/07_Modeling_Step3_Grid.sln` | 성공 | 성공 | 성공 | 성공 | 확보 | 2026-08-02 현재 확인 · project 폴더 CWD · 5×3 Grid의 24 vertices·30 triangles · Shader Model 5.0 · wide·compact·minimize/restore · 전체 창 screenshot 검수 완료 · video 제외 |
| `07_Modeling_Step4_Cylinder` | `Part2_Chapter05-08/07_Modeling_Step4_Cylinder/07_Modeling_Step4_Cylinder.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step5_Sphere_ReferenceSolution` | `Part2_Chapter05-08/07_Modeling_Step5_Sphere_ReferenceSolution/07_Modeling_Step5_Sphere.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step5_Sphere_UserSolution` | `Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/07_Modeling_Step5_Sphere.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step6_Subdivision` | `Part2_Chapter05-08/07_Modeling_Step6_Subdivision/07_Modeling_Step6_Subdivision.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step7_FaceNormals` | `Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/07_Modeling_Step7_FaceNormals.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step8_SphereMapping_ReferenceSolution` | `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_ReferenceSolution/07_Modeling_Step8_SphereMapping.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step8_SphereMapping_UserSolution` | `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_UserSolution/07_Modeling_Step8_SphereMapping.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `07_Modeling_Step9_ModelFiles` | `Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/07_Modeling_Step9_ModelFiles.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step1_RimLighting` | `Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/08_ShaderToys_Step1_RimLighting.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step2_Cubemapping` | `Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/08_ShaderToys_Step2_Cubemapping.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step3_EnvironmentMapping` | `Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping/08_ShaderToys_Step3_EnvironmentMapping.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step4_ImageBasedLighting` | `Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting/08_ShaderToys_Step4_ImageBasedLighting.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step5_FresnelEffect` | `Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/08_ShaderToys_Step5_FresnelEffect.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step6_BloomEffect` | `Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/08_ShaderToys_Step6_BloomEffect.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `08_ShaderToys_Step7_Shadertoy` | `Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/08_ShaderToys_Step7_Shadertoy.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |

## 갱신 기준

- 현재 실행 결과 또는 과거 확인 근거가 있을 때 상태를 변경한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
- capture/result는 `../capture-matrix.md`와 `Docs/03_Demos`에 연결한다.
