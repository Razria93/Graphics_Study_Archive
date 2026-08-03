# Part3 Chapter09 Demo Index

이 문서는 `Part3_Chapter09`의 camera, picking과 object manipulation을 Step 순서대로 연결하고 capture/result 상태를 기록한다.

## 범위

- 순차 흐름: Step1 camera → Step2 GPU picking → Step3 ray picking → Step4 quaternion → Step5 trackball → Step6 drag move
- 주요 demo 후보: FirstPersonView, MousePicking, VirtualTrackball, MouseDragMove
- 비고: 원본 runtime asset은 비공개로 유지하고 Step1~6의 직접 실행 visual은 승인된 Chapter09 Bundle 예외에 따라 공개 가능하다.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Step1 FirstPersonView | [상세 Demo](09_01_FirstPersonView.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md) | [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [WASD](../../_assets/captures/part3_chapter09_01_first_person_view_wasd_storyboard.png), [mouse-look](../../_assets/captures/part3_chapter09_01_first_person_view_mouse_look_storyboard.png) | [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) | 확보 | cursor 기반 yaw·pitch와 WASD camera 이동 |
| Step2 MousePicking | [상세 Demo](09_02_MousePicking.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step2_MousePicking/README.md) | [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [hover 비교](../../_assets/captures/part3_chapter09_02_mouse_picking_hover_storyboard.png) | 미게시 | 확보 | ID color render target의 1×1 staging readback과 red highlight |
| Step3 MousePickingRayCollision | [상세 Demo](09_03_MousePickingRayCollision.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision/README.md) | [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [press lifecycle](../../_assets/captures/part3_chapter09_03_mouse_picking_ray_collision_storyboard.png) | 미게시 | 확보 | screen ray와 BoundingSphere 교차 기반 CPU picking |
| Step4 QuaternionRotation | [상세 Demo](09_04_QuaternionRotation.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step4_QuaternianRotation/README.md) | [Quaternion And Virtual Trackball](../../01_Topics/AnimationAndPhysics/QuaternionAndVirtualTrackball.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [axis 비교](../../_assets/captures/part3_chapter09_04_quaternion_rotation_storyboard.png) | 미게시 | 확보 | axis-angle quaternion rotation과 zero-axis fallback |
| Step5 VirtualTrackball | [상세 Demo](09_05_VirtualTrackball.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step5_VirtualTrackball/README.md) | [Quaternion And Virtual Trackball](../../01_Topics/AnimationAndPhysics/QuaternionAndVirtualTrackball.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [surface drag](../../_assets/captures/part3_chapter09_05_virtual_trackball_storyboard.png), [video 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305) | [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) | 확보 | sphere surface vector 사이의 quaternion drag rotation |
| Step6 MouseDragMove | [상세 Demo](09_06_MouseDragMove.md) | [Example](../../../Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/README.md) | [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [screen drag](../../_assets/captures/part3_chapter09_06_mouse_drag_move_storyboard.png) | [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) | 확보 | near/far hit ratio를 유지하는 object translation |
| 최소 capture | [Step1 상세 Demo](09_01_FirstPersonView.md) | [Step1 Example](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md) | [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md) | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [기본](../../_assets/captures/part3_chapter09_01_first_person_view.png) | 미게시 | 확보 | Chapter 최초 camera interaction visual |
| 대표 capture | [Step5](09_05_VirtualTrackball.md), [Step1](09_01_FirstPersonView.md), [Step6](09_06_MouseDragMove.md) | [Chapter README](../../../Part3_Chapter09/README.md) | 관련 Topic | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [Trackball](../../_assets/captures/part3_chapter09_05_virtual_trackball_storyboard.png), [Mouse-look](../../_assets/captures/part3_chapter09_01_first_person_view_mouse_look_storyboard.png), [Drag](../../_assets/captures/part3_chapter09_06_mouse_drag_move_storyboard.png) | [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) | 확보 | Step5를 대표, Step1과 Step6을 보조 visual로 게시함 |
| video | [Step1](09_01_FirstPersonView.md), [Step3](09_03_MousePickingRayCollision.md), [Step4](09_04_QuaternionRotation.md), [Step5](09_05_VirtualTrackball.md), [Step6](09_06_MouseDragMove.md) | [Chapter README](../../../Part3_Chapter09/README.md) | 관련 Topic | [Verification](../../02_Verification/Part3_Chapter09/verification-index.md) | [Step5 published video](https://github.com/user-attachments/assets/5217ba4b-1b18-4cbb-9635-ecd89d721cb9), selected local video 7개 | [Demo Issue #21 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305) | 확보 | Step5만 한 번 게시하고 나머지 7개는 local evidence로 유지함 |

## 갱신 기준

- 새로운 Step을 검증하면 Step 순서와 상세 Demo 링크를 함께 갱신한다.
- Capture와 Publication 상태는 Verification 및 Publication 정본과 맞춘다.
- 동적 입력이 정지 이미지보다 새로운 정보를 제공할 때만 video를 추가한다.

## 관련 문서

- [Chapter README](../../../Part3_Chapter09/README.md)
- [Verification](../../02_Verification/Part3_Chapter09/verification-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
