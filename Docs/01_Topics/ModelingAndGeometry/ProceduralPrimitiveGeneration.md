# Procedural Primitive Generation

## 목적

Procedural primitive generation은 크기와 분할 수 같은 파라미터로 vertex attribute와 index topology를 계산해 mesh를 만드는 방식이다. 고정 vertex 배열을 복제하지 않고 동일한 생성 규칙을 Grid, cylinder와 sphere 같은 여러 primitive에 확장할 수 있다.

## 책임 범위

- Primitive 파라미터에서 vertex attribute와 index topology를 계산하는 일반 원리를 설명한다.
- 개별 DirectX11 resource 생성과 draw 호출은 각 Example README로 위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- 구현 흐름과 시각 자료는 `Docs/03_Demos`의 [Chapter07 Step3 Demo](../../03_Demos/Part2_Chapter05-08/07_03_Grid.md)와 [Chapter07 Step4 Demo](../../03_Demos/Part2_Chapter05-08/07_04_Cylinder.md)로 위임한다.

## 핵심 개념

### 파라미터와 샘플 수

가로 분할 수를 `slices`, 세로 분할 수를 `stacks`로 두면 Grid의 vertex 수는 `(slices + 1) × (stacks + 1)`이다. 인접 cell이 경계 vertex를 공유하므로 cell 수보다 한 줄씩 많은 vertex가 필요하다.

각 cell을 triangle 두 개로 나누면 index 수는 `6 × slices × stacks`가 된다. Chapter07 Step3의 5×3 Grid는 vertex 24개, cell 15개, triangle 30개와 index 90개를 만든다.

### Vertex attribute 생성

각 sample은 primitive의 파라미터 공간을 position, normal과 texture coordinate로 변환한다.

- Position: 폭과 높이를 분할 간격으로 나눈 실제 공간 좌표
- Normal: surface 방향을 나타내는 단위 vector
- Texture coordinate: 분할 위치를 0~1 범위로 정규화한 UV

Grid는 일정한 간격으로 sample하지만 cylinder와 sphere는 각도와 높이를 함께 사용한다. 생성식이 달라도 sample parameter에서 vertex attribute를 계산한다는 책임은 같다.

### Cell triangulation과 winding

사각 cell의 네 vertex를 두 triangle로 연결할 때 index 순서는 surface normal과 rasterizer의 front-face 규칙에 맞춰 일관되게 유지한다. 대각선 방향을 바꾸면 silhouette은 같아도 triangle topology와 attribute interpolation 경계가 달라질 수 있다.

### Buffer와 draw 책임

Geometry generator는 CPU-side vertex와 index 목록을 만든다. GPU buffer 생성, primitive topology binding과 draw call은 renderer가 담당한다. Normal line처럼 진단용 geometry가 필요하면 surface mesh와 별도 buffer·topology로 분리한다.

## 한계

- 이 문서는 생성 규칙과 자료 구조를 설명하며 개별 DirectX11 resource 호출은 Example README로 위임한다.
- 16-bit index를 사용하면 표현 가능한 vertex index 범위를 넘지 않도록 입력 범위를 제한해야 한다.
- Seam, pole 중복, tangent 생성과 subdivision은 primitive별 Example과 상세 Demo에서 다룬다.

## 관련 문서

- [Chapter07 Step3 Grid Example](../../../Part2_Chapter05-08/07_Modeling_Step3_Grid/README.md)
- [Chapter07 Step3 Grid Demo](../../03_Demos/Part2_Chapter05-08/07_03_Grid.md)
- [Chapter07 Step4 Cylinder Example](../../../Part2_Chapter05-08/07_Modeling_Step4_Cylinder/README.md)
- [Chapter07 Step4 Cylinder Demo](../../03_Demos/Part2_Chapter05-08/07_04_Cylinder.md)
- [Mesh Topology And Wireframe Rasterization](MeshTopologyAndWireframeRasterization.md)
- [Vertex And Face Normals](VertexAndFaceNormals.md)
