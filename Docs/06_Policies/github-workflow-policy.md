# GitHub Workflow Policy

이 문서는 GitHub Issue, PR, gh CLI, pull, push, rebase, merge, Ready for Review 작업의 승인 흐름을 정의한다.

## 책임 경계

| 항목 | 정본 위치 |
| --- | --- |
| Work Unit 흐름 | `Docs/06_Policies/work-unit-workflow-policy.md` |
| 작업 마감 요약 | `Docs/04_WorkLogs` |
| GitHub 초안 | `local/` 임시 초안 |
| GitHub 게시 payload | `Docs/07_GitHub` |
| 실제 게시 여부, comment ID와 URL | GitHub remote |
| Progress Issue 진행판 | GitHub remote |
| 실제 Issue/PR 상태 | GitHub remote |

## 기본 흐름

```text
작업과 PR draft 작성
-> Review 전 최종 검사
-> Ready for Review
-> Review 대응 및 comment 처리
-> 같은 작업 branch의 pre-merge finalization
-> merge 전 최종 검사
-> 일반 merge와 조건부 Progress 동기화
```

## 승인 게이트

다음 작업은 실행 전에 사용자에게 대상, 명령, 예상 효과를 보고하고 승인받는다.

- `git pull`
- `git push`
- `git rebase`
- `git merge`
- branch delete 또는 remote branch 조작
- `gh issue create`, `gh issue edit`, `gh issue close`, `gh issue reopen`
- `gh pr create`, `gh pr edit`, `gh pr ready`, `gh pr merge`, `gh pr close`
- `gh pr review`, `gh pr comment`, `gh issue comment`
- Progress Issue 첫 누적 진행 댓글 또는 Chapter/Bundle 완료 댓글 생성/수정
- Ready for Review 전환
- remote 상태를 바꾸는 모든 GitHub 작업

하나의 terminal 승인에서 특정 PR HEAD의 일반 merge와 merge 성공을 조건으로 한 Progress 댓글 동기화를 함께 승인할 수 있다. 승인안에는 PR 번호와 HEAD SHA, merge 방식, 대상 Issue와 comment, 사용할 tracked payload를 모두 명시한다. 승인 후 HEAD가 바뀌거나 merge가 실패하면 Progress 작업을 실행하지 않는다. Merge 성공 후 Progress 작업만 실패하면 tracked 수정이나 새 PR을 만들지 않고 같은 remote 작업만 재시도한다.

## 브랜치 보존과 merge 방식

포트폴리오 작업 브랜치는 작업 흐름과 상세 변경 이력을 증빙하는 자료가 될 수 있다. 에이전트는 로컬 브랜치와 원격 브랜치를 임의로 삭제하지 않는다.

브랜치 정리 기준:

- branch delete는 사용자가 삭제 대상과 범위를 명시적으로 승인한 경우에만 진행한다.
- merge 후에도 브랜치는 보존할 수 있는 상태로 둔다.
- stale remote-tracking ref 정리는 실제 원격 브랜치를 삭제하지 않는 경우에만 별도 보고 후 진행한다.
- 브랜치 마감은 삭제가 아니라 상태 확인, PR 링크 기록, 다음 작업 제안을 의미한다.

merge 방식:

- PR merge는 기본적으로 일반 merge commit 방식을 사용한다.
- `gh pr merge`를 사용할 때는 기본적으로 `--merge`를 사용한다.
- `--squash`, `--rebase`, history rewrite, force push는 사용자가 별도로 지시하고 위험도를 확인한 경우가 아니면 사용하지 않는다.
- `--delete-branch`는 사용자가 별도로 요청하지 않는 한 사용하지 않는다.

## 작업 PR lifecycle과 예외 closeout PR

작업 PR은 코드·문서 산출물, review 대응과 Work Unit finalization을 함께 merge하는 기본 단위다. Work Unit 상태와 완료 조건의 정본은 `work-unit-workflow-policy.md`를 따른다.

기본 lifecycle은 다음 책임으로 고정한다.

1. Review 전 최종 검사는 현재 pushed HEAD가 review 가능한지만 판정한다.
2. Ready for Review는 PR 상태만 전환한다.
3. Review 대응은 actionable feedback 수정, 영향 범위 검증, 답글과 resolve만 처리한다.
4. Pre-merge finalization은 같은 작업 branch에서 merge될 tracked 마감 snapshot을 완성한다.
5. Merge 전 최종 검사는 finalization HEAD가 바뀌지 않았는지와 remote merge blocker만 확인한다.
6. Terminal execution은 일반 merge와 merge 성공을 조건으로 한 Progress 원격 동기화를 연속 수행한다.

Pre-merge finalization에서는 WorkLog, `work-unit-index.md`, `work-unit-github-index.md`, PR 연결, 제한, 다음 Work Unit과 Progress payload를 모두 merge 후 기본 branch에서 읽힐 최종 관점으로 작성한다. Canonical 문서에 현재 PR의 `Draft`, `Ready 대기`, `merge 시 반영`, `merge 승인 대기` 같은 과도 상태를 기록하지 않는다. 현재 PR 상태와 승인 gate는 GitHub remote와 사용자 보고가 담당한다.

Finalization 이후 HEAD가 바뀌면 이전 종결 검증과 merge 승인은 무효다. 기능·설계 변경이나 새 actionable review는 review 대응 단계로, 마감 문서와 payload 변경은 finalization 단계로 돌아간다.

별도 closeout branch와 PR은 여러 작업 PR의 결과 종합 자체가 review 대상이거나 finalization 누락으로 기본 branch의 정본이 실제로 거짓이고 다음 작업을 막을 때만 사용한다. Merge SHA, posted 상태, comment ID·URL, branch URL을 기록하기 위한 closeout은 만들지 않는다.

예외 closeout PR 기준:

- 새로운 기능 구현, 별도 refactoring, source·asset 변경과 새로운 build/capture 결과를 포함하지 않는다.
- 관련 작업 PR, review 대응, 남은 제한과 다음 Work Unit을 하나의 마감 snapshot으로 기록한다.
- 같은 closeout branch에서 tracked 마감 snapshot과 Progress payload를 완성한다.
- 기본 lifecycle의 review, finalization, merge 전 검사와 terminal execution을 그대로 적용한다.
- 대상 Work Unit을 종료하는 terminal PR이며 별도 Work Unit으로 등록하거나 추가 closeout PR을 만들지 않는다.
- Closeout 중 구현 변경이 필요하면 현재 PR을 확장하지 않고 별도 작업 PR로 분리한다.
- 이 정책 도입 전에 기본 branch에서 이미 마감한 Work Unit에는 소급 적용하지 않는다.

작업 PR과 예외 closeout PR의 push, Ready for Review, review comment, merge와 Progress Issue 동기화에는 이 문서의 승인 게이트를 그대로 적용한다.

## gh CLI 실행 오류 대응

Windows Codex 환경에서 `gh` 명령이 실패해도 인증 만료로 단정하지 않는다. 특히 `token in keyring is invalid`, credential manager 접근 오류, sandbox 안에서만 발생하는 인증 오류는 실행 환경 제한일 수 있다.

처리 순서:

1. 실패한 `gh` 명령과 오류 메시지를 기록한다.
2. 같은 명령을 PowerShell + `require_escalated` 경로로 재시도한다.
3. 재시도에서 성공하면 sandbox의 keyring 접근 제한으로 판단한다.
4. 그래도 실패하면 원격 작업을 중단하고 오류, 실행 명령, 필요한 사용자 조치를 보고한다.

기본 대응으로 사용하지 않는 것:

- `gh auth token`처럼 토큰 값을 출력할 수 있는 명령
- `GH_TOKEN` 또는 `GITHUB_TOKEN` 주입
- Git Bash 직접 호출 우회
- 사용자에게 재로그인을 먼저 요구하는 대응

## commit 기준

commit은 사용자가 명시적으로 요청했거나 현재 대화에서 커밋까지 승인한 작업 단위일 때만 진행한다. 다음 조건을 모두 만족해야 한다.

- 변경 범위가 요청과 일치한다.
- stage 대상 파일을 확인했다.
- `git diff --cached --check`를 통과했다.
- 커밋 메시지가 기존 패턴과 맞는다.
- push는 하지 않는다.


## Commit Readiness 보고

작업 종료 시에는 commit 가능 상태인지 확인하고 보고한다. 실제 commit은 사용자가 명시적으로 요청했거나 현재 대화에서 커밋까지 승인한 경우에만 실행한다.

보고 항목:

- 커밋 가능 여부
- 커밋에 포함할 파일
- 제외할 파일
- 실행한 검증과 결과
- 권장 commit 메시지
- Git Bash 기준 `git add`와 `git commit` 명령
- push 필요 여부와 승인 필요 여부

커밋 가능 기준:

- 변경 범위가 사용자 요청과 일치한다.
- unrelated 변경이 섞이지 않았다.
- `git diff --check` 또는 `git diff --cached --check`를 통과했다.
- 필요한 validator, test, 문체 검수 결과를 확인했다.
- 직접 확인하지 않은 항목은 `미확인`으로 남겼다.

커밋 보류 기준:

- 검증 실패 또는 확인 불가 항목이 설명 없이 남아 있다.
- 변경 범위가 여러 작업 단위로 섞여 분리 판단이 필요하다.
- 사용자 결정이 필요한 파일이나 원격 상태 변경이 포함되어 있다.
- 리뷰 대응을 마지막 커밋으로 남기기로 한 경우처럼 의도된 커밋 순서가 남아 있다.

## Source Docs와 GitHub Body 경계

`Docs/00_Index`부터 `Docs/06_Policies`와 `Docs/_assets`는 GitHub body의 source docs다. 이 범위에는 archive 정본, 상태 기록, 검증 근거, visual result 파일, 정책을 둔다.

`Docs/07_GitHub`는 source docs를 GitHub Issue, PR, comment body로 요약/재구성하는 staging 공간이다. GitHub body는 source docs의 원문을 복제하지 않고, 게시 목적에 맞는 요약과 링크만 둔다.

기본 갱신 기준:

- 매 작업마다 WorkLog, 누적 진행 댓글, PR body 갱신 필요 여부를 확인한다.
- Work Unit Issue, Demo Issue, Verification Issue는 독립 추적 가치가 있을 때만 만든다.
- Verification과 Demo 문서는 GitHub 게시 양식을 고민하는 위치가 아니라 상태와 근거를 관리하는 source docs다.
- GitHub body를 작성할 때는 source docs를 읽고 public-safe 문장으로 재작성한다.
## GitHub body 전환 기준

다음 전환은 remote 상태를 바꾸지 않으므로 agent가 진행할 수 있다. 단, 전환 결과와 validator 결과를 사용자에게 보고한다.

```text
local/ 임시 초안
-> Docs/07_GitHub
-> validator 실행
-> 사용자 검토 요청
```

다음 원격 게이트는 사용자 승인 후에만 진행한다.

```text
GitHub 게시
-> remote body 일치 확인
```

## Progress Issue 운영 기준

상위 Progress Issue는 Graphics Study Archive의 장기 진행판으로 운영한다. Work Unit마다 새 Progress Issue를 만들지 않는다.

Progress Issue의 책임:

- 전체 목표와 범위, 제외 대상, 정본 정책 링크를 제공한다.
- 현재 진행 상황을 첫 누적 진행 댓글로 보여준다.
- 각 Chapter 또는 Chapter 묶음의 마감 기록을 Chapter/Bundle 완료 댓글로 남긴다.
- 상세 설명과 정본은 `Docs`에 두고, Issue에는 요약과 링크만 둔다.

Progress Issue 댓글은 두 종류로 고정한다.

| 댓글 유형 | 게시 후보 파일 | 책임 |
| --- | --- | --- |
| 누적 진행판 | `Docs/07_GitHub/plan/plan-progress.md` | 완료, 진행 중, 예정 Work Unit과 관련 PR 현황 |
| 완료 plan comment | `Docs/07_GitHub/plan/comments/*.md` | 의미 있는 Phase, Chapter 묶음 또는 Work Unit 마감 요약 |

Progress Issue 댓글을 생성하거나 수정하기 전에는 대상 Issue, 사용할 게시 후보 파일, 실행할 `gh` 명령, 예상 변경 요약을 사용자에게 보고하고 승인받는다.

## Issue 책임

Issue는 작업 범위, 검증 항목, demo 필요 여부, 완료 조건을 추적한다. Docs 원문을 복제하지 않고 정본 문서 링크와 요약을 둔다.

Work Unit Issue는 작업 단위가 GitHub에서 별도 추적될 때만 만든다. WorkLog와 PR body를 대체하지 않으며, 범위와 완료 조건만 짧게 남긴다.

Issue에 포함할 항목:

- 대상 Work Unit
- 연결 Example, Topic, Verification, Demo, Publication 문서
- 검증할 build/run/capture 항목
- 완료 조건
- follow-up 후보

## PR 책임

PR 기본 단위는 Chapter 또는 Chapter 묶음이다. Part는 Progress Issue, WorkLog, milestone, 진행판 단위로 다루고 PR 기본 단위로 사용하지 않는다.

PR body는 README의 미러가 아니라 GitHub review를 위한 요약과 링크 허브다. 상세 설명은 Chapter README, Example README, Topic, Verification, Demo, Publication 정본으로 연결한다. PR body의 검증 상태는 게시 시점 snapshot이며, 최신 검증 정본은 `Docs/02_Verification`에 둔다.

PR 초안은 `local/`에서 작성할 수 있고, 게시 후보 정본은 `Docs/07_GitHub/prs`에 둔다.

Chapter 또는 Chapter 묶음 PR에 포함할 항목:

- Chapter 또는 Chapter 묶음 범위
- 핵심 개념과 간단한 설명
- 대표 예제와 README 링크
- 검증 결과 요약
- demo/capture/result 링크
- public readiness 영향
- 남은 known issue
- 다음 Work Unit 또는 Issue 후보

Part 단위 PR은 예제가 적고 변경 범위가 작을 때만 예외로 허용한다. Part 전체 진행은 Progress Issue, WorkLog, milestone 성격으로 추적한다.

closeout, 구조 정리, 문서 정합화, 운영 규칙과 validator 변경처럼 그래픽 개념과 대표 예제가 중심이 아닌 PR은 maintenance 형식을 사용한다. maintenance PR은 `## 주요 변경` heading으로 식별하며 요약, 범위, 주요 변경, 검증, 제한, 문서, 관련 이슈와 다음 단계를 기록한다. 그래픽 결과를 새로 만들거나 검증하지 않은 maintenance PR에는 핵심 개념, 대표 예제와 screenshot을 강제하지 않는다.

Chapter PR body 작성 기준:

- `핵심 개념`과 `대표 예제`는 문단과 짧은 리스트를 기본으로 한다.
- 표는 검증, 상태, 링크 매트릭스처럼 짧은 정보를 비교할 때만 사용한다.
- 파일 변경 목록은 구조 정리 PR처럼 파일 이동 자체가 핵심인 경우에만 중심 섹션으로 둔다.
- public 공개 판단은 PR body에서 단정하지 않고 `Docs/05_Publication`으로 연결한다.
- screenshot/result image는 repo-relative path가 아니라 GitHub absolute URL로 연결한다.
- draft PR 후보는 작업 branch 기준 `https://github.com/<owner>/<repo>/blob/<branch>/Docs/_assets/...?...raw=true` 형식을 사용한다.
- Merge 후 게시할 Progress payload는 finalization부터 기본 branch에서 유효한 URL을 사용한다.

Maintenance PR body 작성 기준:

- `## 주요 변경`을 유형 식별자이자 변경 내용의 중심 section으로 사용한다.
- Chapter PR 전용 section인 `핵심 개념`, `대표 예제`, `스크린샷`을 함께 사용하지 않는다.
- 새 build/run/capture를 수행하지 않았다면 검증 section에 그 사실과 유지하는 기존 정본을 기록한다.
- 파일 목록을 복제하지 않고 상태 정합화, 구조 이동, 운영 규칙과 validator 변경의 review point를 요약한다.

## GitHub body 유형

GitHub에 게시하는 Markdown body는 `Docs/07_GitHub` 파일을 기준으로 검수한다. source docs와 상세 설명은 `Docs/00_Index`부터 `Docs/06_Policies`, `Docs/_assets`에 두고, GitHub body는 요약과 링크 중심으로 재구성한다.

| 유형 | 위치 | 최소 책임 |
| --- | --- | --- |
| Chapter PR Body | `Docs/07_GitHub/prs/**/*.md` | 핵심 개념, 대표 예제, 검증, Demo capture/result, 제한, 관련 Issue/PR |
| Maintenance PR Body | `Docs/07_GitHub/prs/**/*.md` | 범위, 주요 변경, 검증, 제한, 관련 Issue/PR |
| Work Unit Issue | `Docs/07_GitHub/issues/work-unit/work-unit_*.md` | Work Unit 범위, 검증 기준, 완료 조건 |
| Verification Issue | `Docs/07_GitHub/issues/verification/verification_*.md` | build/run/capture 검증 결과와 미확인 항목 |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_*.md` | demo 범위, 생성 기준, 승인 필요 범위 |
| Progress Body | `Docs/07_GitHub/plan/plan-body.md` | 상위 진행판 본문 |
| Progress Comment | `Docs/07_GitHub/plan/plan-progress.md` | 전체 진행판 누적 댓글 |
| Plan Comment | `Docs/07_GitHub/plan/comments/*.md` | 의미 있는 Phase, Chapter 묶음 또는 Work Unit 완료 기록 |

게시 전 후보에는 `Metadata`, 내부 메모, draft 문구, 존댓말을 남기지 않는다. validator가 지원하는 범위는 `Docs/98_Tools/validators/README.md`를 따른다.

Issue와 PR body는 tracked 후보 본문의 첫 H1을 title source로 사용한다. tracked 정본은 H1을 유지하고 validator 검사 대상이 된다. 실제 `gh issue create`와 `gh pr create`에서는 title을 H1에서 쓰고, body는 tracked 정본 그대로 게시한다. comment body는 title이 없으므로 H1을 사용하지 않는다.

누적 진행 댓글은 Progress Issue 당 1개를 유지하고, 새 댓글 생성 대신 기존 댓글을 갱신한다.

## draft to GitHub body 흐름

```text
local/ 임시 초안
-> Docs/07_GitHub
-> GitHub remote
```

## 원격 반영 후 동기화

GitHub remote에 Issue, PR, comment를 게시하거나 수정한 뒤에는 remote 본문과 사용한 `Docs/07_GitHub` payload가 일치하는지만 확인한다. 실제 게시 여부, comment ID·URL과 게시 시각은 GitHub remote가 정본이며 이를 기록하기 위한 tracked 수정이나 후속 PR을 만들지 않는다. 별도 보존 가치가 있을 때만 `local/` snapshot을 선택적으로 만든다.

## WorkLog 반영

WorkLog에는 GitHub 본문 전체가 아니라 다음만 남긴다.

- 작업 범위
- 갱신한 정본 문서 링크
- 검증 요약
- 안정적으로 연결할 Issue/PR 번호
- 리뷰 대응과 follow-up


## PR 리뷰 대응 댓글

PR review comment에 답변할 때는 짧은 고정 형식을 사용한다. 답변은 수정 내용, 검증, 남은 제한만 남기고 긴 원인 분석은 반복하지 않는다.

기본 형식:

```md
반영했습니다.

- 대응: <무엇을 어떻게 수정했는지>
- 검증: <실행한 검증 또는 확인한 근거>
- 비고: <남은 제한 또는 추가 제한 없음>
```

반복 작성용 템플릿은 `Docs/98_Tools/templates/pr-review-response.md`를 따른다. 원격 댓글 게시 또는 review thread resolve는 승인 게이트를 따른다.

## 운영 기준

- Issue/PR 생성은 사용자가 명시적으로 요청한 경우에만 진행한다.
- 게시 전 초안은 local에서 검토할 수 있고, 게시 후보 정본은 `Docs/07_GitHub`에 둔다.
- 게시 전 후보는 `Metadata`, 내부 메모, draft 문구, 존댓말을 제거한다.
- 게시 후 실제 상태는 GitHub remote에서 확인한다.
- Merge 후 Progress 동기화 결과를 tracked 문서에 역동기화하지 않는다.
