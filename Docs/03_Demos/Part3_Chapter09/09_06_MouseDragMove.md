# Chapter09 Step6 MouseDragMove Demo

## 목적

Picking ray의 drag 시작 depth를 보존해 sphere를 world space에서 이동하는 translation interaction을 보여준다.

## 책임 범위

- Ray depth ratio, world delta와 bounding sphere center 동기화를 설명한다.
- Screen ray 이론은 [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md), 검증 사실은 [Verification](../../02_Verification/Part3_Chapter09/verification-index.md)에 위임한다.

## 결과 미리보기

![Chapter09 Step6 MouseDragMove](../../_assets/captures/part3_chapter09_06_mouse_drag_move.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Drag 시작 hit distance와 현재 cursor near/far ray |
| 출력 | World-space translation delta와 이동된 sphere bounds |

## 구현 흐름

1. Drag 시작 ray와 sphere hit distance를 구한다.
2. Near-to-far segment에서 hit point의 depth ratio를 저장한다.
3. 현재 cursor ray의 같은 ratio 지점을 계산한다.
4. 이전 점과 현재 점의 delta를 model translation에 더한다.
5. Bounding sphere center를 model position과 동기화한다.

## 핵심 구현

### Depth-Preserving Drag

동일한 ray parameter를 유지해 screen cursor 이동을 world translation으로 바꾸고 다음 frame의 collision bounds도 함께 이동한다.

- [Drag depth ratio와 world delta](../../../Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/ExampleApp.cpp#L121-L178)
- [Model과 bounds 동기화](../../../Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/ExampleApp.cpp#L180-L183)

## 시각 결과

Textured sphere와 background가 screen-space drag의 depth 기준을 보여준다. Screenshot은 기본 위치를 기록하며 이동 전후 video는 후속 선택 증거다.

## 구현 범위와 한계

- Cursor ray가 이동한 sphere와 교차하지 않으면 drag가 중단된다.
- Plane 또는 axis constraint와 occlusion ordering은 구현하지 않는다.
- Earth와 cubemap asset의 공개 권리 근거가 부족해 Publication은 `검토 필요`다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter09/verification-index.md)

## 관련 코드

- [Mouse capture와 release 복구](../../../Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/AppBase.cpp#L232-L247)
- [Example README](../../../Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/README.md)

## 관련 문서

- [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md)
- [이전 Demo](09_05_VirtualTrackball.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
