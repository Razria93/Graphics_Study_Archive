# Chapter13 Step7 Halo

Depth-aware post effect로 밝은 light 주변의 halo를 합성한다.

## 구현 요약

- PCSS scene에 screen-space depth-aware halo pass를 추가한다.
- Chapter13 공통 scene, HDR post-process와 UI 구조를 유지한다.
- 일반 이론은 [Post Processing And Bloom](../../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)으로, build/run/capture 사실은 Verification으로 위임한다.

## 핵심 코드

- [Depth-aware post effect 기반 halo composite](./PostEffectsPS.hlsl#L79-L153)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Capture | 완료 | 전체 application window |

## Capture/Result

![Chapter13 Step7 Halo Strength 0](../../Docs/_assets/captures/part3_chapter13_07_halo_strength_0p0.png)

![Chapter13 Step7 Halo Strength 0.6](../../Docs/_assets/captures/part3_chapter13_07_halo_strength_0p6.png)

원본 runtime asset은 직접 연결하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/13_07_Halo.md)
- [Post Processing And Bloom](../../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
