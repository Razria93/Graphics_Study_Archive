# Ex1408 BitonicSort

`Ex1408_BitonicSort`는 bitonic sort를 CPU와 GPU compute shader로 각각 수행하고 결과를 비교하는 콘솔 중심 예제입니다. 화면 렌더링보다는 `Initialize()`에서 정렬 테스트를 실행하고, element count별 CPU/GPU timing과 검증 결과를 출력하는 것이 핵심입니다.

## 목적

- bitonic sort의 compare/swap 단계가 compute shader에서 어떻게 dispatch되는지 확인합니다.
- `StructuredBuffer<Element>`를 GPU 정렬 입력/출력 buffer로 사용하는 흐름을 확인합니다.
- CPU `std::sort`, CPU bitonic sort, GPU bitonic sort 결과를 비교합니다.
- element count가 증가할 때 CPU/GPU 측정 시간이 어떻게 변하는지 확인합니다.

## 핵심 흐름

1. `Ex1408_BitonicSort::Initialize()`에서 `BitonicSort::TestBitonicSort()`를 호출합니다.
2. 테스트는 `1024`부터 `1048576`까지 element count를 2배씩 늘려 반복합니다.
3. random key/value 배열을 만들고 세 개의 copy를 준비합니다.
4. `std::sort(std::execution::par, ...)`로 기준 결과를 만듭니다.
5. CPU bitonic sort 결과를 기준 결과와 비교합니다.
6. GPU bitonic sort는 `Ex1408_BitonicSortCS.hlsl`을 사용해 compare/swap 단계를 compute shader로 dispatch합니다.
7. GPU 결과를 download한 뒤 CPU 기준 결과와 비교합니다.
8. 테스트가 끝나면 `exit(0)`으로 종료합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1408_BitonicSort.cpp` | Part4 example wrapper, `TestBitonicSort()` 실행 |
| `Ex1408_BitonicSort.h` | example class 정의 |
| `BitonicSort.cpp` | CPU/GPU bitonic sort, test loop, timing, compare |
| `BitonicSort.h` | `Element`, constant buffer, GPU buffer 멤버 정의 |
| `Ex1408_BitonicSortCS.hlsl` | 실제 테스트에서 사용하는 compute shader compare/swap 구현 |
| `BitonicSortCS.hlsl` | 공용 bitonic sort shader snapshot |
| `StructuredBuffer.h` | GPU array upload/download |
| `Timer.h` | CPU/GPU timing 측정 |
| `main.cpp` | command argument `1408`로 `Ex1408_BitonicSort` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1408`을 지정해야 합니다.

```text
Examples.exe 1408
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- console에 `Ex1408_BitonicSort::Initialize()`가 출력되는지 확인
- `1024`부터 `1048576`까지 test element count가 출력되는지 확인
- CPU bitonic sort와 GPU bitonic sort가 모두 `OK`를 출력하는지 확인
- 실행 종료 code가 `0`인지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
