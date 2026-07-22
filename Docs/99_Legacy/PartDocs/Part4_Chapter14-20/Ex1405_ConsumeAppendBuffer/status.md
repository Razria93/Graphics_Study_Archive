# Ex1405 ConsumeAppendBuffer Status

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

`Ex1405_ConsumeAppendBuffer` 핵심 파일:

- `Ex1405_ConsumeAppendBuffer.cpp`
- `Ex1405_ConsumeAppendBuffer.h`
- `Ex1405_ConsumeAppendCS.hlsl`
- `StructuredBuffer.h`
- `Buffers.h`
- `Ex1404_StructuredBufferVS.hlsl`
- `Ex1404_StructuredBufferPS.hlsl`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1405`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1405_ConsumeAppendCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1404_StructuredBufferVS.hlsl`: Debug/Release x64 모두 Vertex, shader model `5.0`
  - `Ex1404_StructuredBufferPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- Archive files match primary raw hash for all `Ex1405` core files checked.
- `Ex1405_ConsumeAppendBuffer.cpp`, `Ex1405_ConsumeAppendBuffer.h`, `Ex1405_ConsumeAppendCS.hlsl`, `StructuredBuffer.h`, `Ex1404_StructuredBufferVS.hlsl` differ from `_2`/`OriginalExamples`; archive 기준은 primary raw입니다.

## Build / Run

사용자가 Debug/Release x64 실행을 모두 확인했습니다.

실행 command argument:

```text
1405
```

확인 결과:

- Debug x64 build/run 성공
- Release x64 build/run 성공
- `Ex1404_StructuredBuffer`와 유사한 밤하늘 별 모양 particle point cloud 출력 확인
- particle 위치 이동/회전 확인
- `AppendBuffer count` console output 확인

## Notes

- compute shader는 `ConsumeStructuredBuffer<Particle>`에서 particle을 하나씩 꺼내고 `AppendStructuredBuffer<Particle>`에 갱신 결과를 쌓습니다.
- 렌더링 경로는 `Ex1404_StructuredBufferVS.hlsl`/`Ex1404_StructuredBufferPS.hlsl`를 재사용하므로, 시각 결과는 `Ex1404`와 유사하게 보이는 것이 정상입니다.
- `CopyStructureCount()`로 append buffer counter를 CPU staging buffer에 복사한 뒤 `Draw(appendCount, 0)`에 사용합니다.
- 현재 구조는 count를 CPU로 읽어 다시 draw count로 넘기므로, 이후 indirect draw 예제와 비교하기 좋습니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
