# Work Unit Workflow Policy

이 문서는 Graphics Study Archive에서 Part 또는 Chapter를 하나의 Work Unit으로 정리하는 표준 흐름을 정의한다.

## 목적

Work Unit은 코드 확인에서 시작해 예제 설명, Topic, Verification, Demo, Publication, WorkLog, GitHub draft까지 이어지는 작업 단위다. 이 흐름은 산출물 축 구조를 실제 작업 순서에 연결한다.

## 기본 원칙

- 코드 정본은 root의 `Part*_Chapter*`와 `Portfolio_RayTracer`에 둔다.
- 문서 정본은 `Docs/01_Examples`부터 `Docs/06_Publication`까지의 산출물 축 폴더에 둔다.
- 정책 정본은 `Docs/07_Policies`에 둔다.
- 도구와 템플릿은 `Docs/98_Tools`에 둔다.
- import 기록과 기존 Part 문서는 `Docs/99_Legacy`에 둔다.
- 초안, 민감 판단, GitHub 게시 전 본문은 `local/`에 둔다.

## 단계별 흐름

| 단계  | 작업                       | 읽는 위치                                                                       | 쓰는 위치                                    | 기준 정책                                        |
| --- | ------------------------ | --------------------------------------------------------------------------- | ---------------------------------------- | -------------------------------------------- |
| 0   | Work Unit 선택             | `Docs/00_Index`, root code folder                                           | `local/mini-plans` 또는 `Docs/05_WorkLogs` | 이 문서                                         |
| 1   | 코드 구조 확인                 | root `Part*_Chapter*`, `Portfolio_RayTracer`                                | 조사 메모는 `local/`                          | `agent-safety-policy.md`                     |
| 2   | 기존 문서와 raw reference 확인  | `Docs/99_Legacy/PartDocs`, `Docs/99_Legacy/ImportHistory`, raw/reference repo | 검토 메모는 `local/`                          | `local-review-policy.md`                     |
| 3   | 예제 목록과 대표 예제 결정          | code folder, legacy docs                                                    | `Docs/01_Examples`                       | `canonical-docs-policy.md`                    |
| 4   | 예제 설명 작성                 | code folder, local review                                                   | `Docs/01_Examples`                       | `docs-authoring-flow-policy.md`           |
| 5   | graphics Topic 작성        | example docs, code, raw reference                                           | `Docs/02_Topics`                         | `canonical-docs-policy.md`                    |
| 6   | build/run/capture 검증     | solution, executable, assets                                                | `Docs/03_Verification`                   | `verification-policy.md`                     |
| 7   | demo evidence 정리         | 실행 결과, capture 후보                                                           | `Docs/04_Demos`, `Docs/_assets`          | `demo-capture-policy.md`, `assets-policy.md` |
| 8   | public subset 판단         | example, topic, demo, asset 정보                                              | `Docs/06_Publication`                    | `publication-policy.md`                      |
| 9   | 작업 기록 마감                 | 변경된 Docs, 검증 결과                                                             | `Docs/05_WorkLogs`                       | `github-workflow-policy.md`                         |
| 10  | GitHub Issue/PR draft 작성 | WorkLog, Example, Verification, Demo                                        | `local/github/draft`                     | `github-workflow-policy.md`                         |
| 11  | Index 갱신                 | 전체 산출물                                                                      | `Docs/00_Index`                          | `canonical-docs-policy.md`                    |
| 12  | 최종 검수                    | 변경 파일 전체                                                                    | 검수 결과는 final report 또는 WorkLog           | `style-policy.md`, `../98_Tools/validation-tools.md` |

## 산출물별 책임

| 산출물          | 정본 위치                  | 내용                                             |
| ------------ | ---------------------- | ---------------------------------------------- |
| 예제 설명        | `Docs/01_Examples`     | 예제 목적, 핵심 코드 위치, 관련 Topic/Verification/Demo 링크 |
| Topic        | `Docs/02_Topics`       | 여러 예제를 관통하는 graphics 개념과 pipeline 설명           |
| Verification | `Docs/03_Verification` | build/run/capture 상태, known issue, 확인 일자       |
| Demo         | `Docs/04_Demos`        | capture/video evidence, 시연 포인트, 연결 개념          |
| WorkLog      | `Docs/05_WorkLogs`     | 작업 범위, 변경 요약, 검증 요약, Issue/PR 연결, follow-up    |
| Publication  | `Docs/06_Publication`  | public 후보, private 전용, 검토 필요, 제외 판단            |
| Policy       | `Docs/07_Policies`     | 반복 적용되는 규칙                                     |
| Tool         | `Docs/98_Tools`        | validator, template, troubleshooting           |
| Legacy       | `Docs/99_Legacy`       | 이전 문서와 import 기록                               |

## local 사용 기준

`local/`은 tracked Docs로 승격하기 전 작업장이다.

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
- 게시 후 보존 사본은 `local/github/public` 또는 `local/github/snapshots`에 둔다.
- redaction, 공개 제외 판단 근거, 개인 메모는 tracked Docs에 두지 않는다.


## Template 연결

| 단계 | Template |
| --- | --- |
| 예제 설명 작성 | `Docs/98_Tools/templates/example-readme.md` |
| Topic 작성 | `Docs/98_Tools/templates/topic.md` |
| local study review | `Docs/98_Tools/templates/local-study-review.md` |
| publication review | `Docs/98_Tools/templates/local-publication-review.md` |
| WorkLog 마감 | `Docs/98_Tools/templates/worklog.md` |
| 최종 검수 | `Docs/98_Tools/validation-tools.md` |
## Done 기준

Work Unit은 다음 조건을 만족할 때 완료 상태로 둔다.

- 예제 설명 정본이 `Docs/01_Examples`에 있다.
- 관련 Topic이 없으면 없다고 기록하고, 있으면 `Docs/02_Topics`에 연결한다.
- build/run/capture 상태가 `Docs/03_Verification`에 기록되어 있다.
- demo 필요 여부와 evidence 상태가 `Docs/04_Demos`에 기록되어 있다.
- public subset 판단이 `Docs/06_Publication`에 기록되어 있다.
- 작업 요약과 follow-up이 `Docs/05_WorkLogs`에 기록되어 있다.
- `Docs/00_Index` map이 필요한 범위만큼 갱신되어 있다.
- 오래된 `Docs/99_Legacy` 문서를 정본처럼 링크하지 않는다.
