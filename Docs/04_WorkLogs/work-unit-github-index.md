# Work Unit GitHub Index

이 문서는 Work Unit과 GitHub Issue/PR draft 또는 게시 상태의 연결을 기록한다.

## 책임

- Issue/PR/comment 게시 후보 정본은 `Docs/07_GitHub`에 둔다.
- `local/`은 임시 초안과 게시 후 snapshot을 둘 수 있는 작업 공간으로만 사용한다.
- 이 문서에는 게시 여부, 번호, 연결 WorkLog만 요약한다.
- Progress Issue는 전체 진행판으로 하나만 운영하고, Work Unit별 Chapter/Bundle 완료 댓글 상태만 연결한다.
- 사용자가 명시적으로 요청하기 전에는 GitHub Issue/PR/comment를 생성하거나 수정하지 않는다.

## Progress Issue 연결

| 항목 | 상태 | GitHub 번호 | 게시 후보 파일 | 비고 |
| --- | --- | --- | --- | --- |
| 상위 Progress Issue | posted | [Issue #7](https://github.com/Razria93/Graphics_Study_Archive/issues/7) | `Docs/07_GitHub/plan/plan-body.md` | GitHub remote에 게시됨 |
| 누적 진행 댓글 | posted | [댓글 5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690) | `Docs/07_GitHub/plan/plan-progress.md` | 게시 후 tracked 후보와 동기화 |

## 관계 Index

| Work Unit | Chapter/Bundle 완료 댓글 | Work Unit Issue | Demo Issue remote | 로컬 Demo Issue 후보 | Remote PR | 로컬 PR 후보 | 관련 WorkLog | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `WU-Part1` | [댓글 5091227284](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091227284) (`posted`; `Docs/07_GitHub/plan/comments/phase-2-1-plan-comment.md`) | 제외 | [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9) (`posted`) | `Docs/07_GitHub/issues/demo/demo_part1_chapter01-02.md` (`ready`) | [PR #8](https://github.com/Razria93/Graphics_Study_Archive/pull/8) (`Merged`; [`e14f5e3`](https://github.com/Razria93/Graphics_Study_Archive/commit/e14f5e39d1352fb4f1f55bd6b06fb1e9840cb88c)) | `Docs/07_GitHub/prs/part1_chapter01-02.md` (`ready`) | [WU-Part1](work-units/WU-Part1.md) | WU-Part1의 일부 범위인 Chapter01-02 파일럿 완료 기록이다. WU-Part1 전체 완료가 아니다. |
| `WU-Part2` | 예정 | 기본 제외 | 없음 | 예정 | 없음 | 예정 | 없음 | 독립 작업이 생기면 선택 Issue 생성 여부를 판단한다. |
| `WU-Part3` | 예정 | 기본 제외 | 없음 | 예정 | 없음 | 예정 | 없음 | 독립 작업이 생기면 선택 Issue 생성 여부를 판단한다. |
| `WU-Part4` | 예정 | 기본 제외 | 없음 | 예정 | 없음 | 예정 | 없음 | 독립 작업이 생기면 선택 Issue 생성 여부를 판단한다. |
| `WU-Publication` | 예정 | 기본 제외 | 없음 | 예정 | 없음 | 예정 | 없음 | 별도 승인 범위가 생기면 선택 Issue를 생성한다. |
| `WU-StructureCleanup` | 제외 | 제외 | 없음 | 없음 | PR #6 (`posted`) | 없음 | [WU-StructureCleanup](work-units/WU-StructureCleanup.md) | 정책 도입 이전 구조 정리 PR이라 완료 댓글을 예외로 둔다. |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `예정` | 아직 초안 없음 |
| `draft` | `local/`에 임시 초안 있음 |
| `ready` | `Docs/07_GitHub`에 게시 후보 있음 |
| `comment-ready` | Progress comment 또는 completion comment 게시 후보가 `Docs/07_GitHub`에 있음 |
| `posted` | GitHub remote에 게시됨 |
| `snapshot` | 게시 후 사본이 `local/` 하위 snapshot으로 있음 |
| `Draft` | GitHub remote에 Draft PR로 존재함 |
| `Merged` | GitHub remote에서 일반 merge commit 방식으로 병합됨 |
| `기본 제외` | Progress Issue 댓글과 Chapter PR로 추적하며 선택 Issue는 만들지 않음 |
| `제외` | Issue/PR/comment로 만들지 않음 |
