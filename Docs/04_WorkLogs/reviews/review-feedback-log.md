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
- Affected: Chapter09 Step3–6의 `AppBase.cpp`
- Finding: mouse capture 중 client 영역 밖으로 이동한 음수 좌표를 unsigned 값으로 해석해 index texture 범위를 벗어난다.
- Response: `GET_X_LPARAM`, `GET_Y_LPARAM`으로 signed 좌표를 해석하고 실제 index texture 크기로 readback 범위를 검사한다.
- Verification: Step3–6 Debug/Release x64 build, client 경계 밖 drag·release runtime 검사, 관련 Demo code anchor 확인
- Fix: `7a782fd`
- Status: `resolved`
- Regression check: mouse capture를 사용하는 picking 예제는 client 경계 밖의 좌·상·우·하 이동과 외부 release를 포함해 검사한다.

### RF-004 — Demo Issue 본문의 standalone video 검증 누락

- Source: [PR #23 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/23#discussion_r3704747988)
- Category: `validator`
- Affected: GitHub quality validator, visual fixture와 Chapter04 Demo Issue 후보
- Finding: 정책은 video를 별도 Issue comment에 두도록 정의하지만 validator는 Demo Issue 본문의 bare video attachment를 허용한다.
- Response: standalone video attachment를 실패 처리하고 image-only 및 video comment link 허용 fixture를 실제 validator에 연결한다. 기존 Chapter04 후보의 video는 정적 visual로 교체한다.
- Verification: validator 수정 전 invalid fixture 실패 재현, 수정 후 GitHub visual fixture 및 GitHub quality validator 통과
- Fix: `c67c198`
- Status: `resolved`
- Regression check: Demo Issue 후보는 정적 visual만 본문에 두고 동적 evidence는 전용 comment permalink로 연결한다.
