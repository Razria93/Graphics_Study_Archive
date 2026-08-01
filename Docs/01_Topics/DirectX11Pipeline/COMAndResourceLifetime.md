# COM And Resource Lifetime

## 목적

COM-style graphics interface는 object 구현과 interface pointer를 분리하고 reference count로 lifetime을 관리한다. 이 문서는 Direct3D interface를 소유하거나 잠시 참조할 때 ownership을 구분하고 WRL `ComPtr`로 참조를 안전하게 관리하는 기준을 설명한다.

## 책임 범위

- COM interface pointer와 underlying object의 관계를 설명한다.
- Owning reference와 borrowed pointer를 구분한다.
- `ComPtr`의 `As()`, `Get()`, `Reset()`과 scope 종료 의미를 설명한다.
- API out parameter로 받은 interface의 lifetime을 설명한다.
- Step1의 구체적인 device 생성과 출력은 [Chapter06 Step1 COM Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/README.md)로 위임한다.
- 구현 흐름과 제한은 `Docs/03_Demos`의 [Chapter06 Step1 COM Demo](../../03_Demos/Part2_Chapter05-08/06_COM.md)로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 핵심 개념

### Interface Ownership And Reference Counting

COM object는 하나 이상의 interface를 제공하며 client는 interface pointer를 통해 object를 사용한다. Owning reference를 새로 얻으면 reference count가 증가하고 해당 소유권을 놓을 때 감소한다. 마지막 owning reference가 해제될 때 object가 파괴될 수 있으므로 pointer 값과 object lifetime을 같은 의미로 취급하지 않는다.

API가 성공 시 interface pointer를 out parameter로 반환하면 호출자는 반환된 reference의 소유권을 관리해야 한다. Direct3D의 device, context, resource와 view도 이 방식을 따르며, 수동 `Release()` 대신 RAII wrapper를 사용하면 여러 반환 경로에서 해제를 빠뜨릴 위험을 줄일 수 있다.

### ComPtr Ownership Operations

WRL `ComPtr`는 지정된 interface pointer를 보관하고 scope 종료 시 소유한 reference를 해제한다. `As()`는 요청한 interface에 대한 query를 수행해 대상 `ComPtr`에 별도의 owning reference를 저장한다. 같은 interface 타입을 다시 요청할 수도 있지만 일반적인 C++ pointer 복사와 동일한 연산으로 해석하지 않는다.

`Get()`은 내부 interface pointer를 반환하지만 새로운 reference를 얻지 않는다. 반환된 raw pointer는 원래 `ComPtr`보다 오래 사용할 수 없는 borrowed pointer로 취급한다. 장기 소유권이 필요하면 명시적으로 owning reference를 확보해야 한다.

`Reset()`은 해당 `ComPtr`가 소유한 reference를 해제하고 wrapper를 비운다. 다른 interface pointer가 같은 object를 계속 소유한다면 underlying object는 유지되므로 `Reset()` 성공을 object의 최종 파괴 증거로 사용하지 않는다.

### Out Parameters And Scope Lifetime

Direct3D 생성 API는 interface pointer의 주소를 out parameter로 받아 생성된 object의 reference를 반환한다. `ComPtr`를 out parameter에 연결하면 성공 이후 wrapper가 reference를 소유하고, 실패 경로와 정상 scope 종료에서 RAII 정리를 적용할 수 있다.

여러 `ComPtr`가 같은 object를 참조할 때 각 wrapper의 lifetime을 독립적으로 본다. 하나의 wrapper를 reset해도 다른 owning reference가 남아 있을 수 있으며, borrowed raw pointer는 소유 wrapper가 유효한 동안에만 사용한다.

## 한계

- COM binary ABI, class factory, aggregation과 marshaling을 다루지 않는다.
- COM apartment와 thread initialization 규칙을 다루지 않는다.
- 수동 `AddRef()`·`Release()` 구현과 실제 reference count 진단을 다루지 않는다.
- Direct3D device/context의 내부 참조 관계와 driver object lifetime 세부사항을 단정하지 않는다.
- `ComPtr` 외의 smart pointer wrapper와의 API 차이는 비교하지 않는다.

## 관련 문서

- [Chapter06 Step1 COM Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/README.md)
- [Chapter06 Step1 COM Demo](../../03_Demos/Part2_Chapter05-08/06_COM.md)
- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [DirectX11 Pipeline Topic Index](topic-index.md)
