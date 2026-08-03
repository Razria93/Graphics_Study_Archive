# Part3 Chapter09 User Interaction

Chapter09는 camera 입력에서 시작해 GPU·CPU picking, quaternion 회전, virtual trackball과 depth-preserving drag로 확장되는 사용자 상호작용 흐름을 다룬다.

## Study Map

| 단계 | 핵심 변화 | Example | Demo |
| --- | --- | --- | --- |
| Step1 | 절대 cursor 위치와 WASD를 camera pose로 변환 | [FirstPersonView](09_UserInteraction_Step1_FirstPersonView/README.md) | [상세 Demo](../Docs/03_Demos/Part3_Chapter09/09_01_FirstPersonView.md) |
| Step2 | ID color render target과 CPU readback으로 hover picking | [MousePicking](09_UserInteraction_Step2_MousePicking/README.md) | [상세 Demo](../Docs/03_Demos/Part3_Chapter09/09_02_MousePicking.md) |
| Step3 | screen ray와 bounding sphere로 CPU collision picking | [MousePickingRayCollision](09_UserInteraction_Step3_MousePickingRayCollision/README.md) | [상세 Demo](../Docs/03_Demos/Part3_Chapter09/09_03_MousePickingRayCollision.md) |
| Step4 | axis-angle을 quaternion과 rotation matrix로 변환 | [QuaternionRotation](09_UserInteraction_Step4_QuaternianRotation/README.md) | [상세 Demo](../Docs/03_Demos/Part3_Chapter09/09_04_QuaternionRotation.md) |
| Step5 | 구 표면의 두 hit vector로 drag rotation 계산 | [VirtualTrackball](09_UserInteraction_Step5_VirtualTrackball/README.md) | [상세 Demo](../Docs/03_Demos/Part3_Chapter09/09_05_VirtualTrackball.md) |
| Step6 | drag 시작 depth를 유지하며 world translation 계산 | [MouseDragMove](09_UserInteraction_Step6_MouseDragMove/README.md) | [상세 Demo](../Docs/03_Demos/Part3_Chapter09/09_06_MouseDragMove.md) |

## 검증 상태

- Debug/Release x64 Clean/Rebuild와 run: Step1~6 성공, 2026-08-03 현재 확인
- Capture: Step1~6 기본 PNG, Step2 hover·Step3 press PNG와 Step1·3·4·5·6 selected local video 확보
- Runtime working directory: 각 project 폴더
- Publication: 원본 runtime asset은 비공개로 유지하고 Step1~6의 직접 실행 visual은 승인된 Bundle 예외에 따라 공개 가능

## 관련 문서

- [User Interaction Topics](../Docs/01_Topics/AnimationAndPhysics/README.md)
- [Verification](../Docs/02_Verification/Part3_Chapter09/verification-index.md)
- [Demo Index](../Docs/03_Demos/Part3_Chapter09/demo-index.md)
- [Publication Candidate List](../Docs/05_Publication/candidate-list.md)
- [Source Registry](../Docs/99_Legacy/source-registry.md)
