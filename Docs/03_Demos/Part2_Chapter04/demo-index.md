# Part2_Chapter04 Demo Index

이 문서는 `Part2_Chapter04`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: rasterization, depth buffer, projection, lighting
- 비고: 개념 비교 screenshot 중심

## Demo 목록

| Demo 후보 | 연결 Example | 연결 Topic | Verification | Capture/Result | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step1 Triangle](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [Verification](../../02_Verification/Part2_Chapter04/verification-index.md) | [Triangle](../../_assets/captures/part2_chapter04_01_triangle.png) | 확보 | [상세 Demo](01_Triangle.md) · CPU software rasterization 기준선 |
| 대표 capture | [Step8 PerspectiveProjection](../../../Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/README.md) | [Perspective Projection](../../01_Topics/Rasterization/PerspectiveProjection.md) | [Verification](../../02_Verification/Part2_Chapter04/verification-index.md) | [Orthographic](../../_assets/captures/part2_chapter04_08_perspective_projection_orthographic.png), [Affine](../../_assets/captures/part2_chapter04_08_perspective_projection_affine.png), [Perspective-Correct](../../_assets/captures/part2_chapter04_08_perspective_projection_correct.png) | 확보 | [상세 Demo](08_PerspectiveProjection.md) · [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14) |
| video | [Step1A TriangleToCircle](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [Verification](../../02_Verification/Part2_Chapter04/verification-index.md) | [3 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_3.png), [32 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png) | 확보 | [상세 Demo](01_TriangleToCircle.md) · selected video를 [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14)에 게시함 |

## 상세 Demo 문서

- [Step1 Triangle](01_Triangle.md)
- [Step1A TriangleToCircle](01_TriangleToCircle.md)
- [Step2 Circle](02_Circle.md)
- [Step3 Transformations2D](03_Transformations2D.md)
- [Step4 Animation2D](04_Animation2D.md)
- [Step5 DepthBuffer](05_DepthBuffer.md)
- [Step6 ShadersConcept](06_ShadersConcept.md)
- [Step7 BackfaceCulling](07_BackfaceCulling.md)
- [Step8 PerspectiveProjection](08_PerspectiveProjection.md)
- [Step9 Shading](09_Shading.md)
- [Step10 Lights](10_Lights.md)

## 갱신 기준

- Step1을 최소 기준선, Step8을 Chapter 대표 Demo로 유지한다.
- Step1A는 사용자 확장과 video, Step4는 시간 변화, Step10은 기술 보조 Demo로 유지한다.
- selected video의 기술·시각 검수와 Demo Issue 게시 상태를 함께 기록한다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
