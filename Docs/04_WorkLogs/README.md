# Work Logs

이 폴더는 Work Unit의 작업 결정과 마감 snapshot을 기록하는 위치다. Example, Topic, Verification, Demo, Publication 문서의 본문을 대체하지 않고, 어떤 정본 문서를 갱신했는지 추적한다.

WorkLog의 검증, demo, publication 요약은 마감 당시 상태를 압축한 snapshot이다. 최신 상태 정본은 `Docs/02_Verification`, `Docs/03_Demos`, `Docs/05_Publication`, `Docs/07_GitHub`에 둔다.

## 책임

- Work Unit 단위의 작업 범위와 변경 요약을 기록한다.
- 갱신한 Example, Topic, Verification, Demo, Publication 문서를 링크한다.
- 검증, 미확인 항목, known issue, follow-up은 마감 시점 snapshot으로만 남긴다.
- 최신 검증, demo, publication 상태는 각 정본 문서로 연결한다.
- GitHub Issue/PR 상태 연결을 둔다.
- GitHub 게시 후보 정본은 `Docs/07_GitHub`에 둔다.
- WorkLog는 GitHub 게시물이 아니다.
- WorkLog는 Chapter/Bundle 완료 댓글과 PR body의 입력 자료다.
- WorkLog 원문을 GitHub Issue나 댓글에 그대로 복제하지 않는다.

## 문서 목록

| 문서 | 책임 |
| --- | --- |
| [Work Unit Index](work-unit-index.md) | Work Unit 목록과 상태 |
| [Work Unit GitHub Index](work-unit-github-index.md) | Work Unit과 Issue/PR/comment 게시 상태 연결 |
| [active](active/) | 진행 중 Work Unit 기록 |
| [completed](completed/) | 마감된 Work Unit snapshot |
| [decisions](decisions/) | 구조 전환과 정책성 결정 기록 |
| [study-review-summaries](study-review-summaries/) | local study review에서 승격한 반복 판단 요약 |

## WorkLog에 남길 것

- 작업 범위
- 작업 중 확정한 주요 결정
- 갱신한 정본 문서 링크와 위임한 책임
- 검증, demo, publication의 마감 시점 snapshot
- Issue/PR 번호 또는 예정 상태
- follow-up

## WorkLog에 남기지 않을 것

- 예제 구현 설명 전문
- Topic 개념 설명 전문
- build/run 상세 로그 전문
- capture/result 파일 경로와 최신 상태표
- publication 판단 상세
- GitHub draft 본문 전문
- source review 상세와 raw/origin 비교표
- raw/reference 원문과 개인 메모
