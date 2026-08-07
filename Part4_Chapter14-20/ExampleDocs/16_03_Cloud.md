# Chapter16 Ex1603 Cloud

## Overview

`Ex1603_Cloud`는 compute shader로 density Texture3D와 lighting Texture3D를 생성하고 volume ray marching으로 procedural cloud를 합성하는 예제다. `Examples.exe 1603`은 source-root runtime 조건에서 volume data regeneration과 texture-coordinate motion을 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1603`
- Working directory: `Part4_Chapter14-20` source root
- Runtime condition: build output runtime DLL 조건은 Verification 정본 참조
- 주요 source: `Ex1603_Cloud.cpp`
- Shader: `CloudDensityCS.hlsl`, `CloudLightingCS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L77) | command argument `1603`을 `Ex1603_Cloud` instance에 연결 |
| [Ex1603_Cloud.cpp](../Ex1603_Cloud.cpp#L19) | volume model, density/lighting Texture3D와 initial compute pass를 준비 |
| [Ex1603_Cloud.cpp](../Ex1603_Cloud.cpp#L91) | `uvwOffset` update 후 density/lighting field를 다시 생성 |
| [Ex1603_Cloud.cpp](../Ex1603_Cloud.cpp#L137) | volume smoke pipeline으로 cloud volume을 render |

## Capture/Result

![Chapter16 Cloud storyboard](../../Docs/_assets/captures/part4_chapter16_03_cloud.png)

대표 storyboard는 volume render path가 procedural density와 lighting field를 합성한 상태를 보여 준다. timestamp와 lighting 조정은 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- motion은 physical cloud simulation이 아니라 `uvwOffset` 기반 density texture regeneration으로 만든다.
- density와 lighting compute pass를 매 frame 재실행하므로 volume resolution과 ray-march cost에 영향을 받는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter16 Ex1603 Cloud Demo](../../Docs/03_Demos/Part4_Chapter14-20/16_03_Cloud.md)