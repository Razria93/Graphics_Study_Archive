# Shader Stage

## 목적

Shader stage는 graphics pipeline의 각 처리 단계가 어떤 입력을 받고 어떤 출력을 다음 단계로 전달하는지 설명한다. Vertex stage, rasterization과 pixel stage의 책임 경계를 중심으로 다루며 특정 예제 함수나 API 호출은 관련 Example과 Demo로 위임한다.

## 책임 범위

- Stage input과 output contract의 역할을 설명한다.
- Vertex stage가 per-vertex data를 변환하고 attribute를 전달하는 책임을 설명한다.
- Rasterization이 vertex output을 fragment input으로 보간하는 경계를 설명한다.
- Pixel stage가 fragment별 출력값을 결정하는 책임을 설명한다.
- CPU shader stage 모사와 실제 GPU presentation shader를 구분한다.
- Step6 고유 함수와 rotation은 [Step6 ShadersConcept Example](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/README.md)로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos`의 [Step6 ShadersConcept Demo](../../03_Demos/Part2_Chapter04/06_ShadersConcept.md)로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification`의 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.
- 실제 D3D11 semantic, stage별 constant buffer와 UV 분기 구현은 [Chapter06 Step4 Shaders Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders/README.md)로 위임한다.
- 해당 구현의 시각 결과는 [Chapter06 Step4 Shaders Demo](../../03_Demos/Part2_Chapter05-08/06_Shaders.md)로 위임한다.

## 핵심 개념

### Stage Input And Output Contract

각 stage는 필요한 data를 구조화된 입력으로 받고 다음 stage가 소비할 출력을 만든다. Position, color, normal과 UV처럼 vertex마다 존재하는 attribute는 stage 경계를 지날 때 의미와 보간 방식을 유지해야 한다. 명시적인 contract는 transform, interpolation과 shading 책임이 한 함수에 섞이는 것을 줄인다.

### Vertex Stage

Vertex stage는 vertex마다 한 번 실행되며 position을 pipeline의 다음 좌표 공간으로 변환한다. Color와 UV처럼 후속 단계에서 사용할 attribute도 vertex output으로 전달한다. 여러 primitive가 같은 vertex를 공유할 수 있지만 개념적으로는 입력 vertex와 출력 vertex의 대응을 유지한다.

### Rasterization And Interpolation Boundary

Rasterization은 transformed vertex로 primitive coverage를 계산하고 covered sample에 대응하는 fragment를 만든다. Vertex output attribute는 barycentric weight 같은 보간 규칙으로 fragment input으로 변환된다. Perspective projection이 포함된 pipeline에서는 affine interpolation과 perspective-correct interpolation을 구분해야 한다.

### Pixel Stage

Pixel stage는 보간된 fragment input과 texture, material 또는 조명 data를 사용해 color 같은 출력을 결정한다. Depth test, blending과 render target write의 정확한 순서는 API와 pipeline 설정에 따라 달라질 수 있으므로 pixel stage의 계산 책임과 output merger의 저장 책임을 분리해 이해한다.

### Semantic And Constant Buffer Binding

Direct3D input layout과 HLSL 구조체는 `POSITION`, `COLOR`, `TEXCOORD` 같은 semantic으로 vertex data의 의미를 연결한다. Stage input과 output의 semantic 이름·index·type이 대응해야 attribute가 의도한 경로로 전달된다.

Constant buffer register는 stage별 resource slot이다. 같은 draw에서 vertex shader의 transform data를 `b0`, pixel shader의 분기 parameter를 `b1`처럼 분리할 수 있다. CPU 구조체는 HLSL packing과 맞도록 16-byte 경계를 지켜야 하며, buffer 생성뿐 아니라 올바른 stage와 slot에 binding했는지도 함께 확인한다.

### CPU Simulation And GPU Presentation

Shader stage의 contract는 CPU 함수로도 모사할 수 있다. CPU vertex 함수가 transform과 attribute 전달을 수행하고 CPU pixel 함수가 fragment color를 결정하면 stage 사이 data 흐름을 직접 관찰할 수 있다. 이 결과를 화면에 표시하기 위해 별도의 GPU shader가 framebuffer texture를 sampling할 수 있지만, presentation shader가 CPU에서 모사한 학습 stage와 같은 계산을 수행하는 것은 아니다.

## 한계

- Tessellation, geometry, compute shader stage는 포함하지 않는다.
- Shader reflection, resource binding layout과 runtime shader hot reload를 다루지 않는다.
- GPU wave, occupancy와 instruction scheduling 같은 hardware 실행 세부사항을 다루지 않는다.
- Depth-stencil, blending과 render target write는 stage 경계 설명에 필요한 범위만 언급한다.
- Step6의 CPU 모사는 실제 GPU parallel execution과 성능 특성을 재현하지 않는다.

## 관련 문서

- [Step6 ShadersConcept Example](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/README.md)
- [Step6 ShadersConcept Demo](../../03_Demos/Part2_Chapter04/06_ShadersConcept.md)
- [Chapter06 Step4 Shaders Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders/README.md)
- [Chapter06 Step4 Shaders Demo](../../03_Demos/Part2_Chapter05-08/06_Shaders.md)
- [Triangle Rasterization](../Rasterization/TriangleRasterization.md)
- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [DirectX11 Pipeline Topic Index](topic-index.md)
