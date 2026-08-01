# Backface Culling

## 목적

Backface culling은 triangle의 orientation을 기준으로 camera 반대 방향의 face를 rasterization 대상에서 제외하는 원리를 설명한다. Winding, signed area, 좌표계 convention과 mirrored transform의 관계를 중심으로 다루며 특정 예제의 함수와 UI는 관련 Example과 Demo로 위임한다.

## 책임 범위

- Vertex winding으로 triangle orientation을 표현하는 원리를 설명한다.
- Signed area의 부호가 좌표계와 화면 변환에 의존함을 설명한다.
- Backface rejection이 coverage와 fragment shading 전에 수행되는 이유를 설명한다.
- Mirrored transform이 post-transform winding을 반전하는 경우를 설명한다.
- Degenerate triangle과 backface를 구분한다.
- Step7 고유 구현은 [Step7 BackfaceCulling Example](../../../Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling/README.md)로 위임한다.
- 구현 흐름과 시각 결과는 [Step7 BackfaceCulling Demo](../../03_Demos/Part2_Chapter04/07_BackfaceCulling.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과의 책임 정본은 `Docs/03_Demos`에 둔다.
- build/run/capture 사실의 책임 정본은 `Docs/02_Verification`에 둔다.

## 핵심 개념

### Winding과 Face Orientation

Triangle의 세 vertex를 나열한 순서는 primitive의 orientation을 정의한다. Clockwise 또는 counter-clockwise 중 어느 방향을 front face로 취급할지는 graphics API와 rasterizer 설정의 convention이다. 같은 vertex 위치라도 index 순서를 뒤집거나 orientation을 반전하는 transform을 적용하면 front/back 분류가 바뀐다.

### Signed Area와 좌표계 Convention

두 edge의 2D determinant는 triangle의 두 배 signed area를 제공한다. 절댓값은 면적과 비례하고 부호는 orientation을 나타내지만, 부호 자체의 의미는 좌표축 방향에 따라 달라진다. World 또는 NDC의 Y-up 좌표를 raster Y-down 좌표로 변환하면 orientation 부호가 한 번 반전되므로 culling predicate는 area 계산이 수행되는 좌표계와 함께 정의해야 한다.

### Culling의 Pipeline 위치

Back-facing primitive를 coverage 계산 전에 제외하면 bounding box 순회, barycentric interpolation과 fragment shading 비용을 피할 수 있다. 개념적으로는 vertex transform 이후 orientation을 판정하고 rasterization 이전에 primitive를 거르는 단계다. Two-sided surface나 내부 면을 보여줘야 하는 material은 culling을 비활성화하거나 별도 pass를 사용할 수 있다.

### Degenerate Triangle과 Mirrored Transform

Signed area가 0인 triangle은 세 vertex가 한 직선에 놓이거나 같은 위치를 공유해 면적이 없는 degenerate primitive다. 이는 방향이 반대인 backface와 별개로 처리한다. Negative scale, axis reflection 또는 orientation을 뒤집는 transform은 원본 index를 유지해도 post-transform winding을 반전할 수 있으므로 model transform과 culling convention을 함께 확인해야 한다.

## 한계

- Clipping이 orientation 판정에 미치는 세부 순서는 다루지 않는다.
- Perspective division과 viewport transform 전체를 수식으로 전개하지 않는다.
- Two-sided lighting과 material별 culling 설정은 포함하지 않는다.
- Floating-point 오차를 고려한 degenerate epsilon 선택은 구현별 판단으로 남긴다.
- Step7의 CPU 구현은 DirectX11 rasterizer state와 GPU fixed-function 동작을 그대로 재현하지 않는다.

## 관련 문서

- [Step7 BackfaceCulling Example](../../../Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling/README.md)
- [Step7 BackfaceCulling Demo](../../03_Demos/Part2_Chapter04/07_BackfaceCulling.md)
- [Triangle Rasterization](TriangleRasterization.md)
- [Shader Stage](../DirectX11Pipeline/ShaderStage.md)
- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Rasterization Topic Index](topic-index.md)
