# Plan Bodies

이 폴더는 Progress 운영 관련 GitHub body 정본을 둔다.

## 파일

| 파일 | 책임 |
| --- | --- |
| `plan-body.md` | Progress Issue 본문 정본 |
| `plan-progress.md` | Progress 누적 진행 댓글 정본 |
| `comments/*.md` | PR 마감 시 추가하는 Phase plan comment 정본 |

## 운영 규칙

- Progress Issue 본문은 `plan-body.md` 1개를 유지한다.
- 누적 진행 댓글은 `plan-progress.md` 1개를 유지한다.
- PR 하나가 마감될 때마다 `plan-progress.md`를 갱신한다.
- PR 하나가 마감될 때마다 `comments/`에 plan comment를 1개 추가해 Progress Issue comment로 게시한다.
- plan comment 파일명은 `phase-<n>-<m>-plan-comment.md` 패턴을 사용한다.

## 작성 원칙

- `plan-body.md`는 공개 가능한 상위 목표와 운영 기준만 유지한다.
- 내부 운영 상세, 긴 체크리스트, 공개 필요가 낮은 상세 단계는 `Docs/06_Policies` 또는 WorkLog에 둔다.
- `plan-progress.md`와 plan comment는 가시성을 우선해 짧은 bullet과 관련 PR 링크 중심으로 작성한다.

## 게시 규칙

- `gh issue create`와 `gh issue edit`에서 title은 `plan-body.md`의 H1을 사용한다.
- `gh issue comment`에서는 `plan-progress.md` 또는 `comments/*.md`를 body 파일로 사용한다.
- remote 게시/수정은 사용자 승인 후에만 진행한다.
- 게시 전 validator를 실행한다.
