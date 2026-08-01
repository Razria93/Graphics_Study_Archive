# Step3 Transformations2D

## Overview

Step3은 5-segment polygonal fan의 원본 mesh를 보존하고 현재 UI parameter로 derived vertex buffer를 매 frame 다시 계산한다. `Rotation1 → Scale → Translation1 → Rotation2 → Translation2` 순서로 CPU 좌표를 변환해 non-uniform scale, local orientation과 원점 기준 orbit 이동을 함께 보여준다.

Step2의 32-segment circle과 달리 회전 방향과 non-uniform scale을 쉽게 식별하도록 낮은 segment 수를 사용한다. 일반 2D transform과 조합 순서는 [2D Transformations Topic](../../Docs/01_Topics/Rasterization/Transformations2D.md)으로 분리한다.

## 실행 진입점

- Solution: `04_Rasterization_Step3_Transformations2D.sln`
- Application entry: `main.cpp`
- 주요 source: `Rasterization.cpp`, `Rasterization.h`, `Mesh.cpp`, `Example.cpp`
- Shader: `VertexShader.hlsl`, `PixelShader.hlsl`
- Working directory: 현재 example 폴더
- Application title: `ComputerGraphics - Step3 Transformations2D`
- 기본값: identity transform

## Code Map

| 파일 | 역할 |
| --- | --- |
| `Mesh.cpp` | 5-segment 원본 polygonal fan 구성 |
| `Rasterization.cpp` | 원본 mesh 기반 순차 2D transform과 CPU triangle rasterization |
| `Rasterization.h` | transform parameter, 원본 mesh와 derived buffer 상태 |
| `Example.cpp` | CPU buffer 갱신, dynamic texture upload와 full-screen presentation |
| `VertexShader.hlsl` | full-screen quad position과 UV 전달 |
| `PixelShader.hlsl` | CPU 결과 texture sampling |
| `main.cpp` | Transform UI와 Win32 render loop |

## 구현 요약

`circle.vertices`는 원본 geometry로 유지하고 `Update()`가 각 vertex를 `Rotation1 → Scale X/Y → Translation1 → Rotation2 → Translation2` 순서로 변환해 `vertexBuffer`에 기록한다. 첫 rotation과 scale은 원점 기준 형태를 정하고, `Translation1` 이후의 두 번째 rotation은 이동한 geometry와 offset을 함께 원점 기준으로 회전시킨다. 마지막 `Translation2`가 최종 위치를 정한다.

변환은 CPU의 XY 좌표에서 수행한다. CPU rasterizer가 RGBA32F framebuffer를 만들고 DirectX11은 dynamic texture와 full-screen quad로 결과를 표시한다. 처리 흐름과 capture 비교는 [Step3 상세 Demo](../../Docs/03_Demos/Part2_Chapter04/03_Transformations2D.md)에서 확인한다.

## Capture/Result

![Step3 composed transformations](../../Docs/_assets/captures/part2_chapter04_03_transformations2d_composed.png)

기본 5-segment fan에 rotation, non-uniform scale과 두 단계 translation을 적용한다. 조정 상태는 원본을 매 frame 다시 변환하면서 orientation, aspect와 화면 위치가 함께 바뀌는 결과를 보여준다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | 2026-08-01 현재 확인, example 폴더를 working directory로 사용 |
| Application title | 확인 | `ComputerGraphics - Step3 Transformations2D` |
| Transform UI | 확인 | identity와 composed parameter 상태 비교 |
| Capture/Result | 확보 | 기본·조정 상태 전체 창 capture 사용자 확인 완료 |

## Limitations

- Translation UI는 `vec3`를 노출하지만 Z 값은 2D 화면 결과에 영향을 주지 않는다.
- Scale range는 0과 음수를 포함한다. Scale 0은 degenerate triangle을 만들고 한 축의 음수 scale은 winding을 반전해 현재 edge test에서 geometry가 사라질 수 있다.
- `RotateAboutZ()`는 출력 Z를 0으로 고정하며 이 예제는 XY plane의 2D transform만 다룬다.
- Dynamic texture upload는 mapped `RowPitch`와 `Map()` 실패를 별도로 처리하지 않는다.
- Shader와 runtime file 탐색은 example working directory에 의존한다.

## Related Docs

- [2D Transformations Topic](../../Docs/01_Topics/Rasterization/Transformations2D.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../../Docs/03_Demos/Part2_Chapter04/03_Transformations2D.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter04/demo-index.md)
- [Chapter README](../README.md)
