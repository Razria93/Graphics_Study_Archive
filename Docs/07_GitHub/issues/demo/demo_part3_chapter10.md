# Part3 Chapter10 Geometry Pipeline Demo

## 요약

Point primitive 확장에서 시작하는 Geometry Pipeline 흐름이다.

흐름은 billboard, diagnostic normal, procedural fireball과 tessellation으로 이어진다.

## 핵심 목표

- Point primitive를 Geometry Shader에서 triangle-strip quad로 확장
- Surface position과 normal을 diagnostic line geometry로 확인
- Manual과 Distance Adaptive tessellation factor를 구분

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | Geometry·Normal·Tessellation screenshot | 아래 시각 정보에서 결과를 확인함 |
| Result image | 대표 rendered result 3장 | quad, normal, tessellation 결과를 기록함 |
| Video | 없음 | 정적 결과로 핵심 형태를 확인함 |

## 시각 정보

### Geometry Shader quad 기준선

Point 하나가 네 vertex triangle strip으로 확장되어 quad를 만드는 최소 Geometry Shader 경로다.

![Geometry Shader quad](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter10_01_geometry_shader.png?raw=true)

### Normal diagnostic geometry

Surface draw와 별도의 line geometry를 사용해 vertex normal의 위치와 방향을 확인한다.

![Normal diagnostic geometry](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter10_03_normal_lines.png?raw=true)

### Manual Tessellation

UI factor가 Hull Shader의 edge와 inside factor에 직접 반영되는 학습 경로다.

Distance Adaptive mode는 camera 거리에 따라 같은 factor를 계산한다.

이 mode는 사용자 확장으로 분리한다.

![Manual Tessellation](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter10_05_tessellation.png?raw=true)

## 구현 하이라이트

### 네 vertex triangle strip

중복 vertex와 degenerate triangle 없이 네 corner를 표준 strip 순서로 append한다.

- [Quad strip 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/BillboardPointsGeometryShader.hlsl#L29-L53)

### Manual과 Distance Adaptive factor 분리

Manual mode는 UI factor를 그대로 사용하고 Distance Adaptive mode는 near/far 거리 범위에서 계산한 factor를 명시적으로 선택한다.

- [Mode별 tessellation factor](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/TessellatedQuadHS.hlsl#L33-L76)
- [Mode별 UI와 factor 입력](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/ExampleApp.cpp#L476-L505)

### 처리 흐름

1. Point를 Geometry Shader에서 quad로 확장한다.
2. Camera-facing basis로 textured billboard를 구성한다.
3. Position과 normal에서 diagnostic line을 만든다.
4. Time과 primitive ID로 procedural fireball을 표시한다.
5. Hull·Domain Shader로 Manual 또는 Distance Adaptive tessellation을 적용한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void SelectTessellationFactorPseudo(bool distanceAdaptive, float uiFactor)
{
	if (uiFactor <= 0.0f) {
		return;
	}

	float factor = uiFactor;
	if (distanceAdaptive) {
		factor = CalculateDistanceAdaptiveFactor(cameraDistance);
	}

	for (int edge = 0; edge < 4; ++edge) {
		patch.edgeFactor[edge] = factor;
	}
	patch.insideFactor = factor;
}
```

원본 코드: [Mode별 tessellation factor](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/TessellatedQuadHS.hlsl#L33-L76)

## 검증 상태

- Step1–5 Debug/Release x64 build/run 성공
- 전체 application window PNG 5장 full decode·metadata·공개 안전성 확인
- Geometry, Demo, Topic과 Markdown validator 통과

## 구현 범위와 한계

- Distance Adaptive mode는 원래 Manual 학습 예제와 구분한 사용자 확장이다.
- Fireball의 시간 변화는 정적 결과만으로 핵심 형태를 확인할 수 있어 video를 필수로 두지 않는다.
- 강의 제공 runtime texture 원본은 직접 링크하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [Part3 Chapter10-13 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- [Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Step1 GeometryShader 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_01_GeometryShader.md)
- [Step3 NormalLines 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_03_NormalLines.md)
- [Step5 Tessellation 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_05_Tessellation.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
