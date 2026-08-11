# Intersection

## 목적

Ray와 sphere 또는 triangle의 교차를 판정하고 유효한 hit distance를 선택하는 개념을 설명한다. Step4의 sphere drawing과 Step7의 triangle 결과가 어떤 기하 판정에서 나오는지 이해하기 위한 개념 정본으로 사용한다.

## 책임 범위

이 문서는 ray-sphere intersection의 root 선택과 ray-triangle intersection의 plane·내부 판정을 다룬다. Step4와 Step7의 구체적인 class와 함수는 Example README로, build/run/capture 사실은 Verification으로, 구현 선택과 시각 결과는 상세 Demo로 위임한다.

## 개념 흐름

Sphere는 ray의 parametric 식을 implicit equation에 대입해 quadratic root를 구한다. Triangle은 vertex winding으로 plane normal을 정하고 ray-plane 교차점을 구한 뒤 세 edge의 안쪽에 있는지 확인한다. 두 경우 모두 origin 앞쪽의 유효한 hit distance를 closest-hit 후보로 사용한다.

## 핵심 개념

### Discriminant

중심 `c`, 반지름 `r`인 sphere와 ray `p(t) = o + t d`의 관계는 다음 식으로 정리한다.

```text
|o + t d - c|² = r²
```

이를 `a t² + b t + c = 0` 형태로 전개한다. Discriminant가 음수이면 real root가 없으므로 ray는 sphere를 지나지 않는다. 0이면 접하고, 양수이면 두 교점 후보가 생긴다.

### Valid Hit Distance

교점 후보가 있더라도 `t`가 음수이면 ray 진행 방향의 뒤쪽에 있다. 두 root 중 가장 가까운 양수 값을 선택하면 origin 앞에서 처음 만나는 표면을 얻는다.

선택한 `t`로 hit point를 계산하고, sphere center에서 hit point로 향하는 vector를 normalize해 surface normal을 구한다. Step4는 이 hit 정보와 distance를 lighting 대신 diagnostic color에 사용한다.

### Triangle Plane And Winding

Triangle vertex `v0`, `v1`, `v2`의 winding은 다음 face normal 방향을 결정한다.

```text
n = normalize((v1 - v0) × (v2 - v0))
```

Single-sided triangle은 ray 방향과 normal의 관계로 back face를 제거할 수 있다. Ray와 plane이 평행하지 않으면 plane equation으로 `t`를 구하고 `t >= 0`인 교차점만 유지한다.

### Edge Half-Space Test

Plane 교차점이 triangle 내부에 있는지는 세 directed edge와 교차점 vector의 cross product가 face normal과 같은 방향을 향하는지 검사해 판정할 수 있다. 모든 edge test를 통과한 점만 triangle hit로 사용한다.

이 방식은 barycentric coordinate를 계산하지 않아도 내부 판정이 가능하지만 vertex attribute interpolation 값은 제공하지 않는다. Weight 계산과 attribute interpolation은 [Barycentric Coordinates](BarycentricCoordinates.md)에서 다룬다. Degenerate triangle, edge 위의 zero-length vector와 epsilon 선택은 별도 numerical robustness가 필요하다.

## 데모 연결

Step4 Demo는 sphere의 miss, 접선 또는 일반 hit를 diagnostic 결과로 표시한다. Step7 Demo는 triangle의 winding, plane 교차와 edge half-space 판정이 만드는 직선 경계와 flat normal shading을 보여준다. Step9 Demo는 같은 hit point에 barycentric weight를 추가해 vertex color를 보간한다. 실제 계산과 결과 변환은 연결된 source에서 확인한다.

## 한계

- Möller–Trumbore 알고리즘과 barycentric attribute interpolation의 상세는 다루지 않는다.
- acceleration structure와 다중 object closest-hit 탐색은 포함하지 않는다.
- numerical robustness와 scene scale별 epsilon 정책은 다루지 않는다.

## 관련 문서

- Example: [Step4 DrawingSphere README](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md)
- Example: [Step7 Triangle README](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/README.md)
- Example: [Step9 Barycentric Coordinates README](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/03_04_DrawingSphere.md`](../../03_Demos/Part1_Chapter03/03_04_DrawingSphere.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/03_07_Triangle.md`](../../03_Demos/Part1_Chapter03/03_07_Triangle.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/03_09_BarycentricCoordinates.md`](../../03_Demos/Part1_Chapter03/03_09_BarycentricCoordinates.md)
- Related Topic: [Ray](Ray.md)
- Related Topic: [Barycentric Coordinates](BarycentricCoordinates.md)
