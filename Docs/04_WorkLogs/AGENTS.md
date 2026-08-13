# Work Logs Guidelines

## 적용 범위

이 규칙은 `Docs/04_WorkLogs/` 아래 문서에 적용한다.

## 책임

- Work Unit의 작업 범위, 결정 요약, 마감 snapshot, follow-up을 기록한다.
- Example, Topic, Verification, Demo, Publication의 정본 문서로 링크한다.
- 최신 상태 정본을 반복하지 않고 해당 정본 문서로 위임한다.
- Issue/PR 상태 연결을 제공한다.
- GitHub 게시 본문 원문, raw/reference 원문, 개인 메모는 이 폴더에 두지 않는다.

## 작성 단위

- 전체 목록은 `work-unit-index.md`에 둔다.
- Issue/PR 연결은 `work-unit-github-index.md`에 둔다.
- 진행 상태와 관계없이 Work Unit 기록은 `work-units/WU-*.md`에 둔다.
- 진행/마감 상태는 `work-unit-index.md`에서 관리하고 파일 경로로 중복 표현하지 않는다.
- 구조 결정 기록은 `decisions/`에 둔다.
- local study review와 PR review에서 승격한 재사용 가능한 판단 요약은 `reviews/`에 둔다.
- GitHub 게시 후보 정본은 `Docs/07_GitHub`에 둔다.
- `local/github/draft`는 임시 초안으로만 사용한다.

## 상태 전환

- 작업과 review 중인 기본 branch의 Work Unit은 `진행 중`으로 둔다.
- `검증 중`은 build/run/capture를 실제로 확인하는 기간에만 사용한다.
- 같은 작업 branch의 pre-merge finalization에서 WorkLog, Index와 `마감` 상태를 merge 후 관점으로 완성한다.
- Finalization tree가 기본 branch에 merge되면 `마감` 상태가 정본으로 효력을 가진다.
- Merge 후에는 준비된 Progress payload만 remote에 동기화하고 tracked 문서를 다시 수정하지 않는다.
- 상세 완료 조건과 GitHub 절차는 `../06_Policies/work-unit-workflow-policy.md`와 `../06_Policies/github-workflow-policy.md`를 따른다.

## 작성 기준

- WorkLog는 live remote 상태표가 아니라 merge될 마감 snapshot이다.
- build/run/capture 상세는 `Docs/02_Verification`에 둔다.
- demo capture/result 최신 상태는 `Docs/03_Demos`에 둔다.
- public 후보와 제외 판단은 `Docs/05_Publication`에 둔다.
- GitHub 게시 본문은 `Docs/07_GitHub`에 둔다.
- source review 상세와 raw/origin 비교표는 `local/study-review`에 둔다.

## 문체

- 평서형 현재형을 사용한다.
- 존댓말, 대화체, 감상문체를 사용하지 않는다.
- technical keywords, folder names, Issue/PR identifiers는 영어를 유지한다.
