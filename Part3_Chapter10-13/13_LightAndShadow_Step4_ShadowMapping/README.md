# Chapter13 Step4 ShadowMapping

Light-space depth 비교로 hard shadow를 만든다.

## 구현 요약

- Camera depth와 별개로 light depth map과 shadow coordinate를 추가한다.
- Chapter13 공통 scene, HDR post-process와 UI 구조를 유지한다.
- 일반 이론은 [Shadow Mapping And Depth Bias](../../Docs/01_Topics/Shadows/ShadowMappingAndDepthBias.md)로, build/run/capture 사실은 Verification으로 위임한다.

## 핵심 코드

- [Light-space depth 비교 기반 hard shadow](./BasicPS.hlsl#L158-L180)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Capture | 완료 | 전체 application window |

## Capture/Result

![Chapter13 Step4 ShadowMapping](../../Docs/_assets/captures/part3_chapter13_04_shadow_mapping.png)

원본 runtime asset은 직접 연결하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/13_04_ShadowMapping.md)
- [Shadow Mapping And Depth Bias](../../Docs/01_Topics/Shadows/ShadowMappingAndDepthBias.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
