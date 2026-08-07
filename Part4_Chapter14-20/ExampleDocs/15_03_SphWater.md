# Chapter15 Ex1503 SphWater

## Overview

`Ex1503_SphWater`는 dual source에서 particle을 생성하고 CPU SPH update, gravity, boundary collision을 적용해 water-like cluster를 만드는 예제다. `Examples.exe 1503`은 CPU-side density/pressure/viscosity 계산과 structured buffer sprite rendering을 연결한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1503`
- Working directory: `Part4_Chapter14-20` source root
- 주요 source: `Ex1503_SphWater.cpp`, `SphSimulation.cpp`
- Shader: `Ex1503_SphWaterVS.hlsl`, `Ex1503_SphWaterPS.hlsl`, `Ex1501_ParticleSystemGS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L68) | command argument `1503`을 `Ex1503_SphWater` instance에 연결 |
| [Ex1503_SphWater.cpp](../Ex1503_SphWater.cpp#L56) | SPH particle pool과 structured buffer를 준비 |
| [Ex1503_SphWater.cpp](../Ex1503_SphWater.cpp#L80) | dual source spawn, fixed time step, gravity와 boundary collision을 수행 |
| [SphSimulation.cpp](../SphSimulation.cpp#L31) | density, pressure와 viscosity force를 계산 |

## Capture/Result

![Chapter15 SphWater storyboard](../../Docs/_assets/captures/part4_chapter15_03_sph_water.png)

대표 storyboard는 source particle과 boundary 근처 particle accumulation을 보여 준다. frame timestamp와 video provenance는 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Verification 정본 참조 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- SPH pair loop는 CPU에서 수행하며 spatial acceleration structure를 사용하지 않는다.
- fixed time step과 boundary parameter는 예제 안정성 기준이며 일반 purpose fluid solver를 제공하지 않는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter15 Ex1503 SphWater Demo](../../Docs/03_Demos/Part4_Chapter14-20/15_03_SphWater.md)