# Step12 Reflection Demo

## 목적

Closest hit의 local Phong shading과 recursive reflection ray가 반환한 color를 material weight로 결합하는 CPU ray tracing 흐름을 확인한다. Red sphere에 ground와 blue sphere가 반사되는 결과를 실제 코드와 연결한다.

## 책임 범위

- Reflection direction, secondary ray origin, fixed-depth recursion과 color composition을 실제 코드 근거에 연결한다.
- Step11과의 순차 변화는 설명하지만 reflection만 바꾼 통제 비교로 표현하지 않는다.
- 일반적인 reflection vector, recursion과 origin bias는 [Recursive Reflection](../../01_Topics/RayTracing/RecursiveReflection.md)으로 위임한다.
- Local lighting은 [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

![Step12 Reflection result](../../_assets/captures/part1_chapter03_12_reflection.png)

## 입력과 출력

- 입력: red reflection sphere, blue local-shaded sphere, 석재 texture ground와 point light
- Primary ray: 1280×720 image plane에서 scene으로 진행
- Secondary ray: closest hit의 reflected direction으로 생성
- 출력: local Phong color와 recursive reflected color의 weighted sum
- 표시 경로: CPU RGBA32F 결과를 DirectX11 dynamic texture와 full-screen quad로 표시

## Step11 대비 변화

Step11은 160×90 output cell마다 64개 primary ray를 평균하고 결과를 point-upscale한다. Step12는 1280×720 primary ray마다 closest hit에서 reflection ray를 재귀 추적한다. Reflection weight 0.5인 red sphere는 local Phong color와 reflected scene color를 함께 사용한다.

두 Step은 sampling 외에도 output resolution, scene geometry, material과 light가 다르다. 따라서 두 capture는 supersampling과 reflection의 순차적인 기능 발전을 보여주지만 reflection 하나만 바꾼 적용 전·후 비교는 아니다.

## 구현 흐름

```cpp
// Pseudo C++: recursive reflection scene 렌더 흐름
RenderReflectionScene()
{
    for each pixel in 1280x720
    {
        primary = MakeCameraRay(pixel);
        color = TraceReflection(primary, depth = 5);
        output[pixel] = Clamp(color);
    }

    UploadCpuBufferToTexture(output);
    DrawFullscreenQuad();
}
```

- [Reflection scene render](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L147-L163)

## 핵심 구현

### Closest hit와 local shading

`traceRay`는 ray와 교차한 object 중 가장 가까운 양의 distance를 선택한다. Hit가 없으면 black을 반환하고, hit가 있으면 ambient, diffuse와 specular로 local Phong color를 계산한다.

- [Closest positive hit 선택](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L65-L79)
- [Local Phong shading](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L82-L116)

### Reflection direction과 recursive trace

```cpp
// Pseudo C++: 실제 Step12의 고정 depth reflection
Color TraceReflection(Ray ray, int depth)
{
    if (IsDepthExhausted(depth))
    {
        return Black;
    }

    Hit hit = FindClosestPositiveHit(ray);

    if (!hit)
    {
        return Black;
    }

    float localWeight = Clamp(
        1 - hit.reflection - hit.transparency
    );
    Color color = ShadePhong(hit, ray) * localWeight;

    if (HasReflection(hit))
    {
        Vector reflected = Reflect(ray.direction, hit.normal);
        Ray secondary = MakeRay(
            hit.point + reflected * epsilon,
            reflected
        );
        color += TraceReflection(
            secondary,
            depth - 1
        ) * hit.reflection;
    }

    return color;
}
```

코드는 `incident = -ray.dir`을 만든 뒤 `2 dot(incident, normal) normal - incident`를 계산한다. 이는 ray 진행 방향 규약에서 `ray.dir - 2 dot(ray.dir, normal) normal`과 같다. Secondary origin은 reflected direction으로 `1e-4` 이동해 즉시 같은 surface를 다시 hit할 가능성을 줄인다.

- [Recursive reflection과 종료 조건](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L118-L144)
- [Reflection material weight](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Object.h#L14-L25)

### Color composition과 depth

Red sphere의 reflection weight는 0.5이므로 local Phong color와 recursive result가 각각 0.5 weight로 더해진다. Trace는 depth 5에서 시작하고 `depth < 0`에서 종료한다. Depth 0에서도 현재 hit를 shading한 뒤 다음 호출이 black을 반환하므로 이를 단순히 반사 5회라고 표현하지 않고 고정 depth 5의 recursion budget으로 구분한다.

- [Reflection scene과 material 구성](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L24-L62)
- [Primary ray와 depth budget](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L147-L163)

### CPU 결과 표시

Ray tracing은 CPU에서 최초 frame에 한 번 수행한다. HLSL은 ray tracing을 수행하지 않고 CPU가 만든 RGBA32F canvas texture를 full-screen quad에 표시한다.

- [CPU render와 dynamic texture upload](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Example.h#L51-L64)
- [Canvas texture 구성](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Example.h#L187-L203)
- [Full-screen presentation](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Example.h#L291-L314)

## 시각 결과

- Red sphere의 아래쪽에는 석재 ground가 뒤집힌 곡면 형태로 반사된다.
- Red sphere 오른쪽에는 blue sphere가 작은 보라색 reflection으로 나타난다.
- Red sphere의 직접 조명 highlight와 reflected object color가 함께 보여 local shading과 reflection 합성을 구분할 수 있다.
- Blue sphere와 ground는 reflection weight가 0이므로 local Phong shading만 사용한다.
- Background와 reflection ray miss는 black으로 나타난다.
- Capture에서 눈에 띄는 self-intersection acne나 black speckle은 관찰되지 않는다.

## 입력 asset

- 파일: `part1_chapter03_stone_mosaic.png`
- 출처 상태: 사용자 직접 생성
- 규격: 1024×1024, RGB PNG
- Input SHA-256: `D0960C2380D0D4432BECEA77A579ACAB2C6A04EDCD8AC0BFA15B1756866348D9`
- Capture SHA-256: `5BF50FCF2D7BDA84C84433613C64ECABF19968B165FC9C3D7FBBC34D9DB60565`
- 관계: Step10·11 검증 input의 동일 바이트 사본을 Step12 project CWD에 둔다.

## 구현 범위와 한계

- Reflection depth 5와 material weight를 고정 사용한다.
- Miss와 depth 종료는 black이며 environment reflection을 포함하지 않는다.
- Origin bias는 normal 방향이 아닌 reflected direction offset을 사용한다.
- Fresnel, rough reflection, stochastic sampling과 physically based energy model을 포함하지 않는다.
- Step11과 scene·resolution이 달라 capture 차이를 reflection 하나의 영향으로 분리할 수 없다.
- Texture와 shader runtime load는 project working directory에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## 검증

- Debug x64 build/run 성공
- Release x64 build/run 성공
- Project 폴더 working directory에서 PNG와 shader load 확인
- `ComputerGraphics - Step12 Reflection` application title 확인
- Ground와 blue sphere의 reflection 확인
- Release x64 전체 application window capture 확인
- 입력과 capture PNG에 text, EXIF, XMP metadata와 개인 식별자 없음
- 자세한 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)에서 관리한다.

## 관련 코드

- [Reflection scene과 material 구성](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L24-L62)
- [Closest positive hit 선택](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L65-L79)
- [Local Phong shading](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L82-L116)
- [Recursive reflection과 종료 조건](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L118-L144)
- [Primary ray와 depth budget](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Raytracer.h#L147-L163)
- [CPU texture upload](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Example.h#L51-L64)
- [Full-screen presentation](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/Example.h#L291-L314)
- [Application title](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/main.cpp#L38-L40)

## 관련 문서

- [Step12 Example README](../../../Part1_Chapter03/03_Raytracing_Step12_Reflection/README.md)
- [Recursive Reflection](../../01_Topics/RayTracing/RecursiveReflection.md)
- [Phong Shading](../../01_Topics/LightingAndShading/PhongShading.md)
- [Texture Sampling](../../01_Topics/TexturingAndMapping/TextureSampling.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
