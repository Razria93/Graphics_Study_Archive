# Part4_Chapter14-20 Demo Index

이 문서는 `Part4_Chapter14-20`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: compute shader, simulation, animation, foliage, physics, gameplay 후보
- 비고: baseline 후보 정리 단계이며 capture/result는 아직 확보하지 않음

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | 없음 | `Ex1401_Basic` | Compute Shader | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local 후보 | 미게시 | 후보 | Chapter14 최소 set 후보. 2026-08-06 Debug x64 checker screenshot 후보 확보. tracked 승격 전 fixed UI와 bounds 기준으로 desktop 재촬영 필요 |
| 대표 capture | 없음 | `Ex1402_Blur`, `Ex1406_DensityField` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local 후보 | 미게시 | 후보 | Chapter14 최소/확장 visual 후보. `Ex1402_Blur`는 5000ms 안정화 기준, `Ex1406_DensityField`는 fixed UI 후보를 확인함 |
| Chapter14 result compare | 없음 | `Ex1403_MatVecMult`, `Ex1408_BitonicSort` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local stdout 후보 | 미게시 | 후보 | Chapter14 최소 set 후보. CPU/GPU compare와 `ExitCode: 0`을 evidence로 사용하고 screenshot은 불필요 |
| Chapter14 buffer/indirect evidence | 없음 | `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1407_IndirectArguments` | Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local 후보 | 미게시 | 후보 | Chapter14 확장 set 후보. `Ex1404`는 StructuredBuffer visual, `Ex1405`는 fixed UI visual과 append count stdout, `Ex1407`은 fixed UI visual과 indirect draw code evidence 병행 |
| Simulation representative capture | 없음 | `Ex1601_StableFluids`, `Ex1604_RealtimeSmoke`, `Ex1606_HybridWater` | GPU Simulation | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 후보 | runtime asset과 capture 안정성 검토 필요 |
| Animation/Gameplay capture | 없음 | `Ex1701_SkeletalAnimation`, `Ex2001_GamePlay` | 미확인 | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 후보 | Mixamo, PBR, HDRI, PhysX asset/public risk 검토 필요 |
| video | 없음 | `Ex1406_DensityField`, `Ex1407_IndirectArguments` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 미확인 | 노트북 환경에서는 생성하지 않음. density trail 시간 변화는 desktop 환경 별도 후보 |

## 갱신 기준

- Chapter14 최소 evidence set은 `Ex1401_Basic`, `Ex1402_Blur`, `Ex1403_MatVecMult`, `Ex1408_BitonicSort`로 둔다.
- Chapter14 확장 evidence set은 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments`로 둔다.
- tracked screenshot 승격 전 `HLAB_CAPTURE_UI=collapsed`, centered window, visible client area, taskbar 노출, metadata를 확인한다. Chapter14 fixed UI local 후보는 `Ex1404`~`Ex1407`로 둔다. 큰 모니터 기준 centered client-visible 후보는 `Ex1404`, `Ex1405`, `Ex1406`, `Ex1407` 모두 taskbar-free 전체 client로 확인됐다.

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
