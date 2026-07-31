# Part2_Chapter04 Demo Index

이 문서는 `Part2_Chapter04`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 순차 Demo 시작: Step1 Triangle
- Personal Extension: Step1A Triangle To Circle 독립 Demo 확보
- 순차 Demo 진행: Step4 Animation2D 정규화 완료
- 주요 demo 후보: rasterization, depth buffer, projection, lighting
- 비고: 개념 비교 screenshot 중심

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step1 Triangle 상세 Demo](01_Triangle.md) | [Step1 Triangle Example](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [Docs/_assets screenshot](../../_assets/captures/part2_chapter04_01_triangle.png) | 미게시 | 확보 | 최소 software rasterization 기반 |
| Personal Extension: Triangle To Circle | [Step1A 상세 Demo](01_TriangleToCircle.md) | [Step1A Example](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [3 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_3.png), [32 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png) | 미게시 | 확보 | 사용자 개인 응용, Step2와 분리 |
| Step2 Circle | [Step2 상세 Demo](02_Circle.md) | [Step2 Circle Example](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [전체 창 screenshot](../../_assets/captures/part2_chapter04_02_circle.png) | 미게시 | 확보 | 공유 CPU vertex/color 배열과 index 기반 triangle fan |
| Step3 Transformations2D | [Step3 상세 Demo](03_Transformations2D.md) | [Step3 Transformations2D Example](../../../Part2_Chapter04/04_Rasterization_Step3_Transformations2D/README.md) | [2D Transformations](../../01_Topics/Rasterization/Transformations2D.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [기본](../../_assets/captures/part2_chapter04_03_transformations2d_default.png), [조정](../../_assets/captures/part2_chapter04_03_transformations2d_composed.png) | 미게시 | 확보 | 5-segment 원본 mesh와 순차 CPU transform composition |
| Step4 Animation2D | [Step4 상세 Demo](04_Animation2D.md) | [Step4 Animation2D Example](../../../Part2_Chapter04/04_Rasterization_Step4_Animation2D/README.md) | [2D Animation And Hierarchical Orbit](../../01_Topics/AnimationAndPhysics/Animation2D.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [전체 창 screenshot](../../_assets/captures/part2_chapter04_04_animation2d.png) | 미게시 | 확보 | Sun·Earth·Moon 계층적 orbit, selected local video 검수 완료 |
| 대표 capture | 없음 | 미확인 | 미확인 | `Docs/02_Verification` | 없음 | 미게시 | 후보 | 대표 예제 선정 후 갱신 |
| video | [Step1A 상세 Demo](01_TriangleToCircle.md), [Step4 상세 Demo](04_Animation2D.md) | [Step1A Example](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md), [Step4 Example](../../../Part2_Chapter04/04_Rasterization_Step4_Animation2D/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md), [2D Animation](../../01_Topics/AnimationAndPhysics/Animation2D.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | selected local video | 미게시 | 확보 | Step1A segment 변화와 Step4 계층적 orbit 자동·사용자 검수 완료, remote 미게시 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
