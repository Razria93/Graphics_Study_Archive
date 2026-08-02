# Chapter06 Step5A Texturing LightingSelf

이 예제는 Step5의 texture sampling을 box geometry와 point-light shading으로 확장한다. Vertex shader가 world position과 inverse-transpose normal을 전달하고, pixel shader가 texture color에 ambient·diffuse·Blinn-Phong specular와 거리 감쇠를 결합한다.

## 실행 진입점

- Solution: `06_GraphicsPipeline_Step5_Texturing.sln`
- Application entry: `main.cpp`
- 주요 source: `AppBase.cpp`, `ExampleApp.cpp`, `ExampleApp.h`
- Shader: `ColorVertexShader.hlsl`, `ColorPixelShader.hlsl`
- Runtime input: `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter06 Step5A Texturing LightingSelf`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Box vertex·normal·UV](ExampleApp.cpp#L10-L115) | Face별 normal과 UV를 가진 indexed box 구성 |
| [Texture와 sampler 초기화](ExampleApp.cpp#L120-L145) | 공개 검수한 목재 texture를 SRV로 만들고 linear wrap sampler 생성 |
| [Model·normal·view 갱신](ExampleApp.cpp#L197-L233) | Model transform, inverse-transpose normal matrix와 camera position 반영 |
| [Resource binding과 draw](ExampleApp.cpp#L236-L273) | Texture·sampler와 transform·light·material constant buffer 연결 |
| [Lighting UI](ExampleApp.cpp#L276-L325) | Light position·색·감쇠와 material parameter 조정 |
| [Vertex shader contract](ColorVertexShader.hlsl#L10-L51) | Projected position, world position, transformed normal과 UV 전달 |
| [Texture lighting](ColorPixelShader.hlsl#L36-L59) | Texture 기반 point-light shading과 거리 감쇠 계산 |

## 구현 요약

Box는 face마다 독립된 normal과 UV를 가진 24개 vertex로 구성한다. CPU는 Step5에서 검수한 목재 PNG의 동일 바이트 사본을 immutable RGBA texture로 만들고 pixel shader slot `t0`과 sampler slot `s0`에 연결한다.

Vertex shader는 model transform이 적용된 world position과 inverse-transpose normal matrix로 변환한 normal을 전달한다. Pixel shader는 light·view vector로 ambient, Lambert diffuse와 Blinn-Phong specular를 계산하고 `kc + kl·d + kq·d²`의 역수를 거리 감쇠로 사용한다. 일반 조명 이론은 [Phong And Blinn-Phong](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)과 [Light Types](../../Docs/01_Topics/LightingAndShading/LightTypes.md), 구현 선택과 결과 비교는 [Step5A 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_TexturingLightingSelf.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, 정상 종료 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, 정상 종료 |
| Texture·lighting 반영 | 성공 | 목재 texture, normal transform, point-light attenuation과 material parameter 확인 |
| 실패 경로 | 성공 | 잘못된 CWD에서 texture load 실패를 보고하고 exit code `-1`로 종료 |
| Capture/Result | 확보 | 기본 light와 위치 조정 전체 창 screenshot, 사용자 승인 완료 |

Build 뒤의 `pwsh.exe` 환경 경고는 MSBuild 성공과 분리해 관찰했으며 실행 결과에는 영향을 주지 않았다.

## Capture/Result

기본 `lightPos=(0, 0, -1)`은 회전한 box의 전면과 인접 face에 texture와 point-light highlight를 함께 표시한다.

![Chapter06 Step5A Texturing LightingSelf 기본 조명](../../Docs/_assets/captures/part2_chapter06_05a_texturing_lighting_self_default.png)

`lightPos=(0.75, 0.5, -1)`로 옮기면 같은 model·camera·material에서 face별 밝기와 highlight 위치가 달라진다.

![Chapter06 Step5A Texturing LightingSelf 조정 조명](../../Docs/_assets/captures/part2_chapter06_05a_texturing_lighting_self_light_adjusted.png)

두 screenshot이 조명 위치에 따른 정적 차이를 충분히 보여주므로 video는 제외한다.

## 구현 범위와 한계

- 단일 point light와 단일 texture만 사용한다.
- Texture color는 ambient·diffuse뿐 아니라 specular에도 곱하는 예제 고유 구현이다.
- Gamma correction, normal mapping과 physically based attenuation은 다루지 않는다.
- Texture는 mip level 하나만 생성하며 anisotropic filtering을 검증하지 않는다.
- Runtime shader와 texture load는 project 폴더 CWD에 의존한다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 범위에서 제외한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter06 Step5 Texturing](../06_GraphicsPipeline_Step5_Texturing/README.md)
- [다음 단계: Chapter06 Step6 Lighting](../06_GraphicsPipeline_Step6_Lighting/README.md)
- [Texture Sampling Topic](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Phong And Blinn-Phong Topic](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
- [Light Types Topic](../../Docs/01_Topics/LightingAndShading/LightTypes.md)
- [Step5A 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_TexturingLightingSelf.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
