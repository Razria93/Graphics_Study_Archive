# Validation Tools

이 문서는 문서 검수 도구의 용도와 최소 검수 기준을 정의한다.

## 현재 상태

- GitHub body validator는 `validators/validate-github-body.ps1`에 둔다.
- tracked Docs 전용 통합 validator script는 아직 없다.
- GitHub 게시 전 body 검수는 tracked validator와 수동 검색을 함께 사용한다.

## 최소 검수

| 검수 | 목적 | 예시 |
| --- | --- | --- |
| 공백 검사 | trailing whitespace, EOF 문제 확인 | `git diff --check` |
| 문체 검사 | 존댓말, 대화체, draft 문구 확인 | `Select-String` 또는 `rg` |
| stale path 검사 | 오래된 `_repo/workflow`, legacy import 기록의 이전 경로, `Docs/Part*` 정본 경로 확인. `Docs/99_Legacy`의 과거 경로 기록은 문맥을 확인한다. | `rg` |
| 정책 링크 검사 | rename된 정책 파일명과 Index 링크 확인 | `rg` |
| stage 검사 | 커밋 대상 파일 범위 확인 | `git diff --cached --stat` |

## Work Unit 검수 연결

| 단계 | 검수 기준 |
| --- | --- |
| Example 작성 | `templates/example-readme.md`, 코드 폴더 README 정책 |
| Topic 작성 | `templates/topic.md`, `Docs/01_Topics/AGENTS.md` |
| WorkLog 마감 | `templates/worklog.md`, `Docs/04_WorkLogs/AGENTS.md` |
| local study review | `templates/local-study-review.md`, `Docs/06_Policies/local-review-policy.md` |
| publication review | `templates/local-publication-review.md`, `Docs/05_Publication/AGENTS.md` |
| GitHub body 검수 | `Docs/06_Policies/github-workflow-policy.md`, `validators/validate-github-body.ps1` |

## tracked validator 기준

tracked validator는 다음 조건을 만족해야 한다.

- 반복 사용 가치가 있다.
- 민감 정보와 로컬 절대 경로가 없다.
- 입력/출력과 실패 조건이 명확하다.
- `Docs/98_Tools`에 사용법이 문서화되어 있다.
- remote 상태를 바꾸지 않는다.

## GitHub body validator

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
```

기본 입력 위치는 `Docs/07_GitHub`이다. GitHub에 게시하기 전 후보 Markdown을 이 위치에 둔 뒤 실행한다.

지원 디렉터리와 미보장 범위는 `validators/README.md`를 기준으로 확인한다.

Issue/PR 후보 본문의 첫 H1은 title source로 유지한다. 실제 `gh issue create`와 `gh pr create`에서는 title을 H1에서 사용하고 body는 `Docs/07_GitHub` tracked 정본을 그대로 게시한다. comment body는 H1을 사용하지 않는다.

## 금지사항

- 검증하지 않은 문서를 validator 통과처럼 표현하지 않는다.
- GitHub 게시나 remote 상태 변경은 validator 결과만으로 진행하지 않는다.
