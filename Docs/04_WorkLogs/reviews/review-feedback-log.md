# Review Feedback Log

이 문서는 PR review에서 발견된 actionable feedback 중 이후 작업의 회귀 검사에 재사용할 항목만 기록한다. review 원문은 복제하지 않고 GitHub source와 대응 결과를 연결한다.

## 상태

- `open`: 대응 또는 검증이 남아 있다.
- `resolved`: 수정과 검증을 완료했다.
- `accepted`: 검토 결과 현재 상태를 유지한다.

## 기록

### RF-001 — 정책 이동 후 stale link

- Source: [PR #8 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/8#discussion_r3675769532)
- Category: `link`
- Affected: `Docs/99_Legacy/PartDocs/Part1_Chapter01-02`의 Chapter 및 Example README 3개
- Finding: 정책 디렉터리 이동 후 삭제된 이전 정책 경로를 가리키는 링크가 남아 404가 발생한다.
- Response: 세 링크를 현재 정본인 `Docs/06_Policies/docs-authoring-flow-policy.md`로 교체하고 동일한 이전 경로를 저장소 전체에서 검색한다.
- Verification: 상대 링크 대상 확인, 이전 경로 재검색, 필수 validator 5종
- Fix: `a35b1f2`
- Status: `resolved`
- Regression check: 파일 또는 정책 경로를 이동·삭제한 PR은 이전 경로 문자열과 해당 대상을 가리키는 inbound Markdown link를 검색한다.

### RF-002 — 최대화 screenshot capture의 창 상태 변경

- Source: [PR #16 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/16#discussion_r3696198364)
- Category: `capture`
- Affected: `Docs/98_Tools/scripts/capture-example-window.ps1`
- Finding: interactive capture가 최대화된 창의 bounds를 기록한 뒤 창을 복원해 최종 bounds 검사가 실패한다.
- Response: 최소화된 창만 복원하고 필요한 복원을 planned bounds 기록 전에 완료해 최대화 상태를 유지한다.
- Verification: 최대화 창 screenshot smoke, window capture contract test, 전체 문서 validator
- Fix: `4f89fe9`
- Status: `resolved`
- Regression check: capture 준비 중 창 상태를 변경하는 동작은 baseline bounds 기록 전에 완료하고 상태 변경 조건을 contract test로 고정한다.

### RF-003 — Capture 중 client 영역 밖 cursor 좌표 처리

- Source: [PR #23 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/23#discussion_r3704747976)
- Category: `runtime`
- Affected: Chapter09 Step2–6의 `AppBase.cpp`와 Step2 `ExampleApp.cpp`
- Finding: Step3–6은 mouse capture 중 client 영역 밖 음수 좌표를 unsigned 값으로 해석했다. Step2는 resize 뒤 남은 cursor 좌표로 변경된 index texture 범위 밖을 readback할 수 있었다.
- Response: Step2–6은 signed cursor 좌표를 사용한다. Step2는 실제 index texture bounds 밖 readback을 생략하고 resize 전 filter·render resource 참조를 해제한 뒤 재구성한다.
- Verification: Step2–6 Debug/Release x64 build, Step2 wide·medium·compact resize와 minimize/restore, Step3–6 client 경계 밖 drag·release runtime 검사, 관련 Demo code anchor 확인
- Fix: `7a782fd`, `3f6cfb3`
- Status: `resolved`
- Regression check: 모든 picking 예제는 signed cursor 좌표와 실제 readback texture bounds를 확인한다. Mouse capture 예제는 client 경계 밖 좌·상·우·하 이동과 외부 release를 추가로 검사한다.

### RF-004 — Demo Issue 본문의 standalone video 검증 누락

- Source: [PR #23 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/23#discussion_r3704747988)
- Category: `validator`
- Affected: GitHub quality validator, visual fixture와 Chapter04 Demo Issue 후보
- Finding: 정책은 video를 별도 Issue comment에 두도록 정의하지만 validator는 Demo Issue 본문의 bare video attachment를 허용한다.
- Response: standalone video attachment를 실패 처리하고 image-only 및 video comment link 허용 fixture를 실제 validator에 연결한다. Chapter04 Issue #14 본문은 정적 visual 3개로 교체하고 기존 video는 전용 댓글로 이전한다.
- Verification: validator 수정 전 invalid fixture 실패 재현, 수정 후 fixture와 GitHub quality validator 통과, [Issue #14 video 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/14#issuecomment-5168469025)의 1202×932 H.264 재생과 본문의 standalone video 0건 확인
- Fix: `c67c198`
- Status: `resolved`
- Regression check: Demo Issue 후보는 정적 visual만 본문에 두고 동적 evidence는 전용 comment permalink로 연결한다.

### RF-005 — 자동 numeric input의 signed value 입력 누락

- Source: [PR #24 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/24#discussion_r3718880498)
- Category: `capture`
- Affected: `Docs/98_Tools/scripts/window-input-primitives.ps1`, `Docs/98_Tools/validators/test-window-input-primitives.ps1`, `.github/workflows/docs-validation.yml`
- Finding: `Invoke-ExampleNumericInput`는 값을 문자 단위로 입력하지만 `Resolve-ExampleVirtualKey`가 `-`를 매핑하지 않아 `-2.0` 같은 signed numeric input에서 실패할 수 있었다.
- Response: `-`, `MINUS`, `OEM_MINUS`를 `VK_OEM_MINUS(0xBD)`로 매핑하고 decimal/minus 회귀 테스트를 추가했다. 해당 primitive contract test를 `Docs Validation` workflow에 연결했다.
- Verification: window input primitive contract test, 로컬 전체 Docs Validation 명령 묶음, 원격 PR/push `Docs Validation`
- Fix: `5fe65dc`
- Status: `resolved`
- Regression check: capture driver가 numeric field에 signed value를 입력하면 `Resolve-ExampleVirtualKey`의 punctuation mapping과 `test-window-input-primitives.ps1` 회귀 테스트를 함께 확인한다.
