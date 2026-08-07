# Part1_Chapter03 Verification Index

이 문서는 `Part1_Chapter03` 예제의 build/run/capture 상태를 기록한다.

## Provenance

- Step4–13: 2026-07-30–31 현재 확인, 재검증 완료
- Step14: 2026-07-31 현재 확인, 재검증 완료
- 과거 근거: Chapter README에 기록된 Step4부터 Step14까지 Debug/Release build/run 성공

| 예제 | solution | Debug build | Debug run | Release build | Release run | Provenance | 현재 재검증 | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `03_Raytracing_Step4_DrawingSphere` | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/03_Raytracing_Step4_DrawingSphere.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보: 기본](../../_assets/captures/part1_chapter03_04_drawing-sphere.png) · [조정](../../_assets/captures/part1_chapter03_04_drawing-sphere_parameter-adjusted.png) | project 폴더 CWD에서 shader load, 공개 application title, sphere UI와 기본·파라미터 조정 전체 창 screenshot 확인 |
| `03_Raytracing_Step5_PhongShading` | `Part1_Chapter03/03_Raytracing_Step5_PhongShading/03_Raytracing_Step5_PhongShading.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보: 기본](../../_assets/captures/part1_chapter03_05_phong-shading.png) · [Light 위치 조정](../../_assets/captures/part1_chapter03_05_phong-shading_parameter-adjusted.png) | 2026-07-30 project 폴더 CWD에서 shader load, 공개 application title, sphere lighting과 기본·Light 위치 조정 전체 창 screenshot 확인 |
| `03_Raytracing_Step6_PerspectiveView` | `Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/03_Raytracing_Step6_PerspectiveView.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_06_perspective-view.png) | 2026-07-30 project 폴더 CWD에서 shader load, 공개 application title, perspective sphere scene과 전체 창 screenshot 확인 |
| `03_Raytracing_Step7_Triangle` | `Part1_Chapter03/03_Raytracing_Step7_Triangle/03_Raytracing_Step7_Triangle.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_07_triangle.png) | 2026-07-30 project 폴더 CWD에서 shader load, 공개 application title, triangle·sphere scene과 전체 창 screenshot 확인 |
| `03_Raytracing_Step8_Shadow` | `Part1_Chapter03/03_Raytracing_Step8_Shadow/03_Raytracing_Step8_Shadow.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_08_shadow.png) | 2026-07-31 project 폴더 CWD에서 shader load, 공개 application title, Square composite 바닥·cast shadow 전체 창 screenshot 확인 |
| `03_Raytracing_Step9_BarycentricCordinates` | `Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/03_Raytracing_Step9_BarycentricCordinates.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_09_barycentric_coordinates.png) | 2026-07-31 project 폴더 CWD에서 shader load, 공개 application title, RGB vertex color 보간과 전체 창 screenshot 확인 |
| `03_Raytracing_Step10_Texturing` | `Part1_Chapter03/03_Raytracing_Step10_Texturing/03_Raytracing_Step10_Texturing.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_10_texturing.png) | 2026-07-31 project 폴더 CWD에서 shader·사용자 직접 생성 석재 PNG load, 공개 application title, 자연석 mapping·bilinear sampling·Square seam 부재와 전체 창 screenshot 확인 |
| `03_Raytracing_Step11_Supersampling` | `Part1_Chapter03/03_Raytracing_Step11_Supersampling/03_Raytracing_Step11_Supersampling.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_11_supersampling.png) | 2026-07-31 project 폴더 CWD에서 shader·사용자 직접 생성 석재 PNG load, 공개 application title, 64-sample 평균과 160×90 point-upscaled 전체 창 screenshot 확인 |
| `03_Raytracing_Step12_Reflection` | `Part1_Chapter03/03_Raytracing_Step12_Reflection/03_Raytracing_Step12_Reflection.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_12_reflection.png) | 2026-07-31 project 폴더 CWD에서 shader·사용자 직접 생성 석재 PNG load, 공개 application title, recursive reflection과 전체 창 screenshot 확인 |
| `03_Raytracing_Step13_Transparency` | `Part1_Chapter03/03_Raytracing_Step13_Transparency/03_Raytracing_Step13_Transparency.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_13_transparency.png) | 2026-07-31 project 폴더 CWD에서 shader·사용자 직접 생성 석재 ground와 해수면·하늘 background PNG load, 공개 application title, air/glass refraction과 전체 창 screenshot 확인 |
| `03_Raytracing_Step14_CubeEnvironment` | `Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/03_Raytracing_Step14_CubeEnvironment.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | [확보](../../_assets/captures/part1_chapter03_14_cube_environment.png) | 2026-07-31 project CWD와 repository-root CWD에서 shader·cubemap 6면 load, 공개 title과 environment 전체 창 screenshot 확인 |

## 갱신 기준

- 현재 실행 결과 또는 과거 확인 근거가 있을 때 상태를 변경한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
- capture/result는 `../capture-matrix.md`와 `Docs/03_Demos`에 연결한다.
