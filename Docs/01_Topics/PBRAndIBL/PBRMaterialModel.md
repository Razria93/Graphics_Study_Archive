# PBR Material Model

## 목적

Metallic-roughness material에서 diffuse와 specular energy를 나누고 direct light와 IBL을 결합하는 기준을 정의한다.

## 책임 범위

- 개별 shader 구현은 Example README와 상세 Demo로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Fresnel과 material base reflectance

Dielectric은 낮은 고정 F0를 사용하고 metal은 base color를 F0로 사용한다. Schlick approximation은 view와 half vector의 각도에 따른 반사율을 계산한다.

### Microfacet BRDF

GGX normal distribution, geometry attenuation과 Fresnel term을 결합한다. Specular BRDF의 denominator는 light와 view cosine이 0에 가까울 때 수치적으로 보호한다.

### Direct light와 IBL

Direct light는 analytic light의 radiance를 BRDF로 평가한다. IBL은 irradiance cube, prefiltered specular cube와 BRDF LUT로 주변 조명을 근사한다.

## 한계

- Material layering, clear coat와 anisotropy는 다루지 않는다.
- Asset별 texture packing 규칙은 Metallic Roughness Workflow에서 설명한다.

## 관련 문서

- [Chapter12 Step1 Example README](../../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/README.md)
- [Metallic Roughness Workflow](MetallicRoughnessWorkflow.md)
- [Image Based Lighting](../LightingAndShading/ImageBasedLighting.md)
- [Fresnel Reflectance](../LightingAndShading/FresnelReflectance.md)
- [Docs/03_Demos Step1](../../03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
