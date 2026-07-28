# Document System Audit Guide

이 문서는
[Document System Audit Policy](../06_Policies/document-system-audit-policy.md)를
실행하는 순서를 정의한다. 권한, 심각도, keyword 의미는 정책 정본을 따른다.

## 요청 해석

감사 keyword 또는 명시된 입력으로 범위를 정한다.

```text
문서 단일검수 시작: <경로>
문서 영향감사 시작
문서 전수감사 시작
감사 결과 반영 시작: <보고서 또는 DOC ID>
감사 결과 게시 시작: <대상과 작업>
```

`Single`, `Impact`, `Chapter`, `Full` 이외의 범위가 들어오면 가장 좁은 명확한
범위로 해석한다. 수정과 remote 변경은 감사 요청에서 추론하지 않는다.

## 시작 절차

1. `git status --short --branch`로 branch와 기존 변경을 확인한다.
2. root와 대상 범위의 `AGENTS.md`를 메인 에이전트가 직접 읽는다.
3. 관련 README, 정책, template, validator inventory를 만든다.
4. 감사 시작 시점의 필수 validator를 실행하고 결과를 기록한다.
5. 목표 모드를 지원하고 요청 범위에서 권장되면 목표와 완료 조건을 등록한다.

Full 감사의 현재 baseline은 다음 명령을 사용한다.

```powershell
git status --short --branch
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-index-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-doc-quality.ps1
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-topic-doc-quality.ps1
```

감사 대상에 별도 validator가 있으면 같은 baseline에 추가한다.

## 에이전트 분담

Full 감사의 기본 분담은 다음과 같다.

| 역할 | 조사 범위 |
| --- | --- |
| `architecture_audit` | Root, Docs, Chapter 진입 흐름과 책임 분리, 본문 중복 |
| `state_link_audit` | 상태 교차검증, 상대 링크, stale path, remote 상태 |
| `policy_quality_audit` | AGENTS, 정책, template, validator, 공개 문서 품질 |
| 메인 에이전트 | inventory, AGENTS, 실제 문맥 재검증, root cause 통합 |

Impact와 Chapter 감사는 관련 관점을 최대 2개로 합친다. Single 감사는 메인
에이전트가 직접 수행한다. 하위 에이전트를 지원하지 않으면 표의 세 관점을
순서대로 조사한다.

하위 에이전트 요청에는 read-only, 수정·stage·commit 금지를 명시한다.

## 수동 감사

### 진입점과 탐색 흐름

- Root README에서 Docs와 대표 Chapter로 이동할 수 있는지 확인한다.
- Docs README와 각 축 README가 책임 설명을 먼저 제공하는지 확인한다.
- Chapter README가 Example, Topic, Verification, Demo로 연결되는지 확인한다.
- 상위 문서가 하위 정본 본문을 복제하지 않는지 확인한다.

### 책임 분리

- `Canonical Docs Policy`와 각 축 `AGENTS.md`의 현재 책임을 기준으로 비교한다.
- Topic은 여러 예제에 적용되는 개념과 이론을 설명한다.
- Verification은 직접 확인한 build/run/capture 사실을 소유한다.
- Example README는 예제 목적, 핵심 코드 위치, 실행 진입점, 대표 visual 최대
  1개를 소유한다.
- Demo는 구현 선택, 다중 시각 자료, 결과 해석, limitation을 소유한다.
- WorkLog는 작업 당시 결정과 snapshot을 기록한다.
- Publication은 공개 후보와 제외 판단을 소유한다.
- GitHub body는 정본을 복제하지 않고 게시 목적에 맞게 요약한다.
책임 경계 자체가 충돌하면 한쪽 문장을 임의로 고치지 않고 정책 결정 항목으로
보고한다. 위 Example/Demo 경계는 확정된 기준이므로 중복 여부를 직접 검사한다.

### 상태 교차검증

Chapter README, Verification, Demo, Publication, WorkLog, GitHub body가 같은
대상의 상태를 어떻게 표현하는지 비교한다.

- 서로 다른 시점의 snapshot은 오류로 단정하지 않는다.
- 과거 성공 이력과 현재 재검증 여부를 구분한다.
- 직접 증거가 없으면 사용자 확인 사항으로 남긴다.
- remote 상태는 필요한 경우 read-only로 확인한다.

### 링크와 stale path

- Markdown 상대 링크를 파일 위치 기준으로 해석한다.
- 실제 대상 파일과 tracked asset 존재 여부를 확인한다.
- 폐기된 Docs 번호 구조, `_repo`, `local/` 직접 링크를 검색한다.
- Legacy 내부 역사 기록은 제외하고 current 문서의 잘못된 연결만 분류한다.
- template placeholder는 실제 산출물과 구분한다.

### 정책과 도구

- AGENTS와 Policies가 같은 안전 gate를 다르게 표현하는지 확인한다.
- 정책에 있는 규칙이 template과 validator에 필요한 범위만 반영되는지 확인한다.
- validator가 정책이나 template에 없는 규칙을 강제하는지 확인한다.
- validator가 검사하지 않는 의미적 품질을 수동 감사 목록에 남긴다.
- 미구현 tool을 현재 사용 가능한 명령처럼 설명하지 않는다.

### 공개 문서 품질

- 내부 workflow, draft 판단, 로컬 환경 경로를 노출하지 않는지 확인한다.
- source docs를 복제하지 않고 요약과 링크를 사용하는지 확인한다.
- 검증 상태와 limitation을 독자가 오해하지 않게 구분하는지 확인한다.
- 관련 문서가 실제로 이동 가능한 Markdown 또는 GitHub 링크인지 확인한다.

## 메인 재검증

메인 에이전트는 하위 에이전트의 각 후보에 대해 다음을 다시 확인한다.

1. 파일과 line이 실제로 존재하는지 확인한다.
2. 앞뒤 문맥이 보고된 해석을 지지하는지 확인한다.
3. 현재 정본, 과거 snapshot, Legacy를 구분한다.
4. 다른 발견과 같은 root cause인지 확인한다.
5. 자동 검사로 확정 가능한지 수동 판단이 필요한지 구분한다.
6. 오탐 가능성과 필요한 사용자 결정을 기록한다.

확인되지 않은 후보는 최종 발견 표에 포함하지 않는다.

## 보고서 작성

[Document System Audit Report](templates/document-system-audit-report.md)를 사용한다.
발견은 증상이 아니라 root cause 단위로 묶고 P0, P1, P2 순서로 제시한다.

수정 작업 묶음은 다음을 분리한다.

- 즉시 자동 수정 가능한 확정 문제
- 사용자 결정을 반영한 뒤 수정할 문제
- build/run/capture 또는 remote 확인이 필요한 문제
- validator 설계와 구현이 필요한 문제

## 종료 절차

1. 시작 시 실행한 validator를 같은 조건으로 다시 실행한다.
2. 초기와 최종 결과 차이를 기록한다.
3. worktree 변경 여부를 확인한다.
4. read-only 감사면 변경 없음과 commit 불필요 상태를 보고한다.
5. 수정 작업이면 관련 파일, 검증, commit 분할을 보고한다.
6. 목표 모드를 사용했다면 완료 조건을 확인한 뒤 목표를 종료한다.

## Planned Audit Runner

다음 interface는 향후 구현 후보이며 현재 실행 가능한 script가 아니다.

```powershell
powershell -ExecutionPolicy Bypass `
  -File Docs/98_Tools/audits/invoke-document-audit.ps1 `
  -Profile Full `
  -Phase Baseline
```

예상 parameter:

- `-Profile Single|Impact|Chapter|Full`
- `-Phase Baseline|Final|Both`
- 선택 `-TargetPath`
- 선택 `-OutputPath`

Runner는 console-only와 read-only를 기본으로 하며 tracked 파일 생성, 자동 수정,
목표 생성, 하위 에이전트 생성, remote 변경을 담당하지 않는다. 링크와 상태의 의미
판정은 메인 에이전트의 수동 감사에 남긴다.
