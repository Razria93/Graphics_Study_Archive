# Chapter11 Step5 HDRPipeline

## Overview

Floating-point scene buffer를 resolve한 뒤 bloom downsample·upsample과 exposure·gamma composite를 거쳐 back buffer에 표시하는 HDR post-process chain을 구성한다. 기본 bloom strength는 0.2로 둔다.

## 실행 진입점

- Solution: `11_TexturingTechniques_Step5_HDRPipeline.sln`
- Application entry: `main.cpp`
- 주요 source: `ExampleApp.cpp`, `PostProcess.cpp`, `ImageFilter.cpp`
- Shader: `BloomDownPS.hlsl`, `BloomUpPS.hlsl`, `CombinePS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [ExampleApp.cpp](ExampleApp.cpp#L439-L452) | HDR buffer resolve와 post-process 호출 |
| [PostProcess.cpp](PostProcess.cpp#L70-L118) | bloom pyramid와 combine filter 구성 |
| [PostProcess.cpp](PostProcess.cpp#L120-L153) | downsample·upsample·combine 실행 순서 |
| [CombinePS.hlsl](CombinePS.hlsl#L45-L65) | bloom composite, exposure와 gamma 변환 |

## Capture/Result

![Chapter11 Step5 HDRPipeline](../../Docs/_assets/captures/part3_chapter11_05_hdr_pipeline.png)

밝은 창과 태양 주변에서 bloom이 확산되고 exposure 1.0·gamma 2.2가 최종 display mapping에 적용된다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-04 현재 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD, DirectXTex·OpenEXR runtime 필요 |
| Capture/Result | 완료 | 전체 창 1282×752 PNG |

## Limitations

- Auto exposure, temporal adaptation과 color grading은 포함하지 않는다.
- HDRI와 surface texture 원본은 직접 공개하지 않고 rendered evidence만 사용한다.

## Related Docs

- [HDR Rendering Pipeline](../../Docs/01_Topics/TexturingAndMapping/HDRRenderingPipeline.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md)
- [이전 단계](../11_TexturingTechniques_Step4_HDRI/README.md)
- 다음 Chapter: `12_PBR_Step1_UnrealPBR`
