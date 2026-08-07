# Chapter15 Ex1501 ParticleSystem

## Overview

`Ex1501_ParticleSystem`은 fixed-size CPU particle pool을 spawn, gravity, collision으로 갱신한 뒤 structured buffer를 통해 geometry shader sprite로 그리는 예제다. `Examples.exe 1501`은 CPU simulation과 GPU sprite rendering의 역할 분리를 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1501`
- Working directory: `Part4_Chapter14-20` source root
- 주요 source: `Ex1501_ParticleSystem.cpp`
- Shader: `Ex1501_ParticleSystemVS.hlsl`, `Ex1501_ParticleSystemPS.hlsl`, `Ex1501_ParticleSystemGS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L62) | command argument `1501`을 `Ex1501_ParticleSystem` instance에 연결 |
| [Ex1501_ParticleSystem.cpp](../Ex1501_ParticleSystem.cpp#L61) | fixed particle pool과 GPU/staging structured buffer를 준비 |
| [Ex1501_ParticleSystem.cpp](../Ex1501_ParticleSystem.cpp#L88) | spawn, gravity, life, wall/ground collision을 CPU에서 갱신 |
| [Ex1501_ParticleSystem.cpp](../Ex1501_ParticleSystem.cpp#L231) | structured buffer SRV를 geometry shader sprite draw에 연결 |

## Capture/Result

![Chapter15 ParticleSystem storyboard](../../Docs/_assets/captures/part4_chapter15_01_particle_system.png)

대표 storyboard는 particle source, velocity variation, gravity와 collision이 만든 stream shape를 보여 준다. timestamp와 source video provenance는 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Verification 정본 참조 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- particle simulation은 compute shader가 아니라 CPU update 후 structured buffer upload로 수행한다.
- fixed pool은 inactive particle을 재활성화하며 동적 capacity management를 제공하지 않는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter15 Ex1501 ParticleSystem Demo](../../Docs/03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md)