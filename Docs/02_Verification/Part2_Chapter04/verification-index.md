# Part2_Chapter04 Verification Index

이 문서는 `Part2_Chapter04` 예제의 build/run/capture 상태를 기록한다.

## Provenance

- 현재 확인: Step1 Triangle, Step1A Triangle To Circle, Step2 Circle과 Step3 Transformations2D, 2026-07-31–2026-08-01 Debug/Release x64 build/run
- 확인 근거: 과거 확인
- 확인 시점: 문서화 이전(날짜 미기록)
- 현재 재검증: Step1·Step1A·Step2·Step3 완료, 나머지 예제 필요
- 근거: Chapter README에 기록된 전체 예제 Debug/Release build/run 성공

| 예제 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `04_Rasterization_Step1_Triangle` | `Part2_Chapter04/04_Rasterization_Step1_Triangle/04_Rasterization_Step1_Triangle.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_01_triangle.png) | 2026-07-31 현재 확인 · project 폴더 CWD · 사용자 확인 완료 |
| `04_Rasterization_Step1_TriangleToCircle` | `Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/04_Rasterization_Step1_TriangleToCircle.sln` | 성공 | 성공 | 성공 | 성공 | [3](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_3.png), [32](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 사용자 확인 완료 · local video 검증 |
| `04_Rasterization_Step2_Circle` | `Part2_Chapter04/04_Rasterization_Step2_Circle/04_Rasterization_Step2_Circle.sln` | 성공 | 성공 | 성공 | 성공 | [확보](../../_assets/captures/part2_chapter04_02_circle.png) | 2026-08-01 현재 확인 · project 폴더 CWD · title과 고정 32 triangles 확인 · 사용자 확인 완료 |
| `04_Rasterization_Step3_Transformations2D` | `Part2_Chapter04/04_Rasterization_Step3_Transformations2D/04_Rasterization_Step3_Transformations2D.sln` | 성공 | 성공 | 성공 | 성공 | [기본](../../_assets/captures/part2_chapter04_03_transformations2d_default.png), [조정](../../_assets/captures/part2_chapter04_03_transformations2d_composed.png) | 2026-08-01 현재 확인 · project 폴더 CWD · 표준 title과 identity/composed transform 확인 · 사용자 확인 완료 |
| `04_Rasterization_Step4_Animation2D` | `Part2_Chapter04/04_Rasterization_Step4_Animation2D/04_Rasterization_Step4_Animation2D.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `04_Rasterization_Step5_DepthBuffer` | `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/04_Rasterization_Step5_DepthBuffer.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `04_Rasterization_Step6_ShadersConcept` | `Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/04_Rasterization_Step6_ShadersConcept.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `04_Rasterization_Step7_BackfaceCulling` | `Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling/04_Rasterization_Step7_BackfaceCulling.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `04_Rasterization_Step8_PerspectiveProjection` | `Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/04_Rasterization_Step8_PerspectiveProjection.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `04_Rasterization_Step9_Shading` | `Part2_Chapter04/04_Rasterization_Step9_Shading/04_Rasterization_Step9_Shading.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `04_Rasterization_Step10_Lights` | `Part2_Chapter04/04_Rasterization_Step10_Lights/04_Rasterization_Step10_Lights.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |

## 갱신 기준

- 현재 실행 결과 또는 과거 확인 근거가 있을 때 상태를 변경한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
- capture/result는 `../capture-matrix.md`와 `Docs/03_Demos`에 연결한다.
