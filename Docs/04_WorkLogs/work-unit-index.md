# Work Unit Index

이 문서는 Graphics Study Archive 문서화 작업의 Work Unit 목록과 상태를 기록한다.

| Work Unit | 범위 | 주요 산출물 | 상태 | 비고 |
| --- | --- | --- | --- | --- |
| `WU-Part1` | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_RayTracer` 기초 연결 | Example, RayTracing Topic, Verification, Demo | 진행 중 | `02_Bloom` pilot build/run 확인, capture/result 승격 보류 |
| `WU-Part2` | `Part2_Chapter04`, `Part2_Chapter05-08` | Rasterization, DirectX11 Pipeline, Texturing | 예정 | 예제 수가 많아 대표 예제 선정 필요 |
| `WU-Part3` | `Part3_Chapter09`, `Part3_Chapter10-13` | Interaction, PBR/IBL, Shadows | 예정 | demo 우선순위 높음 |
| `WU-Part4` | `Part4_Chapter14-20` | Advanced graphics, compute/simulation 후보 | 예정 | 구조 확인 필요 |
| `WU-Publication` | public subset 후보 정리 | Publication, redaction, excluded material | 예정 | public repo 생성 전 수행 |
| `WU-StructureCleanup` | 산출물 축 문서 구조 정리 | Index, Examples, Topics, Verification, Demos, WorkLogs, Publication, Policies, Tools, Legacy | 마감 | 브랜치 마감 검토 단계 |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `예정` | 아직 작업을 시작하지 않음 |
| `진행 중` | 코드/문서 확인 또는 정본 문서 작성 중 |
| `검증 중` | build/run/capture 확인 중 |
| `마감` | WorkLog와 Index 갱신이 끝남 |
| `보류` | 구조, 권리, 일정 문제로 보류함 |

## 갱신 기준

- Work Unit을 시작하면 상태를 `진행 중`으로 바꾼다.
- build/run/capture 확인을 시작하면 `검증 중`으로 바꾼다.
- 마감 조건을 만족하면 `마감`으로 바꾸고 관련 WorkLog를 갱신한다.
