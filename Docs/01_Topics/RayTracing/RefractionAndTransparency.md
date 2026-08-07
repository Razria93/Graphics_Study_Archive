# Refraction And Transparency

## 목적

Ray가 서로 다른 refractive index를 가진 매질 경계를 통과할 때 방향이 바뀌는 원리와, refracted secondary ray를 transparency color에 결합하는 기본 구조를 설명한다.

## 책임 범위

- Snell’s law, IOR ratio, enter/exit normal 전환, total internal reflection과 transparency weight의 일반 개념을 다룬다.
- Reflection vector와 reflected secondary ray는 [Recursive Reflection](RecursiveReflection.md)으로 위임한다.
- Step13의 scene, 함수 구조와 DirectX11 표시 경로는 [Step13 Example README](../../../Part1_Chapter03/03_Raytracing_Step13_Transparency/README.md)와 [상세 Demo](../../03_Demos/Part1_Chapter03/03_13_Transparency.md)로 위임한다.
- 실제 build/run/capture 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 핵심 개념

### Snell’s law와 IOR ratio

두 매질의 refractive index를 `n1`, `n2`라고 하면 입사각과 굴절각은 `n1 sin(theta1) = n2 sin(theta2)`를 만족한다. Vector refraction 함수는 normalized incident direction, 경계 normal과 `eta = n1 / n2`를 사용해 transmitted direction을 계산한다.

### Enter와 exit 경계

Geometry normal이 항상 바깥쪽을 향한다면 incident direction과 normal의 dot product로 ray가 surface에 들어가는지 나오는지 구분할 수 있다. Enter에서는 outward normal과 외부/내부 IOR ratio를 사용하고, exit에서는 normal을 반전하고 내부/외부 ratio를 사용한다.

### Total internal reflection

높은 IOR 매질에서 낮은 IOR 매질로 나갈 때 transmitted direction이 존재하지 않는 각도가 생긴다. 이 경우 refraction 대신 reflected ray를 사용한다. 구현은 refraction discriminant를 직접 검사하거나 vector 함수가 반환한 invalid 또는 zero result를 판정할 수 있다.

### Transparency color 결합

단순한 transparency 모델은 local, reflected와 refracted contribution에 material weight를 곱해 더한다. Weight 합을 제한하면 과도한 밝기를 줄일 수 있지만, 고정 weight만으로 viewing angle에 따른 Fresnel reflectance나 physically based energy conservation을 표현하지는 못한다.

### Secondary ray와 재귀 종료

Refracted ray는 object 내부에서 exit surface를 다시 만나고 이후 다른 geometry로 진행할 수 있다. Floating-point self-intersection을 줄이기 위해 새 direction으로 origin을 조금 이동하며, depth budget이나 contribution threshold로 재귀를 종료한다.

## 한계

- 이 문서는 nested dielectric을 위한 medium stack과 geometry volume tracking을 다루지 않는다.
- Fresnel, absorption, rough transmission과 dispersion을 다루지 않는다.
- 고정 IOR와 epsilon이 모든 material과 scene scale에 적합하다고 가정하지 않는다.
- Step13은 air와 IOR 1.5 sphere 사이의 단일 dielectric 사례다.

## 관련 문서

- Example: [Step13 Transparency README](../../../Part1_Chapter03/03_Raytracing_Step13_Transparency/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/03_13_Transparency.md`](../../03_Demos/Part1_Chapter03/03_13_Transparency.md)
- Related Topic: [Recursive Reflection](RecursiveReflection.md)
- Related Topic: [Ray](Ray.md)
- Related Topic: [Intersection](Intersection.md)
