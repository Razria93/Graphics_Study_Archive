# Issue And PR Policy

이 문서는 GitHub Issue와 PR 운영 기준을 정의한다.

## 책임 경계

| 항목 | 정본 위치 |
| --- | --- |
| 작업 흐름 기준 | `Docs/07_Policies/work-unit-workflow-policy.md` |
| 작업 마감 요약 | `Docs/05_WorkLogs` |
| GitHub 초안 | `local/github/draft` |
| GitHub 게시 전 후보 | `local/github/public` |
| 게시 후 사본 | `local/github/snapshots` |
| 실제 Issue/PR | GitHub remote |

## Issue 책임

Issue는 작업 범위, 검증 항목, demo 필요 여부, 완료 조건을 추적한다. Docs 원문을 복제하지 않고 정본 문서 링크와 요약을 둔다.

Issue에 포함할 항목:

- 대상 Work Unit
- 연결 Example, Topic, Verification, Demo, Publication 문서
- 검증할 build/run/capture 항목
- 완료 조건
- follow-up 후보

## PR 책임

PR은 변경 범위, 검증 결과, demo evidence, known issue, follow-up을 요약한다. PR 본문 초안은 `local/github/draft/prs`에서 작성한다.

PR에 포함할 항목:

- 변경한 문서와 코드 범위
- 검증 결과 요약
- demo/capture evidence 링크
- public readiness 영향
- 남은 known issue
- 다음 Work Unit 또는 Issue 후보

## WorkLog 책임

Issue/PR 작업 과정과 마감 기록은 `Docs/05_WorkLogs`에 둔다. WorkLog는 예제 설명, Topic, Verification, Demo, Publication 정본을 대체하지 않는다.

WorkLog에는 GitHub 본문 전체가 아니라 다음만 남긴다.

- 작업 범위
- 갱신한 정본 문서 링크
- 검증 요약
- 게시한 Issue/PR 번호 또는 예정 상태
- 리뷰 대응과 follow-up

## draft to public 흐름

```text
local/github/draft
-> local/github/public
-> GitHub remote
-> local/github/snapshots
-> Docs/05_WorkLogs 요약 반영
```

## 운영 기준

- Issue/PR 생성은 사용자가 명시적으로 요청한 경우에만 진행한다.
- 게시 전 본문은 local에서 검토한다.
- 게시 전 후보는 `Metadata`, 내부 메모, draft 문구, 존댓말을 제거한다.
- 게시 후 필요한 사본은 local snapshot에 둔다.
- merge 후 최종 상태는 각 정본 문서에 반영한다.