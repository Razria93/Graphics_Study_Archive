# Chapter16 Ex1605 SmokeCpu

## Overview

`Ex1605_SmokeCpu`는 CPU fluid simulation이 계산한 3D density grid를 매 frame GPU Texture3D로 upload하고 volume ray marching으로 smoke-like field를 표시하는 예제다. `Examples.exe 1605`는 GPU compute simulation이 아닌 CPU update와 upload 비용 경로를 비교 기준으로 둔다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1605`
- Working directory: `Part4_Chapter14-20` source root
- Runtime asset: HDRI cubemap files, 원본 asset은 직접 게시하지 않음
- 주요 source: `Ex1605_SmokeCpu.cpp`, `FluidSimulationCPU.h`
- Shader: `VolumeSmokePS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L83) | command argument `1605`를 `Ex1605_SmokeCpu` instance에 연결 |
| [Ex1605_SmokeCpu.cpp](../Ex1605_SmokeCpu.cpp#L15) | CPU fluid grid와 GPU density Texture3D, volume model을 준비 |
| [Ex1605_SmokeCpu.cpp](../Ex1605_SmokeCpu.cpp#L48) | CPU fluid update 뒤 density array를 Texture3D로 upload |
| [FluidSimulationCPU.h](../FluidSimulationCPU.h#L42) | CPU source, projection과 advection substep을 수행 |
| [Ex1605_SmokeCpu.cpp](../Ex1605_SmokeCpu.cpp#L61) | uploaded density texture를 volume smoke pipeline으로 render |

## Capture/Result

![Chapter16 SmokeCpu storyboard](../../Docs/_assets/captures/part4_chapter16_05_smoke_cpu.png)

대표 storyboard는 CPU density grid가 Texture3D upload 뒤 volume render path에서 표시되는 결과다. timestamp와 HDRI provenance는 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- CPU array update와 full density upload는 grid resolution이 커질수록 simulation과 transfer 비용을 함께 증가시킨다.
- volume render는 GPU에서 수행하지만 fluid solve 자체는 CPU path를 사용한다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter16 Ex1605 SmokeCpu Demo](../../Docs/03_Demos/Part4_Chapter14-20/16_05_SmokeCpu.md)