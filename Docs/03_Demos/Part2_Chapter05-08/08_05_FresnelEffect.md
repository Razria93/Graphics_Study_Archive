# Chapter08 Step5 FresnelEffect Demo

## 목적

Step4의 image based lighting에 Schlick Fresnel factor를 결합해 sphere를 바라보는 각도에 따라 environment reflection 기여가 달라지는 결과를 보여준다.

## 책임 범위

- Step4 대비 추가된 Fresnel 계산과 specular 결합을 설명한다.
- 일반 Fresnel 이론은 [Fresnel Reflectance](../../01_Topics/LightingAndShading/FresnelReflectance.md)로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

![Chapter08 Step5 FresnelEffect](../../_assets/captures/part2_chapter08_05_fresnel_effect.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Sphere normal, view direction, Stonewall diffuse/specular cubemap, material `fresnelR0` |
| 처리 | IBL sampling, Schlick approximation, angle-dependent specular weighting |
| 출력 | 정면과 silhouette의 반사 비율이 다른 environment-lit sphere |

## 구현 흐름

```text
Surface normal + eye direction
→ saturate(N·V)
→ Schlick Fresnel factor
→ environment specular sample weighting
→ diffuse와 합성
```

## 핵심 구현

### Schlick approximation

`1 - saturate(N·V)`의 5제곱으로 grazing angle에서 1에 접근하는 Fresnel factor를 만든다.

```cpp
// Pseudo C++: angle-dependent reflectance
ComputeFresnel(fresnelR0, normal, toEye)
{
    oneMinusCos = 1.0 - Saturate(Dot(normal, toEye));
    return fresnelR0 + (1.0 - fresnelR0) * Pow(oneMinusCos, 5.0);
}
```

- [Schlick Fresnel factor 계산](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/BasicPixelShader.hlsl#L28-L42)

### Environment specular 결합

Reflection direction으로 sampling한 specular cubemap에 material Fresnel factor를 곱한다.

- [Diffuse·specular cubemap과 Fresnel 결합](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/BasicPixelShader.hlsl#L77-L88)
- [FresnelR0 UI 조절](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/ExampleApp.cpp#L407-L409)

## 시각 결과

Stonewall environment가 sphere에 반사되며 view angle과 `fresnelR0`에 따라 specular contribution이 조절된다. UI와 sphere를 한 frame에 두어 material parameter와 결과의 관계를 확인한다.

## 구현 범위와 한계

- Schlick approximation을 사용한다.
- Roughness mip LOD와 split-sum BRDF는 포함하지 않는다.
- Active asset 원본은 비공개로 유지하고 직접 실행한 rendered evidence만 공개한다.
- Video는 정지 이미지가 구현 결과를 충분히 보여주므로 제외한다.

## 검증

- Debug/Release x64 Clean/Rebuild와 run 성공
- Assimp runtime DLL 배치 후 Debug/Release smoke run 성공
- Resize·minimize/restore 정상
- 1282×992 전체 창 PNG 확보
- PNG decode, metadata와 공개 안전성 확인

## 관련 코드

- [Stonewall cubemap 초기화](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/ExampleApp.cpp#L18-L42)
- [Sphere geometry 구성](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/ExampleApp.cpp#L119-L120)
- [Schlick Fresnel shading](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/BasicPixelShader.hlsl#L28-L88)

## 관련 문서

- [Chapter08 Step5 FresnelEffect Example](../../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/README.md)
- [이전 단계: Chapter08 Step4 ImageBasedLighting Demo](08_04_ImageBasedLighting.md)
- [다음 단계: Chapter08 Step6 BloomEffect](08_06_BloomEffect.md)
- [Fresnel Reflectance](../../01_Topics/LightingAndShading/FresnelReflectance.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
