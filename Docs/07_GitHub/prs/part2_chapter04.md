# Part2 Chapter04 CPU Software Rasterization 단계별 정규화와 Demo

## 요약

이 PR은 기존 `Part2_Chapter04` Step1~10 CPU software rasterization 예제를 순서대로 재검증하고, 코드 폴더 README, Topic, Verification과 상세 Demo로 설명 가능한 구조를 정리한다. Step8 PerspectiveProjection을 Chapter 대표 결과로 두고 Step10 Lights, Step1A Personal Extension과 Step4 Animation2D를 보조 흐름으로 연결하며, 반복 capture·video 검수와 문서 자동 검증 기준도 실제 작업에 맞게 보완한다.

## 범위

- Chapter: `Part2_Chapter04`
- 예제: Step1 Triangle, Step1A Triangle To Circle과 Step2 Circle부터 Step10 Lights까지의 기존 CPU rasterization 예제 정규화
- 대표 Demo: Step8 PerspectiveProjection
- 보조 Demo: Step10 Lights, Step1A Triangle To Circle, Step4 Animation2D
- 지원 범위: Example README, Rasterization·Animation·Lighting Topic, Verification, 상세 Demo, Publication, capture·video 도구와 문서 validator
- 제외 범위: `Part2_Chapter05-08`, graphics executable CI, video 원격 게시와 production rasterizer 기능 확장

## 핵심 개념

- Triangle rasterization: Edge function으로 coverage를 판정하고 barycentric weight로 vertex color와 attribute를 보간하는 공통 기반을 Step1부터 유지한다.
- Transform과 visibility: 2D transform·hierarchical animation, per-pixel depth test와 post-transform winding 기반 culling을 단계별로 분리한다.
- Perspective interpolation: Step8에서 Z 기반 크기 변화와 affine interpolation 왜곡을 비교하고 reciprocal-depth weight 보정 결과를 대표 visual로 연결한다.
- CPU lighting: Step9·10에서 CPU shader stage의 normal·position interpolation과 Directional·Point·Spot Blinn-Phong 결과를 비교한다.

## 대표 예제

### Step1 Triangle

Edge function coverage와 barycentric RGB interpolation으로 Chapter의 최소 CPU rasterization 기준선을 구성한다.

- README: [Step1 Triangle README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md)
- Demo: [Step1 Triangle 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/01_Triangle.md)
- Verification: [Chapter04 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/02_Verification/Part2_Chapter04/verification-index.md)

### Step8 PerspectiveProjection

같은 mesh에서 orthographic, affine perspective와 corrected perspective 상태를 비교해 projection과 attribute interpolation의 책임을 구분한다. 구현은 학습용 Z scaling과 reciprocal-depth weight 보정이며 일반적인 clip-space pipeline 전체를 대체하지 않는다.

- README: [Step8 PerspectiveProjection README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/README.md)
- Demo: [Step8 PerspectiveProjection 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/08_PerspectiveProjection.md)
- Verification: [Chapter04 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/02_Verification/Part2_Chapter04/verification-index.md)

### Step10 Lights

같은 geometry와 material에서 Directional, Point와 Spot Light의 방향·거리·cone 차이를 공통 CPU Blinn-Phong 계산 위에서 비교한다.

- README: [Step10 Lights README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/04_Rasterization_Step10_Lights/README.md)
- Demo: [Step10 Lights 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/10_Lights.md)
- Topic: [Light Types](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/01_Topics/LightingAndShading/LightTypes.md)

## 검증

- Debug x64 build/run: Step1, Step1A와 Step2~10 전체 성공
- Release x64 build/run: Step1, Step1A와 Step2~10 전체 성공
- capture/result: 전체 application window screenshot 19개 확보와 사용자 시각 검수 완료
- validator: GitHub body, Demo·Topic·Markdown rendering과 video asset 정책 validator 통과
- Actions: `Docs Validation`은 문서·fixture·asset 정책을 검사하며 C++ graphics build/run은 로컬 Verification을 기준으로 유지

## 대표 Visual

### Step8 Perspective-Correct Interpolation

Affine weight로 휘어진 checker를 reciprocal-depth weight로 보정한 Chapter 대표 결과다.

![Step8 Perspective-Correct Interpolation](https://github.com/Razria93/Graphics_Study_Archive/blob/0249770306c636e298f33f97dd7873046f481b3b/Docs/_assets/captures/part2_chapter04_08_perspective_projection_correct.png?raw=true)

## 구현 범위와 한계

- 기존 Step1~10 예제를 새로 구현한 PR이 아니라 실행 기준, 기본 parameter, 공개 application title, 검증 근거와 설명 책임을 순차 정규화한 작업이다.
- CPU rasterizer 결과를 DirectX11 dynamic texture로 표시하며 GPU rasterization pipeline 구현을 목표로 하지 않는다.
- Step8은 near/far clipping과 일반적인 clip-space pipeline을 포함하지 않는 간소화 projection이다.
- Step10은 단일 Light와 선형 거리 감쇠를 사용하며 PBR, inverse-transpose normal 처리, gamma correction과 tone mapping을 포함하지 않는다.

## 문서

- Example README: [Part2 Chapter04 순차 목록](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Part2_Chapter04/README.md)
- Topic: [Rasterization Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/01_Topics/Rasterization/README.md)
- Verification: [Part2 Chapter04 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/02_Verification/Part2_Chapter04/verification-index.md)
- Demo: [Part2 Chapter04 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/demo-index.md)
- Personal Extension: [Step1A Triangle To Circle 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/01_TriangleToCircle.md)
- 시간 변화: [Step4 Animation2D 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter04-workflow/Docs/03_Demos/Part2_Chapter04/04_Animation2D.md)

## 관련 이슈

- [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14)
