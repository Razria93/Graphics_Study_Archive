# Capture Operation Guide

이 문서는 graphics example의 screenshot·video 개별 take를 계획하고 실행·재촬영·검수하는 순서를 정의한다. 승격 조건은 [Demo Capture Policy](../06_Policies/demo-capture-policy.md), asset 저장·공개 기준은 [Assets Policy](../06_Policies/assets-policy.md)를 따른다.

## 책임 분리

| 책임 | Tracked 범용 도구 | Example별 local driver |
| --- | --- | --- |
| application 실행, PID·exact title | 담당 | 검사 결과 사용 |
| foreground, DWM bounds, 중앙 배치 | 담당 | 조작 전 재확인 |
| screenshot, recording, 기술 검증, cleanup | 담당 | 범용 도구 호출 |
| slider, checkbox, parameter | 비담당 | 담당 |
| 상대 좌표, 조작 sequence, delay, cursor 대피 | 비담당 | 담당 |
| 초기·종료 상태, reset | 재시작 지원 | 계획·확인 |

Example별 좌표와 parameter는 [Local Capture Operation Plan](templates/local-capture-operation-plan.md)을 `local/`에 복사해 기록한다.

## 입력 안전 안내

```text
자동 조작이 시작되면 완료 또는 실패 안내가 나올 때까지
mouse와 keyboard를 조작하지 않는다.
```

1. 자동 조작 전에 안내와 countdown을 표시한다.
2. countdown 종료 후 PID, exact title, foreground와 bounds를 확인한다.
3. 다른 application을 조작하거나 Windows 전체 input을 잠그지 않는다.
4. 사용자 입력으로 대상이 바뀌었다고 의심되면 현재 take를 폐기한다.
5. Foreground 전환을 위해 input queue를 연결한 경우 대상 창을 올린 직후 해제하고 actual foreground를 다시 확인한다.

## 기본 상태 screenshot

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/capture-example-window.ps1 `
  -ExecutablePath <example.exe> `
  -WorkingDirectory <example-folder> `
  -ExpectedTitle "<exact-title>" `
  -OutputPath local/<work-unit>/<example>/base.png `
  -CenterWindow `
  -CountdownSeconds 5 `
  -CaptureImmediately
```

기본 상태는 application 실행 후 안정화를 대기하고 바로 촬영한다. 결과를 확인한 뒤 도구가 시작한 application을 종료한다.

## Parameter-adjusted screenshot

1. local operation plan에 초기값, 목표값, 상대 좌표, delay, cursor 대피와 reset을 기록한다.
2. application을 시작하고 기본 상태를 확인한다.
3. countdown 후 local driver로 목표값을 설정한다.
4. rendering 안정화 후 cursor를 대피하고 screenshot을 저장한다.
5. application을 재시작해 초기 상태를 복구하는 방식을 기본값으로 사용한다.

## Before/after screenshot

- 두 screenshot은 동일한 window size, position, camera, geometry와 capture 방식을 사용한다.
- before 촬영 후 application을 재시작하고 after parameter만 변경한다.
- 두 상태의 bounds와 실행 조건이 다르면 비교 자료로 승격하지 않는다.

## 자동 조작 video

1. 핵심 변화 하나를 선정한다.
2. 초기 안정 구간, 조작, 결과 안정 구간을 계획한다.
3. 동작별 delay는 넓게 시작하고 시각 검수를 거쳐 줄인다.
4. 조작 전에는 PID, title, foreground, bounds를 다시 확인한다.
5. 조작 종료 후 cursor를 대피하고 결과 구간을 유지한다.
6. F10으로 저장·검증한 뒤 시각 검수를 통과한 attempt만 F11로 selected한다.

## 사용자 수동 조작 video

- 사용자에게 조작 순서, 초기값, 목표값과 종료 조건을 촬영 전에 안내한다.
- F9 이후 시작 안정 구간을 유지한 뒤 조작한다.
- 실수한 take는 F8로 폐기하고 application 기본 상태가 필요하면 F7로 재시작한다.
- F11은 F10으로 저장·검증한 최근 정상 attempt가 있을 때만 사용한다.

## Failed take와 reset

- bounds, title, foreground, process, frame decode 또는 metadata 검증이 실패하면 현재 take를 폐기한다.
- screenshot은 불완전한 temporary output을 제거한다.
- video F8은 현재 partial만 제거하고 기존 정상 attempt를 보존한다.
- 초기 UI 상태는 가능하면 application restart로 복구한다.
- 재시작이 불가능하면 parameter를 복구하고 실제 rendering 결과를 확인한다.

## Selected video 재검사

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/inspect-example-video.ps1 `
  -Path local/<work-unit>/<example>/video/<name>_selected.mp4 `
  -ExpectedFrameRate 30
```

재검사는 container, codec, pixel format, dimensions, CFR, duration, stream, metadata, hash와 전체 decode를 확인하며 시각 의미를 판단하지 않는다.

## 사용자 시각 검수

- title bar, border, frame 잘림과 black frame을 확인한다.
- 다른 window, notification, account, local path와 개인 정보 노출을 확인한다.
- 조작과 결과가 설명할 graphics 개념과 대응하는지 확인한다.
- 불필요한 parameter 왕복, click, mouse movement와 대기를 확인한다.
- screenshot대비 video가 추가 설명 가치를 갖는지 확인한다.

## Selected video 기반 Storyboard

1. Selected video에서 입력 전, 입력 중과 결과 상태처럼 의미가 다른 frame을 2~5개 고른다.
2. Frame을 같은 application bounds, crop과 scale로 맞춘다.
3. 각 frame에 읽기 순서와 짧은 상태 label을 넣는다.
4. 2장은 2열, 3장은 3열, 4장은 2×2, 5장은 3+2 구성을 기본으로 사용한다.
5. GitHub 문서 폭에서 title, UI와 결과 차이가 읽히는지 확인한다.
6. 원본 video와 대조해 label, 입력 상태와 결과가 실제 sequence와 일치하는지 확인한다.
7. 기술 검수와 공개 안전성 검수를 통과한 최종 PNG만 tracked capture로 승격한다.

균등 간격 frame을 나열한 QA contact sheet는 누락 frame과 black frame을 찾는 local 검사 자료다. 공개 storyboard는 시간 간격이 아니라 설명할 상태를 기준으로 frame을 선별한다.

## 승격과 게시 전 확인

1. raw, attempt와 selected는 `local/`에 유지한다.
2. screenshot 승격 전 metadata, visual, 입력 asset과 Publication 조건을 확인한다.
3. selected video는 Demo Issue attachment에 한 번만 게시한다.
4. PR에서 video가 필요하면 Demo Issue의 동일 attachment URL을 재사용한다.
5. 승격과 게시는 자동 기술 검수와 사용자 시각 검수를 모두 통과한 후보만 사용한다.
