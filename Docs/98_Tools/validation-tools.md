# Validation Tools

이 문서는 문서 검수 도구의 용도와 최소 검수 기준을 정의한다.

## 현재 상태

- GitHub body validator는 `validators/validate-github-body.ps1`에 둔다.
- GitHub quality, Demo index, 상세 Demo, Topic 문서는 각각의 tracked validator로 검사한다.
- tracked Docs 전체 링크와 상태를 통합 검사하는 validator는 아직 없다.
- 개별 validator와 [Document System Audit Guide](document-system-audit-guide.md)의 수동 감사를 함께 사용한다.

## 로컬과 Actions 실행

로컬 검증은 commit과 push 전에 현재 worktree의 문제를 찾는다. GitHub Actions의 `Docs Validation` workflow는 push와 pull request의 commit을 clean checkout한 `windows-latest` runner에서 다시 검사해 실행 누락과 환경 의존 문제를 찾는다.

Actions run의 validator step 실패는 실제 검사 실패로 분류하고 로컬에서 같은 commit과 명령으로 재현한다. checkout, runner 할당과 GitHub infrastructure 실패는 문서 품질 실패와 구분한다.

Actions 성공은 validator가 담당하는 자동 검사만 증명한다. build/run 사실, capture의 시각 안전성, 문서 책임 분리와 설명의 기술적 정확성은 기존 수동 검수를 유지한다.

## 최소 검수

| 검수 | 목적 | 예시 |
| --- | --- | --- |
| 공백 검사 | trailing whitespace, EOF 문제 확인 | `git diff --check` |
| 문체 검사 | 존댓말, 대화체, draft 문구 확인 | `Select-String` 또는 `rg` |
| stale path 검사 | 오래된 `_repo/workflow`, legacy import 기록의 이전 경로, `Docs/Part*` 정본 경로 확인. `Docs/99_Legacy`의 과거 경로 기록은 문맥을 확인한다. | `rg` |
| 정책 링크 검사 | rename된 정책 파일명과 Index 링크 확인 | `rg` |
| stage 검사 | 커밋 대상 파일 범위 확인 | `git diff --cached --stat` |

일반 본문에는 특정 글자 수 상한을 적용하지 않는다. fenced code는 80자 초과를 warning, 120자 초과를 failure로 분리한다.

인위적 본문 soft-wrap, 링크와 조사·서술어의 분리, 포괄적인 link label은 길이만으로 안정적으로 판별하지 못하므로 agent 또는 수동 검수에서 확인한다. 상세 줄바꿈 기준은 [Docs Authoring Flow Policy](../06_Policies/docs-authoring-flow-policy.md)를 따른다.

## Work Unit 검수 연결

| 단계 | 검수 기준 |
| --- | --- |
| Example 작성 | `templates/example-readme.md`, 코드 폴더 README 정책 |
| Topic 작성 | `templates/topic.md`, `Docs/01_Topics/AGENTS.md` |
| Demo index 작성 | `Docs/03_Demos/AGENTS.md`, `validators/validate-demo-index-quality.ps1` |
| 상세 Demo 작성 | `templates/demo-note.md`, `validators/validate-demo-doc-quality.ps1` |
| WorkLog 마감 | `templates/worklog.md`, `Docs/04_WorkLogs/AGENTS.md` |
| local study review | `templates/local-study-review.md`, `Docs/06_Policies/local-review-policy.md` |
| publication review | `templates/local-publication-review.md`, `Docs/05_Publication/AGENTS.md` |
| GitHub body 검수 | `Docs/06_Policies/github-workflow-policy.md`, `validators/validate-github-body.ps1` |

## 전체 감사와 Validator 경계

Validator는 링크 형식, section, 상태값처럼 반복 가능한 기계 검사를 담당한다.
문서 책임 충돌, 설명 중복, 탐색 흐름, 상태 provenance, public narrative는
수동 감사에서 판단한다. Validator 통과는 전체 문서 감사 통과를 의미하지 않는다.

Publication 검수의 출처 상태, 외부 자료 복제 여부, 라이선스, metadata,
decoded pixel 관계와 강화 출처 검수 필요 여부는 수동으로 판단한다. 현재
validator는 prompt 원문, 생성 화면 screenshot, 생성 날짜와 작업용 원본을
요구하지 않는다.

향후 audit runner의 계획된 interface와 자동화 경계는
`document-system-audit-guide.md`를 따른다. 현재 runner와 전체 링크·상태
validator는 구현되지 않았다.

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

Issue/PR 후보 본문의 첫 H1은 title source로 유지한다. 실제 remote body에서는 첫 H1과 바로 뒤 빈 줄을 제거한다. remote/tracked 비교에도 같은 변환을 적용한다. comment body는 H1을 사용하지 않는다.

## 금지사항

- 검증하지 않은 문서를 validator 통과처럼 표현하지 않는다.
- GitHub 게시나 remote 상태 변경은 validator 결과만으로 진행하지 않는다.
