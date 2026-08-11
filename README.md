# Graphics Study Archive

이 저장소는 DirectX11 graphics study examples와 개인 확장 작업을 코드, 개념 설명, 검증 기록, capture/result로 정리하는 portfolio archive다. raw 자료를 그대로 공개하는 것이 아니라, 직접 확인한 구현과 결과를 바탕으로 공개 가능한 subset을 선별할 수 있게 만드는 것이 목표다.

## Highlights

- DirectX11 initialization과 render loop 구성
- CPU-side image processing 결과의 DirectX11 texture upload
- Bloom post-processing과 original/result 비교
- CPU ray tracing Step4부터 Step14까지와 cubemap environment sampling
- Compute shader, particle·fluid simulation, animation과 gameplay 예제 정리

## Current Work

`Part1_Chapter01-02` pilot부터 `Part4_Chapter14-20`까지의 순차 정규화와 Demo 문서 closeout을 마감했다. `Portfolio_GraphicsLab` 정본 기반 구성과 Part4 selected video comment closeout을 후속 작업으로 유지한다.

- [Part1 Chapter01-02](Part1_Chapter01-02/README.md): DirectX11 기반 렌더링 흐름과 bloom 후처리 pilot
- [01_DX11InitAndImGui](Part1_Chapter01-02/01_DX11InitAndImGui/README.md): DirectX11 device, swap chain, render target, ImGui 기반 예제
- [02_Bloom](Part1_Chapter01-02/02_Bloom/README.md): original input과 bloom result를 비교하는 post-processing 예제
- [PostProcessingAndBloom](Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md): bloom 처리 흐름과 DirectX11 표시 경로
- [Part1 Chapter03](Part1_Chapter03/README.md): CPU ray tracing Step4부터 Step14까지 순차 작업
- [Step14 CubeEnvironment](Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/README.md): direction 기반 cubemap environment sampling
- [Part2 Chapter04](Part2_Chapter04/README.md): CPU software rasterization Step1부터 Step10까지 순차 작업
- [Step1 Triangle](Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md): edge function과 barycentric RGB interpolation 기반 최소 rasterizer
- [Step1A Triangle To Circle](Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md): triangle fan과 segment-count slider를 사용하는 Personal Extension
- [Part2 Chapter05-08](Part2_Chapter05-08/README.md): affine transformation부터 DirectX11 pipeline과 shader toy까지 이어지는 순차 작업
- [Chapter06 Step5A Texturing LightingSelf](Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing_LightingSelf/README.md): GPU texture와 point-light shading 결합
- [Chapter06 Step6 Lighting](Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/README.md): Directional·Point·Spot GPU lighting 비교
- [Chapter06 Step7 ResizingViewport](Part2_Chapter05-08/06_GraphicsPipeline_Step7_ResizingViewport/README.md): ImGui panel과 scene viewport 분리
- [Chapter06 Step8 ResizingWindow](Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/README.md): Window resize와 swap chain dependent resource 재생성
- [Chapter06 Step9 PhongVsBlinnPhong](Part2_Chapter05-08/06_GraphicsPipeline_Step9_PhongVsBlinnPhong/README.md): 동일 조건의 Phong과 Blinn-Phong specular 비교
- [Chapter07 Step1 DrawingWireFrames](Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/README.md): indexed triangle mesh의 wireframe rasterization
- [Chapter07 Step2 DrawingNormals](Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/README.md): surface mesh와 vertex normal line의 분리
- [Chapter07 Step3 Grid](Part2_Chapter05-08/07_Modeling_Step3_Grid/README.md): 분할 파라미터 기반 procedural Grid 생성
- [Chapter07 Step4 Cylinder](Part2_Chapter05-08/07_Modeling_Step4_Cylinder/README.md): ring·slice 기반 열린 cylinder side surface 생성
- [Chapter07 Step5 Sphere](Part2_Chapter05-08/07_Modeling_Step5_Sphere/README.md): 두 반구와 pole fan을 결합한 sphere 구현
- [Chapter07 Step6 Subdivision](Part2_Chapter05-08/07_Modeling_Step6_Subdivision/README.md): triangle subdivision과 sphere surface projection
- [Chapter07 Step7 FaceNormals](Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/README.md): triangle winding과 face-normal diagnostic line
- [Chapter07 Step8 SphereMapping](Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/README.md): icosahedron subdivision과 spherical UV seam 보정

## Featured Result

`02_Bloom`은 ChatGPT로 생성한 입력 이미지를 사용해 bright-pass, blur, composite 단계가 적용된 result image를 만든다.

**Original input**

![02_Bloom original input](Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg)

**Bloom result**

![02_Bloom bloom result](Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png)

- [Bloom 상세 Demo](Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)
- [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9)
- [02_Bloom 코드 안내](Part1_Chapter01-02/02_Bloom/README.md)

## Study Map

| 범위 | 주요 내용 | 코드 보관 | 문서화 |
| --- | --- | --- | --- |
| `Part1_Chapter01-02` | DirectX11 init, render loop, bloom post-processing | 완료 | pilot 마감 |
| `Part1_Chapter03` | ray tracing basics와 cubemap sampling | 완료 | Step4부터 Step14까지 문서화·재검증 완료 |
| `Part2_Chapter04` | rasterization foundation | 완료 | Step1부터 Step10까지·Step1A 문서화·재검증, GitHub 게시와 PR 마감 완료 |
| `Part2_Chapter05-08` | DirectX11 pipeline, texture, mesh와 shader toy 흐름 | 완료 | Chapter05 Step1–4, Chapter06 Step1–9, Chapter07 Step1–9와 Chapter08 Step1–7 완료 |
| `Part3_Chapter09` | camera, picking, quaternion과 object interaction | 완료 | Step1부터 Step6까지 정규화 완료 |
| `Part3_Chapter10-13` | lighting, shadow, PBR/IBL | 완료 | 21개 예제 문서화·재검증, Demo Issue와 PR 마감 완료 |
| `Part4_Chapter14-20` | compute shader, simulation, animation/physics | 완료 | 전체 Demo 문서 closeout과 PR #38 merge 완료 · Chapter14–15 Release 재검증과 selected video 후속 필요 |
| `Portfolio_GraphicsLab` | RayTracing부터 graphics pipeline까지 확장하는 개인 graphics 구현 | 구성 중 | canonical scaffold와 첫 `Rendering/RayTracing` 축 준비 |

## Main Guides

- [Build Guide](BUILD.md): Visual Studio build/run 확인 기준
- [Topics Guide](TOPICS.md): graphics topic 진입점
- [Demo Guide](DEMOS.md): capture/result 운영 기준
- [Docs Guide](Docs/README.md): 문서 구조와 작업 흐름
- [Notice](NOTICE.md): archive/public subset 분리와 주의사항

## Repository Layout

| 위치 | 책임 |
| --- | --- |
| `Part*_Chapter*` | code/build 기준 예제 프로젝트 |
| `Portfolio_GraphicsLab` | 개인 graphics 구현을 단계적으로 확장하는 정본 project |
| `Part*_Chapter*/ExampleName/README.md` | 예제 설명 정본 |
| `Docs/01_Topics` | graphics 개념 정본 |
| `Docs/02_Verification` | build/run/capture 검증 정본 |
| `Docs/03_Demos` | Demo registry와 기술 구현·시각 결과 정본 |
| `Docs/04_WorkLogs` | Issue/PR 작업 기록 정본 |
| `Docs/05_Publication` | public subset 판단 정본 |
| `Docs/06_Policies` | 문서화, 검증, demo, GitHub 운영, 공개 정책 |
| `Docs/07_GitHub` | GitHub Issue/PR/comment 게시 후보 |
| `Docs/98_Tools` | templates, validator, troubleshooting |
| `Docs/99_Legacy` | import 기록과 이전 Docs 구조 |

## Archive And Publication

이 저장소는 private archive를 기준으로 운영하지만, 일부 문서와 결과물은 public portfolio subset 후보가 될 수 있다. 강의 원본 자료, 유료 자료, 강의 화면 캡처, 권리 불명확 asset은 공개 후보로 두지 않는다.

공개 가능성 판단은 [Publication Policy](Docs/06_Policies/publication-policy.md)와 [Publication Candidates](Docs/05_Publication/candidate-list.md)를 기준으로 한다. 직접 확인하지 않은 build/run/capture 항목은 `미확인`으로 기록한다.

## Maintainer Notes

- [Work Session Quickstart](Docs/98_Tools/work-session-quickstart.md)
- [Canonical Docs Policy](Docs/06_Policies/canonical-docs-policy.md)
- [Terminology Policy](Docs/06_Policies/terminology-policy.md)
- [Docs Authoring Flow Policy](Docs/06_Policies/docs-authoring-flow-policy.md)
- [Verification Policy](Docs/06_Policies/verification-policy.md)
- [Legacy Import History](Docs/99_Legacy/ImportHistory/README.md)
