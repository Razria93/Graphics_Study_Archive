# Ex1406 DensityField Status

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

`Ex1406_DensityField` 핵심 파일:

- `Ex1406_DensityField.cpp`
- `Ex1406_DensityField.h`
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

- Command argument: `1406`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1406_DensitySourcingCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1406_DensityDissipationCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1406_SpriteGS.hlsl`: Debug/Release x64 모두 Geometry, shader model `5.0`
  - `Ex1406_SpritePS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- HLSL/HLSLI BOM check: `Ex1406` shader files begin with ASCII bytes and do not include UTF BOM.
- Archive files match primary raw hash for all `Ex1406` core files checked.
- `_2`/`OriginalExamples`의 `Ex1406_DensityField.cpp`, `Ex1406_DensitySourcingCS.hlsl`는 primary raw와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

사용자가 Debug/Release x64 실행을 모두 확인했습니다.

실행 command argument:

```text
1406
```

확인 결과:

- Debug x64 build/run 성공
- Release x64 build/run 성공
- density field sprite/trail 출력 확인
- density 감쇠 동작 확인

## Notes

- `DissipateDensity()`는 `RWTexture2D<float4>`의 색을 매 프레임 줄여 잔상이 서서히 사라지게 만듭니다.
- `AdvectParticles()`는 particle position을 회전장 형태로 갱신합니다.
- `DrawSprites()`는 point list를 geometry shader로 quad sprite로 확장하고, pixel shader에서 원형 falloff를 계산합니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
