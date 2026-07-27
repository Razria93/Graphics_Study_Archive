# Work Unit Workflow Policy

이 문서는 Graphics Study Archive에서 Part 또는 Chapter를 하나의 Work Unit으로 정리하는 표준 흐름을 정의한다.

## 목적

Work Unit은 코드, 주석, raw/reference, origin 기준 확인에서 시작해 예제 설명, Topic, Verification, Demo, Publication, WorkLog, GitHub draft까지 이어지는 작업 단위다. 이 흐름은 산출물 축 구조를 실제 작업 순서에 연결한다.

## 기본 원칙

- 코드 정본은 루트 코드 폴더에 둔다.
- 예제 README 정본은 코드 폴더에 두고, Topic부터 Publication까지의 문서 정본은 `Docs/01_Topics`부터 `Docs/05_Publication`까지의 산출물 축 폴더에 둔다.
- 정책 정본은 `Docs/06_Policies`에 둔다.
- 도구와 템플릿은 `Docs/98_Tools`에 둔다.
- import 기록과 기존 Part 문서는 `Docs/99_Legacy`에 둔다.
- 초안과 민감 판단은 `local/`에 둔다.
- GitHub 게시 후보 정본은 `Docs/07_GitHub`에 둔다.

## 단계별 흐름

| 단계 | 작업 | 읽는 위치 | 쓰는 위치 | 기준 정책 |
| --- | --- | --- | --- | --- |
| 0 | Work Unit 선택과 조사 계획 작성 | `Docs/00_Index`, 루트 코드 폴더 | `local/mini-plans` | 이 문서 |
| 1 | 사용자에게 조사 계획 보고 | `local/mini-plans`, 대상 코드 목록 | final report | `github-workflow-policy.md` |
| 2 | 코드 구조 확인 | root `Part*_Chapter*`, `Portfolio_RayTracer` | 조사 메모는 `local/` | `agent-safety-policy.md` |
| 3 | 소스 주석 inventory 작성 | 관련 source/header/shader | `local/study-review` | `docs-authoring-flow-policy.md` |
| 4 | raw/reference와 origin 기준 확인 | raw/reference repo, origin 또는 원본 예제, `Docs/99_Legacy/ImportHistory` | 검토 메모는 `local/` | `canonical-docs-policy.md`, `local-review-policy.md` |
| 5 | current/raw/origin diff 조사 | 현재 코드, raw/reference, origin 기준 | `local/study-review` | `docs-authoring-flow-policy.md` |
| 6 | 챕터 목표와 핵심 구현 후보 추출 | code, source comment inventory, raw/origin docs | 상세는 `local/study-review`, 요약은 `Docs/04_WorkLogs/study-review-summaries` | `docs-authoring-flow-policy.md` |
| 7 | 예제 목록과 대표 예제 결정 | 루트 코드 폴더, source review, Legacy PartDocs | 코드 폴더 README 계획 또는 `Docs/00_Index` | `canonical-docs-policy.md` |
| 8 | 코드 주석 선별 정리 | source comment inventory | 루트 코드 폴더 | `agent-safety-policy.md`, `docs-authoring-flow-policy.md` |
| 9 | 예제 README 작성 | current/raw/origin 검토 결과 | 대상 코드 폴더 `README.md` | `docs-authoring-flow-policy.md` |
| 10 | graphics Topic 작성 | example docs, code, raw/reference 검토 결과 | `Docs/01_Topics` | `canonical-docs-policy.md` |
| 11 | build/run/capture 검증 | solution, executable, assets | `Docs/02_Verification` | `verification-policy.md` |
| 12 | capture/result 요청 조건 판단 | 검증 결과, 예제 유형, demo 후보 | 사용자 요청 문구 또는 `Docs/03_Demos` 초안 | `demo-capture-policy.md` |
| 13 | Demo capture/result 정리 | 실행 결과, capture 후보 | `Docs/03_Demos`, `Docs/_assets`, 코드 폴더 README | `demo-capture-policy.md`, `assets-policy.md` |
| 14 | public subset 판단 | example, topic, demo, asset 정보 | `Docs/05_Publication` | `publication-policy.md` |
| 15 | 작업 기록 마감 | 변경된 Docs, 검증 결과 | `Docs/04_WorkLogs/active` 또는 `Docs/04_WorkLogs/completed` | `github-workflow-policy.md` |
| 16 | GitHub Issue/PR draft 작성 | WorkLog, Example, Verification, Demo | `local/github/draft` 또는 `Docs/07_GitHub` | `github-workflow-policy.md` |
| 17 | GitHub body 검수 | `Docs/07_GitHub`, WorkLog, Verification | validator 결과와 사용자 검토 보고 | `github-workflow-policy.md`, `../98_Tools/validators/README.md` |
| 18 | Index 갱신 | 전체 산출물 | `Docs/00_Index`, `Docs/04_WorkLogs/work-unit-github-index.md` | `canonical-docs-policy.md`, `github-workflow-policy.md` |
| 19 | README 갱신 여부 확인 | 변경된 Example, Topic, Verification, Demo, Publication | Root/Chapter/Example/Docs/Folder README 중 필요한 문서 | `canonical-docs-policy.md`, `docs-authoring-flow-policy.md` |
| 20 | 최종 검수 | 변경 파일 전체 | 검수 결과는 final report 또는 WorkLog | `style-policy.md`, `../98_Tools/validation-tools.md` |
| 21 | 사용자 검토 요청 | 변경 요약, 미확인 항목, follow-up | 대화 보고 또는 WorkLog | `github-workflow-policy.md` |
| 22 | commit readiness 보고 | 변경 파일, 검증 결과, 권장 commit 메시지 | 대화 보고 | `github-workflow-policy.md` |

## 산출물별 책임

| 산출물 | 정본 위치 | 내용 |
| --- | --- | --- |
| 예제 README | 대상 코드 폴더 `README.md` | 예제 목적, 핵심 코드 위치, 관련 Topic/Verification/Demo 링크 |
| Topic | `Docs/01_Topics` | 여러 예제를 관통하는 graphics 개념과 pipeline 설명 |
| Verification | `Docs/02_Verification` | build/run/capture 상태, known issue, 확인 일자 |
| Demo | `Docs/03_Demos` | capture/result, 시연 포인트, 연결 개념 |
| WorkLog | `Docs/04_WorkLogs` | 작업 범위, 주요 결정, 마감 snapshot, Issue/PR 연결, follow-up |
| Review Summary | `Docs/04_WorkLogs/study-review-summaries` | 상세 local 조사에서 승격한 결론과 반복 가능한 판단 기준 |
| Publication | `Docs/05_Publication` | public 후보, private 전용, 검토 필요, 제외 판단 |
| Policy | `Docs/06_Policies` | 반복 적용되는 규칙 |
| GitHub Body | `Docs/07_GitHub` | Issue, PR, comment 게시 후보 |
| Tool | `Docs/98_Tools` | validator, template, troubleshooting |
| Legacy | `Docs/99_Legacy` | 이전 문서와 import 기록 |

## 작성 깊이 기준

모든 예제를 같은 깊이로 문서화하지 않는다. 예제는 빠짐없이 추적하되, 상세 문서는 대표 예제 중심으로 작성한다.

| 대상 | 필수 산출물 | 선택 또는 대표 산출물 |
| --- | --- | --- |
| 모든 예제 | 코드 폴더 README, `Docs/02_Verification` 상태 | 상세 Topic/Demo 연결 |
| 대표 예제 | 상세 코드 폴더 README, Topic 연결, Demo 후보, WorkLog 결정 요약 | Publication 후보 상태 |
| Part/Chapter | README, example-index, verification-index, demo-index | 대표 Topic, 대표 capture/result |
| 공개 후보 | `Docs/05_Publication` 상태 기록 | public subset 문장 재작성 |

Publication은 기본 산출물이 아니라 공개 후보가 생겼을 때 사용하는 판단 축이다. Topic과 Demo도 모든 예제에 깊게 붙이지 않고, 대표 예제와 설명 가치가 높은 개념에 우선 적용한다.

## local-only 자료 영역 사용 기준

`local/`은 정본 문서로 승격하기 전 local-only 자료 영역이다.

권장 구조:

```text
local/
  mini-plans/
  source-comments/
  study-review/
  publication/
  github/
    draft/
      issues/
      prs/
      comments/
    snapshots/
```

사용 기준:

- code/raw 조사 중 나온 원문 메모와 상세 비교표는 `local/study-review/`에 둔다.
- tracked Docs에는 `local/`로 직접 연결되는 링크를 만들지 않는다.
- 다음 작업자가 반복 조사하지 않아도 되는 결론은 `Docs/04_WorkLogs/study-review-summaries/`에 요약한다.
- GitHub 초안은 `local/github/draft`에 둘 수 있다.
- GitHub 게시 후보 정본은 `Docs/07_GitHub`에 둔다.
- 게시 후 실제 게시본과 리뷰 대응 사본은 `local/github/snapshots`에 둔다.
- redaction, 공개 제외 판단 근거, 개인 메모는 tracked Docs에 두지 않는다.

## Template 연결

| 단계 | Template |
| --- | --- |
| 예제 설명 작성 | `Docs/98_Tools/templates/example-readme.md` |
| Topic 작성 | `Docs/98_Tools/templates/topic.md` |
| Verification 기록 | `Docs/98_Tools/templates/verification-note.md` |
| Demo 기록 | `Docs/98_Tools/templates/demo-note.md` |
| local study review | `Docs/98_Tools/templates/local-study-review.md` |
| publication review | `Docs/98_Tools/templates/local-publication-review.md` |
| WorkLog 마감 | `Docs/98_Tools/templates/worklog.md` |
| 최종 검수 | `Docs/98_Tools/validation-tools.md` |

## Docs/01_Examples 폐기 기준

- Docs/01_Examples는 폐기된 예전 링크 허브로 취급한다.
- 예제 설명 본문은 코드 폴더 README에 둔다.
- build/run/capture 상세 상태는 Docs/02_Verification에 둔다.
- 내부 source review와 stale 판단은 코드 폴더 README에 노출하지 않는다.
- 상세 조사 기록은 `local/study-review/`에 두고, 재사용 가능한 판단 요약만 `Docs/04_WorkLogs/study-review-summaries/`에 둔다.

## 사용자 검토 지점

다음 지점에서는 작업자가 사용자에게 상태를 보고하고 진행 방향을 확인한다.

- Work Unit 범위와 조사 계획을 세운 직후
- source comment inventory와 current/raw/origin diff에서 예상과 다른 차이를 발견했을 때
- 코드 주석 제거 또는 재작성 후보가 생겼을 때
- build/run 검증 후 screenshot, video, result image가 필요하다고 판단했을 때
- Example/Topic/Verification/Demo 초안 작성 후
- GitHub Issue/PR draft를 게시하기 전
- commit readiness를 보고할 때

## Done 기준

Work Unit은 다음 조건을 만족할 때 완료 상태로 둔다.

- 예제 README 정본이 대상 코드 폴더에 있다.
- 소스 주석 inventory와 raw/origin/current 비교 상세는 `local/study-review/`에 있고, 반복 가능한 판단 요약은 필요한 경우 `Docs/04_WorkLogs/study-review-summaries/`에 있다.
- 관련 Topic이 없으면 없다고 기록하고, 있으면 `Docs/01_Topics`에 연결한다.
- build/run/capture 상태가 `Docs/02_Verification`에 기록되어 있다.
- demo 필요 여부와 capture/result 상태가 `Docs/03_Demos`에 기록되어 있다.
- public subset 판단이 `Docs/05_Publication`에 기록되어 있다.
- 작업 결정, 마감 snapshot, follow-up이 `Docs/04_WorkLogs`에 기록되어 있다.
- GitHub Issue/PR을 운영하는 Work Unit이면 `Docs/07_GitHub` 후보와 validator 결과가 준비되어 있다.
- Progress Issue 누적 진행 댓글 및 Chapter/Bundle 완료 댓글 갱신 필요 여부가 판단되어 있다.
- `Docs/04_WorkLogs/work-unit-github-index.md`에 Issue/PR/Progress comment 상태가 반영되어 있다.
- `Docs/00_Index` map이 필요한 범위만큼 갱신되어 있다.
- Root, Chapter, Example, Docs, Folder README의 갱신 필요 여부가 판단되어 있고, 필요한 README만 갱신되어 있다.
- README를 갱신하지 않은 경우 그 이유가 WorkLog 또는 검토 보고에 남아 있다.
- 오래된 `Docs/99_Legacy` 문서와 폐기된 `Docs/01_Examples` 본문을 정본처럼 링크하지 않는다.
- 사용자 검토 요청과 commit readiness 보고가 끝나 있다.
