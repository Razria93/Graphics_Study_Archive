# Device And Context

## 목적

D3D11 device는 resource와 pipeline object를 생성하는 주체이고 device context는 생성된 object를 pipeline에 binding하고 draw command를 제출하는 주체다. 이 문서는 두 interface의 책임과 feature level 선택이 application 초기화에 미치는 의미를 설명한다.

## 책임 범위

- Device와 immediate context의 역할을 구분한다.
- Hardware driver와 feature level 선택 관계를 설명한다.
- Resource 생성과 command 제출을 분리해 설명한다.
- COM ownership은 [COM And Resource Lifetime](COMAndResourceLifetime.md)으로 위임한다.
- Step2의 실제 API 호출은 [Chapter06 Step2 Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md)로 위임한다.
- 구현 흐름과 시각 자료는 `Docs/03_Demos`의 [Chapter06 Step2 Demo](../../03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 개념 흐름

1. Application이 사용할 driver type과 feature level 후보를 준비한다.
2. D3D11 runtime이 조건에 맞는 device와 immediate context를 생성한다.
3. Device로 buffer, texture, view, shader와 pipeline state object를 만든다.
4. Context로 resource와 state를 pipeline stage에 binding한다.
5. Context에 draw command를 제출하고 swap chain으로 결과를 표시한다.

## 핵심 개념

### Device As Resource Factory

`ID3D11Device`는 GPU resource와 immutable pipeline object를 생성한다. Buffer와 texture는 데이터를 저장하고 view는 resource를 pipeline의 특정 용도로 해석한다. Shader와 input layout, rasterizer·depth-stencil state도 device를 통해 생성한다.

Device 생성은 현재 adapter와 driver가 지원하는 feature level을 함께 결정한다. Feature level은 API version 문자열이 아니라 해당 device에서 보장되는 graphics capability 집합이므로 실제 반환값을 보관하고 이후 resource·shader 요구사항과 비교해야 한다.

### Context As Command Submission Interface

`ID3D11DeviceContext`는 render target, shader, buffer와 state를 pipeline에 binding하고 clear·draw·resource update command를 제출한다. Resource를 소유하거나 생성하는 책임과 현재 frame에 사용할 상태를 선택하는 책임을 분리하면 초기화와 frame 처리 경계가 명확해진다.

Immediate context는 application이 제출한 command를 단일 순서로 처리하는 기본 context다. Deferred context와 command list는 별도 실행 모델이며 현재 예제 범위에 포함하지 않는다.

### Initialization Boundary

Device와 context만 생성해도 graphics interface를 사용할 준비는 되지만 화면에 표시되는 frame은 만들어지지 않는다. Window presentation에는 swap chain과 back buffer view가 추가로 필요하고, 실제 draw에는 shader, buffer, viewport와 output-merger resource가 필요하다.

Chapter06 Step1은 device·context의 ownership만 분리해 확인한다. Step2는 같은 interface를 window와 frame pipeline에 연결해 resource 생성과 command 제출의 실제 경계를 보여준다.

## 데모 연결

Chapter06 Step2는 device로 swap chain dependent resource, depth resource, shader와 buffer를 만들고 immediate context로 viewport와 pipeline binding을 설정해 indexed cube draw를 제출한다. 구체적인 호출 순서와 시각 결과는 [상세 Demo](../../03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)에서 확인한다.

## 한계

- Adapter enumeration, software·WARP fallback과 device-lost recovery를 다루지 않는다.
- Deferred context, command list와 multithreaded command recording을 다루지 않는다.
- Feature level별 세부 capability 표를 복제하지 않는다.
- Driver 내부 scheduling과 GPU execution timing을 단정하지 않는다.

## 관련 문서

- [Chapter06 Step1 COM Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/README.md)
- [Chapter06 Step2 InitializingD3D Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md)
- [Chapter06 Step2 InitializingD3D Demo](../../03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)
- [COM And Resource Lifetime](COMAndResourceLifetime.md)
- [Swap Chain And Viewport](SwapChainAndViewport.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [DirectX11 Pipeline Topic Index](topic-index.md)
