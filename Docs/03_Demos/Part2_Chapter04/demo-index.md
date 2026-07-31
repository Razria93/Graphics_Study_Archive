# Part2_Chapter04 Demo Index

이 문서는 `Part2_Chapter04`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 순차 Demo 시작: Step1 Triangle
- Personal Extension: Step1A Triangle To Circle 독립 Demo 확보
- 주요 demo 후보: rasterization, depth buffer, projection, lighting
- 비고: 개념 비교 screenshot 중심

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step1 Triangle 상세 Demo](01_Triangle.md) | [Step1 Triangle Example](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [Docs/_assets screenshot](../../_assets/captures/part2_chapter04_01_triangle.png) | 미게시 | 확보 | 최소 software rasterization 기반 |
| Personal Extension: Triangle To Circle | [Step1A 상세 Demo](01_TriangleToCircle.md) | [Step1A Example](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md) | [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md) | [현재 확인](../../02_Verification/Part2_Chapter04/verification-index.md) | [3 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_3.png), [32 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png) | 미게시 | 확보 | 사용자 개인 응용, Step2와 분리 |
| 대표 capture | 없음 | 미확인 | 미확인 | `Docs/02_Verification` | 없음 | 미게시 | 후보 | 대표 예제 선정 후 갱신 |
| video | 없음 | Step1A·Step4 후보 | 미확인 | `Docs/02_Verification` | 없음 | 미게시 | 후보 | Step1A 3→32 local 후보 검증, tracked/public 승격은 별도 판단 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
