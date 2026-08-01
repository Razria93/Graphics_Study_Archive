# Step4 Animation2D

## Overview

Step4는 Sun, Earth와 Moon을 10-segment polygonal fan으로 만들고 두 각도를 매 frame 갱신해 계층적 2D orbit을 구성한다. Earth는 Sun 원점을 기준으로 공전하고 Moon은 Earth 주변 local orbit과 Earth의 Sun 기준 공전을 차례로 적용한다.

Step3의 수동 transform 조합을 시간에 따라 갱신되는 상태로 확장한다. 일반 timestep과 계층적 animation 개념은 [2D Animation Topic](../../Docs/01_Topics/AnimationAndPhysics/Animation2D.md)으로 분리한다.

## 실행 진입점

- Solution: `04_Rasterization_Step4_Animation2D.sln`
- Application entry: `main.cpp`
- 주요 source: `Rasterization.cpp`, `Rasterization.h`, `Mesh.cpp`, `Example.cpp`
- Shader: `VertexShader.hlsl`, `PixelShader.hlsl`
- Working directory: 현재 example 폴더
- Application title: `ComputerGraphics - Step4 Animation2D`
- 기본값: Earth angular velocity `0.3`, Moon angular velocity `1.0`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `Mesh.cpp` | Sun, Earth와 Moon의 indexed circle fan 원본 구성 |
| `Rasterization.cpp` | 계층적 orbit transform, 각도 갱신과 CPU triangle rasterization |
| `Rasterization.h` | 천체별 mesh, position, angle과 angular velocity 상태 |
| `Example.cpp` | CPU pixel buffer 갱신, dynamic texture upload와 full-screen presentation |
| `VertexShader.hlsl` | Full-screen quad position과 UV 전달 |
| `PixelShader.hlsl` | CPU 결과 texture sampling |
| `main.cpp` | Orbit parameter UI와 Win32 render loop |

## 구현 요약

Earth vertex는 local position에 `earthPosition`을 더한 뒤 `earthAngle`로 원점 주위 회전한다. Moon vertex는 `moonPosition`과 `moonAngle`로 Earth 기준 local orbit을 만든 다음 `earthPosition`과 `earthAngle`을 적용해 Earth의 Sun 기준 공전을 함께 따른다.

`Update()`는 고정 `dt = 1/30`으로 두 angle을 증가시킨다. CPU rasterizer가 매 frame RGBA32F pixel buffer를 만들고 DirectX11은 dynamic texture와 full-screen quad로 결과를 표시한다. 처리 흐름과 animation 결과는 [Step4 상세 Demo](../../Docs/03_Demos/Part2_Chapter04/04_Animation2D.md)에서 확인한다.

## Capture/Result

대표 전체 창 screenshot과 selected video를 생성하고 자동·기술·사용자 시각 검수를 완료했다.

![Step4 Animation2D](../../Docs/_assets/captures/part2_chapter04_04_animation2d.png)

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Application title | 확인 | `ComputerGraphics - Step4 Animation2D` |
| Hierarchical orbit | 확인 | Sun 고정, Earth 공전과 Moon local orbit 조합 |
| Screenshot/Video | 확보 | 자동·기술·사용자 시각 검수 완료 |

## Limitations

- 고정 `dt = 1/30`을 render loop마다 적용하므로 실제 frame cadence가 30 FPS와 다르면 wall-clock animation 속도도 달라진다.
- Angle은 범위 제한 없이 계속 누적되며 장시간 실행 시 floating-point 정밀도가 낮아질 수 있다.
- Circle은 uniform color이므로 천체 자체의 local rotation과 공전을 시각적으로 분리하지 않는다.
- Dynamic texture upload는 mapped `RowPitch`와 `Map()` 실패를 별도로 처리하지 않는다.
- Shader와 runtime file 탐색은 example working directory에 의존한다.

## Related Docs

- [2D Animation Topic](../../Docs/01_Topics/AnimationAndPhysics/Animation2D.md)
- [2D Transformations Topic](../../Docs/01_Topics/Rasterization/Transformations2D.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../../Docs/03_Demos/Part2_Chapter04/04_Animation2D.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter04/demo-index.md)
- [Chapter README](../README.md)
