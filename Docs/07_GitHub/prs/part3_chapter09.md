# Part3 Chapter09 User Interaction 구현과 Demo

## 요약

이 PR은 `Part3_Chapter09` Step1–6의 camera·picking·object manipulation 흐름을 현재 build/run으로 재검증하고 Example, Topic, Verification과 상세 Demo로 연결한다. 입력과 결과 변화는 정적 storyboard로 설명하고, 대표 VirtualTrackball video는 Demo Issue 전용 댓글로 분리한다. 보조 마감 범위로 Chapter08 rendered evidence 공개 판단과 [Demo Issue #22](https://github.com/Razria93/Graphics_Study_Archive/issues/22), Demo 정적·동적 visual 게시 기준을 정렬한다.

## 범위

- Chapter09 Step1–6: FirstPersonView, GPU·CPU picking, quaternion rotation, VirtualTrackball과 MouseDragMove
- 문서·검증: Example README 6개, interaction Topic 3개, Verification, 상세 Demo 6개와 storyboard 7개
- Chapter08 publication closeout: 원본 runtime asset 비공개와 rendered evidence 공개 범위, [Demo Issue #22](https://github.com/Razria93/Graphics_Study_Archive/issues/22) 게시 상태 정렬
- Demo visual 체계: Issue 본문 정적 visual과 전용 댓글 video의 책임, template·validator·Publication checklist 정렬

## 핵심 개념

- Camera interaction: Client cursor의 절대 NDC 위치를 yaw·pitch로 변환하고 WASD 이동을 같은 view matrix에 반영한다.
- Picking: Object ID color를 1×1 staging texture로 읽는 GPU 방식에서 screen ray와 bounding sphere를 사용하는 CPU 방식으로 확장한다.
- Quaternion manipulation: Axis-angle 회전에서 시작해 sphere surface의 직전·현재 vector 사이 quaternion을 frame별로 누적한다.
- Depth-preserving drag: Drag 시작 hit의 near–far 비율을 유지한 world position을 계산해 object와 bounding volume을 함께 이동한다.

## 대표 예제

### Step1 FirstPersonView

Keyboard 이동과 cursor 기반 mouse-look을 camera view 갱신에 연결하는 Chapter09 interaction 기준선이다.

- README: [Step1 FirstPersonView](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md)
- Demo: [Step1 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_01_FirstPersonView.md)
- Topic: [Camera Interaction](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/CameraInteraction.md)

### Step2·3 Picking

GPU ID-color readback과 CPU screen-ray collision을 순서대로 구현해 hover·press interaction의 선택 경로를 비교한다.

- GPU picking: [Step2 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_02_MousePicking.md)
- CPU picking: [Step3 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_03_MousePickingRayCollision.md)
- Topic: [Picking And Screen Ray](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/PickingAndScreenRay.md)

### Step4–6 Object Manipulation

Axis-angle quaternion에서 VirtualTrackball 누적 회전으로 확장하고, 마지막 단계에서 같은 picking ray를 depth-preserving translation에 사용한다.

- Quaternion: [Step4 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_04_QuaternionRotation.md)
- VirtualTrackball: [Step5 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_05_VirtualTrackball.md)
- Drag move: [Step6 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/09_06_MouseDragMove.md)
- Topic: [Quaternion And Virtual Trackball](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/QuaternionAndVirtualTrackball.md)

## 검증

- Build/Run: Step1–6 Debug/Release x64 Clean/Rebuild와 Release run 성공
- Capture/Result: 전체 창 PNG 8장과 storyboard 7장의 full decode·metadata·공개 안전성 확인
- Video: interaction 동적 근거 8개 기술 검수, Step5 한 개를 Demo Issue 전용 댓글로 게시
- 문서: GitHub body, Demo, Topic, Markdown rendering·table·wrap과 video asset validator 통과

## 스크린샷

### Step5 VirtualTrackball 누적 회전

왼쪽에서 오른쪽으로 읽으면 sphere 표면의 drag가 frame별 quaternion 회전으로 누적되어 object orientation을 갱신하는 흐름이 보인다.

![Step5 VirtualTrackball](https://github.com/Razria93/Graphics_Study_Archive/blob/b9ca69933057894e0d124632018dca74735ecc5f/Docs/_assets/captures/part3_chapter09_05_virtual_trackball_storyboard.png?raw=true)

- 동적 근거: [VirtualTrackball video 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305)

## 미확인 / 제한

- Step1 mouse-look은 상대 mouse delta가 아니라 client cursor의 절대 NDC 위치를 사용한다.
- Step2는 picking pixel을 CPU로 동기 readback한다.
- Step3–6은 bounding sphere를 interaction proxy로 사용하며 triangle 단위 collision은 포함하지 않는다.
- Step5·6은 Windows mouse capture로 client 밖 release 상태를 복구한다.
- Runtime asset 원본과 직접 다운로드 링크는 공개하지 않고 승인된 Bundle의 rendered evidence만 사용한다.
- Resize resource lifetime의 공통 정규화는 현재 범위에 포함하지 않는다.

## 문서

- Chapter README: [Part3 Chapter09](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Part3_Chapter09/README.md)
- Topic: [Animation And Physics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/01_Topics/AnimationAndPhysics/README.md)
- Verification: [Part3 Chapter09 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/02_Verification/Part3_Chapter09/verification-index.md)
- Demo: [Part3 Chapter09 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/03_Demos/Part3_Chapter09/demo-index.md)
- WorkLog: [WU-Part3](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/04_WorkLogs/work-units/WU-Part3.md)
- Publication: [Candidate List](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter09-workflow/Docs/05_Publication/candidate-list.md)

## 관련 이슈

- [Part2 Chapter08 Shader Experiments Demo #22](https://github.com/Razria93/Graphics_Study_Archive/issues/22)
- [Part3 Chapter09 User Interaction Demo #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21)
- [Step5 VirtualTrackball video 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305)

## 다음 단계

- interaction video와 resize resource lifetime의 후속 검증 범위를 별도 작업으로 결정한다.
