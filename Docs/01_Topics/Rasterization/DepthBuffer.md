# Depth Buffer

## 목적

Depth buffer는 rasterized fragment마다 camera 기준 깊이를 비교해 같은 pixel을 덮는 surface 중 보이는 fragment를 선택하는 방법을 설명한다. 특정 graphics API보다 per-pixel storage, 초기화, 비교와 갱신 순서에 집중한다.

## 책임 범위

- Color buffer와 별도로 유지하는 per-pixel depth storage를 설명한다.
- Depth clear, test와 write의 frame 단위 흐름을 설명한다.
- Interpolated depth와 visibility 결정의 관계를 설명한다.
- 동일 depth, precision과 screen-space interpolation의 한계를 설명한다.
- Step5의 실제 함수와 parameter는 [Step5 DepthBuffer Example](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/README.md)로 위임한다.
- 구현 선택과 시각 결과는 `Docs/03_Demos`의 [Step5 DepthBuffer Demo](../../03_Demos/Part2_Chapter04/05_DepthBuffer.md)로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 핵심 개념

### Per-Pixel Depth Storage And Clear

Color buffer의 각 pixel과 같은 index에 depth 값을 저장한다. Frame 시작 시 모든 depth를 가장 먼 초기값으로 clear하면 첫 유효 fragment가 비교를 통과할 수 있다. Reversed-Z처럼 비교 방향이 다른 체계에서는 clear 값과 비교 함수도 함께 반전하지만, 같은 convention을 frame 전체에서 유지해야 한다.

### Depth Test And Write

Rasterizer가 fragment의 depth를 계산한 뒤 현재 pixel에 저장된 값과 비교한다. 일반적인 smaller-is-nearer convention에서는 새 depth가 더 작을 때 color와 depth를 함께 갱신한다. Color만 바꾸거나 depth만 바꾸면 이후 fragment의 visibility 판단과 화면 결과가 어긋난다.

```text
clear color and depth
→ rasterize primitive
→ interpolate fragment depth
→ compare with stored depth
→ pass: write color and depth
→ fail: keep previous pixel
```

### Interpolated Depth

Triangle의 vertex depth는 covered pixel마다 barycentric weight로 보간할 수 있다. Projection을 적용한 pipeline에서는 어떤 공간의 depth를 보간하는지와 perspective division 전후의 관계가 중요하다. 단순 screen-space 예제의 affine Z 보간은 visibility 원리를 보여주지만 일반 perspective pipeline 전체를 대신하지 않는다.

### Equal Depth And Precision

두 fragment의 depth가 같으면 `<`, `<=` 같은 비교 함수와 draw order가 결과를 결정한다. Coplanar surface의 값이 floating-point precision 범위에서 반복해 앞뒤로 바뀌면 Z-fighting이 나타날 수 있다. Geometry 분리, depth bias, near/far 범위 조정과 더 높은 precision이 상황에 따라 필요하다.

## 한계

- 이 문서는 hierarchical Z, early-Z, depth pre-pass와 GPU compression을 다루지 않는다.
- Reversed-Z와 logarithmic depth는 비교 가능한 확장으로만 언급하고 구현 절차를 포함하지 않는다.
- Transparency는 단순 depth test만으로 해결되지 않으며 sorting 또는 별도 compositing이 필요하다.
- MSAA sample별 depth와 stencil operation은 포함하지 않는다.

## 관련 문서

- [Step5 DepthBuffer Example](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/README.md)
- [Step5 DepthBuffer Demo](../../03_Demos/Part2_Chapter04/05_DepthBuffer.md)
- [Triangle Rasterization](TriangleRasterization.md)
- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Rasterization Topic Index](topic-index.md)
