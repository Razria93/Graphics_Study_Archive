# Chapter14 Ex1403 MatVecMult Demo

## 목적

Matrix-vector multiplication을 compute shader로 수행하고 CPU 결과와 GPU 결과를 stdout evidence로 비교한다.

## 책임 범위

- `Ex1403_MatVecMult`의 CPU/GPU result compare와 stdout evidence를 설명한다.
- Build/run 사실은 [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md)으로 위임한다.
- public 후보 판단은 [Publication Candidate List](../../05_Publication/candidate-list.md)로 위임한다.

## 결과 미리보기

이 Step은 렌더링 없이 종료하는 console 중심 예제다. Screenshot 대신 CPU/GPU result compare stdout을 evidence로 사용한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | command argument `1403`, deterministic matrix/vector data |
| 출력 | `Result CPU`, `GPU Result`, `Error GPU 0`, `ExitCode: 0` stdout |

## 구현 흐름

1. Deterministic random seed로 matrix와 vector를 준비한다.
2. CPU에서 row별 dot product를 계산한다.
3. Matrix, vector와 output texture를 GPU resource로 준비한다.
4. Compute shader로 row별 result를 계산한다.
5. GPU result를 download하고 CPU result와 error sum을 비교한 뒤 종료한다.

## 핵심 구현

- [CPU/GPU result compare와 종료](../../../Part4_Chapter14-20/Ex1403_MatVecMult.cpp#L30-L72)
- [CPU row별 dot product](../../../Part4_Chapter14-20/Ex1403_MatVecMult.cpp#L135-L166)
- [GPU texture upload와 compute dispatch](../../../Part4_Chapter14-20/Ex1403_MatVecMult.cpp#L171-L240)

## Stdout evidence

```text
Result CPU: 1.78619e+12
Error GPU 0
GPU Result 1.78619e+12
ExitCode: 0
```

## 시각 결과

시각 결과는 없다. 이 Step의 evidence는 GPU 계산 결과가 CPU 기준 결과와 일치한다는 stdout이다.

## 구현 범위와 한계

- Screenshot은 만들지 않는다.
- Timing 값은 환경 의존성이 있으므로 public 설명의 핵심 evidence로 사용하지 않는다.
- Release 현재 재검증은 별도 범위다.

## 검증

- [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- Debug x64 run 성공
- `Error GPU 0`, `ExitCode: 0` 확인

## 관련 코드

- [Example README](../../../Part4_Chapter14-20/README.md)
- [Example selection entry point](../../../Part4_Chapter14-20/main.cpp)

## 관련 문서

- [Demo Index](demo-index.md)
- [Compute Shader And Resource Flow](../../01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [WorkLog WU-Part4](../../04_WorkLogs/work-units/WU-Part4.md)
