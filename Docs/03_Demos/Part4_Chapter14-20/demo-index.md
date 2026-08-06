# Part4_Chapter14-20 Demo Index

이 문서는 `Part4_Chapter14-20`의 demo capture/result와 video evidence 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: advanced graphics, compute/simulation
- 비고: Chapter14 static capture와 Chapter15 timestamp storyboard를 확보함. video attachment URL은 GitHub 게시 후 별도로 기록함.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Ex1401 Basic](14_01_Basic.md), [Ex1402 Blur](14_02_Blur.md), [Ex1403 MatVecMult](14_03_MatVecMult.md), [Ex1404 StructuredBuffer](14_04_StructuredBuffer.md), [Ex1405 ConsumeAppendBuffer](14_05_ConsumeAppendBuffer.md), [Ex1406 DensityField](14_06_DensityField.md), [Ex1407 IndirectArguments](14_07_IndirectArguments.md), [Ex1408 BitonicSort](14_08_BitonicSort.md) | `Ex1402`, `Ex1404`~`Ex1407` | Compute and simulation | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | `Docs/_assets/captures/part4_chapter14_02_blur.png` | 미게시 | 확보 | title bar 없는 static client-area capture 5장 확보 |
| 대표 capture | [Ex1501 ParticleSystem](15_01_ParticleSystem.md), [Ex1502 SpriteFireEffect](15_02_SpriteFireEffect.md), [Ex1503 SphWater](15_03_SphWater.md) | `Ex1501`~`Ex1503` | Compute and simulation | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | `Docs/_assets/captures/part4_chapter15_01_particle_system.png` | 게시 후보 [Chapter15 Demo](../../07_GitHub/issues/demo/demo_part4_chapter15.md) | 확보 | `ComputerGraphics` title과 01~03 timestamp frame의 Chapter15 storyboard 3장 확보 |
| video | [Ex1503 SphWater](15_03_SphWater.md) | `Ex1501`~`Ex1503` | Compute and simulation | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | 없음 | 게시 후보 [Chapter15 Demo](../../07_GitHub/issues/demo/demo_part4_chapter15.md) | 후보 | local video source 확보, GitHub attachment URL 미게시 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
