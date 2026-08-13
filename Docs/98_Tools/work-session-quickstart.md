# Work Session Quickstart

이 문서는 Graphics Study Archive 작업 세션의 실행 순서를 안내한다. 반복 규칙의 정본은 `Docs/06_Policies`에 두며, 이 문서는 작업 유형에 맞는 정책, template과 validator를 찾는 router로만 사용한다.

## 1. 세션 시작

1. `git status --short --branch`로 branch와 worktree를 확인한다.
2. root `AGENTS.md`와 작업 대상 경로의 하위 `AGENTS.md`를 확인한다.
3. 요청이 조사, 수정, commit, push 또는 remote 변경 중 어디까지 허용하는지 구분한다.
4. 예상하지 못한 tracked 변경은 현재 작업에 포함하지 않고 소유 범위를 확인한다.

권한과 승인 기준은 [Agent Safety Policy](../06_Policies/agent-safety-policy.md)와 [GitHub Workflow Policy](../06_Policies/github-workflow-policy.md)를 따른다.

## 2. 작업 방식 선택

| 작업 유형 | 목표 모드 | 하위 agent |
| --- | --- | --- |
| 단일 파일의 명확한 수정 | 선택 | 사용하지 않음 |
| 여러 정본에 영향을 주는 조사 | 권장 | read-only 1개 또는 2개 |
| 문서 전수감사 | 사용 | read-only 최대 3개 |
| dirty worktree commit 분리 | 권장 | 사용하지 않음 |
| push와 remote body 동기화 | 권장 | 사용하지 않음 |
| PR 최종 read-only 감사 | 권장 | read-only 1개 또는 2개 |
| Ready 전환과 merge | 권장 | 사용하지 않음 |

조사와 비교는 read-only 범위에서 병렬화할 수 있다. 파일 수정, stage, commit과 remote 변경은 메인 agent가 직렬로 수행한다. 하위 agent 결과는 실제 파일과 상태를 메인 agent가 다시 확인한다.

문서 감사 keyword와 세부 구성은 [Document System Audit Policy](../06_Policies/document-system-audit-policy.md)와 [Document System Audit Guide](document-system-audit-guide.md)를 따른다.

### Chapter 시작 체크리스트

Chapter Work Unit을 시작할 때는 [Work Unit Workflow Policy](../06_Policies/work-unit-workflow-policy.md)의 Chapter 시작 체크포인트를 먼저 정리한다. 반복 사용하는 초안은 [Local Chapter Start Checkpoint](templates/local-chapter-start-checkpoint.md)를 사용한다.

1. Chapter 범위 확정
   - 예제 목록과 command argument를 확인한다.
   - build/run 대상과 제외 대상을 구분한다.
   - screenshot, stdout, video evidence를 분리한다.
   - 외부 asset 또는 공개 위험 요소를 확인한다.
2. 검증 기준선 작성
   - Debug x64 build/run을 우선 확인한다.
   - Release는 현재 재검증 대상인지 후속인지 구분한다.
   - runtime DLL, working directory, command argument, capture mode를 확인한다.
   - 실패는 `미확인`으로 뭉뚱그리지 않고 실패 원인과 다음 action으로 기록한다.
3. Capture 후보 생성 기준
   - target window/client area 기준을 사용한다.
   - overlay, taskbar, 녹화 툴, 알림 노출 여부를 확인한다.
   - video가 필요하면 desktop 환경 별도 목표로 분리한다.
   - local 후보와 tracked 승격 후보를 구분한다.
4. Demo 문서화 기준
   - Step별 상세 Demo 작성 여부를 판단한다.
   - Demo index에 representative, auxiliary, follow-up 상태를 기록한다.
   - code evidence link는 실제 source line count 안에 있는지 확인한다.
   - stdout-only 예제는 representative visual 없음이 의도된 상태인지 기록한다.
5. GitHub 게시 후보 기준
   - Demo Issue, PR body, Progress comment 후보 필요 여부를 판단한다.
   - Work Unit GitHub Index 갱신 후보를 확인한다.
   - H1 title source와 remote body 변환 규칙을 적용한다.
6. Remote 게시 전 승인안
   - push, Issue 생성, PR create/edit와 Ready 전환 대상을 분리한다.
   - 예상 remote 변경 객체와 rollback이 어려운 작업을 명시한다.
   - 승인 전 remote 변경을 실행하지 않는다.
7. Remote 게시 확인
   - 실제 remote body와 사용한 tracked payload가 일치하는지 확인한다.
   - Comment ID·URL과 posted 상태를 tracked 문서에 역동기화하지 않는다.
8. Ready for Review 감사
   - PR head와 branch head 일치를 확인한다.
   - remote body와 tracked 후보 일치를 확인한다.
   - 필요한 validator와 Browser 렌더링 표본을 확인한다.
   - 이미지 로딩을 확인한다.
   - Ready 전환은 별도 승인 후 실행한다.
9. Review 대응
   - 지적사항별 원인, 대응, 검증, 반영 commit을 기록한다.
   - thread 답글을 작성한다.
   - thread resolve 상태를 확인한다.
   - PR/Issue body에 필요한 링크를 보정한다.
10. Pre-merge finalization과 merge 검사
   - 같은 작업 branch에서 WorkLog, Index, PR 연결, 제한, 다음 작업과 Progress payload를 merge 후 관점으로 완성한다.
   - Finalization commit에서 전체 validator와 lifecycle 정합성 검사를 한 번 실행한다.
   - Merge 전에는 같은 SHA, clean worktree, Actions, review, conflict와 remote body만 read-only로 확인한다.
   - 일반 merge와 merge 성공을 조건으로 한 Progress 동기화 대상을 하나의 terminal 승인안으로 작성한다.

## 3. 책임 정본 찾기

먼저 [Docs Index](../00_Index/README.md)와 [Canonical Docs Policy](../06_Policies/canonical-docs-policy.md)에서 수정할 정본을 찾는다.

| 내용 | 정본 |
| --- | --- |
| 예제 목적과 기술적 구현 | 코드 폴더 `README.md` |
| graphics 개념과 이론 | `Docs/01_Topics` |
| 직접 확인한 build/run/capture | `Docs/02_Verification` |
| 구현 선택, visual과 결과 해석 | `Docs/03_Demos` |
| 작업 당시 결정과 마감 상태 | `Docs/04_WorkLogs` |
| public subset 판단 | `Docs/05_Publication` |
| 반복 운영 규칙 | `Docs/06_Policies` |
| GitHub 게시 후보 | `Docs/07_GitHub` |
| 실행 가이드와 validator | `Docs/98_Tools` |

같은 설명을 여러 정본에 복제하지 않고 요약과 링크로 연결한다.

## 4. 계획과 중단 조건

수정 전 대상 파일, 책임 정본, 검증 방법과 승인 범위를 정한다. 다음 상황에서는 추측해 진행하지 않고 작업을 중단해 보고한다.

- 요청과 다른 tracked 변경이 현재 파일과 겹친다.
- 직접 확인하지 않은 build/run/capture 상태를 성공으로 바꿔야 한다.
- 민감 정보, raw 원문 또는 공개 권한이 불명확한 asset을 발견한다.
- 삭제, history rewrite, non-fast-forward push가 필요하다.
- 사용자 선택에 따라 결과가 크게 달라진다.

## 5. 수정과 검증

대상 폴더의 README, AGENTS, 관련 policy와 template을 확인한 뒤 최소 범위로 수정한다. 검증은 작업 유형에 필요한 항목만 선택한다.

- 문서 공백과 patch 품질: `git diff --check`
- GitHub body: `validate-github-body.ps1`, `validate-github-quality.ps1`
- Demo index와 상세 Demo: 대응 Demo validator
- Topic: Topic validator
- Markdown: 상대 링크 대상과 stale path
- Markdown table: table validator와 fixture
- asset: tracked 여부, metadata, dimensions와 hash
- application window capture: [Example Window Capture](example-window-capture.md)
- application window recording: [Example Window Recording](example-window-recording.md)
- capture 조작 계획과 reset: [Capture Operation Guide](capture-operation-guide.md)
- code: 관련 build/test/run

validator의 지원 범위와 수동 검수 경계는 [Validation Tools](validation-tools.md)와 [Validators](validators/README.md)를 따른다.

새 PR/Issue, 공개 진입점, 큰 table 또는 대표 visual을 변경하면 push 후 로그인된 GitHub UI에서 대표 표본을 read-only로 확인한다. table·목록 layout, 의도하지 않은 줄바꿈, 이미지 로드·비율·잘림과 연결 문서 이동을 확인하며 상세 절차는 [Validation Tools](validation-tools.md)를 따른다.

## 6. Dirty Worktree와 Commit

1. `git status --short`와 `git diff --name-status`로 변경 전체를 확인한다.
2. 요청한 변경과 unrelated 변경을 구분한다.
3. 정책, 도구, 산출물과 게시 후보처럼 독립 검토 가능한 묶음으로 나눈다.
4. 각 묶음만 stage하고 `git diff --cached`로 범위를 확인한다.
5. `git diff --cached --check`와 해당 validator를 실행한다.
6. 승인된 경우에만 commit하고 남은 worktree를 다시 확인한다.

commit 승인과 readiness 기준은 [GitHub Workflow Policy](../06_Policies/github-workflow-policy.md)를 따른다.

## 7. Push Preflight와 Postflight

push 전에는 branch, upstream, ahead/behind, worktree, staged 변경, push 대상 commit과 fast-forward 가능 여부를 확인한다. force push는 별도 승인 없이는 사용하지 않는다.

push 후에는 local HEAD, tracking ref, 실제 remote branch head와 PR head를 비교한다. 값이 다르면 PR, Issue 또는 comment를 수정하지 않는다.

push 또는 pull request에 `Docs Validation` run이 생성되면 완료 상태와 validator별 step을 확인한다. 실패하면 [Validators](validators/README.md)와 [GitHub Workflow Policy](../06_Policies/github-workflow-policy.md)를 기준으로 validator 실패와 runner 또는 GitHub infrastructure 실패를 구분한다.

## 8. Remote 반영

Remote 변경은 사용자에게 대상, 명령과 예상 효과를 보고하고 승인받은 뒤 수행한다.

```text
대상과 조건 확인
-> remote 변경
-> 실제 remote 상태 확인
```

조건부 terminal execution에서는 merge 성공을 확인한 경우에만 Progress 동기화를 이어서 수행한다. Merge 후 Progress 작업만 실패하면 tracked 문서를 수정하지 않고 같은 remote 작업만 재시도한다.

Issue와 PR 후보의 첫 H1은 remote title source다. remote body에서는 첫 H1과 바로 뒤 빈 줄을 제거한다. comment body에는 H1을 사용하지 않는다.

## 9. 게시 후 확인

Remote body와 사용한 tracked payload의 일치만 확인한다. 실제 게시 여부, comment ID·URL과 게시 시각은 GitHub remote에 두며 tracked 역동기화를 만들지 않는다.

## 10. Ready, Review와 Merge

| 단계 | 확인 범위 | 실패 시 복귀 |
| --- | --- | --- |
| Review 전 최종 검사 | scope, PR body, 변경 범위 validator, build/test, 링크와 render | 작업 단계 |
| Ready for Review | PR 상태 전환과 remote 확인 | Ready 단계 |
| Review 대응 | actionable feedback, 영향 범위 regression, 답글과 resolve | Review 대응 |
| Pre-merge finalization | WorkLog, Index, 제한, 다음 작업, Progress payload와 전체 validator | Finalization |
| Merge 전 최종 검사 | 고정 SHA, clean/sync, Actions, review, conflict와 remote body | Review 또는 finalization |
| Terminal execution | 일반 merge, 기본 branch 확인, 조건부 Progress 동기화와 body 확인 | Remote 재시도 |

Finalization 문서는 merge 후 기본 branch에서 읽힐 상태로 작성한다. `Draft`, `Ready 대기`, `merge 시 반영`, `merge 승인 대기` 같은 현재 PR 과도 상태는 canonical 문서에 두지 않는다. Finalization 이후 HEAD가 바뀌면 종결 검사 증거와 merge 승인을 폐기하고 변경 성격에 맞는 단계로 돌아간다.

Finalization에서 전체 validator, `git diff --check`, lifecycle 정합성과 필요한 Browser 표본을 한 번 확인한다. Merge 전에는 같은 검사를 반복하지 않고 local HEAD, tracking, remote branch와 PR head 일치, clean worktree, Actions 성공, mergeable, `CHANGES_REQUESTED`와 미해결 actionable thread 부재만 확인한다.

Merge와 Progress 동기화를 함께 승인할 때는 PR 번호와 HEAD SHA, `--merge`, 대상 Issue와 comment, 사용할 payload를 명시한다. Merge가 실패하면 Progress 작업을 실행하지 않으며, Progress 작업만 실패하면 새 tracked 수정 없이 같은 remote 작업만 재시도한다. 둘 다 성공해야 작업 목표를 종료한다.

## 11. 종료와 Handoff

작업 종료 시 다음을 보고한다.

- 목표와 완료·보류 상태
- branch, worktree, upstream과 remote 상태
- 변경 파일과 책임별 작업 묶음
- 실행한 validator, test와 수동 검수
- 생성한 commit과 push 여부
- blocker, warning과 미확인 항목
- 승인받은 작업과 아직 승인받지 않은 remote 작업
- 다음 작업 범위와 권장 순서

현재 작업이 commit 가능한 상태면 stage 대상과 권장 commit 메시지를 함께 제시한다.

목표 상태와 Git 상태를 정리하고 필요한 사용자 승인·결정을 명시한 뒤, 사용자 확인이 필요한 terminal point이면 [User Attention Notification](user-attention-notification.md)을 한 번 실행하고 최종 응답을 제공한다.

일반 terminal point에는 즉시 알림을 사용한다. 후속 작업에 바로 사용하는 완성형 작업 프롬프트를 제공한 경우에는 최종 응답 직전에 `-DelaySeconds 60`으로 알림을 한 번 예약한다. 세부 대상, 비대상과 중복 처리 기준은 User Attention Notification을 따른다.
