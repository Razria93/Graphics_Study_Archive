# Swap Chain And Viewport

## 목적

Swap chain은 application의 render buffer와 window presentation을 연결하고 viewport는 render target 안에서 rasterized 결과가 놓일 영역을 정의한다. 이 문서는 back buffer, render target view, depth resource, viewport와 `Present()`가 하나의 frame 출력 경로를 이루는 관계를 설명한다.

## 책임 범위

- Swap chain과 back buffer의 presentation 역할을 설명한다.
- Render target view와 depth-stencil view가 resource를 output-merger에 연결하는 방식을 설명한다.
- Viewport가 clip-space 결과를 render target 영역으로 mapping하는 역할을 설명한다.
- Step2의 고정 resolution과 API 호출 순서는 [Chapter06 Step2 Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md)로 위임한다.
- 구현 흐름과 시각 자료는 `Docs/03_Demos`의 [Chapter06 Step2 Demo](../../03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)로 위임한다.
- Runtime resize 구현은 Chapter06 Step7·8에서 다룬다.
- build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 개념 흐름

1. Window handle, buffer format과 크기를 포함한 swap chain 조건을 정의한다.
2. Swap chain의 back buffer resource를 얻어 render target view를 만든다.
3. 같은 frame 크기의 depth texture와 depth-stencil view를 만든다.
4. Viewport의 위치, 크기와 depth 범위를 정한다.
5. Render target과 depth view를 output-merger에 binding하고 frame을 그린다.
6. `Present()`로 완성된 back buffer를 window에 표시한다.

## 핵심 개념

### Swap Chain And Back Buffer

Swap chain은 여러 presentation buffer의 교체와 표시 시점을 관리한다. Application은 현재 back buffer에 render하고 `Present()`를 호출해 완성된 frame을 window presentation 경로로 넘긴다. Buffer count, format, swap effect와 synchronization 설정은 latency와 presentation 동작에 영향을 준다.

Back buffer는 texture resource이므로 그 자체만으로 output-merger target이 되지 않는다. Render target view를 만들면 pipeline이 해당 resource를 color output 대상으로 해석할 수 있다.

### Render Target And Depth View

Render target view는 pixel shader의 color output을 받을 resource view다. Depth-stencil view는 각 fragment의 depth·stencil test와 update를 담당하는 별도 resource view다. 두 resource는 같은 frame 영역을 설명하도록 크기와 sample 조건을 맞춰야 한다.

View는 resource 데이터를 복제하지 않고 pipeline에서 사용할 형식과 역할을 정의한다. Resource lifetime과 view lifetime은 COM ownership 규칙을 따르며 resize 시에는 이전 back buffer에 연결된 view를 놓고 새 buffer에서 다시 생성해야 한다.

### Viewport And Presentation Surface

Viewport는 normalized device coordinate를 render target의 pixel rectangle과 depth range로 mapping한다. Swap chain buffer 크기와 viewport가 같으면 전체 window client area를 사용하고, 더 작은 viewport를 사용하면 render target 일부 영역만 rasterization 대상으로 삼을 수 있다.

Window 크기가 바뀌면 viewport만 바꾸는 것으로 충분하지 않을 수 있다. Back buffer와 depth resource 크기도 새 client area에 맞춰 재생성해야 하므로 resize는 presentation resource 전체의 lifetime 문제다.

## 데모 연결

Chapter06 Step2는 고정 client size에서 swap chain, back buffer view, depth resource와 viewport를 만든 뒤 rotating cube frame을 `Present(1, 0)`으로 표시한다. Step7과 Step8은 viewport와 window resize 책임을 별도 단계에서 확장한다.

## 한계

- Flip model과 legacy blit model의 세부 비교를 다루지 않는다.
- Tearing, variable refresh rate, HDR과 color space 설정을 다루지 않는다.
- MSAA resolve와 multi-sampled swap chain trade-off를 상세히 비교하지 않는다.
- ResizeBuffers 호출 순서와 device-lost 복구는 후속 Example 책임으로 둔다.

## 관련 문서

- [Chapter06 Step2 InitializingD3D Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md)
- [Chapter06 Step2 InitializingD3D Demo](../../03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)
- [Device And Context](DeviceAndContext.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [DirectX11 Pipeline Topic Index](topic-index.md)
