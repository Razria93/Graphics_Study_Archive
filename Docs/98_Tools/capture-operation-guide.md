# Capture Operation Guide

이 문서는 graphics example의 screenshot·video 개별 take를 계획하고 실행·재촬영·검수하는 순서를 정의한다. 승격 조건은 [Demo Capture Policy](../06_Policies/demo-capture-policy.md), asset 저장·공개 기준은 [Assets Policy](../06_Policies/assets-policy.md)를 따른다.

## 책임 분리

| 책임 | Tracked 범용 도구 | Example별 local driver |
| --- | --- | --- |
| application 실행, PID·exact title | 담당 | 검사 결과 사용 |
| foreground, DWM·native·client bounds, 중앙 배치 | 담당 | 조작 전 재확인 |
| screenshot, recording, 기술 검증, cleanup | 담당 | 범용 도구 호출 |
| slider, checkbox, parameter | 비담당 | 담당 |
| 상대 좌표, 조작 sequence, delay, cursor 대피 | 비담당 | 담당 |
| 초기·종료 상태, reset | 재시작 지원 | 계획·확인 |

Example별 좌표와 parameter는 [Local Capture Operation Plan](templates/local-capture-operation-plan.md)을 `local/`에 복사해 기록한다.

## Step visual 계획과 승인

Step별 작업은 작업자가 실제 code, UI, 기존 문서와 capture를 조사해 촬영 기준 초안을 먼저 작성한다. 사용자는 빈 양식을 다시 작성하지 않고 의도와 다른 항목만 수정한다.

```text
촬영 기준 초안
→ 사용자 수정
→ 구현·촬영 가능성 재검토
→ 사용자 기준 승인
→ 기존 visual 유지 또는 촬영
```

초안에는 재촬영 여부, screenshot 수, video 필요성, 학습 목표, 각 매체에 표현할 내용, 시작 상태와 parameter, 승인 기준과 촬영자를 포함한다. 수정하지 않은 항목은 초안에 동의한 것으로 처리하고 구현과 충돌하거나 설명이 부족한 항목만 다시 확인한다.

사용자 승인 뒤에는 screenshot 수, parameter, camera·model 상태, 조작 sequence와 승인 기준을 임의로 바꾸지 않는다. 기준 변경이 필요하면 local operation plan의 revision을 올리고 다시 승인받는다.

## 기존 visual 유지

다음 조건을 만족하면 새 촬영 없이 기존 visual을 유지할 수 있다.

- Step의 핵심 결과가 기존 visual에서 분명하다.
- 사용자 조작이나 시간 변화가 핵심이 아니다.
- 비교할 mode 또는 parameter가 없다.
- image 품질, 구도, UI와 title에 문제가 없다.
- 추가 매체가 새로운 구현 정보를 제공하지 않는다.

기존 visual 유지도 사용자 검수를 거쳐 `retained`로 마감한다. 정본 변경이 없으면 파일 수정과 commit을 만들지 않는다.

## 촬영자 시프트

촬영은 자동 조작을 기본값으로 둔다. 정확한 parameter 입력, 좌표 click·drag, 일정 시간 key press와 동일 bounds 반복 촬영은 자동 조작 대상으로 유지한다.

사용자가 촬영 의도를 설명하고 반복 조율하는 비용보다 직접 촬영하는 비용이 낮다고 판단하면 사용자 촬영으로 전환할 수 있다. 사용자 촬영 중에는 자동 조작을 수행하지 않는다. 사용자가 촬영 완료를 알리면 작업자는 기술 검수부터 이어간다. 촬영자가 바뀌어도 검수와 승격 기준은 바뀌지 않는다.

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

## Capture/run session preflight

자동 capture/run은 하나의 session이 하나의 example 실행만 소유하는 single-flight 방식으로 수행한다. 새 session을 시작하기 전에 stale 상태를 먼저 확인한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/find-capture-run-state.ps1 `
  -TargetProcessName <example-process-name> `
  -ExpectedTitle "<exact-title>" `
  -FailOnFound
```

확인 대상은 session lock, 관련 example process, known error dialog와 target title이다. 하나라도 남아 있으면 새 example을 실행하지 않는다.

중단 또는 실패 후에는 cleanup 명령으로 session 상태를 정리하고 quiet period 동안 0건을 유지하는지 확인한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/clear-capture-run-state.ps1 `
  -TargetProcessName <example-process-name> `
  -ExpectedTitle "<exact-title>" `
  -CloseErrorDialogs `
  -QuietSeconds 3
```

`clear-capture-run-state.ps1`는 기본적으로 non-destructive scan만 수행한다. 실제 종료는 `-CloseErrorDialogs`, `-KillExampleProcess`, `-RemoveSessionLock`처럼 명시한 option이 있을 때만 수행한다. `powershell`, `pwsh`, VSCode, ChatGPT, Codex, explorer 같은 broad process는 종료 대상으로 사용하지 않는다.

`wait-capture-run-quiet.ps1`는 error dialog가 늦게 뜨는 상황을 고려해 quiet period 동안 상태가 계속 0건인지 확인한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/wait-capture-run-quiet.ps1 `
  -TargetProcessName <example-process-name> `
  -ExpectedTitle "<exact-title>" `
  -QuietSeconds 3 `
  -TimeoutSeconds 30
```

Codex 목표 모드 중단은 이미 시작된 외부 runner, example EXE, system dialog를 자동 회수한다고 가정하지 않는다. 자동 capture/run 작업은 session cleanup 명령으로 별도 종료 증거를 확보한 뒤 중단 완료로 본다.

## 자동 입력 primitive 실행 순서

Example별 local driver는 GUI 조작을 한 번에 밀어 넣지 않고 primitive 단위로 실행한다. 기본 대기 시간은 1초로 시작하고 안정성이 확인된 경우에만 줄인다.

| Primitive | 실행 순서 | 사후 확인 |
| --- | --- | --- |
| focus | foreground 전환, target window click, 1초 대기 | actual foreground, title, bounds |
| keyboard toggle | key down/up, 1초 대기 | UI 상태, frame hash 또는 camera 변화 |
| axis key hold | key down, 지정 duration 유지, key up, 1초 대기 | 이동 전후 visual 변화 |
| mouse move | 시작 cursor origin 고정, 1초 대기, drag 없는 move | camera 방향과 cursor 위치 |
| mouse click | control 상태 확인, click, 1초 대기 | toggle 또는 값 변화 |
| slider drag | press, hold, duration 이동, release, 1초 대기 | 목표값과 rendering 변화 |
| numeric input | strict sequence로 field focus, numeric edit activation, select/clear, 값 입력, Enter, 단계별 대기 | UI 표시값과 결과 |

FPV나 mouse-look처럼 현재 cursor 위치가 camera 회전 기준이 되는 기능은 toggle 전에 cursor를 client center 같은 명시한 origin으로 이동한다. cursor origin을 고정하지 않은 상태에서 FPV를 켜면 첫 frame에서 시야가 크게 돌아갈 수 있다.

ImGui panel이 이전 실행의 open/closed 상태를 보존하면 panel arrow 좌표 클릭은 실패하기 쉽다. panel arrow click은 열기와 닫기가 같은 좌표이므로 가능하면 피하고, 동일 기능을 keyboard toggle, checkbox 상태 확인 또는 numeric input으로 만든다.

Tracked helper `scripts/window-input-primitives.ps1`는 focus, key tap, key hold, mouse move, click과 drag primitive를 제공한다. 이 helper는 실제 DirectX app을 실행하지 않으며 example별 local driver가 필요한 sequence와 좌표를 결정한다.

정확값을 재현해야 하는 `numeric input`은 일반 click 조합으로 축약하지 않고 다음 strict sequence를 사용한다.

1. focus 확보
2. 1초 대기
3. 변경할 값이 있는 slider의 value field로 pointer 이동
4. 1초 대기
5. `Ctrl + Left Click`
6. 0.5초 대기
7. `Ctrl + A`
8. 0.5초 대기
9. `Backspace`
10. 0.5초 대기
11. 원하는 값 입력
12. 0.5초 대기
13. `Enter`
14. 0.5초 대기

위 대기 시간은 빠른 입력으로 command가 씹히는 상황을 줄이기 위한 안정화 기준으로 사용한다. exact value가 필요한 screenshot과 verification capture에서는 slider drag보다 numeric input을 우선한다.

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

### Video capture mode

- 기본값은 title bar와 border를 포함하는 `FullWindow`다.
- `FullWindow` desktop crop에서 white frame, compositor artifact 또는 반복적인 UI 손상이 재현되고 같은 실행의 screenshot과 수동 run은 정상일 때만 `ClientOnly` fallback을 사용한다.
- `ClientOnly`는 exact title로 client area를 녹화하며 같은 Demo의 `FullWindow` screenshot이 application identity와 필요한 UI 상태를 보완한다.
- ImGui 조작이 핵심이면 UI를 숨기지 않고 함께 녹화한다. FPV와 펼친 UI 조합에서만 손상이 재현되면 `FullWindow` UI screenshot과 panel을 접은 동적 video로 증거를 분리한다.
- 선택한 mode, fallback 사유와 보완 screenshot을 local operation plan에 기록한다.

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
- 시작 frame, 첫 상태 종료 frame, 전환 중간 frame, 마지막 상태 frame과 종료 frame을 추출해 white·black·stale frame, UI 가림, 잘못된 foreground, 움직임 부재와 종료 상태 불일치를 확인한다.

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
3. selected video에서 본문용 storyboard를 만들고 제목, 읽는 방향, 입력 변화와 관찰 결과를 작성한다.
4. Demo Issue 본문은 정적 visual로 먼저 게시하고 selected video는 독립 설명 축별 전용 댓글에 한 번만 첨부한다.
5. 댓글 게시 후 comment permalink와 attachment URL을 각각 확인하고 video registry에 기록한다.
6. PR에서 video가 필요하면 Demo Issue의 comment permalink를 연결하고 attachment를 다시 업로드하지 않는다.
7. 같은 설명 축의 개선은 기존 댓글 수정, 다른 설명 축은 새 댓글 추가로 처리한다.
8. 승격과 게시는 자동 기술 검수와 사용자 시각 검수를 모두 통과한 후보만 사용한다.
## Runtime error dialog preflight

외부 DLL 또는 `assimp`를 사용하는 example은 capture/run 전후에 error dialog 상태를 확인한다. process 종료만으로 Windows loader error dialog가 사라졌다고 가정하지 않는다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/find-example-error-windows.ps1 `
  -TargetProcessName <example-process-name> `
  -ExpectedTitle "<exact-title>" `
  -FailOnFound
```

실행 실패 후 안전 후보가 확인되면 내부 `WM_CLOSE`, UI Automation close, button `BM_CLICK` 순서로 닫는다. mouse 좌표 클릭은 사용하지 않는다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/clear-example-error-windows.ps1 `
  -TargetProcessName <example-process-name> `
  -ExpectedTitle "<exact-title>" `
  -Close
```

dialog 후보가 target example과 관련 있는지 확신할 수 없으면 닫지 않는다. 무인 모드에서는 사용자 알림으로 중단하고 재실행 루프를 돌지 않는다.

`clear-example-error-windows.ps1 -Close`는 후보를 한 번만 닫고 끝내지 않고 drain pass를 반복한다. 각 후보는 title, class, process id/name/start time, child message text, button text로 만든 fingerprint를 기록한다. 닫기 직후 다시 scan해 같은 fingerprint가 남으면 `StillPresent`, 다른 fingerprint가 나타나면 `Replaced`, 후보가 0건이면 `Quiet`으로 보고한다. Windows loader dialog는 DirectXTK 누락 dialog를 닫은 뒤 assimp 누락 dialog가 새로 나타나는 방식으로 순차 발생할 수 있으므로 `Replaced`는 실패가 아니라 다음 drain 대상으로 처리한다. 후보가 0건이 된 뒤에도 quiet period를 기다리고 다시 scan한다. quiet period 이후에도 후보가 남으면 실패로 보고하고 같은 executable을 재실행하지 않는다.

## Troubleshooting: FPV 입력이 적용되지 않는 경우

Chapter10 Step2 Billboards 촬영에서는 다음 원인으로 FPV와 이동 입력이 적용되지 않은 take가 발생했다.

- cursor가 window 밖에 있는 상태에서 focus 확보 없이 keyboard input을 보냈다.
- focus 확보와 `F` toggle 사이의 안정화 시간이 부족했다.
- ImGui panel state가 이전 실행에서 보존되어 panel arrow 좌표 클릭이 열기 대신 닫기를 수행했다.
- panel state가 달라진 뒤 checkbox 좌표를 클릭해 실제 control이 아니라 빈 영역을 클릭했다.
- FPV toggle 확인 전에 axis key input을 연속으로 보내 시각 결과가 바뀌지 않았다.

해당 유형의 예제는 다음 probe sequence로 먼저 입력 경로를 확인한다.

```text
focus 확보
→ 1초 대기
→ F key tap
→ 1초 대기
→ A key press 2초
→ release
→ 1초 대기
→ D key press 4초
→ release
→ 1초 대기
→ screenshot/hash/visual 변화 확인
```

이 probe가 실패하면 본 촬영으로 넘어가지 않는다. take를 폐기하고 error dialog sweep, application restart, focus primitive 재검증과 입력 간격 확대를 순서대로 수행한다.
