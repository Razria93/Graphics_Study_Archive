# Part4 Chapter14 Compute Shader Evidence Demo

## 요약

Chapter14는 compute shader dispatch에서 시작해 blur, structured buffer, consume/append counter, density field, indirect draw와 GPU sort로 확장되는 evidence 묶음이다. Visual evidence는 `Ex1402`, `Ex1404`~`Ex1407`의 centered client-visible screenshot으로 구성하고, console 중심 예제는 CPU/GPU result compare와 exit code로 확인한다. `Ex1407`은 `Ex1406`과 visual이 유사하므로 indirect argument buffer 생성과 `DrawInstancedIndirect` 호출을 code evidence로 함께 본다.

## 결과

### StructuredBuffer point cloud

`Ex1404_StructuredBuffer`는 25600개 particle을 structured buffer에 두고 compute shader update 뒤 point list로 그린다.

![StructuredBuffer point cloud](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter14_04_structured_buffer.png?raw=true)

### Consume/Append counter

`Ex1405_ConsumeAppendBuffer`는 consume buffer에서 읽은 particle을 append buffer에 다시 쌓고 `AppendBuffer count: 25600` stdout으로 counter 결과를 확인한다.

![ConsumeAppendBuffer point cloud](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter14_05_consume_append_buffer.png?raw=true)

### Density field trail

`Ex1406_DensityField`는 particle sourcing과 density dissipation을 compute shader로 수행하고 sprite draw를 누적해 color trail을 만든다.

![Density field trail](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter14_06_density_field.png?raw=true)

## 핵심 구현

### Structured buffer render path

`Ex1404`는 vertex buffer를 사용하지 않고 `StructuredBuffer<Particle>`을 vertex shader SRV로 바인딩한 뒤 particle 수만큼 draw한다.

- [StructuredBuffer update와 point draw](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1404_StructuredBuffer.cpp#L80-L119)

### Append counter evidence

`Ex1405`는 `CopyStructureCount`로 append buffer counter를 staging buffer에 복사하고, 내려받은 `appendCount`를 `Draw(appendCount, 0)`에 사용한다.

- [Append counter 복사와 append count draw](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1405_ConsumeAppendBuffer.cpp#L98-L130)

### Indirect draw evidence

`Ex1407`은 `D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS` 용도의 argument buffer를 만들고, offset이 가리키는 argument 묶음을 `DrawInstancedIndirect`에 넘긴다.

- [Indirect argument buffer 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L56-L64)
- [DrawInstancedIndirect 호출](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L165-L190)

### Stdout result compare

`Ex1403_MatVecMult`는 CPU와 GPU matrix-vector multiplication 결과를 비교해 `Error GPU 0`, `ExitCode: 0`을 확인한다. `Ex1408_BitonicSort`는 `1024`부터 `1048576`까지 element count를 늘리며 CPU sort와 GPU bitonic sort가 모두 `OK`인지 확인한다.

- [MatVecMult CPU/GPU result compare](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/Ex1403_MatVecMult.cpp#L30-L72)
- [BitonicSort element count별 CPU/GPU compare](https://github.com/Razria93/Graphics_Study_Archive/blob/44e3c118f80994949b5089f90b388fdcbea15e1c/Part4_Chapter14-20/BitonicSort.cpp#L180-L263)

## 처리 흐름

1. `Examples.exe` command argument `1401`~`1408`로 Chapter14 예제를 선택한다.
2. Visual 예제는 compute shader로 UAV 또는 structured buffer를 갱신하고 graphics pipeline에서 결과를 표시한다.
3. Console 예제는 GPU result를 CPU로 내려받아 CPU 기준 결과와 비교한다.
4. Consume/Append와 indirect draw 예제는 GPU-side count 또는 argument buffer를 draw 경로에 연결한다.
5. Screenshot 후보는 collapsed capture UI, centered window와 visible client area 기준으로 검수한다.

## 구현 범위와 한계

- 현재 tracked visual evidence는 `Ex1402`, `Ex1404`~`Ex1407` screenshot 5개다.
- `Ex1401_Basic`은 local screenshot 후보만 있으며 desktop 재촬영 후 승격 여부를 판단한다.
- `Ex1403_MatVecMult`와 `Ex1408_BitonicSort`는 stdout-only evidence로 사용한다.
- `Ex1406`과 `Ex1407`의 시간 변화는 video 후보지만, 이 본문은 static screenshot과 code evidence만 사용한다.
- Release 현재 재검증과 Chapter15~20 재검증은 별도 범위다.

## 검증

- `Ex1401`~`Ex1408` Debug x64 build/run 성공과 exit code 확인
- `Ex1403` CPU/GPU matrix-vector compare `Error GPU 0`, `Ex1408` element count별 CPU/GPU sort `OK` 확인
- `Ex1402`, `Ex1404`~`Ex1407` screenshot은 taskbar-free centered client-visible capture이며 PNG text metadata chunk가 없음

## 더 자세히 보기

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex1402 Blur 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_02_Blur.md)
- [Ex1404 StructuredBuffer 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_04_StructuredBuffer.md)
- [Ex1405 ConsumeAppendBuffer 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_05_ConsumeAppendBuffer.md)
- [Ex1406 DensityField 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_06_DensityField.md)
- [Ex1407 IndirectArguments 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/14_07_IndirectArguments.md)
- [Chapter14 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Compute And Simulation Topic Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/ComputeAndSimulation/topic-index.md)
- [PR #30](https://github.com/Razria93/Graphics_Study_Archive/pull/30)
