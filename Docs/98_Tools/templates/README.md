# Templates

이 폴더는 반복 사용할 문서 양식을 둔다. 템플릿은 정본 문서를 대체하지 않고, 각 산출물 폴더의 책임에 맞는 최소 구조만 제공한다.

## Template Index

| 템플릿 | 사용 위치 | 성격 | 비고 |
| --- | --- | --- | --- |
| [Example README](example-readme.md) | 코드 폴더 README | tracked 정본 문서용 | 예제 설명, 핵심 코드, 관련 문서 연결 |
| [Topic](topic.md) | `Docs/01_Topics` | tracked 정본 문서용 | graphics concept와 이론, Example/Verification/Demo 연결 |
| [Verification Note](verification-note.md) | `Docs/02_Verification` | tracked 정본 문서용 | build/run/capture 확인 기록 |
| [Demo Note](demo-note.md) | `Docs/03_Demos` 또는 `local/<work-unit>` | tracked/local 검토용 | demo 목표, capture/result 후보, generated image provenance 기록 |
| [WorkLog](worklog.md) | `Docs/04_WorkLogs` | tracked 정본 문서용 | Work Unit 결정 요약과 마감 snapshot |
| [PR Body](pr-body.md) | `Docs/07_GitHub/prs` | GitHub 게시 후보 | 핵심 개념, 대표 예제, 검증, demo 중심 PR 본문 |
| [Progress Issue](progress-issue.md) | `Docs/07_GitHub/plan/plan-body.md` | GitHub 게시 후보 | 전체 목표, 운영 기준, 완료 조건 |
| [Work Unit Issue](work-unit-issue.md) | `Docs/07_GitHub/issues/work-unit/work-unit_*.md` | GitHub 게시 후보 | Work Unit 범위, 검증 기준, 완료 조건 |
| [Plan Progress Comment](plan-progress-comment.md) | `Docs/07_GitHub/plan/plan-progress.md` | GitHub 게시 후보 | 누적 진행 요약 댓글 |
| [Plan Comment](work-unit-completion-comment.md) | `Docs/07_GitHub/plan/comments/*.md` | GitHub 게시 후보 | PR 마감 단위 기록 |
| [Local Study Review](local-study-review.md) | `local/study-review` | local-only 검토용 | raw/source 주석 inventory와 diff 검토 메모 |
| [Local Publication Review](local-publication-review.md) | `local/publication` | local-only 검토용 | 공개 전 점검 메모 |
| [PR Review Response](pr-review-response.md) | GitHub PR review comment 답변 | GitHub 게시용 짧은 댓글 | 대응, 검증, 비고 고정 형식 |
| [Document System Audit Report](document-system-audit-report.md) | `Docs/04_WorkLogs/reviews` 또는 대화 보고 | 감사 snapshot용 | 발견 근거, 사용자 판정, 수정 작업 묶음 |

## 사용 기준

- tracked 정본 문서용 템플릿은 해당 산출물 폴더 책임만 담는다.
- local-only 템플릿은 tracked Docs로 그대로 복사하지 않는다.
- README 계층별 책임과 갱신 기준은 `../../06_Policies/canonical-docs-policy.md`를 따른다.
- 상세 정책은 `Docs/06_Policies`를 기준으로 한다.
- 문체 검수와 stale 경로 검수는 `../validation-tools.md`를 따른다.
- 감사 보고서는 최신 상태 정본을 대체하지 않는다.

## 삭제된 템플릿

상태 통합 템플릿은 삭제한다. 상태 정보를 Example, Verification, Demo, Publication, WorkLog에 다시 모으는 구조라 산출물 축 책임과 충돌한다.
