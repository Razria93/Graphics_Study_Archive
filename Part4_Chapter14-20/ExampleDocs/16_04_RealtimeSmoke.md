# Chapter16 Ex1604 RealtimeSmoke

## Overview

`Ex1604_RealtimeSmoke`는 GPU Texture3D velocity와 density field를 projection, difference upsample, advection으로 갱신하고 volume ray marching으로 smoke를 그리는 예제다. `Examples.exe 1604`는 GPU compute simulation과 HDRI가 포함된 rendered evidence를 분리해 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1604`
- Working directory: `Part4_Chapter14-20` source root
- Runtime asset: HDRI cubemap files, 원본 asset은 직접 게시하지 않음
- 주요 source: `Ex1604_RealtimeSmoke.cpp`
- Shader: `Ex1604_SourcingCS.hlsl`, `Ex1604_JacobiCS.hlsl`, `Ex1604_AdvectionCS.hlsl`, `VolumeSmokePS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L80) | command argument `1604`를 `Ex1604_RealtimeSmoke` instance에 연결 |
| [Ex1604_RealtimeSmoke.cpp](../Ex1604_RealtimeSmoke.cpp#L15) | low/high-resolution 3D field와 volume rendering resource를 준비 |
| [Ex1604_RealtimeSmoke.cpp](../Ex1604_RealtimeSmoke.cpp#L170) | downsample, source, projection, difference upsample, advection substep을 수행 |
| [Ex1604_RealtimeSmoke.cpp](../Ex1604_RealtimeSmoke.cpp#L221) | divergence와 Jacobi pressure iteration으로 projection을 수행 |
| [Ex1604_RealtimeSmoke.cpp](../Ex1604_RealtimeSmoke.cpp#L316) | high-resolution density Texture3D를 volume smoke pipeline에 연결 |

## Capture/Result

![Chapter16 RealtimeSmoke storyboard](../../Docs/_assets/captures/part4_chapter16_04_realtime_smoke.png)

대표 storyboard는 GPU density field를 volume rendering한 결과다. timestamp와 HDRI rendered evidence의 provenance는 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- `DiffUpSample`은 independent diffusion solve가 아니라 projection 전후 low-resolution field 차이를 high-resolution field에 반영한다.
- volume quality는 ray-march step, density absorption, light와 anisotropy parameter에 의존한다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter16 Ex1604 RealtimeSmoke Demo](../../Docs/03_Demos/Part4_Chapter14-20/16_04_RealtimeSmoke.md)