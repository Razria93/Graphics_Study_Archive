# Topic Map

이 문서는 `Docs/02_Topics`에 둘 graphics concept 문서의 분류와 우선순위를 정의한다.

## Topic 분류

| Topic 그룹 | 예시 주제 | 연결 후보 | 상태 |
| --- | --- | --- | --- |
| Ray Tracing | ray, intersection, normal, shading, reflection | `Part1_Chapter03`, `Portfolio_RayTracer` | 골격 작성 |
| Rasterization | vertex processing, depth buffer, viewport, raster step | `Part2_Chapter04` | 골격 작성 |
| DirectX11 Pipeline | device/context, buffer, shader stage, input layout | `Part1_Chapter01-02`, `Part2_Chapter05-08` | 골격 작성 |
| Texturing And Mapping | texture sampling, UV, normal map, cubemap | `Part2_Chapter05-08`, `Part3_Chapter10-13` | 골격 작성 |
| Lighting And Shading | Blinn-Phong, material, light type, BRDF 기초 | `Part2_Chapter05-08`, `Part3_Chapter10-13` | 골격 작성 |
| PBR And IBL | metallic/roughness, environment map, IBL | `Part2_Chapter05-08`, `Part3_Chapter10-13` | 골격 작성 |
| Shadows | shadow mapping, depth comparison, bias | `Part1_Chapter03`, `Part3_Chapter10-13` | 골격 작성 |
| Compute And Simulation | compute shader, particle, fluid/simulation 후보 | `Part4_Chapter14-20` | 골격 작성 |
| Animation And Physics | transform, time step, simulation update | `Part2_Chapter04`, `Part3_Chapter09`, `Part4_Chapter14-20` | 골격 작성 |

## 작성 깊이

| 등급 | 기준 | 산출물 |
| --- | --- | --- |
| P0 | 포트폴리오 README와 면접 설명에 직접 사용 | Topic 문서, 대표 캡처, 예제 링크 |
| P1 | 대표 예제를 이해하는 데 필요 | Topic 문서 또는 짧은 section |
| P2 | 보조 개념 또는 후순위 정리 대상 | topic-index 후보 또는 WorkLog follow-up |

## 작성 기준

- Topic 문서는 강의 원문 구조를 복제하지 않는다.
- 예제별 구현 설명은 `Docs/01_Examples`에 둔다.
- Topic 문서에는 개념, pipeline 위치, 관련 예제, 확인한 코드 위치, 시연 포인트를 둔다.
- 코드 확인 전 항목은 `미확인`으로 둔다.
