# Ex1404 StructuredBuffer Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | particle 데이터를 코드에서 생성 |
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

`Ex1404_StructuredBuffer` 핵심 파일:

- `Ex1404_StructuredBuffer.cpp`
- `Ex1404_StructuredBuffer.h`
- `Ex1404_StructuredBufferCS.hlsl`
- `Ex1404_StructuredBufferVS.hlsl`
- `Ex1404_StructuredBufferPS.hlsl`
- `StructuredBuffer.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1404`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1404_StructuredBufferCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1404_StructuredBufferVS.hlsl`: Debug/Release x64 모두 Vertex, shader model `5.0`
  - `Ex1404_StructuredBufferPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- Archive files match primary raw hash for all `Ex1404` core files checked.
- `Ex1404_StructuredBuffer.cpp`, `Ex1404_StructuredBuffer.h`, `Ex1404_StructuredBufferCS.hlsl`, `Ex1404_StructuredBufferVS.hlsl`, `StructuredBuffer.h` differ from `_2`/`OriginalExamples`; archive 기준은 primary raw입니다.

## Build / Run

미확인.

실행 command argument:

```text
1404
```

확인 예정:

- Debug x64 build/run
- Release x64 build/run
- particle point cloud가 출력되는지 확인
- compute shader update로 particle 위치가 움직이는지 확인

## Notes

- compute shader는 `RWStructuredBuffer<Particle>`로 particle position을 갱신합니다.
- vertex shader는 vertex buffer 대신 `SV_VertexID`로 `StructuredBuffer<Particle>`를 조회합니다.
- `IASetInputLayout`과 `IASetVertexBuffers`를 사용하지 않는 것이 이 예제의 핵심입니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
