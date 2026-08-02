# Part2 Chapter05-08 DirectX11 Pipeline·Modeling·Shader 예제 정규화와 Demo

## 요약

이 PR은 `Part2_Chapter05-08`의 30개 예제를 Chapter05 affine transformation API 비교, Chapter06 DirectX11 pipeline, Chapter07 procedural modeling과 Chapter08 shader experiment 흐름으로 재검증하고 설명 가능한 문서 구조로 정리한다. Example README, Topic, Verification, 상세 Demo와 Publication 판정을 연결하고 공개 안전한 Chapter05·06·07 결과를 대표 Demo로 구성한다.

## 범위

- Chapter05: GLM에서 DirectXMath·SimpleMath로 이어지는 affine transformation API와 convention 비교
- Chapter06: COM ownership, DirectX11 초기화, MVP·shader·texture·lighting과 resize resource lifetime
- Chapter07: Wireframe·normal·procedural primitive, subdivision과 spherical texture mapping
- Chapter08: Rim lighting, cubemap·environment mapping, IBL·Fresnel, bloom과 Shadertoy 구현 검증
- 제외 범위: Graphics executable CI, 권리 근거가 확인되지 않은 외부 asset의 대표 publication visual 선정, project GUID와 공통 project metadata 정리

## 핵심 개념

- Affine transform convention: GLM과 DirectXMath·SimpleMath의 vector convention에 맞춰 composition을 구성하고 동등한 geometry·lighting 의도를 확인한다.
- DirectX11 resource pipeline: Device·context에서 shader·texture binding과 resize-dependent resource 재생성까지 단계별 책임을 분리한다.
- Procedural modeling: Indexed topology에서 Sphere와 subdivision으로 확장하고 spherical UV의 U seam을 triangle-local vertex 복제로 보정한다.
- Shader experiments: Cubemap, environment lighting, Fresnel과 post-processing 구현은 archive 검증 범위로 유지하고 공개 대표 visual은 별도로 선별한다.

## 대표 예제

### Chapter05 Step2·4 Affine Comparison

같은 transform 의도를 GLM과 SimpleMath convention에 맞게 구성해 API 전환과 결과 대응을 설명한다.

- README: [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/README.md)
- Demo: [Step2 Lights(GLM)](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/05_LightsGLM.md) · [Step4 Lights(SimpleMath)](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/05_LightsSimpleMath.md)
- Verification: [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### Chapter06 Graphics Pipeline

첫 Direct3D frame에서 lighting과 window resize까지 pipeline과 resource lifetime을 순차적으로 확장한다.

- README: [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/README.md)
- Demo: [Step2 InitializingD3D](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/06_InitializingD3D.md) · [Step6 Lighting](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/06_Lighting.md) · [Step8 ResizingWindow](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/08_ResizingWindow.md)
- Verification: [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### Chapter07 Procedural Modeling

Triangle topology의 wireframe 기준선에서 사용자 Sphere, subdivision과 spherical mapping 결과로 확장한다.

- README: [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/README.md)
- Demo: [Step1 DrawingWireFrames](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/07_01_DrawingWireFrames.md) · [Step5 Sphere](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/07_05_Sphere.md) · [Step8 SphereMapping](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/07_08_SphereMapping.md)
- Verification: [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

## 검증

- Chapter05 Step1–4, Chapter06 Step1–9, Chapter07 Step1–9와 Chapter08 Step1–7 Debug/Release x64 build/run 성공
- Graphics Example application window screenshot 확보와 사용자 시각 확인 완료
- Tracked capture·generated asset의 metadata와 개인 식별자 검사 완료
- 문서·Markdown rendering·table·video asset validator와 fixture 검사 통과

## 대표 Visual

### Chapter07 Step8 SphereMapping

Procedural subdivision, radial normal, spherical UV와 seam 보정을 공개 안전한 generated fictional planet texture로 보여주는 대표 결과다.

![Chapter07 Step8 SphereMapping](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter07_08_sphere_mapping.png?raw=true)

## 구현 범위와 한계

- Chapter05–08의 학습용 DirectX11 예제를 설명 가능한 archive 구조로 정리하며 production renderer나 engine framework를 목표로 하지 않는다.
- Chapter06의 resize interaction video는 후속 개선이며 현재 Compact·Default·Wide screenshot과 반복 resize 검증을 사용한다.
- 외부 asset을 사용하는 Chapter07 Step9와 Chapter08 결과는 구현·실행 검증에 포함하지만 대표 publication visual로 선정하지 않는다.
- RowPitch·Map failure와 project metadata 정리는 별도 code maintenance 범위로 유지한다.

## 문서

- Chapter README: [Part2 Chapter05-08](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/README.md)
- Topic: [DirectX11 Pipeline](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/DirectX11Pipeline/README.md) · [Modeling And Geometry](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/ModelingAndGeometry/README.md)
- Verification: [Part2 Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- Demo: [Part2 Chapter05-08 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/demo-index.md)

## 관련 이슈

- [Chapter05 Affine Transformations Demo #17](https://github.com/Razria93/Graphics_Study_Archive/issues/17)
- [Chapter06 DirectX11 Graphics Pipeline Demo #18](https://github.com/Razria93/Graphics_Study_Archive/issues/18)
- [Chapter07 Procedural Modeling Demo #19](https://github.com/Razria93/Graphics_Study_Archive/issues/19)
