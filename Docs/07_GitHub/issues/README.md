# Issue Bodies

이 폴더는 선택 Issue body 후보를 둔다. Progress Issue 정본은 `../plan`에서 관리한다.

## 하위 폴더

| 폴더 | 파일명 규칙 | 생성 기준 |
| --- | --- | --- |
| `work-unit` | `work-unit_<slug>.md` | Progress 댓글과 Chapter PR만으로 추적하기 어려운 독립 Work Unit이 있을 때 |
| `verification` | `verification_<slug>.md` | build/run 실패, 환경 문제, 미확인 묶음이 별도 추적 대상일 때 |
| `demo` | `demo_<slug>.md` | screenshot, video, result image 제작이나 승인 범위가 별도 작업일 때 |

PR 자체를 위한 별도 Issue는 기본으로 만들지 않는다. PR 상태는 `Docs/04_WorkLogs/work-unit-github-index.md`와 `../plan/plan-progress.md`에서 추적한다.

## 작성 원칙

- Issue body 후보는 첫 H1을 title source로 유지한다.
- 실제 `gh issue create`에서는 title을 H1에서 사용하고 remote body에서 첫 H1과
  바로 뒤 빈 줄을 제거한다.
- Docs 정본 원문을 복제하지 않고 범위, 완료 조건, 관련 링크만 둔다.

반복 작성용 템플릿은 `../../98_Tools/templates/work-unit-issue.md`를 따른다. 게시 전 검사는 `../../98_Tools/validators/validate-github-body.ps1`를 사용한다.
