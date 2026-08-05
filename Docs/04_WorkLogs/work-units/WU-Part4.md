# WU-Part4

## 범위

- `Part4_Chapter14-20`

## 현재 상태

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| Source/import | 반영 완료 | `SRC-P4-C14-20`으로 source provenance를 추적한다. |
| Branch | 진행 중 | `docs/part4-chapter14-20-workflow`에서 baseline 문서 축 정규화를 시작한다. |
| Build/run | 과거 확인 | Ex1401~Ex2001 Debug/Release 성공 기록을 유지하되 현재 재검증 필요 상태로 둔다. |
| Capture | 미확인 | 이번 baseline 정규화 범위에서는 capture를 수행하지 않는다. |
| Demo | 후보 정리 중 | stale 후보를 제거하고 실제 Ex 기반 후보로 재정렬한다. |
| Publication | 검토 필요 | public 후보 확정이 아니라 asset/public risk 검토 축으로만 기록한다. |
| GitHub | 미게시 | Issue, PR, comment remote 게시를 이번 범위에 포함하지 않는다. |

## 시작 결정

- Part4는 예제별 solution이 아니라 `Examples.sln` 단일 project와 command argument 기반 sample 선택 구조로 유지한다.
- 첫 작업은 Chapter14 compute slice나 build/run 재검증이 아니라 baseline 문서 축 정규화로 제한한다.
- 이번 범위에서는 build/run/capture를 수행하지 않고, 과거 확인과 현재 재검증 필요 상태를 분리한다.
- Demo Issue, Progress comment, PR remote 게시는 후속 승인 범위로 둔다.

## 정본 연결

| 책임 | 정본 |
| --- | --- |
| Chapter와 실행 구조 | [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md) |
| build/run/capture 사실 | [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md) |
| Demo 후보와 capture/result 상태 | [Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md) |
| compute/simulation Topic 후보 | [Compute And Simulation Topic Index](../../01_Topics/ComputeAndSimulation/topic-index.md) |
| public 후보와 risk 검토 | [Publication Candidate List](../../05_Publication/candidate-list.md) |
| source provenance | [Source Registry](../../99_Legacy/source-registry.md) |

## 다음 작업

1. baseline 정규화 변경을 검증하고 커밋한다.
2. 후속 목표에서 Chapter14 compute shader slice 또는 build/run revalidation plan 중 하나를 선택한다.
3. 실제 build/run/capture를 시작할 때 Work Unit 상태를 `검증 중`으로 전환한다.