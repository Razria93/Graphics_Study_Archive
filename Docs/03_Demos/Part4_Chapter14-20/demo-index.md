# Part4_Chapter14-20 Demo Index

이 문서는 `Part4_Chapter14-20`의 demo capture/result와 video evidence 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: advanced graphics, compute/simulation
- 비고: Chapter14 static capture, Chapter15와 Chapter16부터 Chapter20까지 timestamp storyboard를 확보함. video attachment URL은 GitHub 게시 후 별도로 기록함.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Ex1401 Basic](14_01_Basic.md), [Ex1402 Blur](14_02_Blur.md), [Ex1403 MatVecMult](14_03_MatVecMult.md), [Ex1404 StructuredBuffer](14_04_StructuredBuffer.md), [Ex1405 ConsumeAppendBuffer](14_05_ConsumeAppendBuffer.md), [Ex1406 DensityField](14_06_DensityField.md), [Ex1407 IndirectArguments](14_07_IndirectArguments.md), [Ex1408 BitonicSort](14_08_BitonicSort.md) | `Ex1402`, `Ex1404`부터 `Ex1407`까지 | Compute and simulation | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | `Docs/_assets/captures/part4_chapter14_02_blur.png` | 게시됨 [Chapter14 Demo](../../07_GitHub/issues/demo/demo_part4_chapter14.md) | 확보 | title bar 없는 static client-area capture 5장 확보 |
| 대표 capture | [Ex1501 ParticleSystem](15_01_ParticleSystem.md), [Ex1502 SpriteFireEffect](15_02_SpriteFireEffect.md), [Ex1503 SphWater](15_03_SphWater.md) | `Ex1501`부터 `Ex1503`까지 | Compute and simulation | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | `Docs/_assets/captures/part4_chapter15_01_particle_system.png` | 게시됨 [Chapter15 Demo](../../07_GitHub/issues/demo/demo_part4_chapter15.md) | 확보 | `ComputerGraphics` title과 01부터 03까지 timestamp frame의 Chapter15 storyboard 3장 확보 |
| Chapter16부터 Chapter20까지 대표 storyboard | [Ex1601 StableFluids](16_01_StableFluids.md), [Ex1602 CurlNoise](16_02_CurlNoise.md), [Ex1603 Cloud](16_03_Cloud.md), [Ex1604 RealtimeSmoke](16_04_RealtimeSmoke.md), [Ex1605 SmokeCpu](16_05_SmokeCpu.md), [Ex1606 HybridWater](16_06_HybridWater.md), [Ex1701 SkeletalAnimation](17_01_SkeletalAnimation.md), [Ex1801 Tree](18_01_Tree.md), [Ex1802 Grass](18_02_Grass.md), [Ex1803 Landscape](18_03_Landscape.md), Chapter19부터 Chapter20까지 상세 Demo는 후속 | `Ex1601`부터 `Ex1606`까지, `Ex1701`, `Ex1801`부터 `Ex1803`까지, `Ex1901`, `Ex2001` | Compute and simulation, animation, foliage, physics, gameplay | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | [Ex1601](../../_assets/captures/part4_chapter16_01_stable_fluids.png), [Ex1602](../../_assets/captures/part4_chapter16_02_curl_noise.png), [Ex1603](../../_assets/captures/part4_chapter16_03_cloud.png), [Ex1604](../../_assets/captures/part4_chapter16_04_realtime_smoke.png), [Ex1605](../../_assets/captures/part4_chapter16_05_smoke_cpu.png), [Ex1606](../../_assets/captures/part4_chapter16_06_hybrid_water.png), [Ex1701](../../_assets/captures/part4_chapter17_01_skeletal_animation.png), [Ex1801](../../_assets/captures/part4_chapter18_01_tree.png), [Ex1802](../../_assets/captures/part4_chapter18_02_grass.png), [Ex1803](../../_assets/captures/part4_chapter18_03_landscape.png), [Ex1901](../../_assets/captures/part4_chapter19_01_physx.png), [Ex2001](../../_assets/captures/part4_chapter20_01_gameplay.png) | 미게시 | 확보 | `GraphicsVideo` 원본 MP4는 local-only로 유지. HDRI와 character, foliage, terrain 원본 asset은 직접 게시하지 않고 rendered storyboard만 사용 |
| video | [Ex1503 SphWater](15_03_SphWater.md) | `Ex1501`부터 `Ex1503`까지 | Compute and simulation | `Docs/02_Verification/Part4_Chapter14-20/verification-index.md` | 없음 | 게시됨 [Chapter15 Demo](../../07_GitHub/issues/demo/demo_part4_chapter15.md) | 후보 | local video source 확보, GitHub attachment URL 미게시 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
