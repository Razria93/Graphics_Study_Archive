# Depth Reconstruction And Fog

## 목적

Depth buffer 값을 view 또는 world distance로 복원해 screen-space fog에 사용하는 기준을 정의한다.

## 책임 범위

- 개별 구현은 Example README와 상세 Demo로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Non-linear depth

Projection 이후 depth는 선형 거리가 아니므로 near·far와 projection 관계를 사용해 복원한다.

### Fog composition

복원한 거리에 따라 scene color와 fog color의 blend factor를 계산한다.

## 한계

- Volumetric scattering과 temporal integration은 다루지 않는다.

## 관련 문서

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step3_DepthBufferAndFog/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/13_03_DepthBufferAndFog.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
