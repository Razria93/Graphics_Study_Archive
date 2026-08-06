# Assimp Runtime Dialog

이 문서는 `assimp` 또는 외부 DLL을 사용하는 graphics example 실행 중 Windows loader error dialog가 발생하는 경우의 확인 절차를 정의한다.

## 증상

- example process를 종료했는데도 error dialog가 화면 위에 남는다.
- 새 example window가 정상 실행되어도 이전 error dialog가 capture에 함께 찍힌다.
- capture tool은 `main window not found` 또는 조기 종료만 보고하고 실제 원인 dialog를 직접 설명하지 못한다.
- Debug 또는 Release output 폴더에 필요한 `assimp` DLL이 없거나 오래된 상태다.

## 원인

Windows loader error dialog는 target example process와 별개의 top-level window 상태로 남을 수 있다. 따라서 process 종료, 재실행, 반환값 확인만으로는 화면에 남은 modal dialog를 제거했다고 볼 수 없다.

## 원칙

- 반환값만으로 runtime error를 판정하지 않는다.
- assimp 또는 외부 DLL을 사용하는 example은 실행 전 output DLL을 확인한다.
- 실행 실패 후에는 target process뿐 아니라 top-level error dialog 잔존 여부를 확인한다.
- error dialog 후보가 남아 있으면 해당 capture 후보를 폐기한다.
- error dialog가 하나만 생긴다고 가정하지 않는다.
- DirectXTK, assimp 같은 loader dialog는 하나를 닫은 뒤 다음 dialog가 순차로 나타날 수 있으므로 남은 후보 수만으로 close 실패를 판정하지 않는다.
- 닫기 전후의 handle, title, class, process, start time, child message text, button text 기반 fingerprint를 비교해 같은 dialog 잔존과 새 dialog 교체를 구분한다.
- 후보를 닫은 뒤 2~3초 quiet period를 두고 다시 scan해 0건을 확인한다.
- 실패한 executable은 DLL, working directory, build configuration 또는 Clean/Rebuild 필요성을 확인하기 전까지 반복 실행하지 않는다.
- 무인 모드에서는 관련성이 불확실한 dialog를 닫지 않고 사용자 알림으로 중단한다.
- error dialog는 mouse click이 아니라 `WM_CLOSE`, UI Automation close, button `BM_CLICK` 기반 내부 명령으로만 닫는다.

## 확인 명령

실행 전후 의심 dialog를 찾는다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/find-example-error-windows.ps1 `
  -TargetProcessName 10_GeometryPipeline_Step3_NormalLines `
  -ExpectedTitle "ComputerGraphics - Chapter10 Step3 NormalLines" `
  -FailOnFound
```

안전 후보만 닫는다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/clear-example-error-windows.ps1 `
  -TargetProcessName 10_GeometryPipeline_Step3_NormalLines `
  -ExpectedTitle "ComputerGraphics - Chapter10 Step3 NormalLines" `
  -Close `
  -QuietSeconds 3
```

capture/run session 전체 quiet 상태를 확인한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/wait-capture-run-quiet.ps1 `
  -TargetProcessName 10_GeometryPipeline_Step3_NormalLines `
  -ExpectedTitle "ComputerGraphics - Chapter10 Step3 NormalLines" `
  -QuietSeconds 3
```

## Clean/Rebuild 발동 기준

다음 경우 해당 example만 Clean/Rebuild한다.

- output 폴더의 assimp DLL이 누락된다.
- DLL dialog가 탐지된다.
- runtime preflight에서 예상 title window가 뜨지 않는다.
- 같은 executable을 재실행해도 이전 error dialog가 남는다.

모든 example을 무조건 Clean/Rebuild하지 않는다. 외부 DLL 사용 또는 dialog 의심 상황에서만 안정성을 우선한다.

## Controlled Failure Rehearsal

capture/run cleanup 도구를 바꾸거나 무인 촬영을 재개하기 전에는 실제 example을 반복 실행하지 않고 synthetic dialog fixture로 먼저 drain 동작을 확인한다.

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/validators/test-capture-run-state.ps1
```

이 rehearsal은 stale session lock, protected process target 거부, message/fingerprint 수집, 다중 error dialog drain, 순차 dialog chain의 `Replaced` 판정, quiet period 재검사를 확인한다. 이 테스트가 실패하면 assimp 사용 example을 다시 실행하지 않고 원인을 먼저 조사한다.

## 중단 기준

- error dialog 후보가 target example과 관련 있는지 확신할 수 없다.
- close 후에도 같은 fingerprint 후보가 `StillPresent`로 남는다.
- quiet period 뒤에도 후보가 다시 나타난다.
- DLL 임시 rename 테스트 후 DLL 복원에 실패한다.
- GUI/window enumeration이 현재 세션에서 동작하지 않는다.
- 같은 error handling test가 반복 실패한다.

중단 시 사용자 알림을 실행하고 재실행 루프를 돌지 않는다.
