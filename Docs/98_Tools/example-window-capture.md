# Example Window Capture

Windows에서 graphics example의 보이는 application window 전체를 PNG 후보로 저장하는 도구 사용법을 정의한다. 이 도구는 capture 생성만 담당하며 tracked asset 승격, Publication 판정, Git 작업은 수행하지 않는다.

## 도구

`scripts/capture-example-window.ps1`은 실행 파일을 시작하고 exact window title을 확인한 뒤 DWM extended frame bounds 기준으로 화면을 캡처한다. `CopyFromScreen`을 사용하므로 대상 창 위에 다른 창이 겹치지 않게 유지해야 한다.

필수 parameter는 다음과 같다.

| Parameter | 의미 |
| --- | --- |
| `ExecutablePath` | 실행할 example executable |
| `WorkingDirectory` | shader와 asset을 찾는 runtime working directory |
| `ExpectedTitle` | 오촬영을 막기 위한 exact application title |
| `OutputPath` | 기존 directory 안에 저장할 `.png` 후보 경로 |

선택 parameter는 다음과 같다.

| Parameter | 기본값과 의미 |
| --- | --- |
| `CaptureDelayMilliseconds` | foreground 전환 후 대기 시간, 기본값 `750` |
| `Overwrite` | 기존 output 교체 허용 |
| `KeepApplicationOpen` | 성공 후 application 유지 |
| `CaptureImmediately` | parameter 조작을 위한 Enter 대기 생략 |
| `CenterWindow` | monitor working area 중앙으로 창을 이동하고 크기는 유지 |
| `CountdownSeconds` | 입력 중단 안내 뒤 capture까지 countdown, 기본값 `0`, 범위 `0`~`10` |

## Interactive capture

파라미터나 camera를 직접 조작해야 하면 prompt가 나타난 뒤 application에서 원하는 상태를 만든다. 창을 가리지 않는 terminal에서 Enter를 누르면 대상 창을 foreground로 전환한 뒤 캡처한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/capture-example-window.ps1 `
  -ExecutablePath Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/x64/Debug/03_Raytracing_Step4_DrawingSphere.exe `
  -WorkingDirectory Part1_Chapter03/03_Raytracing_Step4_DrawingSphere `
  -ExpectedTitle "ComputerGraphics - Step4 DrawingSphere" `
  -OutputPath local/chapter03/step4/step4-window.png
```

## Immediate capture

기본 상태를 바로 기록하면 `CaptureImmediately`를 사용한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/capture-example-window.ps1 `
  -ExecutablePath Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/x64/Debug/03_Raytracing_Step4_DrawingSphere.exe `
  -WorkingDirectory Part1_Chapter03/03_Raytracing_Step4_DrawingSphere `
  -ExpectedTitle "ComputerGraphics - Step4 DrawingSphere" `
  -OutputPath local/chapter03/step4/step4-base-window.png `
  -CenterWindow `
  -CountdownSeconds 5 `
  -CaptureImmediately `
  -Overwrite
```

`CenterWindow`는 application의 현재 크기를 바꾸지 않고 해당 monitor의 taskbar를 제외한 working area 중앙에 배치한다. 창이 working area보다 크거나 중앙 배치 후 bounds가 벗어나면 capture하지 않는다. countdown을 사용하는 동안 사용자는 마우스와 키보드를 조작하지 않는다. 도구는 global input을 잠그거나 system 설정을 변경하지 않는다.

성공 결과는 absolute output path, 실제 image dimensions와 SHA-256을 출력한다. OS theme, DPI와 window border에 따라 전체 image dimensions는 달라질 수 있다.

## 실패 처리

- executable, working directory 또는 output directory가 없으면 application을 시작하지 않고 실패한다.
- output이 이미 있으면 `Overwrite` 없이는 실패한다.
- application이 조기 종료되거나 main window를 찾지 못하면 실패한다.
- actual title이 `ExpectedTitle`과 정확히 일치하지 않으면 실패한다.
- foreground 전환, DWM bounds 조회 또는 PNG 저장이 실패하면 불완전한 임시 파일을 제거한다.
- 실패 시 도구가 시작한 application을 종료하며, 성공 시에도 `KeepApplicationOpen`이 없으면 종료한다.

## 검수와 승격

도구가 출력하는 dimensions와 hash는 검수 보조 증거이며 공개 안전성을 자동으로 보장하지 않는다. 창 겹침, title, overlay, watermark, 계정, 로컬 경로, taskbar와 notification 노출을 직접 확인하고 image metadata도 별도로 검사한다.

capture 후보는 먼저 `local/`에 저장한다.

parameter 변경 전후 상태, reset과 재촬영 순서는 [Capture Operation Guide](capture-operation-guide.md)와 local-only [Capture Operation Plan Template](templates/local-capture-operation-plan.md)에 기록한다.

검수 후 `Docs/_assets`로 승격하고 관련 Verification, Demo와 Publication 문서를 갱신하는 절차는 [Demo Capture Policy](../06_Policies/demo-capture-policy.md)와 [Publication Policy](../06_Policies/publication-policy.md)를 따른다.

## 제한

- Windows interactive desktop와 DWM 환경만 지원한다.
- `CopyFromScreen` 방식이므로 다른 창이 대상 위에 겹치면 함께 저장될 수 있다.
- application parameter 자동 조작, desktop fallback, taskbar crop 추정은 제공하지 않는다.
- capture 생성 후 stage, commit, push 또는 remote 게시를 수행하지 않는다.
