# Ex1403 MatVecMult

`Ex1403_MatVecMult`는 compute shader로 matrix-vector multiplication을 수행하고 CPU 계산 결과와 비교하는 예제입니다. 화면 렌더링이 아니라 콘솔 출력으로 CPU/GPU 결과와 시간을 확인한 뒤 종료합니다.

## 목적

- CPU와 GPU compute shader의 matrix-vector multiplication 결과를 비교합니다.
- matrix와 vector 데이터를 texture로 업로드하고 compute shader에서 읽는 흐름을 확인합니다.
- GPU 결과를 staging texture를 통해 CPU로 다운로드하는 흐름을 확인합니다.
- `Error GPU 0`으로 CPU/GPU 결과 일치 여부를 검증합니다.

## 핵심 흐름

1. `m_numRows = 1024`, `m_numCols = 2048`, `m_repeat = 1`로 실험 크기를 설정합니다.
2. 고정 seed 난수로 matrix와 vector를 생성합니다.
3. CPU에서 row별 dot product로 결과 vector를 계산합니다.
4. matrix/vector를 texture로 업로드합니다.
5. `Ex1403_MatVecMultCS.hlsl` compute shader로 row별 dot product를 계산합니다.
6. GPU 결과 texture를 CPU로 다운로드합니다.
7. CPU 결과와 GPU 결과의 절대 오차 합을 출력합니다.
8. `exit(0)`으로 렌더링 없이 종료합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1403_MatVecMult.cpp` | CPU/GPU matrix-vector multiplication, result comparison, console output |
| `Ex1403_MatVecMult.h` | input/output vector와 실험 크기 멤버 정의 |
| `Ex1403_MatVecMultCS.hlsl` | matrix texture row와 vector texture의 dot product 계산 |
| `Texture2D.h` | CPU/GPU texture upload/download helper |
| `main.cpp` | command argument `1403`으로 `Ex1403_MatVecMult` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1403`을 지정해야 합니다.

```text
Examples.exe 1403
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 콘솔에 `Result CPU`와 `GPU Result`가 같은 값으로 출력되는지 확인
- `Error GPU 0`이 출력되는지 확인
- 프로세스가 `0` 코드로 종료되는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
