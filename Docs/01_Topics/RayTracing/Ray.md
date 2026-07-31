# Ray

## 목적

Ray tracing에서 ray가 표현하는 위치와 방향, 그리고 scene query에 사용하는 parametric 형태를 설명한다. `Part1_Chapter03`의 Step4, Step6와 Step7이 화면 pixel을 primary ray로 바꾸고 여러 primitive를 조회하는 방식을 이해하기 위한 개념 정본으로 사용한다.

## 책임 범위

이 문서는 ray의 일반적인 구성과 primary ray의 역할을 다룬다. Step4, Step6와 Step7의 함수 및 DirectX11 표시 구현은 Example README로, build/run/capture 사실은 Verification으로, 실제 처리 흐름과 시각 결과는 상세 Demo로 위임한다.

## 개념 흐름

화면의 sample 위치를 정한 뒤 camera model에 맞는 origin과 direction을 구성한다. ray는 scene object와의 교차 검사에 전달되고, 유효한 hit가 있으면 해당 위치의 색이나 후속 ray 계산에 사용된다.

## 핵심 개념

### Origin And Direction

Ray는 시작점 `o`와 방향 `d`로 표현한다. 방향은 교차 거리의 의미를 일정하게 유지하기 위해 일반적으로 normalize한다. ray 위의 점은 다음 parametric 식으로 나타낸다.

```text
p(t) = o + t d
```

`t`가 양수이면 origin 앞쪽에 있는 점을 나타낸다. 교차 검사는 보통 가장 작은 유효 양수 `t`를 선택한다.

### Primary Ray

Primary ray는 화면 sample에서 scene으로 처음 보내는 ray다. Perspective camera는 대개 camera 위치를 공통 origin으로 사용하고 pixel마다 direction을 바꾼다. Orthographic camera는 direction을 고정하고 pixel마다 origin을 이동한다.

Step4는 각 pixel의 camera-plane 위치를 origin으로 사용하고 direction을 `(0, 0, 1)`로 고정한다. 따라서 perspective distortion 없이 sphere intersection의 기본 구조를 확인한다.

Step6는 eye에서 camera-plane sample로 향하는 direction을 normalize해 pixel마다 다른 perspective 방향을 만든다. 일반적인 perspective camera와 달리 실제 ray origin은 eye가 아니라 camera-plane sample에 두므로 image plane 앞쪽 구간은 교차 검사에서 제외한다.

## 데모 연결

Step4 Example은 화면의 각 pixel을 orthographic primary ray로 바꾸고 sphere와 교차시킨다. Step6 Example은 perspective 방향과 closest-hit scene query를 추가하고 Step7 Example은 같은 ray를 sphere와 triangle에 전달한다. 구체적인 함수 연결과 결과 화면은 각 Example README와 상세 Demo에서 확인한다.

## 한계

- secondary ray, shadow ray와 recursive ray는 다루지 않는다.
- camera projection의 전체 수학은 다루지 않는다.
- object별 intersection 구현은 Intersection Topic에 위임한다.

## 관련 문서

- Example: [Step4 DrawingSphere README](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md)
- Example: [Step6 PerspectiveView README](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/README.md)
- Example: [Step7 Triangle README](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/04_DrawingSphere.md`](../../03_Demos/Part1_Chapter03/04_DrawingSphere.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/06_PerspectiveView.md`](../../03_Demos/Part1_Chapter03/06_PerspectiveView.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/07_Triangle.md`](../../03_Demos/Part1_Chapter03/07_Triangle.md)
- Related Topic: [Intersection](Intersection.md)
