# GitHub Workflow Policy

이 문서는 GitHub Issue, PR, gh CLI, pull, push, rebase, merge, Ready for Review 작업의 승인 흐름을 정의한다.

## 책임 경계

| 항목 | 정본 위치 |
| --- | --- |
| Work Unit 흐름 | `Docs/06_Policies/work-unit-workflow-policy.md` |
| 작업 마감 요약 | `Docs/04_WorkLogs` |
| GitHub 초안 | `local/` 임시 초안 |
| GitHub 게시 후보 정본 | `Docs/07_GitHub` |
| 선택적으로 보존하는 게시본과 리뷰 대응 사본 | `local/` 하위 snapshot |
| Progress Issue 진행판 | GitHub remote, `Docs/07_GitHub/plan` |
| 실제 Issue/PR | GitHub remote |

## 기본 흐름

```text
내용 파악
-> 작업 플랜 작성
-> 사용자 보고
-> 코드/문서 작업
-> 사용자 검토
-> 검증 확인
-> capture/result 정리
-> Issue/PR draft 작성
-> 사용자 검토 요청
-> gh 작업 계획 제안
-> 승인 후 GitHub 게시
-> Ready for Review
-> 리뷰 검토와 대응
-> merge 승인 확인
-> merge
-> 브랜치 마감 상태 확인
-> 다음 작업 제안
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

## Push 확인 기준

push는 승인 후 실행하며, 실행 전에는 현재 branch, upstream, ahead/behind, worktree, staged 변경과 push 대상 commit을 확인한다. upstream이 예상과 다르거나 non-fast-forward 가능성이 있으면 push를 중단하고 차이를 보고한다. force push는 사용자가 별도로 승인하지 않는 한 사용하지 않는다.

push 후에는 local HEAD, tracking ref, 실제 remote branch head와 PR head를 비교한다. 각 값이 일치하지 않으면 후속 remote 변경을 진행하지 않는다.

## Remote 변경의 직렬 실행

Issue, PR, comment와 Ready 상태 같은 remote 변경은 한 번에 한 객체씩 수행하고 즉시 결과를 확인한다. 여러 객체를 동시에 수정하지 않는다.

remote 변경이 일부만 성공하면 다음 원칙을 적용한다.

- 후속 remote 변경을 중단한다.
- 성공한 대상과 실행되지 않은 대상을 구분해 기록한다.
- 실패 원인과 실제 remote 상태를 read-only로 다시 확인한다.
- 확인되지 않은 rollback이나 우회 수정을 시도하지 않는다.
- 복구 범위와 명령을 보고하고 다시 승인받는다.

## Source Docs와 GitHub Body 경계

코드 폴더 README, `Docs/00_Index`부터 `Docs/06_Policies`, `Docs/_assets`는
GitHub body의 source docs다. 이 범위에는 archive 정본, 상태 기록, 검증 근거,
visual result 파일, 정책을 둔다.

`Docs/07_GitHub`는 source docs를 GitHub Issue, PR, comment body로 요약/재구성하는 staging 공간이다. GitHub body는 source docs의 원문을 복제하지 않고, 게시 목적에 맞는 요약과 링크만 둔다.

기본 갱신 기준:

- 매 작업마다 WorkLog, 누적 진행 댓글, PR body 갱신 필요 여부를 확인한다.
- Work Unit Issue와 Verification Issue는 독립 추적 가치가 있을 때만 만든다.
- Demo Issue는 독립적인 시각·기술 공개 가치가 있을 때만 만든다.
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

다음 단계는 사용자 승인 후에만 진행한다.

```text
GitHub 게시
-> 필요 시 local/ 하위 snapshot 저장
-> Docs/04_WorkLogs 갱신
-> Docs/04_WorkLogs/work-unit-github-index.md 갱신
```

게시 후에는 실제 Issue/PR 번호와 URL을 기록하고, 변경 영향이 있는 Chapter
README, 상세 Demo, Demo index, PR 후보, WorkLog, Publication 후보만
동기화한다. 모든 문서를 기계적으로 갱신하지 않는다.

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
| PR 마감 plan comment | `Docs/07_GitHub/plan/comments/*.md` | PR 마감 단위 요약, 검증, 남은 제한, 관련 PR |

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

### Demo Issue

Demo Issue는 상세 Demo 정본에서 공개 가치가 높은 결과와 구현을 선별한 curated
publication view다. Issue 하나만 읽어도 대표 결과, 핵심 구현, 구현 범위와 한계를
이해할 수 있게 작성하고 상세 Demo 전체를 복제하지 않는다.

- 대표 visual 1~3개와 핵심 구현 요약을 자체 포함한다.
- 상세 Demo, Example, Topic, Verification, 코드와 관련 PR을 연결한다.
- capture 생성 승인이나 내부 workflow 추적에 사용하지 않는다.
- 게시 시점 snapshot으로 보되 중요한 구현, 결과, limitation이 바뀌면
  동기화 필요 여부를 확인한다.

## PR 책임

PR 기본 단위는 Chapter 또는 Chapter 묶음이다. Part는 Progress Issue, WorkLog, milestone, 진행판 단위로 다루고 PR 기본 단위로 사용하지 않는다.

PR body는 README의 미러가 아니라 GitHub review를 위한 요약과 링크 허브다. 상세 설명은 Chapter README, Example README, Topic, Verification, Demo, Publication 정본으로 연결한다. PR body의 검증 상태는 게시 시점 snapshot이며, 최신 검증 정본은 `Docs/02_Verification`에 둔다.

PR 초안은 `local/`에서 작성할 수 있고, 게시 후보 정본은 `Docs/07_GitHub/prs`에 둔다.

PR에 포함할 항목:

- Chapter 또는 Chapter 묶음 범위
- 핵심 개념과 간단한 설명
- 대표 예제와 README 링크
- 검증 결과 요약
- demo/capture/result 링크
- 대표 visual 0~1개
- Publication 판단 링크와 독자에게 필요한 영향 요약
- 남은 known issue
- 독자에게 필요한 기술 follow-up이 있을 때만 선택적으로 추가

Part 단위 PR은 예제가 적고 변경 범위가 작을 때만 예외로 허용한다. Part 전체 진행은 Progress Issue, WorkLog, milestone 성격으로 추적한다.

PR body 작성 기준:

- `핵심 개념`과 `대표 예제`는 문단과 짧은 리스트를 기본으로 한다.
- 표는 검증, 상태, 링크 매트릭스처럼 짧은 정보를 비교할 때만 사용한다.
- 파일 변경 목록은 구조 정리 PR처럼 파일 이동 자체가 핵심인 경우에만 중심 섹션으로 둔다.
- public 공개 판단은 PR body에서 단정하지 않고 `Docs/05_Publication`으로 연결한다.
- screenshot/result image는 repo-relative path가 아니라 GitHub absolute URL로 연결한다.
- 게시 전 branch 검토가 필요하면 후보 branch URL을 임시로 사용할 수 있다.
- 계속 갱신되는 문서 이동 링크는 확인된 default branch URL을 사용한다.
- 게시 시점의 이미지와 코드 증거는 commit permalink를 사용한다.
- 상세 visual과 기술 showcase는 Demo Issue로 위임한다.
- Demo Issue가 게시되지 않았으면 상세 Demo 정본으로 직접 연결한다.

## GitHub body 유형

GitHub에 게시하는 Markdown body는 `Docs/07_GitHub` 파일을 기준으로 검수한다. source docs와 상세 설명은 `Docs/00_Index`부터 `Docs/06_Policies`, `Docs/_assets`에 두고, GitHub body는 요약과 링크 중심으로 재구성한다.

| 유형 | 위치 | 최소 책임 |
| --- | --- | --- |
| PR Body | `Docs/07_GitHub/prs/**/*.md` | 핵심 개념, 대표 예제, 검증, 대표 visual 0~1개, Demo 링크, 제한 |
| Work Unit Issue | `Docs/07_GitHub/issues/work-unit/work-unit_*.md` | Work Unit 범위, 검증 기준, 완료 조건 |
| Verification Issue | `Docs/07_GitHub/issues/verification/verification_*.md` | build/run/capture 검증 결과와 미확인 항목 |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_*.md` | 대표 visual, 핵심 구현, 범위와 한계, 상세 Demo·코드·검증·PR 링크 |
| Progress Body | `Docs/07_GitHub/plan/plan-body.md` | 상위 진행판 본문 |
| Progress Comment | `Docs/07_GitHub/plan/plan-progress.md` | 전체 진행판 누적 댓글 |
| Plan Comment | `Docs/07_GitHub/plan/comments/*.md` | PR 마감 기록 |

게시 전 후보에는 `Metadata`, 내부 메모, draft 문구, 존댓말을 남기지 않는다. validator가 지원하는 범위는 `Docs/98_Tools/validators/README.md`를 따른다.

Issue와 PR body는 tracked 후보 본문의 첫 H1을 title source로 사용한다. tracked 정본은 H1을 유지하고 validator 검사 대상이 된다. 실제 remote title은 첫 H1의 본문을 사용하고 remote body에서는 첫 H1과 바로 뒤 빈 줄을 제거한다. remote body와 tracked 후보를 비교할 때도 같은 변환을 적용한다. comment body는 title이 없으므로 H1을 사용하지 않는다.

누적 진행 댓글은 Progress Issue 당 1개를 유지하고, 새 댓글 생성 대신 기존 댓글을 갱신한다.

## draft to GitHub body 흐름

```text
local/ 임시 초안
-> Docs/07_GitHub
-> GitHub remote
-> 필요 시 local/ 하위 snapshot
-> Docs/04_WorkLogs 요약 반영
```

## 원격 반영 후 동기화

GitHub remote에 Issue, PR, comment를 게시하거나 수정한 뒤에는 다음을 확인한다.

- GitHub remote 본문과 H1 title source 변환을 적용한 `Docs/07_GitHub` 파일의 내용이 일치한다.
- 실제 Issue/PR 번호와 URL을 WorkLog index에 기록한다.
- 게시 후 실제 본문 또는 리뷰 대응 기록이 필요하면 `local/` 하위 snapshot에 남긴다.
- `Docs/04_WorkLogs`에는 원문이 아니라 요약과 링크만 반영한다.
- `Docs/04_WorkLogs/work-unit-github-index.md`의 Issue/PR/Progress comment 상태를 갱신한다.
- 변경 영향이 있는 Chapter README, 상세 Demo, Demo index, PR 후보,
  Publication 후보의 링크와 상태를 확인한다.

## Ready for Review 확인

Ready for Review 감사와 실제 상태 전환을 분리한다. 감사 단계는 read-only로 진행하고 다음을 확인한다.

- local, tracking ref, 실제 remote branch와 PR head가 일치한다.
- PR title과 body가 tracked 후보 및 실제 변경 범위를 설명한다.
- validator, 필요한 test와 public safety 검사가 통과한다.
- 깨진 링크, 미해결 review thread, 충돌과 merge 차단 요소가 없다.
- 남은 warning과 follow-up이 Ready 전환을 막는지 구분한다.

감사 결과는 `READY`, `READY WITH WARNINGS`, `BLOCKED` 중 하나로 보고한다. 판정은 상태 전환 승인을 대신하지 않는다. `gh pr ready`는 별도 사용자 승인 후에만 실행한다.

## WorkLog 반영

WorkLog에는 GitHub 본문 전체가 아니라 다음만 남긴다.

- 작업 범위
- 갱신한 정본 문서 링크
- 검증 요약
- 게시한 Issue/PR 번호 또는 예정 상태
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
- 게시 후 실제 게시본이나 리뷰 대응 기록을 별도로 보존할 필요가 있을 때만 `local/` 하위 snapshot에 둔다.
- merge 후 최종 상태는 각 정본 문서에 반영한다.
