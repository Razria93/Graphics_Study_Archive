# Graphics Study Archive

이 저장소는 DirectX11 graphics study examples와 개인 확장 작업을 코드, 개념 설명, 검증 기록, capture/result로 정리하는 portfolio archive다. raw 자료를 그대로 공개하는 것이 아니라, 직접 확인한 구현과 결과를 바탕으로 공개 가능한 subset을 선별할 수 있게 만드는 것이 목표다.

## Highlights

- DirectX11 initialization과 render loop 구성
- CPU-side image processing 결과의 DirectX11 texture upload
- Bloom post-processing과 original/result 비교
- Ray tracing, rasterization, lighting, shadows, PBR/IBL 정리 예정
- Compute shader와 simulation 예제 정리 예정

## Current Pilot

현재는 `Part1_Chapter01-02`를 기준으로 새 문서화 workflow를 검증하고 있다.

- [Part1 Chapter01-02](Part1_Chapter01-02/README.md): DirectX11 기반 렌더링 흐름과 bloom 후처리 pilot
- [01_DX11InitAndImGui](Part1_Chapter01-02/01_DX11InitAndImGui/README.md): DirectX11 device, swap chain, render target, ImGui 기반 예제
- [02_Bloom](Part1_Chapter01-02/02_Bloom/README.md): original input과 bloom result를 비교하는 post-processing 예제
- [PostProcessingAndBloom](Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md): bloom 처리 흐름과 DirectX11 표시 경로

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
| `Part1_Chapter01-02` | DirectX11 init, render loop, bloom post-processing | 완료 | pilot 진행 |
| `Part1_Chapter03` | ray tracing basics | 완료 | 대기 |
| `Part2_Chapter04` | rasterization foundation | 완료 | 대기 |
| `Part2_Chapter05-08` | DirectX11 pipeline, texture, mesh 흐름 | 완료 | 대기 |
| `Part3_Chapter09` | texturing and mapping | 완료 | 대기 |
| `Part3_Chapter10-13` | lighting, shadow, PBR/IBL | 완료 | 대기 |
| `Part4_Chapter14-20` | compute shader, simulation, animation/physics | 완료 | 대기 |
| `Portfolio_RayTracer` | Part1 기반 ray tracing 확장 작업 | 확인 필요 | 대기 |

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
| `Portfolio_RayTracer` | Part1 기반 ray tracing 확장 작업 |
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
