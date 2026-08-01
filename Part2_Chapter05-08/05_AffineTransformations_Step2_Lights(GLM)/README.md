# Chapter05 Step2 Lights(GLM)

이 예제는 Step1에서 확인한 GLM affine transformation을 CPU rasterizer의 model transform과 normal transform에 적용하고, Directional·Point·Spot Light를 Blinn-Phong 항으로 계산한다. DirectX11과 HLSL은 CPU가 만든 pixel buffer를 화면에 표시하는 presentation 경로를 담당한다.

## 실행 진입점

- Solution: `05_AffineTransformations_Step2_Lights(GLM).sln`
- Project type: Windows desktop application
- Entry point: `main.cpp`
- External dependency: GLM과 ImGui headers
- Runtime dependency: project 폴더의 `VertexShader.hlsl`, `PixelShader.hlsl`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Model과 normal matrix 구성](Rasterization.cpp#L140-L160) | `T * Rz * Ry * Rx * S` model matrix와 inverse-transpose normal matrix 구성 |
| [Position과 normal 변환](MyShader.h#L90-L110) | Position에 `w=1`, normal에 `w=0`을 사용하고 변환된 normal 정규화 |
| [Light별 Blinn-Phong 계산](MyShader.h#L17-L87) | Ambient·diffuse·specular, attenuation과 spot cone 계산 |
| [CPU rasterization과 shading](Rasterization.cpp#L60-L138) | Coverage, depth, perspective-correct interpolation과 pixel shading |
| [Dynamic texture presentation](Example.cpp#L10-L21) | CPU pixel buffer를 D3D11 dynamic texture로 업로드 |
| [Transform·material·light UI](main.cpp#L64-L131) | Object, material과 Directional·Point·Spot parameter 조작 |

## 구현 요약

GLM column-vector convention에서 model matrix는 `translation * rotationZ * rotationY * rotationX * scale`로 구성한다. 따라서 vertex에는 scale부터 rotation과 translation 순서로 적용된다. Position은 translation의 영향을 받는 `w=1`로 변환하고, normal은 translation을 제외하는 `w=0`과 inverse-transpose matrix를 사용한다.

CPU rasterizer는 triangle coverage, depth와 perspective-correct interpolation을 처리한 뒤 각 pixel에서 Blinn-Phong lighting을 계산한다. Directional Light는 저장 방향의 반대를 사용하고 Point와 Spot Light는 위치에 따른 방향과 선형 attenuation을 추가한다. HLSL은 geometry와 lighting을 다시 계산하지 않고 CPU 결과 texture를 full-screen quad에 표시한다.

일반 matrix와 normal transform 원리는 [Matrix And Affine Transformations](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md), lighting 이론은 [Phong And Blinn-Phong](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)과 [Light Types](../../Docs/01_Topics/LightingAndShading/LightTypes.md)로 위임한다. Build/run/capture 사실은 [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Runtime shader load | 성공 | `VertexShader.hlsl`, `PixelShader.hlsl` 로드 |
| Capture/Result | 확보 | 기본·non-uniform scale 전체 창 screenshot |

## Capture/Result

![Chapter05 Step2 Lights GLM adjusted](../../Docs/_assets/captures/part2_chapter05_02_lights_glm_adjusted.png)

기본 상태와 조정 상태의 transform·lighting 관계는 [Step2 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_LightsGLM.md)에서 비교한다.

## 구현 범위와 한계

- CPU rasterizer와 CPU Blinn-Phong lighting을 설명하며 HLSL lighting 예제로 일반화하지 않는다.
- UI는 한 번에 하나의 Directional·Point·Spot Light만 선택한다.
- Point·Spot attenuation은 물리 기반 inverse-square가 아닌 선형 구간을 사용한다.
- Shadow, gamma correction, tone mapping과 multiple light accumulation은 포함하지 않는다.
- Dynamic texture upload의 `RowPitch` 처리는 별도 portability 작업으로 둔다.
- Project의 GLM·ImGui include는 개발 환경 integration에 의존한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [Matrix And Affine Transformations Topic](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Phong And Blinn-Phong Topic](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
- [Light Types Topic](../../Docs/01_Topics/LightingAndShading/LightTypes.md)
- [Step2 Lights(GLM) 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_LightsGLM.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
