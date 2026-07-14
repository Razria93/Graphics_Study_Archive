# Ex1401 Basic Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | compute shader가 back buffer UAV에 직접 출력 |
| Build/run | 미확인 | 사용자 Debug/Release 실행 확인 전 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 아니오 | build/run 확인 후 판단 |
| Public readiness | 검토 필요 | 강의 기반 학습 예제. public subset 전 별도 검토 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

Part4는 단일 Visual Studio project 구조이므로 `Ex1401_Basic`만 별도 project로 분리하지 않고, `Examples` project 전체 source/project를 archive에 반영했습니다.

`Ex1401_Basic` 핵심 파일:

- `Ex1401_Basic.cpp`
- `Ex1401_Basic.h`
- `Ex1401_CS.hlsl`
- `main.cpp`
- `Examples.sln`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Excluded files: `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`, `.clang-format`
- Project reference check: 통과
- HLSL/HLSLI BOM check: raw와 동일하게 BOM 없음 확인
- Raw build output/capture file check: 통과
- Personal path check: raw `.vcxproj`의 personal vcpkg include path 제거, `VCPKG_ROOT` 조건부 include로 보정

## Build / Run

미확인.

실행 확인 시 command argument:

```text
1401
```

## Notes

- `Ex1401_CS.hlsl`은 Debug/Release x64 모두 compute shader, shader model `5.0`으로 설정되어 있습니다.
- 단일 project 전체를 빌드하므로 `Ex1401` 실행 확인 중에도 PhysX/Assimp include 설정 문제가 먼저 나타날 수 있습니다.
- raw `Ex1401_Basic.cpp`, `Ex1401_Basic.h`, `Ex1401_CS.hlsl`은 main raw와 `_2`/`OriginalExamples` 사이 hash가 다릅니다.
- `_2`와 `OriginalExamples`의 `Ex1401` 관련 파일 hash는 같습니다.
- Part4 shader 주석은 raw와 동일하게 BOM 없는 legacy encoding 계열 주석이 섞여 있어 UTF-8 terminal에서는 깨져 보일 수 있습니다. 1차 import에서는 source shape을 유지하고, 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
- 따라서 archive 기준은 `Part4_HongLabGraphics` main raw입니다.
