# Step7 Triangle Demo

## 목적

Step7은 Step6의 perspective ray와 closest-hit 흐름에 triangle primitive를 추가한다. Sphere와 triangle을 같은 scene query로 처리하면서 winding, ray-plane intersection과 edge half-space 내부 판정이 화면의 삼각형 경계와 flat surface shading으로 이어지는 과정을 보여준다.

## 책임 범위

- Step6에서 유지한 perspective primary ray와 closest-hit 흐름을 확인한다.
- Triangle의 back-face, plane intersection과 내부 판정 순서를 설명한다.
- Flat face normal과 sphere radial normal의 시각 차이를 해석한다.
- 일반적인 ray와 primitive intersection 이론은 [Ray](../../01_Topics/RayTracing/Ray.md)와 [Intersection](../../01_Topics/RayTracing/Intersection.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

![Step7 Triangle result](../../_assets/captures/part1_chapter03_07_triangle.png)

Gray triangle의 직선 경계와 red sphere의 곡면이 같은 perspective scene에 나타난다. 두 object가 화면에서 겹치는 영역에서는 ray 진행 방향에서 가장 가까운 교차점을 선택하므로 camera에 가까운 sphere가 triangle을 가린다.

## 입력과 출력

입력은 z=0 image plane의 pixel 위치와 `(0, 0, -1.5)` eye에서 계산한 perspective direction, sphere 하나, triangle vertex 세 개와 point light다. 출력은 CPU가 계산한 RGBA32F pixel buffer이며 DirectX11 full-screen quad가 이를 화면에 표시한다.

## Step6 대비 변화

Step6은 깊이가 다른 sphere 세 개로 perspective 크기 변화와 sphere 간 closest-hit를 보여준다. Step7은 scene을 sphere 하나와 triangle 하나로 바꾸고 `Object` interface를 통해 서로 다른 primitive의 hit를 같은 탐색에 결합한다.

Triangle은 radial normal 대신 vertex winding에서 만든 단일 face normal을 사용한다. 따라서 sphere는 표면 위치마다 normal이 변해 둥근 highlight를 만들지만 triangle은 한 평면 위에서 light와 view 방향 변화만 반영한다.

## 구현 흐름

```text
screen pixel
→ image-plane origin과 perspective direction
→ sphere와 triangle 교차 검사
→ 가장 작은 nonnegative t 선택
→ 선택한 object의 material과 normal로 Phong shading
→ RGBA32F CPU buffer
→ DirectX11 dynamic texture
→ full-screen quad
```

## 핵심 구현

### Sphere와 Triangle Scene

```cpp
BuildScene()
{
    AddSphere(center, radius, sphereMaterial);
    AddTriangle(v0, v1, v2, triangleMaterial);
    SetPointLight(position);
}
```

Step7은 서로 다른 primitive를 `Object` 목록에 함께 추가한다. 각 object는 고유 교차 함수를 제공하고 공통 closest-hit와 shading 경로는 그대로 사용한다.

- [Sphere와 triangle scene 및 material 구성](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Raytracer.h#L23-L44)

### Winding과 Plane Intersection

```cpp
IntersectTriangle(ray, v0, v1, v2)
{
    faceNormal = Normalize(Cross(v1 - v0, v2 - v0));

    if (IsBackFace(ray.direction, faceNormal))
    {
        return Miss;
    }

    denominator = Dot(ray.direction, faceNormal);
    if (IsNearlyParallel(denominator))
    {
        return Miss;
    }

    t = PlaneDistance(ray, v0, faceNormal, denominator);
    if (t < 0)
    {
        return Miss;
    }

    return ray.origin + t * ray.direction;
}
```

Vertex winding은 face normal 방향을 결정한다. 현재 vertex 순서는 `-Z` normal을 만들어 camera 쪽 front face를 유지한다. 이후 ray와 plane이 거의 평행한지 확인하고 origin 앞쪽의 교차점만 받는다.

- [Face normal, back-face culling과 ray-plane 교차](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Triangle.h#L42-L73)

### Edge Half-Space 내부 판정

```cpp
IsInsideTriangle(point, v0, v1, v2, faceNormal)
{
    edgeNormal0 = Normalize(Cross(v1 - v0, point - v0));
    edgeNormal1 = Normalize(Cross(v2 - v1, point - v1));
    edgeNormal2 = Normalize(Cross(v0 - v2, point - v2));

    return SameHemisphere(edgeNormal0, faceNormal)
        && SameHemisphere(edgeNormal1, faceNormal)
        && SameHemisphere(edgeNormal2, faceNormal);
}
```

교차점이 세 directed edge의 안쪽에 있는지 각 edge cross product와 face normal의 부호로 판정한다. `u`, `v` parameter는 이 단계에서 계산하지 않으므로 Step9의 barycentric interpolation과 구분한다.

- [세 edge의 half-space 내부 판정과 미사용 `u`, `v`](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Triangle.h#L75-L94)

### Primitive 공통 Closest Hit

```cpp
FindClosestHit(ray)
{
    closest = Miss;

    for (object in scene)
    {
        hit = object.Intersect(ray);
        if (hit.IsCloserThan(closest))
        {
            closest = hit;
        }
    }

    return closest;
}
```

Sphere와 triangle은 같은 object 목록에서 검사된다. 가장 작은 nonnegative distance를 가진 hit가 선택되므로 겹치는 영역에서 camera에 가까운 sphere가 triangle을 가린다.

- [Primitive 공통 closest-hit 선택](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Raytracer.h#L46-L61)
- [Sphere radial normal과 triangle flat normal 비교](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Sphere.h#L20-L56)

## 시각 결과

- Triangle의 세 vertex가 만드는 half-space가 화면의 직선 대각선 경계로 나타난다.
- Triangle은 단일 face normal을 사용하지만 point light 방향과 view 방향은 hit 위치에 따라 달라져 diffuse와 specular 값이 평면 위에서 변한다.
- Sphere는 hit point에서 center를 뺀 radial normal을 사용해 둥근 명암과 작은 specular highlight를 만든다.
- Sphere와 triangle이 겹치는 부분은 공통 closest-hit가 더 가까운 sphere를 선택한다.

## 구현 범위와 한계

- Triangle은 single-sided이며 back face를 제거한다.
- Degenerate triangle과 정확한 edge의 zero-length cross vector를 별도로 보호하지 않는다.
- Plane parallel 판정은 scene scale과 무관한 절대 epsilon `1e-2`를 사용한다.
- `u`, `v`는 placeholder이며 barycentric coordinate를 계산하지 않는다.
- Perspective direction은 eye에서 계산하지만 ray origin은 image plane에 둔다.
- Shadow ray와 secondary ray를 포함하지 않는다.
- CPU 결과는 최초 frame에 한 번만 계산하므로 runtime parameter 조작을 지원하지 않는다.
- Shader는 project working directory의 상대경로 파일에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## 검증

- 2026-07-30 Debug x64 build와 run을 직접 확인했다.
- 2026-07-30 Release x64 build와 run을 직접 확인했다.
- 두 configuration은 project 폴더를 working directory로 사용했다.
- 공개 application title과 triangle·sphere scene을 전체 창에서 확인했다.
- 조작 가능한 runtime parameter가 없어 기본 전체 창 screenshot 한 장만 사용한다.
- 공개 visual은 PNG text/EXIF/XMP chunk와 개인 식별 정보를 검사한 tracked screenshot을 사용한다.
- 상세 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)와 [Capture Registry](../../_assets/captures/README.md)에서 확인한다.

## 관련 코드

- [Step7 Triangle Example README](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/README.md)
- [Raytracer.h](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Raytracer.h)
- [Triangle.h](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Triangle.h)
- [Sphere.h](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Sphere.h)
- [Example.h](../../../Part1_Chapter03/03_Raytracing_Step7_Triangle/Example.h)

## 관련 문서

- [Ray Topic](../../01_Topics/RayTracing/Ray.md)
- [Intersection Topic](../../01_Topics/RayTracing/Intersection.md)
- [Phong Shading Topic](../../01_Topics/LightingAndShading/PhongShading.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
