# Chapter14 Ex1404 StructuredBuffer

## Overview

`Ex1404_StructuredBuffer`는 25600개 particle의 position/color를 custom structured buffer에 올리고, compute shader가 UAV로 위치를 갱신한 뒤 vertex shader가 같은 resource를 SRV로 읽어 point cloud를 그리는 예제다. `Examples.exe 1404`는 vertex buffer 없이 structured buffer 기반 draw를 확인한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1404`
- 주요 source: `Ex1404_StructuredBuffer.cpp`
- Shader: `Ex1404_StructuredBufferCS.hlsl`, `Ex1404_StructuredBufferVS.hlsl`, `Ex1404_StructuredBufferPS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L47) | command argument `1404`를 `Ex1404_StructuredBuffer` instance에 연결 |
| [Ex1404_StructuredBuffer.cpp](../Ex1404_StructuredBuffer.cpp#L26) | deterministic particle data와 custom structured buffer, shader를 준비 |
| [Ex1404_StructuredBuffer.cpp](../Ex1404_StructuredBuffer.cpp#L80) | UAV compute update 뒤 SRV point-list draw를 수행 |
| [Ex1404_StructuredBufferCS.hlsl](../Ex1404_StructuredBufferCS.hlsl#L1) | particle position을 갱신하는 `RWStructuredBuffer` compute shader |

## Capture/Result

![Chapter14 StructuredBuffer](../../Docs/_assets/captures/part4_chapter14_04_structured_buffer.png)

1280x1280 centered client-visible tracked screenshot 후보에서 structured buffer particle point cloud를 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-06 직접 확인 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | tracked 후보 | taskbar-free 1280x1280 point cloud capture |

## Limitations

- static screenshot은 particle motion의 시간 변화를 설명하지 않으며, 동작 흐름은 상세 Demo에 둔다.
- particle 수와 update rule은 예제의 fixed configuration이며 범용 particle system API를 제공하지 않는다.

## Related Docs

- [Chapter14-20 README](../README.md)
- [Compute Shader And Resource Flow](../../Docs/01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter14 Ex1404 StructuredBuffer Demo](../../Docs/03_Demos/Part4_Chapter14-20/14_04_StructuredBuffer.md)
- [Publication Candidate List](../../Docs/05_Publication/candidate-list.md)