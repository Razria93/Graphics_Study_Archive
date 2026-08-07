# Barycentric Coordinates

## 목적

Triangle 내부의 한 점을 세 vertex의 weight로 표현하고, vertex color나 UV 같은 attribute를 보간하는 원리를 설명한다.

## 책임 범위

이 문서는 barycentric weight의 의미, 내부 조건과 attribute interpolation을 다룬다. Ray와 triangle의 교차·내부 판정은 [Intersection](Intersection.md)으로, Step9의 실제 계산과 결과는 Example README와 상세 Demo로 위임한다.

## 핵심 개념

### 세 Vertex의 Weight

Triangle vertex `v0`, `v1`, `v2`와 내부 점 `p`는 다음과 같이 표현할 수 있다.

```text
p = w0 v0 + w1 v1 + w2 v2
w0 + w1 + w2 = 1
```

점이 triangle 내부 또는 경계에 있으면 세 weight는 0 이상이다. 한 vertex에서 해당 weight는 1이고 나머지는 0이며, 반대편 edge에서는 그 vertex의 weight가 0이다.

### 면적 비율

각 weight는 원래 triangle 면적에 대한 맞은편 sub-triangle 면적의 비율로 구할 수 있다. Step9은 `w0`과 `w1`을 면적 비율로 계산하고 부동소수점 합을 맞추기 위해 `w2 = 1 - w0 - w1`을 사용한다.

Degenerate triangle은 전체 면적이 0이므로 나눗셈 전에 별도 방어가 필요하다. 내부 판정과 winding도 weight의 유효성을 판단하는 전제다.

### Vertex Attribute Interpolation

Vertex마다 attribute `a0`, `a1`, `a2`가 있으면 hit point의 값은 같은 weight로 계산한다.

```text
a(p) = w0 a0 + w1 a1 + w2 a2
```

Step9은 세 RGB color를 보간하고 Step10은 같은 weight로 texture coordinate를 보간한다.

### Ray Hit와 Rasterization의 경계

Step9은 world-space ray와 triangle의 실제 hit point에서 weight를 계산하므로 affine attribute interpolation에 직접 사용한다. Rasterizer가 screen-space weight로 perspective projection 이전 attribute를 복원할 때 필요한 perspective-correct interpolation과는 계산 맥락이 다르다.

## 데모 연결

Step9 Demo의 triangle 세 꼭짓점은 red, green, blue에 대응한다. Step10은 같은 weight를 UV에 적용해 두 triangle으로 구성한 Square에서 image coordinate를 연속적으로 전달한다.

## 한계

- General polygon coordinate와 tetrahedral coordinate는 다루지 않는다.
- Degenerate triangle과 numerical robustness의 상세 정책은 포함하지 않는다.
- Rasterization pipeline의 perspective-correct 공식은 비교 범위로만 언급한다.

## 관련 문서

- Example: [Step9 Barycentric Coordinates README](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/README.md)
- Example: [Step10 Texturing README](../../../Part1_Chapter03/03_Raytracing_Step10_Texturing/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/03_09_BarycentricCoordinates.md`](../../03_Demos/Part1_Chapter03/03_09_BarycentricCoordinates.md)
- Related Topic: [Intersection](Intersection.md)
- Related Topic: [Ray](Ray.md)
- Related Topic: [Texture Sampling](../TexturingAndMapping/TextureSampling.md)
