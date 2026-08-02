# Mesh Topology And Wireframe Rasterization

## 목적

Mesh의 vertex와 index가 primitive를 구성하는 방식과 DirectX11 rasterizer fill mode가 triangle의 내부 채움만 바꾸는 관계를 설명한다. Line geometry와 triangle wireframe을 구분해 같은 선 모양의 결과가 서로 다른 pipeline 입력에서 나올 수 있음을 정리한다.

## 책임 범위

- Indexed triangle mesh와 primitive topology의 관계를 설명한다.
- Solid와 wireframe rasterizer state의 차이를 설명한다.
- 명시적 line geometry와 triangle wireframe을 구분한다.
- 실제 구현은 [Chapter07 Step1 Example](../../../Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/README.md)로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- 시각 결과는 `Docs/03_Demos`의 [Chapter07 Step1 Demo](../../03_Demos/Part2_Chapter05-08/07_01_DrawingWireFrames.md)로 위임한다.

## 개념 흐름

1. Vertex buffer가 위치, normal과 UV 같은 vertex attribute를 제공한다.
2. Index buffer가 vertex를 재사용해 triangle 세 꼭짓점의 순서를 지정한다.
3. Input assembler가 `TRIANGLELIST` 단위로 primitive를 조립한다.
4. Vertex shader가 각 vertex를 clip space로 변환한다.
5. Rasterizer가 solid 또는 wireframe fill mode로 같은 triangle을 rasterize한다.
6. Wireframe mode에서는 triangle boundary가 표시되므로 quad 내부 대각선도 보일 수 있다.

## 핵심 개념

### Indexed Triangle Mesh

Triangle list는 index 세 개마다 독립 triangle을 만든다. Box는 여섯 사각 face를 각각 두 triangle으로 나누므로 36개 index가 12개 triangle을 구성한다. Normal과 UV가 face마다 달라야 하면 모서리 위치가 같아도 vertex를 분리할 수 있다.

이 구조를 단순히 8개 shared corner vertex로 합치면 face normal과 UV seam의 의미가 달라진다. Vertex 수는 위치의 고유 개수만이 아니라 vertex attribute 조합의 고유 개수를 나타낸다.

### Wireframe Fill Mode

`D3D11_FILL_SOLID`와 `D3D11_FILL_WIREFRAME`은 같은 triangle geometry를 다른 방식으로 rasterize한다. Wireframe mode는 triangle 내부를 채우지 않고 edge를 표시하지만 input assembler topology를 line list로 바꾸지 않는다.

따라서 box의 외곽선뿐 아니라 각 face를 둘로 나눈 diagonal이 함께 나타난다. 이 결과는 mesh triangulation을 관찰하는 데 유용하지만 명시적으로 생성한 box edge 목록과는 다르다.

### Line Geometry와의 구분

명시적 line geometry는 두 vertex마다 하나의 line primitive를 구성하고 `LINELIST` 같은 topology를 사용한다. Chapter07 Step2의 normal 표시는 surface triangle과 별도로 normal 방향의 line vertex와 index를 만든다.

Triangle wireframe은 기존 surface mesh의 topology를 그대로 관찰하는 방법이고 line geometry는 새로운 primitive data를 추가하는 방법이다. 목적과 buffer 구성이 다르므로 문서와 Demo에서 두 방식을 구분한다.

## 데모 연결

Chapter07 Step1은 24개 face vertex와 36개 index로 만든 box를 triangle list로 draw한다. UI의 `Wireframe` checkbox가 solid와 wireframe rasterizer state를 전환하며, 기본 screenshot은 세 면과 각 face의 diagonal을 함께 보여준다.

## 한계

- Geometry shader 기반 wireframe, barycentric edge rendering과 anti-aliased line을 다루지 않는다.
- Triangle adjacency, strip topology와 tessellation을 다루지 않는다.
- Hidden-line removal이나 CAD wireframe 표현을 다루지 않는다.
- Procedural sphere와 subdivision 알고리즘은 이후 Topic으로 분리한다.

## 관련 문서

- [Chapter07 Step1 Example](../../../Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/README.md)
- [Chapter07 Step1 Demo](../../03_Demos/Part2_Chapter05-08/07_01_DrawingWireFrames.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Device And Context](../DirectX11Pipeline/DeviceAndContext.md)
- [Modeling And Geometry Topic Index](topic-index.md)
