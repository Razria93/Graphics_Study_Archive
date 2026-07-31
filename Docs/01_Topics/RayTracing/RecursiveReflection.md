# Recursive Reflection

## 목적

Surface hit에서 reflected direction을 계산하고 secondary ray를 재귀 추적해 local shading과 reflected scene color를 결합하는 기본 원리를 설명한다.

## 책임 범위

- Reflection vector, recursive secondary ray, depth termination, origin bias와 color weight의 일반 개념을 다룬다.
- Step12의 scene, 함수 구조와 DirectX11 표시 경로는 [Step12 Example README](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/README.md)와 [상세 Demo](../../03_Demos/Part1_Chapter03/12_Reflection.md)로 위임한다.
- Phong specular highlight에 사용하는 light reflection vector는 [Phong Shading](../LightingAndShading/PhongShading.md)으로 위임한다.
- 실제 build/run/capture 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 핵심 개념

### Reflection vector

Ray의 진행 방향을 `D`, normalized surface normal을 `N`이라고 하면 reflected direction은 `R = D - 2 dot(D, N) N`으로 계산한다. `D`가 surface를 향하는 방향이라는 규약을 먼저 고정해야 부호를 일관되게 사용할 수 있다.

### Secondary ray와 origin bias

Reflection은 primary hit point에서 `R` 방향의 secondary ray를 만든다. Floating-point 오차로 새 ray가 같은 surface를 즉시 다시 hit하지 않도록 origin을 작은 epsilon만큼 옮긴다. Normal 방향 offset과 ray 방향 offset은 grazing angle과 surface orientation에서 서로 다른 수치 특성을 가지므로 구현 규약을 명시한다.

### Recursive trace와 종료

Secondary ray도 closest hit, shading과 추가 reflection을 반복할 수 있다. 무한 재귀를 막기 위해 depth budget, contribution threshold 또는 ray miss를 종료 조건으로 사용한다. 고정 depth는 결과와 비용을 예측하기 쉽지만 작은 contribution도 같은 횟수만큼 추적한다.

### Local color와 reflected color

Material reflection weight를 `k`라고 하면 단순한 결합은 `local × (1 - k) + reflected × k`로 표현할 수 있다. 여러 transport 항을 함께 사용할 때 weight 합을 제한하면 과도한 밝기를 줄일 수 있지만, 이 선형 결합만으로 Fresnel이나 physically based energy conservation을 보장하지는 않는다.

## 한계

- 이 문서는 refraction, transparency와 total internal reflection을 다루지 않는다.
- Fresnel, rough reflection, microfacet BRDF와 importance sampling을 다루지 않는다.
- 고정 epsilon과 depth가 모든 scene scale과 viewing angle에 적합하다고 가정하지 않는다.
- Step12는 miss와 depth 종료에서 black을 반환하는 단순 사례다.

## 관련 문서

- Example: [Step12 Reflection README](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/12_Reflection.md`](../../03_Demos/Part1_Chapter03/12_Reflection.md)
- Related Topic: [Ray](Ray.md)
- Related Topic: [Intersection](Intersection.md)
- Related Topic: [Phong Shading](../LightingAndShading/PhongShading.md)
