# Issue PR Index

이 문서는 Work Unit과 GitHub Issue/PR draft 또는 게시 상태의 연결을 기록한다.

## 책임

- Issue/PR 본문 원문은 `local/github`에 둔다.
- 이 문서에는 게시 여부, 번호, 연결 WorkLog만 요약한다.
- Plan Issue는 전체 진행판으로 하나만 운영하고, Work Unit별 댓글 상태만 연결한다.
- 사용자가 명시적으로 요청하기 전에는 GitHub Issue/PR/comment를 생성하거나 수정하지 않는다.

## Plan Issue 연결

| 항목 | 상태 | GitHub 번호 | local public 파일 | 비고 |
| --- | --- | --- | --- | --- |
| 상위 Plan Issue | 예정 | 없음 | 없음 | 전체 진행판 생성 여부 사용자 승인 필요 |
| 누적 진행 댓글 | 예정 | 없음 | `local/github/public/issues/plan-comments/plan_progress_summary_comment.md` | Plan Issue 생성 후 작성 |

## Index

| Work Unit | Issue 상태 | PR 상태 | Plan 댓글 상태 | GitHub 번호 | 관련 WorkLog | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| `WU-Part1` | 예정 | 예정 | 예정 | 없음 | [WU-Part1](WU-Part1.md) |  |
| `WU-Part2` | 예정 | 예정 | 예정 | 없음 | [WU-Part2](WU-Part2.md) |  |
| `WU-Part3` | 예정 | 예정 | 예정 | 없음 | [WU-Part3](WU-Part3.md) |  |
| `WU-Part4` | 예정 | 예정 | 예정 | 없음 | [WU-Part4](WU-Part4.md) |  |
| `WU-Publication` | 예정 | 예정 | 예정 | 없음 | [WU-Publication](WU-Publication.md) | public subset 확정 후 판단 |
| `WU-StructureCleanup` | 예정 | posted | 예정 | PR #6 | [WU-StructureCleanup](WU-StructureCleanup.md) | draft PR 생성 완료 |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `예정` | 아직 초안 없음 |
| `draft` | `local/github/draft`에 초안 있음 |
| `public-ready` | `local/github/public`에 게시 후보 있음 |
| `comment-ready` | Plan comment 또는 PR comment 게시 후보가 `local/github/public`에 있음 |
| `posted` | GitHub remote에 게시됨 |
| `snapshot` | 게시 후 사본이 `local/github/snapshots`에 있음 |
| `제외` | Issue/PR/comment로 만들지 않음 |
