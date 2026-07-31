# Triangle Rasterization

## 목적

Triangle rasterization은 세 vertex가 정의하는 연속 영역을 raster pixel 표본으로 변환하고 vertex attribute를 내부 pixel로 보간하는 과정을 설명한다. 특정 예제의 API 호출보다 edge function, bounding box와 barycentric coordinate의 공통 원리를 다룬다.

## 책임 범위

- world 또는 NDC 좌표를 raster 좌표로 옮긴 뒤 triangle coverage를 판정하는 기초를 설명한다.
- signed edge function과 winding의 관계를 설명한다.
- bounding box traversal과 barycentric interpolation을 설명한다.
- Step1과 Step1A의 실제 함수와 상수는 [Step1 Triangle Example](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md)과 [Step1A Triangle To Circle Example](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 핵심 개념

### Raster 좌표와 Pixel 표본

Vertex를 raster 좌표로 변환하면 화면의 각 pixel을 같은 좌표계에서 검사할 수 있다. Pixel center를 표본 위치로 사용할 경우 좌표 변환과 edge 판정에서 같은 convention을 유지해야 경계가 반 pixel만큼 밀리는 문제를 줄일 수 있다.

### Edge Function과 Winding

두 vertex가 만드는 directed edge와 검사점 사이의 2D cross product 부호는 점이 edge의 어느 쪽에 있는지 나타낸다. 세 edge 값의 부호가 winding과 일관되면 점을 triangle 내부로 판정할 수 있다. Vertex 순서를 반대로 바꾸면 signed area와 edge 값의 부호도 함께 바뀌므로 inside test는 winding convention을 명시해야 한다.

### Bounding Box Traversal

전체 framebuffer를 검사하는 대신 세 raster vertex의 최소·최대 좌표로 axis-aligned bounding box를 만든다. 화면 범위로 clamp한 box 내부만 순회하면 coverage 후보를 줄일 수 있지만 box 안의 모든 pixel이 triangle에 포함되는 것은 아니므로 edge test가 계속 필요하다.

### Barycentric Interpolation

세 edge 값 또는 부분 triangle area를 전체 signed area로 나누면 barycentric weight를 얻는다. 내부 점에서는 세 weight의 합이 1이 되며 각 vertex color, UV와 normal 같은 attribute를 같은 위치로 보간할 수 있다. Perspective projection 이후의 attribute에는 perspective-correct interpolation이 별도로 필요하다.

### Triangle Fan과 Polygonal Circle Approximation

하나의 center vertex와 원주를 나눈 boundary vertex 쌍으로 triangle을 반복하면 fan 형태의 polygon을 만들 수 있다. Segment 수가 증가할수록 boundary edge가 짧아져 circle에 가까워지지만 geometry 수와 rasterization 작업량도 함께 증가한다. Shared vertex와 index를 사용할 수도 있고 각 triangle을 독립 객체로 저장할 수도 있으며, 두 방식은 같은 silhouette를 만들더라도 메모리 구성과 갱신 책임이 다르다.

## 처리 단계

```text
vertex position
→ raster coordinate
→ triangle bounding box
→ pixel coverage test
→ barycentric weight
→ vertex attribute interpolation
→ framebuffer write
```

## 한계

- 이 문서는 clipping, multisampling과 subpixel precision 규칙을 상세히 다루지 않는다.
- Depth test, backface culling과 perspective-correct interpolation은 후속 단계의 별도 책임으로 둔다.
- Shared edge에서 중복 또는 누락을 피하는 top-left rule은 현재 Step1 구현 범위에 포함하지 않는다.

## 관련 문서

- [Step1 Triangle Example](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md)
- [Step1A Triangle To Circle Example](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md)
- Demo: [`Docs/03_Demos/Part2_Chapter04/01_Triangle.md`](../../03_Demos/Part2_Chapter04/01_Triangle.md)
- Demo: [`Docs/03_Demos/Part2_Chapter04/01_TriangleToCircle.md`](../../03_Demos/Part2_Chapter04/01_TriangleToCircle.md)
- Verification: [`Docs/02_Verification/Part2_Chapter04/verification-index.md`](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Rasterization Topic Index](topic-index.md)
