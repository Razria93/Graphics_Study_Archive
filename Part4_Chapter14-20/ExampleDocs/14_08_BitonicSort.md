# Chapter14 Ex1408 BitonicSort

## Overview

`Ex1408_BitonicSort`는 GPU compute shader bitonic sort 결과를 CPU sort 기준과 element count별로 비교하는 console 중심 예제다. `Examples.exe 1408`은 test를 실행하고 `OK` 결과를 출력한 뒤 rendering 없이 종료한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1408`
- 주요 source: `Ex1408_BitonicSort.cpp`, `BitonicSort.cpp`
- Shader: `BitonicSortCS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L59) | command argument `1408`을 `Ex1408_BitonicSort` instance에 연결 |
| [Ex1408_BitonicSort.cpp](../Ex1408_BitonicSort.cpp#L13) | `BitonicSort::TestBitonicSort` test entry를 호출 |
| [BitonicSort.cpp](../BitonicSort.cpp#L95) | GPU bitonic sort stage별 compute dispatch를 수행 |
| [BitonicSort.cpp](../BitonicSort.cpp#L180) | element count별 CPU/GPU sort result를 비교 |

## Capture/Result

tracked screenshot은 사용하지 않는다. `1024`부터 `1048576`까지의 element count에서 CPU/GPU sort compare가 `OK`이고 `ExitCode: 0`인 stdout을 evidence로 사용한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-06 stdout과 exit code 0 직접 확인 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | 불필요 | console sort compare가 정본 evidence |

## Limitations

- screenshot은 만들지 않으며 sort correctness는 stdout compare로만 확인한다.
- 현재 test는 정해진 element count와 input distribution을 사용하며 일반 purpose sorting benchmark를 제공하지 않는다.

## Related Docs

- [Chapter14-20 README](../README.md)
- [Compute Shader And Resource Flow](../../Docs/01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter14 Ex1408 BitonicSort Demo](../../Docs/03_Demos/Part4_Chapter14-20/14_08_BitonicSort.md)
- [Publication Candidate List](../../Docs/05_Publication/candidate-list.md)