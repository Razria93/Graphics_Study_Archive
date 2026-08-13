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

- 작업 PR review, finalization 또는 merge가 남아 있는 Work Unit은 `진행 중`으로 둔다.
- `검증 중`은 build/run/capture를 실제로 확인하는 기간에만 사용한다.
- 작업 PR review 완료와 finalization 진행 승인 후 같은 작업 branch의 finalization commit에서 최종 WorkLog와 Index, `마감` 전환을 준비한다.
- Finalization commit의 validator와 review 상태를 다시 확인하고 최신 PR HEAD에 대한 merge 실행 승인을 다시 받은 뒤 merge한다.
- Finalization commit을 포함한 PR이 기본 branch에 merge되면 Work Unit의 `마감` 상태가 정본에 반영된다.
- 여러 작업 PR 종합이나 post-merge 정리가 필요한 경우에만 별도 closeout branch와 PR을 사용한다.
- 예외 closeout PR은 별도 Work Unit으로 등록하거나 추가 closeout 대상으로 삼지 않는다.
- 상세 완료 조건과 GitHub 절차는 `../06_Policies/work-unit-workflow-policy.md`와 `../06_Policies/github-workflow-policy.md`를 따른다.

## 작성 기준

- WorkLog는 최신 상태표가 아니라 마감 시점 snapshot이다.
- build/run/capture 상세는 `Docs/02_Verification`에 둔다.
- demo capture/result 최신 상태는 `Docs/03_Demos`에 둔다.
- public 후보와 제외 판단은 `Docs/05_Publication`에 둔다.
- GitHub 게시 본문은 `Docs/07_GitHub`에 둔다.
- source review 상세와 raw/origin 비교표는 `local/study-review`에 둔다.

## 문체

- 평서형 현재형을 사용한다.
- 존댓말, 대화체, 감상문체를 사용하지 않는다.
- technical keywords, folder names, Issue/PR identifiers는 영어를 유지한다.
