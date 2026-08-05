# Shadow Mapping And Depth Bias

## 목적

Light-space depth map과 receiver depth 비교로 hard shadow를 만드는 기준을 정의한다.

## 책임 범위

- 개별 구현은 Example README와 상세 Demo로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Light-space projection

World position을 light view-projection으로 변환하고 shadow texture 좌표로 매핑한다.

### Depth bias

Self-shadowing을 줄이기 위해 receiver depth에 작은 bias를 적용하되 peter-panning과 균형을 맞춘다.

## 한계

- Cascade, slope-scale bias와 moment shadow map은 다루지 않는다.

## 관련 문서

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/13_04_ShadowMapping.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
