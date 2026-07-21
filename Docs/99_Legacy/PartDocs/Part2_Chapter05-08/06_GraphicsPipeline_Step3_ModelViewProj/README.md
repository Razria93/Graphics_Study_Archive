# 06 GraphicsPipeline Step3 ModelViewProj

## 목적

D3D11 graphics pipeline에서 cube geometry를 model/view/projection 변환으로 화면에 배치하는 예제입니다. Step2의 window/device/swap chain 초기화 흐름 위에 constant buffer를 사용해 CPU에서 계산한 transform matrix를 vertex shader로 전달합니다.

## 핵심 키워드

- model matrix
- view matrix
- projection matrix
- constant buffer
- `XMMatrixRotationY`
- `XMMatrixLookAtLH`
- `XMMatrixPerspectiveFovLH`
- `VSSetConstantBuffers`
- depth clip

## 구현 흐름

1. `AppBase`에서 D3D11 window, device/context, swap chain, render target, depth stencil을 초기화합니다.
2. `ExampleApp`에서 cube vertex/index buffer와 constant buffer를 생성합니다.
3. 매 frame마다 model, view, projection matrix를 갱신합니다.
4. constant buffer를 `UpdateSubresource()`로 GPU에 복사합니다.
5. vertex shader가 constant buffer의 transform을 사용해 cube vertex를 clip space로 변환합니다.
6. IA/VS/RS/PS/OM pipeline state를 설정하고 indexed draw를 호출합니다.

## 핵심 코드

```cpp
m_constantBufferData.model = XMMatrixTranspose(XMMatrixRotationY(m_modelRotation));
m_constantBufferData.view = XMMatrixTranspose(XMMatrixLookAtLH(m_viewEye, m_viewFocus, m_viewUp));
m_constantBufferData.projection = XMMatrixTranspose(
    XMMatrixPerspectiveFovLH(m_projFovAngleY, m_aspect, m_nearZ, m_farZ));
```

CPU 쪽에서 model/view/projection matrix를 계산하고 shader에서 쓰기 좋은 형태로 전치합니다.

```cpp
m_context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &m_constantBufferData, 0, 0);
m_context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
```

constant buffer를 GPU에 갱신하고 vertex shader stage에 연결합니다. 이 예제의 핵심은 geometry 자체보다 transform data를 frame마다 shader로 전달하는 흐름입니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 링크 메모는 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj/source-comments.md`로 분리했습니다.
- `.vs/`, `x64/`, 중간 build folder, `.user`, `imgui.ini`, `.clang-format`는 archive에 포함하지 않았습니다.
- shader 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.
- 외부 asset은 없습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: Debug x64, Release x64 성공
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 source 구조, shader, ImGui/vcpkg dependency, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
