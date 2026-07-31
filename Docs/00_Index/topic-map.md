# Topic Map

이 문서는 graphics Topic 문서의 정본 위치를 안내한다. Topic별 최신 작성 상태와 우선순위는 각 그룹의 `topic-index.md`에 둔다.

## Topic 그룹 위치

| Topic 그룹 | 위치 | 주 연결 후보 |
| --- | --- | --- |
| Ray Tracing | `Docs/01_Topics/RayTracing` | `Part1_Chapter03`, `Portfolio_RayTracer` |
| Rasterization | `Docs/01_Topics/Rasterization` | `Part2_Chapter04` |
| DirectX11 Pipeline | `Docs/01_Topics/DirectX11Pipeline` | `Part1_Chapter01-02`, `Part2_Chapter05-08` |
| Texturing And Mapping | `Docs/01_Topics/TexturingAndMapping` | `Part2_Chapter05-08`, `Part3_Chapter10-13` |
| Lighting And Shading | `Docs/01_Topics/LightingAndShading` | `Part1_Chapter03`, `Part2_Chapter05-08`, `Part3_Chapter10-13` |
| PBR And IBL | `Docs/01_Topics/PBRAndIBL` | `Part2_Chapter05-08`, `Part3_Chapter10-13` |
| Shadows | `Docs/01_Topics/Shadows` | `Part1_Chapter03`, `Part3_Chapter10-13` |
| Compute And Simulation | `Docs/01_Topics/ComputeAndSimulation` | `Part4_Chapter14-20` |
| Animation And Physics | `Docs/01_Topics/AnimationAndPhysics` | `Part2_Chapter04`, `Part3_Chapter09`, `Part4_Chapter14-20` |

## Topic 작성 깊이

Topic의 P0/P1/P2 판단은 각 그룹의 `topic-index.md`에서 관리한다. 이 map에는 등급별 세부 상태를 복제하지 않는다.

| 등급 | 기준 | 산출물 |
| --- | --- | --- |
| P0 | 포트폴리오 README와 면접 설명에 직접 사용 | Topic 문서, 대표 capture/result, 예제 링크 |
| P1 | 대표 예제를 이해하는 데 필요 | Topic 문서 또는 짧은 section |
| P2 | 보조 개념 또는 나중에 정리할 대상 | topic-index 후보 또는 WorkLog follow-up |

## 작성 기준

- Topic 문서는 강의 원문 구조를 복제하지 않는다.
- 예제별 구현 설명은 대상 코드 폴더 README에 둔다.
- Topic 문서에는 개념, pipeline 위치, 관련 예제, 확인한 코드 위치, 시연 포인트를 둔다.
- build/run/capture 결과는 `Docs/02_Verification`에 둔다.
