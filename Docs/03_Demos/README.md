# Demos

이 폴더는 demo capture/video evidence 계획과 시연 우선순위의 정본 위치다. 실제 build/run 검증 상태는 `Docs/02_Verification`을 기준으로 하고, 검토된 asset 파일은 `Docs/_assets`에 둔다.

## 책임

- Part/Chapter별 최소 capture, 대표 capture, 선택 capture 후보를 관리한다.
- capture/video가 보여주는 Example과 Topic을 연결한다.
- 실제 파일 위치는 `Docs/_assets/captures`, `Docs/_assets/videos`, `Docs/_assets/diagrams`로 연결한다.
- public 공개 가능성 판단은 `Docs/05_Publication`으로 분리한다.
- raw capture 후보와 게시 전 검토 메모는 `local/`에 둔다.

## 문서 목록

| 문서 | 책임 |
| --- | --- |
| [Demo Priority](demo-priority.md) | Part별 demo 우선순위와 대표 후보 |
| [Capture Plan](capture-plan.md) | screenshot evidence 계획 |
| [Video Plan](video-plan.md) | video evidence 계획 |

## Part/Chapter Demo

| 범위 | 문서 위치 | 상태 |
| --- | --- | --- |
| Part1 Chapter01-02 | [Part1_Chapter01-02](Part1_Chapter01-02/demo-index.md) | 골격 작성 |
| Part1 Chapter03 | [Part1_Chapter03](Part1_Chapter03/demo-index.md) | 골격 작성 |
| Part2 Chapter04 | [Part2_Chapter04](Part2_Chapter04/demo-index.md) | 골격 작성 |
| Part2 Chapter05-08 | [Part2_Chapter05-08](Part2_Chapter05-08/demo-index.md) | 골격 작성 |
| Part3 Chapter09 | [Part3_Chapter09](Part3_Chapter09/demo-index.md) | 골격 작성 |
| Part3 Chapter10-13 | [Part3_Chapter10-13](Part3_Chapter10-13/demo-index.md) | 골격 작성 |
| Part4 Chapter14-20 | [Part4_Chapter14-20](Part4_Chapter14-20/demo-index.md) | 골격 작성 |
| Portfolio RayTracer | [Portfolio_RayTracer](Portfolio_RayTracer/demo-index.md) | 골격 작성 |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `미확인` | 아직 실행 또는 capture를 확인하지 않음 |
| `후보` | demo 후보로 선정했지만 evidence가 없음 |
| `확보` | 검토된 capture/video evidence가 있음 |
| `보류` | 구조, 권리, 품질 문제로 보류함 |
| `제외` | demo 후보에서 제외함 |
