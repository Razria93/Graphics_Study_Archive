# 2D Animation And Hierarchical Orbit

## 목적

시간에 따라 angle과 transform state를 갱신해 2D object를 움직이고 parent motion과 child local motion을 조합하는 기본 animation 구조를 설명한다. 특정 Example의 천체 크기나 UI 값보다 timestep, angular velocity와 transform hierarchy의 공통 관계를 다룬다.

## 책임 범위

- Angular velocity와 timestep으로 angle을 갱신하는 관계를 설명한다.
- 고정 timestep과 실제 frame cadence가 animation 속도에 미치는 영향을 설명한다.
- Parent transform과 child local transform을 조합하는 계층적 orbit을 설명한다.
- Translation과 rotation의 일반 수학은 [2D Transformations](../Rasterization/Transformations2D.md)으로 위임한다.
- 실제 구현은 [Step4 Animation2D Example](../../../Part2_Chapter04/04_Rasterization_Step4_Animation2D/README.md), 시각 결과는 [상세 Demo](../../03_Demos/Part2_Chapter04/04_Animation2D.md), 검증 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 핵심 개념

### Angular State Update

Angular velocity `ω`와 timestep `Δt`가 있으면 한 update의 각도 변화는 `Δθ = ωΔt`다. 현재 angle에 이 값을 누적하면 일정한 방향과 속도의 rotation 또는 orbit을 만든다. Angle 자체를 화면 위치로 직접 사용하지 않고 local offset을 rotation한 결과로 위치를 계산하면 radius와 phase를 독립적으로 조절할 수 있다.

고정 timestep은 update 한 번의 변화량을 일정하게 만들지만 update 호출 횟수가 실제 시간과 일치한다는 전제가 필요하다. Render loop가 30회보다 빠르거나 느리게 호출되면 wall-clock 기준 animation 속도도 달라진다. 실제 시간에 맞춘 animation은 elapsed time을 측정하거나 fixed-update accumulator를 사용해 render cadence와 simulation cadence를 분리한다.

### Hierarchical Orbit Composition

Child의 local orbit은 child geometry에 local offset과 local angle을 먼저 적용해 계산한다. 이 결과에 parent offset과 parent angle을 적용하면 child는 parent 주변을 움직이면서 parent의 상위 orbit도 함께 따른다. Parent motion이 바뀌어도 child local radius와 phase는 local space 책임으로 유지된다.

2D column-vector 관점에서 child world position은 `ParentTransform * ChildLocalTransform * localPosition`으로 해석할 수 있다. 코드는 matrix를 직접 만들지 않고 offset addition과 `RotateAboutZ()`를 같은 순서로 호출해 동일한 hierarchy를 구성할 수 있다.

### State, Rendering And Presentation

Animation state 갱신, geometry transform, rasterization과 화면 표시는 서로 다른 책임이다. CPU 예제에서는 angle을 갱신한 뒤 transformed vertex를 rasterize하고, DirectX11 shader는 완성된 CPU framebuffer를 texture로 표시한다. 이 구조에서는 shader가 object animation을 수행하지 않는다.

## 한계

- 기본 angle update와 2단계 orbit hierarchy만 다루며 skeletal animation, keyframe interpolation과 physics integration은 포함하지 않는다.
- 고정 timestep의 안정성 개념을 설명하지만 collision이나 force simulation을 위한 integrator 비교는 포함하지 않는다.
- Parent가 하나인 2D hierarchy를 기준으로 하며 scene graph의 ownership과 matrix cache 정책은 포함하지 않는다.
- 실제 orbit radius, velocity range와 UI 선택은 연결된 Example 책임으로 둔다.

## 관련 문서

- [Step4 Animation2D Example](../../../Part2_Chapter04/04_Rasterization_Step4_Animation2D/README.md)
- Demo: [`Docs/03_Demos/Part2_Chapter04/04_Animation2D.md`](../../03_Demos/Part2_Chapter04/04_Animation2D.md)
- Verification: [`Docs/02_Verification/Part2_Chapter04/verification-index.md`](../../02_Verification/Part2_Chapter04/verification-index.md)
- [2D Transformations](../Rasterization/Transformations2D.md)
- [Animation And Physics Topic Index](topic-index.md)
