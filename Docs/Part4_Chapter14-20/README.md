# Part4 Chapter14-20

Compute shader, simulation, animation, foliage, physics, gameplay 예제를 정리하는 문서 공간입니다.

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Raw source | `C:\ComputerGraphics\Part4_HongLabGraphics` |
| Reference source | `C:\ComputerGraphics\Part4_HongLabGraphics_2`, `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics` |
| Import status | `Examples` project 반영 완료, 예제별 확인 진행 중 |
| Build/run | Ex1401-Ex1407 Debug/Release 확인 완료 |
| Public readiness | 검토 필요 |

## Raw 판단

`Part4_HongLabGraphics`를 primary source로 사용합니다. `_2`와 `OriginalExamples`는 baseline/reference snapshot으로만 봅니다.

Part4는 예제별 폴더가 아니라 `Examples` 단일 project에 `Ex1401`-`Ex2001` 파일이 모여 있으므로, import 전에 project 구조를 어떻게 archive에 둘지 먼저 확정합니다.

## 실행 방식

Part4는 단일 executable이 command-line argument로 실행할 예제를 선택합니다. 예제 이름의 `Ex` 뒤 4자리 숫자를 Visual Studio `Debugging > Command Arguments`에 입력합니다.

| Example | Command argument |
| --- | --- |
| `Ex1401_Basic` | `1401` |
| `Ex1402_Blur` | `1402` |
| `Ex2001_GamePlay` | `2001` |

Debug/Release 확인 시 같은 command argument가 설정되어 있는지 먼저 확인합니다.

## 예정 범위

| Chapter | Examples | Focus |
| --- | --- | --- |
| Ch14 | `Ex1401`-`Ex1408` | Compute shader basics, structured buffers, indirect arguments, bitonic sort |
| Ch15 | `Ex1501`-`Ex1503` | Particle system, sprite fire, SPH water |
| Ch16 | `Ex1601`-`Ex1606` | Stable fluids, curl noise, cloud, smoke, hybrid water |
| Ch17 | `Ex1701` | Skeletal animation |
| Ch18 | `Ex1801`-`Ex1803` | Tree, grass, landscape/ocean |
| Ch19 | `Ex1901` | PhysX |
| Ch20 | `Ex2001` | Gameplay integration |

## Import Status

| Example | Import | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| [`Ex1401_Basic`](Ex1401_Basic/README.md) | 반영 완료 | 성공 | 검토 필요 | compute shader dispatch, back buffer UAV, 32x32 group checkerboard, command argument `1401` |
| [`Ex1402_Blur`](Ex1402_Blur/README.md) | 반영 완료 | 성공 | 검토 필요 | compute shader separable blur, SRV/UAV ping-pong, 1000회 반복으로 10 FPS 이하 확인, command argument `1402` |
| [`Ex1403_MatVecMult`](Ex1403_MatVecMult/README.md) | 반영 완료 | 성공 | 검토 필요 | compute shader matrix-vector multiplication, CPU/GPU 결과 일치, command argument `1403` |
| [`Ex1404_StructuredBuffer`](Ex1404_StructuredBuffer/README.md) | 반영 완료 | 성공 | 검토 필요 | compute shader particle update, structured buffer rendering, command argument `1404` |
| [`Ex1405_ConsumeAppendBuffer`](Ex1405_ConsumeAppendBuffer/README.md) | 반영 완료 | 성공 | 검토 필요 | consume/append structured buffer, append count rendering, command argument `1405` |
| [`Ex1406_DensityField`](Ex1406_DensityField/README.md) | 반영 완료 | 성공 | 검토 필요 | density texture, sprite geometry shader, accumulate blend, command argument `1406` |
| [`Ex1407_IndirectArguments`](Ex1407_IndirectArguments/README.md) | 반영 완료 | 성공 | 검토 필요 | indirect argument buffer, `DrawInstancedIndirect`, command argument `1407` |

## Import 기준

- source/project/shader/필수 runtime asset만 선별합니다.
- `Assets/` 전체 복사는 하지 않습니다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`, `.clang-format`은 제외합니다.
- `.dds`, `.exr`, `.fbx`, `.hdr`는 LFS 추적 기준을 따릅니다.

## 다음 작업

1. `Ex1408_BitonicSort`의 source/shader/project 설정을 확인합니다.
2. Debug/Release x64 실행 확인 전까지 build/run은 `미확인`으로 둡니다.
3. 실행 확인 후 status와 migration board를 갱신합니다.

## 관련 문서

- [Part4 Import Plan](../_repo/manifests/Part4_Chapter14-20.md)
- [Raw to Archive Map](../_repo/reference/raw-to-archive-map.md)
- [Import Integrity Checklist](../_repo/workflow/import-integrity-checklist.md)
