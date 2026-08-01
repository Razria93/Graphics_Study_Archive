# Part2 Chapter04 CPU Software Rasterization Demo

## 요약

`Part2_Chapter04`는 triangle coverage와 barycentric interpolation에서 시작해 2D transform, depth test, culling, perspective interpolation과 CPU lighting으로 확장되는 software rasterization 학습 흐름이다. Step8 PerspectiveProjection을 Chapter 대표 결과로 두고 Step10 Lights를 기술 보조, Step1A Triangle To Circle을 Personal Extension, Step4 Animation2D를 시간 변화 사례로 연결한다.

## 결과

### Step8 — Perspective-Correct Interpolation

같은 triangle mesh에서 Z 기반 크기 변화와 interpolation 방식을 함께 바꾸어, affine weight로 휘어진 checker가 reciprocal-depth 보정 뒤 안정된 형태로 나타나는 결과를 확인한다.

![Step8 Perspective-Correct Interpolation](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Docs/_assets/captures/part2_chapter04_08_perspective_projection_correct.png?raw=true)

## 핵심 구현

### Triangle Coverage와 Attribute Interpolation

각 triangle의 screen-space bounding box를 순회하며 edge function으로 내부 pixel을 판정하고, barycentric weight로 vertex attribute를 보간한다. 이 공통 기반이 Step1의 RGB triangle부터 이후 depth, texture coordinate와 lighting input까지 이어진다.

- [Edge function 기반 coverage와 barycentric weight 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L117-L156)

### Perspective Projection과 보간 보정

Step8은 vertex Z에 따라 화면 좌표를 축소하는 간소화된 projection을 적용한다. Raster space의 affine weight를 vertex의 eye-relative Z로 다시 계산해 color와 UV가 원근에 맞게 변화하도록 보정하며, near/far clipping과 일반적인 clip-space pipeline은 포함하지 않는다.

- [Z 기반 간소화 projection](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L92-L107)
- [Reciprocal-depth 기반 perspective weight 보정](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/Rasterization.cpp#L152-L175)

### Directional·Point·Spot Light 비교

Step10은 같은 geometry와 material에 공통 Blinn-Phong 항을 사용하고 Light type에 따라 방향, 거리 감쇠와 spot cone factor를 선택한다. 세 결과는 CPU shading 단계의 입력과 분기 차이가 최종 밝기 분포에 미치는 영향을 보여준다.

- [공통 Blinn-Phong와 Directional Light 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step10_Lights/MyShader.h#L31-L48)
- [Point Light 거리 감쇠와 Spot Light cone 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Part2_Chapter04/04_Rasterization_Step10_Lights/MyShader.h#L55-L101)

## 처리 흐름

1. Vertex와 index로 triangle mesh를 준비한다.
2. CPU vertex stage에서 model·view 성격의 transform과 projection을 적용한다.
3. Screen-space bounding box와 edge function으로 triangle coverage를 판정한다.
4. Depth와 barycentric weight로 visible fragment와 interpolated attribute를 계산한다.
5. CPU pixel stage에서 color 또는 lighting 결과를 RGBA32F framebuffer에 기록한다.
6. DirectX11 dynamic texture와 full-screen quad로 CPU 결과를 application window에 표시한다.

## 구현 범위와 한계

- 포함: Step1~10의 triangle rasterization, indexed geometry, 2D transform·animation, depth test, CPU shader stage, backface culling, 간소화 projection, perspective-correct interpolation과 Blinn-Phong Light 비교
- 포함: Step1을 triangle fan으로 확장한 사용자 Personal Extension과 Step4 계층적 orbit 사례
- 한계: Step8은 full projection matrix, clip space와 near/far clipping을 포함하지 않는 학습용 projection이다.
- 한계: Step10은 단일 Light와 선형 거리 감쇠를 사용하며 PBR, gamma correction과 tone mapping을 포함하지 않는다.

## 검증

- Build/Run: Step1, Step1A와 Step2~10의 Debug/Release x64 build/run 성공을 2026-07-31–2026-08-01에 project 폴더 CWD 기준으로 재확인
- Capture/Result: 전체 예제 application window screenshot 19개와 공개 안전성 확인
- Documentation: 문서 validator와 GitHub Actions `Docs Validation`은 문서·fixture·asset 정책을 검사하며 graphics executable build/run은 로컬 Verification에 기록

## 더 자세히 보기

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
