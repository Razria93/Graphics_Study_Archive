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
| 누적 진행 댓글 | posted | [댓글 5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690) | `Docs/07_GitHub/plan/plan-progress.md` | Remote는 Phase 5-1 게시 상태이며 local body는 Phase 5-2 후보를 포함한다. |

## 관계 Index

| Work Unit | Chapter/Bundle 완료 댓글 | Work Unit Issue | Demo Issue remote | 로컬 Demo Issue 후보 | Remote PR | 로컬 PR 후보 | 관련 WorkLog | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `WU-Part1` | [댓글 5091227284](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091227284) (`posted`; `Docs/07_GitHub/plan/comments/phase-2-1-plan-comment.md`) | 제외 | [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9) (`posted`) | `Docs/07_GitHub/issues/demo/demo_part1_chapter01-02.md` (`ready`) | [PR #8](https://github.com/Razria93/Graphics_Study_Archive/pull/8) (`Merged`; [`e14f5e3`](https://github.com/Razria93/Graphics_Study_Archive/commit/e14f5e39d1352fb4f1f55bd6b06fb1e9840cb88c)) | `Docs/07_GitHub/prs/part1_chapter01-02.md` (`ready`) | [WU-Part1](work-units/WU-Part1.md) | WU-Part1의 일부 범위인 Chapter01-02 파일럿 완료 기록이다. WU-Part1 전체 완료가 아니다. |
| `WU-Part1 / Chapter03` | [댓글 5142322616](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5142322616) (`posted`; `Docs/07_GitHub/plan/comments/phase-2-4-plan-comment.md`) | 제외 | [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12) (`posted`) | `Docs/07_GitHub/issues/demo/demo_part1_chapter03.md` (`ready`) | [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11) (`Merged`; [`eeb7897`](https://github.com/Razria93/Graphics_Study_Archive/commit/eeb7897142c30bfc5fa8479b03548cf9351c6968)) | `Docs/07_GitHub/prs/part1_chapter03.md` (`ready`) | [WU-Part1](work-units/WU-Part1.md) | Phase 2-4 Chapter03 PR, Demo Issue와 Progress 게시를 마감했다. 교정 기록은 [PR #13](https://github.com/Razria93/Graphics_Study_Archive/pull/13)에 둔다. |
| `WU-Part2` | 예정 | 기본 제외 | 없음 | 예정 | 없음 | 예정 | [WU-Part2](work-units/WU-Part2.md) | Chapter04와 Chapter05-08의 Chapter별 게시 상태를 하위 행에서 관리한다. |
| `WU-Part2 / Chapter04` | [댓글 5150875726](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5150875726) (`posted`; `Docs/07_GitHub/plan/comments/phase-3-1-plan-comment.md`) | 기본 제외 | [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14) · [video 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/14#issuecomment-5168469025) (`posted`) | `Docs/07_GitHub/issues/demo/demo_part2_chapter04.md` (`ready`) | [PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15) (`Merged`) | `Docs/07_GitHub/prs/part2_chapter04.md` (`ready`) | [WU-Part2](work-units/WU-Part2.md) | 본문은 정적 visual 3개, 동적 결과는 전용 video 댓글로 마감했다. |
| `WU-Part2 / Chapter05-08` | [댓글 5160239752](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5160239752) (`posted`; `Docs/07_GitHub/plan/comments/phase-3-2-plan-comment.md`) | 기본 제외 | [#17](https://github.com/Razria93/Graphics_Study_Archive/issues/17) · [#18](https://github.com/Razria93/Graphics_Study_Archive/issues/18) · [#19](https://github.com/Razria93/Graphics_Study_Archive/issues/19) · [#22](https://github.com/Razria93/Graphics_Study_Archive/issues/22) (`posted`) | Chapter05·06·07·08 후보 4개 (`ready`) | [PR #20](https://github.com/Razria93/Graphics_Study_Archive/pull/20) (`Merged`) | `Docs/07_GitHub/prs/part2_chapter05-08.md` (`ready`) | [WU-Part2](work-units/WU-Part2.md) | Chapter08 Step1·6·7 rendered evidence를 Issue #22에 게시하고 selected video 댓글은 미게시로 유지한다. |
| `WU-Part3` | 하위 Chapter 행에서 관리 | 기본 제외 | 하위 Chapter 행에서 관리 | 하위 Chapter 행에서 관리 | 하위 Chapter 행에서 관리 | 하위 Chapter 행에서 관리 | [WU-Part3](work-units/WU-Part3.md) | Chapter09와 Chapter10-13의 게시·PR merge를 모두 마감했다. |
| `WU-Part3 / Chapter09` | Chapter09 로컬 정규화 완료 | 기본 제외 | [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) (`posted`) | `Docs/07_GitHub/issues/demo/demo_part3_chapter09.md` (`ready`) | [PR #23](https://github.com/Razria93/Graphics_Study_Archive/pull/23) (`Merged`; [`3467f09`](https://github.com/Razria93/Graphics_Study_Archive/commit/3467f0961c9717998cf4fab76112d01e88680d0a)) | `Docs/07_GitHub/prs/part3_chapter09.md` (`ready`) | [WU-Part3](work-units/WU-Part3.md) | Step5·1·6 rendered evidence와 [Step5 video 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305)을 게시하고 PR review 대응을 마감했다. |
| `WU-Part3 / Chapter10-13` | [댓글 5189162548](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5189162548) (`posted`; `Docs/07_GitHub/plan/comments/phase-4-2-plan-comment.md`) | 기본 제외 | [#25](https://github.com/Razria93/Graphics_Study_Archive/issues/25) · [#26](https://github.com/Razria93/Graphics_Study_Archive/issues/26) · [#27](https://github.com/Razria93/Graphics_Study_Archive/issues/27) · [#28](https://github.com/Razria93/Graphics_Study_Archive/issues/28) (`posted`) | Chapter10·11·12·13 후보 4개 (`ready`) | [PR #24](https://github.com/Razria93/Graphics_Study_Archive/pull/24) (`Merged`; [`75d1c71`](https://github.com/Razria93/Graphics_Study_Archive/commit/75d1c715d90a2e031680f2f30a586eb54674ae5b)) | `Docs/07_GitHub/prs/part3_chapter10-13.md` (`ready`) | [WU-Part3](work-units/WU-Part3.md) | Demo Issues #25-#28, 누적 Progress comment와 Phase 4-2 완료 댓글을 게시하고 일반 merge commit으로 PR #24를 마감했다. |
| `WU-Part4` | 하위 Chapter 행에서 관리 | 기본 제외 | 하위 Chapter 행에서 관리 | 하위 Chapter 행에서 관리 | 하위 Chapter 행에서 관리 | 하위 Chapter 행에서 관리 | [WU-Part4](work-units/WU-Part4.md) | Chapter14부터 Chapter별 게시 후보와 PR 상태를 하위 행에서 관리한다. |
| `WU-Part4 / Chapter14` | [댓글 5196232081](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5196232081) (`posted`; `Docs/07_GitHub/plan/comments/phase-5-1-plan-comment.md`) | 기본 제외 | [Demo Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) (`posted`) | `Docs/07_GitHub/issues/demo/demo_part4_chapter14.md` (`ready`) | [PR #30](https://github.com/Razria93/Graphics_Study_Archive/pull/30) (`Merged`) | `Docs/07_GitHub/prs/part4_chapter14.md` (`ready`) | [WU-Part4](work-units/WU-Part4.md) | Demo Issue #29, 누적 Progress comment, Phase 5-1 완료 댓글과 PR #30을 게시했다. 리뷰 지적사항 대응 commit, thread 응답과 merge를 마감했다. |
| `WU-Part4 / Chapter15` | `Docs/07_GitHub/plan/comments/phase-5-2-plan-comment.md` (`comment-ready`) | 기본 제외 | 없음 | `Docs/07_GitHub/issues/demo/demo_part4_chapter15.md` (`ready`) | 없음 | 예정 | [WU-Part4](work-units/WU-Part4.md) | Ex1501과 10초 지연 Ex1503 tracked capture를 Chapter15 Demo Issue body에 연결했다. Ex1502는 `flare0.dds` provenance 확인 전까지 보류로 둔다. |
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
| `Ready for Review` | GitHub remote에서 review 가능한 PR로 존재함 |
| `Merged` | GitHub remote에서 일반 merge commit 방식으로 병합됨 |
| `기본 제외` | Progress Issue 댓글과 Chapter PR로 추적하며 선택 Issue는 만들지 않음 |
| `제외` | Issue/PR/comment로 만들지 않음 |
