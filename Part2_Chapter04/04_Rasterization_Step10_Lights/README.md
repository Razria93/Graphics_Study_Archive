# Step10 Lights

## Overview

Step10은 Step9의 CPU Blinn-Phong shading 경로에 Directional, Point와 Spot Light를 추가한다. 같은 geometry, material과 view 조건에서 surface-to-light vector, distance attenuation과 spot factor를 바꾸어 공간적 Light model이 최종 fragment color에 미치는 차이를 비교한다.

일반적인 Light type과 감쇠 개념은 [Light Types Topic](../../Docs/01_Topics/LightingAndShading/LightTypes.md)으로 분리한다. 이 예제의 구현 흐름과 세 Light 결과 비교는 [Step10 상세 Demo](../../Docs/03_Demos/Part2_Chapter04/10_Lights.md)에서 설명한다.

## 실행 진입점

- Solution: `04_Rasterization_Step10_Lights.sln`
- Application entry: `main.cpp`
- 주요 source: `Mesh.h`, `MyShader.h`, `Rasterization.cpp`, `Example.cpp`
- Presentation shader: `VertexShader.hlsl`, `PixelShader.hlsl`
- Working directory: 현재 example 폴더
- Application title: `ComputerGraphics - Step10 Lights`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `Mesh.h` | Material과 Directional·Point·Spot 공통 Light parameter 정의 |
| `MyShader.h` | CPU Blinn-Phong, distance attenuation과 Light type별 계산 |
| `Rasterization.cpp` | Perspective-correct position·normal 보간과 CPU constants 설정 |
| `Rasterization.h` | CPU framebuffer, object, Light와 `lightType` 상태 보관 |
| `Example.cpp` | CPU framebuffer 갱신, dynamic texture upload와 full-screen presentation |
| `main.cpp` | Win32 render loop와 Light type·parameter ImGui control |
| `VertexShader.hlsl` | Presentation quad의 position과 UV 전달 |
| `PixelShader.hlsl` | CPU framebuffer texture sampling |

## 구현 요약

Directional Light는 저장된 진행 방향의 반대를 surface-to-light vector로 사용한다. Point Light는 world position에서 Light position까지의 방향과 거리를 구하고 `fallOffStart`와 `fallOffEnd` 사이에서 선형 감쇠한다. Spot Light는 Point Light의 거리 감쇠에 Light 진행 방향과 light-to-surface 방향의 내적을 `spotPower`만큼 거듭제곱한 cone factor를 추가한다.

세 경로는 같은 CPU Blinn-Phong 함수로 ambient, diffuse와 specular를 합성한다. Rasterizer는 perspective-correct barycentric weight로 world position과 normal을 보간하며 DirectX11 HLSL은 CPU 결과 texture를 화면에 표시하는 presentation만 담당한다.

## Capture/Result

![Step10 Point Light 전체 창 capture](../../Docs/_assets/captures/part2_chapter04_10_lights_point.png)

기본 Point Light는 `(0, 0.5, 0.5)` 위치에서 넓은 radial highlight와 거리 감쇠를 만든다. Directional·Point·Spot의 동일 조건 비교는 상세 Demo의 세 capture로 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Application title | 확인 | `ComputerGraphics - Step10 Lights` |
| Runtime shader load | 확인 | `VertexShader.hlsl`, `PixelShader.hlsl` runtime compile 성공 |
| Light type | 확인 | Directional·Point·Spot 전환과 결과 차이 확인 |
| Screenshot | 확보 | 1282×992 전체 창 capture 3장, 기술·사용자 시각 검수 완료 |
| Video | 제외 | 세 이산 상태는 screenshot 비교로 설명 가능 |

## Limitations

- `fallOffStart`와 `fallOffEnd`가 같으면 attenuation 분모가 0이 된다.
- Point·Spot Light position과 fragment position이 같으면 방향 정규화에서 0으로 나눌 수 있다.
- Point·Spot 경계와 Spot cone 밖에서도 material ambient가 남아 cutoff가 물리적으로 연속적이지 않다.
- Normal transform은 rotation만 적용하므로 일반 mesh의 non-uniform scale에서 inverse-transpose normal matrix 결과와 다를 수 있다.
- Dynamic texture upload는 `Map()` 실패와 mapped `RowPitch` 차이를 별도로 처리하지 않는다.
- Near/far clipping, output clamp, gamma correction과 tone mapping을 포함하지 않는다.
- Shader file 탐색은 example working directory에 의존한다.

## Related Docs

- [Light Types Topic](../../Docs/01_Topics/LightingAndShading/LightTypes.md)
- [Phong And Blinn-Phong Topic](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../../Docs/03_Demos/Part2_Chapter04/10_Lights.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter04/demo-index.md)
- [Chapter README](../README.md)
