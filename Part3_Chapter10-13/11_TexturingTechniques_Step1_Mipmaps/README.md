# Chapter11 Step1 Mipmaps

## Overview

Pixel shader가 명시적인 mip level을 선택해 texture의 축소 단계가 화면 결과에 미치는 영향을 확인한다. 기본값은 level 3으로 두어 level 0과 구분되는 filtering 결과를 즉시 판독할 수 있게 한다.

## 실행 진입점

- Solution: `11_TexturingTechniques_Step1_Mipmaps.sln`
- Application entry: `main.cpp`
- 주요 source: `ExampleApp.cpp`, `BasicMeshGroup.cpp`
- Shader: `BasicPixelShader.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [ExampleApp.cpp](ExampleApp.cpp#L61-L78) | sphere texture와 기본 mip level 설정 |
| [ExampleApp.cpp](ExampleApp.cpp#L461-L473) | mip level UI |
| [BasicPixelShader.hlsl](BasicPixelShader.hlsl#L95-L103) | `SampleLevel` 기반 명시적 mip 선택 |

## Capture/Result

![Chapter11 Step1 Mipmaps](../../Docs/_assets/captures/part3_chapter11_01_mipmaps.png)

Level 3을 선택한 sphere에서 고해상도 원본보다 완화된 texture detail을 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-04 현재 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD, `DirectXTK.dll` 필요 |
| Capture/Result | 완료 | 전체 창 1282×752 PNG |

## Limitations

- 자동 LOD 선택이나 trilinear·anisotropic filtering 비교는 포함하지 않는다.
- 외부 texture 원본은 runtime dependency로만 사용하고 rendered evidence만 공개 후보로 둔다.

## Related Docs

- [Texture Sampling](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/11_01_Mipmaps.md)
- [다음 단계](../11_TexturingTechniques_Step2_NormalMapping/README.md)
