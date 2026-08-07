# Chapter16 Ex1601 StableFluids

## Overview

`Ex1601_StableFluids`는 mouse position과 left-button input을 2D stable fluids의 density/velocity source로 주입하고 compute pipeline 결과를 back buffer에 표시하는 예제다. `Examples.exe 1601`은 source-root working directory와 runtime DLL 조건에서 interaction-driven density field를 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1601`
- Working directory: `Part4_Chapter14-20` source root
- Runtime condition: build output runtime DLL 조건은 Verification 정본 참조
- 주요 source: `Ex1601_StableFluids.cpp`, `StableFluids.cpp`
- Shader: `Ex1601_SourcingCS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L71) | command argument `1601`을 `Ex1601_StableFluids` instance에 연결 |
| [Ex1601_StableFluids.cpp](../Ex1601_StableFluids.cpp#L29) | mouse position, press event와 drag velocity를 source constants에 기록 |
| [StableFluids.cpp](../StableFluids.cpp#L15) | stable-fluid resources와 compute update pipeline을 초기화 |
| [StableFluids.cpp](../StableFluids.cpp#L76) | sourcing, diffusion, projection, advection pass를 호출 |

## Capture/Result

![Chapter16 StableFluids storyboard](../../Docs/_assets/captures/part4_chapter16_01_stable_fluids.png)

대표 storyboard는 source injection 뒤 color density field가 변하는 interaction 상태를 보여 준다. frame timestamp와 capture 조건은 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | interaction representative visual |

## Limitations

- mouse input이 source 위치와 velocity를 결정하므로 같은 initial condition의 정량 비교를 제공하지 않는다.
- simulation은 2D texture field 기반이며 3D volume fluid rendering을 수행하지 않는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter16 Ex1601 StableFluids Demo](../../Docs/03_Demos/Part4_Chapter14-20/16_01_StableFluids.md)