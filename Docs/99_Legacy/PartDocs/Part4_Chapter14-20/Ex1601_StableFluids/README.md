# Ex1601 StableFluids

## 목적

`Ex1601_StableFluids`는 compute shader 기반 2D stable fluids 예제입니다. velocity, pressure, divergence, vorticity, density texture를 GPU resource로 두고 `Sourcing -> Diffuse -> Projection -> Advection` pass를 순서대로 실행합니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1601` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | 없음 |
| Build/run status | Debug/Release 확인 완료 |

확인할 동작:

- 시작 직후에는 density texture가 비어 있어 검은 화면에 가깝게 보일 수 있습니다.
- 마우스 좌클릭으로 density source가 추가됩니다.
- 좌클릭 드래그 시 mouse delta가 sourcing velocity로 들어가 색이 밀리고 번지는 흐름을 확인합니다.

## 핵심 흐름

1. `Ex1601_StableFluids::Initialize()`에서 back buffer format을 `DXGI_FORMAT_R16G16B16A16_FLOAT`로 설정하고 `StableFluids`를 초기화합니다.
2. `Ex1601_StableFluids::Update()`는 mouse position, density color, drag velocity를 `StableFluids::Consts`에 기록합니다.
3. `StableFluids::Update()`는 `Sourcing -> Diffuse -> Projection -> Advection` 순서로 compute shader pass를 실행합니다.
4. `Sourcing`은 density/velocity를 주입하고 vorticity 계산 및 confinement를 수행합니다.
5. `Diffuse`는 ping-pong texture를 사용해 velocity와 density를 반복 완화합니다.
6. `Projection`은 divergence를 계산하고 Jacobi iteration으로 pressure를 구한 뒤 velocity에서 pressure gradient를 제거합니다.
7. `Advection`은 velocity field를 따라 velocity/density를 이동시킵니다.
8. `Render()`는 최종 density texture를 back buffer에 복사합니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1601_StableFluids.cpp/.h` | 예제 entry, mouse input, render copy |
| `StableFluids.cpp/.h` | fluid simulation pass orchestration |
| `Ex1601_SourcingCS.hlsl` | source density/velocity injection |
| `Ex1601_ComputeVorticityCS.hlsl` | vorticity 계산 |
| `Ex1601_ConfineVorticityCS.hlsl` | vorticity confinement |
| `Ex1601_DiffuseCS.hlsl` | diffusion iteration |
| `Ex1601_DivergenceCS.hlsl` | velocity divergence 계산 |
| `Ex1601_JacobiCS.hlsl` | pressure solve iteration |
| `Ex1601_ApplyPressureCS.hlsl` | pressure gradient 적용 |
| `Ex1601_AdvectionCS.hlsl` | semi-Lagrangian advection |
| `main.cpp` | command argument `1601` mapping |
| `Examples.vcxproj` | source/shader build registration |

## Import 메모

- core C++ files는 primary raw `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`와 hash가 일치합니다.
- runtime asset은 요구하지 않습니다.
- Ex1601 compute shaders는 Debug/Release x64에서 compute shader model `5.0`으로 등록되어 있습니다.
- 사용자 확인 기준으로 Debug/Release x64 모두 실행 확인 완료 상태입니다.
