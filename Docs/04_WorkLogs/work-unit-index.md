# Work Unit Index

이 문서는 Graphics Study Archive 문서화 작업의 Work Unit 목록과 상태를 기록한다.

| Work Unit | 범위 | 주요 산출물 | 상태 | 비고 |
| --- | --- | --- | --- | --- |
| [WU-Part1](work-units/WU-Part1.md) | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_GraphicsLab/Rendering/RayTracing` 기초 연결 | Example, RayTracing Topic, Verification, Demo | 진행 중 | `02_Bloom`과 Chapter03 마감. GraphicsLab scaffold 완료, WU-A0 전환기 closeout 후 WU-R1 reconstruction 예정 |
| [WU-GraphicsLab-Architecture](work-units/WU-GraphicsLab-Architecture.md) | Phase S reconstruction 전략, Phase A original evidence, WU-A0 architecture | Decision, Review, Architecture, Part1 roadmap | 마감 | PR #41 구현 merge와 전환기 예외 PR #42 finalization 완료. PR #42 merge 시 기본 branch에 마감 반영 |
| [WU-Part2](work-units/WU-Part2.md) | `Part2_Chapter04`, `Part2_Chapter05-08` | Rasterization, DirectX11 Pipeline, Texturing | 마감 | Chapter04와 Chapter05–08 정규화·재검증, Demo Issue와 PR merge 완료 |
| [WU-Part3](work-units/WU-Part3.md) | `Part3_Chapter09`, `Part3_Chapter10-13` | Interaction, PBR/IBL, Shadows | 마감 | Chapter09와 Chapter10→13 정규화, Demo Issue 게시, Progress comment와 PR merge 완료 |
| [WU-Part4](work-units/WU-Part4.md) | `Part4_Chapter14-20` | Advanced graphics, compute/simulation, animation, foliage, physics, gameplay | 마감 | Chapter14부터 Chapter20까지 source docs, Demo와 GitHub body closeout, PR #38 merge 완료. Release 재검증과 selected video는 후속 작업 |
| `WU-Publication` | public subset 후보 정리 | Publication, redaction, excluded material | 예정 | public repo 생성 전 수행 |
| [WU-StructureCleanup](work-units/WU-StructureCleanup.md) | 산출물 축 문서 구조 정리 | Index, Examples, Topics, Verification, Demos, WorkLogs, Publication, Policies, Tools, Legacy | 마감 | 브랜치 마감 검토 단계 |

## Work Unit과 PR 단위

Work Unit은 Part 또는 portfolio 흐름을 추적하는 운영 단위다. GitHub PR의 기본 단위는 Chapter 또는 Chapter 묶음이므로, 하나의 Work Unit이 여러 Chapter PR 후보를 가질 수 있다. Part 전체 PR은 예제가 적고 변경 범위가 작을 때만 예외로 사용한다.

## 상태값

| 상태 | 의미 |
| --- | --- |
| `예정` | 아직 작업을 시작하지 않음 |
| `진행 중` | 코드·문서 작업, 작업 PR review·finalization 또는 merge가 남아 있음 |
| `검증 중` | build/run/capture를 실제로 확인하고 있음 |
| `마감` | finalization commit을 포함한 PR이 merge되어 최종 기록이 기본 branch에 반영됨 |
| `보류` | 구조, 권리, 일정 문제로 보류함 |

## 갱신 기준

- Work Unit을 시작하면 상태를 `진행 중`으로 바꾼다.
- build/run/capture 확인을 시작하면 상태를 `검증 중`으로 바꾼다.
- build/run/capture 확인을 마치고 작업 PR review 또는 finalization이 남아 있으면 `진행 중`으로 되돌린다.
- 작업 PR review 완료와 finalization 진행 승인 후 같은 branch의 finalization commit에서 WorkLog, Index와 `마감` 전환을 확정한다.
- Finalization commit의 validator와 review 상태를 다시 확인하고 최신 PR HEAD에 대한 merge 실행 승인을 다시 받은 뒤 merge한다.
- Finalization commit을 포함한 PR이 기본 branch에 merge되면 `마감` 상태가 정본에 반영된다.
- 여러 작업 PR 종합이나 post-merge 정리가 필요한 경우에만 별도 closeout PR을 사용한다.
- 상세 조건은 [Work Unit Workflow Policy](../06_Policies/work-unit-workflow-policy.md)를 따른다.
