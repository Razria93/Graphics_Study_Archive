# Chapter06 Step1 COM

이 예제는 graphics window와 swap chain을 만들기 전에 최소 D3D11 device·immediate context를 생성하고 COM-style interface lifetime을 WRL `ComPtr`로 관리한다. `As()`, `Get()`과 `Reset()`이 각각 interface query, borrowed pointer 접근과 소유 참조 해제를 담당하는 차이를 console 출력과 코드로 확인한다.

## 실행 진입점

- Solution: `06_D3D11GraphicsPipeline_Step1_COM.sln`
- Project type: Console application
- Entry point: `main.cpp`
- Runtime dependency: Windows SDK의 D3D11 runtime
- Runtime working directory: 별도 파일 의존성 없음

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Feature level 출력](main.cpp#L8-L11) | 생성된 D3D feature level을 16진수로 출력 |
| [Device와 context 생성](main.cpp#L18-L42) | `D3D11CreateDevice()` out parameter와 `HRESULT` 실패 처리 |
| [Interface query와 borrowed pointer](main.cpp#L44-L51) | `As()`로 owning reference를 얻고 `Get()`으로 raw view 확인 |
| [소유 참조 해제](main.cpp#L53-L56) | `Reset()`으로 `copiedDevice`의 참조를 해제하고 null 상태 확인 |

## 구현 요약

`D3D11CreateDevice()`는 hardware driver에서 지원 가능한 첫 feature level을 선택하고 `ID3D11Device`와 `ID3D11DeviceContext` interface를 반환한다. 반환값은 `ComPtr`가 소유하므로 scope 종료 시 남은 interface reference를 자동으로 해제한다.

`device.As(&copiedDevice)`는 일반 C++ smart pointer 복사가 아니라 요청한 interface에 대한 query를 수행해 별도의 owning reference를 얻는다. 현재 코드는 같은 `ID3D11Device` 타입을 다시 요청하므로 기능상 중복이지만 interface query의 ownership 의미를 보여준다. `Get()`은 `AddRef()` 없이 borrowed raw pointer를 반환하고, `Reset()`은 `copiedDevice`가 가진 참조 하나만 해제한다.

일반 COM interface와 reference-counted lifetime은 [COM And Resource Lifetime](../../Docs/01_Topics/DirectX11Pipeline/COMAndResourceLifetime.md), 실제 흐름과 제한은 [Step1 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_COM.md), build/run 사실은 [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Device 생성 | 성공 | feature level `0xc100` 확인 |
| Capture/Result | 제외 | 결정적 console 출력과 코드가 ownership 설명에 더 적합 |

## Capture/Result

이 예제는 graphics window 없이 console text만 출력한다. Raw pointer 주소는 실행마다 달라지고 screenshot이 interface ownership을 추가로 증명하지 못하므로 screenshot과 video를 제외한다.

## 구현 범위와 한계

- `copiedDevice.Reset()`은 해당 wrapper의 참조 하나만 해제하며 underlying device의 최종 파괴를 증명하지 않는다.
- 원래 `device`와 `context`는 scope가 끝날 때 `ComPtr` destructor로 해제된다.
- COM apartment 초기화, 수동 `AddRef()`·`Release()`, 최종 reference count와 leak 검증은 다루지 않는다.
- Hardware driver만 요청하며 WARP fallback과 device 생성 재시도는 포함하지 않는다.
- Window, swap chain, render target, viewport와 frame loop는 Step2로 위임한다.
- Win32 configuration 재현성은 현재 검증 범위에 포함하지 않는다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter05 Step4 Lights(SimpleMath)](../05_AffineTransformations_Step4_Lights%28SimpleMath%29/README.md)
- 다음 단계: Chapter06 Step2 InitializingD3D 문서화 대기
- [COM And Resource Lifetime Topic](../../Docs/01_Topics/DirectX11Pipeline/COMAndResourceLifetime.md)
- [Step1 COM 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_COM.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
