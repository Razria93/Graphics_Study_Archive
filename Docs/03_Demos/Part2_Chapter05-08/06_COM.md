# Chapter06 Step1 COM Demo

## 목적

Step1은 full graphics pipeline을 구성하기 전에 D3D11 device와 immediate context를 최소 조건으로 생성하고 WRL `ComPtr`가 COM-style interface reference를 소유·조회·해제하는 흐름을 분리해 확인한다. Graphics 결과보다 lifetime 연산의 의미를 코드와 결정적 console 출력으로 설명한다.

## 책임 범위

- `D3D11CreateDevice()`의 out parameter와 `HRESULT` 실패 처리를 설명한다.
- `ComPtr::As()`가 interface query를 통해 별도 owning reference를 얻는 의미를 설명한다.
- `Get()`의 borrowed pointer와 `Reset()`의 reference 해제를 구분한다.
- 일반 COM ownership 이론은 [COM And Resource Lifetime](../../01_Topics/DirectX11Pipeline/COMAndResourceLifetime.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

| 확인 항목 | 대표 결과 |
| --- | --- |
| Device 생성 | Hardware driver에서 feature level `0xc100` 선택 |
| Interface query | 같은 `ID3D11Device` interface에 대한 별도 owning reference 획득 |
| Borrowed pointer | `Get()`으로 raw interface 주소를 출력하되 ownership은 이전하지 않음 |
| Reference 해제 | `copiedDevice.Reset()` 후 wrapper가 null 상태로 전환 |
| Scope 정리 | 남은 device와 context를 `ComPtr` destructor가 해제 |

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Hardware driver type과 지원 후보 feature level 목록 |
| 생성 | `ID3D11Device`, `ID3D11DeviceContext` interface |
| 출력 | Feature level, 실행마다 달라지는 raw pointer 주소, `copiedDevice` 해제 확인 |
| 시각 자료 | Graphics window와 시간 변화가 없어 screenshot과 video 제외 |

## 구현 흐름

1. Device와 immediate context를 소유할 `ComPtr`를 준비한다.
2. Feature level 후보와 hardware driver를 사용해 `D3D11CreateDevice()`를 호출한다.
3. 실패한 `HRESULT`를 처리하고 성공 시 선택된 feature level을 출력한다.
4. `As()`로 같은 device interface에 대한 별도 owning reference를 얻는다.
5. `Get()`으로 ownership을 이전하지 않는 raw pointer를 확인한다.
6. `Reset()`으로 복제한 wrapper의 참조만 해제한다.
7. Scope 종료 시 원래 device와 context reference를 자동으로 정리한다.

## 핵심 구현

### Device And Context Creation

Device와 context는 `ComPtr`가 소유하며 생성 API의 out parameter로 채워진다. Feature level 배열은 높은 level부터 시도되고 성공 시 실제 선택값을 별도로 반환한다.

#### Device 생성 의사코드

```cpp
// Pseudo C++: D3D11 device와 immediate context 생성
ComPtr device;
ComPtr context;
FeatureLevel selected = DefaultFeatureLevel;

Result result = CreateDevice(
    HardwareDriver,
    CandidateFeatureLevels,
    &device,
    &selected,
    &context);

if (Failed(result))
{
    return Failure;
}

Print(selected);
```

- [Device·context 생성과 실패 처리](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/main.cpp#L18-L42)

### Owning Reference And Borrowed Pointer

`As()`는 대상 interface를 query해 `copiedDevice`에 owning reference를 저장한다. 현재 예제는 같은 interface 타입을 요청하므로 기능상 중복이지만 query와 ownership을 보여준다. `Get()`은 reference count를 늘리지 않는 borrowed pointer를 반환하고 `Reset()`은 `copiedDevice`가 가진 참조 하나만 해제한다.

#### Interface lifetime 의사코드

```cpp
// Pseudo C++: interface query, borrowed pointer와 reference 해제
ComPtr queriedDevice;

if (Failed(device.As(&queriedDevice)))
{
    return Failure;
}

Device* borrowedDevice = queriedDevice.Get();
Print(borrowedDevice);

queriedDevice.Reset();
Assert(queriedDevice Is Null);
```

- [Interface query와 borrowed raw pointer](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/main.cpp#L44-L51)
- [Owning reference 해제와 null 확인](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/main.cpp#L53-L56)

## 시각 결과

이 예제는 console application이며 graphics frame을 만들지 않는다. Raw pointer 주소는 실행마다 달라 screenshot의 비교 기준으로 사용할 수 없고, ownership 의미는 source와 출력 종류로 더 정확하게 설명할 수 있어 screenshot과 video를 제외한다.

Visual status: console evidence로 기록하며 screenshot과 video는 제외한다.

## 구현 범위와 한계

- `copiedDevice.Reset()`은 해당 wrapper의 reference만 해제하며 underlying device의 최종 파괴를 증명하지 않는다.
- 원래 `device`와 `context`가 scope 안에서 계속 유효하므로 raw pointer 출력 이후에도 device lifetime이 유지된다.
- COM apartment 초기화, 수동 reference count 조작과 leak 진단은 포함하지 않는다.
- Hardware driver 실패 시 WARP로 재시도하지 않는다.
- Debug build도 D3D11 debug layer를 요청하지 않는다.
- Window, swap chain, render target과 frame loop는 Step2에서 다룬다.

## 검증

- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-02 현재 확인, exit code 0
- Release x64 build/run: 성공, 2026-08-02 현재 확인, exit code 0
- Debug/Release output: feature level과 해제 상태 일치, raw pointer 주소만 실행별 차이
- Capture: 설명 중심 console 예제로 제외

## 관련 코드

- [Feature level 출력 helper](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/main.cpp#L8-L11)
- [Device 생성과 COM interface lifetime](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/main.cpp#L15-L58)

## 관련 문서

- [Chapter06 Step1 COM Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/README.md)
- [이전 단계: Chapter05 Step4 Lights(SimpleMath) Demo](05_LightsSimpleMath.md)
- [COM And Resource Lifetime Topic](../../01_Topics/DirectX11Pipeline/COMAndResourceLifetime.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
