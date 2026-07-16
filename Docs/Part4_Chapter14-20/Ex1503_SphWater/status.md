# Ex1503 SphWater Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | SPH particle 데이터를 코드에서 생성 |
| Build/run | 미확인 | 사용자 Debug/Release 실행 확인 전 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 아니오 | build/run 확인 후 촬영 판단 |
| Public readiness | 검토 필요 | 강의 기반 학습 예제. public subset 전 별도 검토 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

`Ex1503_SphWater` 핵심 파일:

- `Ex1503_SphWater.cpp`
- `Ex1503_SphWater.h`
- `Ex1503_SphWaterVS.hlsl`
- `Ex1503_SphWaterPS.hlsl`
- `Ex1501_ParticleSystemGS.hlsl`
- `SphSimulation.cpp`
- `SphSimulation.h`
- `SphKernels.h`
- `GraphicsCommon.*`
- `D3D11Utils.*`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1503`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1503_SphWaterVS.hlsl`: Debug/Release x64 모두 Vertex, shader model `5.0`
  - `Ex1501_ParticleSystemGS.hlsl`: Debug/Release x64 모두 Geometry, shader model `5.0`
  - `Ex1503_SphWaterPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- Archive `Ex1503`/`SphSimulation` core files match primary raw hash.
- `_2`/`OriginalExamples`의 `Ex1503_SphWater.cpp`, `SphSimulation.cpp`는 primary raw와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

아직 사용자가 Debug/Release x64 실행을 확인하지 않았습니다.

실행 command argument:

```text
1503
```

확인 예정:

- Debug x64 build/run
- Release x64 build/run
- 좌우 source에서 SPH water particle 생성
- particle density/pressure interaction
- wall/ground collision

## Notes

- 이 예제는 CPU에서 SPH simulation을 수행하고 staging buffer로 GPU에 업로드합니다.
- `SphSimulation::UpdateDensity()`와 `UpdateForces()`는 활성 particle 전체를 순회하므로 particle count가 늘어나면 비용이 커집니다.
- `Ex1501_ParticleSystemGS.hlsl`를 재사용해 point particle을 quad sprite로 확장합니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
