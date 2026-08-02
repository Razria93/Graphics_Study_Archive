# Perspective Projection

## 목적

Perspective projection은 camera에서 멀어질수록 물체가 작게 보이는 원근 관계와 projection 이후 attribute를 올바르게 보간하는 원리를 설명한다. Depth에 따른 화면 좌표 축소와 perspective-correct interpolation을 구분해 다룬다.

## 책임 범위

- Eye-relative depth와 projected XY 크기의 관계를 설명한다.
- Orthographic projection과 perspective projection의 차이를 설명한다.
- Screen-space affine interpolation이 perspective 장면에서 attribute를 왜곡하는 이유를 설명한다.
- Reciprocal depth를 사용한 perspective-correct interpolation의 원리를 설명한다.
- Step8 고유 구현은 [Step8 PerspectiveProjection Example](../../../Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/README.md)로 위임한다.
- 구현 흐름과 시각 결과는 [Step8 PerspectiveProjection Demo](../../03_Demos/Part2_Chapter04/08_PerspectiveProjection.md)로 위임한다.
- D3D11 pipeline에서 projection parameter를 직접 전환하는 구현은 [Chapter06 Step3 ModelViewProj Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj/README.md)과 [상세 Demo](../../03_Demos/Part2_Chapter05-08/06_ModelViewProj.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과의 책임 정본은 `Docs/03_Demos`에 둔다.
- build/run/capture 사실의 책임 정본은 `Docs/02_Verification`에 둔다.

## 핵심 개념

### Orthographic과 Perspective Projection

Orthographic projection은 depth가 달라도 같은 크기의 물체를 같은 화면 크기로 유지한다. Perspective projection은 eye에서 screen plane까지의 거리와 vertex depth의 비율로 XY를 축소한다. 간소화된 camera가 negative Z 방향에 있고 screen plane이 eye 앞에 있다고 보면 `d / (d + z)` 같은 비율을 사용할 수 있으며, `z`가 커질수록 projected XY가 작아진다.

실제 graphics pipeline은 homogeneous clip coordinate와 projection matrix를 사용한다. Clip-space position을 `w`로 나누어 NDC를 만들며 near/far clipping과 depth mapping도 함께 정의한다. 간소화된 비율은 원근 크기 관계를 보여주지만 완전한 projection pipeline을 대체하지 않는다.

Perspective projection은 vertical FOV, aspect ratio와 near·far plane을 함께 사용한다. FOV가 작아지면 같은 scene이 확대되어 보이고 aspect ratio는 horizontal coverage에 영향을 준다. Orthographic projection은 FOV 대신 화면에 대응할 폭과 높이를 직접 정하므로 같은 Model·View에서도 object의 투영 크기와 평행선 표현이 달라진다.

유효한 projection에는 `near < far`, 양수 depth range와 극단적이지 않은 FOV가 필요하다. UI로 parameter를 노출하는 예제는 invalid 조합이 화면 소실이나 불안정한 matrix로 이어질 수 있음을 별도 제약으로 기록한다.

### Affine Interpolation의 왜곡

Rasterizer가 화면 공간의 barycentric weight로 UV와 color를 바로 보간하면 screen-space affine interpolation이 된다. Orthographic projection에서는 이 관계가 자연스럽지만 perspective division을 거친 triangle에서는 world 또는 view-space의 선형 관계가 화면 공간에서 비선형으로 보인다. 기울어진 surface의 checker가 한쪽으로 몰리거나 직선 패턴의 간격이 부자연스러워지는 현상이 대표적인 결과다.

### Perspective-Correct Interpolation

각 vertex의 screen-space weight를 clip-space `w` 또는 eye-relative depth로 나눈 뒤 합으로 정규화하면 perspective-correct weight를 얻는다. 이 weight로 UV와 color를 보간하면 projection 이전 공간의 선형 관계를 복원할 수 있다.

일반적인 형태는 `a = Σ(λᵢ aᵢ / wᵢ) / Σ(λᵢ / wᵢ)`다. 여기서 `λᵢ`는 screen-space barycentric weight, `aᵢ`는 vertex attribute, `wᵢ`는 projection division에 사용한 homogeneous 값이다. 구현에 따라 reciprocal depth를 미리 전달해 같은 계산을 구성한다.

### Projection과 Depth Test

Projection은 화면상의 XY와 attribute 보간뿐 아니라 visibility를 위한 depth 표현과도 연결된다. GPU pipeline은 projection matrix와 viewport depth range에 따라 depth를 매핑하지만, 교육용 CPU rasterizer는 eye-relative Z를 직접 보간해 작은 값을 가까운 fragment로 취급할 수 있다. 이 경우 depth 초기값과 유효 범위를 명시적으로 관리해야 한다.

## 한계

- Projection matrix의 전체 유도와 handedness별 행렬 convention은 다루지 않는다.
- Homogeneous clipping과 near/far plane clipping 알고리즘은 포함하지 않는다.
- Reversed-Z, logarithmic depth와 depth precision 최적화는 다루지 않는다.
- Derivative 기반 texture filtering과 anisotropic filtering은 포함하지 않는다.
- Step8의 간소화된 depth 보간 방식은 GPU fixed-function depth 동작과 동일하지 않다.

## 관련 문서

- [Step8 PerspectiveProjection Example](../../../Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/README.md)
- [Step8 PerspectiveProjection Demo](../../03_Demos/Part2_Chapter04/08_PerspectiveProjection.md)
- [Chapter06 Step3 ModelViewProj Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj/README.md)
- [Chapter06 Step3 ModelViewProj Demo](../../03_Demos/Part2_Chapter05-08/06_ModelViewProj.md)
- [Depth Buffer](DepthBuffer.md)
- [Triangle Rasterization](TriangleRasterization.md)
- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Rasterization Topic Index](topic-index.md)
