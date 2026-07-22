# Ex1407 IndirectArguments Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | particle/density 데이터를 코드에서 생성 |
| Build/run | 성공 | 사용자 Debug/Release 실행 확인 완료 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 보류 | 촬영은 사용자 진행 |
| Public readiness | 검토 필요 | 강의 기반 학습 예제. public subset 전 별도 검토 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

`Ex1407_IndirectArguments` 핵심 파일:

- `Ex1407_IndirectArguments.cpp`
- `Ex1407_IndirectArguments.h`
- `D3D11Utils.cpp`
- `D3D11Utils.h`
- `Ex1406_DensitySourcingCS.hlsl`
- `Ex1406_DensityDissipationCS.hlsl`
- `Ex1406_SpriteGS.hlsl`
- `Ex1406_SpritePS.hlsl`
- `Ex1404_StructuredBufferVS.hlsl`
- `StructuredBuffer.h`
- `Texture2D.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1407`
- Required runtime asset: 없음
- Shader settings: Ex1406 density/sprite shader settings를 재사용
  - `Ex1406_DensitySourcingCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1406_DensityDissipationCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1406_SpriteGS.hlsl`: Debug/Release x64 모두 Geometry, shader model `5.0`
  - `Ex1406_SpritePS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- `CreateIndirectArgsBuffer()`는 `D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS` misc flag를 사용합니다.
- Archive `Ex1407_IndirectArguments.cpp`/`.h` files match primary raw hash.
- `_2`/`OriginalExamples`의 `Ex1407_IndirectArguments.cpp`/`.h`는 primary raw와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

사용자가 Debug/Release x64 실행을 모두 확인했습니다.

실행 command argument:

```text
1407
```

확인 결과:

- Debug x64 build/run 성공
- Release x64 build/run 성공
- `DrawInstancedIndirect()` 경로 실행 확인
- density sprite/trail 출력 확인

## Notes

- `IndirectArgs`는 `DrawInstanced`에 필요한 `UINT` 4개 값을 담습니다.
- 현재 offset은 `sizeof(IndirectArgs) * 0`으로 첫 번째 argument set을 사용합니다.
- 이 예제의 핵심은 시각 효과 변화보다 draw argument를 GPU buffer에서 읽는 실행 구조입니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
