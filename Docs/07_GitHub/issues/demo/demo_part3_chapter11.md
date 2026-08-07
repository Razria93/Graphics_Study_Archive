# Part3 Chapter11 Texturing Techniques Demo

## 요약

Texture LOD에서 시작해 normal mapping과 height mapping으로 확장되는 다섯 단계다.

후반 흐름은 HDR image 표시와 bloom을 포함한 HDR post-process pipeline을 다룬다.

## 핵심 목표

- Tangent-space normal texture를 TBN basis로 lighting normal에 변환
- Height texture로 vertex position과 sphere silhouette 변형
- HDR scene, bloom pyramid, exposure·gamma composite 연결

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | Normal·Height·HDR screenshot | 아래 시각 정보에서 mapping과 pipeline을 확인함 |
| Result image | 대표 rendered result 3장 | normal, height, HDR 결과를 기록함 |
| Video | 없음 | 정적 screenshot으로 post-process 결과를 확인함 |

## 시각 정보

### Normal Mapping

Tangent-space normal texture가 TBN basis를 거쳐 lighting normal로 변환되어 평면 geometry에 미세한 방향 변화를 만든다.

![Normal Mapping](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter11_02_normal_mapping.png?raw=true)

### Height Mapping

Height sample을 vertex position에 적용해 shading뿐 아니라 sphere silhouette까지 변화시킨다.

![Height Mapping](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter11_03_height_mapping.png?raw=true)

### HDR Pipeline

HDR scene resolve, bloom pyramid와 exposure·gamma composite를 하나의 post-process chain으로 연결한다.

![HDR Pipeline](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter11_05_hdr_pipeline.png?raw=true)

## 구현 하이라이트

### Tangent-space normal 변환

Vertex stage가 TBN basis를 전달하고 Pixel Shader가 normal texture를 decode해 lighting 계산에 사용한다.

- [TBN 전달](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/BasicVertexShader.hlsl#L30-L56)
- [Normal texture 변환](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/BasicPixelShader.hlsl#L61-L82)

### HDR와 bloom composite

Downsampled bloom pyramid를 구성하고 HDR scene과 합성한 뒤 exposure와 gamma를 적용한다.

- [Bloom pyramid](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/PostProcess.cpp#L70-L118)
- [최종 composite](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/CombinePS.hlsl#L45-L65)

### 처리 흐름

1. 명시적 mip level로 texture LOD를 확인한다.
2. Normal texture와 TBN으로 shading normal을 바꾼다.
3. Height texture로 vertex position과 silhouette을 변형한다.
4. EXR input을 exposure·gamma display 경로로 표시한다.
5. HDR render target과 bloom pyramid를 최종 composite한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void CompositeHdrBloomPseudo(Texture hdrScene, float exposure)
{
	if (!hdrScene.IsValid()) {
		return;
	}

	Texture bloom = hdrScene;
	for (int level = 0; level < pyramidLevelCount; ++level) {
		bloom = DownsampleBloom(bloom);
	}

	ApplyExposureAndGamma(hdrScene, bloom, exposure);
}
```

원본 코드: [최종 composite](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/CombinePS.hlsl#L45-L65)

## 검증 상태

- Step1–5 Debug/Release x64 build/run 성공
- DirectXTex·OpenEXR runtime과 전체 창 PNG 5장 확인
- Capture full decode·metadata·공개 안전성과 validator 통과

## 구현 범위와 한계

- Height mapping은 vertex displacement이며 parallax occlusion mapping을 포함하지 않는다.
- HDRI·material 원본은 archive runtime dependency로 유지하고 직접 링크하지 않는다.
- Production tone mapper나 temporal exposure adaptation은 포함하지 않는다.

## 관련 문서

- [Part3 Chapter10-13 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- [Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Step2 NormalMapping 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/11_02_NormalMapping.md)
- [Step3 HeightMapping 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/11_03_HeightMapping.md)
- [Step5 HDRPipeline 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
