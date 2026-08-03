# Quaternion And Virtual Trackball

## 목적

Axis-angle rotation을 quaternion으로 표현하고, 구 표면의 pointer 이동을 object rotation으로 변환하는 virtual trackball 원리를 설명한다.

## 책임 범위

Quaternion 표현과 두 vector 사이 회전의 일반 개념을 다룬다. Chapter09의 UI 값, collision point와 matrix 적용 코드는 Step4·5 Example README로 위임한다.

## 개념 흐름

회전축과 각도를 unit quaternion으로 만들거나 drag 시작·현재 vector 사이의 quaternion을 계산하고, 이를 rotation matrix로 변환해 기존 model transform에 합성한다.

## 핵심 개념

### Axis-Angle Quaternion

단위 축 `n`과 각도 `theta`는 vector part `n sin(theta/2)`와 scalar part `cos(theta/2)`로 표현한다. 축 길이가 0이면 정규화할 수 없으므로 안전한 기본 축 또는 identity rotation이 필요하다.

### Virtual Trackball

구 표면의 이전 hit vector와 현재 hit vector를 정규화하고 두 방향을 잇는 quaternion을 구한다. 화면 drag가 object 중심을 기준으로 하는 3D rotation으로 변환된다.

## 데모 연결

Step4는 수치 axis-angle 입력을, Step5는 sphere hit point의 연속 변화로 만든 quaternion을 적용한다. Step6은 rotation이 아니라 같은 screen ray를 translation에 재사용한다.

## 한계

Cursor가 sphere silhouette 밖으로 나갔을 때의 continuous arcball projection, angular inertia와 constraint axis는 다루지 않는다.

## 관련 문서

- [Step4 Example](../../../Part3_Chapter09/09_UserInteraction_Step4_QuaternianRotation/README.md)
- [`Docs/03_Demos` Step4 Demo](../../03_Demos/Part3_Chapter09/09_04_QuaternionRotation.md)
- [`Docs/02_Verification`](../../02_Verification/Part3_Chapter09/verification-index.md)
