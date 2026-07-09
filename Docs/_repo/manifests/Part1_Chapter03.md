# Import Manifest: Part1_Chapter03

이 문서는 `C:\ComputerGraphics\Part1_Chapter03` raw/reference 자료를 `C:\Graphics_Study_Archive\Part1_Chapter03` archive 폴더로 step별 선별 정리하기 위한 manifest입니다.

## Source / Target

| 항목 | 값 |
| --- | --- |
| Source | `C:\ComputerGraphics\Part1_Chapter03` |
| Target | `Part1_Chapter03` |
| Docs target | `Docs/Part1_Chapter03` |
| Import status | Step4-11 반영 |
| Public readiness | 검토 필요 |
| Build/run status | Step4-11 Debug/Release build/run 성공 |
| 작업 방식 | Ch03 전체 계획 + Step별 import |

## Raw 구조 요약

| Raw path | 성격 | 판단 |
| --- | --- | --- |
| `03_Raytracing_Step1_Vector(GLM)/` | GLM vector basics | 후보 |
| `03_Raytracing_Step2_CircleScreenSpace/` | screen-space circle | 후보 |
| `03_Raytracing_Step3_CircleWorldSpace/` | screen-space to world-space 확장 | 후보 |
| `03_Raytracing_Step4_DrawingSphere/` | ray-sphere intersection | 반영 완료 |
| `03_Raytracing_Step5_PhongShading/` | Phong shading | 반영 완료 |
| `03_Raytracing_Step6_PerspectiveView/` | camera/perspective ray | 반영 완료 |
| `03_Raytracing_Step7_Triangle/` | ray-triangle intersection | 반영 완료 |
| `03_Raytracing_Step8_Shadow/` | shadow ray | 반영 완료 |
| `03_Raytracing_Step8_Shadow_Square/` | shadow + square scene | 반영 완료 |
| `03_Raytracing_Step9_BarycentricCordinates/` | barycentric coordinate | 반영 완료 |
| `03_Raytracing_Step10_Texturing/` | texture mapping | 반영 완료 |
| `03_Raytracing_Step11_Supersampling/` | anti-aliasing / supersampling | 반영 완료 |
| `03_Raytracing_Step12_Reflection/` | reflection | asset 검토 필요 |
| `03_Raytracing_Step13_Transparency/` | transparency/refraction 후보 | asset 검토 필요 |
| `03_Raytracing_Step14_CubeEnvironment/` | cube environment / skybox | 별도 asset 검토 |

## Include candidates

Step별로 아래 파일 유형만 선별 반영합니다.

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- `main.cpp`
- `Example.h`
- ray tracing domain headers: `Ray.h`, `Hit.h`, `Sphere.h`, `Raytracer.h`, `Light.h`, `Object.h`, `Triangle.h`, `Square.h`, `Texture.h`
- `Texture.cpp`는 texture step부터 포함
- `VS.hlsl`, `PS.hlsl`
- 실행에 필요한 강의 제공 open-source 성격의 입력 asset

## Exclude patterns

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- raw result/capture image
- public 공개 전 출처/라이선스 표기가 불명확한 asset
- helper script 또는 생성 도구는 별도 검토 전까지 제외

## Step4-11 반영 기록

| Step | Code import | Source comment cleanup | Debug x64 build | Release x64 build | Run | Capture |
| --- | --- | --- | --- | --- | --- | --- |
| Step4 DrawingSphere | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step5 PhongShading | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step6 PerspectiveView | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step7 Triangle | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step8 Shadow | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step8 Shadow Square | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step9 BarycentricCordinates | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step10 Texturing | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |
| Step11 Supersampling | 완료 | 완료 | 성공 | 성공 | 성공 | 보류 |

## Asset record

| Step | Asset | Archive status | Public status |
| --- | --- | --- | --- |
| Step10 Texturing | `shadertoy_abstract1.jpg` | 포함 | 공개 전 출처/라이선스 확인 |
| Step11 Supersampling | `shadertoy_abstract1.jpg` | 포함 | 공개 전 출처/라이선스 확인 |

## Related raw docs

| Raw docs | 연결 Step |
| --- | --- |
| `Chapter03_RayTarcing_Step1~2.md` | Step1-2 |
| `Chapter03_Raytracing_Step3_CircleWorldSpace.md` | Step3 |
| `Chapter03_Raytracing_Step4_DrawingSphere.md` | Step4 |
| `Chapter03_Raytracing_Step5_PhongShading.md` | Step5 |
| `Chapter03_Raytracing_Step6_PerspectiveView.md` | Step6 |
| `Chapter03_Raytracing_Step7_Triangle.md` | Step7 |
| `Chapter03_Raytracing_Step8_Shadow.md` | Step8 Shadow / Shadow Square |
| `Chapter03_Raytracing_Step9_BarycentricCordinates.md` | Step9 |
| `Chapter03_Raytracing_Step10_Texturing.md` | Step10 |
| `Chapter03_Raytracing_Step11_Supersampling.md` | Step11 |
| `@ Raytacing vs Rasterization.md` | Ch03 개념 보조 |
| `@ Phong & Blinn-Phong 관련.md` | Step5 개념 보조 |
| `@ Texturing & Sampling.md` | Step10+ 개념 보조 |

## Next action

1. `03_Raytracing_Step12_Reflection` asset/import 범위를 검토합니다.
2. Step12 이후 reflection/skybox 관련 asset은 별도 asset review를 거친 뒤 진행합니다.
