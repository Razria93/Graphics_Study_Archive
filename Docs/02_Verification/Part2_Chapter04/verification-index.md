# Part2_Chapter04 Verification Index

이 문서는 `Part2_Chapter04` 예제의 build/run/capture 상태를 기록한다.

## 현재 검증

- 확인 범위: Step1 Triangle, Step1A Triangle To Circle과 Step2 Circle부터 Step10 Lights까지
- 확인 시점: 2026-07-31–2026-08-01
- 실행 기준: project 폴더 CWD, Debug/Release x64 build/run
- 현재 결과: 전체 예제 재검증 완료

## 문서화 이전 이력

- 문서화 이전에도 전체 예제의 build/run 성공을 직접 확인했으나 날짜는 기록하지 않았다.
- 과거 이력은 보조 provenance로 유지하며 현재 상태는 위 재검증 결과를 기준으로 판정한다.

| 예제 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `04_Rasterization_Step1_Triangle` | `Part2_Chapter04/04_Rasterization_Step1_Triangle/04_Rasterization_Step1_Triangle.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_01_triangle.png) | 2026-07-31 현재 확인 · project 폴더 CWD · 사용자 확인 완료 |
| `04_Rasterization_Step1_TriangleToCircle` | `Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/04_Rasterization_Step1_TriangleToCircle.sln` | 성공 | 성공 | 성공 | 성공 | [3](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_3.png), [32](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 사용자 확인 완료 · local video 검증 |
| `04_Rasterization_Step2_Circle` | `Part2_Chapter04/04_Rasterization_Step2_Circle/04_Rasterization_Step2_Circle.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_02_circle.png) | 2026-08-01 현재 확인 · project 폴더 CWD · title과 고정 32 triangles 확인 · 사용자 확인 완료 |
| `04_Rasterization_Step3_Transformations2D` | `Part2_Chapter04/04_Rasterization_Step3_Transformations2D/04_Rasterization_Step3_Transformations2D.sln` | 성공 | 성공 | 성공 | 성공 | [기본](../../_assets/captures/part2_chapter04_03_transformations2d_default.png), [조정](../../_assets/captures/part2_chapter04_03_transformations2d_composed.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 identity/composed transform 확인 · 사용자 확인 완료 |
| `04_Rasterization_Step4_Animation2D` | `Part2_Chapter04/04_Rasterization_Step4_Animation2D/04_Rasterization_Step4_Animation2D.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_04_animation2d.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 계층적 orbit 확인 · screenshot·selected video 사용자 확인 완료 |
| `04_Rasterization_Step5_DepthBuffer` | `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/04_Rasterization_Step5_DepthBuffer.sln` | 성공 | 성공 | 성공 | 성공 | [기본](../../_assets/captures/part2_chapter04_05_depth_buffer_default.png), [반전](../../_assets/captures/part2_chapter04_05_depth_buffer_reordered.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 depth 순서 반전 확인 · screenshot·selected video 기술·사용자 시각 검수 완료 |
| `04_Rasterization_Step6_ShadersConcept` | `Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/04_Rasterization_Step6_ShadersConcept.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_06_shaders_concept.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 runtime shader compile 확인 · screenshot·selected video 기술·사용자 시각 검수 완료 |
| `04_Rasterization_Step7_BackfaceCulling` | `Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling/04_Rasterization_Step7_BackfaceCulling.sln` | 성공 | 성공 | 성공 | 성공 | [Culling On](../../_assets/captures/part2_chapter04_07_backface_culling_on.png), [Culling Off](../../_assets/captures/part2_chapter04_07_backface_culling_off.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 Culling On/Off 확인 · screenshot·selected video 기술·사용자 시각 검수 완료 |
| `04_Rasterization_Step8_PerspectiveProjection` | `Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/04_Rasterization_Step8_PerspectiveProjection.sln` | 성공 | 성공 | 성공 | 성공 | [직교](../../_assets/captures/part2_chapter04_08_perspective_projection_orthographic.png), [affine](../../_assets/captures/part2_chapter04_08_perspective_projection_affine.png), [보정](../../_assets/captures/part2_chapter04_08_perspective_projection_correct.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 projection·interpolation 비교 확인 · 사용자 시각 검수 완료 |
| `04_Rasterization_Step9_Shading` | `Part2_Chapter04/04_Rasterization_Step9_Shading/04_Rasterization_Step9_Shading.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_09_shading.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 directional Blinn-Phong shading 확인 · 사용자 시각 검수 완료 |
| `04_Rasterization_Step10_Lights` | `Part2_Chapter04/04_Rasterization_Step10_Lights/04_Rasterization_Step10_Lights.sln` | 성공 | 성공 | 성공 | 성공 | [Directional](../../_assets/captures/part2_chapter04_10_lights_directional.png), [Point](../../_assets/captures/part2_chapter04_10_lights_point.png), [Spot](../../_assets/captures/part2_chapter04_10_lights_spot.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 Directional·Point·Spot 결과 확인 · 사용자 시각 검수 완료 |

## 갱신 기준

- 현재 실행 결과 또는 과거 확인 근거가 있을 때 상태를 변경한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
- capture/result는 `../capture-matrix.md`와 `Docs/03_Demos`에 연결한다.
