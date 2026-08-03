# Chapter11 Step4 HDRI

## Overview

EXR의 floating-point HDR image를 읽고 exposure와 gamma 변환을 적용해 LDR display에 표시한다. Load 실패를 빈 image로 계속 사용하지 않고 명시적 오류로 중단한다.

## 실행 진입점

- Solution: `11_TexturingTechniques_Step4_HDRI.sln`
- Application entry: `main.cpp`
- 주요 source: `ExampleApp.cpp`, `D3D11Utils.cpp`
- Shader: `BasicPixelShader.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [D3D11Utils.cpp](D3D11Utils.cpp#L223-L249) | EXR metadata·pixel load와 실패 전파 |
| [ExampleApp.cpp](ExampleApp.cpp#L136-L159) | HDRI input과 textured ground 구성 |
| [BasicPixelShader.hlsl](BasicPixelShader.hlsl#L61-L78) | exposure와 gamma 변환 |

## Capture/Result

![Chapter11 Step4 HDRI](../../Docs/_assets/captures/part3_chapter11_04_hdri.png)

Exposure 1.0과 gamma 1.0에서 EXR panorama의 넓은 luminance 범위를 display 결과로 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-04 현재 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD, DirectXTex·OpenEXR runtime 필요 |
| Capture/Result | 완료 | 전체 창 1282×752 PNG |

## Limitations

- Filmic tone mapping operator 비교는 포함하지 않는다.
- EXR 원본은 runtime dependency로만 사용하고 rendered evidence만 공개 후보로 둔다.

## Related Docs

- [HDR Rendering Pipeline](../../Docs/01_Topics/TexturingAndMapping/HDRRenderingPipeline.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/11_04_HDRI.md)
- [이전 단계](../11_TexturingTechniques_Step3_HeightMapping/README.md)
- [다음 단계](../11_TexturingTechniques_Step5_HDRPipeline/README.md)
