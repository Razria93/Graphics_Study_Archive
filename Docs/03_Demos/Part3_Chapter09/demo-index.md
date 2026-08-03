# Part3 Chapter09 Demo Index

이 문서는 `Part3_Chapter09`의 camera, picking과 object manipulation을 Step 순서대로 연결하고 capture/result 상태를 기록한다.

## 범위

- 순차 흐름: Step1 camera → Step2 GPU picking → Step3 ray picking → Step4 quaternion → Step5 trackball → Step6 drag move
- 주요 demo 후보: FirstPersonView, MousePicking, VirtualTrackball, MouseDragMove
- 비고: Step1~6 screenshot은 확보했으나 runtime asset 권리 근거 확인 전에는 GitHub 게시 후보로 선정하지 않는다.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Step1 FirstPersonView | [상세 Demo](09_01_FirstPersonView.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md) | [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [기본](../../_assets/captures/part3_chapter09_01_first_person_view.png) | 미게시 | 확보 | cursor 기반 yaw·pitch와 WASD camera 이동 |
| Step2 MousePicking | [상세 Demo](09_02_MousePicking.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step2_MousePicking/README.md) | [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [기본](../../_assets/captures/part3_chapter09_02_mouse_picking.png) | 미게시 | 확보 | ID color render target의 1×1 staging readback |
| 최소 capture | [Step1 상세 Demo](09_01_FirstPersonView.md) | [Step1 Example](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md) | [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [기본](../../_assets/captures/part3_chapter09_01_first_person_view.png) | 미게시 | 확보 | Chapter 최초 camera interaction visual |
| 대표 capture | [Step2 상세 Demo](09_02_MousePicking.md) | [Step2 Example](../../../Part3_Chapter09/09_UserInteraction_Step2_MousePicking/README.md) | [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [Picking](../../_assets/captures/part3_chapter09_02_mouse_picking.png) | 미게시 | 확보 | Checkpoint 1 대표 visual, 권리 근거 확인 전 Publication 검토 필요 |
| video | [Step1 상세 Demo](09_01_FirstPersonView.md) | [Step1 Example](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md) | [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | 없음 | 미게시 | 제외 | Checkpoint 1에서는 screenshot만 사용 |

## 갱신 기준

- 새로운 Step을 검증하면 Step 순서와 상세 Demo 링크를 함께 갱신한다.
- Capture와 Publication 상태는 Verification 및 Publication 정본과 맞춘다.
- 동적 입력이 정지 이미지보다 새로운 정보를 제공할 때만 video를 추가한다.

## 관련 문서

- [Chapter README](../../../Part3_Chapter09/README.md)
- [Verification](../../02_Verification/Part3_Chapter09/verification-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
