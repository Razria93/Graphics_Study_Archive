# Chapter08 Step4 ImageBasedLighting

## 목적

Diffuse irradiance와 specular environment cubemap을 surface lighting 입력으로 사용한다.

## 구현 요약

- Atrium diffuse/specular IBL DDS를 texture-cube SRV로 로드한다.
- Normal direction으로 diffuse cubemap을, reflection direction으로 specular cubemap을 sampling한다.
- Material diffuse·specular·shininess parameter로 두 기여도를 조절한다.
- Scalar shininess 계산과 `pow` 입력 범위를 명시해 HLSL warning을 제거한다.

일반 이론은 [Image Based Lighting](../../Docs/01_Topics/LightingAndShading/ImageBasedLighting.md)으로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug/Release x64 build/run | 성공 | Clean/Rebuild와 DirectXTK runtime 확인 |
| Resize | 성공 | minimize/restore 포함 |
| Capture | 확보 | Atrium 환경과 IBL sphere 확인 |

## Capture/Result

![Chapter08 Step4 ImageBasedLighting](../../Docs/_assets/captures/part2_chapter08_04_image_based_lighting.png)

## 핵심 코드

- [Diffuse·specular IBL cubemap load](ExampleApp.cpp#L24-L41)
- [IBL sampling과 material weight](BasicPixelShader.hlsl#L50-L64)
- [Cubemap resource binding](ExampleApp.cpp#L356-L421)

## 범위와 한계

- Roughness 기반 mip LOD와 BRDF integration은 구현하지 않는다.
- Atrium cubemap과 `ojwD8.jpg`의 공개 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 둔다.
- 정적 비교가 충분해 video는 제외한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/08_04_ImageBasedLighting.md)
- [Image Based Lighting](../../Docs/01_Topics/LightingAndShading/ImageBasedLighting.md)
- [Verification](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [이전 단계: Step3 EnvironmentMapping](../08_ShaderToys_Step3_EnvironmentMapping/README.md)
- 다음 단계: Step5 FresnelEffect
