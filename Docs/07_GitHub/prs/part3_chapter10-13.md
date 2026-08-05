# Part3 Chapter10-13 Geometry·Texturing·PBR·Light/Shadow 단계별 구현과 Demo

## 요약

이 PR은 `Part3_Chapter10-13`의 21개 예제를 Geometry Pipeline, Texturing Techniques, PBR와 Light/Shadow 순서로 재검증하고 Example, Topic, Verification과 상세 Demo로 연결한다. 각 Chapter의 runtime asset과 rendered evidence 책임을 분리하고 공개 가능한 정적 visual을 구성한다.

## 범위

- Chapter10: Geometry Shader, billboard, normal lines, fireball과 Manual·Distance Adaptive tessellation
- Chapter11: Mipmap, normal·height mapping, HDRI와 bloom을 포함한 HDR pipeline
- Chapter12: Metallic-roughness PBR sphere와 imported PBR model material binding, Off/On comparison evidence
- Chapter13: Stencil mirror, pipeline state, shadow prototype, fog, shadow mapping, PCF·PCSS, halo strength와 sphere light radius evidence
- 문서·검증: Example README 21개, Topic, Verification, 상세 Demo 21개와 전체 창 capture

## 핵심 개념

- Programmable geometry: Point primitive 확장과 diagnostic line에서 Hull·Domain Shader tessellation까지 geometry 생성 stage를 확장한다.
- Surface detail과 HDR: Texture LOD, TBN normal, vertex displacement, EXR input과 bloom composite를 순차적으로 연결한다.
- Metallic-roughness PBR: Direct GGX BRDF와 IBL을 material map에 결합하고 imported model의 submesh resource binding으로 확장한다.
- Light와 shadow: Stencil mirror에서 시작해 hard shadow, fixed-kernel PCF와 blocker 기반 variable-penumbra PCSS를 비교한다.

## 대표 예제

### Chapter10 Step5 Tessellation

원래 학습 경로인 Manual UI factor를 기본으로 유지하고 camera distance 기반 Adaptive mode를 사용자 확장으로 분리한다.

- [Step5 Tessellation 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/10_05_Tessellation.md)
- [Tessellation Pipeline Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/01_Topics/ModelingAndGeometry/TessellationPipeline.md)

### Chapter11 Step5 HDRPipeline

HDR scene resolve, bloom pyramid, exposure와 gamma를 하나의 post-process chain으로 구성한다.

- [Step5 HDRPipeline 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md)
- [HDR Rendering Pipeline Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/01_Topics/TexturingAndMapping/HDRRenderingPipeline.md)

### Chapter12 Step1 UnrealPBR

Metallic-roughness map과 direct GGX BRDF·IBL을 결합해 PBR material의 입력과 결과를 한 화면에서 확인한다.

- [Step1 UnrealPBR 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md)
- [PBR Material Model Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/01_Topics/PBRAndIBL/PBRMaterialModel.md)

### Chapter13 Step4→6 Shadow Filtering

같은 계열 장면에서 hard shadow, PCF와 PCSS의 edge와 penumbra 차이를 비교한다.

- [Step4 ShadowMapping 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_04_ShadowMapping.md)
- [Step5 SoftShadowPCF 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_05_SoftShadowPCF.md)
- [Step6 SoftShadowPCSS 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_06_SoftShadowPCSS.md)

## 검증

- 21개 예제 Debug/Release x64 Clean/Rebuild와 run 성공
- Application title, project CWD, runtime DLL·resource load와 핵심 시각 결과 확인
- 전체 application window screenshot과 Chapter13 shadow filtering·sphere light radius storyboard 검수
- PNG full decode, dimensions, SHA-256, metadata·개인 식별자와 공개 안전성 확인
- GitHub body, Demo, Topic, Markdown wrap·render·table과 video asset validator 통과

## 대표 Visual

### Chapter13 Hard Shadow → PCF → PCSS

왼쪽에서 오른쪽으로 단일 depth comparison, 고정 kernel filtering과 blocker 기반 variable penumbra를 비교한다.

![Chapter13 Shadow Comparison](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter13_04_06_shadow_filtering_storyboard.png?raw=true)

Material/IBL 결과 축은 [Chapter12 PBR Demo #27](https://github.com/Razria93/Graphics_Study_Archive/issues/27)의 UnrealPBR·PBR Models Off/On comparison으로 분리해 확인한다.

## 구현 범위와 한계

- Chapter10 Step5의 Distance Adaptive tessellation은 원래 Manual 학습 경로와 분리한 사용자 확장이다.
- Chapter13의 raw 중복 Step2 경로는 유지하고 공개 표시만 Step2 PipelineStateObject와 Step2B Shadow Prototype으로 구분한다.
- 강의 제공·출처 불완전 runtime asset 원본과 직접 다운로드 링크는 공개하지 않고 rendered evidence만 사용한다.
- P2 architecture와 portability 개선은 현재 21개 예제의 학습 흐름과 실행 검증 범위에 포함하지 않는다.

## 문서

- Chapter README: [Part3 Chapter10-13](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- Topic: [Topic Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/01_Topics/README.md)
- Verification: [Part3 Chapter10-13 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- Demo: [Part3 Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- WorkLog: [WU-Part3](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/04_WorkLogs/work-units/WU-Part3.md)

## 관련 이슈

- [Chapter10 Geometry Pipeline Demo #25](https://github.com/Razria93/Graphics_Study_Archive/issues/25)
- [Chapter11 Texturing Techniques Demo #26](https://github.com/Razria93/Graphics_Study_Archive/issues/26)
- [Chapter12 Physically Based Rendering Demo #27](https://github.com/Razria93/Graphics_Study_Archive/issues/27)
- [Chapter13 Light And Shadow Demo #28](https://github.com/Razria93/Graphics_Study_Archive/issues/28)
