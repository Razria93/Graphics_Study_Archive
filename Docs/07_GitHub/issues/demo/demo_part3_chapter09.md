# Part3 Chapter09 User Interaction Demo

## 요약

Camera 입력에서 시작해 GPU·CPU picking, quaternion 회전, virtual trackball과 depth-preserving drag로 확장되는 여섯 단계의 interaction 흐름이다.

대표 visual은 구 표면 drag 회전, mouse-look camera 전환, 화면 drag에 따른 object translation을 서로 다른 설명 축으로 보여준다.

## 결과

### VirtualTrackball 누적 회전

왼쪽에서 오른쪽으로 읽으면 sphere hit 지점의 변화가 frame별 quaternion 회전으로 누적되어 object orientation을 갱신하는 흐름이 보인다.

![VirtualTrackball 누적 회전](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Docs/_assets/captures/part3_chapter09_05_virtual_trackball_storyboard.png?raw=true)

### FirstPersonView mouse-look

왼쪽 시야에서 정면을 거쳐 오른쪽 시야로 이동하며 cursor의 절대 NDC 위치가 camera yaw와 pitch에 반영되는 결과를 보여준다.

![FirstPersonView mouse-look](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Docs/_assets/captures/part3_chapter09_01_first_person_view_mouse_look_storyboard.png?raw=true)

### MouseDragMove world translation

화면 위 drag가 시작 hit의 depth ratio를 유지한 world-space 이동으로 변환되어 sphere가 cursor를 따라 움직이는 결과를 보여준다.

![MouseDragMove world translation](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Docs/_assets/captures/part3_chapter09_06_mouse_drag_move_storyboard.png?raw=true)

## 핵심 구현

### Sphere surface vector 기반 VirtualTrackball

Picking ray가 sphere와 만나는 지점을 중심 기준 vector로 바꾸고 직전 vector와 현재 vector 사이의 quaternion을 계산한다. 기준 vector를 매 frame 갱신해 drag 경로를 object rotation에 누적한다.

- [Sphere hit와 frame별 quaternion 누적](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Part3_Chapter09/09_UserInteraction_Step5_VirtualTrackball/ExampleApp.cpp#L120-L193)

### Cursor NDC 기반 camera 조작

Client cursor 위치를 NDC로 바꿔 yaw와 pitch를 계산하고, WASD 상태는 camera의 forward·right 방향 이동으로 연결한다. Mouse-look과 keyboard 이동이 같은 view matrix에 반영된다.

- [Cursor 위치의 NDC 변환과 camera 전달](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/AppBase.cpp#L136-L155)
- [WASD 상태의 camera 이동 반영](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/ExampleApp.cpp#L53-L68)
- [Yaw·pitch와 camera 방향 갱신](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/Camera.cpp#L26-L55)

### Hit depth를 보존하는 object drag

Drag 시작 시 near–far segment에서 hit가 차지하는 비율을 저장하고 이후 cursor ray에서도 같은 비율의 world position을 계산한다. Frame 간 위치 차이를 model translation과 bounding sphere에 함께 반영한다.

- [Picking depth ratio와 world-space translation](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/ExampleApp.cpp#L121-L183)

## 처리 흐름

1. Step1에서 cursor와 WASD 입력을 camera view 변화로 연결한다.
2. Step2에서 object ID color target을 1×1 staging texture로 읽어 GPU picking을 확인한다.
3. Step3에서 screen ray와 bounding sphere intersection으로 CPU picking을 구성한다.
4. Step4에서 axis-angle 입력을 quaternion과 rotation matrix로 변환한다.
5. Step5에서 sphere surface drag vector 사이의 quaternion을 누적한다.
6. Step6에서 drag 시작 depth를 유지하며 object와 bounding volume을 함께 이동한다.

## 구현 범위와 한계

- Step1 mouse-look은 상대 mouse delta가 아니라 client cursor의 절대 NDC 위치를 사용한다.
- Step2 GPU picking은 ID color target의 cursor pixel을 CPU로 동기 readback한다.
- Step3~6은 bounding sphere를 interaction proxy로 사용하며 mesh triangle 단위 collision은 포함하지 않는다.
- Step5·6은 drag 중 cursor가 client 밖으로 나간 뒤 release되는 상태를 복구한다.
- Resize resource 수명 정규화는 후속 공통 portability 작업으로 분리한다.

## 검증

- Step1~6 Debug/Release x64 Clean/Rebuild와 Release run 성공
- 1282×752 전체 창 PNG 8장과 storyboard 7장 full decode 및 공개 안전성 확인
- Selected local video 8개의 H.264, `yuv420p`, CFR 30 FPS, audio stream 0개와 full decode 확인

## 더 자세히 보기

### Chapter 안내

- [Part3 Chapter09 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Part3_Chapter09/README.md)
- [Chapter09 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/demo-index.md)
- [Chapter09 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/02_Verification/Part3_Chapter09/verification-index.md)

### 대표 구현

- [Step5 VirtualTrackball 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_05_VirtualTrackball.md)
- [Step1 FirstPersonView 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_01_FirstPersonView.md)
- [Step6 MouseDragMove 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_06_MouseDragMove.md)

### 관련 개념

- [Camera Interaction](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/CameraInteraction.md)
- [Picking And Screen Ray](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/PickingAndScreenRay.md)
- [Quaternion And Virtual Trackball](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/QuaternionAndVirtualTrackball.md)
