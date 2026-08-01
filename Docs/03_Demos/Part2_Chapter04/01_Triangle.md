# Step1 Triangle Demo

## 목적

Step1은 세 vertex로 정의한 triangle을 CPU에서 pixel 단위로 rasterize하고 RGB vertex color를 내부에 보간하는 최소 software rasterization 흐름을 보여준다. CPU 계산과 DirectX11 presentation의 책임 경계도 함께 확인한다.

## 최소 기반

Chapter04의 첫 단계로서 raster 좌표 변환, triangle coverage와 attribute interpolation을 구성한다. 후속 Personal Extension과 Step2는 이 triangle 기반을 여러 primitive로 확장하며, 이번 Demo에는 포함하지 않는다.

## 책임 범위

- Step1의 triangle 구성, bounding box, edge test와 RGB 보간 흐름을 설명한다.
- CPU pixel buffer에서 DirectX11 화면으로 이어지는 구현 경계를 설명한다.
- 일반 이론은 [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 결과 미리보기

![Step1 Triangle result](../../_assets/captures/part2_chapter04_01_triangle.png)

세 vertex의 red, green과 blue가 triangle 내부에서 연속적으로 섞인다. Bounding box 밖과 coverage를 통과하지 않은 pixel은 검은 framebuffer 값을 유지한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | 세 vertex의 NDC position과 RGB color |
| 중간 결과 | raster vertex, bounding box, signed area와 barycentric weight |
| CPU 출력 | 1280×720 RGBA32F pixel buffer |
| 화면 출력 | dynamic texture를 sampling한 full-screen quad |

## 구현 흐름

1. 세 vertex의 position과 RGB color를 정의한다.
2. Aspect ratio와 pixel-center offset을 반영해 raster 좌표로 변환한다.
3. Raster vertex의 최소·최대 좌표로 framebuffer에 clamp한 bounding box를 만든다.
4. Box의 각 pixel에서 세 edge function을 전체 signed area로 정규화한다.
5. 세 barycentric weight가 모두 0 이상인 pixel에 RGB 보간 결과를 기록한다.
6. CPU buffer를 DirectX11 dynamic texture에 복사한다.
7. Pixel shader가 texture를 sampling해 full-screen quad에 표시한다.

## 핵심 구현

### Triangle Coverage와 Color Interpolation

Step1은 전체 framebuffer가 아니라 triangle bounding box만 순회한다. 각 pixel에 대한 세 edge function을 signed area로 나눈 값을 inside test와 vertex color interpolation에 함께 사용한다.

#### Rasterization 의사코드

```cpp
// Pseudo C++: edge test와 barycentric color interpolation
auto rasterVertices = ProjectToRaster(triangle.vertices);
auto bounds = ClampToFramebuffer(BoundingBox(rasterVertices));
auto area = SignedArea(rasterVertices);

for (auto pixel : bounds)
{
    auto weights = EdgeWeights(rasterVertices, pixel) / area;
    if (AllNonNegative(weights))
    {
        framebuffer[pixel] = Interpolate(triangle.colors, weights);
    }
}
```

## 시각 결과

Triangle 꼭짓점에 가까운 영역은 해당 vertex color의 비중이 높고 중심으로 갈수록 세 색이 섞인다. 직선 silhouette는 세 edge function의 inside test 결과이며 내부의 연속적인 색 변화는 같은 barycentric weight가 attribute interpolation에도 쓰인다는 점을 보여준다.

## 구현 범위와 한계

- 하나의 triangle과 RGB vertex color를 다룬다.
- Clipping, top-left fill rule, depth buffer와 perspective-correct interpolation을 포함하지 않는다.
- Dynamic texture upload의 mapped `RowPitch` 처리는 별도 portability 작업으로 남긴다.
- Video Capture 도구의 시험 영상은 이 Demo의 tracked asset으로 사용하지 않는다.

## 검증

- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- Debug x64 build/run: 성공, 현재 확인
- Release x64 build/run: 성공, 현재 확인
- Capture: 전체 application window screenshot 확보, 사용자 확인 완료

## 관련 코드

- [Triangle position과 vertex color](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Rasterization.cpp#L21-L27)
- [NDC에서 raster 좌표로의 변환](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Rasterization.cpp#L30-L46)
- [Signed edge function](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Rasterization.cpp#L49-L55)
- [Bounding box와 pixel 순회](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Rasterization.cpp#L59-L72)
- [Coverage test와 RGB 보간](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Rasterization.cpp#L74-L100)

### DirectX11 Presentation

`Example.cpp`는 매 frame CPU buffer를 초기화하고 software rasterizer를 실행한 뒤 결과를 RGBA32F dynamic texture에 복사한다. Vertex shader와 pixel shader는 full-screen quad와 texture sampling만 담당한다.

- [CPU rasterization과 dynamic texture update](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Example.cpp#L14-L28)
- [RGBA32F dynamic texture 생성](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Example.cpp#L151-L172)
- [Full-screen quad draw](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/Example.cpp#L258-L274)
- [Vertex shader](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/VertexShader.hlsl)
- [Pixel shader](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/PixelShader.hlsl)

## 관련 문서

- [Step1 Triangle Example](../../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md)
- [Triangle Rasterization Topic](../../01_Topics/Rasterization/TriangleRasterization.md)
- [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Demo Index](demo-index.md)
