# Phong And Blinn-Phong

## 목적

Surface normal, light direction과 view direction으로 specular highlight를 계산할 때 Phong reflection vector와 Blinn half-vector가 어떤 기준을 사용하는지 비교한다. 두 모델이 공유하는 ambient와 Lambert diffuse 구성, shininess의 역할과 directional light 해석을 함께 설명한다.

## 책임 범위

이 문서는 Phong과 Blinn-Phong의 일반적인 vector 관계와 parameter 의미를 설명한다. 특정 예제의 함수, 상수와 UI는 Example README로 위임하고, 구현 흐름과 capture 해석은 `Docs/03_Demos`로 위임한다. Build/run/capture 사실은 `Docs/02_Verification`으로 위임한다.

## 핵심 개념

### Shared Ambient And Diffuse Terms

두 모델은 surface에 남기는 기본 밝기인 ambient 항과 normal `N`, surface-to-light direction `L`의 cosine을 사용하는 Lambert diffuse 항을 함께 사용할 수 있다.

```text
diffuse = max(dot(N, L), 0)
```

Directional light는 위치가 아니라 방향으로 정의한다. 구현이 light ray가 진행하는 방향을 보관하면 shading 계산에서는 그 반대 방향을 surface-to-light vector로 사용한다.

### Phong Reflection Vector

Phong specular는 light vector를 normal 기준으로 반사한 vector `R`과 surface-to-view direction `V`의 정렬 정도를 사용한다.

```text
R = normalize(2 * dot(N, L) * N - L)
phongSpecular = pow(max(dot(R, V), 0), shininess)
```

View 방향이 reflection vector에 가까울수록 highlight가 강해진다. Reflection vector 계산과 view 관계가 직접 드러나는 장점이 있다.

### Blinn Half Vector

Blinn-Phong specular는 light direction과 view direction 사이의 half-vector `H`를 만들고 normal과의 정렬 정도를 사용한다.

```text
H = normalize(L + V)
blinnSpecular = pow(max(dot(N, H), 0), shininess)
```

두 모델에 같은 shininess 값을 넣어도 highlight 폭과 세기가 동일하다고 가정하지 않는다. 구현마다 coefficient, clamp와 추가 weighting이 달라질 수 있으므로 parameter는 해당 모델의 결과를 기준으로 조정한다.

### Material And View Parameters

Material ambient, diffuse와 specular color는 각 light 항의 색과 세기를 조절한다. `kd`와 `ks` 같은 coefficient는 diffuse와 specular 기여도를 분리하고 shininess는 specular lobe의 집중도를 조절한다.

Normal, light direction과 view direction은 같은 좌표계에서 정규화해 비교한다. Object에 non-uniform scale이 있으면 normal을 position과 같은 방식으로 변환하지 않고 inverse-transpose normal matrix를 사용하는 것이 일반적이다.

## 한계

- Phong과 Blinn-Phong은 physically based energy conservation을 자동으로 보장하지 않는다.
- 같은 shininess 값은 두 모델에서 같은 highlight를 의미하지 않는다.
- Shadow, attenuation, gamma correction과 tone mapping은 별도 문제로 다룬다.
- Step9 Shading은 Blinn-Phong만 구현하며 두 모델을 runtime에서 직접 비교하지 않는다.
- Step9의 specular에 `N·L`을 추가로 곱하는 방식은 가능한 구현 variant이며 보편적인 유일한 식으로 일반화하지 않는다.

## 관련 문서

- Example: [Step9 Shading README](../../../Part2_Chapter04/04_Rasterization_Step9_Shading/README.md)
- Verification: [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- Demo: [Step9 Shading Demo](../../03_Demos/Part2_Chapter04/09_Shading.md)
- Related Topic: [Phong Shading](PhongShading.md)
- Related Topic: [Perspective Projection](../Rasterization/PerspectiveProjection.md)
