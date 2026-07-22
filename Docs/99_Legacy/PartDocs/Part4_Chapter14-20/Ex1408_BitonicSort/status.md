# Ex1408 BitonicSort Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | sort input 데이터를 코드에서 생성 |
| Build/run | 성공 | 사용자 Debug/Release 실행 확인 완료 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 보류 | console output 확인 예제. 촬영은 사용자 진행 |
| Public readiness | 검토 필요 | 강의 기반 학습 예제. public subset 전 별도 검토 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

`Ex1408_BitonicSort` 핵심 파일:

- `Ex1408_BitonicSort.cpp`
- `Ex1408_BitonicSort.h`
- `Ex1408_BitonicSortCS.hlsl`
- `BitonicSort.cpp`
- `BitonicSort.h`
- `BitonicSortCS.hlsl`
- `StructuredBuffer.h`
- `Timer.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1408`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1408_BitonicSortCS.hlsl`: Debug/Release x64 모두 Compute
  - `BitonicSortCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
- Archive `Ex1408`/`BitonicSort` core files match primary raw hash.
- `_2`/`OriginalExamples`의 `Ex1408_BitonicSort.cpp`, `BitonicSort.cpp`는 primary raw와 hash가 다르므로, archive 기준은 primary raw입니다.

## Build / Run

사용자가 Debug/Release x64 실행을 모두 확인했습니다.

실행 command argument:

```text
1408
```

확인 결과:

- Debug x64 build/run 성공
- Release x64 build/run 성공
- `1024`부터 `1048576`까지 test case 출력 확인
- 각 test case에서 CPU bitonic sort result `OK` 확인
- 각 test case에서 GPU bitonic sort result `OK` 확인
- Debug/Release 모두 exit code `0` 확인

Debug output summary:

```text
Ex1408_BitonicSort::Initialize()
Test Num Elements 1024 ... OK ... OK
...
Test Num Elements 1048576 ... OK ... OK
exit code 0
```

Release output summary:

```text
Ex1408_BitonicSort::Initialize()
Test Num Elements 1024 ... OK ... OK
...
Test Num Elements 1048576 ... OK ... OK
exit code 0
```

## Notes

- `Ex1408_BitonicSort`는 렌더링 화면보다 console output이 핵심입니다.
- `BitonicSort::TestBitonicSort()`는 테스트 완료 후 `exit(0)`으로 종료합니다.
- GPU sort는 `k`, `j` constant buffer를 단계별로 바꾸며 compute shader를 반복 dispatch합니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
