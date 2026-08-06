# Part2 Chapter04 CPU Software Rasterization Demo

## 요약

`Part2_Chapter04`는 triangle coverage와 barycentric interpolation에서 시작해 2D transform, depth test,
culling, perspective interpolation과 CPU lighting으로 확장되는 software rasterization 학습 흐름이다.
Step8 PerspectiveProjection을 Chapter 대표 결과로 두고 Step10 Lights를 기술 보조, Step1A Triangle To Circle을
Personal Extension, Step4 Animation2D를 시간 변화 사례로 연결한다.

## 핵심 목표

- Edge function과 barycentric weight 기반의 triangle coverage를 확인한다.
- Z 기반 projection과 reciprocal-depth 보정의 차이를 시각적으로 비교한다.
- Directional, Point, Spot Light의 밝기 분포 차이를 확인한다.
- Triangle fan과 계층적 orbit으로 사용자 확장과 시간 변화를 연결한다.

## Demo Assets

| Type | Asset | Purpose |
| --- | --- | --- |
| Input screenshot | 없음 | 구현 단계별 결과를 비교하므로 공통 입력 화면을 사용하지 않는다. |
| Result screenshot | Step1A, Step8, Step10 capture | rasterization, perspective, light 결과를 확인한다. |
| Result image | Step10 light comparison | Light type별 밝기 분포를 비교한다. |
| Video | Step1A interaction video | triangle fan segment 조정 결과를 확인한다. |

## 시각 정보

### Step1A — Triangle To Circle Personal Extension

Step1의 단일 triangle rasterizer를 사용자가 triangle fan으로 확장했다.
Segment를 32로 조정해 같은 반지름과 color interpolation을 유지한 결과를 확인할 수 있다.

![Step1A Triangle To Circle 32 segments](https://github.com/Razria93/Graphics_Study_Archive/blob/05e496ede9b47dcaae6299446dd86bf754d574eb/Docs/_assets/captures/part2_chapter04_01a_triangle_to_circle_segments_32.png?raw=true)

### Step8 — Perspective-Correct Interpolation

같은 triangle mesh에서 Z 기반 크기 변화와 interpolation 방식을 함께 바꾼다.
Affine weight로 휘어진 checker가 reciprocal-depth 보정 뒤 안정된 형태로 나타나는 결과를 확인한다.

![Step8 Perspective-Correct Interpolation](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Docs/_assets/captures/part2_chapter04_08_perspective_projection_correct.png?raw=true)

### Step10 — Directional·Point·Spot Light 비교

같은 geometry, material과 Light parameter에서 type만 바꾼다.
Directional의 전역 방향, Point의 거리 감쇠와 Spot의 cone 집중이 바꾸는 밝기 분포를 비교한다.

![Step10 Directional Point Spot Light Comparison](https://github.com/Razria93/Graphics_Study_Archive/blob/512882ac239f461f80ae1b4ad836aeca22906f28/Docs/_assets/captures/part2_chapter04_10_lights_comparison.png?raw=true)

## 구현 하이라이트

### Triangle Coverage와 Attribute Interpolation

각 triangle의 screen-space bounding box를 순회하며 edge function으로 내부 pixel을 판정한다.
Barycentric weight로 vertex attribute를 보간하며, 이 기반은 이후 depth, texture coordinate와 lighting input까지 이어진다.

- [Edge function 기반 coverage와 barycentric weight 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L117-L156)

### Perspective Projection과 보간 보정

Step8은 vertex Z에 따라 화면 좌표를 축소하는 간소화된 projection을 적용한다.
Raster space의 affine weight를 vertex의 eye-relative Z로 다시 계산해 color와 UV를 보정한다.
Near/far clipping과 일반적인 clip-space pipeline은 포함하지 않는다.

- [Z 기반 간소화 projection](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L92-L107)
- [Reciprocal-depth 기반 perspective weight 보정](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L152-L175)

### Directional·Point·Spot Light 비교

Step10은 같은 geometry와 material에 공통 Blinn-Phong 항을 사용한다.
Light type에 따라 방향, 거리 감쇠와 spot cone factor를 선택한다.
세 결과는 CPU shading 단계의 입력과 분기 차이가 최종 밝기 분포에 미치는 영향을 보여준다.

- [공통 Blinn-Phong와 Directional Light 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step10_Lights/MyShader.h#L31-L48)
- [Point Light 거리 감쇠와 Spot Light cone 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step10_Lights/MyShader.h#L55-L101)

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void RasterizeTrianglePseudo(const Triangle& triangle)
{
	for (Pixel pixel : GetScreenBounds(triangle)) {
		Barycentric weight = CalculateEdgeWeights(pixel, triangle);
		if (!weight.IsInside() || !PassesDepthTest(pixel, weight)) continue;
		WriteFramebuffer(pixel, InterpolatePerspectiveCorrect(weight));
	}
}
```

원본 코드: [Step8 coverage와 perspective weight 보정](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L117-L175)

## 검증 상태

- Step1, Step1A와 Step2부터 Step10까지 Debug/Release x64 build/run 성공을 재확인한다.
- Application window screenshot 19개와 Step10 비교 image, Step1A interaction video를 확인한다.
- 문서 validator와 GitHub Actions `Docs Validation` 범위는 문서·fixture·asset 정책으로 한정한다.

## 구현 범위와 한계

- 포함: Step1부터 Step10까지의 triangle rasterization, indexed geometry, 2D transform·animation, depth test를 다룬다.
- 포함: CPU shader stage, backface culling, 간소화 projection과 perspective-correct interpolation을 다룬다.
- 포함: Blinn-Phong Light 비교를 다룬다.
- 포함: Step1을 triangle fan으로 확장한 사용자 Personal Extension과 Step4 계층적 orbit 사례
- 한계: Step8은 full projection matrix, clip space와 near/far clipping을 포함하지 않는 학습용 projection이다.
- 한계: Step10은 단일 Light와 선형 거리 감쇠를 사용하며 PBR, gamma correction과 tone mapping을 포함하지 않는다.

## 관련 문서

### Chapter 안내

- [Part2 Chapter04 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/README.md)
- [Chapter04 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/demo-index.md)
- [Chapter04 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/02_Verification/Part2_Chapter04/verification-index.md)

### 대표 구현

- Step8 PerspectiveProjection: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/08_PerspectiveProjection.md)
- Step10 Lights: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/04_Rasterization_Step10_Lights/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/10_Lights.md)

### 확장과 시간 변화

- [Step1A Triangle To Circle 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/01_TriangleToCircle.md)
- [Step4 Animation2D 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/04_Animation2D.md)

### 관련 개념

- [Rasterization Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/01_Topics/Rasterization/README.md)
- [Lighting And Shading Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/01_Topics/LightingAndShading/README.md)
