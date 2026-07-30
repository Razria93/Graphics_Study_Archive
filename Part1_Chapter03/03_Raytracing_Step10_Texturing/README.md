# Step10 Texturing

## Overview

이 예제는 triangle hit의 barycentric weight로 UV를 보간하고 CPU에서 image texture를 bilinear sampling한다. Textured Square와 별도 sphere를 같은 closest-hit·Phong shading 경로로 처리한 뒤 DirectX11 texture로 화면에 표시한다.

일반적인 UV와 texture sampling은 [Texture Sampling](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)으로 위임한다. 이 문서는 Step10 코드와 실행 진입점을 설명한다.

## 실행 진입점

- Solution: `03_Raytracing_Step10_Texturing.sln`
- Application entry: `main.cpp`
- Scene과 CPU shading: `Raytracer.h`
- Triangle UV interpolation: `Triangle.h`
- Square composite와 UV seam: `Square.h`
- Image load와 sampling: `Texture.cpp`, `Texture.h`
- DirectX11 upload/render: `Example.h`
- Shader: `VS.hlsl`, `PS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `main.cpp` | Win32 window, DirectX11·ImGui 초기화와 실행 loop |
| `Raytracer.h` | textured Square scene, closest-hit와 diffuse texture sample |
| `Triangle.h` | ray-triangle intersection, barycentric weight와 UV interpolation |
| `Square.h` | 두 child triangle과 공유 UV 구성 |
| `Texture.cpp` | `stb_image` 기반 RGB image load |
| `Texture.h` | UV-to-texel 변환, point/clamp와 bilinear/wrap sampling |
| `Hit.h` | distance, point, normal, UV와 hit object |
| `Object.h` | material과 texture slot |
| `Example.h` | CPU buffer 생성, dynamic texture upload와 full-screen draw |
| `VS.hlsl`, `PS.hlsl` | CPU 결과 canvas texture 표시 |

## 구현 요약

Square의 네 vertex는 image의 좌상단부터 시계 방향으로 `(0,0)`, `(1,0)`, `(1,1)`, `(0,1)` UV를 사용한다. 두 child triangle은 공용 대각선의 vertex와 UV를 공유한다. Triangle hit는 Step9과 같은 barycentric weight로 세 UV를 보간해 `Hit`에 저장한다.

`Texture::SampleLinear`는 UV를 texel center 기준 좌표로 변환하고 네 이웃 pixel을 wrap address 방식으로 bilinear 보간한다. CPU shading은 texture가 있는 object의 diffuse color에 이 sample을 곱한다. HLSL은 원본 JPEG를 sampling하지 않고 CPU가 계산한 RGBA32F canvas를 표시한다.

세부 흐름과 시각 결과는 출처·라이선스가 확인된 capture를 승격한 뒤 상세 Demo로 연결한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Solution | 존재 | `03_Raytracing_Step10_Texturing.sln` |
| Debug x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Input texture | 포함 | `shadertoy_abstract1.jpg`, 출처·라이선스 검토 필요 |
| Capture/Result | 보류 | 외부 입력 texture 권리 gate 미완료 |

## Capture/Result

전체 창 capture 후보는 local 검토 위치에 보관한다. 입력 texture의 출처와 라이선스를 확인하거나 승인된 대체 asset을 적용하기 전에는 tracked capture로 승격하지 않는다.

직접 실행에서는 texture가 원본 방향으로 Square에 표시되고 두 child triangle 경계에서 UV seam이 보이지 않으며, 별도 sphere도 정상적으로 shading된다.

## Limitations

- 입력 JPEG와 shader runtime load는 project working directory에 의존한다.
- 입력 JPEG의 출처와 라이선스가 확인되지 않아 capture와 Publication을 보류한다.
- Active sampling은 bilinear filtering과 wrap address를 고정 사용한다.
- Mipmap과 anisotropic filtering은 포함하지 않는다.
- Degenerate triangle 방어와 adaptive intersection epsilon은 포함하지 않는다.
- CPU 결과는 최초 frame에 한 번 계산한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## Related Docs

- [Texture Sampling Topic](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Barycentric Coordinates Topic](../../Docs/01_Topics/RayTracing/BarycentricCoordinates.md)
- [Intersection Topic](../../Docs/01_Topics/RayTracing/Intersection.md)
- [Phong Shading Topic](../../Docs/01_Topics/LightingAndShading/PhongShading.md)
- [Verification](../../Docs/02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part1_Chapter03/demo-index.md)
