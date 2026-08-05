# Chapter13 Step5 SoftShadowPCF

여러 depth comparison sample을 평균해 shadow edge를 부드럽게 만든다.

## 구현 요약

- Step4의 단일 hard comparison을 64-sample PCF kernel로 확장한다.
- Chapter13 공통 scene, HDR post-process와 UI 구조를 유지한다.
- 일반 이론은 [Percentage Closer Filtering And PCSS](../../Docs/01_Topics/Shadows/PercentageCloserFilteringAndPCSS.md)로, build/run/capture 사실은 Verification으로 위임한다.

## 핵심 코드

- [Depth comparison sample 평균 기반 PCF](./BasicPS.hlsl#L215-L275)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Capture | 완료 | 전체 application window |

## Capture/Result

![Chapter13 Step5 SoftShadowPCF](../../Docs/_assets/captures/part3_chapter13_05_soft_shadow_pcf_ui_left.png)

원본 runtime asset은 직접 연결하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/13_05_SoftShadowPCF.md)
- [Percentage Closer Filtering And PCSS](../../Docs/01_Topics/Shadows/PercentageCloserFilteringAndPCSS.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
