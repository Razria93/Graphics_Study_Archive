# Ex1501 ParticleSystem Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | particle 데이터를 코드에서 생성 |
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

`Ex1501_ParticleSystem` 핵심 파일:

- `Ex1501_ParticleSystem.cpp`
- `Ex1501_ParticleSystem.h`
- `Ex1501_ParticleSystemVS.hlsl`
- `Ex1501_ParticleSystemGS.hlsl`
- `Ex1501_ParticleSystemPS.hlsl`
- `GraphicsCommon.*`
- `D3D11Utils.*`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1501`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1501_ParticleSystemVS.hlsl`: Debug/Release x64 모두 Vertex, shader model `5.0`
  - `Ex1501_ParticleSystemGS.hlsl`: Debug/Release x64 모두 Geometry, shader model `5.0`
  - `Ex1501_ParticleSystemPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- Archive `Ex1501` core files match primary raw hash.
- `_2`/`OriginalExamples`의 `Ex1501_ParticleSystem.cpp`, `Ex1501_ParticleSystemVS.hlsl`는 primary raw와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

사용자가 Debug/Release x64 실행을 모두 확인했습니다.

실행 command argument:

```text
1501
```

확인 결과:

- Debug x64 build/run 성공
- Release x64 build/run 성공
- particle sprite 자동 생성/이동 확인
- gravity와 wall/ground collision 동작 확인
- mouse left click 위치 particle spawn 확인

## Notes

- 이 예제는 CPU에서 particle simulation을 수행하고 staging buffer로 GPU에 업로드합니다.
- `life < 0.0f`인 particle은 비활성 slot으로 취급합니다.
- geometry shader가 point list를 quad sprite로 확장합니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
