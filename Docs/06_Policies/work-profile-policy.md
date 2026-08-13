# Work Profile Policy

이 문서는 저장소 작업을 `Graphics Work`와 `Maintenance Work` 두 profile로 분류하고, 각 profile의 필수 산출물, 내부 작업 순서, 검증과 사용자 검수용 완료 후보 조건을 정의한다. 공통 lifecycle과 Work Unit 종료 조건은 [Work Unit Workflow Policy](work-unit-workflow-policy.md)를 따른다.

## 기본 원칙

- 모든 작업은 수정 전에 두 profile 중 하나를 선택한다.
- Part1부터 Part4까지의 기존 graphics example 정리와 `Portfolio_GraphicsLab` 구현·재구성은 모두 `Graphics Work`로 분류한다.
- Policy, workflow, README 탐색 경로, template, validator, 문서 구조와 정합화는 `Maintenance Work`로 분류한다.
- Archive, GraphicsLab Development와 Terminal Maintenance 같은 추가 작업 유형을 만들지 않는다.
- Work Unit 또는 Progress 단위 종료 여부는 작업 유형이 아니라 `Closes Work Unit`과 `Progress impact` 속성으로 표현한다.
- 작업 유형은 필요한 산출물과 검증을 결정하고, Work Unit 정책은 상태와 마감 lifecycle을 결정하며, GitHub 정책은 승인과 remote 실행을 결정한다.

## 공통 Work Contract

모든 작업은 조사나 수정 전에 다음 contract를 확정한다. 반복 사용하는 초안은 [Work Contract](../98_Tools/templates/work-contract.md)를 사용한다.

| 항목 | 허용 값과 책임 |
| --- | --- |
| `Work type` | `Graphics` 또는 `Maintenance` |
| `Work Unit` | 연결된 Work Unit 또는 `없음` |
| `Closes Work Unit` | `Yes` 또는 `No` |
| `Progress impact` | `Required`, `Not required` 또는 `Pending` |
| `Goal` | 이번 branch에서 만들어야 하는 최종 상태 |
| `Scope` | 조사·수정·검증 대상 |
| `Excluded` | 이번 작업에서 다루지 않는 대상 |
| `Required artifacts` | 선택한 profile에서 판정할 산출물 |
| `Validation profile` | 산출물과 변경 영향에 맞는 검증 |
| `Completion condition` | 사용자 검수, review, merge와 remote 동기화를 포함한 종료 조건 |

`Progress impact: Pending`은 계획 시점의 임시 값이다. 확정 시점과 이후 단계의 진입 조건은 [Work Unit Workflow Policy](work-unit-workflow-policy.md)를 따른다.

이미 진행 중인 branch에 명시적인 Work Contract가 없으면 branch diff, PR body와 상태, WorkLog, Work Unit Index와 GitHub Index를 읽어 현재 contract를 복원한다. 작업 유형, 종료 여부 또는 필수 산출물을 근거로 판정할 수 없으면 일반적인 merge 절차만 제시하지 않고 사용자에게 누락된 결정을 요청한다.

## 산출물 판정

선택한 profile의 각 산출물은 다음 상태 중 하나로 판정한다.

| 상태 | 의미 |
| --- | --- |
| `Created` | 새 산출물을 만든다. |
| `Updated` | 기존 정본을 현재 작업 결과에 맞게 갱신한다. |
| `Linked` | 기존 정본이 충분해 연결만 확인하거나 추가한다. |
| `N/A` | 현재 작업에 적용되지 않으며 그 이유를 기록한다. |

산출물 판정은 새 파일 생성을 강제하는 checklist가 아니다. 각 축을 빠짐없이 검토해 의도적 제외와 누락을 구분하는 contract다. `N/A`에는 이유가 필요하며, 아무 기록 없이 산출물을 생략할 수 없다.

## Graphics Work

### 정의와 범위

`Graphics Work`는 graphics 기능을 구현·재구성·확장하거나 기존 구현을 검증하고 설명 가능한 결과로 만드는 작업이다.

- Part1부터 Part4까지의 기존 graphics example 분석·정리·검증
- `Portfolio_GraphicsLab` 신규 구현과 reconstruction
- ray tracing, rasterization와 graphics pipeline 구현
- shader, material, lighting와 simulation 구현
- graphics 결과에 연결된 build, run과 capture

기존 예제를 archive로 정리하는지 새 canonical code를 구현하는지는 조사와 구현 범위의 차이다. 두 경우 모두 구현 핵심 구조, 사용한 원리, 직접 검증과 시각 결과를 같은 Graphics 산출물 축으로 판정한다.

### 산출물 profile

| 산출물 | 정본 또는 결과 | 요구 내용 |
| --- | --- | --- |
| Implementation | 루트 코드 폴더 | 실제 source, shader, asset 또는 reconstruction 결과 |
| Structure | 코드 폴더 README 또는 architecture/decision 정본 | 책임 구조, 처리 흐름과 주요 코드 위치 |
| Topic | `Docs/01_Topics` | 구현에 사용한 graphics 이론·원리 또는 기존 Topic 연결 |
| Verification | `Docs/02_Verification` | build, test, run, capture 결과와 직접 확인 범위 |
| Demo | `Docs/03_Demos`, `Docs/_assets` | 입력·처리·출력, 구현 선택과 시각 결과 |
| README | 대상 코드 폴더 README | 구현 목적, 진입점, 핵심 구조, 제한과 정본 링크 |
| WorkLog | `Docs/04_WorkLogs` | 목표, 결정, 검증, 제한과 다음 작업 |
| PR body | `Docs/07_GitHub/prs` | reviewer용 구현·결과·검증 요약과 정본 링크 |
| Index | `Docs/00_Index`부터 `Docs/04_WorkLogs`의 대응 index | 변경된 Topic, Verification, Demo와 Work Unit 연결 |
| Progress | `Docs/07_GitHub/plan` | 의미 있는 Phase 또는 Work Unit의 진행·마감 payload |

모든 Graphics Work에서 새 Topic이나 Demo 파일을 만들 필요는 없다. 기존 정본이 충분하면 `Linked`로 판정하고, scaffold처럼 시각 결과를 의도적으로 만들지 않는 작업은 `Demo: N/A`와 이유를 기록한다.

### Profile 작업 순서

1. Work Contract를 확정한다.
2. current code, raw/reference와 기존 정본을 조사한다.
3. 구현 목표, 구조, Topic과 Demo 계획을 확정한다.
4. 코드 또는 graphics 기능을 구현한다.
5. 관련 build, test와 run을 검증한다.
6. 필요한 Demo capture/result를 생성하고 검수한다.
7. README, Topic, Verification과 Demo 정본을 작성하거나 연결한다.
8. WorkLog, Index, PR body와 필요한 Progress payload를 작성한다.
9. 산출물 판정과 제한을 정리해 사용자 검수 가능한 완료 후보로 만든다.

Current/raw/reference 조사와 문서 작성의 세부 기준은 [Docs Authoring Flow Policy](docs-authoring-flow-policy.md)를 따르고, build/run/capture는 [Verification Policy](verification-policy.md)와 [Demo Capture Policy](demo-capture-policy.md)를 따른다.

### 검증 profile

- 변경한 source와 project에 대응하는 build, test와 run
- 직접 확인한 결과와 `미확인`·실패·제한의 분리
- Topic과 구현 설명의 code 정합성
- Demo 입력·처리·출력과 capture/result의 시각 검수
- README, Verification, Demo, WorkLog와 Index 연결
- 변경된 Markdown과 GitHub body validator
- `git diff --check`와 작업 범위 밖 변경 부재

### Profile 완료 후보 조건

- 약속한 기능 또는 reconstruction 결과가 구현됐다.
- 관련 build, test와 run을 직접 확인했거나 확인하지 못한 이유를 기록했다.
- 모든 Graphics 산출물을 `Created`, `Updated`, `Linked`, `N/A` 중 하나로 판정했다.
- README, Topic, Verification, Demo와 WorkLog가 현재 구현과 일치한다.
- 필요한 Index, PR body와 Progress payload가 준비됐다.

사용자 검수 이후의 공통 lifecycle은 [Work Unit Workflow Policy](work-unit-workflow-policy.md)를 따른다.

## Maintenance Work

### 정의와 범위

`Maintenance Work`는 graphics 결과를 새로 만드는 대신 저장소와 협업 체계를 유지·보완하는 작업이다.

- Policy와 workflow
- README 탐색 경로
- Template과 validator
- 문서 구조와 책임 경계
- 링크, 명칭과 상태 정합화
- Build configuration만 다루는 기반 정리
- PR body 형식과 GitHub 운영 규칙

### 산출물 profile

| 산출물 | 정본 또는 결과 | 요구 내용 |
| --- | --- | --- |
| Maintenance change | 대상 policy, README, template, validator 또는 설정 | 승인된 문제를 해결하는 최소 변경 |
| Rationale | 변경 문서, decision 또는 WorkLog | 기존 문제가 무엇이고 어떤 책임 경계로 교정했는지 설명 |
| Impact | 변경 문서와 PR body | 영향받는 workflow, 문서, validator와 사용자 작업 |
| Regression verification | validator, fixture, link/render 검사 또는 관련 build/test | 변경이 기존 계약을 깨지 않는다는 근거 |
| Maintenance PR body | `Docs/07_GitHub/prs` | 요약, 범위, 주요 변경, 검증, 제한과 다음 단계 |
| WorkLog | 조건부 `Docs/04_WorkLogs` | Work Unit 연결 또는 결정 보존 가치가 있을 때 작성·갱신 |
| Index | 조건부 대응 index | 실제 연결, 상태 또는 문서 구조가 바뀔 때만 갱신 |
| Progress | 조건부 `Docs/07_GitHub/plan` | 의미 있는 Phase 또는 Work Unit을 종료할 때만 갱신 |

Maintenance Work에는 graphics Topic, Demo, screenshot/video, graphics build/run, Example README와 Publication 판단을 기본 산출물로 요구하지 않는다. Build 또는 실행 계약을 바꾸면 관련 build/test를 Regression verification에 포함하되 작업 유형은 Maintenance로 유지한다.

### Profile 작업 순서

1. Work Contract를 확정한다.
2. 현재 policy, 문서, 도구와 문제 원인을 조사한다.
3. 책임 경계와 최소 수정 범위를 확정한다.
4. Policy, README, template, validator 또는 설정을 수정한다.
5. 관련 regression과 문서 검증을 수행한다.
6. Maintenance PR body와 필요한 WorkLog, Index와 Progress payload를 작성한다.
7. 산출물 판정과 제한을 정리해 사용자 검수 가능한 완료 후보로 만든다.

### 검증 profile

- 문제 원인과 실제 수정 책임의 일치
- 현재 정책, README, template과 validator 사이의 중복·충돌 부재
- 변경 영향에 대응하는 regression validator와 fixture
- 상대 링크, Markdown render/table/wrap과 strict UTF-8
- GitHub body를 변경한 경우 대응 body validator
- Build 또는 실행 계약을 변경한 경우 관련 build/test
- `git diff --check`와 작업 범위 밖 변경 부재

### Profile 완료 후보 조건

- 문제 원인과 수정 책임이 일치한다.
- 반대되는 정본이나 중복된 규칙이 남지 않는다.
- 관련 regression, 문서와 필요한 build/test 검증이 통과한다.
- 변경한 README와 router의 탐색 경로가 실제로 작동한다.
- Maintenance PR body가 변경 범위, 영향과 검증 결과를 설명한다.

사용자 검수 이후의 공통 lifecycle은 [Work Unit Workflow Policy](work-unit-workflow-policy.md)를 따른다.

## 공통 lifecycle 연결

`Closes Work Unit`과 `Progress impact`는 profile 산출물의 종류가 아니라 공통 lifecycle의 finalization과 terminal 조건을 결정한다. Work Unit 마감 산출물, 상태 전환, 단계별 완료와 복귀 조건은 [Work Unit Workflow Policy](work-unit-workflow-policy.md)만 정의한다. GitHub 승인과 remote 실행 방법은 [GitHub Workflow Policy](github-workflow-policy.md)를 따른다.
