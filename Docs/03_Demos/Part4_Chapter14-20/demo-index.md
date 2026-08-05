# Part4_Chapter14-20 Demo Index

이 문서는 `Part4_Chapter14-20`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: compute shader, simulation, animation, foliage, physics, gameplay 후보
- 비고: Chapter14 tracked capture/result는 확보했으며 Chapter15~20, video와 desktop 재촬영 후보는 후속 검토 범위다.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Ex1401 Basic](14_01_Basic.md) | `Ex1401_Basic` | Compute Shader | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local 후보 | 미게시 | 후보 | Chapter14 최소 set 후보. 2026-08-06 Debug x64 checker screenshot 후보 확보. tracked 승격 전 fixed UI와 bounds 기준으로 desktop 재촬영 필요 |
| 대표 capture | [Ex1406 DensityField](14_06_DensityField.md) | `Ex1406_DensityField` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | [tracked capture](../../_assets/captures/part4_chapter14_06_density_field.png) | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | Chapter14 대표 density visual 후보. 시간 변화는 desktop video 후보 |
| Ex1402 blur visual | [Ex1402 Blur](14_02_Blur.md) | `Ex1402_Blur` | Compute Shader | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | [tracked capture](../../_assets/captures/part4_chapter14_02_blur.png) | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | 5000ms 안정화, collapsed UI, centered client-visible 1280×768 capture를 승격 |
| Ex1403 result compare | [Ex1403 MatVecMult](14_03_MatVecMult.md) | `Ex1403_MatVecMult` | Compute Shader | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local stdout 후보 | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | CPU/GPU matrix-vector compare와 `ExitCode: 0`을 evidence로 사용하고 screenshot은 불필요 |
| Ex1404 structured buffer | [Ex1404 StructuredBuffer](14_04_StructuredBuffer.md) | `Ex1404_StructuredBuffer` | Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | [tracked capture](../../_assets/captures/part4_chapter14_04_structured_buffer.png) | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | StructuredBuffer SRV/UAV update와 point draw evidence |
| Ex1405 consume/append | [Ex1405 ConsumeAppendBuffer](14_05_ConsumeAppendBuffer.md) | `Ex1405_ConsumeAppendBuffer` | Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | [tracked capture](../../_assets/captures/part4_chapter14_05_consume_append_buffer.png) + stdout | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | Append counter와 `AppendBuffer count: 25600` evidence |
| Ex1407 indirect draw | [Ex1407 IndirectArguments](14_07_IndirectArguments.md) | `Ex1407_IndirectArguments` | Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | [tracked capture](../../_assets/captures/part4_chapter14_07_indirect_arguments.png) + code evidence | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | Visual은 Ex1406과 유사하므로 `DrawInstancedIndirect` code evidence를 병행 |
| Ex1408 bitonic sort | [Ex1408 BitonicSort](14_08_BitonicSort.md) | `Ex1408_BitonicSort` | Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local stdout 후보 | [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) | 후보 | element count별 CPU/GPU sort `OK`와 `ExitCode: 0` evidence |
| Simulation representative capture | 없음 | `Ex1601_StableFluids`, `Ex1604_RealtimeSmoke`, `Ex1606_HybridWater` | GPU Simulation | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 후보 | runtime asset과 capture 안정성 검토 필요 |
| Animation/Gameplay capture | 없음 | `Ex1701_SkeletalAnimation`, `Ex2001_GamePlay` | 미확인 | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 후보 | Mixamo, PBR, HDRI, PhysX asset/public risk 검토 필요 |
| video | [Ex1406 DensityField](14_06_DensityField.md), [Ex1407 IndirectArguments](14_07_IndirectArguments.md) | `Ex1406_DensityField`, `Ex1407_IndirectArguments` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 미확인 | 노트북 환경에서는 생성하지 않음. density trail 시간 변화는 desktop 환경 별도 후보 |

## 갱신 기준

- Chapter14 최소 evidence set은 `Ex1401_Basic`, `Ex1402_Blur`, `Ex1403_MatVecMult`, `Ex1408_BitonicSort`로 둔다.
- Chapter14 확장 evidence set은 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments`로 둔다.
- Chapter14 `Ex1402`, `Ex1404`~`Ex1407` centered client-visible fixed UI 후보는 `Docs/_assets/captures`에 승격했다. 승격 PNG는 taskbar-free 전체 client이며 text metadata chunk가 없다.
- Chapter14 GitHub Demo Issue는 [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29)에 게시했다.

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
