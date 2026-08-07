# Chapter14 Ex1406 DensityField

## Overview

`Ex1406_DensityField`는 particle structured buffer와 density texture를 compute shader로 갱신하고 sprite draw의 accumulate blend로 colored density trail을 만드는 예제다. `Examples.exe 1406`은 density dissipation, particle sourcing, geometry shader sprite draw의 순서를 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1406`
- 주요 source: `Ex1406_DensityField.cpp`
- Shader: `Ex1406_DensitySourcingCS.hlsl`, `Ex1406_DensityDissipationCS.hlsl`, `Ex1406_SpriteGS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L53) | command argument `1406`을 `Ex1406_DensityField` instance에 연결 |
| [Ex1406_DensityField.cpp](../Ex1406_DensityField.cpp#L21) | rainbow particle buffer, float density texture와 shader를 준비 |
| [Ex1406_DensityField.cpp](../Ex1406_DensityField.cpp#L84) | dissipation, advection, sprite draw와 back buffer copy 순서를 수행 |
| [Ex1406_DensityField.cpp](../Ex1406_DensityField.cpp#L103) | density texture와 particle UAV를 compute shader에서 갱신 |
| [Ex1406_DensityField.cpp](../Ex1406_DensityField.cpp#L142) | geometry shader sprite와 accumulate blend로 trail을 누적 |

## Capture/Result

![Chapter14 DensityField](../../Docs/_assets/captures/part4_chapter14_06_density_field.png)

1024x1024 centered client-visible tracked screenshot 후보에서 colored density trail을 확인한다. 시간 변화는 static image가 아닌 별도 video 후보로 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-06 직접 확인 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | tracked 후보 | 1024x1024 density trail capture |

## Limitations

- static screenshot은 dissipation과 trail accumulation의 시간 변화를 충분히 표현하지 않는다.
- particle 수와 density field resolution은 예제의 fixed configuration이며 fluid simulation solver 전체를 제공하지 않는다.

## Related Docs

- [Chapter14-20 README](../README.md)
- [Gpu Particle And Fluid Simulation](../../Docs/01_Topics/ComputeAndSimulation/GpuParticleAndFluidSimulation.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter14 Ex1406 DensityField Demo](../../Docs/03_Demos/Part4_Chapter14-20/14_06_DensityField.md)
- [Publication Candidate List](../../Docs/05_Publication/candidate-list.md)