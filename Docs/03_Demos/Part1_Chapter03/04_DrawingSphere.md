# Step4 DrawingSphere Demo

## 목적

Step4는 화면의 각 pixel에서 orthographic primary ray를 만들고 sphere와
교차시켜 최초 형상을 그리는 CPU ray tracing 기반을 보여준다. 결과 pixel을
DirectX11 dynamic texture로 전달해 계산과 화면 표시의 경계도 함께 확인한다.

## 책임 범위

- Step4의 primary ray, sphere intersection과 diagnostic color 연결을 설명한다.
- CPU pixel buffer에서 DirectX11 화면으로 이어지는 구현 경계를 설명한다.
- 일반 ray 개념은 [Ray](../../01_Topics/RayTracing/Ray.md)로 위임한다.
- 교차 이론은 [Intersection](../../01_Topics/RayTracing/Intersection.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

![Step4 DrawingSphere result](../../_assets/captures/part1_chapter03_04_drawing-sphere.png)

검은 배경 중앙에 sphere가 나타난다. 밝기 변화는 lighting이 아니라 hit distance와
교차 상태를 확인하기 위한 diagnostic visualization이다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | 1280×720 pixel coordinate와 ImGui의 sphere center, radius, RGB |
| 중간 결과 | orthographic primary ray와 ray-sphere hit 정보 |
| CPU 출력 | RGBA32F pixel buffer |
| 화면 출력 | dynamic texture를 sampling한 full-screen quad |

## 구현 흐름

1. 화면 pixel을 aspect ratio가 반영된 camera-plane 위치로 변환한다.
2. pixel 위치를 origin으로 하고 `+Z`를 direction으로 하는 primary ray를 만든다.
3. ray와 sphere의 quadratic equation을 풀어 가장 가까운 양수 hit를 선택한다.
4. miss와 hit distance, 교차 상태를 diagnostic color로 변환한다.
5. 모든 pixel 결과를 RGBA32F CPU buffer에 기록한다.
6. CPU buffer를 DirectX11 dynamic texture에 업로드한다.
7. pixel shader가 texture를 sampling하고 full-screen quad로 표시한다.

## 핵심 구현

### Orthographic Primary Ray

Step4는 perspective camera보다 단순한 기반을 사용한다. 모든 ray direction을
`+Z`로 고정하고 pixel마다 camera-plane origin을 이동해 sphere intersection
자체에 집중한다.

#### Primary ray 생성 의사코드

```cpp
// Pseudo C++: pixel마다 고정 방향의 orthographic ray를 생성
for (each pixel)
{
    auto origin = ScreenToWorld(pixel);
    Ray ray
    {
        origin,
        ForwardZ
    };

    pixels[pixel] = Trace(ray);
}
```

- [화면 좌표 변환과 primary ray 생성](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Raytracer.h#L26-L34)
- [pixel 순회와 ray tracing 결과 기록](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Raytracer.h#L59-L72)

### Ray-Sphere Intersection

Sphere는 quadratic discriminant로 교차 여부를 판정한다. 두 root가 존재하면 ray
origin 앞에 있는 가장 가까운 값을 선택하고 hit point와 normal을 계산한다.

#### Sphere intersection 의사코드

```cpp
// Pseudo C++: 가장 가까운 양수 sphere hit를 선택
auto offset = ray.origin - sphere.center;
auto roots = SolveQuadratic(ray.direction, offset, sphere.radius);

if (!roots.hasRealValue)
{
    return Miss;
}

auto distance = NearestPositive(roots);
if (!distance.hasValue)
{
    return Miss;
}

Hit hit;
hit.distance = distance.value;
hit.point = ray.origin + ray.direction * distance.value;
hit.normal = Normalize(hit.point - sphere.center);
return hit;
```

- [quadratic equation과 유효 root 선택](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Sphere.h#L24-L73)
- [hit diagnostic color 변환](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Raytracer.h#L36-L57)

### DirectX11 Presentation

`Example.h`는 CPU pixel buffer를 RGBA32F dynamic texture에 복사한다. Vertex
shader는 full-screen quad의 position과 UV를 전달하고 pixel shader는 texture를
그대로 sampling한다. HLSL은 ray tracing 계산이 아니라 presentation만 담당한다.

- [CPU render와 dynamic texture update](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Example.h#L50-L61)
- [Dynamic texture 생성](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Example.h#L183-L200)
- [Full-screen quad draw](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Example.h#L287-L310)
- [Vertex shader](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/VS.hlsl)
- [Pixel shader](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/PS.hlsl)

## 시각 결과

기본 설정에서는 검은 배경 중앙에 회색 sphere가 표시된다. Sphere 중심에 가까운
hit와 경계에 가까운 hit의 distance 차이가 밝기 변화로 나타나 원형 silhouette와
교차 범위를 확인할 수 있다. Center, Radius와 RGB UI를 바꾸면 다음 frame의 CPU
pixel 계산에 즉시 반영된다.

이 결과는 surface lighting을 표현하지 않는다. Step4에서는 sphere intersection이
정상적으로 형상을 만드는지 확인하기 위한 시각화로 해석한다.

## 구현 범위와 한계

- 하나의 sphere와 고정 `+Z` orthographic primary ray를 다룬다.
- Phong shading, shadow, texture와 recursive ray는 포함하지 않는다.
- 모든 pixel을 CPU에서 매 frame 다시 계산한다.
- shader runtime load는 project working directory에 의존한다.
- 현재 texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.
- HLSL은 CPU 결과를 표시하며 ray tracing 계산을 수행하지 않는다.

## 검증

- 2026-07-30에 Debug x64 build와 run을 직접 확인했다.
- 2026-07-30에 Release x64 build와 run을 직접 확인했다.
- 두 configuration은 project 폴더를 working directory로 사용했다.
- 실행 창에서 sphere, center/radius/RGB UI와 정상 응답을 확인했다.
- 공개 visual은 client area만 캡처하고 metadata와 식별 정보를 검사한 tracked
  screenshot을 사용한다.
- 상세 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)와 [Capture Registry](../../_assets/captures/README.md)를 기준으로 확인한다.

## 관련 코드

- [Step4 DrawingSphere Example README](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md)
- [Raytracer.h](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Raytracer.h)
- [Sphere.h](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Sphere.h)
- [Example.h](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/Example.h)

## 관련 문서

- [Ray Topic](../../01_Topics/RayTracing/Ray.md)
- [Intersection Topic](../../01_Topics/RayTracing/Intersection.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
