# Chapter13 Step3 DepthBufferAndFog

Depth buffer를 reconstruct해 distance fog post effect를 계산한다.

## 구현 요약

- PSO scene에 depth-only resource와 fog post-process를 추가한다.
- Chapter13 공통 scene, HDR post-process와 UI 구조를 유지한다.
- 일반 이론은 Topic으로, build/run/capture 사실은 Verification으로 위임한다.

## 핵심 코드

- [Depth reconstruction 기반 distance fog post effect](./PostEffectsPS.hlsl#L49-L67)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Capture | 완료 | 전체 application window |

## Capture/Result

![Chapter13 Step3 DepthBufferAndFog](../../Docs/_assets/captures/part3_chapter13_03_depth_buffer_and_fog.png)

원본 runtime asset은 직접 연결하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/13_03_DepthBufferAndFog.md)
- [Topic](../../Docs/01_Topics/DirectX11Pipeline/DepthReconstructionAndFog.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
