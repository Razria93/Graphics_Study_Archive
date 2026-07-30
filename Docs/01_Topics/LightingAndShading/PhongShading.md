# Phong Shading

## 목적

Surface normal, light direction과 view direction으로 ambient, diffuse와 specular
항을 구성하는 Phong shading의 기본 원리를 설명한다. 여러 예제에서 반복되는
lighting 이론을 하나의 개념 정본으로 제공한다.

## 책임 범위

이 문서는 reflection vector 기반 Phong shading과 각 항의 의미를 설명한다. 특정
예제의 API와 parameter 값은 Example README로 위임하고, 구현 흐름과 capture
해석은 `Docs/03_Demos`로 위임한다. Build/run/capture 사실은
`Docs/02_Verification`으로 위임한다.

## 핵심 개념

### Ambient And Diffuse

Ambient 항은 직접 조명 계산과 무관하게 surface에 남기는 기본 밝기다. 단순한
모델에서는 material의 ambient color를 그대로 사용한다.

Diffuse 항은 surface normal `N`과 light 방향 `L`의 cosine 관계를 사용한다.

```text
diffuse = max(dot(N, L), 0)
```

두 vector가 같은 방향에 가까울수록 surface가 밝아지고, light가 surface 뒤에
있으면 음수를 0으로 제한한다.

### Reflection-Vector Specular

Phong specular는 light vector를 normal 기준으로 반사한 vector `R`과 view 방향
`V`가 가까운 정도를 사용한다.

```text
R = normalize(2 * dot(N, L) * N - L)
specular = pow(max(dot(R, V), 0), shininess)
```

`shininess`가 커지면 highlight가 좁아지고, specular coefficient와 color는 최종
highlight의 세기와 색을 조절한다. Blinn-Phong은 reflection vector 대신
half-vector를 사용하므로 별도의 shading model이다.

### Lighting Composition

단순 Phong lighting은 세 항을 합성한다.

```text
color =
    ambientColor
    + diffuseColor * diffuse
    + specularColor * specular * specularCoefficient
```

출력 범위를 제한하는 clamp는 display 가능한 값을 만들지만, 합산 값이 큰 영역의
detail을 잃을 수 있다. Linear color space, gamma correction, tone mapping과 light
attenuation은 별도의 확장 문제다.

## 한계

- Shadow와 visibility를 포함하지 않는다.
- Physically based energy conservation을 보장하지 않는다.
- Light attenuation, gamma correction과 tone mapping은 별도 개념으로 다룬다.
- Blinn-Phong과의 구현 비교는 이 문서의 핵심 범위에 포함하지 않는다.

## 관련 문서

- Example: [Step5 PhongShading README](../../../Part1_Chapter03/03_Raytracing_Step5_PhongShading/README.md)
- Verification: [Part1 Chapter03 Verification](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [Step5 PhongShading Demo](../../03_Demos/Part1_Chapter03/05_PhongShading.md)
- Related Topic: [Ray](../RayTracing/Ray.md)
- Related Topic: [Intersection](../RayTracing/Intersection.md)
