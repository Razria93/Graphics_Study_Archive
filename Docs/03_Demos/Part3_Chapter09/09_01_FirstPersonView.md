# Chapter09 Step1 FirstPersonView Demo

## 목적

Keyboard와 cursor 입력이 camera view 변화로 이어지는 Chapter09의 입력 기준선을 보여준다.

## 책임 범위

- 절대 cursor NDC와 WASD 상태를 camera에 연결하는 구현을 설명한다.
- 일반 camera 이론은 [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md), 검증 사실은 [Verification](../../02_Verification/Part3_Chapter09/verification-index.md)에 위임한다.

## 결과 미리보기

### WASD 이동

`Initial → W → S → A → D` 순서로 왼쪽 위에서 오른쪽 아래로 본다.

![Chapter09 Step1 WASD storyboard](../../_assets/captures/part3_chapter09_01_first_person_view_wasd_storyboard.png)

- 입력 변화: 각 방향 key를 2초간 누른 뒤 release한다.
- 관찰 지점: 같은 정면 기준에서 camera position 변화가 지면 숫자와 원경의 상대 위치에 반영된다.
- 구현 결과: Keyboard 상태와 frame delta가 camera translation으로 누적된다.

### Mouse-look 시선 전환

`Center → Left → Center → Right → Center` 순서로 왼쪽 위에서 오른쪽 아래로 본다.

![Chapter09 Step1 mouse-look storyboard](../../_assets/captures/part3_chapter09_01_first_person_view_mouse_look_storyboard.png)

- 입력 변화: Cursor를 중앙에서 왼쪽 끝과 오른쪽 끝으로 각각 5초간 drag한다.
- 관찰 지점: 수평 입력 방향에 따라 camera yaw가 바뀌고 중앙으로 돌아오면 정면 view가 복구된다.
- 구현 결과: 절대 cursor NDC가 camera orientation에 직접 연결된다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Cursor client position, WASD key state, frame delta |
| 출력 | Camera yaw·pitch·position과 갱신된 view matrix |

## 구현 흐름

1. Cursor 위치를 NDC로 변환한다.
2. Camera가 NDC에서 yaw와 pitch를 갱신한다.
3. WASD 상태에 frame delta를 적용해 camera position을 이동한다.
4. View·projection을 scene constant buffer에 전달한다.

## 핵심 구현

### Camera Input Mapping

절대 cursor 위치가 orientation을 직접 결정하고 keyboard 상태는 frame마다 translation을 누적한다.

- [Cursor NDC와 camera 전달](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/AppBase.cpp#L136-L155)
- [WASD camera translation](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/ExampleApp.cpp#L52-L67)

## 시각 결과

두 storyboard는 translation과 orientation을 별도 변화 축으로 보여준다. 연속 이동 속도와 camera 전환 과정은 selected local video 두 개에서 확인한다.

## 구현 범위와 한계

- 절대 cursor 매핑을 사용하며 relative mouse-look은 구현하지 않는다.
- Pointer lock, raw input과 focus reset은 범위 밖이다.
- Mouse-look video는 사용자가 지정한 네 구간의 5초 이동을 보존해 일반 권장 길이보다 길다.
- Scene asset의 공개 권리 근거가 부족해 Publication은 `검토 필요`다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter09/verification-index.md)

## 관련 코드

- [Camera orientation 계산](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/Camera.cpp#L26-L55)
- [Example README](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md)

## 관련 문서

- [Camera Interaction](../../01_Topics/AnimationAndPhysics/CameraInteraction.md)
- [Demo Index](demo-index.md)
- [다음 Demo](09_02_MousePicking.md)
