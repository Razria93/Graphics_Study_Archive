# Example Window Recording

Windows graphics example의 application 전체 창을 MP4 후보로 녹화하는 반복 실행 도구를 정의한다. 이 도구는 raw video를 `local/`에만 만들며 tracked asset 승격, Publication 판정과 Git 작업은 수행하지 않는다.

## 준비

`scripts/record-example-window.ps1`은 실행 파일을 직접 시작하고 exact window title과 DWM extended frame bounds를 확인한 뒤 FFmpeg `gdigrab`으로 해당 영역을 녹화한다. 별도 topmost 상태 창은 대상 영역 밖에서 `READY`, `STARTING`, `RECORDING`, `FINALIZING`, `SAVED`, `DISCARDED`, `RESTARTED`와 단축키를 표시한다. 녹화 중 창을 이동하거나 크기를 바꾸면 현재 attempt를 중단한다. 다른 창이 대상 위를 가리면 함께 녹화될 수 있으므로 대상 창을 계속 보이게 둔다.

FFmpeg 탐색 순서는 다음과 같다.

1. `FfmpegPath`로 지정한 실행 파일
2. `PATH`에서 찾은 `ffmpeg`
3. `local/tools/ffmpeg/bin/ffmpeg.exe`

도구는 `ffprobe.exe`, `gdigrab`과 `libx264` 지원 여부를 함께 확인한다. FFmpeg를 자동 설치하거나 `PATH`, registry와 system 설정을 변경하지 않는다.

## 실행

output directory는 저장소의 `local/` 아래에 미리 만든다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/record-example-window.ps1 `
  -ExecutablePath Part2_Chapter04/04_Rasterization_Step1_Triangle/x64/Debug/04_Rasterization_Step1_Triangle.exe `
  -WorkingDirectory Part2_Chapter04/04_Rasterization_Step1_Triangle `
  -ExpectedTitle "ComputerGraphics - Step1 Triangle" `
  -OutputDirectory local/chapter04/step1/video `
  -BaseName step1-triangle
```

주요 parameter는 다음과 같다.

| Parameter | 책임 |
| --- | --- |
| `ExecutablePath` | 도구가 직접 시작할 example executable |
| `WorkingDirectory` | shader와 runtime asset 탐색 기준 |
| `ExpectedTitle` | 다른 창과 혼동하지 않을 exact application title |
| `OutputDirectory` | `local/` 아래 raw video 저장 위치 |
| `BaseName` | attempt와 selected 파일의 공통 이름 |
| `FfmpegPath` | 선택적 portable FFmpeg 실행 파일 |
| `FrameRate` | 녹화 FPS, 기본값 `30` |
| `StartTimeoutSeconds` | application window 탐색 제한 시간 |
| `KeepApplicationOpen` | 최종 선택 뒤 application 유지 |
| `OverwriteSelection` | 기존 selected 파일 교체 허용 |
| `CenterWindow` | 시작·재시작 시 monitor working area 중앙으로 창 이동 |
| `CountdownSeconds` | F9 뒤 녹화 시작까지 countdown, 기본값 `0`, 범위 `0`~`10` |

## Global hotkey

| 단축키 | 동작 |
| --- | --- |
| `Ctrl+Shift+F9` | `STARTING` countdown과 상태 재검증 후 현재 window bounds로 녹화 시작 |
| `Ctrl+Shift+F10` | FFmpeg를 정상 종료하고 attempt 저장 |
| `Ctrl+Shift+F8` | 현재 녹화를 폐기하고 partial 제거 |
| `Ctrl+Shift+F7` | 현재 녹화를 폐기하고 도구가 시작한 application만 재시작 |
| `Ctrl+Shift+F11` | F10으로 저장한 최근 정상 attempt를 selected 파일로 복사하고 종료 |

F8은 recording 중에 사용하는 재촬영 준비 동작이다. 저장된 attempt를 삭제하지 않는다. F7도 exact PID만 종료하며 같은 title의 다른 process를 종료하지 않는다. F11은 F9로 시작하고 F10으로 정상 저장한 attempt가 있어야 동작한다. 단축키 등록에 실패하면 충돌한 조합을 보고하고 등록한 단축키를 해제한다.

F9는 일반 크기와 최대화 상태를 유지한다. 대상 창이 최소화된 경우에만 이전 상태로 복원한다. 상태 창을 녹화 영역 밖에 배치할 공간이 없으면 녹화를 시작하지 않는다. `CenterWindow`를 사용하면 application 크기를 유지한 채 monitor working area 중앙으로 이동한다. countdown 동안 사용자는 마우스와 키보드를 조작하지 않는다. countdown 뒤 exact PID·title·foreground·bounds를 다시 확인하고 하나라도 달라지면 녹화를 시작하지 않는다.

## 파일과 검증

녹화 중에는 숨김 partial 파일을 사용한다. 정상 stop 뒤 `attempt-01`, `attempt-02` 순으로 번호를 증가시키며 F11은 최근 attempt를 `_selected.mp4`로 확정한다.

정상 attempt는 다음 조건을 자동 확인한다.

- MP4 container와 H.264
- `yuv420p`
- CFR 지정 FPS
- 양수 duration
- video stream 1개와 audio stream 0개
- DWM bounds에 대응하는 dimensions
- 민감한 title, author, comment, location, date와 software metadata tag 부재
- 전체 frame decode 성공

MP4 brand, `handler_name`과 encoder library처럼 개인 정보가 아닌 기술 container metadata는 허용한다. F11은 최근 정상 attempt를 selected 파일로 복사한 뒤 attempt와 selected의 SHA-256 일치를 확인한다.

강제 종료된 FFmpeg 결과와 검증에 실패한 partial은 정상 attempt로 승격하지 않는다. 도구 종료 뒤 FFmpeg process와 global hotkey가 남지 않아야 한다.

## 사용자 확인

자동 검증은 실제 화면 의미와 공개 안전성을 대신하지 않는다. selected video를 직접 재생해 다음을 확인한다.

- title bar와 border 포함
- frame 잘림, black frame과 손상 부재
- 다른 window, notification, 계정과 개인 정보 미노출
- 조작 흐름과 시각 결과의 설명 가능성

검토가 끝난 selected video도 기본적으로 `local/`에 유지한다. 독립적으로 다시 검사할 때는 `scripts/inspect-example-video.ps1`을 사용한다. 게시와 reference 연결은 [Demo Capture Policy](../06_Policies/demo-capture-policy.md), [Assets Policy](../06_Policies/assets-policy.md)와 [Video Plan](../03_Demos/video-plan.md)을 따른다.

촬영할 UI action, dwell time, retry와 reset은 [Capture Operation Guide](capture-operation-guide.md)와 local-only [Capture Operation Plan Template](templates/local-capture-operation-plan.md)에 먼저 기록한다.

## Selected video 재검사

기존 selected MP4는 application을 다시 실행하지 않고 read-only로 검사할 수 있다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/inspect-example-video.ps1 `
  -Path local/chapter04/step1a/video/step1a-triangle-to-circle_selected.mp4 `
  -ExpectedFrameRate 30
```

검사 결과는 container, codec, pixel format, dimensions, CFR, duration, stream 수, 민감 metadata, 전체 decode, size와 SHA-256을 출력한다. 이 결과는 화면 의미와 공개 안전성에 대한 사용자 시각 검수를 대신하지 않는다.

## 제한

- Windows interactive desktop과 DWM 환경만 지원한다.
- exact native window capture가 아니라 desktop 영역 crop을 사용한다.
- 녹화 중 대상 창 이동과 resize는 허용하지 않는다.
- application 내부 parameter를 자동 조작하지 않는다.
- stage, commit, push와 GitHub 게시를 수행하지 않는다.
