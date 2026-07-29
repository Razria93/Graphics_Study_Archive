# User Attention Notification

이 문서는 substantive task가 종료되거나 사용자 확인이 필요할 때 Windows 알림음을 한 번 재생하는 방법을 설명한다.

## 실행 조건

- 목표 모드가 `complete` 또는 `blocked`로 종료된다.
- 장시간 또는 도구를 사용한 작업의 최종 보고를 제공한다.
- 사용자 승인이나 결정이 필요해 작업을 중단한다.
- 오류 또는 외부 상태 때문에 더 진행할 수 없다.

단순 설명, 짧은 질의응답, 중간 commentary와 status update에는 실행하지 않는다. 한 assistant turn의 같은 terminal point에서는 한 번만 실행한다.

## 실행

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/scripts/notify-user.ps1 -Event Complete
```

`-Event`는 `Complete`, `Attention`, `Blocked` 중 하나를 사용한다. 현재 모든 event는 `%WINDIR%\Media\Windows Logon.wav`를 재생한다.

목표 모드를 사용하는 경우 목표 상태를 먼저 정리하고 최종 응답 직전에 실행한다.

## 실패 처리

Windows가 아니거나 음원 파일 또는 audio device를 사용할 수 없으면 짧은 warning만 출력한다. 알림 실패는 원래 작업, validator와 commit 결과를 변경하지 않는다.

스크립트는 system volume, registry, Windows notification 설정과 system file을 변경하지 않으며 background process와 로그 파일을 만들지 않는다.

실제 소리가 들렸는지는 사용자가 확인한다.
