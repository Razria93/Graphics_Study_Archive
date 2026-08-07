# Chapter16 Ex1602 CurlNoise

## Overview

`Ex1602_CurlNoise`는 curl-noise compute shader가 structured particle buffer를 갱신하고, sprite accumulation이 colored density trail을 만드는 예제다. `Examples.exe 1602`는 density dissipation과 curl vector update가 이어지는 GPU resource flow를 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1602`
- Working directory: `Part4_Chapter14-20` source root
- Runtime condition: build output runtime DLL 조건은 Verification 정본 참조
- 주요 source: `Ex1602_CurlNoise.cpp`
- Shader: `Ex1602_CurlNoiseCS.hlsl`, `Ex1406_DensityDissipationCS.hlsl`, `Ex1406_SpriteGS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L74) | command argument `1602`를 `Ex1602_CurlNoise` instance에 연결 |
| [Ex1602_CurlNoise.cpp](../Ex1602_CurlNoise.cpp#L21) | particle structured buffer, density texture와 shader를 준비 |
| [Ex1602_CurlNoise.cpp](../Ex1602_CurlNoise.cpp#L74) | density dissipation 후 particle/density UAV curl-noise dispatch를 수행 |
| [Ex1602_CurlNoiseCS.hlsl](../Ex1602_CurlNoiseCS.hlsl#L18) | curl vector를 계산하고 particle position을 갱신 |

## Capture/Result

![Chapter16 CurlNoise storyboard](../../Docs/_assets/captures/part4_chapter16_02_curl_noise.png)

대표 storyboard는 colored curl-noise density trail의 변화를 보여 준다. timestamp와 stability 판단은 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- shader 내부 fixed `dt`와 density dissipation이 trail의 temporal behavior를 결정한다.
- particle lifetime 또는 screen boundary 재진입은 이 update path에서 관리하지 않는다.

## Related Docs

- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter16 Ex1602 CurlNoise Demo](../../Docs/03_Demos/Part4_Chapter14-20/16_02_CurlNoise.md)