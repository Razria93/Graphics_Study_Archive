# Area Light Approximation

## 목적

Point light와 달리 유한한 크기를 가진 emitter를 representative point로 근사하는 기준을 정의한다.

## 책임 범위

- 개별 구현은 Example README와 상세 Demo로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Representative point

Reflection ray와 sphere emitter 관계를 사용해 shading point가 참조할 light 위치를 보정한다.

### Radius response

Emitter radius가 커질수록 highlight와 illumination의 공간적 범위가 넓어지는 효과를 근사한다.

## 한계

- 정확한 sphere integration과 multiple importance sampling은 다루지 않는다.

## 관련 문서

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step8_UnrealSphereLight/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/13_08_UnrealSphereLight.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
