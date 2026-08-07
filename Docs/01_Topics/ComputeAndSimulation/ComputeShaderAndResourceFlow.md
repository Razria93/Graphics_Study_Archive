# Compute Shader And Resource Flow

## 목적

Compute shader는 rasterization 경로와 분리된 thread group 실행 모델로 texture와 buffer를 갱신한다. 이 Topic은 Part4 Chapter14의 compute dispatch, SRV/UAV view 전환, GPU draw argument 전달을 설명한다.

## 책임 범위

- Compute shader의 dispatch 단위와 resource view 역할을 설명한다.
- 같은 resource를 읽기와 쓰기 용도로 바꾸는 binding 경계와 indirect draw argument 전달을 설명한다.
- 예제별 shader와 buffer 구현은 [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md)와 상세 Demo로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification/Part4_Chapter14-20`의 [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos/Part4_Chapter14-20`의 상세 Demo로 위임한다.

## 핵심 개념

### Thread Group Dispatch

Compute shader는 `Dispatch(x, y, z)`로 thread group을 실행한다. thread group 크기와 dispatch 차원은 처리할 texture 또는 buffer의 범위를 덮어야 하며, 경계 밖 thread는 shader에서 제외한다. `Ex1401_Basic`의 back buffer UAV와 `Ex1402_Blur`의 pass 갱신은 이 실행 단위를 보여준다.

### SRV, UAV And Binding Boundary

SRV는 shader read view이고 UAV는 unordered read/write view다. 동일 resource를 다음 pipeline 단계에서 읽으려면 이전 UAV binding을 해제하고 필요한 view로 다시 binding해야 한다. 이 경계는 resource 데이터 복사가 아니라 pipeline이 resource를 해석하는 방식을 전환하는 단계다.

### GPU Generated Draw Arguments

Append/consume buffer의 count와 indirect argument buffer는 GPU가 계산한 개수를 다음 draw command에 전달한다. `CopyStructureCount`와 `DrawInstancedIndirect`는 CPU가 instance count를 다시 읽지 않아도 GPU buffer를 draw 입력으로 사용하게 한다.

## 한계

- D3D11 immediate context의 세부 synchronization과 multi-context command recording을 다루지 않는다.
- driver 내부 scheduling 순서와 각 shader의 성능은 단정하지 않는다.
- 예제별 thread group 상수와 호출 순서는 상세 Demo 범위로 둔다.

## 관련 문서

- [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md)
- [Ex1402 Blur Demo](../../03_Demos/Part4_Chapter14-20/14_02_Blur.md)
- [Ex1405 ConsumeAppendBuffer Demo](../../03_Demos/Part4_Chapter14-20/14_05_ConsumeAppendBuffer.md)
- [Ex1407 IndirectArguments Demo](../../03_Demos/Part4_Chapter14-20/14_07_IndirectArguments.md)
- [Part4 Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- [Compute And Simulation Topic Index](topic-index.md)