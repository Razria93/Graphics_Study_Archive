# Part4 Chapter14-20

Compute shader, simulation, animation, foliage, physics, gameplay 예제를 정리한 Part4 archive 폴더입니다.

Part4 source는 예제별 solution이 아니라 `Examples` 단일 Visual Studio project 안에 `Ex1401`-`Ex2001` 파일이 모인 구조다. Primary와 reference-only baseline의 관계는 [`SRC-P4-C14-20`](../Docs/99_Legacy/source-registry.md)으로 추적한다.

## 상태

- 학습 코드 정리: import 완료
- Build/run: Chapter14 Ex1401-Ex1408과 Chapter15 Ex1501-Ex1503 Debug x64 현재 확인, Chapter16-20과 Release 현재 재검증 필요
- 캡처: Chapter14 tracked capture 확보, Chapter15 Ex1501-Ex1503 local 후보 확보, Chapter16-20 capture 후속

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P4-C14-20`](../Docs/99_Legacy/source-registry.md) |
| Import status | 반영 완료 |
| Public readiness | 검토 필요 |
| Build/run status | Chapter14 Debug x64 현재 확인 · Chapter15 Debug x64 smoke 확인 · Chapter16-20과 Release 재검증 필요 |
| Next action | Chapter15 evidence 승격 범위와 `flare0.dds` public risk 판단 |

## 예정 주제

- Compute shader basics
- Structured buffers
- Particle systems
- SPH water, stable fluids, smoke, cloud demos
- Skeletal animation
- Foliage, landscape/ocean
- PhysX and gameplay integration

## Chapter14 Compute Shader 기준

Chapter14는 compute shader의 기본 dispatch에서 structured buffer, append/consume buffer, indirect draw와 GPU sort로 확장되는 흐름이다. 현재 작업에서는 `Ex1401`-`Ex1408` Debug x64 build/run을 확인하고, `Ex1402`, `Ex1404`-`Ex1407` tracked capture와 `Ex1403`, `Ex1405`, `Ex1408` stdout evidence를 정본 문서에 연결한다.

| Example | Command argument | 핵심 개념 | Evidence 후보 | 비고 |
| --- | --- | --- | --- | --- |
| `Ex1401_Basic` | `1401` | back buffer UAV, compute dispatch, thread group | screenshot | asset 없음. 최소 compute visual 후보 |
| `Ex1402_Blur` | `1402` | separable blur, SRV/UAV ping-pong, compute barrier | screenshot | compute blur 대표 visual 후보 |
| `Ex1403_MatVecMult` | `1403` | matrix-vector multiplication, GPU result download, CPU/GPU compare | console output | 렌더링 없이 `exit(0)`로 종료하는 result compare 예제 |
| `Ex1404_StructuredBuffer` | `1404` | `RWStructuredBuffer`, `SV_VertexID`, point rendering | screenshot | structured buffer update/render 기준 후보 |
| `Ex1405_ConsumeAppendBuffer` | `1405` | consume/append counter, `CopyStructureCount`, append count draw | screenshot + console output | `AppendBuffer count: 25600` 확인 |
| `Ex1406_DensityField` | `1406` | density texture, sprite geometry shader, accumulate blend | screenshot | density trail visual 후보 |
| `Ex1407_IndirectArguments` | `1407` | indirect argument buffer, `DrawInstancedIndirect` | screenshot | Ex1406 visual 흐름에 indirect draw call을 결합 |
| `Ex1408_BitonicSort` | `1408` | bitonic sort, structured buffer GPU sort, CPU/GPU compare | console output | 렌더링 없이 `exit(0)`로 종료하는 result compare 예제 |

## 문서

- [Part4 Verification](../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Part4 Demo Index](../Docs/03_Demos/Part4_Chapter14-20/demo-index.md)
- [Compute And Simulation Topic Index](../Docs/01_Topics/ComputeAndSimulation/topic-index.md)
- [Part4 source provenance](../Docs/99_Legacy/source-registry.md)

