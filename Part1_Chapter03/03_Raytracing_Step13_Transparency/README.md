# Step13 Transparency

## Overview

이 예제는 Step12의 recursive ray trace에 refraction path를 추가한다. IOR 1.5인 transparent sphere가 air와 glass 경계를 드나들 때 normal과 IOR ratio를 전환하고, `glm::refract`로 계산한 secondary ray를 재귀 추적한다.

일반적인 Snell’s law, IOR와 total internal reflection은 [Refraction And Transparency](../../Docs/01_Topics/RayTracing/RefractionAndTransparency.md)로 위임한다. 이 문서는 Step13 코드와 실행 진입점을 설명한다.

## 실행 진입점

- Solution: `03_Raytracing_Step13_Transparency.sln`
- Application entry: `main.cpp`
- Scene, reflection과 refraction trace: `Raytracer.h`
- Material weight: `Object.h`
- Image load와 sampling: `Texture.cpp`, `Texture.h`
- DirectX11 upload/render: `Example.h`
- Shader: `VS.hlsl`, `PS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `main.cpp` | Win32 window와 DirectX11 실행 loop |
| `Raytracer.h` | Transparent sphere scene, air/glass IOR 전환과 recursive reflection/refraction |
| `Object.h` | Reflection과 transparency material weight |
| `Sphere.h`, `Square.h`, `Triangle.h` | Primitive intersection, outward normal과 UV 계산 |
| `Texture.cpp`, `Texture.h` | PNG texture load와 bilinear sampling |
| `Example.h` | CPU RGBA32F buffer, dynamic texture upload와 full-screen draw |
| `VS.hlsl`, `PS.hlsl` | CPU 결과 canvas texture 표시 |

## 구현 요약

`TraceRefraction`은 `dot(ray.dir, hit.normal)`의 부호로 ray의 진입과 이탈을 구분한다. 진입할 때는 outward normal과 `1 / 1.5`, 이탈할 때는 반전 normal과 `1.5`를 `glm::refract`에 전달한다. 반환 방향이 zero vector이면 total internal reflection으로 보고 reflection path를 사용한다.

Transparent sphere의 transparency는 1.0이고 reflection은 0이므로 local Phong weight는 0이며 refracted result만 사용한다. Miss와 depth 종료는 black을 반환하지만 z=10의 textured Square가 scene background 역할을 한다. 세부 구현과 시각 결과는 [Step13 상세 Demo](../../Docs/03_Demos/Part1_Chapter03/03_13_Transparency.md)에서 확인한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Solution | 존재 | `03_Raytracing_Step13_Transparency.sln` |
| Debug x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Ground texture | 포함 | `part1_chapter03_stone_mosaic.png`, Step10부터 Step12까지 검증 asset과 동일 SHA-256 |
| Background texture | 포함 | `part1_chapter03_ocean_sunset.png`, 사용자 요청으로 생성한 해수면·하늘 asset |
| Capture/Result | 확보 | Sphere 내부의 background 왜곡과 경계 굴절 확인 |

## Capture/Result

![Step13 Transparency result](../../Docs/_assets/captures/part1_chapter03_13_transparency.png)

Sphere 내부에서 background의 수평선과 구름, 수면 반사가 확대되고 휘어진다. 상단과 하단의 겹친 경계는 ray가 sphere의 진입·이탈 surface를 통과한 결과를 보여준다.

## Limitations

- IOR는 air 1.0과 glass 1.5로 고정되며 material별 IOR와 nested medium을 지원하지 않는다.
- Total internal reflection은 `glm::refract`의 zero vector 반환에 의존한다.
- Transparent sphere는 transparency 1.0과 reflection 0을 사용하므로 Fresnel 기반 혼합이 아니다.
- Absorption, tint, rough transmission과 spectral dispersion을 포함하지 않는다.
- Miss와 depth 종료는 black이며 background는 environment map이 아닌 textured Square다.
- Secondary origin은 normal이 아니라 ray direction으로 `1e-4` 이동한다.
- Step12 대비 scene, material, light와 background가 달라 두 capture는 transparency만 바꾼 통제 비교가 아니다.
- Texture와 shader runtime load는 project working directory에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## Related Docs

- [Refraction And Transparency Topic](../../Docs/01_Topics/RayTracing/RefractionAndTransparency.md)
- [Recursive Reflection Topic](../../Docs/01_Topics/RayTracing/RecursiveReflection.md)
- [Texture Sampling Topic](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Verification](../../Docs/02_Verification/Part1_Chapter03/verification-index.md)
- [Step13 상세 Demo](../../Docs/03_Demos/Part1_Chapter03/03_13_Transparency.md)
- [Demo Index](../../Docs/03_Demos/Part1_Chapter03/demo-index.md)
