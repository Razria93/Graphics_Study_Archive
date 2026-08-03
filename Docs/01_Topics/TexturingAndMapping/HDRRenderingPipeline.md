# HDR Rendering Pipeline

## 목적

Scene luminance를 floating-point target에 보존하고 bloom, exposure, tone mapping과 gamma 변환을 거쳐 display color로 만드는 경로를 설명한다.

## 책임 범위

이 문서는 HDR buffer와 post-process stage의 책임을 다룬다. EXR file I/O, 개별 shader와 runtime resource binding은 Example README로 위임한다.

## 핵심 개념

### HDR scene buffer

LDR back buffer는 제한된 범위만 저장하지만 floating-point render target은 1보다 큰 luminance를 보존한다. Bloom이나 exposure는 이 높은 값을 잃기 전에 처리해야 한다.

### Bloom pyramid

밝은 영역을 여러 낮은 해상도로 downsample하면 넓은 범위의 glow를 비교적 적은 sample로 만들 수 있다. 다시 upsample한 결과를 원본 scene에 strength로 합성한다.

```cpp
// Pseudo C++: HDR display pipeline
float3 bloom = BuildBloomPyramid(sceneHDR);
float3 combined = sceneHDR + bloom * strength;
float3 mapped = 1.0 - exp(-combined * exposure);
float3 display = pow(mapped, 1.0 / gamma);
```

### Exposure와 gamma

Exposure는 scene luminance를 display 범위에 배치한다. Gamma encoding은 linear color를 display transfer에 맞게 변환한다. 두 연산은 목적이 다르므로 하나의 밝기 slider처럼 취급하지 않는다.

## 한계

- Tone mapping operator에 따라 highlight roll-off와 color saturation이 달라진다.
- Auto exposure는 시간에 따른 luminance adaptation과 안정화가 필요하다.
- Bloom은 scene lighting을 대체하지 않고 높은 luminance의 시각적 확산만 표현한다.

## 관련 문서

- [Post Processing And Bloom](../DirectX11Pipeline/PostProcessingAndBloom.md)
- [HDRI Example README](../../../Part3_Chapter10-13/11_TexturingTechniques_Step4_HDRI/README.md)
- [HDR Pipeline Example README](../../../Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/README.md)
- [Docs/03_Demos HDRI](../../03_Demos/Part3_Chapter10-13/11_04_HDRI.md)
- [Docs/03_Demos HDR Pipeline](../../03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
