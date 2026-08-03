# Chapter13 Step2B Shadow Prototype

독립 DepthPass와 MainPass로 array shadow prototype을 구성한다.

## 구현 요약

- 주 PSO 계보와 별개인 실험 branch를 Step2B로 표시한다.
- Chapter13 공통 scene, HDR post-process와 UI 구조를 유지한다.
- 일반 이론은 Topic으로, build/run/capture 사실은 Verification으로 위임한다.

## 핵심 코드

- [독립 DepthPass와 MainPass 기반 array shadow prototype](./ExampleApp.cpp#L503-L571)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Capture | 완료 | 전체 application window |

## Capture/Result

![Chapter13 Step2B Shadow Prototype](../../Docs/_assets/captures/part3_chapter13_02b_shadow_prototype.png)

원본 runtime asset은 직접 연결하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/13_02B_ShadowPrototype.md)
- [Topic](../../Docs/01_Topics/Shadows/ShadowMappingAndDepthBias.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
