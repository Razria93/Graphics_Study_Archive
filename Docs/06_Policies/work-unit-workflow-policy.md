# Work Unit Workflow Policy

이 문서는 Graphics Study Archive에서 Work Unit의 선택, 상태, review, pre-merge finalization과 종료 lifecycle을 정의한다. 작업 유형별 산출물, 작업 순서, 검증과 종료 조건은 [Work Profile Policy](work-profile-policy.md)를 정본으로 사용한다.

## 책임 경계

| 책임 | 정본 |
| --- | --- |
| Graphics와 Maintenance 분류, 산출물과 검증 | `work-profile-policy.md` |
| Work Unit 상태, finalization과 마감 | 이 문서 |
| GitHub 승인, review comment, merge와 Progress remote 실행 | `github-workflow-policy.md` |
| 산출물별 정본 위치와 README 계층 | `canonical-docs-policy.md` |
| Graphics current/raw/reference 조사와 문서 작성 | `docs-authoring-flow-policy.md` |
| Template과 validator 실행 | `Docs/98_Tools` |

같은 규칙을 여러 정책에 복제하지 않는다. 이 문서는 Graphics 산출물 목록이나 Maintenance 검증 항목을 다시 정의하지 않는다.

## Work Unit 시작

Work Unit을 시작할 때 [Work Contract](../98_Tools/templates/work-contract.md)를 작성하거나 같은 항목을 계획에 명시한다.

- `Work type`: `Graphics` 또는 `Maintenance`
- `Work Unit`: 연결된 Work Unit
- `Closes Work Unit`: `Yes` 또는 `No`
- `Progress impact`: `Required`, `Not required` 또는 `Pending`
- 목표, 범위와 제외 범위
- 선택한 profile의 필수 산출물과 판정 계획
- 검증과 종료 조건

Graphics Work는 current code, raw/reference와 기존 정본을 조사하고 구현 핵심 구조, Topic, Verification과 Demo 축을 판정한다. Maintenance Work는 현재 policy·문서·도구의 문제 원인과 책임 경계를 조사한다. 세부 수행 순서는 Work Profile Policy를 따른다.

## 상태값

| 상태 | 의미 |
| --- | --- |
| `예정` | 아직 작업을 시작하지 않음 |
| `진행 중` | 구현·문서 작업 또는 review가 진행 중임 |
| `검증 중` | build, run 또는 capture를 실제로 확인하고 있음 |
| `마감` | finalization tree가 기본 branch에 merge됨 |
| `보류` | 구조, 권리, 일정 또는 외부 blocker로 진행을 보류함 |

- Work Unit을 시작하면 `진행 중`으로 둔다.
- `검증 중`은 build/run/capture를 실제로 확인하는 기간에만 사용한다.
- 검증이 끝나고 review가 남아 있으면 `진행 중`으로 되돌린다.
- 작업 branch의 pre-merge finalization에서는 merge 후 관점의 `마감` 상태를 작성할 수 있다.
- 작업 branch의 `마감`은 예정된 final state이며 해당 tree가 기본 branch에 merge될 때 정본으로 효력을 가진다.

## Work Unit 진행 흐름

| 단계 | 책임 | 기준 |
| --- | --- | --- |
| 0. Contract | Work type, Work Unit, 종료 여부, Progress 영향, 산출물과 검증 확정 | Work Profile Policy |
| 1. Profile 작업 | 선택한 profile의 조사, 구현·수정, 산출물 작성과 검증 | Work Profile Policy와 분야별 policy |
| 2. 사용자 검수 | 산출물 판정, 검증, 제한과 remote 제외 범위 확인 | Work Contract |
| 3. Review | Review 전 검사, Ready 전환, feedback과 comment 처리 | GitHub Workflow Policy |
| 4. Finalization | 같은 branch에서 마감 snapshot과 필요한 Progress payload 완성 | 이 문서 |
| 5. Merge gate | 고정 HEAD와 remote blocker만 read-only 확인 | GitHub Workflow Policy |
| 6. Terminal execution | 일반 merge와 조건부 Progress 동기화 | GitHub Workflow Policy |
| 7. Handoff | 종료 결과와 다음 Work Unit 제안 | WorkLog와 final report |

`Closes Work Unit: No`인 작업은 profile 산출물과 검증을 완료해 merge하되 Work Unit 상태를 `마감`으로 바꾸지 않는다. `Closes Work Unit: Yes`인 작업만 finalization에서 Work Unit 마감 산출물을 완성한다.

## 구현 또는 수정 완료 후보

작업 branch는 다음 조건을 만족할 때 사용자 1차 검수와 review 후보가 된다. 이 단계만으로 Work Unit을 `마감`으로 확정하지 않는다.

- Work Contract의 목표와 범위를 충족했다.
- 선택한 profile의 모든 산출물을 `Created`, `Updated`, `Linked`, `N/A` 중 하나로 판정했다.
- `N/A`와 직접 확인하지 못한 결과에 이유가 있다.
- Profile 검증과 변경 영향 검증을 수행했다.
- WorkLog, PR body와 Index 같은 조건부 산출물의 필요 여부를 판정했다.
- `Progress impact: Pending`이면 pre-merge finalization 전 확정할 판단 근거가 있다.
- README 갱신 기준을 확인하고 필요한 README만 갱신했다.
- 사용자 검수 요청과 commit readiness 보고를 준비했다.

Graphics Work의 current/raw/reference 비교, Topic, Verification, Demo와 Publication 세부 기준은 Work Profile Policy와 분야별 policy를 따른다. Maintenance Work에 graphics 산출물을 강제하지 않는다.

## Review와 pre-merge finalization

```text
Review 전 최종 검사
-> Ready for Review
-> Review 대응 및 comment 처리
-> 같은 작업 branch의 pre-merge finalization
-> merge 전 read-only 최종 검사
-> 일반 merge와 조건부 Progress 동기화
```

Pre-merge finalization은 review가 끝난 같은 작업 branch에서 수행한다. Finalization commit에는 새 기능, 새 설계 범위와 미검증 결과를 섞지 않는다.

`Closes Work Unit: Yes`이면 다음을 merge 후 기본 branch에서 읽힐 관점으로 완성한다.

- WorkLog 최종 snapshot과 review·검증 요약
- `work-unit-index.md`의 최종 상태와 비고
- `work-unit-github-index.md`의 안정적인 PR·Issue와 Progress payload 연결
- 남은 제한과 다음 Work Unit
- `Progress impact: Required`인 누적·완료 payload
- PR body의 최종 review snapshot

Canonical 문서에는 `Draft`, `Ready 대기`, `merge 시 반영`과 `merge 승인 대기` 같은 현재 PR 과도 상태를 기록하지 않는다. Finalization tree가 기본 branch에 merge되면 작성해 둔 `마감` 상태가 정본이 된다.

Finalization에서 전체 validator, `git diff --check`, lifecycle 정합성과 필요한 Browser 표본을 한 번 확인한다. 이후 HEAD가 바뀌면 기존 finalization 검증은 무효다. 기능·설계 변경이나 새 actionable review는 Review 단계로 돌아가고, 마감 문서와 payload 변경은 Finalization을 다시 수행한다.

## Merge 전 검사와 terminal execution

Merge 전 검사는 validator를 반복하는 단계가 아니다. 다음 read-only 상태만 확인한다.

- local HEAD, tracking ref, remote branch와 PR head가 같은 finalization SHA임
- clean worktree와 remote body 일치
- Actions 성공과 mergeable 상태
- `CHANGES_REQUESTED`, 새 actionable review와 미해결 thread 부재

하나의 terminal 승인에서 특정 PR HEAD의 일반 merge와 merge 성공을 조건으로 한 Progress 동기화를 함께 승인할 수 있다. Merge가 실패하면 Progress 작업을 실행하지 않는다. Progress 작업만 실패하면 tracked 수정이나 새 PR을 만들지 않고 같은 remote 작업만 재시도한다.

## Work Unit 마감 기준

`Closes Work Unit: Yes`인 작업은 다음 조건을 모두 만족해야 종료한다.

- 선택한 Work Profile의 산출물과 검증 조건을 충족했다.
- Review feedback과 comment 처리가 완료됐다.
- 같은 branch의 finalization commit에 마감 snapshot, 안정적인 GitHub 연결, 제한, 다음 Work Unit과 필요한 Progress payload가 있다.
- Finalization HEAD의 validator와 `git diff --check`가 통과했다.
- Merge 전 read-only 검사에서 같은 HEAD, Actions 성공, review clear와 mergeable 상태를 확인했다.
- 일반 merge와 `Progress impact: Required`인 Progress 원격 동기화를 완료했다.
- Remote body와 사용한 tracked payload가 일치한다.
- Merge 후 tracked 수정, 별도 closeout과 게시 결과 역동기화가 남아 있지 않다.

Progress 동기화 결과는 GitHub remote에서 확인하고 tracked 문서에 다시 기록하지 않는다.

## 예외 closeout

별도 closeout branch와 PR은 다음 조건 중 하나를 만족할 때만 사용한다.

- 하나의 Work Unit이 여러 작업 PR로 구성되어 결과 종합 자체가 review 대상이다.
- Finalization 누락으로 기본 branch의 정본이 실제로 거짓이고 다음 작업을 막는다.

예외 closeout은 `Maintenance Work`, `Closes Work Unit: Yes`로 분류한다. 새로운 기능, refactoring과 새 graphics 결과를 포함하지 않으며 terminal maintenance PR 한 번으로 끝낸다. Merge SHA, posted 상태, comment ID·URL과 URL 치환은 closeout 사유가 아니다.
