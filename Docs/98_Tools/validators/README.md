# Validators

이 폴더는 반복 실행 가능한 tracked validator script를 둔다. 정책 정본은 `Docs/06_Policies`에 두고, 이 폴더에는 실행 파일과 사용법만 둔다.

## Script 목록

| Script | 목적 | 입력 |
| --- | --- | --- |
| `validate-github-body.ps1` | GitHub Issue/PR/comment 게시 전 Markdown body 검사 | `Docs/07_GitHub` |
| `validate-github-quality.ps1` | Demo Issue 품질 검사(전개, 시각 자료, 구현 설명, 가독성) | `Docs/07_GitHub/issues/demo` |
| `test-github-visual-quality.ps1` | GitHub image와 video attachment 합산 fixture 검사 | inline fixture |
| `validate-topic-doc-quality.ps1` | 상세 Topic 정본 품질 검사(책임 구조, 핵심 개념, Example/Verification/Demo 연결) | `Docs/01_Topics` |
| `validate-demo-index-quality.ps1` | Demo source docs 구현도 균일성 검사(필수 구조, 테이블 스키마, 상태값, 최소 capture 기준) | `Docs/03_Demos/**/demo-index.md` |
| `test-demo-index-quality.ps1` | Demo index의 selected·published video reference fixture 검사 | `fixtures/demo-index-video` |
| `validate-demo-doc-quality.ps1` | 상세 Demo 기술 정본 검사(구조, 링크, tracked visual, 금지 경로) | `Docs/03_Demos/**/[0-9][0-9]_*.md` |
| `test-demo-doc-quality.ps1` | 상세 Demo 코드 근거 link label과 의사코드 fence fixture 검사 | `fixtures/demo-doc-link-label`, `fixtures/demo-doc-pseudocode` |
| `validate-video-asset-quality.ps1` | 예상하지 못한 tracked MP4, MOV와 WEBM 검사 | Git tracked path |
| `test-video-asset-quality.ps1` | tracked video path fixture 검사 | `fixtures/video-asset-quality` |
| `validate-markdown-wrap-quality.ps1` | 현재 정본 Markdown의 명백한 인위적 soft-wrap 검사 | Root·Example README, `Docs/00_Index`~`Docs/07_GitHub`, `Docs/98_Tools`, tracked `.github` Markdown |
| `test-markdown-render-quality.ps1` | Markdown 범위 표기의 취소선 오해 방지 fixture 검사 | `fixtures/markdown-render-quality` |
| `validate-markdown-render-quality.ps1` | 한 줄의 복수 단일-tilde 범위로 발생하는 의도하지 않은 취소선 검사 | Root·Example README, `Docs/00_Index`~`Docs/07_GitHub`, `Docs/98_Tools`, tracked `.github` Markdown |
| `test-markdown-table-quality.ps1` | Markdown table 열 정합성 fixture 검사 | `fixtures/markdown-table-quality` |
| `validate-markdown-table-quality.ps1` | 현재 정본 Markdown table의 header·separator·data row 열 정합성 검사 | Root·Example README, `Docs/00_Index`~`Docs/07_GitHub`, `Docs/98_Tools`, tracked `.github` Markdown |

## 사용법

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-github-visual-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-topic-doc-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-index-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-demo-index-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-doc-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-demo-doc-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-video-asset-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-video-asset-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-markdown-wrap-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-markdown-render-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-render-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-markdown-table-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-table-quality.ps1
```

GitHub body validator의 기본 입력은 `Docs/07_GitHub`이다. Topic과 Demo source docs validator는 각각 `Docs/01_Topics`, `Docs/03_Demos`를 기본 입력으로 사용한다.

## GitHub Actions

`.github/workflows/docs-validation.yml`의 `Docs Validation` workflow는 push와 pull request에서 문서 validator, Demo·Markdown 줄바꿈·Markdown table fixture와 현재 정본 검사를 같은 입력 기준으로 실행한다. Actions는 검사 기준의 정본이 아니라 로컬 validator를 실행하는 원격 환경이다.

GitHub의 Actions tab 또는 PR Checks에서 `Docs Validation` run을 열고 validator별 step과 log를 확인한다. validator step 실패와 checkout, runner 또는 GitHub infrastructure 실패를 구분하며 상세 판정은 [GitHub Workflow Policy](../../06_Policies/github-workflow-policy.md)를 따른다.

Fixture가 validator의 exit code를 확인하기 위해 자식 PowerShell process를 실행할 때는 현재 host executable을 사용한다. 로컬 Windows PowerShell과 Actions의 `pwsh` 사이에서 host를 바꾸지 않아 BOM 없는 UTF-8 script의 해석 기준을 유지한다. 관련 장애 처리는 [Session Troubleshooting](../session-troubleshooting.md)을 따른다.

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1 -GitHubRoot Docs/07_GitHub
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-quality.ps1 -GitHubRoot Docs/07_GitHub
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-github-visual-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-topic-doc-quality.ps1 -TopicsRoot Docs/01_Topics
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-index-quality.ps1 -DemosRoot Docs/03_Demos
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-demo-index-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-doc-quality.ps1 -DemosRoot Docs/03_Demos
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-demo-doc-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-video-asset-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-video-asset-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-markdown-wrap-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-markdown-render-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-render-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/test-markdown-table-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-table-quality.ps1
```

`validate-github-quality.ps1`는 현재 `issues/demo/demo_*.md`를 대상으로 다음을 검사한다.

- curated Demo Issue 필수 섹션과 순서
- 대표 GitHub visual 1~3개, screenshot 최소 1개와 standalone video attachment URL 합산
- 상세 Demo와 Verification 링크
- 핵심 구현의 commit-pinned C++ source line 링크
- 선택적 C++ 의사코드와 같은 섹션의 source line 링크
- `Pseudo C++` 함수와 `if`, `else`, `for`, `while`의 Allman brace style
- fenced code의 80자 초과 warning과 120자 초과 failure

`validate-demo-index-quality.ps1`는 현재 `Docs/03_Demos/**/demo-index.md`를 대상으로 다음을 검사한다.

- 필수 섹션 존재와 순서(`## 범위`, `## Demo 목록`, `## 갱신 기준`)
- `## 범위`의 `주요 demo 후보`, `비고` 항목 존재
- Demo 목록 테이블 필수 컬럼 존재(`상세 Demo`, `GitHub Demo Issue` 포함)
- Demo 목록의 필수 행(`최소 capture`, `대표 capture`, `video`) 존재
- 상태값 허용 목록 준수(`미확인`, `후보`, `확보`, `보류`, `제외`)
- `확보` 상태일 때 Capture/Result가 `없음`이 아니며 tracked asset, selected local video 또는 published Demo Issue 중 하나를 참조하는지 확인
- `확보` 상태일 때 상세 Demo Markdown 링크가 있는지 확인
- 상세 Demo와 Demo Issue 후보의 상대 링크 대상 존재 여부 확인
- Demo Issue가 `게시 후보`, `미게시`, 실제 GitHub Issue URL 중 하나로 표현되는지 확인
- 각 행 `비고` 비어있지 않은지 확인
- `최소 capture` 행의 Example 대상 지정 여부 확인

`validate-demo-doc-quality.ps1`는 상세 Demo 문서를 대상으로 다음을 검사한다.

- 필수 섹션과 순서, 의미 있는 본문
- Example, Topic, Verification Markdown 링크
- repo-relative 링크 대상 존재 여부
- tracked `Docs/_assets` visual
- 모든 `cpp` fence의 `Pseudo C++` 표기와 대응 source line 링크
- C++ 함수 block을 `text` fence로 분류한 의사코드 탐지
- `## 핵심 구현` source line 코드 근거 bullet의 명사형 label과 끝 마침표 금지
- `Pseudo C++` 함수와 `if`, `else`, `for`, `while`의 Allman brace style
- `local/`, Legacy, stale path, placeholder
- fenced code의 80자 초과 warning과 120자 초과 failure
- 같은 폴더 `demo-index.md`의 상세 Demo 연결

상세 Demo는 실제 C++ source를 복제하지 않고 source line 링크로 연결한다. `cpp` fence는 첫 비공백 줄에 `// Pseudo C++:`와 요약을 두며 Allman style을 적용한다. 함수 block을 포함하지 않는 화살표 기반 흐름도는 `text` fence로 유지한다. multiline signature, brace balance, indentation, source link의 의미상 대응은 수동 검수한다.

`validate-topic-doc-quality.ps1`는 `Docs/01_Topics`의 승격된 상세 Topic 문서를 대상으로 다음을 검사한다.

- `README.md`, `topic-index.md`, `AGENTS.md`를 제외한 상세 Topic 최소 1개 존재 여부
- 필수 섹션 존재와 순서(`## 목적`, `## 책임 범위`, `## 핵심 개념`, `## 한계`, `## 관련 문서`)
- 각 필수 섹션의 의미 있는 내용 존재 여부
- `## 핵심 개념` 아래 최소 2개 `###` 개념 소제목 존재 여부
- Example README Markdown 링크 존재 여부
- `Docs/02_Verification`, `Docs/03_Demos` 정본 연결 여부
- placeholder와 `local/`, `Docs/99_Legacy` 경로 존재 여부

## 검사 기준

- 일반 문단과 하나의 목록 항목은 각각 하나의 물리적 줄로 작성하고 특정 글자 수 상한을 두지 않는다.
- 같은 문단·목록 항목의 연속 물리 줄처럼 구조적으로 확실한 인위적 soft-wrap은 `validate-markdown-wrap-quality.ps1`로 검사한다.
- 애매한 들여쓰기 continuation은 warning으로 보고하며 `-WarningAsFailure`에서만 실패로 승격한다.
- Markdown table은 header, separator와 data row의 열 수가 일치하는지 검사하고 separator cell의 alignment marker 문법을 확인한다.
- 일반 문장의 단계·숫자·날짜 범위는 en dash를 사용한다. 같은 줄의 복수 단일-tilde 범위는 의도하지 않은 취소선으로 렌더링될 수 있어 render validator로 검사한다.
- code span, fenced code, escaped tilde와 `~~`로 표시한 의도적 취소선은 render validator에서 제외한다.
- escaped pipe는 cell 내용으로 처리하고 fenced code block과 HTML table은 table 검사에서 제외한다.
- 문장 흐름과 렌더링 가독성처럼 문맥 판단이 필요한 항목은 agent 또는 수동 검수에서 확인한다.
- 실제 GitHub UI에서 table, 목록과 이미지가 의도대로 렌더링되는지는 validator가 보장하지 않으며 [Validation Tools](../validation-tools.md)의 Browser 표본 검수에서 확인한다.
- validator는 Markdown을 자동 reflow하거나 수정하지 않는다.
- fenced code는 80자를 권장하고 120자를 상한으로 검사한다.
- GitHub 게시 전 body에 draft/local-only 경로가 남아 있지 않은지 확인한다.
- 필수 섹션이 빠지지 않았는지 확인한다.
- 필수 섹션이 비어 있거나 `-`만 있는지 확인한다.
- placeholder(`<...>`), TODO, TBD가 남아 있는지 확인한다.
- GitHub body가 한국어 섹션 기준을 따르는지 확인한다.
- screenshot Markdown이 `Docs/_assets/captures`를 가리키는지 확인한다.
- screenshot/result image는 GitHub absolute URL을 사용해야 한다.
- 허용 URL은 `https://github.com/<owner>/<repo>/blob/<branch>/Docs/_assets/captures/<file>?raw=true` 또는 `https://raw.githubusercontent.com/<owner>/<repo>/<branch>/Docs/_assets/captures/<file>` 형식이다.
- image URL 검사는 형식 검사이며 실제 파일 존재를 보증하지 않는다.
- PR은 screenshot과 standalone video attachment를 합해 대표 visual을 최대 1개 사용하고 상세 Demo, Demo Issue 후보 또는 게시된 Demo Issue를 연결한다.
- template에 특정 Issue 번호가 하드코딩되어 있지 않은지 확인한다.
- Issue/PR 후보는 첫 H1을 title source로 유지한다. 실제 remote body에서는 첫 H1과 바로 뒤 빈 줄을 제거하고 remote/tracked 비교에도 같은 변환을 적용한다.

## 지원 범위

현재 validator는 `Docs/07_GitHub` 아래의 다음 Markdown을 검사한다.

| 위치 | 검사 |
| --- | --- |
| `prs/**/*.md` | PR body |
| `plan/plan-body.md` | Progress issue |
| `plan/plan-progress.md` | Progress Issue 누적 진행 댓글 |
| `plan/comments/*.md` | PR 마감 plan comment |
| `issues/work-unit/work-unit_*.md` | Work Unit issue |
| `issues/verification/verification_*.md` | Verification issue |
| `issues/demo/demo_*.md` | Demo issue |


## Work Unit issue schema

Work Unit Issue는 작업 범위와 완료 조건을 GitHub에서 추적하기 위한 body다. PR body, WorkLog, Topic, Verification 문서의 내용을 복제하지 않는다.

| 파일 | 책임 | 주요 검사 |
| --- | --- | --- |
| `issues/work-unit/work-unit_*.md` | Work Unit 범위와 완료 조건 | `## 요약`, `## 목표`, `## 범위`, `## 핵심 작업`, `## 검증 기준`, `## Demo/Capture 필요 여부`, `## 완료 조건`, `## 관련 문서`, `## 제외 범위` 순서 |

Work Unit Issue에는 screenshot/image URL을 필수로 요구하지 않는다. capture/result 상세는 `Docs/03_Demos`와 PR body에서 다룬다.

## Progress issue schema

Progress Issue는 전체 목표와 완료 조건을 추적한다. Work Unit 상세 본문을 복제하지 않고 운영 모델과 책임만 요약한다.

| 파일 | 책임 | 주요 검사 |
| --- | --- | --- |
| `plan/plan-body.md` | 상위 진행판 | `## 요약`, `## 목표`, `## Phase 범위`, `## 완료 조건`, `## 기본 게시 객체`, `## 선택 Issue 생성 기준`, `## 관련 문서`, `## 제외 범위` 순서 |

Progress Issue에는 screenshot/image URL을 필수로 요구하지 않는다.
## Progress comment schema

Progress Issue 관련 GitHub body는 두 종류만 검사한다.

| 파일 | 책임 | 주요 검사 |
| --- | --- | --- |
| `plan/plan-progress.md` | 전체 진행판 | `## Graphics Study 진행 요약`, `## 완료`, `## 진행 예정`, `## Related PRs` 구조와 Phase heading |
| `plan/comments/*.md` | PR 마감 기록 | `## Phase <n-n> 완료 기록`, 완료 내용, 검증, 남은 제한, 관련 PR |

comment body는 H1과 내부 안내 문구를 허용하지 않는다.

## 지원하지 않는 schema

- `plan/` 아래에서 `plan-body.md`, `plan-progress.md`, `comments/*.md` 외 파일명은 실패 처리한다.
- `issues/` 아래에서 `work-unit/work-unit_*.md`, `verification/verification_*.md`, `demo/demo_*.md` 외 파일명은 실패 처리한다.

Progress comment는 Docs 정본을 복제하지 않고 진행 상태와 링크만 요약한다. 상세 정책은 `Docs/06_Policies/github-workflow-policy.md`를 따른다.

## 검사하지 않는 것

- `local/` 임시 초안에서 `Docs/07_GitHub`로 승격했는지 여부
- GitHub 게시 승인 여부
- 실제 `gh` 게시 여부
- `local/` 하위 snapshot 생성 여부
- `Docs/04_WorkLogs`와 `work-unit-github-index.md` 동기화 여부
- build/run/capture 실제 성공 여부
- asset 출처 상태, 외부 자료 복제 여부, 라이선스와 metadata
- 실행 입력과 tracked asset의 hash 또는 decoded pixel 관계
- prompt 원문, 생성 화면 screenshot, 생성 날짜와 작업용 원본
- 상세 Demo와 Example 또는 Demo Issue의 의미 중복
- visual 대표성과 limitation의 기술적 정확성
- video 필요성, 조작과 결과의 대응, 시작·종료 frame과 공개 화면 안전성
- private repository attachment의 실제 재생과 비인가 독자 접근 가능성

Video binary와 게시 상태는 다음 방식으로 함께 확인한다.

- 기존 selected MP4의 기술 검사는 `../scripts/inspect-example-video.ps1`을 사용한다.
- 예상하지 못한 tracked MP4, MOV와 WEBM은 `validate-video-asset-quality.ps1`로 검사한다.
- Demo Issue video attachment의 실제 GitHub UI 재생은 Browser 수동 검수로 확인한다.
- 같은 video의 중복 업로드와 PR 대표성은 게시 전 수동 감사로 확인한다.

## 주의

- validator 통과는 GitHub 게시 승인이 아니다.
- `git push`, `gh issue create`, `gh pr create`, Ready for Review 전환은 사용자 승인 후 진행한다.
- local 초안 원문은 이 폴더에 두지 않는다.
