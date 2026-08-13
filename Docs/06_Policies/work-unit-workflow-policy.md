# Work Unit Workflow Policy

이 문서는 Graphics Study Archive 작업의 공통 lifecycle과 Work Unit 상태를 정의하는 단일 정본이다. Lifecycle 단계의 순서, 진입·완료 조건, 상태 전환, 실패 시 복귀와 종료 조건은 이 문서만 정의한다. 다른 정책과 실행 문서는 이 lifecycle을 재정의하지 않고 필요한 단계에서 이 문서를 참조한다.

작업 유형별 산출물, profile 내부 작업 순서와 검증 후보 조건은 [Work Profile Policy](work-profile-policy.md)를 정본으로 사용한다.

## 책임 경계

| 책임 | 정본 |
| --- | --- |
| Graphics와 Maintenance 분류, 산출물, profile 내부 작업과 검증 | `work-profile-policy.md` |
| 공통 lifecycle, Work Unit 상태, finalization과 종료 | 이 문서 |
| GitHub 승인, review comment, merge와 Progress remote 실행 | `github-workflow-policy.md` |
| 산출물별 정본 위치와 README 계층 | `canonical-docs-policy.md` |
| Graphics current/raw/reference 조사와 문서 작성 | `docs-authoring-flow-policy.md` |
| Template과 validator 실행 | `Docs/98_Tools` |

같은 규칙을 여러 정책에 복제하지 않는다. 이 문서는 Graphics 산출물 목록이나 Maintenance 검증 항목을 다시 정의하지 않으며, 다른 문서는 이 문서의 단계 순서와 전환 규칙을 요약해서 다시 쓰지 않는다.

## Work Unit 시작

Work Unit을 시작할 때 [Work Contract](../98_Tools/templates/work-contract.md)를 작성하거나 같은 항목을 계획에 명시한다.

- `Work type`: `Graphics` 또는 `Maintenance`
- `Work Unit`: 연결된 Work Unit 또는 `없음`
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

## 공통 lifecycle

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

## 단계 진입과 완료 조건

| 단계 | 진입 조건 | 완료 조건 |
| --- | --- | --- |
| 0. Contract | 작업 요청과 현재 repository 상태를 확인함 | Work type, Work Unit, 종료 여부, Progress 영향, 범위, 산출물과 검증을 확정함 |
| 1. Profile 작업 | Contract가 확정됨 | 선택한 profile의 산출물과 검증을 완료 후보로 판정함 |
| 2. 사용자 검수 | Profile 완료 후보와 제한을 보고할 수 있음 | 사용자가 산출물과 다음 remote 제외 범위를 확인함 |
| 3. Review | 사용자 검수를 완료함 | Review 전 검사, Ready 전환, actionable feedback, 답글과 resolve를 완료함 |
| 4. Finalization | Review가 끝나고 `Progress impact`를 확정한 뒤 finalization 진행 승인을 받음 | 같은 branch에서 마감 snapshot, 제한, 다음 작업과 필요한 payload를 검증함 |
| 5. Merge gate | Finalization HEAD가 고정됨 | 동일 HEAD, clean/sync, Actions, review와 mergeable 상태를 read-only로 확인함 |
| 6. Terminal execution | 특정 HEAD와 remote 대상에 terminal 승인을 받음 | 일반 merge와 필요한 remote 동기화를 완료하고 body 일치를 확인함 |
| 7. Handoff | Terminal execution 결과를 확인함 | 종료 상태, 남은 제한과 다음 작업을 보고함 |

## 실패와 변경 시 복귀

| 발생 조건 | 복귀 단계 |
| --- | --- |
| Contract의 목표, 범위 또는 산출물 판정 변경 | 0. Contract |
| 구현·문서·검증 결과의 실질 변경 | 1. Profile 작업 |
| 사용자 검수에서 산출물 보완 요청 | 1. Profile 작업 |
| 새 actionable review 또는 `CHANGES_REQUESTED` | 3. Review |
| Finalization 문서나 Progress payload 변경 | 4. Finalization |
| Finalization 이후 HEAD 변경 | 변경 성격에 따라 1. Profile 작업, 3. Review 또는 4. Finalization |
| Merge gate의 HEAD·Actions·review·mergeable 불일치 | 원인에 따라 3. Review 또는 4. Finalization |
| Merge 실패 | 5. Merge gate |
| Merge 성공 후 remote 동기화만 실패 | 6. Terminal execution에서 실패한 remote 작업만 재시도 |

복귀한 단계 이후의 검증과 승인은 이전 결과를 재사용하지 않는다. 단, Merge gate에서 HEAD가 변하지 않았고 remote 상태만 다시 확인하는 경우에는 고정된 finalization 검증을 재사용한다.

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

공통 lifecycle의 3. Review부터 6. Terminal execution까지를 적용한다. 단계 순서와 진입·완료 조건은 위의 공통 lifecycle 표를 기준으로 한다.

Pre-merge finalization은 review가 끝난 같은 작업 branch에서 수행한다. Finalization commit에는 새 기능, 새 설계 범위와 미검증 결과를 섞지 않는다.

`Closes Work Unit: Yes`이면 다음을 merge 후 기본 branch에서 읽힐 관점으로 완성한다.

- WorkLog 최종 snapshot과 review·검증 요약
- `work-unit-index.md`의 최종 상태와 비고
- `work-unit-github-index.md`의 안정적인 PR·Issue와 Progress payload 연결
- 남은 제한과 다음 Work Unit
- `Progress impact: Required`인 누적·완료 payload
- PR body의 최종 review snapshot

Canonical 문서에는 `Draft`, `Ready 대기`, `merge 시 반영`과 `merge 승인 대기` 같은 현재 PR 과도 상태를 기록하지 않는다. Finalization tree가 기본 branch에 merge되면 작성해 둔 `마감` 상태가 정본이 된다.

Finalization에서 전체 validator, `git diff --check`, lifecycle 정합성과 필요한 Browser 표본을 한 번 확인한다. 이후 HEAD가 바뀌면 기존 finalization 검증은 무효다. 기능·설계 변경은 Profile 작업 단계로, 새 actionable review는 Review 단계로 돌아가고, 마감 문서와 payload 변경은 Finalization을 다시 수행한다.

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

- 관련 작업 PR, review 대응, 남은 제한과 다음 Work Unit을 하나의 마감 snapshot으로 기록한다.
- 같은 closeout branch에서 필요한 tracked 마감 snapshot과 Progress payload를 완성한다.
- 공통 lifecycle과 상태 전환은 이 문서를 그대로 적용한다.
- 대상 Work Unit을 종료하며 별도 Work Unit으로 등록하거나 추가 closeout PR을 만들지 않는다.
- Closeout 중 구현 변경이 필요하면 현재 PR을 확장하지 않고 별도 profile 작업으로 분리한다.
- 이 정책 도입 전에 기본 branch에서 이미 마감한 Work Unit에는 소급 적용하지 않는다.
