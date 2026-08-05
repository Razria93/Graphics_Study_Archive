# Chapter13 Step3 DepthBufferAndFog Demo

## 목적

Depth buffer를 reconstruct해 distance fog post effect를 계산한다.

## 책임 범위

- PSO scene에 depth-only resource와 fog post-process를 추가한다.
- 일반 이론은 [Depth Reconstruction And Fog](../../01_Topics/DirectX11Pipeline/DepthReconstructionAndFog.md)으로 위임한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)으로 위임한다.

## 결과 미리보기

### Render View

![Chapter13 Step3 Render](../../_assets/captures/part3_chapter13_03_render_depthscale_0p5.png)

### Depth View

![Chapter13 Step3 Depth](../../_assets/captures/part3_chapter13_03_depth_depthscale_0p5.png)

DepthScale 0.5 기준에서 render view와 reconstructed depth view를 비교한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Scene color, depth buffer, projection parameters |
| 출력 | Depth 기반 fog가 적용된 scene |

## 구현 흐름

1. 필요한 scene resource와 pipeline state를 준비한다.
2. PSO scene에 depth-only resource와 fog post-process를 추가한다.
3. 결과를 HDR target과 post-process를 거쳐 표시한다.

## 핵심 구현

- [Depth reconstruction 기반 distance fog post effect](../../../Part3_Chapter10-13/13_LightAndShadow_Step3_DepthBufferAndFog/PostEffectsPS.hlsl#L49-L67)

## 시각 결과

전체 창 capture에서 render view와 depth view 전환에 따른 depth reconstruction 결과를 확인한다.

## 구현 범위와 한계

- 단일 exponential·distance fog이며 volumetric scattering은 제외한다.
- 출처 불완전 runtime asset은 직접 공개 링크하지 않는다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter10-13/verification-index.md)

## 관련 코드

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step3_DepthBufferAndFog/README.md)

## 관련 문서

- [Demo Index](demo-index.md)
- [이전 Demo](13_02B_ShadowPrototype.md)
- [다음 Demo](13_04_ShadowMapping.md)
