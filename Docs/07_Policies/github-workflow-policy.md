# GitHub Workflow Policy

이 문서는 GitHub Issue, PR, gh CLI, pull, push, rebase, merge, Ready for Review 작업의 승인 흐름을 정의한다.

## 책임 경계

| 항목 | 정본 위치 |
| --- | --- |
| Work Unit 흐름 | `Docs/07_Policies/work-unit-workflow-policy.md` |
| 작업 마감 요약 | `Docs/05_WorkLogs` |
| GitHub 초안 | `local/github/draft` |
| GitHub 게시 직전 최종 후보 | `local/github/public` |
| 게시 후 실제 게시본과 리뷰 대응 사본 | `local/github/snapshots` |
| Plan Issue 진행판 | GitHub remote, `local/github/public/issues/plan-comments` |
| 실제 Issue/PR | GitHub remote |

## 기본 흐름

```text
내용 파악
-> 작업 플랜 작성
-> 사용자 보고
-> 코드/문서 작업
-> 사용자 검토
-> 검증 확인
-> 캡처/영상 evidence 정리
-> Issue/PR draft 작성
-> 사용자 검토 요청
-> gh 작업 계획 제안
-> 승인 후 GitHub 게시
-> Ready for Review
-> 리뷰 검토와 대응
-> merge 승인 확인
-> merge
-> 브랜치 마감
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
- Plan Issue 첫 누적 진행 댓글 또는 WorkLog 댓글 생성/수정
- Ready for Review 전환
- remote 상태를 바꾸는 모든 GitHub 작업

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

## local GitHub body 전환 기준

다음 local-only 전환은 remote 상태를 바꾸지 않으므로 agent가 진행할 수 있다. 단, 전환 결과와 validator 결과를 사용자에게 보고한다.

```text
local/github/draft
-> local/github/public
-> validator 실행
-> 사용자 검토 요청
```

다음 단계는 사용자 승인 후에만 진행한다.

```text
GitHub 게시
-> local/github/snapshots 저장
-> Docs/05_WorkLogs 갱신
-> Docs/05_WorkLogs/issue-pr-index.md 갱신
```

## Plan Issue 운영 기준

상위 `[Plan]` Issue는 Graphics Study Archive의 장기 진행판으로 운영한다. Work Unit마다 새 Plan Issue를 만들지 않는다.

Plan Issue의 책임:

- 전체 목표와 범위, 제외 대상, 정본 정책 링크를 제공한다.
- 현재 진행 상황을 첫 누적 진행 댓글로 보여준다.
- 각 Work Unit 또는 PR 마감 기록을 별도 댓글로 남긴다.
- 상세 설명과 정본은 `Docs`에 두고, Issue에는 요약과 링크만 둔다.

Plan Issue 댓글은 두 종류로 고정한다.

| 댓글 유형 | local public 파일 | 책임 |
| --- | --- | --- |
| 누적 진행판 | `local/github/public/issues/plan-comments/plan_progress_summary_comment.md` | 완료, 진행 중, 예정 Work Unit과 관련 PR 현황 |
| WorkLog 마감 댓글 | `local/github/public/issues/plan-comments/*_worklog_comment.md` | Work Unit 또는 PR 마감 요약, 검증, 남은 제한, 관련 PR |

Plan Issue 댓글을 생성하거나 수정하기 전에는 대상 Issue, 사용할 local public 파일, 실행할 `gh` 명령, 예상 변경 요약을 사용자에게 보고하고 승인받는다.

## Issue 책임

Issue는 작업 범위, 검증 항목, demo 필요 여부, 완료 조건을 추적한다. Docs 원문을 복제하지 않고 정본 문서 링크와 요약을 둔다.

Issue에 포함할 항목:

- 대상 Work Unit
- 연결 Example, Topic, Verification, Demo, Publication 문서
- 검증할 build/run/capture 항목
- 완료 조건
- follow-up 후보

## PR 책임

PR은 변경 범위, 검증 결과, Demo evidence, known issue, follow-up을 요약한다. PR 본문 초안은 `local/github/draft/prs`에서 작성한다.

PR에 포함할 항목:

- 변경한 문서와 코드 범위
- 검증 결과 요약
- demo/capture evidence 링크
- public readiness 영향
- 남은 known issue
- 다음 Work Unit 또는 Issue 후보

## GitHub public body 유형

GitHub에 게시하는 Markdown body는 `local/github/public` 파일을 기준으로 검수한다. 정본 정책과 상세 설명은 `Docs`에 두고, GitHub body는 요약과 링크 중심으로 작성한다.

| 유형 | 위치 | 최소 책임 |
| --- | --- | --- |
| PR Body | `local/github/public/prs/**/*.md` | 변경 범위, 검증, Demo evidence, 제한, 관련 Issue/PR |
| Topic Issue | `local/github/public/issues/topic/*.md` | Topic 정리 범위와 연결 문서 |
| Verification Issue | `local/github/public/issues/verification/*.md` | build/run/capture 검증 결과와 미확인 항목 |
| Plan Progress Comment | `local/github/public/issues/plan-comments/plan_progress_summary_comment.md` | 전체 진행판 |
| WorkLog Comment | `local/github/public/issues/plan-comments/*_worklog_comment.md` | 작업 마감 기록 |
| Demo Evidence Comment | `local/github/public/pr-comments/*.md` | capture/video evidence 보강 |

게시 전 후보에는 `Metadata`, 내부 메모, draft 문구, 존댓말을 남기지 않는다. validator가 지원하는 범위는 `Docs/98_Tools/validators/README.md`를 따른다.

## draft to public 흐름

```text
local/github/draft
-> local/github/public
-> GitHub remote
-> local/github/snapshots
-> Docs/05_WorkLogs 요약 반영
```

## 원격 반영 후 동기화

GitHub remote에 Issue, PR, comment를 게시하거나 수정한 뒤에는 다음을 확인한다.

- GitHub remote 본문과 `local/github/public` 파일의 내용이 일치한다.
- 게시 후 실제 본문 또는 리뷰 대응 기록이 필요하면 `local/github/snapshots`에 남긴다.
- `Docs/05_WorkLogs`에는 원문이 아니라 요약과 링크만 반영한다.
- `Docs/05_WorkLogs/issue-pr-index.md`의 Issue/PR/Plan comment 상태를 갱신한다.

## WorkLog 반영

WorkLog에는 GitHub 본문 전체가 아니라 다음만 남긴다.

- 작업 범위
- 갱신한 정본 문서 링크
- 검증 요약
- 게시한 Issue/PR 번호 또는 예정 상태
- 리뷰 대응과 follow-up

## 운영 기준

- Issue/PR 생성은 사용자가 명시적으로 요청한 경우에만 진행한다.
- 게시 전 본문은 local에서 검토한다.
- 게시 전 후보는 `Metadata`, 내부 메모, draft 문구, 존댓말을 제거한다.
- 게시 후 실제 게시본과 리뷰 대응 기록은 `local/github/snapshots`에 둔다.
- merge 후 최종 상태는 각 정본 문서에 반영한다.
