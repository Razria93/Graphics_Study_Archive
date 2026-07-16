# Ex1502 SpriteFireEffect Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 반영 완료 | `Assets/Textures/flare0.dds` |
| Build/run | 미확인 | 사용자 Debug/Release 실행 확인 전 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 아니오 | build/run 확인 후 촬영 판단 |
| Public readiness | 검토 필요 | `flare0.dds` asset source/license 확인 필요 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Primary asset: `C:\ComputerGraphics\Part4_HongLabGraphics\Assets\Textures\flare0.dds`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

`Ex1502_SpriteFireEffect` 핵심 파일:

- `Ex1502_SpriteFireEffect.cpp`
- `Ex1502_SpriteFireEffect.h`
- `Ex1502_SpriteFireEffectVS.hlsl`
- `Ex1502_SpriteFireEffectPS.hlsl`
- `Ex1501_ParticleSystemGS.hlsl`
- `Assets/Textures/flare0.dds`
- `GraphicsCommon.*`
- `D3D11Utils.*`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1502`
- Required runtime asset: `../Assets/Textures/flare0.dds`
- Shader settings:
  - `Ex1502_SpriteFireEffectVS.hlsl`: Debug/Release x64 모두 Vertex, shader model `5.0`
  - `Ex1501_ParticleSystemGS.hlsl`: Debug/Release x64 모두 Geometry, shader model `5.0`
  - `Ex1502_SpriteFireEffectPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- Archive `Ex1502` core files match primary raw hash.
- `flare0.dds` archive asset hash matches primary raw asset hash.
- `flare0.dds` is covered by repository LFS attributes: `filter=lfs`, `diff=lfs`, `merge=lfs`, `text unset`.
- `_2`/`OriginalExamples`의 `Ex1502_SpriteFireEffect.cpp`, `Ex1502_SpriteFireEffectVS.hlsl`는 primary raw와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

아직 사용자가 Debug/Release x64 실행을 확인하지 않았습니다.

실행 command argument:

```text
1502
```

확인 예정:

- Debug x64 build/run
- Release x64 build/run
- fire-like sprite particle 자동 생성
- buoyancy 기반 위쪽 이동
- mouse left click 위치 particle spawn
- `flare0.dds` texture 적용

## Notes

- 이 예제는 CPU에서 particle simulation을 수행하고 staging buffer로 GPU에 업로드합니다.
- `Ex1501_ParticleSystemGS.hlsl`를 재사용해 point particle을 quad sprite로 확장합니다.
- pixel shader는 `flare0.dds`의 RGB/alpha와 particle color를 곱해 출력합니다.
- `flare0.dds`는 private archive 실행 재현용 asset이며, public subset 이동 전 source/license 검토가 필요합니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
