# Ex1403 MatVecMult Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | matrix/vector 데이터를 코드에서 생성 |
| Build/run | 성공 | 사용자 Debug/Release 실행 확인 완료 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 보류 | 콘솔 출력 중심 예제. 촬영은 사용자 진행 |
| Public readiness | 검토 필요 | 강의 기반 학습 예제. public subset 전 별도 검토 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

`Ex1403_MatVecMult` 핵심 파일:

- `Ex1403_MatVecMult.cpp`
- `Ex1403_MatVecMult.h`
- `Ex1403_MatVecMultCS.hlsl`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1403`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1403_MatVecMultCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
- Archive files match primary raw hash for all `Ex1403` core files checked.
- `Ex1403_MatVecMult.cpp`와 `Ex1403_MatVecMultCS.hlsl`은 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

사용자가 Debug/Release x64 실행을 모두 확인했습니다.

실행 command argument:

```text
1403
```

Debug 확인 결과:

```text
CPU: 8.6508
Result CPU: 1.78619e+12
GPU: 0, CPU: 0.8998
Error GPU 0
GPU Result 1.78619e+12
exit code 0
```

Release 확인 결과:

```text
CPU: 2.231
Result CPU: 1.78619e+12
GPU: 0, CPU: 0.4126
Error GPU 0
GPU Result 1.78619e+12
exit code 0
```

## Notes

- 이 예제는 렌더링 화면이 아니라 콘솔 출력으로 검증합니다.
- `Error GPU 0`은 CPU 결과와 GPU 결과의 절대 오차 합이 0이라는 뜻이므로 계산 검증 성공으로 봅니다.
- `GPU: 0`은 GPU timer 측정값이 현재 실험 크기/측정 방식에서 0에 가깝게 출력된 것으로 기록합니다.
- `Initialize()` 마지막에서 `exit(0)`을 호출하므로 정상 실행 후 창이 바로 종료되는 것이 의도된 흐름입니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
