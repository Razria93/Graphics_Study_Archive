# Validation Tools

이 문서는 문서 검수 도구의 용도와 최소 검수 기준을 정의한다.

## 현재 상태

- tracked Docs 전용 validator script는 아직 없다.
- GitHub body validator는 `local/tools/validate-github-body.ps1`에 있는 local-only 도구다.
- tracked script로 승격하기 전까지는 수동 검색과 `git diff --check`를 최소 검수로 사용한다.

## 최소 검수

| 검수 | 목적 | 예시 |
| --- | --- | --- |
| 공백 검사 | trailing whitespace, EOF 문제 확인 | `git diff --check` |
| 문체 검사 | 존댓말, 대화체, draft 문구 확인 | `Select-String` 또는 `rg` |
| stale path 검사 | 오래된 `_repo/workflow`, `_repo/ImportPhase`, `Docs/Part*` 정본 경로 확인 | `rg` |
| 정책 링크 검사 | rename된 정책 파일명과 Index 링크 확인 | `rg` |
| stage 검사 | 커밋 대상 파일 범위 확인 | `git diff --cached --stat` |

## Work Unit 검수 연결

| 단계 | 검수 기준 |
| --- | --- |
| Example 작성 | `templates/example-readme.md`, `Docs/01_Examples/AGENTS.md` |
| Topic 작성 | `templates/topic.md`, `Docs/02_Topics/AGENTS.md` |
| WorkLog 마감 | `templates/worklog.md`, `Docs/05_WorkLogs/AGENTS.md` |
| local study review | `templates/local-study-review.md`, `Docs/07_Policies/local-review-policy.md` |
| publication review | `templates/local-publication-review.md`, `Docs/06_Publication/AGENTS.md` |
| GitHub body 검수 | `Docs/07_Policies/github-workflow-policy.md`, local validator |

## tracked validator 승격 기준

local validator는 다음 조건을 만족할 때 tracked script 후보로 본다.

- 반복 사용 가치가 있다.
- 민감 정보와 로컬 절대 경로가 없다.
- 입력/출력과 실패 조건이 명확하다.
- `Docs/98_Tools`에 사용법이 문서화되어 있다.
- 사용자 승인 후 tracked script로 추가한다.

## 금지사항

- local-only validator를 검토 없이 tracked script로 승격하지 않는다.
- 검증하지 않은 문서를 validator 통과처럼 표현하지 않는다.
- GitHub 게시나 remote 상태 변경은 validator 결과만으로 진행하지 않는다.
