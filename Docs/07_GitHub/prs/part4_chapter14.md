# Part4 Chapter14 Compute Shader evidence 문서화와 capture 승격

## 요약

이 PR은 `Part4_Chapter14-20` 중 Chapter14 compute shader slice를 먼저 재검증하고, visual evidence와 stdout/code evidence를 Demo 문서와 GitHub body 후보로 연결한다. 단일 `Examples.exe` command argument 구조, Debug x64 build/run 결과, capture UI 기준과 tracked screenshot 후보를 정리한다.

## 범위

- Chapter14 `Ex1401_Basic`부터 `Ex1408_BitonicSort`까지 Debug x64 build/run/capture evidence 정리
- `Ex1402`, `Ex1404`부터 `Ex1407`까지 centered client-visible screenshot 5개를 `Docs/_assets/captures`로 승격
- `Ex1403`, `Ex1405`, `Ex1408` stdout evidence와 `Ex1407` indirect draw code evidence 정리
- Chapter14 상세 Demo와 Demo Issue 후보, PR body 후보 작성
- Chapter15부터 Chapter20까지 재검증, Release 현재 재검증, desktop video capture는 제외

## 핵심 개념

- Compute shader dispatch: UAV와 structured buffer를 compute shader에서 갱신하고 graphics pipeline으로 결과를 표시한다.
- GPU result compare: rendering이 없는 예제는 GPU result를 CPU로 내려받아 CPU 기준 결과와 비교한다.
- Resource synchronization: structured buffer SRV/UAV 전환, append counter 복사와 shader barrier가 evidence 기준이 된다.
- Indirect draw: draw argument를 CPU 함수 인자가 아니라 GPU buffer에 저장하고 `DrawInstancedIndirect`에서 읽는다.

## 대표 예제

### Ex1404 StructuredBuffer

25600개 particle을 structured buffer에 저장하고 compute shader update 뒤 vertex buffer 없이 point list로 그린다.

- [Ex1404 StructuredBuffer 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_04_StructuredBuffer.md)
- [StructuredBuffer update와 point draw](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1404_StructuredBuffer.cpp#L80-L119)

### Ex1405 ConsumeAppendBuffer

consume buffer에서 읽은 particle을 append buffer에 쌓고, `CopyStructureCount`로 얻은 `appendCount`를 draw count로 사용한다.

- [Append counter 복사와 append count draw](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1405_ConsumeAppendBuffer.cpp#L98-L130)

### Ex1407 IndirectArguments

Density trail visual은 `Ex1406` 계열을 공유하지만, indirect argument buffer와 `DrawInstancedIndirect` 호출을 code evidence로 분리한다.

- [Indirect argument buffer 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L56-L64)
- [DrawInstancedIndirect 호출](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L165-L190)

### Ex1403 MatVecMult와 Ex1408 BitonicSort

`Ex1403`은 matrix-vector multiplication CPU/GPU result compare에서 `Error GPU 0`, `ExitCode: 0`을 확인한다. `Ex1408`은 `1024`부터 `1048576`까지 element count를 늘리며 CPU sort와 GPU bitonic sort 결과가 모두 `OK`인지 확인한다.

- [MatVecMult CPU/GPU result compare](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1403_MatVecMult.cpp#L30-L72)
- [BitonicSort element count별 CPU/GPU compare](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/BitonicSort.cpp#L180-L253)

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build 경고 0개, 오류 0개 확인
- `Ex1401`부터 `Ex1408`까지 Debug x64 run 성공과 exit code 확인
- `Ex1403` CPU/GPU result compare, `Ex1405` append count, `Ex1408` element count별 sort compare stdout 확인
- `Ex1402`, `Ex1404`부터 `Ex1407`까지 PNG full format, dimensions, taskbar-free centered client-visible capture와 text metadata chunk 없음 확인
- Demo index, 상세 Demo, GitHub body와 Markdown validator 통과 대상

## 스크린샷

### Chapter14 DensityField

`Ex1406_DensityField`는 particle sourcing과 density dissipation을 compute shader로 수행하고, sprite draw와 accumulate blend로 color trail을 남긴다.

![Chapter14 DensityField](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter14_06_density_field.png?raw=true)

## 미확인 / 제한

- 이 PR의 현재 재검증 범위는 Chapter14 Debug x64다.
- Release 현재 재검증은 과거 확인 상태를 유지하고 후속 범위로 둔다.
- `Ex1401_Basic`은 local screenshot 후보만 있으며 desktop 재촬영 후 tracked 승격 여부를 판단한다.
- `Ex1406`과 `Ex1407`의 시간 변화는 video 후보지만 현재 PR은 static screenshot과 code evidence 중심으로 정리한다.
- Ready for Review 전환은 별도 승인 후 수행한다.

## 문서

- Chapter README: [Part4 Chapter14-20](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- Verification: [Part4 Chapter14-20 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- Demo: [Part4 Chapter14-20 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/demo-index.md)
- 상세 Demo: [Ex1402 Blur](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_02_Blur.md), [Ex1404 StructuredBuffer](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_04_StructuredBuffer.md), [Ex1405 ConsumeAppendBuffer](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_05_ConsumeAppendBuffer.md), [Ex1406 DensityField](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_06_DensityField.md), [Ex1407 IndirectArguments](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_07_IndirectArguments.md)
- Topic: [Compute And Simulation Topic Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/ComputeAndSimulation/topic-index.md)
- WorkLog: [WU-Part4](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/04_WorkLogs/work-units/WU-Part4.md)

## 관련 이슈

- Demo Issue: [Part4 Chapter14 Compute Shader Evidence Demo #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29)
- Progress 완료 댓글: [Phase 5-1 완료 기록](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5196232081)

## 다음 단계

- Chapter15부터 Chapter20까지의 재검증은 별도 작업 단위로 진행한다.
