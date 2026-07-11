# Part3 Chapter09

User interaction 예제를 archive 기준으로 정리하는 문서입니다.

## Scope

- Raw source: `C:\ComputerGraphics\Part3_Chapter09`
- Archive source: `Part3_Chapter09`
- Topic: first-person camera, mouse picking, picking ray collision, quaternion rotation, virtual trackball, mouse drag movement
- Import status: Step1 imported
- Build/run: 미확인
- Capture: 보류
- Public readiness: 검토 필요

## Import Candidates

| Example | Import status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | 반영 완료 | 미확인 | 검토 필요 | first-person camera, skybox cubemap, ground texture, selected assets 포함 |
| `09_UserInteraction_Step2_MousePicking` | 예정 | 미확인 | 검토 필요 | mainline mouse picking 작업본 |
| `09_UserInteraction_Step2_MousePicking_Debug` | 제외 / reference-only | 미확인 | 제외 | debug/memo 실험 흔적 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | 예정 | 미확인 | 검토 필요 | 사용자 작업본 |
| `09_UserInteraction_Step3_MousePickingRayCollision_Debug` | 제외 / reference-only | 미확인 | 제외 | debug variant |
| `09_UserInteraction_Step3_MousePickingRayCollision_Solution` | reference solution 후보 | 미확인 | 검토 필요 | public 후보 아님 |
| `09_UserInteraction_Step4_QuaternianRotation` | 예정 | 미확인 | 검토 필요 | quaternion rotation |
| `09_UserInteraction_Step5_VirtualTrackball` | 예정 | 미확인 | 검토 필요 | virtual trackball 작업본 |
| `09_UserInteraction_Step5_VirtualTrackball_Debug` | 제외 / reference-only | 미확인 | 제외 | debug 출력/실험 흔적 |
| `09_UserInteraction_Step6_MouseDragMove` | 예정 | 미확인 | 검토 필요 | mouse drag movement |

## Current Step

현재 import 대상은 `09_UserInteraction_Step1_FirstPersonView`입니다.

Step1에서 확인한 항목:

- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format` 제외
- 실행에 필요한 selected asset만 포함
- `Common.hlsli`는 shader compile 대상이 아니라 include/document file로 유지
- HLSL/HLSLI BOM 확인
- `.clang-format` project/filter 참조 제거와 STB include path 추가 이유를 `status.md`에 기록

다음 단계는 사용자의 Debug/Release 실행 확인입니다.
