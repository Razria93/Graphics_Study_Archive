# 06 GraphicsPipeline Step1 COM

## 목적

D3D11 graphics pipeline 예제로 들어가기 전에 Windows COM 객체와 `Microsoft::WRL::ComPtr` 사용 흐름을 확인하는 콘솔 예제입니다. `D3D11CreateDevice()`로 device/context를 만들고, COM smart pointer의 복사/조회/해제 패턴을 확인합니다.

## 핵심 키워드

- COM
- `Microsoft::WRL::ComPtr`
- `ID3D11Device`
- `ID3D11DeviceContext`
- `D3D11CreateDevice`
- `D3D_FEATURE_LEVEL`
- `HRESULT`

## 구현 흐름

1. `ComPtr<ID3D11Device>`와 `ComPtr<ID3D11DeviceContext>`를 준비합니다.
2. 지원할 feature level 목록을 높은 버전부터 나열합니다.
3. `D3D11CreateDevice()`로 hardware device와 immediate context를 생성합니다.
4. 생성된 feature level과 raw pointer 값을 출력해 생성 여부를 확인합니다.
5. `ComPtr::As()`로 interface pointer를 다른 `ComPtr`에 복사합니다.
6. `Reset()`으로 참조를 해제하고 null 상태를 확인합니다.

## 핵심 코드

```cpp
const HRESULT hr = D3D11CreateDevice(
    nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, creationFlags,
    featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &device,
    &createdFeatureLevel, &context);
```

이 호출은 D3D11 device와 immediate context를 생성합니다. 이후 예제들은 이 device/context를 기반으로 swap chain, render target, buffer, shader 등을 구성합니다.

```cpp
ComPtr<ID3D11Device> copiedDevice;
device.As(&copiedDevice);
copiedDevice.Reset();
```

`ComPtr`는 COM 객체의 reference counting을 관리합니다. raw pointer를 직접 `Release()`하는 대신 smart pointer의 수명과 `Reset()`으로 해제 흐름을 다룹니다.

## Archive 반영 메모

- raw source의 COM 설명 주석과 링크 메모는 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/source-comments.md`로 분리했습니다.
- `.clang-format`, `.vs/`는 archive에 포함하지 않았습니다.
- project file에서 `.clang-format` 참조를 제거했습니다.
- 외부 asset은 없습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 source 주석, 문서, dependency 설명, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
