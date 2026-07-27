# Demos

이 폴더는 demo capture/result 계획과 시연 우선순위의 source docs다. 실제 build/run 검증 상태는 `Docs/02_Verification`을 기준으로 하고, 검토된 asset 파일은 `Docs/_assets`에 둔다.

## 책임

- Part/Chapter별 최소 capture, 대표 capture, 선택 capture 후보를 관리한다.
- capture/result가 보여주는 Example과 Topic을 연결한다.
- 실제 파일 위치는 `Docs/_assets/captures`, `Docs/_assets/videos`, `Docs/_assets/diagrams`로 연결한다.
- public 공개 가능성 판단은 `Docs/05_Publication`으로 분리한다.
- raw capture 후보와 게시 전 검토 메모는 `local/`에 둔다.
- GitHub 게시 body는 이 폴더에서 직접 작성하지 않고 `Docs/07_GitHub`에서 source docs를 요약/재구성한다.

## 최소 기준

- graphics 문서화에서는 Chapter 또는 Chapter 묶음 demo-index마다 screenshot 최소 1개를 필수로 둔다.
- screenshot 추가본은 해당 Chapter 작업을 설명하는 데 필수적인 장면만 선별한다.
- video가 필요하다고 판단한 경우 사용자에게 요청 조건을 제시한다.
- 사용자가 demo 구성을 요청한 경우 해당 범위 demo를 구성한다.

## 문서 목록

| 문서 | 책임 |
| --- | --- |
| [Demo Priority](demo-priority.md) | Part별 demo 우선순위와 대표 후보 |
| [Capture Plan](capture-plan.md) | screenshot 계획 |
| [Video Plan](video-plan.md) | video 계획 |

## Part/Chapter Demo

| 범위 | 문서 위치 | 문서 상태 |
| --- | --- | --- |
| Part1 Chapter01-02 | [Part1_Chapter01-02](Part1_Chapter01-02/demo-index.md) | 골격 작성 |
| Part1 Chapter03 | [Part1_Chapter03](Part1_Chapter03/demo-index.md) | 골격 작성 |
| Part2 Chapter04 | [Part2_Chapter04](Part2_Chapter04/demo-index.md) | 골격 작성 |
| Part2 Chapter05-08 | [Part2_Chapter05-08](Part2_Chapter05-08/demo-index.md) | 골격 작성 |
| Part3 Chapter09 | [Part3_Chapter09](Part3_Chapter09/demo-index.md) | 골격 작성 |
| Part3 Chapter10-13 | [Part3_Chapter10-13](Part3_Chapter10-13/demo-index.md) | 골격 작성 |
| Part4 Chapter14-20 | [Part4_Chapter14-20](Part4_Chapter14-20/demo-index.md) | 골격 작성 |
| Portfolio RayTracer | [Portfolio_RayTracer](Portfolio_RayTracer/demo-index.md) | 골격 작성 |

## 문서 상태값

Part/Chapter 표의 `문서 상태`는 capture/result 상태가 아니라 문서 골격의 작성 상태를 뜻한다.

| 상태 | 의미 |
| --- | --- |
| `골격 작성` | 기본 문서만 있으며 실제 demo 정리는 아직 부족함 |
| `작성 중` | 대표 예제와 capture/result 연결을 정리하는 중 |
| `작성 완료` | 현재 범위의 demo 설명과 연결 문서가 정리됨 |
| `후속 필요` | 추가 검증, capture/result, public 판단이 남음 |

## Capture/Result 상태값

| 상태 | 의미 |
| --- | --- |
| `미확인` | 아직 실행 또는 capture를 확인하지 않음 |
| `후보` | demo 후보로 선정했지만 capture/result가 아직 없음 |
| `확보` | 검토된 capture/result가 있음 |
| `보류` | 구조, 권리, 품질 문제로 보류함 |
| `제외` | demo 후보에서 제외함 |
