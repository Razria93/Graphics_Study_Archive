# Fresnel Reflectance

## 목적

Fresnel reflectance는 surface를 바라보는 각도에 따라 반사 비율이 달라지는 현상과 Schlick approximation의 역할을 설명한다.

## 책임 범위

- Normal과 view direction의 각도에 따른 reflectance 변화를 설명한다.
- `fresnelR0`와 grazing-angle reflectance의 의미를 구분한다.
- Chapter08 Step5 구현은 [Example README](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/README.md)로 위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos`의 [상세 Demo](../../03_Demos/Part2_Chapter05-08/08_05_FresnelEffect.md)로 위임한다.

## 핵심 개념

### Normal incidence와 grazing angle

Surface를 정면에서 바라볼 때 reflectance는 material의 기본 반사율 `R0`에 가깝다. View direction이 surface tangent에 가까워질수록 reflectance는 1에 접근한다.

### Schlick approximation

Schlick approximation은 `R0 + (1 - R0)(1 - N·V)^5` 형태로 angle-dependent reflectance를 근사한다. `N`과 `V`는 정규화하고 dot product는 유효 범위로 제한한다.

### IBL과의 결합

Environment specular sample에 Fresnel factor를 곱하면 sphere 중심과 silhouette 부근의 반사 기여가 다르게 나타난다. Step5는 Step4의 diffuse/specular cubemap 경로에 이 각도 의존 가중치를 추가한다.

## 한계

- Schlick approximation은 정확한 Fresnel equation의 근사다.
- Step5는 roughness 기반 prefiltered mip LOD와 split-sum BRDF를 구현하지 않는다.
- Dielectric과 conductor의 복소 굴절률 계산은 범위에 포함하지 않는다.

## 관련 문서

- [Image Based Lighting](ImageBasedLighting.md)
- [Chapter08 Step5 Example](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/README.md)
- [Chapter08 Step5 상세 Demo](../../03_Demos/Part2_Chapter05-08/08_05_FresnelEffect.md)
