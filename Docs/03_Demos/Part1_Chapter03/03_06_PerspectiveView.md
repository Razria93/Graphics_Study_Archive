# Step6 PerspectiveView Demo

## 목적

Step6는 Step5의 고정 방향 orthographic ray를 perspective 방향으로 바꾸고, 깊이가 다른 sphere 세 개에서 가장 가까운 교차를 선택한다. Image-plane sample과 eye 위치가 ray 방향을 만들고 object depth가 화면 크기와 가림 순서로 나타나는 흐름을 보여준다.

## 책임 범위

- Step5 대비 추가된 perspective direction, scene object 목록과 closest-hit 선택을 설명한다.
- CPU ray tracing 결과와 DirectX11 presentation 경계를 설명한다.
- 일반 ray와 camera model은 [Ray](../../01_Topics/RayTracing/Ray.md)로 위임한다.
- Intersection과 Phong 이론은 [Intersection](../../01_Topics/RayTracing/Intersection.md)과 [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md)으로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

### Perspective scene

![Step6 PerspectiveView result](../../_assets/captures/part1_chapter03_06_perspective-view.png)

가까운 red sphere가 가장 크게 보이고 green과 blue sphere는 깊어질수록 작아진다. 겹치는 부분에서는 가장 가까운 양수 hit를 선택해 앞쪽 sphere가 뒤쪽 sphere를 가린다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | 1280×720 pixel coordinate, eye·image plane과 sphere 세 개 |
| 중간 결과 | perspective direction, object별 hit와 closest positive hit |
| CPU 출력 | Phong shading을 적용한 RGBA32F pixel buffer |
| 화면 출력 | dynamic texture를 sampling한 full-screen quad |

## 구현 흐름

1. 각 pixel을 z=0 image-plane position으로 변환한다.
2. `(0, 0, -1.5)` eye에서 image-plane position으로 향하는 direction을 normalize한다.
3. Image-plane position을 origin으로 primary ray를 만든다.
4. Scene object 전체와 교차하고 가장 작은 양수 hit를 선택한다.
5. Hit object의 material과 point light로 ambient, diffuse와 specular color를 계산한다.
6. Clamp한 CPU pixel buffer를 DirectX11 dynamic texture로 복사한다.
7. Pixel shader가 texture를 sampling해 full-screen quad에 표시한다.

## 핵심 구현

### Perspective Primary Ray

Step5는 pixel별 image-plane position을 origin으로 사용하고 direction을 `+Z`로 고정한다. Step6는 eye 위치를 추가하고 image-plane position과의 차이를 normalize해 pixel마다 다른 direction을 만든다. 다만 실제 ray origin은 eye가 아니라 image-plane position으로 유지한다.

#### Perspective ray 생성 의사코드

```cpp
// Pseudo C++: eye와 image-plane sample로 perspective direction 생성
RenderPerspectiveScene()
{
    auto eye = Vector3(0.0f, 0.0f, -1.5f);

    for (each pixel)
    {
        auto planePoint = ScreenToImagePlane(pixel);
        auto direction = Normalize(planePoint - eye);
        Ray ray
        {
            planePoint,
            direction
        };

        pixels[pixel] = Clamp01(TraceRay(ray));
    }
}
```

- [Eye, perspective direction과 primary ray](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Raytracer.h#L86-L100)
- [Screen coordinate를 image plane으로 변환](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Raytracer.h#L104-L110)

### Scene Object와 Closest Hit

Step6는 sphere별 position, depth와 material을 scene object 목록에 저장한다. Object를 순회하며 양수 hit 중 가장 작은 거리를 선택하므로 vector 삽입 순서와 무관하게 화면에서 가장 앞쪽 surface가 shading 대상이 된다.

#### Closest-hit 선택 의사코드

```cpp
// Pseudo C++: scene에서 가장 가까운 유효 교차 선택
FindClosestPositiveHit(ray)
{
    auto closest = Miss;

    for (each object in scene)
    {
        auto hit = object.Intersect(ray);
        if (hit.distance >= 0.0f
            && (closest is Miss || hit.distance < closest.distance))
        {
            hit.object = object;
            closest = hit;
        }
    }

    return closest;
}
```

- [Sphere 세 개와 material 구성](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Raytracer.h#L22-L48)
- [Closest positive hit 선택](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Raytracer.h#L51-L65)
- [Object material과 intersection interface](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Object.h#L12-L27)
- [Sphere intersection 구현](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Sphere.h#L20-L56)

### CPU Shading과 화면 표시

Closest hit가 있으면 Step5의 reflection-vector 기반 Phong lighting을 적용한다. CPU 결과는 최초 frame에 dynamic texture로 업로드하고 HLSL은 full-screen quad에서 texture를 sampling한다.

- [Closest hit와 Phong color 계산](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Raytracer.h#L68-L83)
- [CPU render와 texture upload](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Example.h#L51-L66)
- [Runtime shader load](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Example.h#L68-L95)
- [Full-screen quad draw](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Example.h#L291-L313)

## 시각 결과

Red, green과 blue sphere는 같은 radius를 사용하지만 camera에서 멀어질수록 화면에서 작아진다. 이는 image-plane sample마다 eye를 기준으로 다른 direction을 만들기 때문에 생기는 perspective 크기 변화다.

Sphere가 서로 겹치는 영역에서는 red, green, blue 순으로 앞쪽 surface가 뒤쪽 surface를 가린다. Object 목록은 반대 깊이 순서로 삽입되지만 closest-hit 비교가 거리를 기준으로 동작하므로 삽입 순서가 최종 가림을 결정하지 않는다.

각 sphere의 diffuse color와 white specular highlight는 Step5의 shading 흐름이 여러 object와 perspective view direction으로 확장됐음을 보여준다.

## 구현 범위와 한계

- Perspective direction은 eye에서 계산하지만 primary ray origin은 z=0 image plane이다.
- Image plane 앞쪽 구간은 교차 검사 범위에 포함하지 않는다.
- Pixel center offset과 configurable field of view를 사용하지 않는다.
- Sphere 세 개와 point light 하나만 사용한다.
- Shadow, reflection, refraction, gamma correction과 tone mapping을 포함하지 않는다.
- CPU 결과를 최초 frame에 한 번만 계산하므로 runtime parameter 조작을 지원하지 않는다.
- Shader는 project working directory의 파일에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## 검증

- 2026-07-30 Debug x64 build와 run을 직접 확인했다.
- 2026-07-30 Release x64 build와 run을 직접 확인했다.
- 두 configuration은 project 폴더를 working directory로 사용했다.
- 공개 application title과 perspective scene을 전체 창에서 확인했다.
- UI에는 조절 parameter가 없어 기본 전체 창 screenshot 한 장만 사용한다.
- 공개 visual은 PNG text/EXIF/XMP chunk와 개인 식별 정보를 검사한 tracked screenshot을 사용한다.
- 상세 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)와 [Capture Registry](../../_assets/captures/README.md)를 기준으로 확인한다.

## 관련 코드

- [Step6 PerspectiveView Example README](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/README.md)
- [Raytracer.h](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Raytracer.h)
- [Object.h](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Object.h)
- [Sphere.h](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Sphere.h)
- [Example.h](../../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/Example.h)

## 관련 문서

- [Ray Topic](../../01_Topics/RayTracing/Ray.md)
- [Intersection Topic](../../01_Topics/RayTracing/Intersection.md)
- [Phong Shading Topic](../../01_Topics/LightingAndShading/PhongShading.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
