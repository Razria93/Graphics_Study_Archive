# Topic Map

이 문서는 `Docs/02_Topics`에 둘 graphics concept 문서의 분류와 우선순위를 정의한다.

## Topic 분류

| Topic 그룹 | 예시 주제 | 연결 후보 |
| --- | --- | --- |
| Ray Tracing | ray, intersection, normal, shading, reflection | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_RayTracer` |
| Rasterization | vertex processing, depth buffer, viewport, raster step | `Part2_Chapter04` |
| DirectX11 Pipeline | device/context, buffer, shader stage, input layout | `Part2_Chapter04`, `Part2_Chapter05-08` |
| Texturing And Mapping | texture sampling, uv, normal map, cube map | `Part2_Chapter05-08`, `Part3_Chapter10-13` |
| Lighting And Shading | Blinn-Phong, material, light type, BRDF 기초 | `Part2_Chapter05-08`, `Part3_Chapter10-13` |
| Shadows | shadow mapping, depth comparison, bias | `Part3_Chapter10-13` |
| PBR And IBL | metallic/roughness, environment map, IBL | `Part3_Chapter10-13` |
| Compute And Simulation | compute shader, particle, fluid/simulation 후보 | `Part4_Chapter14-20` |
| Animation And Physics | transform, time step, simulation update | `Part4_Chapter14-20` |

## 작성 깊이

| 등급 | 기준 | 산출물 |
| --- | --- | --- |
| P0 | 포트폴리오 README와 면접 설명에 직접 사용 | Topic 문서, 대표 캡처, 예제 링크 |
| P1 | 대표 예제를 이해하는 데 필요 | Topic 문서 또는 짧은 section |
| P2 | 보조 개념 또는 후순위 정리 대상 | TODO 또는 WorkLog follow-up |

## 작성 기준

- Topic 문서는 강의 원문 구조를 복제하지 않는다.
- 예제별 구현 설명은 `Docs/01_Examples`에 둔다.
- Topic 문서에는 개념, pipeline 위치, 관련 예제, 확인한 코드 위치, 시연 포인트를 둔다.
