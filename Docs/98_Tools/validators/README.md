# Validators

이 폴더는 반복 실행 가능한 tracked validator script를 둔다. 정책 정본은 `Docs/06_Policies`에 두고, 이 폴더에는 실행 파일과 사용법만 둔다.

## Script 목록

| Script | 목적 | 입력 |
| --- | --- | --- |
| `validate-github-body.ps1` | GitHub Issue/PR/comment 게시 전 Markdown body 검사 | `local/github/public` |

## 사용법

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
```

기본 입력 위치는 `local/github/public`이다. 다른 위치를 검사할 때는 `-PublicRoot`를 지정한다.

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1 -PublicRoot local/github/public
```

## 검사 기준

- GitHub 게시 전 body에 draft/local-only 경로가 남아 있지 않은지 확인한다.
- 필수 섹션이 빠지지 않았는지 확인한다.
- GitHub body가 한국어 섹션 기준을 따르는지 확인한다.
- screenshot Markdown이 `Docs/_assets/captures`를 가리키는지 확인한다.
- template에 특정 Issue 번호가 하드코딩되어 있지 않은지 확인한다.

## 지원 범위

현재 validator는 `local/github/public` 아래의 다음 Markdown을 검사한다.

| 위치 | 검사 |
| --- | --- |
| `prs/**/*.md` | PR body |
| `issues/topic/*.md` | Topic issue |
| `issues/verification/*.md` | Verification issue |
| `issues/plan-comments/plan_progress_summary_comment.md` | Plan Issue 첫 누적 진행 댓글 |
| `issues/plan-comments/*_worklog_comment.md` | Work Unit 또는 PR 마감 댓글 |
| `pr-comments/*.md` | PR screenshot 또는 Demo evidence comment |

## Plan comment schema

Plan Issue 관련 public body는 두 종류만 검사한다.

| 파일 | 책임 | 주요 검사 |
| --- | --- | --- |
| `issues/plan-comments/plan_progress_summary_comment.md` | 전체 진행판 | `## Graphics Study 진행 요약`, `## 완료`, `## 진행 예정`, `## Related PRs` 구조와 Phase heading |
| `issues/plan-comments/*_worklog_comment.md` | Work Unit 마감 기록 | `## Phase <n-n> progress record`, 완료 내용, 검증, 남은 제한, 관련 PR |

Plan comment는 Docs 정본을 복제하지 않고 진행 상태와 링크만 요약한다. 상세 정책은 `Docs/06_Policies/github-workflow-policy.md`를 따른다.

## 검사하지 않는 것

- `draft`에서 `public`으로 복사했는지 여부
- GitHub 게시 승인 여부
- 실제 `gh` 게시 여부
- `local/github/snapshots` 생성 여부
- `Docs/04_WorkLogs`와 `issue-pr-index.md` 동기화 여부
- build/run/capture 실제 성공 여부

## 주의

- validator 통과는 GitHub 게시 승인이 아니다.
- `git push`, `gh issue create`, `gh pr create`, Ready for Review 전환은 사용자 승인 후 진행한다.
- local draft 원문은 이 폴더에 두지 않는다.
