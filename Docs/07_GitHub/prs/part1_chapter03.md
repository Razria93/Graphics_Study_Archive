# Part1 Chapter03 CPU Ray Tracing 단계별 구현과 Demo

## 요약

이 PR은 `Part1_Chapter03`의 Step4부터 Step14까지 CPU ray tracing 예제를 코드 폴더 README, Topic, Verification과 독립 상세 Demo로 연결한다. Primary ray와 primitive intersection에서 shadow, texturing, supersampling, recursive reflection/refraction까지 이어지는 학습 흐름을 현재 build/run과 capture로 검증한다. Chapter 작업에 필요한 capture 도구, asset 정리, 문서 validator와 GitHub Actions 기준도 실제 예제에 맞게 보완한다.

## 범위

- Chapter: `Part1_Chapter03`
- 대표 예제: Step4 DrawingSphere, Step8 Shadow, Step13 Transparency
- 지원 범위: RayTracing Topic, Verification, 상세 Demo, capture tooling, asset 검수, validator와 Docs Validation workflow
- 지원 범위: RayTracing Topic, Verification, 상세 Demo, capture tooling, asset 검수, validator와 Docs Validation workflow
- 독립 변형: Step14 CubeEnvironment
- 제외 범위: `Portfolio_RayTracer`, Part2 이후 Chapter

## 핵심 개념

- Ray와 intersection: 화면 좌표에서 camera ray를 만들고 sphere, triangle과 Square의 가장 가까운 양수 hit를 선택한다.
- Visibility와 shading: Surface normal과 point light로 Phong shading을 계산하고 shadow ray로 direct lighting 여부를 결정한다.
- Sampling과 material: Barycentric weight, texture sampling과 supersampling을 거쳐 reflected·refracted secondary ray를 재귀 추적한다.
- Environment sampling: Step14는 geometry hit 대신 ray direction을 cubemap face와 UV로 변환하는 독립 변형이다.

## 대표 예제

### Step4 DrawingSphere

Orthographic primary ray와 ray-sphere intersection으로 Chapter의 최소 CPU ray tracing 기준선을 만든다.

- README: [Step4 DrawingSphere README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md)
- Demo: [Step4 DrawingSphere 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part1_Chapter03/03_04_DrawingSphere.md)
- Verification: [Chapter03 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Docs/02_Verification/Part1_Chapter03/verification-index.md)

### Step8 Shadow

Sphere와 Square 바닥을 하나의 scene으로 구성하고 shadow ray의 light 구간 blocker 판정으로 hard shadow를 만든다.

- README: [Step8 Shadow README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Part1_Chapter03/03_Raytracing_Step8_Shadow/README.md)
- Demo: [Step8 Shadow 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part1_Chapter03/03_08_Shadow.md)
- Topic: [Shadow Ray](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Docs/01_Topics/Shadows/ShadowRay.md)

### Step13 Transparency

Enter/exit 상태에 따라 IOR ratio와 normal을 전환하고 reflected·refracted ray를 재귀 추적해 background가 투명 구체에서 왜곡되는 결과를 만든다.

- README: [Step13 Transparency README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Part1_Chapter03/03_Raytracing_Step13_Transparency/README.md)
- Demo: [Step13 Transparency 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part1_Chapter03/03_13_Transparency.md)
- Topic: [Refraction And Transparency](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Docs/01_Topics/RayTracing/RefractionAndTransparency.md)

## 검증

- Step4부터 Step14까지 Debug x64 build/run 성공
- Step4부터 Step14까지 Release x64 build/run 성공
- Step4부터 Step14까지 전체 application window capture 확보
- Tracked capture와 input asset의 metadata·개인 식별자 검사 완료
- 로컬 문서 validator와 fixture 전체 통과
- GitHub Actions `Docs Validation` workflow 구성

## 스크린샷

### Step13 Transparency

Recursive refraction이 해수면·하늘 background를 투명 구체 내부에서 확대하고 왜곡하는 Chapter 대표 결과다.

![Step13 Transparency](https://github.com/Razria93/Graphics_Study_Archive/blob/f8c475a24abd534f4f1c461d0e7cc6bf6adeed43/Docs/_assets/captures/part1_chapter03_13_transparency.png?raw=true)

## 미확인 / 제한

- Step4부터 Step13까지는 순차 학습 흐름이지만 각 capture는 동일 scene의 단일 변수 A/B 비교가 아닌 구현 milestone이다.
- CPU ray tracing 결과를 DirectX11 dynamic texture로 표시하며 GPU ray tracing pipeline은 포함하지 않는다.
- Step13은 고정 IOR과 recursion budget을 사용하고 Fresnel, absorption과 medium stack을 포함하지 않는다.
- Step14는 Humus/Emil Persson의 CC BY 3.0 cubemap 6면과 attribution 원문을 유지하며 geometry·refraction과 별개의 변형이다.

## 문서

- Chapter README: [Part1 Chapter03](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Part1_Chapter03/README.md)
- Example README: [Step4부터 Step14까지 순차 목록](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Part1_Chapter03/README.md#순차-step)
- Topic: [Ray Tracing Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Docs/01_Topics/RayTracing/README.md)
- Verification: [Part1 Chapter03 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Docs/02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [Part1 Chapter03 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-chapter03-workflow/Docs/03_Demos/Part1_Chapter03/demo-index.md)
- Step14 attribution: [CubeEnvironment 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part1_Chapter03/03_14_CubeEnvironment.md)

## 관련 이슈

- 없음

## 다음 단계

- 대표 Demo Issue 게시 범위와 public subset 승격 여부를 별도 검수로 결정한다.
