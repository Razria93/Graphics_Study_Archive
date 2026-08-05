# Part4_Chapter14-20 Demo Index

이 문서는 `Part4_Chapter14-20`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: compute shader, simulation, animation, foliage, physics, gameplay 후보
- 비고: baseline 후보 정리 단계이며 capture/result는 아직 확보하지 않음

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | 없음 | `Ex1401_Basic` | Compute Shader | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local 후보 | 미게시 | 후보 | 2026-08-06 Debug x64 checker screenshot 후보 확보. tracked 승격 전 검수 필요 |
| 대표 capture | 없음 | `Ex1402_Blur`, `Ex1406_DensityField` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local 후보 | 미게시 | 후보 | `Ex1402_Blur`는 2026-08-06 5000ms 안정화 capture에서 RGB blur visual 확인. tracked 승격 전 metadata와 visual 재검수 필요 |
| Chapter14 result compare | 없음 | `Ex1403_MatVecMult`, `Ex1408_BitonicSort` | Compute Shader, Resource Synchronization | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | local stdout 후보 | 미게시 | 후보 | `Ex1403_MatVecMult`는 2026-08-06 CPU/GPU compare와 `ExitCode: 0` 확인. screenshot 불필요 |
| Simulation representative capture | 없음 | `Ex1601_StableFluids`, `Ex1604_RealtimeSmoke`, `Ex1606_HybridWater` | GPU Simulation | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 후보 | runtime asset과 capture 안정성 검토 필요 |
| Animation/Gameplay capture | 없음 | `Ex1701_SkeletalAnimation`, `Ex2001_GamePlay` | 미확인 | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 후보 | Mixamo, PBR, HDRI, PhysX asset/public risk 검토 필요 |
| video | 없음 | 미확인 | 미확인 | [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md) | 없음 | 미게시 | 미확인 | 시간 변화가 capture보다 설명력이 클 때만 후속 선정 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
