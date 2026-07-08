# 01_DX11InitAndImGui

## 목표

DirectX11 device/swap chain을 초기화하고, CPU에서 갱신한 작은 canvas texture를 full-screen quad로 표시하며, ImGui overlay로 배경색을 조정하는 기본 실행 예제입니다.

## 핵심 키워드

- Win32 message loop
- D3D11 device / device context
- swap chain / back buffer
- render target view
- HLSL shader compile
- input layout
- dynamic texture
- shader resource view
- sampler state
- vertex/index buffer
- ImGui overlay

## 개념 정리

이 예제의 중심은 CPU 메모리의 픽셀 배열을 `ID3D11Texture2D`로 올리고, pixel shader가 `ShaderResourceView`로 그 texture를 읽어 화면에 출력하는 흐름입니다.

`RenderTargetView`는 GPU가 결과를 쓸 수 있는 대상이고, `ShaderResourceView`는 shader가 texture를 읽을 수 있게 해주는 view입니다. 같은 texture resource라도 어떤 view를 만드느냐에 따라 pipeline에서 읽기/쓰기 용도가 달라집니다.

## 구현 포인트

- Win32 window를 만들고 그 handle을 기준으로 swap chain을 생성합니다.
- back buffer에서 `RenderTargetView`를 만들어 화면 출력 대상으로 사용합니다.
- `VS.hlsl`, `PS.hlsl`를 파일에서 컴파일하고 input layout을 설정합니다.
- CPU가 매 프레임 `std::vector<Vec4>` 픽셀 배열을 만들고 `Map` / `memcpy` / `Unmap`으로 dynamic texture에 업로드합니다.
- quad vertex/index buffer를 만들고 canvas texture를 pixel shader resource로 바인딩해 그립니다.
- ImGui slider가 `backgroundColor`를 바꾸고, `Update()`가 그 값을 canvas 기본색으로 사용합니다.

## 핵심 코드 위치

| 위치 | 역할 |
| --- | --- |
| `main.cpp` | Win32 window, ImGui setup, message/render loop |
| `Example.h::Initialize` | D3D11 device/swap chain, render target, viewport, texture, geometry setup |
| `Example.h::InitShaders` | HLSL compile, shader object, input layout setup |
| `Example.h::Update` | CPU-side pixel buffer 생성과 dynamic texture upload |
| `Example.h::Render` | shader/resource binding과 indexed draw |
| `Example.h::Clean` | D3D resource release |

## 핵심 코드 흐름

이 예제에서 실제로 확인해야 할 흐름은 “window 생성” 자체보다, GPU가 그릴 대상과 shader가 읽을 texture를 어떻게 연결하는지입니다.

### 1. Swap chain과 back buffer를 화면 출력 대상으로 만든다

```cpp
swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
swapChainDesc.OutputWindow = window;
swapChainDesc.SampleDesc.Count = 1;
swapChainDesc.Windowed = TRUE;

D3D11CreateDeviceAndSwapChain(
    nullptr,
    D3D_DRIVER_TYPE_HARDWARE,
    nullptr,
    createDeviceFlags,
    featureLevelArray,
    1,
    D3D11_SDK_VERSION,
    &swapChainDesc,
    &swapChain,
    &device,
    nullptr,
    &deviceContext);
```

여기서 `swapChain`은 window에 표시될 buffer 교체 흐름을 만들고, `device`와 `deviceContext`는 이후 resource 생성과 draw command 기록에 사용됩니다.

```cpp
swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
device->CreateRenderTargetView(pBackBuffer, nullptr, &renderTargetView);
deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
```

back buffer를 `RenderTargetView`로 감싸야 output merger stage가 최종 색을 쓸 수 있습니다.

### 2. CPU가 쓸 수 있는 dynamic texture를 만들고 SRV로 노출한다

```cpp
textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
textureDesc.Usage = D3D11_USAGE_DYNAMIC;
textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
textureDesc.Width = canvasWidth;
textureDesc.Height = canvasHeight;

device->CreateTexture2D(&textureDesc, nullptr, &canvasTexture);
device->CreateShaderResourceView(canvasTexture, nullptr, &canvasTextureView);
```

`D3D11_USAGE_DYNAMIC`과 `D3D11_CPU_ACCESS_WRITE` 조합 때문에 CPU가 매 프레임 texture 내용을 다시 쓸 수 있습니다. 하지만 shader가 읽으려면 texture 자체가 아니라 `ShaderResourceView`를 binding해야 합니다.

### 3. CPU 픽셀 배열을 texture로 업로드한다

```cpp
std::vector<Vec4> pixels(
    canvasWidth * canvasHeight,
    Vec4{ backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3] });

D3D11_MAPPED_SUBRESOURCE mapped;
deviceContext->Map(canvasTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
memcpy(mapped.pData, pixels.data(), pixels.size() * sizeof(Vec4));
deviceContext->Unmap(canvasTexture, 0);
```

CPU 메모리에서 만든 `pixels`를 GPU texture memory로 복사하는 부분입니다. `Map`으로 CPU가 쓸 수 있는 포인터를 얻고, 복사가 끝나면 `Unmap`으로 GPU가 다시 사용할 수 있게 돌려줍니다.

### 4. Canvas texture를 pixel shader에 묶고 quad를 그린다

```cpp
deviceContext->VSSetShader(vertexShader, 0, 0);
deviceContext->PSSetShader(pixelShader, 0, 0);

deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

deviceContext->PSSetSamplers(0, 1, &colorSampler);
deviceContext->PSSetShaderResources(0, 1, &canvasTextureView);
deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
deviceContext->DrawIndexed(indexCount, 0, 0);
```

full-screen quad는 화면 전체를 덮는 geometry이고, pixel shader는 각 pixel에서 `canvasTextureView`를 읽습니다. 결과적으로 CPU가 만든 작은 canvas가 화면에 확대되어 보입니다.

## 헷갈렸던 지점

- `Resource`와 `View`의 차이: resource는 실제 GPU 메모리이고, view는 shader/render pipeline이 그 메모리에 접근하는 방식입니다.
- `std::vector`와 graphics vector의 차이: 이 예제의 `std::vector<Vec4>`는 CPU-side pixel storage이고, 수학 벡터 계산 타입이 아닙니다.
- CPU texture upload 흐름: CPU에서 만든 픽셀 배열은 `Map`으로 GPU texture memory에 접근한 뒤 `memcpy`로 복사하고 `Unmap`으로 GPU 사용 가능 상태로 돌려줍니다.

## 이해한 내용

DX11 초기화 예제는 단순히 창을 띄우는 코드가 아니라 이후 모든 예제의 최소 렌더링 루프를 구성합니다. device/context/swap chain/render target을 만든 뒤 shader와 geometry를 묶어 매 프레임에 어떤 resource를 읽고 어디로 출력할지 명확히 지정해야 합니다.

## 추가 탐구 / 고찰

- 현재 예제는 `Example.h`에 구현이 많이 들어 있어 archive 정리 과정에서 `.cpp` 분리를 검토할 수 있습니다.
- `Sleep(100)`은 시연을 의도적으로 느리게 만드는 역할로 보이며, 실제 demo frame loop에서는 제거하거나 frame timing으로 대체할 수 있습니다.
- shader file path가 실행 working directory에 의존할 수 있으므로 build/run 확인 때 별도 기록이 필요합니다.

## 실행 결과

- Build/run status: 미확인
- Capture: 예정

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive의 학습 예제로 먼저 정리합니다. 구현 설명에 필요한 짧은 코드 조각은 사용할 수 있지만, 강의 기반 파일 전체를 public repo에 그대로 옮기지는 않습니다. public 후보로 보려면 강의 기반 코드 범위, 직접 작성한 범위, 실행 캡처 권리 문제를 별도로 확인해야 합니다.

## 관련 문서

- [Part1 Chapter01-02 Docs](../README.md)
- [Example status](status.md)
- [Part Import 작업 방식](../../_repo/workflow/part-import-workflow.md)
- [Chapter Study 정리 방식](../../_repo/workflow/chapter-study-workflow.md)
- [Part1 import manifest](../../_repo/manifests/Part1_Chapter01-02.md)
