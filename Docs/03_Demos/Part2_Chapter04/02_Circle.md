# Step2 Circle Demo

## 목적

Step2는 circle을 구성하는 center와 outer-ring data를 공유 CPU 배열에 저장하고 index 세 개로 각 triangle을 조립해 rasterize하는 indexed representation을 보여준다. Step1A의 가변 triangle fan과 시각 결과가 비슷해도 자료 구조와 갱신 책임이 다른 정규 학습 단계다.

## 책임 범위

- 공유 CPU position/color 배열과 index 배열로 triangle fan을 구성하는 흐름을 설명한다.
- Index 세 개로 triangle을 조립하고 position과 color를 조회하는 구현 선택을 설명한다.
- CPU circle geometry와 DirectX11 full-screen presentation geometry의 책임을 구분한다.
- 일반 coverage와 barycentric interpolation은 [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 결과 미리보기

![Step2 Circle result](../../_assets/captures/part2_chapter04_02_circle.png)

32개 triangle이 검은 framebuffer 중앙에 원에 가까운 silhouette를 구성한다. Red center와 green boundary 사이의 연속적인 변화는 공유 color 배열을 barycentric weight로 보간한 결과다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | radius 0.5, 고정 triangle 수 32, red center와 green boundary |
| 중간 결과 | 33 positions, 33 colors, 96 indices와 triangle별 raster 좌표 |
| CPU 출력 | 1280×960 RGBA32F pixel buffer |
| 화면 출력 | dynamic texture를 sampling한 full-screen quad |

## 구현 흐름

1. Center position과 red color를 배열의 첫 원소에 추가한다.
2. 원주를 32등분한 outer-ring position과 green color를 추가한다.
3. 각 segment에 center, 다음 boundary와 현재 boundary index를 기록한다.
4. Index 배열을 세 개씩 순회해 triangle 하나를 조립한다.
5. Index로 position과 color를 조회하고 raster 좌표로 변환한다.
6. Bounding box에서 edge test와 barycentric color interpolation을 수행한다.
7. CPU framebuffer를 DirectX11 dynamic texture에 복사한다.
8. Full-screen quad에서 결과 texture를 sampling해 표시한다.

## 핵심 구현

### Indexed Triangle Fan

Step2는 center와 각 boundary vertex를 한 번만 저장한다. Triangle마다 세 vertex를 복제하는 Step1A와 달리 index 배열이 공유 data를 참조하며, 마지막 triangle은 modulo 연산으로 첫 boundary vertex에 연결된다.

#### Indexed Fan 의사코드

```cpp
// Pseudo C++: 공유 vertex와 index로 고정 triangle fan 구성
positions.push_back(center);
colors.push_back(red);

for (int segment = 0; segment < segmentCount; ++segment)
{
    positions.push_back(CircleVertex(segment, segmentCount));
    colors.push_back(green);
}

for (int segment = 0; segment < segmentCount; ++segment)
{
    indices.push_back(centerIndex);
    indices.push_back(NextBoundaryIndex(segment, segmentCount));
    indices.push_back(CurrentBoundaryIndex(segment));
}
```

- [공유 position/color/index 배열](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.h#L27-L29)
- [Center와 outer-ring vertex 구성](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.cpp#L13-L35)
- [Modulo 기반 triangle index 구성](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.cpp#L37-L46)

### Per-triangle Rasterization

`Render()`는 index 배열을 세 개씩 진행한다. `DrawIndexedTriangle()`은 세 index로 position과 color를 조회한 뒤 Step1과 같은 raster 좌표 변환, bounding box, edge function과 barycentric interpolation을 적용한다.

- [Index 조회와 raster 좌표 변환](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.cpp#L75-L88)
- [Bounding box, coverage와 color interpolation](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.cpp#L90-L113)
- [세 index 단위 render loop](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.cpp#L116-L123)

### DirectX11 Presentation

Circle position과 index는 CPU rasterizer의 `std::vector`에 있다. `Example.cpp`의 DirectX11 vertex/index buffer는 이미 계산한 CPU texture를 화면 전체에 표시하는 quad를 구성하므로 circle geometry와 구분한다.

- [CPU rasterization과 dynamic texture update](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Example.cpp#L10-L23)
- [RGBA32F dynamic texture 생성](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Example.cpp#L146-L170)
- [Full-screen quad presentation](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Example.cpp#L248-L268)

## 시각 결과

Red center에서 green boundary로 이어지는 color interpolation은 각 triangle 내부의 barycentric weight가 공유 color data에 적용된 결과다. 32개 boundary edge는 현재 출력 크기에서 원에 가까운 silhouette를 만들며 segment 경계마다 같은 center와 인접 boundary를 참조한다.

## 구현 범위와 한계

- Step1A의 slider와 fan 재생성을 포함하지 않는 고정 indexed representation이다.
- Circle은 32개 triangle로 근사한 polygon이며 analytic circle rasterization을 수행하지 않는다.
- CPU circle data와 DirectX11 full-screen quad data는 서로 다른 책임을 가진다.
- Clipping, shared-edge top-left rule, depth test와 perspective-correct interpolation을 포함하지 않는다.
- Dynamic texture upload의 mapped `RowPitch` 처리는 별도 portability 작업으로 남긴다.
- Video 필요성은 고정 결과 한 장으로 구현 차이를 설명할 수 있으므로 `생략`으로 판정한다.

## 검증

- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-01 현재 확인
- Release x64 build/run: 성공, 2026-08-01 현재 확인
- Application title: `ComputerGraphics - Step2 Circle`
- Capture: 1282×992 전체 application window screenshot 확보, 사용자 확인 완료

## 관련 코드

- [고정 triangle 수와 circle radius](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.cpp#L13-L19)
- [Indexed triangle rasterization interface](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/Rasterization.h#L12-L29)
- [Application title](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/main.cpp#L30-L40)
- [Vertex shader](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/VertexShader.hlsl)
- [Pixel shader](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/PixelShader.hlsl)

## 관련 문서

- [Step2 Circle Example](../../../Part2_Chapter04/04_Rasterization_Step2_Circle/README.md)
- [Step1A Triangle To Circle Demo](01_TriangleToCircle.md)
- [Triangle Rasterization Topic](../../01_Topics/Rasterization/TriangleRasterization.md)
- [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Demo Index](demo-index.md)
