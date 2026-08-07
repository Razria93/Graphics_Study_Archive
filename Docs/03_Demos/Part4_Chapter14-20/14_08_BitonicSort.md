# Chapter14 Ex1408 BitonicSort Demo

## 목적

GPU compute shader bitonic sort 결과를 CPU sort 기준 결과와 비교하고 stdout evidence로 검증한다.

## 책임 범위

- `Ex1408_BitonicSort`의 element count별 CPU/GPU compare와 stdout evidence를 설명한다.
- Build/run 사실은 [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md)으로 위임한다.
- public 후보 판단은 [Publication Candidate List](../../05_Publication/candidate-list.md)로 위임한다.

## 결과 미리보기

이 Step은 렌더링 없이 종료하는 console 중심 예제다. Screenshot 대신 element count별 `OK` stdout을 evidence로 사용한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | command argument `1408`, random key/value array, bitonic sort compute shader |
| 출력 | `1024`~`1048576` element count별 CPU/GPU compare `OK`, `ExitCode: 0` stdout |

## 구현 흐름

1. `Ex1408_BitonicSort::Initialize`에서 sort test를 실행한다.
2. Element count를 `1024`부터 `1048576`까지 두 배씩 늘린다.
3. CPU 기준으로 `std::sort`와 CPU bitonic sort 결과를 비교한다.
4. 같은 입력을 GPU structured buffer에 업로드한다.
5. Bitonic sort compute shader를 단계별로 dispatch한다.
6. GPU result를 download하고 CPU 기준 결과와 비교한 뒤 종료한다.

## 핵심 구현

- [BitonicSort test entry](../../../Part4_Chapter14-20/Ex1408_BitonicSort.cpp#L13-L22)
- [GPU bitonic sort dispatch loop](../../../Part4_Chapter14-20/BitonicSort.cpp#L95-L116)
- [Element count별 CPU/GPU compare](../../../Part4_Chapter14-20/BitonicSort.cpp#L180-L253)

## Stdout evidence

```text
Test Num Elements 1024
OK
OK
...
Test Num Elements 1048576
OK
OK
ExitCode: 0
```

## 시각 결과

시각 결과는 없다. 이 Step의 evidence는 element count별 CPU/GPU sort 결과가 모두 `OK`라는 stdout이다.

## 구현 범위와 한계

- Screenshot은 만들지 않는다.
- Timing 값은 환경 의존성이 있으므로 public 설명의 핵심 evidence로 사용하지 않는다.
- Release 현재 재검증은 별도 범위다.

## 검증

- [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- Debug x64 run 성공
- `1024`~`1048576` element count별 CPU/GPU compare `OK`, `ExitCode: 0` 확인

## 관련 코드

- [Example README](../../../Part4_Chapter14-20/README.md)
- [Example selection entry point](../../../Part4_Chapter14-20/main.cpp)

## 관련 문서

- [Demo Index](demo-index.md)
- [Compute Shader And Resource Flow](../../01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [WorkLog WU-Part4](../../04_WorkLogs/work-units/WU-Part4.md)
