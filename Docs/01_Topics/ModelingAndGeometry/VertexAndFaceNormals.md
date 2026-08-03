# Vertex And Face Normals

## 목적

Mesh surface의 방향을 표현하는 vertex normal과 face normal의 책임을 구분하고, normal을 line geometry로 시각화할 때 필요한 변환을 정리한다.

## 책임 범위

- Normal vector의 의미와 surface position에서 diagnostic line을 만드는 방법을 설명한다.
- Chapter07 Step2와 Step7의 구현 차이는 각 Example README와 상세 Demo로 위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- 구현 흐름과 시각 자료는 `Docs/03_Demos`의 [Chapter07 Step2 Demo](../../03_Demos/Part2_Chapter05-08/07_02_DrawingNormals.md)와 [Chapter07 Step7 Demo](../../03_Demos/Part2_Chapter05-08/07_07_FaceNormals.md)로 위임한다.

## 핵심 개념

### Vertex normal과 face normal

Face normal은 triangle을 구성하는 두 edge의 cross product로 계산한 면 단위 방향이다. Vertex normal은 vertex에 저장되어 shading과 interpolation에 사용되는 방향이며, 여러 face가 vertex를 공유하면 주변 face normal을 조합해 만들 수 있다.

Face마다 vertex가 분리된 mesh에서는 같은 위치라도 서로 다른 normal을 가질 수 있다. 따라서 normal의 공유 방식은 surface가 매끈하게 보이는지 각져 보이는지를 결정한다.

Cross product의 operand 순서와 triangle winding은 face normal 방향을 함께 결정한다. Sphere처럼 중심이 알려진 convex surface에서는 face center 방향과 face normal의 dot product를 사용해 outward 또는 inward를 수치로 판정할 수 있다.

### Diagnostic line geometry

Normal은 위치가 아니라 방향이므로 화면에 직접 그릴 수 없다. Surface position `p`와 정규화된 normal `n`, 표시 길이 `s`를 사용해 `p`에서 `p + n * s`까지의 line segment를 만든다. Surface triangle과 분리된 vertex/index buffer를 `LINELIST`로 그리면 shading 경로와 독립적으로 normal 분포를 확인할 수 있다.

Line 시작점은 표현 목적에 따라 face center나 triangle vertex를 사용할 수 있다. Chapter07 Step7은 triangle-local 세 vertex에 같은 face normal을 복제하고 각 corner에서 평행한 line 세 개를 그린다.

면적이 0인 degenerate triangle은 cross product가 zero vector가 된다. 정규화와 diagnostic geometry 생성 전에 길이를 검사하거나, 길이 0 line으로 유지한다면 그 동작과 한계를 명시해야 한다.

### Normal transform

Model matrix에 non-uniform scale이 포함되면 position과 같은 방식으로 normal을 변환할 수 없다. Normal은 inverse-transpose matrix로 변환한 뒤 다시 정규화한다. Uniform scale이나 rotation만 사용하는 단순 예제에서도 이 규칙을 유지하면 이후 mesh 변형으로 확장하기 쉽다.

## 한계

- Normal line은 diagnostic 표현이며 실제 lighting 결과를 대신하지 않는다.
- Line 길이는 가독성을 위한 값이므로 geometry의 물리적 크기를 뜻하지 않는다.
- Tangent와 bitangent, normal mapping은 이 문서의 범위에 포함하지 않는다.

## 관련 문서

- [Mesh Topology And Wireframe Rasterization](MeshTopologyAndWireframeRasterization.md)
- [Chapter07 Step2 Example](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/README.md)
- [Chapter07 Step2 Demo](../../03_Demos/Part2_Chapter05-08/07_02_DrawingNormals.md)
- [Chapter07 Step7 Example](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/README.md)
- [Chapter07 Step7 Demo](../../03_Demos/Part2_Chapter05-08/07_07_FaceNormals.md)
