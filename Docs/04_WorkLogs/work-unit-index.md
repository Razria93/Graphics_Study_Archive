# Work Unit Index

이 문서는 Graphics Study Archive 문서화 작업의 Work Unit 목록과 상태를 기록한다.

| Work Unit | 범위 | 주요 산출물 | 상태 | 비고 |
| --- | --- | --- | --- | --- |
| [WU-Part1](work-units/WU-Part1.md) | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_RayTracer` 기초 연결 | Example, RayTracing Topic, Verification, Demo | 진행 중 | `02_Bloom` pilot 마감. Chapter03 Step4~14 정규화·감사와 GitHub 게시 마감 완료 |
| [WU-Part2](work-units/WU-Part2.md) | `Part2_Chapter04`, `Part2_Chapter05-08` | Rasterization, DirectX11 Pipeline, Texturing | 진행 중 | Chapter04 게시 마감과 Chapter05–08 순차 정규화 완료, Chapter05–08 Publication·GitHub 게시 준비 |
| `WU-Part3` | `Part3_Chapter09`, `Part3_Chapter10-13` | Interaction, PBR/IBL, Shadows | 예정 | demo 우선순위 높음 |
| `WU-Part4` | `Part4_Chapter14-20` | Advanced graphics, compute/simulation 후보 | 예정 | 구조 확인 필요 |
| `WU-Publication` | public subset 후보 정리 | Publication, redaction, excluded material | 예정 | public repo 생성 전 수행 |
| [WU-StructureCleanup](work-units/WU-StructureCleanup.md) | 산출물 축 문서 구조 정리 | Index, Examples, Topics, Verification, Demos, WorkLogs, Publication, Policies, Tools, Legacy | 마감 | 브랜치 마감 검토 단계 |

## Work Unit과 PR 단위

Work Unit은 Part 또는 portfolio 흐름을 추적하는 운영 단위다. GitHub PR의 기본 단위는 Chapter 또는 Chapter 묶음이므로, 하나의 Work Unit이 여러 Chapter PR 후보를 가질 수 있다. Part 전체 PR은 예제가 적고 변경 범위가 작을 때만 예외로 사용한다.

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
- build/run/capture 확인을 시작하면 상태를 `검증 중`으로 바꾼다.
- 마감 조건을 만족하면 `마감`으로 바꾸고 `work-units/`의 관련 WorkLog를 갱신한다.
