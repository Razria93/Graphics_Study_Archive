# Part1 Chapter03

이 Chapter는 CPU ray tracing의 기반부터 environment sampling까지 Step 단위로 확장하는 예제를 정리한다. 각 Step은 코드 폴더 README, Verification와 독립 상세 Demo를 같은 순서로 연결한다.

## 상태

- 학습 코드: Step4~14 보관 완료
- 현재 문서화: Step4~14 완료
- 현재 재검증: Step4~14 Debug/Release x64 build/run 완료
- Capture: Step4~14 screenshot 확보

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P1-C03`](../Docs/99_Legacy/source-registry.md) |
| Import status | Step4~14 반영 |
| Public readiness | Step4~14 asset 검토 완료, GitHub 게시 후보 미선정 |
| Build/run status | Step4~14 현재 확인 |
| Texture/environment asset | Step10~13 검수 asset 적용, Step14는 Humus CC BY 3.0 cubemap 6면과 attribution 원문 유지 |
| Verification | [Part1 Chapter03 Verification](../Docs/02_Verification/Part1_Chapter03/verification-index.md) |
| Demo | [Part1 Chapter03 Demo Index](../Docs/03_Demos/Part1_Chapter03/demo-index.md) |
| Topic | [Ray Tracing Topics](../Docs/01_Topics/RayTracing/README.md), [Lighting And Shading Topics](../Docs/01_Topics/LightingAndShading/README.md), [Shadow Topics](../Docs/01_Topics/Shadows/README.md), [Texturing And Mapping Topics](../Docs/01_Topics/TexturingAndMapping/README.md) |
| Next action | 대표 Demo Publication 판정과 GitHub 게시 후보 구성 |

## 순차 Step

| 순서 | Example | 문서 상태 | 검증 상태 | 상세 Demo |
| --- | --- | --- | --- | --- |
| Step4 | [DrawingSphere](03_Raytracing_Step4_DrawingSphere/README.md) | 완료 | 현재 확인 | [DrawingSphere Demo](../Docs/03_Demos/Part1_Chapter03/04_DrawingSphere.md) |
| Step5 | [PhongShading](03_Raytracing_Step5_PhongShading/README.md) | 완료 | 현재 확인 | [PhongShading Demo](../Docs/03_Demos/Part1_Chapter03/05_PhongShading.md) |
| Step6 | [PerspectiveView](03_Raytracing_Step6_PerspectiveView/README.md) | 완료 | 현재 확인 | [PerspectiveView Demo](../Docs/03_Demos/Part1_Chapter03/06_PerspectiveView.md) |
| Step7 | [Triangle](03_Raytracing_Step7_Triangle/README.md) | 완료 | 현재 확인 | [Triangle Demo](../Docs/03_Demos/Part1_Chapter03/07_Triangle.md) |
| Step8 | [Shadow](03_Raytracing_Step8_Shadow/README.md) | 완료 | 현재 확인 | [Shadow Demo](../Docs/03_Demos/Part1_Chapter03/08_Shadow.md) |
| Step9 | [Barycentric Coordinates](03_Raytracing_Step9_BarycentricCordinates/README.md) | 완료 | 현재 확인 | [Barycentric Coordinates Demo](../Docs/03_Demos/Part1_Chapter03/09_BarycentricCoordinates.md) |
| Step10 | [Texturing](03_Raytracing_Step10_Texturing/README.md) | 완료 | 현재 확인 | [Texturing Demo](../Docs/03_Demos/Part1_Chapter03/10_Texturing.md) |
| Step11 | [Supersampling](03_Raytracing_Step11_Supersampling/README.md) | 완료 | 현재 확인 | [Supersampling Demo](../Docs/03_Demos/Part1_Chapter03/11_Supersampling.md) |
| Step12 | [Reflection](03_Raytracing_Step12_Reflection/README.md) | 완료 | 현재 확인 | [Reflection Demo](../Docs/03_Demos/Part1_Chapter03/12_Reflection.md) |
| Step13 | [Transparency](03_Raytracing_Step13_Transparency/README.md) | 완료 | 현재 확인 | [Transparency Demo](../Docs/03_Demos/Part1_Chapter03/13_Transparency.md) |
| Step14 | [CubeEnvironment](03_Raytracing_Step14_CubeEnvironment/README.md) | 완료 | 현재 확인 | [CubeEnvironment Demo](../Docs/03_Demos/Part1_Chapter03/14_CubeEnvironment.md) |

## Topic 연결

- [Ray](../Docs/01_Topics/RayTracing/Ray.md)
- [Intersection](../Docs/01_Topics/RayTracing/Intersection.md)
- [Phong Shading](../Docs/01_Topics/LightingAndShading/PhongShading.md)
- [Shadow Ray](../Docs/01_Topics/Shadows/ShadowRay.md)
- [Barycentric Coordinates](../Docs/01_Topics/RayTracing/BarycentricCoordinates.md)
- [Texture Sampling](../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Sampling And Anti Aliasing](../Docs/01_Topics/RayTracing/SamplingAndAntiAliasing.md)
- [Recursive Reflection](../Docs/01_Topics/RayTracing/RecursiveReflection.md)
- [Refraction And Transparency](../Docs/01_Topics/RayTracing/RefractionAndTransparency.md)
- [Cubemap And Environment Mapping](../Docs/01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)
