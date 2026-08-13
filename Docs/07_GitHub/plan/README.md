# Plan Bodies

이 폴더는 Progress 운영 관련 GitHub body 정본을 둔다.

## 파일

| 파일 | 책임 |
| --- | --- |
| `plan-body.md` | Progress Issue 본문 정본 |
| `plan-progress.md` | Progress 누적 진행 댓글 정본 |
| `comments/*.md` | 의미 있는 Phase, Chapter 묶음 또는 Work Unit 완료 댓글 payload |

## 운영 규칙

- Progress Issue 본문은 `plan-body.md` 1개를 유지한다.
- 누적 진행 댓글은 `plan-progress.md` 1개를 유지한다.
- 의미 있는 Phase, Chapter 묶음 또는 Work Unit이 마감될 때 `plan-progress.md`를 갱신한다.
- 같은 마감 단위에는 완료 댓글 payload를 최대 1개 작성하며 여러 관련 PR을 하나로 묶을 수 있다.
- plan comment 파일명은 `phase-<n>-<m>-plan-comment.md` 패턴을 사용한다.

## 작성 원칙

- `plan-body.md`는 공개 가능한 상위 목표와 운영 기준만 유지한다.
- 내부 운영 상세, 긴 체크리스트, 공개 필요가 낮은 상세 단계는 `Docs/06_Policies` 또는 WorkLog에 둔다.
- `plan-progress.md`와 plan comment는 가시성을 우선해 짧은 bullet과 관련 PR 링크 중심으로 작성한다.
- 이 폴더의 문서는 remote 게시 payload이며 실제 게시 여부, comment ID·URL과 게시 시각의 정본이 아니다.

## 게시 규칙

- `gh issue create`와 `gh issue edit`에서 title은 `plan-body.md`의 H1을 사용한다.
- `gh issue comment`에서는 `plan-progress.md` 또는 `comments/*.md`를 body 파일로 사용한다.
- remote 게시/수정은 사용자 승인 후에만 진행한다.
- 게시 전 validator를 실행한다.
- Merge 후에는 finalization에서 준비한 payload를 그대로 게시하고 결과를 tracked 문서에 역동기화하지 않는다.
