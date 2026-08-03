# Rim Lighting

## 목적

Rim lighting은 view direction과 surface normal의 관계를 사용해 object silhouette을 강조하는 stylized shading 기법이다.

## 책임 범위

- Normal·view angle에서 rim mask를 만드는 일반 원리를 설명한다.
- Chapter08 Step1의 shader와 UI 구현은 Example README로 위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`의 [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)으로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos`의 [상세 Demo](../../03_Demos/Part2_Chapter05-08/08_01_RimLighting.md)로 위임한다.

## 핵심 개념

### Normal과 view direction

정규화된 surface normal `N`과 surface에서 eye로 향하는 direction `V`의 dot product는 camera를 정면으로 향할수록 1에 가깝고 silhouette에 가까울수록 0에 가까워진다. `1 - saturate(dot(N, V))`를 사용하면 이 관계를 rim mask로 뒤집을 수 있다.

### Rim shaping

Power exponent는 rim의 폭과 집중도를 조절한다. Exponent가 커질수록 silhouette에 가까운 영역으로 좁아진다. Smoothstep은 threshold 구간을 부드럽게 연결하는 대안이며, 원하는 미술 방향에 맞춰 color와 strength를 함께 조절한다.

```cpp
// Pseudo C++: normal과 view angle에서 rim contribution 계산
ComputeRim(normal, toEye, color, power, strength)
{
    base = 1.0 - Saturate(Dot(normal, toEye));
    mask = Pow(Max(base, Epsilon), Max(power, 0.0));
    return mask * color * strength;
}
```

### Fresnel과의 차이

Rim lighting은 Fresnel과 유사한 grazing-angle 강조 형태를 사용할 수 있지만, 실제 반사율이나 material의 index of refraction을 계산하지 않는다. 물리 기반 Fresnel은 Chapter08 Step5에서 별도로 다룬다.

## 한계

- 잘못된 normal transform은 rim 위치와 두께를 왜곡한다.
- 과도한 strength는 base shading과 surface detail을 가린다.
- Screen-space outline이나 geometry silhouette expansion과는 다른 기법이다.

## 관련 문서

- [Chapter08 Step1 RimLighting Example](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/README.md)
- [Chapter08 Step1 RimLighting Demo](../../03_Demos/Part2_Chapter05-08/08_01_RimLighting.md)
- [Phong And Blinn-Phong](PhongAndBlinnPhong.md)
