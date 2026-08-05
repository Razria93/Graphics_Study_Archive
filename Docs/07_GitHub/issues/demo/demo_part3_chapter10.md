# Part3 Chapter10 Geometry Pipeline Demo

## 요약

Point primitive 확장에서 시작해 billboard, diagnostic normal, procedural fireball과 tessellation으로 이어지는 Geometry Pipeline 흐름이다.

## 결과

### Geometry Shader quad 기준선

Point 하나가 네 vertex triangle strip으로 확장되어 quad를 만드는 최소 Geometry Shader 경로다.

![Geometry Shader quad](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter10_01_geometry_shader.png?raw=true)

### Normal diagnostic geometry

Surface draw와 별도의 line geometry를 사용해 vertex normal의 위치와 방향을 확인한다.

![Normal diagnostic geometry](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter10_03_normal_lines.png?raw=true)

### Manual Tessellation

UI factor가 Hull Shader의 edge와 inside factor에 직접 반영되는 원래 학습 경로다. Distance Adaptive mode는 camera 거리에 따라 같은 factor를 계산하는 사용자 확장으로 분리한다.

![Manual Tessellation](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter10_05_tessellation.png?raw=true)

## 핵심 구현

### 네 vertex triangle strip

중복 vertex와 degenerate triangle 없이 네 corner를 표준 strip 순서로 append한다.

- [Quad strip 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/BillboardPointsGeometryShader.hlsl#L29-L53)

### Manual과 Distance Adaptive factor 분리

Manual mode는 UI factor를 그대로 사용하고 Distance Adaptive mode는 near/far 거리 범위에서 계산한 factor를 명시적으로 선택한다.

- [Mode별 tessellation factor](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/TessellatedQuadHS.hlsl#L33-L76)
- [Mode별 UI와 factor 입력](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/ExampleApp.cpp#L476-L505)

## 처리 흐름

1. Point를 Geometry Shader에서 quad로 확장한다.
2. Camera-facing basis로 textured billboard를 구성한다.
3. Position과 normal에서 diagnostic line을 만든다.
4. Time과 primitive ID로 procedural fireball을 표시한다.
5. Hull·Domain Shader로 Manual 또는 Distance Adaptive tessellation을 적용한다.

## 구현 범위와 한계

- Distance Adaptive mode는 원래 Manual 학습 예제와 구분한 사용자 확장이다.
- Fireball의 시간 변화는 정적 결과만으로 핵심 형태를 확인할 수 있어 video를 필수로 두지 않는다.
- 강의 제공 runtime texture 원본은 직접 링크하지 않고 rendered evidence만 사용한다.

## 검증

- Step1–5 Debug/Release x64 build/run 성공
- 전체 application window PNG 5장 full decode·metadata·공개 안전성 확인
- Geometry, Demo, Topic과 Markdown validator 통과

## 더 자세히 보기

- [Part3 Chapter10-13 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- [Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Step1 GeometryShader 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_01_GeometryShader.md)
- [Step3 NormalLines 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_03_NormalLines.md)
- [Step5 Tessellation 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_05_Tessellation.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
