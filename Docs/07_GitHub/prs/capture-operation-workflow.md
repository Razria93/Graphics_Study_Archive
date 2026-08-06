# Capture 자동 제어와 조작 workflow 보완

## 요약

이 PR은 graphics example의 전체 창 screenshot과 video 녹화를 다음 Chapter에서도 같은 기준으로 반복할 수 있도록 capture 운영 절차를 정리한다. 자동 조작 전 입력 중단 안내, 선택적 창 중앙 배치, countdown과 촬영 직전 상태 재검증을 범용 도구에 추가하고, 예제별 UI 조작은 비추적 driver 책임으로 분리한다.

## 범위

- 대상: Demo capture 정책, 실행 가이드, 비추적 operation plan template, screenshot·video PowerShell 도구와 회귀 검사
- 보완 기능: `CenterWindow`, `CountdownSeconds`, PID·exact title·foreground·DWM bounds 재검증과 video `STARTING` 상태
- 제외 범위: Chapter04 예제 코드·문서·기존 capture 변경, application parameter의 범용 하드코딩, Windows input lock과 system setting 변경

## 핵심 개념

- 재현 가능한 capture lifecycle: 초기 상태, 목표 조작, rendering 안정화, 촬영, 검증과 reset을 하나의 순서로 정의해 비교 자료의 window·bounds·상태 조건을 유지한다.
- 안전한 자동 제어: countdown 뒤 대상 process, title, foreground와 bounds를 다시 확인하고 조건이 달라지면 screenshot 또는 video attempt를 생성하지 않는다.
- 책임 분리: 범용 도구는 application 실행·배치·capture·기술 검증·cleanup을 담당하고 slider, checkbox, 상대 좌표와 조작 sequence는 예제별 비추적 driver에 둔다.

## 대표 예제

### 전체 창 Screenshot

기존 명령은 그대로 유지하면서 선택적으로 application 크기를 보존한 중앙 배치와 countdown을 적용한다. 창이 monitor working area보다 크거나 촬영 준비 중 focus·title·bounds가 바뀌면 불완전한 결과를 남기지 않고 실패한다.

- 도구: [Example Window Capture](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/example-window-capture.md)
- 실행 기준: [Capture Operation Guide](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/capture-operation-guide.md)

### Video Recorder Lifecycle

`READY → STARTING → RECORDING → SAVED → SELECTED` 상태를 구분하고 F8 partial 폐기와 F7 exact PID 재시작을 포함한 재촬영 흐름을 유지한다. Status window가 capture bounds 밖에 없거나 녹화 준비 중 대상 상태가 달라지면 FFmpeg를 시작하지 않는다.

- 도구: [Example Window Recording](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/example-window-recording.md)
- 조작 계획: [Capture Operation Plan Template](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/templates/local-capture-operation-plan.md)
- 적용 사례: [Step7 BackfaceCulling 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter04/07_BackfaceCulling.md)

## 검증

- Screenshot smoke: Step2 Circle 전체 창 1282×992, 중앙 배치, 성능 overlay·잘림·민감 metadata 부재와 process cleanup 확인
- Video smoke: Step7 BackfaceCulling F8 폐기·F7 재시작·F10 저장·F11 선택 lifecycle, H.264, `yuv420p`, CFR 30 FPS, audio stream 0과 전체 frame decode 확인
- 하위 호환성: 신규 option을 사용하지 않으면 기존 위치와 countdown 0초 동작 유지
- Local validator: GitHub body, Demo, Topic, video asset, Markdown과 capture tool contract 검사 통과
- Remote validator: `Docs Validation` workflow에 capture tool contract test를 연결

## 스크린샷

- 없음

## 미확인 / 제한

- Windows interactive desktop, DWM과 FFmpeg `gdigrab` 환경을 대상으로 한다.
- 범용 도구는 application 내부 parameter, slider와 checkbox를 자동 조작하지 않는다.
- Windows 전체 input을 잠그지 않으므로 안내된 countdown과 촬영 중에는 사용자가 mouse와 keyboard 조작을 멈춰야 한다.
- 자동 기술 검증은 화면 의미와 공개 안전성에 대한 사용자 시각 검수를 대체하지 않는다.

## 문서

- 정책: [Demo Capture Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/06_Policies/demo-capture-policy.md)
- 실행 안내: [Capture Operation Guide](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/capture-operation-guide.md)
- Screenshot 도구: [Example Window Capture](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/example-window-capture.md)
- Video 도구: [Example Window Recording](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/example-window-recording.md)
- 회귀 검사: [Validators](https://github.com/Razria93/Graphics_Study_Archive/blob/chore/capture-operation-workflow/Docs/98_Tools/validators/README.md)

## 관련 이슈

- 없음

## 다음 단계

- 다음 Chapter capture 작업에서 예제별 비추적 operation plan을 적용해 재현성을 확인한다.
