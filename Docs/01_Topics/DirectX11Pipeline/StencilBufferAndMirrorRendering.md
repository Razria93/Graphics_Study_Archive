# Stencil Buffer And Mirror Rendering

## 목적

Stencil buffer로 mirror 영역을 표시하고 reflection transform을 적용한 geometry를 해당 영역에 제한하는 과정을 정의한다.

## 책임 범위

- 개별 구현은 Example README와 상세 Demo로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Stencil mask

Mirror polygon을 stencil reference로 기록하고 reflected pass는 같은 reference를 통과한 pixel만 갱신한다.

### Reflection transform

Mirror plane에 대한 reflection matrix로 object transform을 만들고 winding·culling 변화까지 함께 관리한다.

## 한계

- Planar mirror와 단일 reflection pass만 다룬다.

## 관련 문서

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/13_01_Mirror.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
