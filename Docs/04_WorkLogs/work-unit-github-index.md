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
| 상위 Progress Issue | posted | #7 | `Docs/07_GitHub/plan/plan-body.md` | 전체 진행판으로 유지 |
| 누적 진행 댓글 | posted | #7 comment 5091068690 | `Docs/07_GitHub/plan/plan-progress.md` | Phase 5-3까지 게시 · 최신 상태 보완 후보 |

## 관계 Index

| Work Unit | Chapter/Bundle 완료 댓글 | 선택 Issue | Chapter PR 목록 | 관련 WorkLog | 비고 |
| --- | --- | --- | --- | --- | --- |
| `WU-Part1` | posted (Phase 2-1, Phase 2-4) | Demo Issue #9, #12 | PR #8, PR #11 (merged) | [WU-Part1](work-units/WU-Part1.md) | Chapter01-02와 Chapter03은 마감했다. `Portfolio_GraphicsLab/Rendering/RayTracing` 연계가 남아 있어 WU-Part1 전체는 진행 중이다. |
| `WU-Part2` | posted (Phase 3-1, Phase 3-2) | Demo Issue #14, #17, #18, #19, #22 | PR #15, PR #20 (merged) | [WU-Part2](work-units/WU-Part2.md) | Chapter04와 Chapter05–08 게시·merge를 마감했다. |
| `WU-Part3` | posted (Phase 4-1, Phase 4-2) | Demo Issue #21, #25, #26, #27, #28 | PR #23, PR #24 (merged) | [WU-Part3](work-units/WU-Part3.md) | Chapter09와 Chapter10–13 게시·merge를 마감했다. |
| `WU-Part4` | posted (Phase 5-1, Phase 5-2, Phase 5-3) | Demo Issue #29, #31, #33–#37 | PR #30, PR #32, PR #38 (merged) | [WU-Part4](work-units/WU-Part4.md) | Chapter14부터 Chapter20까지 GitHub body closeout과 PR merge를 마감했다. selected video comment는 후속 작업이다. |
| `WU-Publication` | 예정 | 기본 제외 | 예정 | 없음 | 별도 승인 범위가 생기면 선택 Issue를 생성한다. |
| `WU-StructureCleanup` | 제외 | 제외 | PR #6 (posted) | [WU-StructureCleanup](work-units/WU-StructureCleanup.md) | 정책 도입 이전 구조 정리 PR이라 완료 댓글을 예외로 둔다. |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `예정` | 아직 초안 없음 |
| `draft` | `local/`에 임시 초안 있음 |
| `ready` | `Docs/07_GitHub`에 게시 후보 있음 |
| `comment-ready` | Progress comment 또는 completion comment 게시 후보가 `Docs/07_GitHub`에 있음 |
| `posted` | GitHub remote에 게시됨 |
| `snapshot` | 게시 후 사본이 `local/` 하위 snapshot으로 있음 |
| `기본 제외` | Progress Issue 댓글과 Chapter PR로 추적하며 선택 Issue는 만들지 않음 |
| `제외` | Issue/PR/comment로 만들지 않음 |
