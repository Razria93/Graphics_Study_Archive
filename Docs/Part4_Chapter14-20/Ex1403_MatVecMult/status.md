# Ex1403 MatVecMult Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | matrix/vector 데이터를 코드에서 생성 |
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

미확인.

실행 command argument:

```text
1403
```

확인 예정:

- Debug x64 build/run
- Release x64 build/run
- `Result CPU`와 `GPU Result`가 같은 값으로 출력되는지 확인
- `Error GPU 0`이 출력되는지 확인
- 프로세스가 exit code `0`으로 종료되는지 확인

## Notes

- 이 예제는 렌더링 화면이 아니라 콘솔 출력으로 검증합니다.
- `Error GPU 0`은 CPU 결과와 GPU 결과의 절대 오차 합이 0이라는 뜻이므로 계산 검증 성공으로 봅니다.
- `Initialize()` 마지막에서 `exit(0)`을 호출하므로 정상 실행 후 창이 바로 종료되는 것이 의도된 흐름입니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
