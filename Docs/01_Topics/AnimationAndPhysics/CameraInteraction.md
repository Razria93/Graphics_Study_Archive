# Camera Interaction

## 목적

Keyboard와 pointer 입력을 camera pose 변화로 해석하고 view matrix에 반영하는 기본 흐름을 설명한다.

## 책임 범위

일반적인 camera input과 view 갱신을 다룬다. Chapter09 Step1의 구체적인 key code와 source 위치는 Example README, 실행 결과는 상세 Demo, build/run 사실은 Verification에 위임한다.

## 개념 흐름

입력 상태를 수집하고 frame delta에 따라 translation 또는 orientation을 갱신한 뒤, camera basis에서 view matrix를 다시 계산한다.

## 핵심 개념

### Translation Input

WASD 같은 digital input은 frame마다 이동 방향과 속도를 누적한다. Frame delta를 곱하면 frame rate에 따른 이동량 차이를 줄일 수 있다.

### Orientation Input

Pointer 좌표 또는 상대 이동량은 yaw와 pitch로 변환한다. 절대 위치 매핑은 구현이 단순하지만 cursor 위치가 orientation을 직접 결정하므로 상대 mouse-look과 조작 감각이 다르다.

## 데모 연결

Chapter09 Step1은 절대 cursor NDC와 keyboard 상태를 camera에 전달하는 예시다. Scene과 asset 구성은 camera 이론이 아니라 Example의 시각적 기준선이다.

## 한계

Pointer lock, raw input, acceleration, pitch clamp와 focus 복구 같은 production camera 기능은 다루지 않는다.

## 관련 문서

- [Step1 Example](../../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md)
- [`Docs/03_Demos` Step1 Demo](../../03_Demos/Part3_Chapter09/09_01_FirstPersonView.md)
- [`Docs/02_Verification`](../../02_Verification/Part3_Chapter09/verification-index.md)
