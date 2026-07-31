# Document System Audit Policy

이 문서는 Graphics Study Archive의 문서 체계를 반복 검수하는 감사 기준과 승인 경계를 정의한다.

## 목적

- 문서 정합성, 탐색 흐름, 책임 분리, 상태, 링크를 함께 검수한다.
- 정책, template, validator가 같은 기준을 표현하는지 확인한다.
- 자동 검사가 놓치는 의미 충돌을 근거가 있는 발견 항목으로 기록한다.
- 감사와 수정 단계를 분리해 사용자 판단 전에 정본을 바꾸지 않는다.

## 책임 경계

- 문서 정본 위치와 축별 책임은 [Canonical Docs Policy](canonical-docs-policy.md)를 따른다.
- 일반 문서 작성 순서는 [Docs Authoring Flow Policy](docs-authoring-flow-policy.md)를 따른다.
- commit과 되돌리기 어려운 작업은 [Agent Safety Policy](agent-safety-policy.md)를 따른다.
- GitHub remote 변경 승인은 [GitHub Workflow Policy](github-workflow-policy.md)를 따른다.
- 실행 절차는 [Document System Audit Guide](../98_Tools/document-system-audit-guide.md)에 둔다.
- 보고 형식은 [Document System Audit Report](../98_Tools/templates/document-system-audit-report.md)를 사용한다.

이 정책은 기존 정본 위계나 Verification 상태값을 새로 정의하지 않는다. 감사에서 필요한 변경은 발견 항목으로 제안하고 해당 책임 정책에서 확정한다.

## 감사 유형

| 유형 | 범위 | 목표 모드 | 하위 에이전트 |
| --- | --- | --- | --- |
| `Single` | 지정 문서와 직접 연결된 정본 | 선택 | 기본 미사용 |
| `Impact` | 현재 변경과 영향을 받는 문서 | 권장 | 최대 2개 |
| `Chapter` | Chapter와 연결된 전체 문서 축 | 권장 | 최대 2개 |
| `Full` | 저장소 전체 문서 체계 | 사용 | 최대 3개 |

목표 모드를 지원하면 감사 목적과 완료 조건을 목표로 등록한다. 지원하지 않으면 같은 내용을 작업 계획으로 유지한다. 목표 기능 부재는 감사 중단 사유가 아니다.

## 에이전트 구성

- `Full` 감사에는 메인 에이전트를 포함해 최대 4개 concurrency slot을 사용한다.
- 하위 에이전트는 architecture, state/link, policy/quality 관점을 분리한다.
- 하위 에이전트는 read-only 조사만 수행한다.
- 메인 에이전트는 적용되는 `AGENTS.md`를 직접 확인한다.
- 메인 에이전트는 하위 결과의 경로, line, 문맥, 중복, 충돌, 오탐을 재검증한다.
- 최종 발견은 여러 증상을 하나의 root cause로 통합한다.

하위 에이전트나 concurrency 기능을 지원하지 않으면 메인 에이전트가 세 관점을 순서대로 조사한다.

## Workflow Keyword

자연어 keyword는 플랫폼 내장 command가 아니라 저장소 workflow contract다.

| Keyword | 해석과 기본 권한 |
| --- | --- |
| `문서 단일검수 시작: <경로>` | `Single`, read-only, 목표 모드 선택, 하위 에이전트 기본 미사용 |
| `문서 영향감사 시작` | `Impact`, read-only, 목표 모드 권장, 하위 에이전트 최대 2개 |
| `문서 전수감사 시작` | `Full`, read-only, 목표 모드 사용, remote read-only, 하위 에이전트 최대 3개 |
| `감사 결과 반영 시작: <보고서 또는 DOC ID>` | 식별 가능한 발견 항목의 로컬 수정만 승인 |
| `감사 결과 게시 시작: <대상과 작업>` | 명시된 remote 대상과 작업을 기존 GitHub 승인 절차로 전달 |

`문서 전수감사 시작`은 지원되는 환경에서 목표 모드와 최대 3개의 read-only 하위 에이전트 사용을 명시적으로 요청한 것으로 해석한다.

`감사 결과 반영 시작`에는 commit과 remote 변경이 포함되지 않는다. 기준 보고서나 DOC ID가 모호하거나 사용자 결정이 남아 있으면 수정하지 않고 범위를 확인한다.

`감사 결과 게시 시작`은 포괄적인 remote 변경 승인이 아니다. 대상, 작업, 게시 후보를 식별하고 `GitHub Workflow Policy`의 사전 보고와 승인 기준을 따른다.

```text
감사 결과 게시 시작:
- 대상: PR #8
- 작업: body 갱신
- 게시 후보: Docs/07_GitHub/prs/part1_chapter01-02.md
```

## Read-only 감사

허용 범위:

- tracked 파일, Git history, branch와 worktree 상태 읽기
- inventory, validator, 링크 대상 존재 검사
- GitHub Issue와 PR 상태의 read-only 조회
- console 또는 임시 출력 분석
- 대화 안에서 감사 보고서와 수정 작업 묶음 작성

금지 범위:

- tracked 파일 수정
- stage와 commit
- branch 상태 변경
- GitHub Issue, PR, comment 변경
- tracked 감사 snapshot 생성

감사 결과를 `Docs/04_WorkLogs/reviews`에 기록하는 작업은 read-only 감사가 끝나고 사용자가 문서화를 승인한 별도 단계로 수행한다.

## 정본 비교 기준

감사는 `Canonical Docs Policy`의 책임 축을 기준으로 같은 사실을 교차검증한다.

| 비교 항목 | 책임 정본 |
| --- | --- |
| repository와 Chapter 진입 흐름 | Root, Chapter, Example README, `Docs/00_Index` |
| graphics 개념과 이론 | `Docs/01_Topics` |
| build/run/capture 사실 | `Docs/02_Verification` |
| demo capture/result와 시연 설명 | `Docs/03_Demos`, `Docs/_assets` |
| 작업 당시 결정과 snapshot | `Docs/04_WorkLogs` |
| 공개 후보와 제외 판단 | `Docs/05_Publication` |
| 반복 운영 규칙 | `Docs/06_Policies` |
| GitHub 게시 후보 | `Docs/07_GitHub` |
| template과 validator | `Docs/98_Tools` |

WorkLog의 과거 snapshot과 최신 정본의 차이는 자동으로 오류로 분류하지 않는다. 두 문서가 같은 시점의 현재 상태를 주장할 때만 상태 충돌로 판정한다.

## 발견 항목과 심각도

- `P0`: 깨진 현재 링크, 잘못된 정본, 공개 위험, 확인된 사실과 다른 상태
- `P1`: 책임 또는 상태 충돌, provenance 단절, 잘못된 탐색 흐름, 정책·template·validator 충돌
- `P2`: 이름, 문체, 표현, 탐색성, 유지보수성과 자동화 coverage

심각도는 가능성이 아니라 확인된 영향으로 정한다. 판단이 부족한 항목은 심각도를 임의로 낮추지 않고 확인 사항을 별도로 기록한다.

각 발견 항목에는 다음 정보를 둔다.

- 고유 ID와 심각도
- 실제 파일 경로와 가능한 line
- 직접 관찰한 증거와 문제인 이유
- 책임 정본과 권장 수정
- 함께 수정할 관련 파일
- 자동 수정 가능 여부
- 오탐 가능성 또는 확인 사항
- 사용자 판정
- `확정`, `재분류`, `철회`, `보류`, `반영 완료` 중 항목 상태

## Validator와 수동 감사

Validator는 반복 가능한 기계 검사를 담당한다.

- 실제 대상이 없는 상대 링크
- 금지된 current path
- placeholder와 필수 section 누락
- 허용하지 않는 상태값과 형식
- 추적되지 않는 공개 asset
- 같은 문단·목록 항목을 나눈 명백한 인위적 soft-wrap

문맥에 따라 사실 확인이 필요한 항목은 warning 후보로 다룬다.

- 서로 다른 축의 상태 문자열 차이
- 필수 탐색 링크 후보 누락
- 절대 로컬 경로와 내부 workflow 표현
- 여러 문서의 capture 또는 설명 중복

다음 항목은 수동 감사에 남긴다.

- 정본 책임 충돌과 실질적인 설명 중복
- Topic, Example, Demo의 의미 경계
- 탐색 흐름의 자연스러움
- 역사 정보의 필요성과 provenance 신뢰도
- public-facing narrative 품질
- 자동 판정이 어려운 문장 흐름과 렌더링 가독성

Validator 통과는 전체 문서 감사 통과를 의미하지 않는다.

공개·레이아웃 민감 문서의 실제 GitHub UI는 Browser로 표본 검수한다. Browser에서 확인된 반복 가능한 구조 결함은 validator와 fixture 후보로 환류하며, 자동 검사 통과를 실제 렌더링 확인으로 대체하지 않는다. 표본 선택과 판정 절차는 [Validation Tools](../98_Tools/validation-tools.md)를 따른다.

## Legacy와 오탐

- `Docs/99_Legacy` 내부의 폐기 경로와 역사 기록은 현재 문제로 계산하지 않는다.
- 현재 정본이 Legacy를 최신 정본처럼 연결할 때만 문제로 분류한다.
- template의 placeholder와 설명용 예시 경로는 실제 산출물 링크와 구분한다.
- 금지 문자열을 찾는 validator source 자체는 stale path 문제로 분류하지 않는다.
- `local/` 위치를 정책상 설명하는 문장과 tracked 문서가 `local/`로 직접 이동시키는 링크를 구분한다.

## 원격 상태 확인

Remote read-only 조회는 로컬 기록과 실제 Issue/PR 상태를 비교할 때 사용할 수 있다. 조회 결과와 조회 시점을 보고서에 기록한다. 인증 또는 실행 환경 승인은 repository 변경 승인과 구분한다.

Remote 변경은 감사 범위에 포함하지 않는다. 게시 단계는 정확한 대상과 작업을 확정한 뒤 `GitHub Workflow Policy`를 따른다.

## 감사 Snapshot

승인된 감사 결과는 `Docs/04_WorkLogs/reviews`에 시점 snapshot으로 기록할 수 있다.

- 감사 범위와 최종 판정
- tracked 경로와 짧은 증거
- 사용자 결정과 항목 상태
- 수정 작업 묶음과 후속 validator 제안

명령 전체 출력, raw/reference 원문, source comment inventory, 민감 경로는 넣지 않는다. Snapshot은 최신 상태 정본을 대체하지 않는다.

## 완료 조건

- 요청 범위와 문서 inventory를 확인한다.
- 적용되는 `AGENTS.md`를 메인 에이전트가 직접 확인한다.
- 초기와 최종 validator 결과를 기록한다.
- 책임, 상태, 링크, stale path, 정책과 도구 품질을 범위에 맞게 조사한다.
- 하위 에이전트 결과를 메인 에이전트가 재검증한다.
- Legacy 역사 기록과 현재 문제를 구분한다.
- 중복 발견을 root cause 단위로 통합한다.
- 모든 최종 발견이 필수 증거를 가진다.
- 사용자 결정과 자동 수정 가능 범위를 분리한다.
- 변경 여부와 commit readiness를 보고한다.
- 사용자 승인 전에는 수정 단계로 넘어가지 않는다.
