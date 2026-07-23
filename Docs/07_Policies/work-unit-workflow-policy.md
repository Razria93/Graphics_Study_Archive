# Work Unit Workflow Policy

이 문서는 Graphics Study Archive에서 Part 또는 Chapter를 하나의 Work Unit으로 정리하는 표준 흐름을 정의한다.

## 목적

Work Unit은 코드, 주석, raw/reference, origin 기준 확인에서 시작해 예제 설명, Topic, Verification, Demo, Publication, WorkLog, GitHub draft까지 이어지는 작업 단위다. 이 흐름은 산출물 축 구조를 실제 작업 순서에 연결한다.

## 기본 원칙

- 코드 정본은 루트 코드 폴더에 둔다.
- 문서 정본은 `Docs/01_Examples`부터 `Docs/06_Publication`까지의 산출물 축 폴더에 둔다.
- 정책 정본은 `Docs/07_Policies`에 둔다.
- 도구와 템플릿은 `Docs/98_Tools`에 둔다.
- import 기록과 기존 Part 문서는 `Docs/99_Legacy`에 둔다.
- 초안, 민감 판단, GitHub 게시 전 본문은 `local/`에 둔다.

## 단계별 흐름

| 단계 | 작업 | 읽는 위치 | 쓰는 위치 | 기준 정책 |
| --- | --- | --- | --- | --- |
| 0 | Work Unit 선택과 조사 계획 작성 | `Docs/00_Index`, 루트 코드 폴더 | `local/mini-plans` 또는 `Docs/05_WorkLogs` | 이 문서 |
| 1 | 사용자에게 조사 계획 보고 | `local/mini-plans`, 대상 코드 목록 | final report 또는 WorkLog 초안 | `github-workflow-policy.md` |
| 2 | 코드 구조 확인 | root `Part*_Chapter*`, `Portfolio_RayTracer` | 조사 메모는 `local/` | `agent-safety-policy.md` |
| 3 | 소스 주석 inventory 작성 | 관련 source/header/shader | `local/study-review` | `docs-authoring-flow-policy.md` |
| 4 | raw/reference와 origin 기준 확인 | raw/reference repo, origin 또는 원본 예제, `Docs/99_Legacy/ImportHistory` | 검토 메모는 `local/` | `canonical-docs-policy.md`, `local-review-policy.md` |
| 5 | current/raw/origin diff 조사 | 현재 코드, raw/reference, origin 기준 | `local/study-review` | `docs-authoring-flow-policy.md` |
| 6 | 챕터 목표와 핵심 구현 후보 추출 | code, source comment inventory, raw/origin docs | `local/study-review` 또는 `Docs/05_WorkLogs` | `docs-authoring-flow-policy.md` |
| 7 | 예제 목록과 대표 예제 결정 | 루트 코드 폴더, source review, Legacy PartDocs | `Docs/01_Examples` | `canonical-docs-policy.md` |
| 8 | 코드 주석 선별 정리 | source comment inventory | 루트 코드 폴더 | `agent-safety-policy.md`, `docs-authoring-flow-policy.md` |
| 9 | 예제 설명 작성 | current/raw/origin 검토 결과 | `Docs/01_Examples` | `docs-authoring-flow-policy.md` |
| 10 | graphics Topic 작성 | example docs, code, raw/reference 검토 결과 | `Docs/02_Topics` | `canonical-docs-policy.md` |
| 11 | build/run/capture 검증 | solution, executable, assets | `Docs/03_Verification` | `verification-policy.md` |
| 12 | Demo evidence 정리 | 실행 결과, capture 후보 | `Docs/04_Demos`, `Docs/_assets` | `demo-capture-policy.md`, `assets-policy.md` |
| 13 | public subset 판단 | example, topic, demo, asset 정보 | `Docs/06_Publication` | `publication-policy.md` |
| 14 | 작업 기록 마감 | 변경된 Docs, 검증 결과 | `Docs/05_WorkLogs` | `github-workflow-policy.md` |
| 15 | GitHub Issue/PR draft 작성 | WorkLog, Example, Verification, Demo | `local/github/draft` | `github-workflow-policy.md` |
| 16 | GitHub public body 검수 | `local/github/draft`, WorkLog, Verification | `local/github/public` | `github-workflow-policy.md`, `../98_Tools/validators/README.md` |
| 17 | Index 갱신 | 전체 산출물 | `Docs/00_Index`, `Docs/05_WorkLogs/issue-pr-index.md` | `canonical-docs-policy.md`, `github-workflow-policy.md` |
| 18 | 최종 검수 | 변경 파일 전체 | 검수 결과는 final report 또는 WorkLog | `style-policy.md`, `../98_Tools/validation-tools.md` |
| 19 | 사용자 검토 요청 | 변경 요약, 미확인 항목, follow-up | 대화 보고 또는 WorkLog | `github-workflow-policy.md` |
| 20 | commit readiness 보고 | 변경 파일, 검증 결과, 권장 commit 메시지 | 대화 보고 | `github-workflow-policy.md` |

## 산출물별 책임

| 산출물 | 정본 위치 | 내용 |
| --- | --- | --- |
| 예제 설명 | `Docs/01_Examples` | 예제 목적, 핵심 코드 위치, 관련 Topic/Verification/Demo 링크 |
| Topic | `Docs/02_Topics` | 여러 예제를 관통하는 graphics 개념과 pipeline 설명 |
| Verification | `Docs/03_Verification` | build/run/capture 상태, known issue, 확인 일자 |
| Demo | `Docs/04_Demos` | capture/video evidence, 시연 포인트, 연결 개념 |
| WorkLog | `Docs/05_WorkLogs` | 작업 범위, 변경 요약, 검증 요약, Issue/PR 연결, follow-up |
| Publication | `Docs/06_Publication` | public 후보, private 전용, 검토 필요, 제외 판단 |
| Policy | `Docs/07_Policies` | 반복 적용되는 규칙 |
| Tool | `Docs/98_Tools` | validator, template, troubleshooting |
| Legacy | `Docs/99_Legacy` | 이전 문서와 import 기록 |

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
    public/
      issues/
      prs/
      comments/
    snapshots/
```

사용 기준:

- code/raw 조사 중 나온 원문 메모는 `local/`에 둔다.
- GitHub 게시 전 본문은 `local/github/draft`에 둔다.
- 게시 직전 최종 후보는 `local/github/public`에 둔다.
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

## 사용자 검토 지점

다음 지점에서는 작업자가 사용자에게 상태를 보고하고 진행 방향을 확인한다.

- Work Unit 범위와 조사 계획을 세운 직후
- source comment inventory와 current/raw/origin diff에서 예상과 다른 차이를 발견했을 때
- 코드 주석 제거 또는 재작성 후보가 생겼을 때
- Example/Topic/Verification/Demo 초안 작성 후
- GitHub Issue/PR draft를 게시하기 전
- commit readiness를 보고할 때

## Done 기준

Work Unit은 다음 조건을 만족할 때 완료 상태로 둔다.

- 예제 설명 정본이 `Docs/01_Examples`에 있다.
- 소스 주석 inventory와 raw/origin/current 비교 여부가 기록되어 있다.
- 관련 Topic이 없으면 없다고 기록하고, 있으면 `Docs/02_Topics`에 연결한다.
- build/run/capture 상태가 `Docs/03_Verification`에 기록되어 있다.
- demo 필요 여부와 evidence 상태가 `Docs/04_Demos`에 기록되어 있다.
- public subset 판단이 `Docs/06_Publication`에 기록되어 있다.
- 작업 요약과 follow-up이 `Docs/05_WorkLogs`에 기록되어 있다.
- GitHub Issue/PR을 운영하는 Work Unit이면 `local/github/public` 후보와 validator 결과가 준비되어 있다.
- Plan Issue 누적 진행 댓글 또는 WorkLog 댓글 갱신 필요 여부가 판단되어 있다.
- `Docs/05_WorkLogs/issue-pr-index.md`에 Issue/PR/Plan comment 상태가 반영되어 있다.
- `Docs/00_Index` map이 필요한 범위만큼 갱신되어 있다.
- 오래된 `Docs/99_Legacy` 문서를 정본처럼 링크하지 않는다.
- 사용자 검토 요청과 commit readiness 보고가 끝나 있다.
