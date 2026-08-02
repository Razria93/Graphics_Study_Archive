# Captures

이 폴더는 검토된 screenshot과 result image를 둔다. 검토 전 후보, 실패한 capture, 중복 capture는 이 폴더에 승격하지 않는다.

## 기준

- build/run 상태가 `성공` 또는 `부분 성공`인 예제의 capture/result만 둔다.
- 파일명은 Part/Chapter/Portfolio, 예제 또는 Topic을 드러낸다.
- 강의 화면 캡처, 유료 자료, 출처 불명 asset은 제외한다.
- `Docs/03_Demos` 또는 `Docs/02_Verification`에서 실제로 참조하는 capture/result만 둔다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.

## 파일명 기준

상세 파일명 정책의 정본은 `Docs/06_Policies/demo-capture-policy.md`를 따른다.

```text
part#_chapter##_example-or-topic.png
part#_chapter##-##_example-or-topic_input.png
part#_chapter##-##_example-or-topic_result.png
portfolio_raytracer_topic.png
```

예시:

```text
part1_chapter01-02_02_bloom_input.jpg
part1_chapter01-02_02_bloom_result.png
part2_chapter04_depth-buffer.png
```

파일명에는 branch 이름이나 PR 번호보다 Part/Chapter/Portfolio와 graphics 개념을 우선 반영한다.

## 승격된 파일

| 파일 | 유형 | 연결 예제 | 상태 | 비고 |
| --- | --- | --- | --- | --- |
| `part1_chapter01-02_02_bloom_input.jpg` | input image | `Part1_Chapter01-02/02_Bloom` | 확보 | bloom 전 원본 비교 이미지 |
| `part1_chapter01-02_02_bloom_result.png` | result image | `Part1_Chapter01-02/02_Bloom` | 확보 | ChatGPT 생성 입력 이미지 기반 `result.png`를 승격함 |
| `part1_chapter03_04_drawing-sphere.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere` | 확보 | Debug x64 전체 application window에서 기본 sphere와 조절 UI 확인 |
| `part1_chapter03_04_drawing-sphere_parameter-adjusted.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere` | 확보 | 전체 application window에서 Center, Radius와 RGB 조정 결과 확인 |
| `part1_chapter03_05_phong-shading.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step5_PhongShading` | 확보 | Debug x64 전체 application window에서 기본 Phong lighting과 parameter UI 확인 |
| `part1_chapter03_05_phong-shading_parameter-adjusted.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step5_PhongShading` | 확보 | 전체 application window에서 Light 위치 조정과 highlight 이동 확인 |
| `part1_chapter03_06_perspective-view.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step6_PerspectiveView` | 확보 | Release x64 전체 application window에서 perspective 크기 변화와 sphere overlap 확인 |
| `part1_chapter03_07_triangle.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step7_Triangle` | 확보 | Debug x64 전체 application window에서 triangle 경계, flat normal shading과 sphere closest-hit 확인 |
| `part1_chapter03_08_shadow.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step8_Shadow` | 확보 | Release x64 전체 application window에서 Square 바닥의 연속 면과 cast shadow 확인 |
| `part1_chapter03_09_barycentric_coordinates.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates` | 확보 | Release x64 전체 application window에서 RGB vertex color의 연속 보간 확인 |
| `part1_chapter03_10_texturing.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step10_Texturing` | 확보 | Release x64 전체 application window에서 사용자 직접 생성 석재 texture의 mapping·보간·seam 부재 확인 |
| `part1_chapter03_11_supersampling.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step11_Supersampling` | 확보 | Release x64 전체 application window에서 160×90 grid의 64-sample 평균과 8배 point upscale 확인 |
| `part1_chapter03_12_reflection.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step12_Reflection` | 확보 | Release x64 전체 application window에서 ground와 blue sphere의 recursive reflection 확인 |
| `part1_chapter03_13_transparency.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step13_Transparency` | 확보 | Release x64 전체 application window에서 sphere 내부의 해수면·하늘 background 왜곡과 enter/exit 경계 확인 |
| `part1_chapter03_14_cube_environment.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment` | 확보 | Release x64 전체 application window에서 PosZ 중심과 PosX·NegX 경계 environment 확인 |
| `part2_chapter04_01_triangle.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step1_Triangle` | 확보 | Edge function coverage와 barycentric RGB interpolation 결과 확인 |
| `part2_chapter04_01a_triangle_to_circle_segments_3.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle` | 확보 | 3개 segment의 triangle silhouette와 red center·blue boundary 보간 확인 |
| `part2_chapter04_01a_triangle_to_circle_segments_32.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle` | 확보 | 32개 segment에서 같은 반지름·색 보간을 유지한 circle 근사 확인 |
| `part2_chapter04_02_circle.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step2_Circle` | 확보 | 32개 indexed triangle fan과 red center·green boundary 보간 확인 |
| `part2_chapter04_03_transformations2d_default.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step3_Transformations2D` | 확보 | 원점의 5-segment fan과 identity transform 기준 상태 확인 |
| `part2_chapter04_03_transformations2d_composed.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step3_Transformations2D` | 확보 | rotation·non-uniform scale·translation 합성에 따른 orientation·aspect·위치 변화 확인 |
| `part2_chapter04_04_animation2d.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step4_Animation2D` | 확보 | Sun·Earth·Moon의 한 시점 계층 배치와 Scene Control UI 확인 |
| `part2_chapter04_05_depth_buffer_default.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer` | 확보 | red 0.1·blue 0.3·yellow 0.7의 기본 depth visibility 확인 |
| `part2_chapter04_05_depth_buffer_reordered.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer` | 확보 | red 0.7·blue 0.3·yellow 0.1의 반전 depth visibility 확인 |
| `part2_chapter04_06_shaders_concept.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step6_ShadersConcept` | 확보 | CPU vertex stage rotation이 적용된 white square와 framebuffer 출력 확인 |
| `part2_chapter04_07_backface_culling_on.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling` | 확보 | Culling On에서 front-facing 왼쪽 square만 남는 결과 확인 |
| `part2_chapter04_07_backface_culling_off.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling` | 확보 | Culling Off에서 반전된 오른쪽 square까지 표시되는 결과 확인 |
| `part2_chapter04_08_perspective_projection_orthographic.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection` | 확보 | 서로 다른 Z에서도 같은 크기를 유지하는 orthographic 기준 상태 확인 |
| `part2_chapter04_08_perspective_projection_affine.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection` | 확보 | Perspective 크기 변화와 screen-space affine checker 왜곡 확인 |
| `part2_chapter04_08_perspective_projection_correct.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection` | 확보 | Reciprocal-depth 보정 이후 perspective-correct checker 결과 확인 |
| `part2_chapter04_09_shading.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step9_Shading` | 확보 | Face별 flat normal과 directional Blinn-Phong shading, material·light UI 확인 |
| `part2_chapter04_10_lights_directional.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step10_Lights` | 확보 | 공통 기본 parameter에서 거리 감쇠 없는 Directional Light 결과 확인 |
| `part2_chapter04_10_lights_point.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step10_Lights` | 확보 | Position `(0, 0.5, 0.5)`과 선형 distance attenuation의 radial highlight 확인 |
| `part2_chapter04_10_lights_spot.png` | screenshot | `Part2_Chapter04/04_Rasterization_Step10_Lights` | 확보 | Point 감쇠에 `spotPower=400` cone factor를 적용한 집중 영역 확인 |
| `part2_chapter04_10_lights_comparison.png` | comparison image | `Part2_Chapter04/04_Rasterization_Step10_Lights` | 확보 | 동일한 기본 parameter의 Directional·Point·Spot screenshot을 원본 크기로 세로 배치한 GitHub Demo Issue용 비교 자료 |
| `part2_chapter05_02_lights_glm_default.png` | screenshot | `Part2_Chapter05-08/05_AffineTransformations_Step2_Lights(GLM)` | 확보 | 기본 transform과 Directional Light의 전체 application window 확인 |
| `part2_chapter05_02_lights_glm_adjusted.png` | screenshot | `Part2_Chapter05-08/05_AffineTransformations_Step2_Lights(GLM)` | 확보 | Y rotation과 non-uniform scale을 적용한 geometry·lighting 변화 확인 |
| `part2_chapter05_04_lights_simplemath_adjusted.png` | screenshot | `Part2_Chapter05-08/05_AffineTransformations_Step4_Lights(SimpleMath)` | 확보 | Step2 GLM과 같은 transform 의도를 SimpleMath row-vector convention으로 재구성한 geometry·lighting 결과 확인 |
| `part2_chapter06_02_initializing_d3d.png` | screenshot | `Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D` | 확보 | 전체 application window에서 기본 perspective color cube, Scene Control과 D3D11 frame 출력 확인 |
| `part2_chapter06_03_model_view_proj_perspective.png` | screenshot | `Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj` | 확보 | 전체 application window에서 조정한 Model·View와 perspective projection 결과 확인 |
| `part2_chapter06_03_model_view_proj_orthographic.png` | screenshot | `Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj` | 확보 | 동일한 Model·View에서 orthographic projection의 일정한 투영 크기 확인 |
| `part2_chapter06_04_shaders_default.png` | screenshot | `Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders` | 확보 | 전체 application window에서 `xSplitPoint=0.5`의 균등 UV X·Y 분기 확인 |
| `part2_chapter06_04_shaders_split_adjusted.png` | screenshot | `Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders` | 확보 | 동일한 window에서 `xSplitPoint=0.25`의 세로·가로 경계 이동 확인 |

## 승격 체크

| 항목 | 기준 |
| --- | --- |
| 실행 상태 | build/run 상태가 `성공` 또는 `부분 성공`임 |
| 문서 연결 | demo-index, capture-plan, capture-matrix 중 하나 이상에서 참조함 |
| 설명 가능성 | capture/result가 보여주는 graphics 개념을 설명할 수 있음 |
| 중복 여부 | 같은 의미의 capture/result가 이미 승격되어 있지 않음 |
| 공개 가능성 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |
| 식별자 검수 | 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로가 보이지 않음 |

## 연결 문서

- Demo 계획: `Docs/03_Demos`
- Capture 상태: `Docs/02_Verification/capture-matrix.md`
- 공개 판단: `Docs/05_Publication`

## 제외 기준

- 실패 화면만 담긴 capture
- 화질이나 구도가 낮아 개념을 설명하기 어려운 capture/result
- 동일한 의미의 중복 capture/result
- 강의 화면 또는 유료 자료가 포함된 capture/result
- 문서에서 참조하지 않는 보관용 capture/result
