# Step11 Supersampling

## Overview

이 예제는 160×90 output cell마다 화면 영역을 재귀적으로 2×2 분할하고 64개 primary ray의 shading 결과를 평균한다. 평균한 CPU 결과는 DirectX11 point sampler로 1280×720 window에 확대해 표시하며, 규칙적인 subpixel sampling과 저해상도 출력의 trade-off를 함께 보여준다.

일반적인 spatial aliasing과 supersampling은 [Sampling And Anti Aliasing](../../Docs/01_Topics/RayTracing/SamplingAndAntiAliasing.md)으로 위임한다. 이 문서는 Step11 코드와 실행 진입점을 설명한다.

## 실행 진입점

- Solution: `03_Raytracing_Step11_Supersampling.sln`
- Application entry: `main.cpp`
- Scene, shading과 recursive sampling: `Raytracer.h`
- Triangle UV interpolation: `Triangle.h`
- Image load와 sampling: `Texture.cpp`, `Texture.h`
- DirectX11 upload/render: `Example.h`
- Shader: `VS.hlsl`, `PS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `main.cpp` | Win32 window와 DirectX11 실행 loop |
| `Raytracer.h` | 160×90 scene, depth 3의 재귀 2×2 sampling과 64-sample 평균 |
| `Triangle.h`, `Square.h`, `Sphere.h` | leaf ray의 primitive intersection과 UV 계산 |
| `Texture.cpp`, `Texture.h` | 석재 PNG load와 bilinear sampling |
| `Example.h` | CPU RGBA32F buffer, dynamic texture upload와 point-upscaled full-screen draw |
| `VS.hlsl`, `PS.hlsl` | CPU 결과 canvas texture 표시 |

## 구현 요약

`Raytracer`는 1280×720 client 크기를 각 축에서 8로 나눈 160×90 output grid를 사용한다. `TraceRay2x2`는 한 output cell을 depth 3까지 재귀 분할하므로 8×8 규칙 grid의 leaf ray 64개를 만들고, 각 단계에서 네 child color를 평균한다. 총 primary ray 수는 `160 × 90 × 64 = 921,600`이다.

각 leaf ray는 sphere와 두 triangle으로 구성한 Square의 closest hit를 찾고 ambient, diffuse texture와 specular shading을 계산한다. DirectX11 swap chain과 canvas texture의 sample count는 1이므로 이 과정은 GPU MSAA가 아니라 CPU spatial supersampling이다. 세부 구현과 시각 결과는 [Step11 상세 Demo](../../Docs/03_Demos/Part1_Chapter03/11_Supersampling.md)에서 확인한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Solution | 존재 | `03_Raytracing_Step11_Supersampling.sln` |
| Debug x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Input texture | 포함 | `part1_chapter03_stone_mosaic.png`, Step10 검증 asset과 동일 SHA-256 |
| Capture/Result | 확보 | 전체 application window에서 64-sample 평균과 8배 point upscale 확인 |

## Capture/Result

![Step11 Supersampling result](../../Docs/_assets/captures/part1_chapter03_11_supersampling.png)

석재 Square와 sphere가 160×90 grid에서 계산된 뒤 1280×720 viewport에 확대된다. 큰 pixel block은 낮은 output resolution을 보여주고, sphere silhouette와 texture 경계의 중간 color는 각 cell에서 64개 sample을 평균한 coverage를 보여준다.

## Limitations

- 160×90 결과를 point sampling으로 8배 확대하므로 최종 화면의 공간 해상도가 낮다.
- Sampling depth는 3으로 고정되며 runtime parameter와 적용 전·후 전환 UI가 없다.
- 규칙적인 8×8 grid와 box average만 사용하며 jitter, adaptive sampling과 reconstruction filter는 포함하지 않는다.
- Step10 대비 sphere 크기와 Square ambient도 달라 두 Step의 capture는 supersampling만 바꾼 통제 비교가 아니다.
- Texture와 shader runtime load는 project working directory에 의존한다.
- CPU 결과는 최초 frame에 한 번 계산한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.

## Related Docs

- [Sampling And Anti Aliasing Topic](../../Docs/01_Topics/RayTracing/SamplingAndAntiAliasing.md)
- [Texture Sampling Topic](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Intersection Topic](../../Docs/01_Topics/RayTracing/Intersection.md)
- [Verification](../../Docs/02_Verification/Part1_Chapter03/verification-index.md)
- [Step11 상세 Demo](../../Docs/03_Demos/Part1_Chapter03/11_Supersampling.md)
- [Demo Index](../../Docs/03_Demos/Part1_Chapter03/demo-index.md)
