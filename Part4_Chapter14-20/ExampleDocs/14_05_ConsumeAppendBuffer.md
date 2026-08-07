# Chapter14 Ex1405 ConsumeAppendBuffer

## Overview

`Ex1405_ConsumeAppendBuffer`는 consume buffer의 particle을 compute shader에서 읽어 append buffer에 기록하고, append counter를 draw count로 사용하는 예제다. `Examples.exe 1405`는 UAV counter 초기화, `CopyStructureCount`, CPU download와 매 frame buffer role swap을 연결한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1405`
- 주요 source: `Ex1405_ConsumeAppendBuffer.cpp`
- Shader: `Ex1405_ConsumeAppendCS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L50) | command argument `1405`를 `Ex1405_ConsumeAppendBuffer` instance에 연결 |
| [Ex1405_ConsumeAppendBuffer.cpp](../Ex1405_ConsumeAppendBuffer.cpp#L26) | consume/append buffer와 counter staging buffer를 준비 |
| [Ex1405_ConsumeAppendBuffer.cpp](../Ex1405_ConsumeAppendBuffer.cpp#L69) | UAV counter 초기화, compute dispatch와 barrier를 수행 |
| [Ex1405_ConsumeAppendBuffer.cpp](../Ex1405_ConsumeAppendBuffer.cpp#L98) | append counter를 download해 draw count로 사용하고 buffer 역할을 교체 |

## Capture/Result

![Chapter14 ConsumeAppendBuffer](../../Docs/_assets/captures/part4_chapter14_05_consume_append_buffer.png)

tracked screenshot 후보의 point cloud와 `AppendBuffer count: 25600` stdout을 함께 evidence로 사용한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-06 직접 확인 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | tracked 후보 + stdout | 1280x1280 point cloud와 append count |

## Limitations

- 현재 구현은 append counter를 CPU staging buffer로 내려받은 뒤 draw call에 다시 전달한다.
- CPU readback 없이 GPU argument buffer를 사용하는 흐름은 `Ex1407_IndirectArguments`에서 다룬다.

## Related Docs

- [Chapter14-20 README](../README.md)
- [Compute Shader And Resource Flow](../../Docs/01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter14 Ex1405 ConsumeAppendBuffer Demo](../../Docs/03_Demos/Part4_Chapter14-20/14_05_ConsumeAppendBuffer.md)
- [Publication Candidate List](../../Docs/05_Publication/candidate-list.md)