# Part1_Chapter03 Demo Index

이 문서는 `Part1_Chapter03`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: ray tracing steps, reflection, transparency, cubemap
- 비고: Step4~14 독립 상세 Demo를 순차적으로 작성하고 등급은 전체 완료 후 확정

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step4 DrawingSphere](04_DrawingSphere.md) | [Step4 Example](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md) | [Ray](../../01_Topics/RayTracing/Ray.md), [Intersection](../../01_Topics/RayTracing/Intersection.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_04_drawing-sphere.png), [파라미터 조정](../../_assets/captures/part1_chapter03_04_drawing-sphere_parameter-adjusted.png) | 미게시 | 후보 | Step4 최소 capture 후보, 등급은 전체 Step 완료 후 확정 |
| 대표 capture | 없음 | 미확인 | 미확인 | [Verification](../../02_Verification/Part1_Chapter03/verification-index.md) | 없음 | 미게시 | 후보 | 전체 Step 완료 후 선정 |
| video | 없음 | 미확인 | 미확인 | [Verification](../../02_Verification/Part1_Chapter03/verification-index.md) | 없음 | 미게시 | 미확인 | 전체 Step 완료 후 필요 여부 검토 |
| Step4 DrawingSphere | [상세 Demo](04_DrawingSphere.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md) | [Ray](../../01_Topics/RayTracing/Ray.md), [Intersection](../../01_Topics/RayTracing/Intersection.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_04_drawing-sphere.png), [파라미터 조정](../../_assets/captures/part1_chapter03_04_drawing-sphere_parameter-adjusted.png) | 미게시 | 확보 | 2026-07-30 Debug/Release x64와 전체 창 비교 screenshot 확인 |
| Step5 PhongShading | [상세 Demo](05_PhongShading.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step5_PhongShading/README.md) | [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_05_phong-shading.png), [Light 위치 조정](../../_assets/captures/part1_chapter03_05_phong-shading_parameter-adjusted.png) | 미게시 | 확보 | 2026-07-30 Debug/Release x64와 전체 창 비교 screenshot 확인 |
| Step6 PerspectiveView | [상세 Demo](06_PerspectiveView.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/README.md) | [Ray](../../01_Topics/RayTracing/Ray.md), [Intersection](../../01_Topics/RayTracing/Intersection.md), [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_06_perspective-view.png) | 미게시 | 확보 | 2026-07-30 Debug/Release x64와 perspective scene 전체 창 screenshot 확인 |
| Step7 Triangle | [상세 Demo](07_Triangle.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/README.md) | [Ray](../../01_Topics/RayTracing/Ray.md), [Intersection](../../01_Topics/RayTracing/Intersection.md), [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_07_triangle.png) | 미게시 | 확보 | 2026-07-30 Debug/Release x64와 triangle·sphere scene 전체 창 screenshot 확인 |
| Step8 Shadow | [상세 Demo](08_Shadow.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow/README.md) | [Shadow Ray](../../01_Topics/Shadows/ShadowRay.md), [Intersection](../../01_Topics/RayTracing/Intersection.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_08_shadow.png) | 미게시 | 확보 | 2026-07-31 Debug/Release x64와 Square composite 바닥·cast shadow 전체 창 screenshot 확인 |
| Step9 Barycentric Coordinates | [상세 Demo](09_BarycentricCoordinates.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/README.md) | [Barycentric Coordinates](../../01_Topics/RayTracing/BarycentricCoordinates.md), [Intersection](../../01_Topics/RayTracing/Intersection.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_09_barycentric_coordinates.png) | 미게시 | 확보 | 2026-07-31 Debug/Release x64와 RGB vertex color 보간 전체 창 screenshot 확인 |
| Step10 Texturing | [상세 Demo](10_Texturing.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step10_Texturing/README.md) | [Texture Sampling](../../01_Topics/TexturingAndMapping/TextureSampling.md), [Barycentric Coordinates](../../01_Topics/RayTracing/BarycentricCoordinates.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_10_texturing.png) | 미게시 | 확보 | 2026-07-31 Debug/Release x64와 사용자 직접 생성 석재 texture의 자연석 mapping·bilinear sampling·Square seam 부재 전체 창 screenshot 확인 |
| Step11 Supersampling | [상세 Demo](11_Supersampling.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step11_Supersampling/README.md) | [Sampling And Anti Aliasing](../../01_Topics/RayTracing/SamplingAndAntiAliasing.md), [Texture Sampling](../../01_Topics/TexturingAndMapping/TextureSampling.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_11_supersampling.png) | 미게시 | 확보 | 2026-07-31 Debug/Release x64와 160×90 grid의 64-sample 평균·point-upscaled 전체 창 screenshot 확인 |
| Step12 Reflection | [상세 Demo](12_Reflection.md) | [Example README](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/README.md) | [Recursive Reflection](../../01_Topics/RayTracing/RecursiveReflection.md), [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md) | [현재 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_12_reflection.png) | 미게시 | 확보 | 2026-07-31 Debug/Release x64와 ground·blue sphere의 recursive reflection 전체 창 screenshot 확인 |
| Step13 Transparency | 없음 | `03_Raytracing_Step13_Transparency` | 미확인 | [과거 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | 없음 | 미게시 | 후보 | 문서 작성과 asset 검토 대기 |
| Step14 CubeEnvironment | 없음 | `03_Raytracing_Step14_CubeEnvironment` | 미확인 | [과거 확인](../../02_Verification/Part1_Chapter03/verification-index.md) | 없음 | 미게시 | 후보 | 문서 작성과 attribution 검토 대기 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
