# Part2 Chapter08 Shader Experiments Demo

## 요약

Chapter08은 surface rim lighting에서 시작해 GPU post-processing과 procedural full-screen shader로 확장되는 shader experiment 흐름이다. 대표 결과는 서로 다른 세 축인 silhouette shading, bloom filter chain과 시간 기반 star shader를 보여준다.

## 핵심 목표

- Normal과 view direction으로 view-dependent rim contribution 구성
- Threshold·downsample·blur·composite bloom filter chain 연결
- Time·resolution·texture channel을 full-screen procedural shader에 전달

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | Step1·Step6·Step7 screenshot | 아래 시각 정보에서 shader 결과를 확인함 |
| Result image | Step1·Step6·Step7 rendered result | rim, bloom, star 결과를 기록함 |
| Video | 없음 | 정적 결과만으로 구현과 출력을 설명함 |

## 시각 정보

### Step1 — Rim Lighting

검은 배경의 Dragon 외곽을 따라 파란 rim이 나타난다. Normal과 view direction이 수직에 가까워질수록 rim contribution이 커지며 UI의 color·power·strength가 윤곽의 색과 폭을 제어한다.

![Step1 Rim Lighting](https://github.com/Razria93/Graphics_Study_Archive/blob/b4feaf756ab197f896934adb9038972fb8923285/Docs/_assets/captures/part2_chapter08_01_rim_lighting.png?raw=true)

- 입력 또는 상태 변화: 파란 rim color, power 2.5, strength 1.25
- 관찰 결과: 어두운 surface와 구분되는 view-dependent silhouette 강조
- 구현 목적: surface normal과 eye direction만으로 만드는 stylized edge lighting 확인

### Step6 — Bloom Post-Processing

밝은 skybox와 sphere highlight가 threshold를 통과한 뒤 주변으로 부드럽게 확산된다. Scene render와 blur 결과를 다시 합성해 원본 형태를 유지하면서 glow를 더한다.

![Step6 Bloom](https://github.com/Razria93/Graphics_Study_Archive/blob/13d90c183379f3b8a5b0b90464d8297709d3f634/Docs/_assets/captures/part2_chapter08_06_bloom_effect.png?raw=true)

- 입력 또는 상태 변화: sphere scene, bloom threshold 0.3, strength 1.0
- 관찰 결과: 고휘도 영역 주변의 glow와 원본 scene 합성
- 구현 목적: threshold·downsample·blur·composite로 이어지는 GPU post-process chain 확인

### Step7 — Procedural Star

Full-screen pixel shader가 누적 시간, 현재 resolution과 texture channel을 사용해 star surface와 corona를 합성한다. 정지 frame에서도 중심 표면 noise와 바깥 glow의 서로 다른 주파수 구조를 확인할 수 있다.

![Step7 Shadertoy](https://github.com/Razria93/Graphics_Study_Archive/blob/7b516a72cea5a40e981a881d9fe24115410fce7f/Docs/_assets/captures/part2_chapter08_07_shadertoy.png?raw=true)

- 입력 또는 상태 변화: 누적 `iTime`, 현재 `iResolution`, texture channel 0
- 관찰 결과: procedural noise로 구성된 star surface와 corona
- 구현 목적: Shadertoy 형태의 runtime input을 DirectX11 full-screen pass에 연결

## 구현 하이라이트

### View angle 기반 rim contribution

정규화한 normal과 eye direction의 내적을 반전해 silhouette 쪽에서 커지는 rim base를 만든다. Power 또는 smoothstep shaping을 거친 값을 color와 strength에 곱해 surface lighting에 더한다.

- [Rim base와 shaping 적용](https://github.com/Razria93/Graphics_Study_Archive/blob/905120c0a305f1efb1d08bfe2459b137dd05a0f8/Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/BasicPixelShader.hlsl#L59-L70)

### Threshold·blur·composite filter chain

Back buffer를 shader-readable texture로 복사하고 threshold pass 뒤에 downsample과 separable blur를 반복한다. 마지막 pass는 blur 결과와 원본을 합성하며 resize 시 크기 의존 filter chain을 다시 만든다.

- [Back buffer 복사와 filter 실행](https://github.com/Razria93/Graphics_Study_Archive/blob/b939291f87e7cf84f02b8519fa2b2aa06fd8da42/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L153-L164)
- [Threshold·downsample·blur 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/b939291f87e7cf84f02b8519fa2b2aa06fd8da42/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L168-L241)
- [원본 합성과 resize 재구성](https://github.com/Razria93/Graphics_Study_Archive/blob/b939291f87e7cf84f02b8519fa2b2aa06fd8da42/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L255-L265)

### Multi-frequency star surface와 corona

여러 주파수의 procedural noise를 시간에 따라 이동시키고 radial mask로 star 본체와 바깥 corona를 나눈다. Texture channel의 밝기 입력과 noise를 결합해 surface 세부와 glow를 만든다.

- [Texture 입력과 multi-frequency noise](https://github.com/Razria93/Graphics_Study_Archive/blob/6d0823763dffebd77c60d029e114efafcf73c3b8/Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/StarPixelShader.hlsl#L58-L94)
- [Star surface와 corona 합성](https://github.com/Razria93/Graphics_Study_Archive/blob/6d0823763dffebd77c60d029e114efafcf73c3b8/Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/StarPixelShader.hlsl#L98-L127)

### 처리 흐름

1. Step1에서 normal·view angle 기반 rim lighting을 surface에 더한다.
2. Step2–5에서 cubemap sampling, environment reflection, IBL과 Fresnel로 확장한다.
3. Step6에서 scene 결과를 threshold·downsample·blur·composite post-process chain에 연결한다.
4. Step7에서 time·resolution·texture channel을 받는 full-screen procedural shader로 전환한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void ApplyBloomFilterChainPseudo(Texture scene, Size renderSize)
{
	if (!scene.IsValid() || renderSize.IsEmpty()) {
		return;
	}

	Texture bright = ApplyThreshold(scene);
	for (int level = 0; level < blurPassCount; ++level) {
		bright = DownsampleAndBlur(bright);
	}

	CompositeSceneAndBloom(scene, bright);
}
```

원본 코드: [Threshold·downsample·blur 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/b939291f87e7cf84f02b8519fa2b2aa06fd8da42/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L168-L241)

## 검증 상태

- Build/Run: Chapter08 Step1–7 Debug/Release x64 성공
- Capture/Result: Step1–7 전체 창 PNG 확보, 1282×992 full decode와 공개 안전성 확인
- Video: 본문은 정적 결과만으로 구현과 출력이 이해되도록 구성

## 구현 범위와 한계

- 포함: Rim lighting, cubemap·environment mapping, IBL·Fresnel, bloom과 Shadertoy runtime input
- 한계: 학습용 DirectX11 shader experiment이며 production renderer의 tone mapping, exposure adaptation과 multi-pass Shadertoy runtime은 포함하지 않는다.
- Asset: 강의 제공 또는 출처 정보가 불완전한 runtime asset 원본은 첨부하거나 직접 링크하지 않고, 직접 실행해 생성한 rendered evidence만 공개한다.

## 관련 문서

### Chapter 안내

- [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/README.md)
- [Chapter05-08 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
- [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### 대표 구현

- Step1 RimLighting: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/08_01_RimLighting.md)
- Step6 BloomEffect: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/08_06_BloomEffect.md)
- Step7 Shadertoy: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md)

### 관련 개념

- [Rim Lighting](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/01_Topics/LightingAndShading/RimLighting.md)
- [Post Processing And Bloom](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- [Shadertoy Runtime Inputs](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md)
