# Part1 Chapter03

이 Chapter는 CPU ray tracing의 기반부터 environment sampling까지 Step 단위로 확장하는 예제를 정리한다. 각 Step은 코드 폴더 README, Verification와 독립 상세 Demo를 같은 순서로 연결한다.

## 상태

- 학습 코드: Step4~14 보관 완료
- 현재 문서화: Step4~10 완료, Step11 문서화 대기
- 현재 재검증: Step4~10 Debug/Release x64 build/run 완료
- 과거 확인: Step11~14 Debug/Release build/run 성공, 현재 재검증 필요
- Capture: Step4~9 screenshot 확보, Step10 권리 검토 보류

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P1-C03`](../Docs/99_Legacy/source-registry.md) |
| Import status | Step4~14 반영 |
| Public readiness | Step4~9 검토 필요, Step10 권리 검토 보류, Step11~14 미판정 |
| Build/run status | Step4~10 현재 확인, Step11~14 과거 확인 |
| Texture/environment asset | Step10 이후 외부 asset은 각 Step 작업에서 별도 검토 |
| Verification | [Part1 Chapter03 Verification](../Docs/02_Verification/Part1_Chapter03/verification-index.md) |
| Demo | [Part1 Chapter03 Demo Index](../Docs/03_Demos/Part1_Chapter03/demo-index.md) |
| Topic | [Ray Tracing Topics](../Docs/01_Topics/RayTracing/README.md), [Lighting And Shading Topics](../Docs/01_Topics/LightingAndShading/README.md), [Shadow Topics](../Docs/01_Topics/Shadows/README.md) |
| Next action | Step10 input texture 출처 확인 또는 교체, Step11 Supersampling 검증과 문서화 |

## 순차 Step

| 순서 | Example | 문서 상태 | 검증 상태 | 상세 Demo |
| --- | --- | --- | --- | --- |
| Step4 | [DrawingSphere](03_Raytracing_Step4_DrawingSphere/README.md) | 완료 | 현재 확인 | [DrawingSphere Demo](../Docs/03_Demos/Part1_Chapter03/04_DrawingSphere.md) |
| Step5 | [PhongShading](03_Raytracing_Step5_PhongShading/README.md) | 완료 | 현재 확인 | [PhongShading Demo](../Docs/03_Demos/Part1_Chapter03/05_PhongShading.md) |
| Step6 | [PerspectiveView](03_Raytracing_Step6_PerspectiveView/README.md) | 완료 | 현재 확인 | [PerspectiveView Demo](../Docs/03_Demos/Part1_Chapter03/06_PerspectiveView.md) |
| Step7 | [Triangle](03_Raytracing_Step7_Triangle/README.md) | 완료 | 현재 확인 | [Triangle Demo](../Docs/03_Demos/Part1_Chapter03/07_Triangle.md) |
| Step8 | [Shadow](03_Raytracing_Step8_Shadow/README.md) | 완료 | 현재 확인 | [Shadow Demo](../Docs/03_Demos/Part1_Chapter03/08_Shadow.md) |
| Step9 | [Barycentric Coordinates](03_Raytracing_Step9_BarycentricCordinates/README.md) | 완료 | 현재 확인 | [Barycentric Coordinates Demo](../Docs/03_Demos/Part1_Chapter03/09_BarycentricCoordinates.md) |
| Step10 | [Texturing](03_Raytracing_Step10_Texturing/README.md) | 완료 | 현재 확인 | 권리 검토 보류 |
| Step11 | `03_Raytracing_Step11_Supersampling` | 대기 | 과거 확인 | 대기 |
| Step12 | `03_Raytracing_Step12_Reflection` | 대기 | 과거 확인 | 대기 |
| Step13 | `03_Raytracing_Step13_Transparency` | 대기 | 과거 확인 | 대기 |
| Step14 | `03_Raytracing_Step14_CubeEnvironment` | 대기 | 과거 확인 | 대기 |

## Topic 연결

- [Ray](../Docs/01_Topics/RayTracing/Ray.md)
- [Intersection](../Docs/01_Topics/RayTracing/Intersection.md)
- [Phong Shading](../Docs/01_Topics/LightingAndShading/PhongShading.md)
- [Shadow Ray](../Docs/01_Topics/Shadows/ShadowRay.md)
- [Barycentric Coordinates](../Docs/01_Topics/RayTracing/BarycentricCoordinates.md)
- [Texture Sampling](../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)

Step11 이후 Topic은 해당 Step의 코드와 실행 결과를 확인한 뒤 순서대로 연결한다.

## Asset 검토가 필요한 Step

- Step10~13 texture는 실제 사용 여부와 출처를 각 Step 작업에서 확인한다.
- Step14 environment asset은 public 공개 전 attribution과 사용 subset을 검토한다.
