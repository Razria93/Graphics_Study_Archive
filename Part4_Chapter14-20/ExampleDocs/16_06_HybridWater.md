# Chapter16 Ex1606 HybridWater

## Overview

`Ex1606_HybridWater`는 grid velocity projection과 particle step을 결합하고, sorted particle을 grid density와 signed-distance field로 변환해 volume 또는 raycast surface로 표시하는 예제다. `Examples.exe 1606`은 GPU particle-grid hybrid data flow와 rendering toggle의 책임을 구분한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1606`
- Working directory: `Part4_Chapter14-20` source root
- Runtime condition: build output runtime DLL 조건은 Verification 정본 참조
- 주요 source: `Ex1606_HybridWater.cpp`
- Shader: `Ex1606_ParticleStepCS.hlsl`, `Ex1606_ParticleToGridCS.hlsl`, `Ex1606_SignedDistancePS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L86) | command argument `1606`을 `Ex1606_HybridWater` instance에 연결 |
| [Ex1606_HybridWater.cpp](../Ex1606_HybridWater.cpp#L17) | grid Texture3D, particle buffer, bitonic sort와 rendering resource를 준비 |
| [Ex1606_HybridWater.cpp](../Ex1606_HybridWater.cpp#L199) | grid projection과 particle step을 호출 |
| [Ex1606_HybridWater.cpp](../Ex1606_HybridWater.cpp#L334) | particle sort, first index, particle-to-grid density/SDF dispatch를 수행 |
| [Ex1606_HybridWater.cpp](../Ex1606_HybridWater.cpp#L375) | density volume, particles, marching cubes, SDF raycasting render branch를 선택 |

## Capture/Result

![Chapter16 HybridWater storyboard](../../Docs/_assets/captures/part4_chapter16_06_hybrid_water.png)

대표 storyboard는 signed-distance raycasting surface와 density volume display를 보여 준다. timestamp와 rendering branch 해석은 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- `RenderDensity`는 density Texture3D visualization toggle이며 particle physics 또는 material mode를 바꾸지 않는다.
- `m_upScale`은 `1`이므로 이름에 `Up`이 있는 resource가 별도 upsampling 구현을 뜻하지 않는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter16 Ex1606 HybridWater Demo](../../Docs/03_Demos/Part4_Chapter14-20/16_06_HybridWater.md)