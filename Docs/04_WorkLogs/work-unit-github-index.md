# Work Unit GitHub Index

이 문서는 Work Unit과 안정적인 GitHub 객체, tracked 게시 payload의 연결을 기록한다. GitHub의 live 상태와 comment ID·URL을 복제하지 않는다.

## 책임

- Work Unit과 관련 PR·Issue 번호를 연결한다.
- Pre-merge finalization에서 사용할 Progress payload 경로와 필요 여부를 기록한다.
- 실제 merge, 게시 여부, comment ID·URL과 게시 시각은 GitHub remote에 위임한다.
- Remote 게시 결과를 반영하기 위한 tracked 수정이나 후속 PR을 만들지 않는다.

## Progress 연결

| 대상 | GitHub 객체 | Tracked payload | 용도 |
| --- | --- | --- | --- |
| 상위 진행판 | Progress Issue #7 | `Docs/07_GitHub/plan/plan-body.md` | 전체 목표와 운영 범위 |
| 누적 진행 댓글 | Issue #7 기존 누적 댓글 | `Docs/07_GitHub/plan/plan-progress.md` | 완료와 예정 Work Unit의 public dashboard |

## Work Unit 연결

| Work Unit | 관련 PR·Issue | 완료 payload | 관련 WorkLog | 비고 |
| --- | --- | --- | --- | --- |
| `WU-Part1` | PR #8, #10, #11 · Demo Issue #9, #12 | Phase 2-1·2-4 완료 댓글 | [WU-Part1](work-units/WU-Part1.md) | Chapter01-03 마감, GraphicsLab Part1 reconstruction 진행 중 |
| `WU-GraphicsLab-Architecture` | PR #40, #41, #42 | `Docs/07_GitHub/plan/comments/phase-2-5-plan-comment.md` | [WU-GraphicsLab-Architecture](work-units/WU-GraphicsLab-Architecture.md) | GraphicsLab scaffold, reconstruction 전략과 WU-A0 architecture 마감 |
| `WU-Part2` | PR #15, #20 · Demo Issue #14, #17-#19, #22 | Phase 3-1·3-2 완료 댓글 | [WU-Part2](work-units/WU-Part2.md) | Chapter04-08 마감 |
| `WU-Part3` | PR #23, #24 · Demo Issue #21, #25-#28 | Phase 4-1·4-2 완료 댓글 | [WU-Part3](work-units/WU-Part3.md) | Chapter09-13 마감 |
| `WU-Part4` | PR #30, #32, #38 · Demo Issue #29, #31, #33-#37 | Phase 5-1·5-3 완료 댓글 | [WU-Part4](work-units/WU-Part4.md) | Chapter14-20 마감, selected video는 별도 범위 |
| `WU-Publication` | 필요할 때 확정 | 의도적 제외 | 없음 | public repo 생성 전 수행 |
| `WU-StructureCleanup` | PR #6 | 의도적 제외 | [WU-StructureCleanup](work-units/WU-StructureCleanup.md) | 정책 도입 이전 구조 정리 |
