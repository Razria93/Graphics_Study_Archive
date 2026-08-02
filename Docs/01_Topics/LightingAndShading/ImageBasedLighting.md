# Image Based Lighting

## 목적

Image Based Lighting(IBL)은 scene 주변의 환경 영상을 조명 입력으로 사용하는
방식을 설명한다.

## 책임 범위

- Diffuse와 specular environment lighting의 역할을 구분한다.
- Cubemap 방향 sampling과 surface normal·view direction의 관계를 설명한다.
- Chapter08 Step4의 실제 구현은
  [Example README](../../../Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting/README.md)로
  위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`의
  [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로
  위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos`의
  [상세 Demo](../../03_Demos/Part2_Chapter05-08/08_04_ImageBasedLighting.md)로
  위임한다.

## 핵심 개념

### Diffuse environment lighting

Diffuse irradiance cubemap은 여러 방향에서 들어오는 입사광을 저주파 형태로
누적한다. Surface normal을 lookup 방향으로 사용하면 주변 환경이 제공하는 간접
diffuse contribution을 근사할 수 있다.

### Specular environment lighting

View direction과 surface normal로 계산한 reflection direction은 specular cubemap의
lookup 방향이 된다. 일반적인 physically based IBL은 roughness에 따라 prefiltered
mip level을 고르고 BRDF integration 결과를 함께 사용한다.

### Step4의 최소 IBL 경로

Chapter08 Step4는 미리 생성된 diffuse와 specular cubemap을 각각 한 번 sampling한
뒤 material weight와 결합한다. 이 구조는 environment lighting의 두 책임을
구분하지만 roughness 기반 적분 전체를 구현하지 않는다.

## 한계

- Roughness 기반 prefiltered mip LOD를 사용하지 않는다.
- Split-sum BRDF integration 또는 energy conservation을 구현하지 않는다.
- Cubemap 생성 과정과 asset 권리 판정은 Topic 책임에 포함하지 않는다.

## 관련 문서

- [Cubemap And Environment Mapping](../TexturingAndMapping/CubemapAndEnvironmentMapping.md)
- [Chapter08 Step4 Example](../../../Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting/README.md)
- [Chapter08 Step4 상세 Demo](../../03_Demos/Part2_Chapter05-08/08_04_ImageBasedLighting.md)
