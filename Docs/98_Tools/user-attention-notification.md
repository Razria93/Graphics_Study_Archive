# User Attention Notification

이 문서는 substantive task가 종료되거나 사용자 확인이 필요할 때 Windows 알림음을 한 번 재생하는 방법을 설명한다.

## 실행 조건

- 목표 모드가 `complete` 또는 `blocked`로 종료된다.
- 장시간 또는 도구를 사용한 작업의 최종 보고를 제공한다.
- 후속 작업에 바로 사용할 수 있는 완성형 작업 프롬프트를 최종 산출물로 제공한다.
- 사용자 승인이나 결정이 필요해 작업을 중단한다.
- 오류 또는 외부 상태 때문에 더 진행할 수 없다.

완성형 작업 프롬프트는 권한, 작업 범위, 검증과 완료 조건을 갖추고 복사해 다음 작업에 바로 사용할 수 있는 전체 프롬프트를 말한다. 일부 문장이나 제목만 제안한 경우, 후속 수정이 필요한 초안, 일반 작업 계획, 단순 설명, 짧은 질의응답, 중간 commentary와 status update에는 실행하지 않는다. 일부 수정 요청의 결과로 완성된 전체 프롬프트를 다시 제공하면 실행 조건에 포함한다.

한 assistant turn에서는 여러 terminal point가 겹쳐도 알림을 최대 한 번만 실행한다. event는 실제 종료 상태에 따라 다음 우선순위로 선택한다.

1. 진행 불가 blocker는 `Blocked`를 사용한다.
2. 사용자 승인이나 결정이 필요하면 `Attention`을 사용한다.
3. 정상 목표 완료 또는 완성형 작업 프롬프트 제공은 `Complete`를 사용한다.

목표 모드 완료와 완성형 작업 프롬프트 제공이 겹치면 `Complete`를 한 번만 실행한다.

## 실행

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/scripts/notify-user.ps1 -Event Complete
```

`-Event`는 `Complete`, `Attention`, `Blocked` 중 하나를 사용한다. 현재 모든 event는 `%WINDIR%\Media\Windows Logon.wav`를 재생한다.

목표 모드를 사용하는 경우 목표 상태를 먼저 정리하고 최종 응답 직전에 실행한다. 완성형 작업 프롬프트를 제공하는 경우에도 전체 프롬프트 작성을 마친 뒤 최종 응답 직전에 실행한다.

## 판정 예시

다음 요청에 전체 실행 프롬프트를 제공하면 알림을 실행한다.

- 목표 모드와 agent 활용을 포함한 다음 작업 프롬프트 작성
- 4중 백틱으로 바로 사용할 수 있는 작업 프롬프트 작성
- 다음 세션에서 실행할 전체 프롬프트 작성

다음 응답에는 알림을 실행하지 않는다.

- 용어나 문장의 의미 설명
- 일반 작업 계획 제안
- 프롬프트 제목이나 일부 문장만 수정
- 도구 실행 전 임시 초안과 중간 상태 보고

## 실패 처리

Windows가 아니거나 음원 파일 또는 audio device를 사용할 수 없으면 짧은 warning만 출력한다. 알림 실패는 원래 작업, validator와 commit 결과를 변경하지 않는다.

스크립트는 system volume, registry, Windows notification 설정과 system file을 변경하지 않으며 background process와 로그 파일을 만들지 않는다.

실제 소리가 들렸는지는 사용자가 확인한다.
