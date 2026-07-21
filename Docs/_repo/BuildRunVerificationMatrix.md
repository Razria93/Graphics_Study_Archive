# Build / Run Verification Matrix

이 문서는 archive 기준 최신 build/run/capture 상태의 기준 문서입니다.

Import manifests, import board, PR summaries는 import 당시 기록입니다. 최신 검증 상태를 판단할 때는 이 문서와 각 예제 `status.md`를 우선 확인합니다.

## Status Values

| 값 | 의미 |
| --- | --- |
| 미확인 | 아직 직접 확인하지 않음 |
| 성공 | 직접 확인 완료 |
| 실패 | 실패 원인 기록 필요 |
| 보류 | 현재 범위 밖이거나 촬영 대기 |
| 해당 없음 | 해당 검증이 필요 없음 |

## Matrix

| Part | Example / Range | Archive target / project | Debug x64 | Release x64 | Run | Capture | Note |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Part1 Ch01-02 | `01_DX11InitAndImGui`, `02_Bloom` | `Part1_Chapter01-02` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인 |
| Part1 Ch03 | `03_Raytracing_Step4`-`Step14` | `Part1_Chapter03` | 성공 | 성공 | 성공 | 보류 | ray tracing portfolio 확장 후보 |
| Part2 Ch04 | `04_Rasterization_*` | `Part2_Chapter04` | 성공 | 성공 | 성공 | 보류 | rasterization/depth/texture/filtering 계열 |
| Part2 Ch05 | `05_AffineTransformations_*` | `Part2_Chapter05-08` | 성공 | 성공 | 성공 | 보류 | transform 기초 예제 |
| Part2 Ch06 | `06_GraphicsPipeline_*` | `Part2_Chapter05-08` | 성공 | 성공 | 성공 | 보류 | COM, vertex/pixel shader, lighting pipeline |
| Part2 Ch07 | `07_Modeling_*` | `Part2_Chapter05-08` | 성공 | 성공 | 성공 | 보류 | procedural mesh, normal, subdivision, model loading |
| Part2 Ch08 | `08_ShaderToys_*` | `Part2_Chapter05-08` | 성공 | 성공 | 성공 | 보류 | rim lighting, cubemap, IBL, Fresnel, bloom |
| Part3 Ch09 | `09_UserInteraction_*` | `Part3_Chapter09` | 성공 | 성공 | 성공 | 보류 | camera, picking, quaternion, virtual trackball |
| Part3 Ch10 | `10_GeometryPipeline_*` | `Part3_Chapter10-13` | 성공 | 성공 | 성공 | 보류 | geometry shader, billboard, normal line, tessellation |
| Part3 Ch11 | `11_TexturingTechniques_*` | `Part3_Chapter10-13` | 성공 | 성공 | 성공 | 보류 | mipmap, normal/height mapping, HDR/HDR pipeline |
| Part3 Ch12 | `12_PBR_*` | `Part3_Chapter10-13` | 성공 | 성공 | 성공 | 보류 | Unreal PBR, PBR model rendering |
| Part3 Ch13 | `13_LightAndShadow_*` | `Part3_Chapter10-13` | 성공 | 성공 | 성공 | 보류 | mirror/stencil, shadow map, fog, PCF, PCSS, halo, sphere light |
| Part4 Ch14 | `Ex1401`-`Ex1408` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | compute shader, blur, structured buffer, indirect draw, bitonic sort |
| Part4 Ch15 | `Ex1501`-`Ex1503` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | particle system, sprite fire, SPH water |
| Part4 Ch16 | `Ex1601`-`Ex1606` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | stable fluids, curl noise, cloud, smoke, hybrid water |
| Part4 Ch17 | `Ex1701` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | skeletal animation |
| Part4 Ch18 | `Ex1801`-`Ex1803` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | tree, grass, landscape |
| Part4 Ch19 | `Ex1901` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | PhysX rigid body simulation |
| Part4 Ch20 | `Ex2001` | `Part4_Chapter14-20` | 성공 | 성공 | 성공 | 보류 | gameplay integration |
| Portfolio | ray tracing extension | `Portfolio_RayTracer` | 미확인 | 미확인 | 미확인 | 미확인 | 별도 대표 작업물로 검증 예정 |

## Part4 Command Arguments

Part4는 `Examples.sln` 단일 solution으로 확인합니다. Visual Studio에서 실행할 때 `Examples` project의 `Debugging > Command Arguments`에 예제 번호를 입력합니다.

| Example | Argument |
| --- | --- |
| `Ex1401_Basic` | `1401` |
| `Ex1402_Blur` | `1402` |
| `Ex1403_MatVecMult` | `1403` |
| `Ex1404_StructuredBuffer` | `1404` |
| `Ex1405_ConsumeAppendBuffer` | `1405` |
| `Ex1406_DensityField` | `1406` |
| `Ex1407_IndirectArguments` | `1407` |
| `Ex1408_BitonicSort` | `1408` |
| `Ex1501_ParticleSystem` | `1501` |
| `Ex1502_SpriteFireEffect` | `1502` |
| `Ex1503_SphWater` | `1503` |
| `Ex1601_StableFluids` | `1601` |
| `Ex1602_CurlNoise` | `1602` |
| `Ex1603_Cloud` | `1603` |
| `Ex1604_RealtimeSmoke` | `1604` |
| `Ex1605_SmokeCpu` | `1605` |
| `Ex1606_HybridWater` | `1606` |
| `Ex1701_SkeletalAnimation` | `1701` |
| `Ex1801_Tree` | `1801` |
| `Ex1802_Grass` | `1802` |
| `Ex1803_Landscape` | `1803` |
| `Ex1901_Physics` | `1901` |
| `Ex2001_GamePlay` | `2001` |

## Known Build / Run Notes

- Part4 `Ex1402_Blur`는 Debug/Release 모두 10 FPS 이하로 확인된 기록이 있습니다.
- Part4 `Ex1403_MatVecMult`는 `Error GPU 0`으로 CPU/GPU result 일치를 확인한 기록이 있습니다.
- Part4 `Ex1408_BitonicSort`는 Debug/Release 모두 `OK` 확인 기록이 있습니다.
- Capture/video는 아직 정식 evidence로 승격하지 않았으므로 대부분 `보류`로 둡니다.
- 직접 재검증하지 않은 항목은 이 문서에서 `성공`으로 바꾸지 않습니다.
