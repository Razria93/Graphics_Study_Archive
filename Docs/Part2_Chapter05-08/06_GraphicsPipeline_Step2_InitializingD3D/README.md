# 06 GraphicsPipeline Step2 InitializingD3D

## 목적

D3D11 window application의 기본 초기화 흐름을 구성하는 예제입니다. Win32 window, D3D11 device/context, swap chain, render target, depth stencil, viewport, rasterizer state, ImGui backend, shader compilation, vertex/index/constant buffer를 연결해 색상 큐브를 렌더링합니다.

## 핵심 키워드

- Win32 message loop
- `D3D11CreateDeviceAndSwapChain`
- swap chain
- render target view
- depth stencil view
- viewport
- rasterizer state
- HLSL shader compilation
- input layout
- vertex buffer / index buffer / constant buffer
- ImGui DX11 backend

## 구현 흐름

1. `AppBase`에서 window class와 main window를 생성합니다.
2. D3D11 device, immediate context, swap chain을 생성합니다.
3. back buffer로 render target view를 만들고 depth stencil buffer/view를 준비합니다.
4. viewport와 rasterizer state를 설정합니다.
5. ImGui Win32/DX11 backend를 초기화합니다.
6. `ExampleApp`에서 cube geometry, shader, input layout, constant buffer를 준비합니다.
7. 매 frame마다 constant buffer를 갱신하고 IA/VS/RS/PS/OM pipeline state를 설정한 뒤 indexed draw를 호출합니다.

## 핵심 코드

```cpp
D3D11CreateDeviceAndSwapChain(
    0, driverType, 0, createDeviceFlags, featureLevels,
    ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &sd, &swapChain, &device,
    &featureLevel, &context);
```

이 호출은 device/context와 swap chain을 한 번에 생성합니다. Step1 COM에서 확인한 device 생성 흐름이 실제 window back buffer와 연결되는 지점입니다.

```cpp
m_context->IASetInputLayout(m_basicInputLayout.Get());
m_context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
m_context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
m_context->DrawIndexed(UINT(m_indices.size()), 0, 0);
```

이 부분은 CPU에서 만든 cube vertex/index buffer를 Input-Assembler stage에 연결하고 indexed draw를 실행합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 링크 메모는 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/source-comments.md`로 분리했습니다.
- `.vs/`, `x64/`, 중간 build folder, `.user`, `imgui.ini`, `.clang-format`는 archive에 포함하지 않았습니다.
- shader 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.
- 외부 asset은 없습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 source 구조, shader, ImGui/vcpkg dependency, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
