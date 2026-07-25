# WorkLog Map

이 문서는 Work Unit 작업 기록과 Issue/PR 요약의 연결 방식을 안내한다. WorkLog는 최신 정본이 아니라 작업 종료 시점의 요약과 결정 기록이다.

## WorkLog 위치

| 위치 | 책임 |
| --- | --- |
| `Docs/04_WorkLogs/active` | 진행 중 Work Unit 요약 |
| `Docs/04_WorkLogs/completed` | 완료된 Work Unit 요약 |
| `Docs/04_WorkLogs/decisions` | 구조 전환, 정책 결정, 마이그레이션 판단 기록 |
| `Docs/04_WorkLogs/study-review-summaries` | local review를 요약한 tracked 기록 |
| `Docs/04_WorkLogs/work-unit-index.md` | Work Unit 목록과 예정 상태 |
| `Docs/04_WorkLogs/work-unit-github-index.md` | Work Unit과 GitHub Issue/PR 후보 연결 |

## GitHub 연결

| 단계 | 위치 | 책임 |
| --- | --- | --- |
| 초안 | `local/` | Issue/PR/comment 초안 작성과 사전 검토 |
| 게시 후보 | `Docs/07_GitHub` | 게시 직전 문체와 민감 정보 검수 |
| 원격 게시 | GitHub remote | 사용자가 명시 요청한 경우만 진행 |
| 게시 후 사본 | `local/` snapshot | 게시 본문과 리뷰 대응 사본 보존 |
| 요약 | `Docs/04_WorkLogs` | 게시 번호, 검증 요약, follow-up 기록 |

## 운영 기준

- WorkLog에는 GitHub 본문 전체가 아니라 요약과 링크만 둔다.
- 정본 문서가 있는 내용은 WorkLog에 반복하지 않는다.
- Work Unit 예정 목록은 placeholder 파일을 만들지 않고 `work-unit-index.md`에 기록한다.
- Issue/PR 생성은 사용자가 명시적으로 요청한 경우에만 진행한다.
