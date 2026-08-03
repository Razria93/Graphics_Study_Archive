# Demo Priority

이 문서는 Graphics Study Archive의 demo 우선순위를 정리한다. 실제 capture/result 확보 전까지 상태는 `후보` 또는 `미확인`으로 둔다.

| 범위 | 최소 demo | 대표 demo 후보 | 선택 demo 후보 | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- |
| Part1_Chapter01-02 | Bloom input/result | Bloom 결과 | 없음 | 확보 | build/run과 tracked visual 확인 완료 |
| Part1_Chapter03 | Step4 DrawingSphere | Step8 Shadow, Step13 Transparency | Step10 Texturing, Step14 CubeEnvironment | 확보 | Step4~14 독립 상세 Demo와 tracked screenshot 확인 완료 |
| Part2_Chapter04 | Step1 Triangle | Step8 PerspectiveProjection | Step1A Personal Extension, Step4 Animation2D, Step10 Lights | 확보 | Step1–10 순차 Demo와 capture 확보. Step8은 Chapter 대표, Step10은 기술 보조, Step1A는 사용자 확장, Step4는 시간 변화 Demo로 유지 |
| Part2_Chapter05-08 | Chapter05 Step2·4 affine 비교 | Chapter06 Step2·6·8 pipeline·lighting·resize, Chapter07 Step1·5·8 modeling·mapping | Chapter06 Step9, Chapter07 Step2·6·7 | 확보 | Chapter05·06·07 대표 구성을 확정한다. Chapter08은 asset 권리 근거 확인 전 공개 Demo Issue를 보류한다. |
| Part3_Chapter09 | Step1 FirstPersonView | Step2 MousePicking, Step5 VirtualTrackball | Step6 MouseDragMove | 검토 필요 | Step1~6 screenshot 확보, interaction video는 자동 조작 안정화 후 선택 |
| Part3_Chapter10-13 | normal mapping 또는 PBR | shadow mapping, PCF/PCSS | HDR pipeline, halo | 후보 | 시각 임팩트 우선순위 높음 |
| Part4_Chapter14-20 | 실행 가능한 대표 sample | compute/simulation 후보 | advanced sample 후보 | 미확인 | 구조 확인 필요 |
| Portfolio_RayTracer | 대표 ray tracing 결과 | portfolio hero capture | step 비교 영상 | 미확인 | solution 확인 필요 |

## 우선순위 기준

- P0: README, PR, 면접 설명에 직접 사용할 대표 demo
- P1: 예제 이해를 돕는 보조 demo
- P2: 시간이 남을 때 정리할 선택 demo

## 갱신 기준

- build/run 상태가 `성공` 또는 `부분 성공`일 때 capture 후보를 `확보`로 올린다.
- capture 품질, 권리, 민감 정보 검토 전에는 public 후보로 두지 않는다.
