# Percentage Closer Filtering And PCSS

## 목적

Shadow map comparison을 공간적으로 filtering하는 PCF와 blocker 기반 variable penumbra를 만드는 PCSS를 구분한다.

## 책임 범위

- 개별 구현은 Example README와 상세 Demo로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### PCF

여러 comparison result를 평균해 binary shadow edge를 고정 폭으로 부드럽게 만든다.

### PCSS

Blocker search에서 평균 blocker depth를 구하고 receiver 거리와 light size로 penumbra 폭을 추정한다.

## 한계

- Sampling pattern, light frustum과 blocker search는 approximation에 의존한다.

## 관련 문서

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/13_06_SoftShadowPCSS.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
