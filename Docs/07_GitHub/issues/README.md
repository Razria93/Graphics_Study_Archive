# Issue Bodies

이 폴더는 GitHub Issue body 후보를 둔다.

## 기본 원칙

기본 Issue는 Progress Issue 1개다. Work Unit Issue는 기본 객체가 아니다. Topic, Demo, Verification Issue는 독립 추적 가치가 있을 때만 선택적으로 만든다.

| 유형 | 파일명 | 생성 기준 |
| --- | --- | --- |
| Progress Issue | `progress-plan.md` | 전체 목표, Phase 범위, 완료 조건을 상위 진행판으로 추적할 때 |
| Work Unit Issue | `work-unit_*.md` | Progress Issue 댓글과 Chapter PR만으로 추적하기 어려운 독립 Work Unit이 있을 때 |
| Topic Issue | `topic_*.md` | 여러 Chapter를 관통하는 개념 문서가 독립 작업일 때 |
| Verification Issue | `verification_*.md` | build/run 실패, 환경 문제, 미확인 묶음이 별도 추적 대상일 때 |
| Demo Issue | 필요 시 별도 결정 | screenshot, video, result image 제작이나 승인 범위가 별도 작업일 때 |

PR 자체를 위한 별도 Issue는 기본으로 만들지 않는다. PR 상태는 `Docs/04_WorkLogs/work-unit-github-index.md`와 Progress Issue 댓글에서 추적한다.

## Progress Issue

Progress Issue는 전체 목표, Phase 범위, 완료 조건, 게시 단위 책임을 관리한다. 상세 내용은 Docs 정본으로 위임하고, Issue에는 요약과 링크만 둔다.

Issue body 후보는 첫 H1을 title source로 유지한다. 실제 `gh issue create --title ... --body-file ...` 직전에는 첫 H1을 제외한 임시 body 파일을 `local/` 아래에 따로 만든다. tracked 후보 원본은 수정하지 않는다.

반복 작성용 템플릿은 `../../98_Tools/templates/progress-issue.md`를 따른다.

## Work Unit Issue

Work Unit Issue는 작업 범위와 완료 조건을 GitHub에서 추적해야 할 때만 만든다. Docs 정본을 복제하지 않고, 범위와 검증 기준, 완료 조건, 관련 문서 링크만 둔다.

반복 작성용 템플릿은 `../../98_Tools/templates/work-unit-issue.md`를 따른다. 게시 전 검사는 `../../98_Tools/validators/validate-github-body.ps1`를 사용한다.
