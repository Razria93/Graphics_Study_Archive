# Chapter15 Ex1502 SpriteFireEffect

## Overview

`Ex1502_SpriteFireEffect`는 CPU particle pool에 buoyancy를 적용하고 textured sprite를 accumulate blend로 그려 fire-like effect를 만드는 예제다. `Examples.exe 1502`는 runtime sprite texture binding과 rendered storyboard evidence를 분리해 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1502`
- Working directory: `Part4_Chapter14-20` source root
- Runtime asset: `../Assets/Textures/flare0.dds`
- 주요 source: `Ex1502_SpriteFireEffect.cpp`
- Shader: `Ex1502_SpriteFireEffectVS.hlsl`, `Ex1502_SpriteFireEffectPS.hlsl`, `Ex1501_ParticleSystemGS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L65) | command argument `1502`를 `Ex1502_SpriteFireEffect` instance에 연결 |
| [Ex1502_SpriteFireEffect.cpp](../Ex1502_SpriteFireEffect.cpp#L44) | particle structured buffer와 staging buffer를 준비 |
| [Ex1502_SpriteFireEffect.cpp](../Ex1502_SpriteFireEffect.cpp#L66) | runtime `flare0.dds` sprite texture를 SRV로 로드 |
| [Ex1502_SpriteFireEffect.cpp](../Ex1502_SpriteFireEffect.cpp#L72) | source spawn, buoyancy, life update를 CPU에서 수행 |
| [Ex1502_SpriteFireEffect.cpp](../Ex1502_SpriteFireEffect.cpp#L155) | texture SRV와 sampler를 pixel shader sprite draw에 연결 |

## Capture/Result

![Chapter15 SpriteFireEffect storyboard](../../Docs/_assets/captures/part4_chapter15_02_sprite_fire_effect.png)

대표 storyboard는 fire-like particle effect의 rendered evidence다. 원본 `flare0.dds`는 직접 링크하거나 공개 asset으로 주장하지 않는다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Verification 정본 참조 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | tracked storyboard | rendered evidence만 사용 |

## Limitations

- particle simulation은 CPU update 후 structured buffer upload로 수행한다.
- `flare0.dds` runtime asset은 실행 전제이며 원본 asset의 공개 가능성을 보장하지 않는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter15 Ex1502 SpriteFireEffect Demo](../../Docs/03_Demos/Part4_Chapter14-20/15_02_SpriteFireEffect.md)