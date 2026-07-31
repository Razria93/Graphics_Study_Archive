# Step9 Barycentric Coordinates Demo

## 목적

Triangle hit point의 barycentric coordinate로 RGB vertex color를 보간하고, 내부 위치에 따라 색이 연속적으로 변하는 결과를 확인한다.

## 책임 범위

- Step8까지 사용한 ray intersection과 closest-hit 위에서 vertex attribute 보간으로 초점을 전환한다.
- Triangle의 weight 계산과 RGB color 합성을 실제 코드 근거에 연결한다.
- 일반적인 weight와 attribute interpolation은 [Barycentric Coordinates](../../01_Topics/RayTracing/BarycentricCoordinates.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

![Step9 Barycentric Coordinates result](../../_assets/captures/part1_chapter03_09_barycentric_coordinates.png)

## 입력과 출력

- 입력: perspective primary ray, RGB color에 대응하는 세 triangle vertex, 별도 sphere와 point light
- 출력: barycentric weight로 보간된 triangle color와 Phong shading sphere
- 표시 경로: CPU RGBA32F buffer를 DirectX11 dynamic texture로 옮기고 full-screen quad로 표시

## Step8 대비 변화

Step8의 Square 바닥과 shadow ray를 누적하지 않고 장면의 초점을 vertex-color triangle으로 전환한다. Ray, triangle intersection, scene closest-hit와 Phong 기반은 유지하며 hit data에 barycentric coordinate를 추가해 attribute interpolation에 사용한다.

## 구현 흐름

```cpp
// Pseudo C++: barycentric color scene 렌더 흐름
PerspectivePrimaryRay()
{
    hit = FindClosestSceneHit(ray);
    barycentric = ComputeTriangleWeights(hit.point);

    if (hit.object == vertexColorTriangle)
    {
        baseColor = Interpolate(red, green, blue, barycentric);
    }

    output = ShadeWithMaterialOrBaseColor(hit, baseColor);
    UploadCpuBufferToTexture(output);
}
```

- [Barycentric scene render](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Raytracer.h#L98-L113)

## 핵심 구현

### Triangle hit에 weight 저장

```cpp
// Pseudo C++: triangle 교차점과 barycentric 입력 확보
Hit Triangle::CheckRayCollision(ray)
{
    if (IntersectRayTriangle(ray, point, normal, barycentric, distance))
    {
        return Hit(distance, point, normal, barycentric);
    }

    return Miss;
}
```

Plane과 내부 판정을 통과한 교차점의 barycentric coordinate를 hit data에 함께 저장한다.

- [Triangle hit와 barycentric 전달](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Triangle.h#L26-L40)

### Sub-triangle 면적 비율

```cpp
// Pseudo C++: triangle 면적비 기반 barycentric weight 계산
ComputeBarycentric(point)
{
    totalArea = Area(v0, v1, v2);
    w0 = Area(point, v1, v2) / totalArea;
    w1 = Area(v0, point, v2) / totalArea;
    w2 = 1 - w0 - w1;
    return (w0, w1, w2);
}
```

`w0`, `w1`, `w2`는 각각 `v0`, `v1`, `v2`에 대응한다. 내부 점에서는 세 weight가 비음수이고 합이 1이므로 convex color 조합으로 사용할 수 있다.

- [Barycentric 면적 weight 계산](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Triangle.h#L92-L97)

### RGB vertex color 보간

```cpp
// Pseudo C++: vertex color barycentric 보간
InterpolateVertexColor(hit)
{
    return Red * hit.w0
        + Green * hit.w1
        + Blue * hit.w2;
}
```

세 vertex color는 triangle에서 계산한 weight 순서와 일치한다. Triangle hit만 보간 color를 사용하고 sphere는 기존 material 경로를 유지한다.

- [RGB vertex color와 weight 대응](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Raytracer.h#L65-L72)
- [Triangle identity와 shading color 선택](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Raytracer.h#L74-L95)

### CPU 결과 표시

```cpp
// Pseudo C++: CPU render 결과를 dynamic texture로 전달
UpdateOnce()
{
    RenderCpuPixels();
    MapDynamicTexture();
    CopyPixels();
    UnmapDynamicTexture();
}
```

Ray tracing과 color interpolation은 CPU에서 수행한다. DirectX11과 HLSL은 계산된 texture를 화면에 표시한다.

- [CPU render와 dynamic texture upload](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Example.h#L51-L64)

## 시각 결과

- Triangle 왼쪽 아래는 red, 왼쪽 위는 green, 오른쪽 위는 blue가 강하다.
- 내부에서는 세 color가 끊김 없이 혼합되어 barycentric weight의 연속성을 보여준다.
- 직선 edge 밖은 background black으로 남아 triangle 내부 판정 경계를 확인할 수 있다.
- 오른쪽 sphere는 별도 closest-hit와 Phong material 경로가 유지됨을 보여준다.

## 구현 범위와 한계

- Degenerate triangle의 전체 면적 0을 별도로 방어하지 않는다.
- Back-face culling과 고정 parallel epsilon `1e-2`를 사용한다.
- UV data는 보유하지만 Step9 color 결과에는 사용하지 않는다.
- CPU 결과는 최초 frame에 한 번 계산한다.
- Shader runtime compile은 project working directory에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## 검증

- Debug x64 build/run 성공
- Release x64 build/run 성공
- Project 폴더 working directory에서 `VS.hlsl`, `PS.hlsl` load 확인
- `ComputerGraphics - Step9 Barycentric Coordinates` application title 확인
- Release x64 전체 창 기본 capture 확인
- RGB vertex color의 연속 보간과 sphere rendering 확인
- 자세한 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)에서 관리한다.

## 관련 코드

- [Triangle hit와 barycentric data](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Triangle.h#L26-L40)
- [Triangle 내부 판정](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Triangle.h#L43-L90)
- [Barycentric 면적 weight](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Triangle.h#L92-L97)
- [RGB vertex color interpolation](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Raytracer.h#L65-L72)
- [Triangle color와 Phong 합성](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Raytracer.h#L74-L95)
- [CPU texture upload](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/Example.h#L51-L64)
- [Application title](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/main.cpp#L38-L40)

## 관련 문서

- [Step9 Example README](../../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/README.md)
- [Barycentric Coordinates](../../01_Topics/RayTracing/BarycentricCoordinates.md)
- [Intersection](../../01_Topics/RayTracing/Intersection.md)
- [Ray](../../01_Topics/RayTracing/Ray.md)
- [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
