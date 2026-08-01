# Step9 Shading

## Overview

Step9은 Step8의 CPU software rasterizer에 box topology, face normal과 directional Blinn-Phong shading을 추가한다. Position과 normal을 CPU vertex stage에서 변환하고 perspective-correct barycentric weight로 fragment position과 normal을 보간한 뒤 ambient, diffuse와 specular를 합성한다.

일반적인 Phong과 Blinn-Phong의 차이는 [Phong And Blinn-Phong Topic](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)으로 분리한다. 이 예제의 box 구성, parameter와 시각 결과는 [Step9 상세 Demo](../../Docs/03_Demos/Part2_Chapter04/09_Shading.md)에서 설명한다.

## 실행 진입점

- Solution: `04_Rasterization_Step9_Shading.sln`
- Application entry: `main.cpp`
- 주요 source: `Mesh.cpp`, `MyShader.h`, `Rasterization.cpp`, `Example.cpp`
- Presentation shader: `VertexShader.hlsl`, `PixelShader.hlsl`
- Working directory: 현재 example 폴더
- Application title: `ComputerGraphics - Step9 Shading`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `Mesh.cpp` | 6개 face별 vertex와 normal, 12개 triangle index 구성 |
| `MyShader.h` | CPU position·normal transform과 directional Blinn-Phong 계산 |
| `Rasterization.cpp` | Perspective projection, coverage, position·normal 보간과 depth test |
| `Rasterization.h` | CPU framebuffer 크기, projection 상태와 object·light 보관 |
| `Example.cpp` | CPU framebuffer 갱신, dynamic texture upload와 full-screen presentation |
| `main.cpp` | Win32 render loop와 object, material, light ImGui control |
| `VertexShader.hlsl` | Presentation quad의 position과 UV 전달 |
| `PixelShader.hlsl` | CPU framebuffer texture sampling |

## 구현 요약

Box는 face마다 vertex 네 개를 복제하고 같은 방향의 normal을 부여한다. 이 구성은 모서리에서 normal을 공유하지 않아 각 face가 구분되는 flat-normal 명암을 만든다. CPU vertex stage는 position에 scale, Y·X·Z rotation과 translation을 적용하고 normal에는 rotation만 적용한다.

Rasterizer는 projected triangle의 coverage와 depth를 계산한다. Perspective correction이 활성화된 상태에서는 position과 normal도 reciprocal-depth weight로 보간하고 normal을 다시 정규화한다. CPU pixel stage는 directional light의 반대 방향을 surface-to-light vector로 사용하고 ambient, Lambert diffuse와 half-vector specular를 합성한다. DirectX11 HLSL은 이 CPU 결과를 texture로 표시하는 presentation 경로만 담당한다.

## Capture/Result

![Step9 directional Blinn-Phong shading 전체 창 capture](../../Docs/_assets/captures/part2_chapter04_09_shading.png)

기본 상태는 흰색 top face와 어두운 side face를 통해 face normal과 light 방향의 관계를 보여준다. Scene Control에는 object transform, material과 light direction parameter가 함께 표시된다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Application title | 확인 | `ComputerGraphics - Step9 Shading` |
| Runtime shader load | 확인 | `VertexShader.hlsl`, `PixelShader.hlsl` runtime compile 성공 |
| Default screenshot | 확보 | 1282×992 전체 창 capture, 기술·사용자 시각 검수 완료 |
| Video | 제외 | 고정된 face별 shading 결과는 screenshot으로 설명 가능 |

## Limitations

- Normal transform은 rotation만 적용하므로 non-uniform scale에서 inverse-transpose normal matrix 결과와 다를 수 있다.
- Box는 face별 동일 normal을 사용하므로 smooth vertex normal shading을 보여주지 않는다.
- 현재 specular 구현은 half-vector 항에 `N·L`을 추가로 곱하는 예제 고유 variant다.
- 간소화된 perspective projection은 homogeneous clip space와 near/far clipping을 포함하지 않는다.
- Output color clamp, gamma correction과 tone mapping을 포함하지 않는다.
- Dynamic texture upload는 `Map()` 실패와 mapped `RowPitch` 차이를 별도로 처리하지 않는다.
- Shader file 탐색은 example working directory에 의존한다.

## Related Docs

- [Phong And Blinn-Phong Topic](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
- [Phong Shading Topic](../../Docs/01_Topics/LightingAndShading/PhongShading.md)
- [Perspective Projection Topic](../../Docs/01_Topics/Rasterization/PerspectiveProjection.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../../Docs/03_Demos/Part2_Chapter04/09_Shading.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter04/demo-index.md)
- [Chapter README](../README.md)
