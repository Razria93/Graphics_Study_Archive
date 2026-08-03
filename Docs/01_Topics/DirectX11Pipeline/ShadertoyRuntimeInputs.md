# Shadertoy Runtime Inputs

## 목적

Full-screen procedural pixel shader가 frame time, output resolution과 texture channel을 입력받아 시간 기반 화면을 만드는 일반 구조를 설명한다.

## 책임 범위

- 이 문서는 Shadertoy 계열 runtime 입력과 DirectX11 연결 원리를 다룬다.
- Chapter08 Step7의 class, 함수와 시각 결과는 [Example README](../../../Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/README.md)와 [상세 Demo](../../03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md)로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 핵심 개념

### Full-screen shader 실행

Shadertoy 계열 fragment shader는 scene mesh 대신 화면 전체를 덮는 primitive를 사용한다. Vertex shader는 clip-space position과 UV를 전달하고 pixel shader가 각 pixel의 최종 color를 계산한다. DirectX11에서는 full-screen triangle 또는 quad와 pixel shader로 같은 역할을 구성할 수 있다.

### Time 입력

Runtime은 frame delta를 누적한 시간을 constant buffer에 기록한다. Shader는 이 값을 noise coordinate, rotation, phase와 animation parameter에 사용한다. Frame 수가 아니라 경과 시간을 사용하면 frame rate가 달라도 변화 속도를 일정하게 유지할 수 있다.

### Resolution 입력

Shader는 output width와 height로 UV 또는 pixel coordinate를 정규화하고 aspect ratio를 보정한다. Resolution을 고정값으로 두면 window resize 후 원이나 sphere가 늘어나므로 현재 render target 크기를 전달해야 한다.

```text
aspect = resolution.x / resolution.y
centered = uv - 0.5
centered.x *= aspect
```

### Texture channel

Texture channel은 procedural shader가 참조하는 image, noise, lookup data를 shader resource slot에 연결한다. Runtime은 channel 번호와 resource binding을 일치시키고 sampler의 filtering과 address mode를 명시한다. 외부 texture를 공개 산출물에 사용할 때는 shader와 별도로 출처와 재배포 권리를 확인한다.

### Resize와 resource lifetime

Window resize는 swap chain, render target, viewport와 resolution constant를 함께 갱신한다. Full-screen filter가 자체 크기 의존 texture나 viewport를 보유하면 같은 시점에 다시 만들어야 한다. Minimize의 0×0 크기에서는 resource 재생성을 건너뛰고 restore 후 유효한 크기로 다시 구성한다.

## 한계

- Shadertoy web runtime의 전체 uniform과 multi-pass buffer 계약을 정의하지 않는다.
- Mouse, audio, keyboard와 network input은 다루지 않는다.
- 개별 procedural effect의 noise 수식과 색상 선택은 상세 Demo 책임으로 둔다.

## 관련 문서

- Verification: [`Docs/02_Verification/Part2_Chapter05-08/verification-index.md`](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- Demo: [`Docs/03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md`](../../03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md)
- [Shader Stage](ShaderStage.md)
- [Swap Chain And Viewport](SwapChainAndViewport.md)
- [Post Processing And Bloom](PostProcessingAndBloom.md)
- [Chapter08 Step7 Example](../../../Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/README.md)
- [Chapter08 Step7 Demo](../../03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md)
