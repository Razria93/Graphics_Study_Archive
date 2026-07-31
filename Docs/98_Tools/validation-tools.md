# Validation Tools

이 문서는 문서 검수 도구의 용도와 최소 검수 기준을 정의한다.

## 현재 상태

- GitHub body validator는 `validators/validate-github-body.ps1`에 둔다.
- GitHub quality, Demo index, 상세 Demo, Topic 문서는 각각의 tracked validator로 검사한다.
- 현재 정본 Markdown의 명백한 인위적 soft-wrap은 `validators/validate-markdown-wrap-quality.ps1`로 검사한다.
- 현재 정본 Markdown table의 header, separator와 data row 열 정합성은 `validators/validate-markdown-table-quality.ps1`로 검사한다.
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

같은 문단·목록 항목을 여러 물리 줄로 나눈 명백한 인위적 soft-wrap은 `validate-markdown-wrap-quality.ps1`로 검사한다. 문장 흐름, 렌더링 가독성과 포괄적인 link label처럼 문맥이 필요한 항목은 agent 또는 수동 검수에서 확인한다. 상세 줄바꿈 기준은 [Docs Authoring Flow Policy](../06_Policies/docs-authoring-flow-policy.md)를 따른다.

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
| Markdown 원문 가독성 | `Docs/06_Policies/docs-authoring-flow-policy.md`, `validators/validate-markdown-wrap-quality.ps1` |
| Markdown table 구조 | `validators/validate-markdown-table-quality.ps1`, `validators/test-markdown-table-quality.ps1` |

## 전체 감사와 Validator 경계

Validator는 링크 형식, section, 상태값처럼 반복 가능한 기계 검사를 담당한다. 문서 책임 충돌, 설명 중복, 탐색 흐름, 상태 provenance, public narrative는 수동 감사에서 판단한다. Validator 통과는 전체 문서 감사 통과를 의미하지 않는다.

Publication 검수의 출처 상태, 외부 자료 복제 여부, 라이선스, metadata, decoded pixel 관계와 강화 출처 검수 필요 여부는 수동으로 판단한다. 현재 validator는 prompt 원문, 생성 화면 screenshot, 생성 날짜와 작업용 원본을 요구하지 않는다.

향후 audit runner의 계획된 interface와 자동화 경계는 `document-system-audit-guide.md`를 따른다. 현재 runner와 전체 링크·상태 validator는 구현되지 않았다.

## GitHub UI 렌더링 표본 검수

자동 validator는 Markdown source의 반복 가능한 구조, 문법과 링크 형식을 검사한다. Browser 검수는 로그인된 GitHub UI에서 실제 layout과 media 표시를 확인한다. 두 검사는 서로 대체하지 않는다.

Browser 표본 검수 대상:

- 새로 게시하거나 본문 구조를 크게 바꾼 PR과 Issue
- Root와 Chapter README 같은 공개 진입점
- 큰 table이 있는 Verification와 Demo Index
- 대표 상세 Demo와 대표 visual
- Markdown policy, template 또는 validator 변경의 영향 문서
- merge 직전 공개 문서 표본

일반적인 문장 수정과 내부 WorkLog는 자동 validator와 source 검수로 충분하면 Browser 필수 대상에서 제외한다. 한 PR의 같은 유형 문서를 모두 열지 않고 구조와 visual 차이를 대표하는 표본을 선택한다.

검수 순서:

1. local, tracking, remote와 PR head가 같은 commit인지 확인한다.
2. GitHub UI에서 대상 문서를 열고 heading, 문단과 목록 indentation을 확인한다.
3. table이 pipe 문단으로 표시되지 않는지, 열 정렬과 필요한 가로 스크롤이 읽기 가능한지 확인한다.
4. 의도하지 않은 문단·목록 줄바꿈과 link label 분리가 없는지 확인한다.
5. 이미지가 alt text나 broken image로 대체되지 않고 비율, 잘림과 대표성이 적절한지 확인한다.
6. PR 또는 Issue의 README, Verification, Demo Index와 상세 Demo 링크를 표본 이동한다.
7. 확인한 URL, commit과 결과를 보고하고 remote 객체는 별도 승인 없이 수정하지 않는다.

Browser에서 반복 가능한 결함을 발견하면 source를 최소 수정하고 같은 유형의 회귀를 자동 판정할 수 있는지 검토한다. 확실한 구조 규칙이면 validator와 PASS/FAIL fixture로 환류하고, 브라우저 layout이나 문맥 판단이면 수동 checklist에 남긴다.

Browser 연결이 없거나 private repository를 열 수 없으면 `렌더링 미확인`으로 보고한다. source와 URL 형식이 정상이라는 사실만으로 렌더링 통과를 선언하지 않는다. 확인된 broken table, broken image 또는 잘린 대표 visual은 수정 후 같은 GitHub UI에서 재검수한다.

Part1 Chapter03 PR의 merge 전 대표 표본은 PR body, Chapter README, Verification Index, Demo Index, Step4 DrawingSphere, Step8 Shadow, Step13 Transparency 상세 Demo와 Step13 대표 visual이다. Step14 attribution은 Publication과 문서 내용 검수 대상이며 layout 변경이 없으면 필수 Browser 표본으로 중복 지정하지 않는다.

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
