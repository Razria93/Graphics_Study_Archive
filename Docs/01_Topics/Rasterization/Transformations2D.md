# 2D Transformations

## 목적

2D geometry에 translation, rotation과 scale을 적용하고 여러 transform을 조합할 때 순서와 기준점이 결과에 미치는 영향을 설명한다. 특정 Example의 UI나 코드 구조보다 좌표를 변환하는 공통 원리와 해석을 다룬다.

## 책임 범위

- 2D translation, rotation과 non-uniform scale의 기본 관계를 설명한다.
- 원점 기준 rotation·scale과 transform 조합의 비가환성을 설명한다.
- 시간 기반 animation은 후속 Step4와 `AnimationAndPhysics` Topic으로 위임한다.
- 실제 결과 설명은 `Docs/03_Demos`, 검증 사실은 `Docs/02_Verification` 정본으로 위임한다.
- 실제 구현 순서와 capture는 [Step3 Transformations2D Example](../../../Part2_Chapter04/04_Rasterization_Step3_Transformations2D/README.md)과 [상세 Demo](../../03_Demos/Part2_Chapter04/03_Transformations2D.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 핵심 개념

### Translation, Rotation And Scale

Translation은 모든 point에 같은 offset을 더해 geometry의 위치를 바꾼다. Rotation은 기준점을 중심으로 각 point의 방향을 바꾸며, scale은 기준점에서 각 point까지의 거리를 축별 비율로 조정한다. X와 Y에 다른 scale을 적용하면 형태의 aspect가 바뀌고 한 축의 부호를 반전하면 reflection까지 포함한다.

2D rotation은 일반적으로 XY plane에서 Z축을 기준으로 수행한다. 원점이 아닌 pivot을 사용하려면 geometry를 pivot의 반대 방향으로 옮기고 rotation을 적용한 뒤 다시 원래 위치로 이동하는 조합이 필요하다.

### Transform Order

Transform 조합은 교환 법칙이 성립하지 않는다. Geometry를 먼저 이동한 뒤 원점 기준으로 회전하면 이동 offset까지 함께 회전해 orbit 형태의 경로가 생긴다. 반대로 먼저 회전하고 마지막에 이동하면 geometry의 orientation만 바뀐 뒤 지정한 위치로 옮겨진다.

Column-vector convention에서 오른쪽 transform이 먼저 적용된다. 예를 들어 `T2 * R2 * T1 * S * R1`은 point에 `R1`, `S`, `T1`, `R2`, `T2` 순서로 적용된다. 실제 코드는 matrix를 명시하지 않더라도 같은 순서로 좌표 연산을 수행할 수 있다.

### Original Geometry And Derived State

매 frame 변환 결과를 이전 frame의 결과에 다시 적용하면 floating-point 오차가 누적되고 parameter를 기본값으로 되돌려도 원본 형태를 정확히 복원하기 어렵다. 변하지 않는 원본 geometry를 유지하고 현재 parameter로 derived vertex를 다시 계산하면 조작 결과가 결정적이며 identity 상태로 쉽게 돌아갈 수 있다.

## 한계

- 2D affine transform의 개념을 다루며 perspective projection과 3D camera transform은 포함하지 않는다.
- Matrix inverse, decomposition, quaternion과 hierarchy transform은 포함하지 않는다.
- Scale이 0이면 geometry가 퇴화하고 음수 scale은 winding을 반전할 수 있으므로 rasterizer의 fill convention과 함께 검토해야 한다.
- 실제 UI range와 transform parameter 선택은 연결된 Example 책임으로 둔다.

## 관련 문서

- [Step3 Transformations2D Example](../../../Part2_Chapter04/04_Rasterization_Step3_Transformations2D/README.md)
- [Step3 Transformations2D Demo](../../03_Demos/Part2_Chapter04/03_Transformations2D.md)
- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Rasterization Topic Index](topic-index.md)
