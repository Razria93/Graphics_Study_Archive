# Part4 Output Completeness Audit Checklist

이 문서는 `Part4_Chapter14-20`의 정규 Work Unit 산출물이 작성 순서와 책임 경계에 맞게 갖추어졌는지 전수감사할 때 사용하는 기준이다. 최신 상태 정본을 대체하지 않으며, 감사 결과는 [Document System Audit Report](templates/document-system-audit-report.md)에 기록한다.

## 목적

- 빠른 capture, storyboard, 상세 Demo 작성이 Topic, Verification, index, WorkLog, Publication 판단을 앞지르지 않았는지 확인한다.
- 예제별 사실과 Part 또는 Chapter 단위 지도 문서의 상태가 같은 증거를 가리키는지 확인한다.
- 누락 산출물, 의도적으로 제외한 산출물, 직접 검증이 필요한 산출물을 구분한다.
- Part4의 23개 Example에 대한 상세 Demo 작성 결정과 일반 정책의 대표 Demo 원칙을 분리한다.

## 적용 범위와 판정값

대상은 `Ex1401`부터 `Ex2001`까지 23개 Example, `Part4_Chapter14-20/README.md`, 그리고 `Docs`의 관련 정본 축이다. `Docs/99_Legacy`와 `local/`은 provenance 확인용으로만 읽고 현재 정본 누락 여부를 대신하지 않는다.

| 판정 | 의미 | 감사 처리 |
| --- | --- | --- |
| 충족 | 책임 정본, 연결, 상태 근거가 현재 코드와 직접 검증 기록에 맞음 | 근거 경로를 기록함 |
| 미충족 | 필요한 정본, 연결, 판정 또는 직접 증거가 없음 | P0, P1, P2 심각도를 판정함 |
| 의도적 제외 | 해당 축이 적용되지 않으며 이유와 책임 문서가 있음 | 제외 사유와 재검토 조건을 기록함 |
| 미확인 | 직접 검증 또는 사용자 판단이 아직 없음 | 성공 또는 확보로 승격하지 않음 |
| historical snapshot | WorkLog 등 과거 시점 기록이며 최신 정본과 비교 대상이 아님 | 현재 상태를 주장할 때만 충돌로 판정함 |

## 감사 선행 조건

- [Document System Audit Policy](../06_Policies/document-system-audit-policy.md)의 `Chapter` 감사로 시작한다.
- 시작 전 worktree의 기존 변경을 기록하고 감사 중에는 tracked 파일을 수정, stage, commit하지 않는다.
- [Canonical Docs Policy](../06_Policies/canonical-docs-policy.md)와 [Docs Authoring Flow Policy](../06_Policies/docs-authoring-flow-policy.md)를 책임 기준으로 사용한다.
- 현재 코드, Example README, 직접 build/run/capture 기록을 우선하고 기존 tracked Docs와 Legacy는 검증 대상이지 정답으로 가정하지 않는다.
- raw MP4, runtime HDRI, character, foliage, terrain asset은 Git 승격 대상이 아니다. rendered evidence와 원본 asset을 구분한다.

## 기준선 Inventory

감사 시작 시 아래 표를 채운다. 파일 존재만으로 `충족`으로 판정하지 않고, 연결과 내용 책임까지 확인한다.

| 축 | 필수 확인 대상 | 완료 조건 |
| --- | --- | --- |
| Chapter 지도 | `Part4_Chapter14-20/README.md` | 23개 Example 범위, 현재 검증 요약, 대표 Topic, Demo, Verification 링크와 후속 범위가 최신 정본을 가리킴 |
| Example README | 23개 Example 코드 폴더 `README.md` | 목적, 실행 진입점, 주요 코드 위치, 고유 구조, limitation, 관련 정본 링크가 있음 |
| Topic | `Docs/01_Topics` group README와 topic-index | concept group별 후보, 우선순위, 관련 Example, 상세 Topic 또는 부재 사유가 있음 |
| Verification | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md`와 관련 known issue | Example별 build/run/capture 상태, configuration, 날짜, evidence 유형, 미확인 범위가 직접 근거와 일치함 |
| Demo | `Docs/03_Demos/Part4_Chapter14-20/demo-index.md`와 Example별 상세 Demo | Demo 필요 여부, capture/result, 결과 해석, limitation, Verification 연결이 있음 |
| Asset registry | `Docs/_assets/captures/README.md`와 연결 PNG | tracked asset, source provenance, metadata 검사, 사용 문서가 일치함 |
| WorkLog | `Docs/04_WorkLogs/work-units/WU-Part4.md`와 필요 review | Work Unit 결정, 최신 산출물 연결, 후속 작업, README 미갱신 사유가 있음 |
| Publication | `Docs/05_Publication/candidate-list.md`, `private-only.md`, `excluded-material.md` | rendered evidence와 원본 asset의 공개 위험, 후보 또는 제외 판단, 재검토 조건이 있음 |
| GitHub | `Docs/07_GitHub`와 WorkLog GitHub index | 게시한 Chapter만 Issue, PR, comment 상태와 source 정본이 일치함. 미게시 Chapter는 미게시가 정상 상태임 |
| Index와 도구 | `Docs/00_Index`, folder README, templates, validators | 새 정본의 진입점과 반복 검사 범위가 필요한 만큼 연결됨 |

## 책임 축별 전수 기준

### 1. Chapter와 Example README

- Chapter README의 Example 수와 command argument 범위가 `Examples.sln`과 일치하는지 확인한다.
- Chapter README는 Topic, Verification, Demo 정본을 링크하고 상세 구현 또는 과거 조사 기록을 복제하지 않는지 확인한다.
- 23개 Example README가 모두 존재하는지 확인한다.
- 각 Example README는 실행 argument, source 또는 shader anchor, 예제 고유 구조, limitation, 관련 Topic/Verification/Demo 연결을 갖추는지 확인한다.
- capture/result를 연결한 Example README는 대표 visual을 최대 1개만 사용하고 다중 frame 해석은 상세 Demo에 위임하는지 확인한다.

### 2. Topic

Topic은 모든 Example에 하나씩 만드는 문서가 아니다. 여러 Example을 관통하는 개념을 설명하는 독립 축이며, Part4에서는 아래 판정이 필요하다.

| Concept group | 연결 후보 | 감사 확인 |
| --- | --- | --- |
| Compute And Simulation | `Ex1401`부터 `Ex1606`까지 | Compute Shader, GPU Simulation, Resource Synchronization 후보의 우선순위와 상세 Topic 승격 또는 보류 사유 |
| Animation And Physics | `Ex1701`, `Ex1901`, `Ex2001` | skeletal animation, rigid-body simulation, gameplay integration을 하나의 Topic 또는 분리 Topic으로 다룰 근거 |
| Foliage And Landscape Rendering | `Ex1801`부터 `Ex1803`까지 | instancing, wind animation, terrain/ocean rendering Topic의 group 위치와 작성 또는 보류 사유 |

- Topic group마다 `README.md`와 `topic-index.md`가 있는지 확인한다.
- `P0`로 승격한 Topic은 `목적`, `책임 범위`, `핵심 개념`, `한계`, `관련 문서`를 갖추고 Topic validator를 통과하는지 확인한다.
- `P1` 또는 `P2` Topic은 topic-index에 후보, 연결 Example, 우선순위, 작성 또는 보류 기준을 기록하는지 확인한다.
- Chapter README, Example README, Demo index의 Topic 표기가 상세 Topic, topic-index, 또는 명시된 부재 사유 중 하나로 연결되는지 확인한다.
- Topic은 build/run 성공이나 storyboard timestamp를 소유하지 않고 Verification과 Demo로 위임하는지 확인한다.

### 3. Verification과 evidence provenance

- 23개 Example 각각에 Debug/Release build와 run 상태, 확인 날짜, command argument, working directory 또는 runtime precondition, capture 필요성 또는 제외 사유가 있는지 확인한다.
- 과거 확인과 현재 재검증을 같은 `성공`으로 합치지 않는지 확인한다.
- stdout-only Example은 screenshot 부재를 결함으로 분류하지 않고 stdout 결과와 exit code를 evidence로 기록하는지 확인한다.
- dynamic Example의 tracked storyboard는 `storyboard-final`과 manifest timestamp를 직접 사용하고, 별도 재합성, crop, resize, 임의 frame 선택을 하지 않았는지 확인한다.
- capture 상태, asset registry, Demo 설명의 filename, frame 수, timestamp, dimension, asset 주의가 서로 일치하는지 확인한다.
- known issue와 runtime DLL, asset, stability 조건이 실제 재현 가능성에 영향을 주면 Verification에서 연결하는지 확인한다.

### 4. Demo와 asset

- `Docs/03_Demos`는 Example별 기술 구현 흐름과 시각 결과의 정본이다. 모든 Part의 실제 관행과 Part4 요구에 따라 23개 모든 Example의 독립 상세 Demo를 작성 대상으로 둔다.
- 대표 Example과 대표 visual의 선별은 상세 Demo 축이 아니라 `Docs/07_GitHub/issues/demo`의 Chapter별 curated publication view에서만 적용한다.
- 따라서 `14_01`부터 `20_01`까지 23개 상세 Demo의 존재, Example 연결, Verification 연결, Topic 연결 또는 부재 사유를 확인한다.
- 각 상세 Demo는 구현 목표, 입력과 출력, 처리 흐름, 구현 선택, 주요 코드, 시각 결과, trade-off 또는 limitation, 관련 문서를 책임 범위로 갖는지 확인한다.
- visual capture가 부적합하거나 불필요한 Example은 `없음`으로 비워 두지 않고 stdout-only, local-only, 제외, 후속 촬영 중 하나로 이유를 기록하는지 확인한다.
- `demo-index.md`의 Example 범위, 상세 Demo 링크, asset 링크, 상태, “후속” 문구가 실제 상세 Demo 및 asset 상태와 일치하는지 확인한다.
- tracked PNG는 `Docs/_assets/captures/README.md`에 등록하고, original runtime asset을 직접 첨부하거나 링크하지 않는지 확인한다.

### 5. WorkLog, Publication, GitHub

- `WU-Part4.md`는 현재 Work Unit의 결정과 완료 또는 후속 범위를 최신 정본에 연결하는지 확인한다. 오래된 후보 선정과 현재 asset 승격 결과가 충돌하면 현재 정본을 기준으로 WorkLog 갱신 필요성을 발견으로 기록한다.
- WorkLog는 Example, Topic, Verification, Demo, Publication 본문을 복제하지 않는지 확인한다.
- Publication은 모든 Part4 evidence에 대해 `검토 필요`, `public 후보`, `private-only`, `excluded` 중 하나와 asset 위험 판단을 기록하는지 확인한다.
- HDRI, character, foliage, terrain을 포함한 capture는 원본 권리 보유를 주장하지 않고 rendered evidence만 다루는지 확인한다.
- GitHub Demo Issue는 Chapter당 하나의 curated publication view로 확인한다. 해당 Issue는 대표 visual과 핵심 구현 요약만 포함하고 모든 상세 Demo를 복제하지 않는지 확인한다.
- GitHub Issue, PR, comment는 게시된 Chapter에만 확인한다. 아직 게시하지 않은 Chapter의 body 부재는 결함이 아니며, WorkLog에 게시 필요 여부와 후보 상태가 기록되었는지 확인한다.

### 6. Index, 링크, validator

- `Docs/00_Index`와 Part4 Chapter README가 현재 문서 진입점 역할을 하며 Topic, Verification, Demo로 이동 가능한지 확인한다.
- 상대 링크, asset 링크, GitHub source link가 실제 대상에 도달하는지 확인한다.
- current 문서가 `Docs/99_Legacy`, `Docs/01_Examples`, `local/`을 현재 정본처럼 직접 링크하지 않는지 확인한다.
- Demo, Topic, GitHub, Markdown render/table/wrap validator 결과를 감사 기준선과 종료 시점에 같은 조건으로 기록한다.
- validator 통과와 의미적 완결성을 구분하고, 책임 중복, Topic 부재 사유, snapshot 시점 차이는 수동 판정으로 남긴다.

## Part4 우선 확인 항목

아래 항목은 현재 inventory에서 이미 확인할 수 있는 감사 출발점이다. 감사 전에는 해결로 간주하지 않는다.

| ID | 우선 항목 | 현재 관찰 | 감사 판정 기준 |
| --- | --- | --- | --- |
| P4-COMP-001 | Topic 실체 | Compute And Simulation topic-index의 모든 항목이 `예정`이며 상세 Topic이 없음 | 우선순위, 보류 사유, 상세 Topic 승격 계획 또는 의도적 제외가 정본에 있는지 확인 |
| P4-COMP-002 | Animation/foliage Topic routing | Part4 README에는 주제 후보가 있으나 group별 정본 연결이 완결되지 않음 | 적절한 Topic group, index, Example/Demo 링크 또는 부재 사유를 확인 |
| P4-COMP-003 | Chapter19와 Chapter20 상세 Demo | Demo index가 `후속`으로 표시하고 상세 Demo 파일이 없음 | `Ex1901`, `Ex2001` 독립 상세 Demo와 index/verification/asset 연결을 확인 |
| P4-COMP-004 | Demo index 최신성 | Chapter16부터 Chapter20까지 storyboard 확보 상태와 “대표 storyboard” 및 후속 문구가 섞여 있음 | 23개 상세 Demo, 12개 storyboard, stdout-only 또는 제외 상태를 현재 상태로 분리하는지 확인 |
| P4-COMP-005 | WorkLog 최신성 | WU-Part4의 8개 storyboard 후보 기록과 이후 12개 final storyboard, 상세 Demo 확장이 시점상 분리됨 | historical snapshot인지, 최신 산출물과 충돌하는 현재 주장인지 판정 |
| P4-COMP-006 | README 완료 주장 | Chapter README의 Demo/next action과 실제 Chapter19와 Chapter20 상세 Demo 부재가 함께 존재함 | 완료 문구, 다음 작업, 정본 링크가 같은 현재 상태를 설명하는지 확인 |

## 감사 실행 순서

1. `문서 전수감사 시작`이 아니라 Part4만 다루는 `Chapter` read-only 감사로 범위를 선언한다.
2. 기준선 worktree와 validator 결과를 기록한다.
3. 23개 Example을 행으로 둔 inventory를 작성하고 Chapter, Example README, Topic, Verification, Demo, asset, Publication, WorkLog, GitHub 열을 채운다.
4. 책임 축별 기준으로 누락, 충돌, 의도적 제외, 미확인을 분류한다.
5. 발견은 root cause 단위로 통합하고 [Document System Audit Report](templates/document-system-audit-report.md)의 P0/P1/P2 표에 기록한다.
6. 수정, stage, commit은 `감사 결과 반영 시작` 승인 뒤에만 수행한다.

## 완료 조건

- 23개 Example 모두가 inventory에 한 행으로 존재한다.
- Topic, Verification, Demo, asset, WorkLog, Publication, GitHub의 적용 여부와 부재 사유가 구분된다.
- 직접 검증한 사실, historical snapshot, candidate, 미확인이 같은 상태로 혼합되지 않는다.
- 모든 발견에 책임 정본, 근거 경로, 권장 수정, 자동 수정 가능 여부, 사용자 판단 항목이 있다.
- 감사 종료 시 수정하지 않은 worktree 상태와 commit 불필요 상태를 보고한다.