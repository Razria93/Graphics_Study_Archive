# Part1-Part4 Closeout 작업 계획

## 목적

이 문서는 Part1부터 Part4까지 완료된 작업의 상태 정합성을 먼저 복구하고,
`Portfolio_RayTracer` 작업으로 빠르게 전환하기 위한 closeout 범위를 정의한다.
문서 정리와 링크 수정처럼 실행 부담이 작은 작업을 우선 수행하고, 전체 코드
주석 정리, Part4 Release 재검증, runtime DLL 자동화와 video 게시 작업은 후속
작업으로 분리한다.

## 브랜치와 제외 범위

- 작업 브랜치: `docs/part1-part4-closeout`
- 기준 브랜치: `main`
- `Portfolio_RayTracer` 구현과 검증은 이 브랜치 범위에 포함하지 않는다.
- `WU-Publication`과 public repository 구성은 별도 Work Unit으로 유지한다.
- 외부 runtime asset 교체는 publication 또는 asset 정비 작업으로 분리한다.
- `WU-Part1`은 `Portfolio_RayTracer`가 남아 있으므로 `진행 중` 상태를 유지한다.

## 1차 작업: 빠른 closeout

### 상태 정합화

- PR #38 상태를 `Merged`로 갱신한다.
- Root README의 Part3 Chapter10-13과 Part4 Chapter14-20 진행 상태를 갱신한다.
- Root README의 compute shader와 simulation `정리 예정` 표현을 현재 상태로
  교체한다.
- `Docs/07_GitHub/plan/plan-progress.md`의 Phase 5-3과 PR #38 상태를 마감한다.
- `WU-Part4`, `work-unit-index`, `work-unit-github-index`의 상태를 교차 검증한다.
- current 문서에 남은 `Draft/Open`, `대기`, `정리 예정` 표현을 검색하고 실제
  상태와 다른 항목만 수정한다.
- Part2 Work Unit은 publication과 GitHub 게시 잔여 범위를 확인한 뒤 마감 여부를
  판정한다.
- Part4 검증과 Phase 6 video closeout은 완료로 올리지 않고 `후속 필요`로 남긴다.

### 완료된 Demo index 정리

다음 Demo index의 초기 placeholder 행을 실제 최소·대표 Demo, capture,
Verification과 GitHub Issue 연결로 교체한다.

- `Part1_Chapter03`
- `Part2_Chapter04`
- `Part2_Chapter05-08`
- `Part3_Chapter10-13`

상세 Demo와 capture가 이미 확보된 범위에 `미확인`, `후보`, `대표 예제 선정 후
갱신`이 남지 않도록 한다. video를 의도적으로 제외하거나 local-only로 유지한
경우에는 해당 판단과 이유를 보존한다.

### Workplan 후보 보완

- Phase 2-1부터 Phase 5-3까지 누락된 진행 기록을 확인한다.
- PR #38 merge 상태를 반영한다.
- Part1부터 Part4까지 완료 범위와 남은 제한을 구분한다.
- Phase 2-5 `Portfolio_RayTracer`를 다음 주요 작업으로 유지한다.
- Phase 6 Part4 selected video closeout을 후속 예정으로 유지한다.
- PR, Demo Issue와 완료 comment 링크를 검증한다.
- 원격 Workplan comment를 수정하기 전에 tracked 후보를 먼저 완성하고 validator를
  통과시킨다.

### Part1 Ray Tracing Demo 번호 정리

`Portfolio_RayTracer`와 직접 연결되는 Part1 Chapter03만 우선 정리한다.

- 기본 규칙은 `<Chapter>_<Step>_<Name>.md`로 둔다.
- 예: `03_04_DrawingSphere.md`, `03_14_CubeEnvironment.md`
- Demo index, Example README, Topic, Verification, Publication, WorkLog와 GitHub body
  후보의 링크를 함께 갱신한다.
- 이전 파일명 참조가 남아 있지 않은지 전수 검색한다.

Part2 Demo 번호 통일은 빠른 closeout의 필수 완료 조건에서 제외한다. Part1 번호
변경 결과와 link 영향 범위를 확인한 뒤 후속 일반 정비에서 적용한다.

## 1차 작업 완료 조건

- current 문서가 PR #38 merge 이후 상태와 일치한다.
- 완료된 Demo index에 초기 placeholder 상태가 남지 않는다.
- Workplan tracked 후보가 최신 상태와 다음 작업을 구분한다.
- Part1 Chapter03 Demo 번호와 링크가 일관된다.
- 전체 Markdown, Demo, Topic과 GitHub body validator가 통과한다.
- `git diff`에 의도하지 않은 코드 변경이 없다.
- `Portfolio_RayTracer` 작업을 시작할 수 있도록 남은 Part1 범위가 명확하다.

## 1차 작업 권장 커밋

```text
docs: Part1부터 Part4까지 진행 상태 정합화
docs: 완료된 Demo index 상태 갱신
docs: Workplan 진행 기록 보완
docs: Part1 Ray Tracing Demo 번호 체계 통일
```

실제 변경량이 작고 검토 경계가 유지되면 인접한 문서 커밋을 합칠 수 있다.

## 2차 작업: 일반 코드와 문서 정비

### Part2 Demo 번호 통일

- Part2 Chapter04와 Chapter05-08에 `<Chapter>_<Step>_<Name>.md` 규칙을 적용한다.
- `06_07_ResizingViewport`, `06_08_ResizingWindow`,
  `06_09_PhongVsBlinnPhong`처럼 Chapter와 Step을 구분한다.
- 모든 current 문서 링크를 갱신하고 stale path를 검사한다.

### Part1-Part4 코드 주석 정리

다음 항목은 삭제한다.

- 강의 내용을 받아 적은 학습 메모
- 코드가 그대로 표현하는 동작을 반복하는 주석
- 추측형, 대화형, 힌트와 추후 소개 표현
- 주석 처리된 폐기 코드
- 깨진 encoding 주석
- 현재 구현과 일치하지 않는 설명

다음 항목은 유지하거나 간결한 English로 바꾼다.

- API 제약
- resource lifetime과 ownership
- CPU 구조체와 shader layout 계약
- matrix convention
- numerical stability 조건
- 성능상 의도적인 선택
- runtime 또는 working directory workaround
- 외부 코드 attribution과 license
- 코드만으로 확인하기 어려운 invariant

주석 정리는 Part 단위로 수행하고 각 Part의 Debug/Release x64 build와 대표 smoke를
통과한 뒤 다음 Part로 이동한다. 코드 로직 변경은 주석 정리 커밋에 포함하지 않는다.

## 3차 작업: Part4 검증 마감

### Chapter14-Chapter15 Release x64 재검증

- Release x64 clean/rebuild를 수행한다.
- `Ex1401`부터 `Ex1408`, `Ex1501`부터 `Ex1503`까지 실행한다.
- sample별 정상 실행과 핵심 결과를 확인한다.
- Debug와 Release 결과 차이를 확인한다.
- 현재 확인 날짜, 환경과 provenance를 Verification에 기록한다.

### `Examples.sln` 실행 절차 정본화

- sample 선택 방식과 command argument를 기록한다.
- 요구되는 working directory를 기록한다.
- Debug/Release executable과 runtime asset 탐색 기준을 기록한다.
- 대표 smoke 순서와 실패 진단 절차를 기록한다.
- Part4 README와 Verification을 상세 정본으로 사용하고 Root BUILD 문서는 진입
  링크와 공통 기준만 유지한다.

### runtime DLL 배치 방식 검토

다음 대안을 비교한다.

1. 현재 수동 DLL 복구 절차 유지
2. MSBuild post-build copy 적용
3. vcpkg integration 활용
4. executable 또는 runtime search path 정리

Debug/Release DLL 혼용 방지, 새 checkout 재현성, sample별 중복 설정, ignored output
배치와 Visual Studio build 흐름을 기준으로 판정한다. 자동화의 영향 범위가
불명확하면 수동 절차를 정본화하고 구현은 별도 build 작업으로 남긴다.

## 4차 작업: Phase 6 video closeout

### 로컬 검수

- selected video와 Example, Demo Issue 대응을 확인한다.
- container, codec, resolution, frame rate, CFR/VFR, decode, audio, stream, duration과
  metadata를 검사한다.
- 개인정보, 계정, 로컬 경로, 강의 화면, 워터마크, 불필요한 UI와 외부 asset
  노출 위험을 육안 검수한다.
- 각 video를 `게시`, `local-only`, `재촬영 필요`, `제외` 중 하나로 판정한다.

### 원격 게시 gate

- Demo Issue 댓글 본문과 Workplan 수정 후보를 먼저 완성한다.
- 게시할 video, 대상 Issue, 댓글 본문과 게시하지 않을 이유를 사용자에게 보고한다.
- 사용자 승인 후에만 Workplan comment 수정과 Demo Issue video 댓글 게시를
  수행한다.
- 게시 후 attachment URL, comment permalink와 실제 재생 상태를 확인한다.

### 게시 결과 동기화

- Demo index와 상세 Demo를 갱신한다.
- `video-plan`, capture matrix, WorkLog와 `plan-progress`를 갱신한다.
- GitHub body/index와 Publication 상태를 갱신한다.
- 전체 validator와 stale status 검색을 다시 실행한다.

## 후속 작업 권장 커밋

```text
docs: Part2 Demo 번호 체계 통일
chore: Part1과 Part2 학습용 코드 주석 정리
chore: Part3과 Part4 학습용 코드 주석 정리
build: Part4 Release 검증과 실행 절차 정리
build: Part4 runtime DLL 배치 자동화
demo: Part4 selected video 검수 결과 정리
docs: Part4 video 게시 상태와 permalink 동기화
```

runtime DLL 자동화를 구현하지 않으면 관련 commit은 만들지 않는다.

## 전체 closeout 완료 조건

- Part1부터 Part4까지 current 문서가 실제 GitHub와 검증 상태에 일치한다.
- Workplan 누락 내용과 PR #38 merge 상태가 반영된다.
- Part1과 Part2 Demo 번호 체계가 일관된다.
- 학습용 코드 주석을 제거하고 기술적으로 필요한 제약과 계약을 보존한다.
- Part4 Chapter14-Chapter15 Release x64 재검증을 완료한다.
- `Examples.sln` 실행 절차와 runtime DLL 운용 판단을 기록한다.
- selected video를 검수하고 승인된 원격 게시와 permalink 동기화를 완료한다.
- 전체 validator와 필요한 build/run 검증을 통과한다.

