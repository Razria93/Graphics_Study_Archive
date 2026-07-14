# Part3 Chapter09

User interaction 예제를 archive 기준으로 정리하는 문서입니다.

## Scope

- Raw source: `C:\ComputerGraphics\Part3_Chapter09`
- Archive source: `Part3_Chapter09`
- Topic: first-person camera, mouse picking, picking ray collision, quaternion rotation, virtual trackball, mouse drag movement
- Import status: Step1-Step6 imported
- Build/run: Step1-Step6 성공
- Capture: 보류
- Public readiness: 검토 필요

## Import Candidates

| Example | Import status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | 반영 완료 | 성공 | 검토 필요 | first-person camera, skybox cubemap, ground texture, selected assets 포함 |
| `09_UserInteraction_Step2_MousePicking` | 반영 완료 | 성공 | 검토 필요 | mainline mouse picking 작업본, Step1 assets 재사용 |
| `09_UserInteraction_Step2_MousePicking_Debug` | 제외 / reference-only | 미확인 | 제외 | debug/memo 실험 흔적 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | 제외 / reference-only | 미확인 | 제외 | 미완성 작업본 |
| `09_UserInteraction_Step3_MousePickingRayCollision_Debug` | 제외 / reference-only | 미확인 | 제외 | debug variant |
| `09_UserInteraction_Step3_MousePickingRayCollision_Solution` | 반영 완료 | 성공 | 검토 필요 | archive 실행 기준, `earth.jpg` 포함 |
| `09_UserInteraction_Step4_QuaternianRotation` | 반영 완료 | 성공 | 검토 필요 | raw spelling 유지, quaternion rotation, Euler X/Y/Z GUI 미적용 |
| `09_UserInteraction_Step5_VirtualTrackball` | 반영 완료 | 성공 | 검토 필요 | mainline virtual trackball 작업본 |
| `09_UserInteraction_Step5_VirtualTrackball_Debug` | 제외 / reference-only | 미확인 | 제외 | debug 출력/실험 흔적 |
| `09_UserInteraction_Step6_MouseDragMove` | 반영 완료 | 성공 | 검토 필요 | mouse drag movement |

## Current Step

최근 import 대상은 `09_UserInteraction_Step6_MouseDragMove`입니다.

Step1에서 확인한 항목:

- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format` 제외
- 실행에 필요한 selected asset만 포함
- `Common.hlsli`는 shader compile 대상이 아니라 include/document file로 유지
- HLSL/HLSLI BOM 확인
- `.clang-format` project/filter 참조 제거와 STB include path 추가 이유를 `status.md`에 기록

Step1은 사용자가 Debug/Release 실행을 모두 확인했습니다.
Step2는 mainline source/project만 반영하고 `_Debug` variant는 reference-only로 제외했습니다.
Step2는 사용자가 Debug/Release 실행을 모두 확인했습니다.
Step3는 mainline과 `_Debug` variant가 미완성이므로 `_Solution` variant를 archive 실행 기준으로 반영했습니다.
Step3는 사용자가 Debug/Release 실행을 모두 확인했습니다.
Step4는 raw spelling `QuaternianRotation`을 유지하고, 문서에서는 quaternion rotation으로 설명합니다.
Step4는 사용자가 Debug/Release 실행을 모두 확인했습니다.
Step4의 `X(alpha)`, `Y(beta)`, `Z(gamma)` GUI는 raw 원본에서도 현재 transform 경로에 미적용입니다.
Step5는 mainline source/project만 반영하고 `_Debug` variant는 reference-only로 제외했습니다.
Step5는 사용자가 Debug/Release 실행을 모두 확인했습니다.
Step6는 Chapter09 마지막 예제로 mouse drag object movement를 확인합니다.
Step6는 사용자가 Debug/Release 실행을 모두 확인했습니다.

Chapter09 Step1-Step6 import와 실행 확인은 완료되었습니다.

다음 단계는 Part3 Chapter10-13 import 착수 전 raw 구조 재확인입니다.
