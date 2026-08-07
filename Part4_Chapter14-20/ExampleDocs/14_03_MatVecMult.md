# Chapter14 Ex1403 MatVecMult

## Overview

`Ex1403_MatVecMult`는 deterministic matrix/vector data의 row-wise dot product를 CPU와 compute shader에서 각각 계산하고 결과를 비교하는 console 중심 예제다. `Examples.exe 1403`은 GPU result를 download한 뒤 error sum을 출력하고 rendering 없이 종료한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1403`
- 주요 source: `Ex1403_MatVecMult.cpp`
- Shader: `Ex1403_MatVecMultCS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L44) | command argument `1403`을 `Ex1403_MatVecMult` instance에 연결 |
| [Ex1403_MatVecMult.cpp](../Ex1403_MatVecMult.cpp#L30) | CPU/GPU result 비교, error sum 출력과 process 종료를 수행 |
| [Ex1403_MatVecMult.cpp](../Ex1403_MatVecMult.cpp#L135) | CPU row-wise dot product를 계산 |
| [Ex1403_MatVecMult.cpp](../Ex1403_MatVecMult.cpp#L171) | texture upload, compute dispatch와 GPU result download를 수행 |

## Capture/Result

tracked screenshot은 사용하지 않는다. 이 예제의 evidence는 `Result CPU`, `GPU Result`, `Error GPU 0`, `ExitCode: 0` stdout이며 rendering 전에 종료하는 흐름에 맞춘다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-06 stdout과 exit code 0 직접 확인 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | 불필요 | console output이 정본 evidence |

## Limitations

- fixed random seed와 현재 matrix dimension의 결과 비교만 다루며, 다양한 input shape의 correctness test는 제공하지 않는다.
- timing 값은 hardware와 driver 환경에 의존하므로 결과 일치 evidence와 분리한다.

## Related Docs

- [Chapter14-20 README](../README.md)
- [Compute Shader And Resource Flow](../../Docs/01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter14 Ex1403 MatVecMult Demo](../../Docs/03_Demos/Part4_Chapter14-20/14_03_MatVecMult.md)
- [Publication Candidate List](../../Docs/05_Publication/candidate-list.md)