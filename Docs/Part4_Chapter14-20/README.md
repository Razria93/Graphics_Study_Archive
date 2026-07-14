# Part4 Chapter14-20

Compute shader, simulation, animation, foliage, physics, gameplay 예제를 정리하는 문서 공간입니다.

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Raw source | `C:\ComputerGraphics\Part4_HongLabGraphics` |
| Reference source | `C:\ComputerGraphics\Part4_HongLabGraphics_2`, `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics` |
| Import status | 계획 수립 |
| Build/run | 미확인 |
| Public readiness | 검토 필요 |

## Raw 판단

`Part4_HongLabGraphics`를 primary source로 사용합니다. `_2`와 `OriginalExamples`는 baseline/reference snapshot으로만 봅니다.

Part4는 예제별 폴더가 아니라 `Examples` 단일 project에 `Ex1401`-`Ex2001` 파일이 모여 있으므로, import 전에 project 구조를 어떻게 archive에 둘지 먼저 확정합니다.

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
| [`Ex1401_Basic`](Ex1401_Basic/README.md) | 반영 완료 | 미확인 | 검토 필요 | compute shader dispatch, back buffer UAV, command argument `1401` |

## Import 기준

- source/project/shader/필수 runtime asset만 선별합니다.
- `Assets/` 전체 복사는 하지 않습니다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`, `.clang-format`은 제외합니다.
- `.dds`, `.exr`, `.fbx`, `.hdr`는 LFS 추적 기준을 따릅니다.

## 다음 작업

1. 단일 `Examples` project 구조를 기준으로 source/project를 archive에 반영합니다.
2. `.vs/`, `x64/`, `.user`, `imgui.ini`, `.clang-format`은 제외합니다.
3. 첫 실행 확인 대상은 `Ex1401_Basic`이며, command argument `1401`로 실행합니다.

## 관련 문서

- [Part4 Import Plan](../_repo/manifests/Part4_Chapter14-20.md)
- [Raw to Archive Map](../_repo/reference/raw-to-archive-map.md)
- [Import Integrity Checklist](../_repo/workflow/import-integrity-checklist.md)
