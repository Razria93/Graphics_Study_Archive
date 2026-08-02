# Part2 Chapter05-08

D3D11 graphics pipeline, modeling, shader toy 예제를 정리하는 폴더다.

## 상태

- 학습 코드 정리: Chapter05 Step1–4 bundle과 Chapter06 Step1–5A 정규화 완료
- Build/run: Chapter05 Step1–4와 Chapter06 Step1–5A 현재 재검증 완료, 나머지 예제 과거 확인 유지
- 현재 대상: Chapter06 graphics pipeline 순차 정규화
- 캡처: Chapter05 Step2·4와 Chapter06 Step2–5 screenshot 확보, Chapter06 Step1 console 예제 제외

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P2-C05-08`](../Docs/99_Legacy/source-registry.md) |
| Import status | code import 완료 / Chapter05 Step1–4와 Chapter06 Step1–5A 순차 verification 완료 |
| Public readiness | 검토 필요 |
| Build/run status | Chapter05 Step1–4와 Chapter06 Step1–5A Debug/Release x64 현재 확인, 나머지 과거 확인 |
| Next action | Chapter06 Step6 Lighting 순차 정규화 |

## 예정 주제

- Model-view-projection transforms
- Shader pipeline
- Texturing and lighting
- Procedural mesh generation
- Cubemapping, environment mapping, and bloom

## Chapter05 Affine Transformations Bundle

Chapter05 Step1~4는 GLM에서 익힌 matrix와 affine transformation을 DirectXMath·SimpleMath 환경으로 옮기는 하나의 학습 흐름이다. 서로 다른 API와 vector convention을 사용해도 각 convention에 맞는 matrix composition을 구성하면 같은 transform 역할과 시각 결과를 얻을 수 있음을 확인한다.

| 단계 | 역할 |
| --- | --- |
| Step1 Matrix(GLM) | Matrix, homogeneous coordinate와 affine composition을 console 출력으로 확인 |
| Step2 Lights(GLM) | GLM model·normal transform을 CPU rasterization과 lighting에 적용 |
| Step3 DirectXMath | DirectXMath 연산형·저장형과 SimpleMath wrapper의 API·semantic 차이를 연결 |
| Step4 Lights(SimpleMath) | Step2와 같은 graphics 처리를 SimpleMath row-vector convention으로 재구성하고 결과 비교 |

Coordinate handedness, matrix memory layout, vector convention과 multiplication order는 서로 구분한다. 이 bundle은 특정 engine 좌표계를 그대로 재현하는 대신 GLM과 DirectXMath/SimpleMath에서 동등한 affine transform을 구성하는 원리를 다룬다.

## Chapter06 Graphics Pipeline

Chapter06은 Direct3D interface lifetime에서 시작해 window, device resource와 pipeline stage를 순서대로 확장한다. Step1은 graphics window 없이 device·immediate context 생성과 `ComPtr` ownership만 분리해 확인하고, Step2부터 swap chain과 rendering loop를 연결한다.

## Modeling variant 기준

- `*_Lecture`: private archive에서 비교용으로 선별한 reference solution 후보로 보존
- `*_Complete`: 사용자 풀이 또는 사용자 완성본으로 보존
- archive 이름은 `ReferenceSolution` / `UserSolution`처럼 제출물 관점의 이름으로 조정 가능
- `ReferenceSolution`은 public 공개 후보가 아니며, 공개 전 별도 권리/출처 검토 필요
- `*_Backup*`, `*_Debug`, 단순 중간 실험 폴더는 기본 제외 후보

## 진행 중인 예제

| Example | 상태 |
| --- | --- |
| [`05_AffineTransformations_Step1_Matrix(GLM)`](05_AffineTransformations_Step1_Matrix%28GLM%29/README.md) | 현재 build/run·문서·상세 Demo 정규화 완료 |
| [`05_AffineTransformations_Step2_Lights(GLM)`](05_AffineTransformations_Step2_Lights%28GLM%29/README.md) | 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| [`05_AffineTransformations_Step3_DirectXMath`](05_AffineTransformations_Step3_DirectXMath/README.md) | 현재 build/run·문서·상세 Demo 정규화 완료 |
| [`05_AffineTransformations_Step4_Lights(SimpleMath)`](05_AffineTransformations_Step4_Lights%28SimpleMath%29/README.md) | 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| [`06_GraphicsPipeline_Step1_COM`](06_GraphicsPipeline_Step1_COM/README.md) | 현재 build/run·문서·상세 Demo 정규화 완료 |
| [`06_GraphicsPipeline_Step2_InitializingD3D`](06_GraphicsPipeline_Step2_InitializingD3D/README.md) | 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| [`06_GraphicsPipeline_Step3_ModelViewProj`](06_GraphicsPipeline_Step3_ModelViewProj/README.md) | 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| [`06_GraphicsPipeline_Step4_Shaders`](06_GraphicsPipeline_Step4_Shaders/README.md) | 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| [`06_GraphicsPipeline_Step5_Texturing`](06_GraphicsPipeline_Step5_Texturing/README.md) | 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| [`06_GraphicsPipeline_Step5_Texturing_LightingSelf`](06_GraphicsPipeline_Step5_Texturing_LightingSelf/README.md) | Step5A 현재 build/run·capture·문서·상세 Demo 정규화 완료 |
| `06_GraphicsPipeline_Step6_Lighting` | 코드 보관 완료 및 현재 문서화 대기 |
| `06_GraphicsPipeline_Step7_ResizingViewport` | 코드 보관 완료 및 현재 문서화 대기 |
| `06_GraphicsPipeline_Step8_ResizingWindow` | 코드 보관 완료 및 현재 문서화 대기 |
| `06_GraphicsPipeline_Step9_PhongVsBlinnPhong` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step1_DrawingWireFrames` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step2_DrawingNormals` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step3_Grid` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step4_Cylinder` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step5_Sphere_UserSolution` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step5_Sphere_ReferenceSolution` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step6_Subdivision` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step7_FaceNormals` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step8_SphereMapping_UserSolution` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step8_SphereMapping_ReferenceSolution` | 코드 보관 완료 및 현재 문서화 대기 |
| `07_Modeling_Step9_ModelFiles` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step1_RimLighting` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step2_Cubemapping` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step3_EnvironmentMapping` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step4_ImageBasedLighting` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step5_FresnelEffect` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step6_BloomEffect` | 코드 보관 완료 및 현재 문서화 대기 |
| `08_ShaderToys_Step7_Shadertoy` | 코드 보관 완료 및 현재 문서화 대기 |
