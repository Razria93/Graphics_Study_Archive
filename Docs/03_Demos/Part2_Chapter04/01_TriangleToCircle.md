# Step1A Triangle To Circle Demo

## 목적

Step1A는 단일 triangle rasterizer를 triangle fan으로 반복해 polygonal circle을 만들고 segment 수가 silhouette에 미치는 영향을 보여준다. 사용자가 Step1을 확장한 Personal Extension이며 강의 단계인 Step2 Circle과 별도 구현으로 유지한다.

## 책임 범위

- 독립 `MyTriangle` 목록을 생성하는 fan 구성과 per-triangle rasterization을 설명한다.
- Slider 값이 바뀔 때 fan을 재생성하는 구현 선택을 설명한다.
- 3개와 32개 segment의 시각 차이와 기본값 선정 근거를 설명한다.
- 일반 coverage와 barycentric interpolation은 [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 결과 미리보기

### 3 Segments

![Step1A 3 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_3.png)

3개 segment에서는 fan의 boundary가 triangle과 같다.

### 32 Segments

![Step1A 32 segments](../../_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png)

32개 segment에서는 같은 반지름과 색 보간을 유지하면서 silhouette가 원에 가까워진다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | radius 0.5, triangle count 3부터 100까지, center red와 boundary blue |
| 중간 결과 | 독립 `MyTriangle` 목록, raster bounding box와 barycentric weight |
| CPU 출력 | 1200×900 RGBA32F pixel buffer |
| 화면 출력 | slider UI와 dynamic texture를 표시한 application window |

## 구현 흐름

1. Slider의 triangle count와 현재 fan count를 비교한다.
2. 값이 달라지면 기존 triangle 목록을 비운다.
3. 원주를 count만큼 나눈 각도로 center와 인접 boundary vertex를 구성한다.
4. Center red와 boundary blue를 가진 독립 triangle을 목록에 추가한다.
5. 각 triangle의 bounding box에서 edge test와 barycentric color interpolation을 수행한다.
6. CPU pixel buffer를 DirectX11 dynamic texture에 복사한다.
7. Full-screen quad와 ImGui slider를 함께 표시한다.

## 핵심 구현

### Dynamic Triangle Fan

`SetTriangleCount()`는 동일한 center를 공유하는 논리적 fan을 만들지만 저장 구조에서는 각 segment를 완전한 `MyTriangle`로 복제한다. 각 boundary vertex의 각도는 `2π / count` 간격으로 계산한다.

#### Triangle Fan 의사코드

```cpp
// Pseudo C++: slider count로 독립 triangle fan 재생성
if (currentCount != requestedCount)
{
    triangles.clear();
    for (int segment = 0; segment < requestedCount; ++segment)
    {
        auto center = Vertex({0, 0}, red);
        auto edge0 = CircleVertex(segment, requestedCount, blue);
        auto edge1 = CircleVertex(segment + 1, requestedCount, blue);
        triangles.push_back(Triangle(center, edge0, edge1));
    }
}
```

### Per-triangle Rasterization

생성한 각 triangle은 Step1과 같은 raster coordinate, bounding box, edge function과 barycentric interpolation을 사용한다. 구조를 공유하지 않고 같은 알고리즘을 triangle 목록에 반복 적용한다.

## 시각 결과

3개 segment는 red center에서 blue boundary로 보간되는 하나의 triangle을 보여준다. Count를 늘리면 각 triangle의 중심 보간은 유지되고 boundary edge 길이가 짧아져 전체 silhouette가 원에 가까워진다. 15는 facet이 뚜렷하고 24는 원에 가깝지만 각이 남으며 32는 현재 출력 크기에서 거의 원으로 읽혀 기본값으로 선택한다.

## 구현 범위와 한계

- Step1을 확장한 사용자 Personal Extension이며 Step2의 indexed geometry를 대신하지 않는다.
- 기본값 32는 현재 1200×900 출력에서의 시각 판단이며 일반적인 품질 기준은 아니다.
- Segment가 증가하면 독립 triangle과 per-pixel 작업량도 증가한다.
- Clipping, shared-edge top-left rule, depth test와 perspective-correct interpolation을 포함하지 않는다.
- Video 필요성은 slider 변화와 fan 재생성 과정을 보여주므로 `필수`로 판정한다. Selected master는 local에서 검증 완료 상태로 유지하고 tracked 상세 Demo는 3·32 PNG 두 장만 사용한다.

## 검증

- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- Debug x64 build/run: 성공, 현재 확인
- Release x64 build/run: 성공, 현재 확인
- Capture: 3·32 전체 application window screenshot 확보, 사용자 확인 완료
- Video: selected local master 자동·사용자 검수 완료, H.264, yuv420p, 1202×932, CFR 30fps, 10.9초, audio 없음, decode 성공, [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14)에 게시

## 관련 코드

- [기본 triangle count와 radius](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/Rasterization.cpp#L18-L21)
- [Triangle fan 생성](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/Rasterization.cpp#L51-L75)
- [Triangle별 coverage와 RGB 보간](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/Rasterization.cpp#L77-L125)
- [Slider 변경에 따른 fan 재생성](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/Rasterization.cpp#L127-L135)
- [Triangle count slider](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/main.cpp#L65-L70)
- [CPU buffer와 dynamic texture update](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/Example.cpp#L14-L28)

## 관련 문서

- [Step1A Triangle To Circle Example](../../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md)
- [Step1 Triangle Example](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md)
- [Triangle Rasterization Topic](../../01_Topics/Rasterization/TriangleRasterization.md)
- [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Demo Index](demo-index.md)
