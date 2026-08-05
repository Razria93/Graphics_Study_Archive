# DirectX11 Pipeline

이 폴더는 DirectX11 Pipeline 관련 graphics concept 문서의 정본 위치다.

## 범위

- 주요 개념: device/context, COM, buffer, shader stage, swap chain, viewport, dynamic texture upload, post-processing
- 연결 예제 후보: Part1_Chapter01-02, Part2_Chapter04, Part2_Chapter05-08
- 우선순위: P0

## 문서 목록

- [Topic Index](topic-index.md)
- [Device And Context](DeviceAndContext.md)
- [COM And Resource Lifetime](COMAndResourceLifetime.md)
- [Swap Chain And Viewport](SwapChainAndViewport.md)
- [Shader Stage](ShaderStage.md)
- [Post Processing And Bloom](PostProcessingAndBloom.md)
- [Shadertoy Runtime Inputs](ShadertoyRuntimeInputs.md)
- [Stencil Buffer And Mirror Rendering](StencilBufferAndMirrorRendering.md)
- [Depth Reconstruction And Fog](DepthReconstructionAndFog.md)

## 상태

- Topic 목록: 작성
- 상세 Topic 문서: 기존 pipeline Topic과 Stencil Buffer And Mirror Rendering, Depth Reconstruction And Fog 작성
- 연결 예제 검토: Part1·Part2 pipeline 예제와 Part3 Chapter13 Step1–3 현재 확인
- demo 연결: 관련 Example의 상세 Demo 연결 완료

## 다음 작업

1. Buffer And Input Layout 상세 Topic을 순차 승격한다.
2. Pipeline State Object 추상화는 공통 구현이 늘어날 때 별도 Topic 승격을 검토한다.
