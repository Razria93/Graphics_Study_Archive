# Step8 Shadow Square Demo

## 목적

두 triangle을 하나의 Square composite primitive로 캡슐화하고 child intersection 결과가 parent object identity와 material을 통해 scene shading으로 이어지는 과정을 확인한다.

## 책임 범위

- Square의 child primitive 구성과 내부 closest-hit를 설명한다.
- Child hit와 parent Square material 연결을 설명한다.
- Square가 독립 scene object로 shadow query에 참여하는 과정을 설명한다.
- 일반 shadow visibility는 [Shadow Ray](../../01_Topics/Shadows/ShadowRay.md)로 위임한다.
- 일반 ray-triangle intersection은 [Intersection](../../01_Topics/RayTracing/Intersection.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

![Step8 Shadow Square result](../../_assets/captures/part1_chapter03_08_shadow-square.png)

## 입력과 출력

- 입력: perspective primary ray, sphere, 네 vertex로 정의한 Square 바닥과 point light
- 출력: 하나의 연속 면으로 shading되는 Square 바닥과 sphere cast shadow
- 표시 경로: CPU RGBA32F buffer를 DirectX11 dynamic texture에 올리고 full-screen quad로 표시

## 이전 순차 Step 대비 변화

앞선 Step8 Shadow는 바닥 triangle 두 개를 각각 scene object로 등록한다. Shadow_Square는 같은 종류의 바닥 surface를 `Square : Object` 하나로 구성한다. 핵심은 화면을 바꾸는 것이 아니라 child primitive의 교차 결과를 parent object 단위로 통합하여 object identity와 material ownership을 구조화하는 데 있다.

## 구현 흐름

```text
네 vertex로 Square 생성
→ 공유 대각선으로 child triangle 두 개 구성
→ 각 child triangle의 ray intersection 검사
→ 유효한 child hit 중 가까운 결과 선택
→ scene closest-hit가 parent Square를 hit object로 연결
→ Square material로 lighting과 shadow 판정
→ CPU 결과를 DirectX11 texture로 표시
```

## 핵심 구현

### Square scene과 parent material

```cpp
CreateScene()
{
    square = MakeSquare(v0, v1, v2, v3);
    square.material = floorMaterial;
    AddObject(square);
}
```

Scene에는 child triangle이 아니라 Square 하나를 등록한다. Ambient, diffuse, specular와 shininess도 Square에 설정한다.

- [Square 바닥과 parent material 구성을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L24-L46).

### Child triangle 구성

```cpp
Square(v0, v1, v2, v3)
{
    triangle1 = Triangle(v0, v1, v2);
    triangle2 = Triangle(v0, v2, v3);
}
```

네 vertex는 공유 대각선 `v0-v2`를 기준으로 두 triangle을 만든다. 현재 winding은 두 child 모두 같은 `+Y` face normal을 만든다.

- [두 child triangle 구성을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Square.h#L7-L15).
- [Triangle의 face normal과 내부 판정을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Triangle.h#L42-L94).

### Square 내부 closest-hit

```cpp
Hit IntersectSquare(ray)
{
    hit1 = triangle1.Intersect(ray);
    hit2 = triangle2.Intersect(ray);

    if (hit1.IsValid() && hit2.IsValid())
    {
        return Nearer(hit1, hit2);
    }
    if (hit1.IsValid())
    {
        return hit1;
    }
    return hit2;
}
```

Square는 child hit 둘을 비교하고 가장 가까운 유효 결과를 반환한다. 공유 대각선에서 두 hit가 함께 유효해도 같은 point와 normal을 가지므로 하나의 surface 결과로 사용할 수 있다.

- [Square의 child closest-hit 선택을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Square.h#L17-L33).

### Parent object identity와 material

```cpp
Hit FindClosestCollision(ray)
{
    closest = Miss;

    for (object in scene)
    {
        hit = object.Intersect(ray);
        if (hit.IsCloserThan(closest))
        {
            hit.object = object;
            closest = hit;
        }
    }

    return closest;
}
```

Child triangle은 geometric hit를 제공한다. Scene query는 그 hit를 반환한 parent Square를 `hit.obj`에 저장하므로 이후 shading은 Square material을 사용한다.

- [Scene closest-hit와 parent object 연결을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L48-L63).
- [Hit의 object field를 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Hit.h#L10-L18).

### Shadow visibility 재사용

```cpp
bool IsInShadow(hit)
{
    shadowRay = MakeOffsetRay(hit, light);
    blocker = FindClosestCollision(shadowRay);
    return blocker.IsBefore(light);
}
```

Primary ray와 shadow ray는 같은 scene closest-hit를 사용한다. Square는 하나의 `Object`이므로 receiver와 blocker query 모두에서 다른 primitive와 같은 contract로 처리된다.

- [Shadow ray와 light-distance blocker 판정을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L65-L73).
- [Visibility에 따른 Square material shading을 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L75-L96).

### CPU 결과 표시

```cpp
UpdateOnce()
{
    RenderCpuPixels();
    MapDynamicTexture();
    CopyPixels();
    UnmapDynamicTexture();
}
```

Square와 shadow intersection은 CPU에서 계산한다. DirectX11과 HLSL은 완성된 texture를 화면에 표시한다.

- [CPU render와 dynamic texture upload를 확인한다](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Example.h#L51-L65).

## 시각 결과

- 네 vertex로 만든 바닥이 하나의 사각 surface로 보인다.
- 두 child triangle 사이의 공유 대각선 seam이 화면에 나타나지 않는다.
- 바닥 전체가 동일한 material과 연속된 `+Y` normal로 shading된다.
- Red sphere 아래에는 Square 바닥 위로 타원형 hard shadow가 나타난다.
- 확인한 장면에는 shadow acne, 끊긴 shadow와 비정상 검은 점이 보이지 않는다.

## 구현 범위와 한계

- Square는 두 triangle의 고정 조합이며 child primitive를 동적으로 추가하지 않는다.
- Child material은 사용하지 않고 parent Square가 scene material을 소유한다.
- 공유 edge에서 두 child hit가 동거리이면 두 번째 hit를 반환하지만 현재 normal과 surface 결과는 같다.
- Triangle의 고정 parallel epsilon과 edge normalize는 grazing ray와 정확한 경계에서 수치 한계가 있다.
- Debug와 Release는 CPU 최종 frame까지 걸리는 시간이 다를 수 있다.
- Project와 executable 이름은 기존 `03_Raytracing_Step8_Shadow`를 유지한다.
- Shader runtime compile은 project working directory에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## 검증

- Debug x64 build/run 성공
- Release x64 build/run 성공
- Project 폴더 working directory에서 `VS.hlsl`, `PS.hlsl` load 확인
- `ComputerGraphics - Step8 Shadow Square` application title 확인
- Debug 최종 frame과 전체 창 capture 확인
- Release가 20초 동안 정상 실행되고 예상 title을 유지함을 확인
- 자세한 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)에서 관리한다.

## 관련 코드

- [Square scene](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L24-L46)
- [Square child intersection](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Square.h#L7-L33)
- [Triangle intersection](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Triangle.h#L42-L94)
- [Parent object closest-hit](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L48-L63)
- [Shadow와 lighting](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Raytracer.h#L65-L96)
- [CPU texture upload](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/Example.h#L51-L65)
- [Application title](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/main.cpp#L38-L40)

## 관련 문서

- [Shadow Square Example README](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/README.md)
- [Shadow Ray](../../01_Topics/Shadows/ShadowRay.md)
- [Intersection](../../01_Topics/RayTracing/Intersection.md)
- [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
