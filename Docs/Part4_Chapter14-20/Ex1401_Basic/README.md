# Ex1401 Basic

`Ex1401_Basic`은 Part4의 첫 compute shader 예제입니다. Pixel shader draw path가 아니라 compute shader dispatch로 back buffer UAV에 직접 값을 써서 화면 결과를 만듭니다.

## 목적

- DirectX11 compute shader 생성과 dispatch 흐름을 확인합니다.
- back buffer를 `UnorderedAccessView`로 만들어 compute shader output 대상으로 사용합니다.
- HLSL `numthreads`와 C++ `Dispatch` group count의 관계를 확인합니다.

## 핵심 흐름

1. `m_backBufferFormat`을 `DXGI_FORMAT_R16G16B16A16_FLOAT`로 설정합니다.
2. swap chain back buffer를 가져옵니다.
3. back buffer에 대한 `ID3D11UnorderedAccessView`를 생성합니다.
4. `Ex1401_CS.hlsl` compute shader를 생성합니다.
5. `CSSetUnorderedAccessViews`로 UAV를 바인딩합니다.
6. `Dispatch(ceil(width / 32), ceil(height / 32), 1)`로 화면 영역을 32x32 thread group 기준으로 처리합니다.
7. `ComputeShaderBarrier()`로 compute shader resource binding을 정리합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1401_Basic.cpp` | back buffer UAV 생성, constant buffer update, compute dispatch |
| `Ex1401_Basic.h` | compute shader, UAV, constant buffer 멤버 정의 |
| `Ex1401_CS.hlsl` | `RWTexture2D<float4>`에 checker pattern 값을 기록 |
| `main.cpp` | command argument `1401`로 `Ex1401_Basic` 선택 |
| `Examples.vcxproj` | `Ex1401_CS.hlsl`을 compute shader로 빌드 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다.

```text
Examples.exe 1401
```

Visual Studio에서 직접 실행할 경우 Debugging command arguments에 `1401`을 지정해야 합니다. 인자가 없으면 raw `main.cpp` 흐름상 "Please specify the example number"를 출력하고 종료합니다.

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요

## 다음 확인

- Debug x64 build/run
- Release x64 build/run
- 실행 시 checker pattern이 출력되는지 확인
- command argument `1401` 설정 누락 여부 확인
