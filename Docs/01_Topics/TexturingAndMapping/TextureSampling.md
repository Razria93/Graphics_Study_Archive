# Texture Sampling

## 목적

UV coordinate를 image texel 좌표로 변환하고 point 또는 bilinear filtering과 address mode로 color를 읽는 기본 원리를 설명한다.

## 책임 범위

이 문서는 UV-to-texel 변환, texel center, filtering과 address mode를 다룬다. Barycentric weight를 이용한 일반 attribute interpolation은 [Barycentric Coordinates](../RayTracing/BarycentricCoordinates.md)로, Step10의 실제 CPU texture class와 textured Square는 Example README로 위임한다.

## 핵심 개념

### UV와 Texel Center

Normalized UV는 image 크기와 독립적인 coordinate다. 폭 `W`, 높이 `H`인 image에서 texel center 기준 좌표는 다음처럼 계산할 수 있다.

```text
xy = uv * (W, H) - (0.5, 0.5)
```

`uv = (0,0)`과 `(1,1)`은 image 경계에 놓인다. Point sampling은 가장 가까운 integer texel을 선택하고, bilinear sampling은 `floor(xy)` 주변 네 texel과 fractional offset을 사용한다.

### Point와 Bilinear Filtering

Point filtering은 한 texel을 선택하므로 경계가 선명하지만 확대 시 block이 보인다. Bilinear filtering은 가로로 두 번 보간한 뒤 두 결과를 세로로 보간해 연속적인 color를 만든다.

```text
top = lerp(c00, c10, dx)
bottom = lerp(c01, c11, dx)
result = lerp(top, bottom, dy)
```

Filtering은 image 안의 sample을 결합하는 규칙이며, UV가 image 경계를 벗어났을 때의 address mode와 구분한다.

### Clamp와 Wrap Address

Clamp는 image 경계 밖 coordinate를 가장 가까운 edge texel에 고정한다. Wrap은 integer texel coordinate를 image 크기로 나눈 나머지로 변환해 반대편 edge로 반복한다.

Step10의 active path는 bilinear filtering과 wrap address를 사용한다. UV 경계에서 네 이웃을 구할 때 반대편 edge texel이 포함될 수 있으므로 반복 가능한 texture에 적합하다.

### Image Row와 V 방향

Image loader와 graphics API는 row origin 규약이 다를 수 있다. Step10은 `stb_image`의 top-row-first data를 뒤집지 않고 Square 위쪽 vertex에 `v=0`, 아래쪽 vertex에 `v=1`을 배치하므로 입력 image가 원래 방향으로 표시된다.

## 한계

- Mipmap, trilinear와 anisotropic filtering은 다루지 않는다.
- Color space와 gamma-correct filtering은 포함하지 않는다.
- GPU sampler state의 상세 동작은 개념 비교 범위로만 다룬다.
- Texture compression과 streaming은 포함하지 않는다.

## 관련 문서

- Example: [Step10 Texturing README](../../../Part1_Chapter03/03_Raytracing_Step10_Texturing/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/demo-index.md`](../../03_Demos/Part1_Chapter03/demo-index.md)
- Related Topic: [Barycentric Coordinates](../RayTracing/BarycentricCoordinates.md)
