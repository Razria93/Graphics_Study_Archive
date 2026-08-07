# Part1_Chapter03 Demo Index

이 문서는 `Part1_Chapter03`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: ray tracing steps, reflection, transparency, cubemap
- 비고: step 비교 screenshot 중심

## Demo 목록

| Demo 후보 | 연결 Example | 연결 Topic | Verification | Capture/Result | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step4 DrawingSphere](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md) | [Ray](../../01_Topics/RayTracing/Ray.md), [Intersection](../../01_Topics/RayTracing/Intersection.md) | [Verification](../../02_Verification/Part1_Chapter03/verification-index.md) | [기본](../../_assets/captures/part1_chapter03_04_drawing-sphere.png), [조정](../../_assets/captures/part1_chapter03_04_drawing-sphere_parameter-adjusted.png) | 확보 | [상세 Demo](04_DrawingSphere.md) · CPU ray tracing 기준선 · [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12) |
| 대표 capture | [Step8 Shadow](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow/README.md), [Step13 Transparency](../../../Part1_Chapter03/03_Raytracing_Step13_Transparency/README.md) | [Shadow Ray](../../01_Topics/Shadows/ShadowRay.md), [Refraction And Transparency](../../01_Topics/RayTracing/RefractionAndTransparency.md) | [Verification](../../02_Verification/Part1_Chapter03/verification-index.md) | [Shadow](../../_assets/captures/part1_chapter03_08_shadow.png), [Transparency](../../_assets/captures/part1_chapter03_13_transparency.png) | 확보 | 상세 Demo [Step8](08_Shadow.md)·[Step13](13_Transparency.md) · [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12) |
| video | [Step8 Shadow](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow/README.md), [Step13 Transparency](../../../Part1_Chapter03/03_Raytracing_Step13_Transparency/README.md) | [Shadow Ray](../../01_Topics/Shadows/ShadowRay.md), [Refraction And Transparency](../../01_Topics/RayTracing/RefractionAndTransparency.md) | [Verification](../../02_Verification/Part1_Chapter03/verification-index.md) | 없음 | 제외 | tracked 정적 결과로 단계별 구현 차이를 판독할 수 있어 video를 사용하지 않음 |

## 상세 Demo 문서

- [Step4 DrawingSphere](04_DrawingSphere.md)
- [Step5 PhongShading](05_PhongShading.md)
- [Step6 PerspectiveView](06_PerspectiveView.md)
- [Step7 Triangle](07_Triangle.md)
- [Step8 Shadow](08_Shadow.md)
- [Step9 BarycentricCoordinates](09_BarycentricCoordinates.md)
- [Step10 Texturing](10_Texturing.md)
- [Step11 Supersampling](11_Supersampling.md)
- [Step12 Reflection](12_Reflection.md)
- [Step13 Transparency](13_Transparency.md)
- [Step14 CubeEnvironment](14_CubeEnvironment.md)

## 갱신 기준

- Step4를 최소 기준선, Step8과 Step13을 Chapter 대표 흐름으로 유지한다.
- Step10과 Step14는 선택 Demo로 유지한다.
- 정적 결과로 단계별 구현 차이를 판독할 수 있어 video는 제외한다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
