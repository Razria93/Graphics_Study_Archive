# Validation Tools

이 문서는 문서 검수 도구의 용도와 최소 검수 기준을 정의한다.

## 현재 상태

- GitHub body validator는 `validators/validate-github-body.ps1`에 둔다.
- GitHub 게시 전 body 검수는 tracked validator와 수동 검색을 함께 사용한다.
- GitHub Actions는 `.github/workflows/docs-validation.yml`의 `Docs Validation` workflow를 기준으로 한다.
- local preflight는 full-scan 결과와 Actions 동일 조건 결과를 분리해 기록한다.

## Actions validator scope

GitHub Actions는 checkout된 head에서 `HEAD~1`과 `HEAD`를 비교해 `changed-files.txt`를 만든다. Local에서 아직 커밋하지 않은 변경을 Actions 입력처럼 재현할 때는 `git diff --name-only HEAD`를 사용한다.

| Actions 단계 | Validator | Scope | 입력 기준 |
| --- | --- | --- | --- |
| Validate GitHub bodies | `validate-github-body.ps1` | full-scan | 기본 입력 `Docs/07_GitHub` |
| Validate GitHub quality | `validate-github-quality.ps1` | full-scan | 기본 입력 `Docs/07_GitHub/issues/demo` |
| Test GitHub visual validator fixtures | `test-github-visual-quality.ps1` | full-scan fixture | fixture 전체 |
| Validate Demo indexes | `validate-demo-index-quality.ps1` | full-scan | 기본 입력 `Docs/03_Demos` |
| Test Demo index validator fixtures | `test-demo-index-quality.ps1` | full-scan fixture | fixture 전체 |
| Validate Demo documents | `validate-demo-doc-quality.ps1` | changed-file scope | `Docs/03_Demos/.+/\d{2}_.+\.md` 또는 `Part\d+_Chapter.*/README.md` |
| Test Demo document validator fixtures | `test-demo-doc-quality.ps1` | full-scan fixture | fixture 전체 |
| Validate tracked video assets | `validate-video-asset-quality.ps1` | full-scan | tracked video asset 전체 |
| Test video asset validator fixtures | `test-video-asset-quality.ps1` | full-scan fixture | fixture 전체 |
| Test window capture tool contracts | `test-window-capture-tools.ps1` | full-scan fixture | tool contract 전체 |
| Test window input primitive contracts | `test-window-input-primitives.ps1` | full-scan fixture | input primitive 전체 |
| Validate Topic documents | `validate-topic-doc-quality.ps1` | full-scan | 기본 입력 `Docs/01_Topics` |
| Test Markdown wrap validator fixtures | `test-markdown-wrap-quality.ps1` | full-scan fixture | fixture 전체 |
| Validate Markdown wrapping | `validate-markdown-wrap-quality.ps1` | changed-file scope | 변경된 `.md` 파일 |
| Test Markdown render validator fixtures | `test-markdown-render-quality.ps1` | full-scan fixture | fixture 전체 |
| Validate Markdown rendering | `validate-markdown-render-quality.ps1` | changed-file scope | 변경된 `.md` 파일 |
| Test Markdown table validator fixtures | `test-markdown-table-quality.ps1` | full-scan fixture | fixture 전체 |
| Validate Markdown tables | `validate-markdown-table-quality.ps1` | changed-file scope | 변경된 `.md` 파일 |

## Local preflight

Full-scan preflight는 기존 문서 부채를 포함한 저장소 전체 상태를 확인한다.

```powershell
$fullScanCommands = @(
	'./Docs/98_Tools/validators/validate-github-body.ps1',
	'./Docs/98_Tools/validators/validate-github-quality.ps1',
	'./Docs/98_Tools/validators/test-github-visual-quality.ps1',
	'./Docs/98_Tools/validators/validate-demo-index-quality.ps1',
	'./Docs/98_Tools/validators/test-demo-index-quality.ps1',
	'./Docs/98_Tools/validators/validate-demo-doc-quality.ps1',
	'./Docs/98_Tools/validators/test-demo-doc-quality.ps1',
	'./Docs/98_Tools/validators/validate-video-asset-quality.ps1',
	'./Docs/98_Tools/validators/test-video-asset-quality.ps1',
	'./Docs/98_Tools/validators/test-window-capture-tools.ps1',
	'./Docs/98_Tools/validators/test-window-input-primitives.ps1',
	'./Docs/98_Tools/validators/validate-topic-doc-quality.ps1',
	'./Docs/98_Tools/validators/test-markdown-wrap-quality.ps1',
	'./Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1',
	'./Docs/98_Tools/validators/test-markdown-render-quality.ps1',
	'./Docs/98_Tools/validators/validate-markdown-render-quality.ps1',
	'./Docs/98_Tools/validators/test-markdown-table-quality.ps1',
	'./Docs/98_Tools/validators/validate-markdown-table-quality.ps1'
)

foreach ($command in $fullScanCommands) {
	& $command
}
```

Actions 동일 조건 preflight는 현재 변경분이 workflow의 changed-file scope에서 통과하는지 확인한다. 커밋 전에는 `git diff --name-only HEAD`를 사용하고, 커밋 후에는 workflow와 같이 `HEAD~1`부터 `HEAD`까지의 변경 파일을 사용한다.

```powershell
$changed = @(
	git diff --name-only HEAD |
		Where-Object { -not [string]::IsNullOrWhiteSpace($_) }
)
Write-Host "changed files:" $changed.Count

$demoFiles = @(
	$changed |
		Where-Object {
			($_ -match '^Docs/03_Demos/.+/\d{2}_.+\.md$') -or
			($_ -match '^Part\d+_Chapter.*/README\.md$')
		}
)
Write-Host "demo scoped files:" $demoFiles.Count
if ($demoFiles.Count -gt 0) {
	./Docs/98_Tools/validators/validate-demo-doc-quality.ps1 -InputPath $demoFiles
}
else {
	Write-Host "No changed Demo documents or example README files."
}

$markdownFiles = @($changed | Where-Object { $_ -match '\.md$' })
Write-Host "markdown scoped files:" $markdownFiles.Count
if ($markdownFiles.Count -gt 0) {
	./Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1 -InputPath $markdownFiles
	./Docs/98_Tools/validators/validate-markdown-render-quality.ps1 -InputPath $markdownFiles
	./Docs/98_Tools/validators/validate-markdown-table-quality.ps1 -InputPath $markdownFiles
}
else {
	Write-Host "No changed Markdown files."
}
```

Whitespace preflight는 validator 결과와 별도로 실행한다.

```powershell
git diff --check
```

## 결과 기록 기준

- `full-scan 통과`는 Local preflight의 full-scan command가 실패와 warning 없이 끝난 상태를 뜻한다.
- `Actions 동일 조건 통과`는 현재 변경 파일 목록으로 changed-file scope validator를 재현해 통과한 상태를 뜻한다.
- 두 결과는 서로 대체하지 않는다. full-scan은 저장소 전체 품질을 보고, Actions 동일 조건은 현재 PR 또는 push에서 실제로 걸릴 scope를 본다.
- warning이 남아 있으면 `통과, warning only`로 분리해 적고 warning 항목과 처리 방침을 함께 기록한다.
- `git diff --check` 결과는 validator 통과와 별도로 기록한다.
- 검증하지 않은 항목은 `미확인`으로 기록한다.

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

새로 작성하거나 수정한 GitHub body는 `-InputPath` 배열로 작업 대상만 지정해 strict 검사를 실행한다. 기본 전수 실행에서 미수정 기존 정본 문서가 실패하면, 현재 작업의 실패로 섞지 않고 별도 이관 backlog로 기록한다.

```powershell
powershell -ExecutionPolicy Bypass -Command "& 'Docs/98_Tools/validators/validate-github-body.ps1' -InputPath @('Docs/07_GitHub/prs/part4_chapter15.md')"
```

지원 디렉터리와 미보장 범위는 `validators/README.md`를 기준으로 확인한다.

Issue/PR 후보 본문의 첫 H1은 title source로 유지한다. 실제 `gh issue create`와 `gh pr create`에서는 title을 H1에서 사용하고 body는 `Docs/07_GitHub` tracked 정본을 그대로 게시한다. comment body는 H1을 사용하지 않는다.

## 금지사항

- 검증하지 않은 문서를 validator 통과처럼 표현하지 않는다.
- GitHub 게시나 remote 상태 변경은 validator 결과만으로 진행하지 않는다.
