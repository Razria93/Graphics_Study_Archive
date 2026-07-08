# Import Manifest: Part1_Chapter03

이 문서는 `C:\ComputerGraphics\Part1_Chapter03` raw/reference 자료를 `C:\Graphics_Study_Archive\Part1_Chapter03` archive 폴더로 Step별 선별 정리하기 위한 manifest입니다.

Part1 Chapter03은 CPU ray tracing 구현이 단계적으로 확장되는 구간입니다. Ch03 전체 구조는 먼저 문서화하되, 실제 code import는 Step 단위로 진행합니다.

## Source / Target

| 항목 | 값 |
| --- | --- |
| Source | `C:\ComputerGraphics\Part1_Chapter03` |
| Target | `Part1_Chapter03` |
| Docs target | `Docs/Part1_Chapter03` |
| Import status | scaffold 작성 |
| Public readiness | 검토 필요 |
| Build/run status | 미확인 |
| 작업 방식 | Ch03 전체 계획 + Step별 import |

## Raw 구조 요약

| Raw path | 성격 | 판단 |
| --- | --- | --- |
| `03_Raytracing_Step1_Vector(GLM)/` | GLM vector 기초 | 후보 |
| `03_Raytracing_Step2_CircleScreenSpace/` | screen-space circle | 후보 |
| `03_Raytracing_Step3_CircleWorldSpace/` | world-space circle | 후보 |
| `03_Raytracing_Step4_DrawingSphere/` | ray-sphere intersection | 1차 우선 |
| `03_Raytracing_Step5_PhongShading/` | Phong shading | 1차 우선 |
| `03_Raytracing_Step6_PerspectiveView/` | camera/perspective ray | 1차 우선 |
| `03_Raytracing_Step7_Triangle/` | ray-triangle intersection | 2차 후보 |
| `03_Raytracing_Step8_Shadow/` | shadow ray | 2차 후보 |
| `03_Raytracing_Step8_Shadow_Square/` | shadow + square scene | 2차 후보 |
| `03_Raytracing_Step9_BarycentricCordinates/` | barycentric coordinate | 2차 후보 |
| `03_Raytracing_Step10_Texturing/` | texture mapping | asset 검토 필요 |
| `03_Raytracing_Step11_Supersampling/` | anti-aliasing / supersampling | 2차 후보 |
| `03_Raytracing_Step12_Reflection/` | reflection | asset 검토 필요 |
| `03_Raytracing_Step13_Transparency/` | transparency/refraction 후보 | asset 검토 필요 |
| `03_Raytracing_Step14_CubeEnvironment/` | cube environment / skybox | 별도 asset 검토 |

## 1차 Import 순서

1. `03_Raytracing_Step4_DrawingSphere`
2. `03_Raytracing_Step5_PhongShading`
3. `03_Raytracing_Step6_PerspectiveView`

이 세 Step은 ray tracing chapter의 핵심 흐름을 설명하기 좋고, build-guide의 최소 검증 대상과도 연결됩니다.

## 2차 Import 후보

1. `03_Raytracing_Step7_Triangle`
2. `03_Raytracing_Step8_Shadow`
3. `03_Raytracing_Step9_BarycentricCordinates`
4. `03_Raytracing_Step11_Supersampling`

## Asset 검토 필요 Step

| Step | Asset 후보 | 판단 |
| --- | --- | --- |
| Step10 Texturing | `shadertoy_abstract1.jpg` | private archive 반영 전 출처/라이선스 확인 |
| Step12 Reflection | `shadertoy_abstract1.jpg`, `back.jpg` | private archive 반영 전 출처/라이선스 확인 |
| Step13 Transparency | `shadertoy_abstract1.jpg`, `back.jpg` | private archive 반영 전 출처/라이선스 확인 |
| Step14 CubeEnvironment | `skybox/`, `SaintPetersBasilica/`, `.dds`, `.jpg` | 별도 manifest 또는 asset review 필요 |

## Include candidates

Step별로 아래 파일 유형만 선별 반영합니다.

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- `main.cpp`
- `Example.h`
- ray tracing domain headers: `Ray.h`, `Hit.h`, `Sphere.h`, `Raytracer.h`, `Light.h`, `Object.h`, `Triangle.h`, `Square.h`, `Texture.h`
- `Texture.cpp`는 texture Step에서만 검토
- `VS.hlsl`, `PS.hlsl`

## Exclude patterns

다음 항목은 archive로 복사하지 않습니다.

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- raw result/capture image
- 출처/라이선스 미확인 texture, skybox, environment map
- helper script 또는 생성 도구는 별도 검토 전까지 제외

## Related raw docs

| Raw docs | 연결 Step |
| --- | --- |
| `Chapter03_RayTarcing_Step1~2.md` | Step1-2 |
| `Chapter03_Raytracing_Step3_CircleWorldSpace.md` | Step3 |
| `Chapter03_Raytracing_Step4_DrawingSphere.md` | Step4 |
| `Chapter03_Raytracing_Step5_PhongShading.md` | Step5 |
| `Chapter03_Raytracing_Step6_PerspectiveView.md` | Step6 |
| `Chapter03_Raytracing_Step7_Triangle.md` | Step7 |
| `Chapter03_Raytracing_Step8_Shadow.md` | Step8 |
| `Chapter03_Raytracing_Step9_BarycentricCordinates.md` | Step9 |
| `Chapter03_Raytracing_Step10_Texturing.md` | Step10 |
| `Chapter03_Raytracing_Step11_Supersampling.md` | Step11 |
| `@ Raytacing vs Rasterization.md` | Ch03 개념 보조 |
| `@ Phong & Blinn-Phong 의 이해.md` | Step5 개념 보조 |
| `@ Texturing & Sampling.md` | Step10+ 개념 보조 |

## Unresolved risks

| 항목 | 내용 | 상태 |
| --- | --- | --- |
| 강의 기반 코드 범위 | Step별 학습 코드이므로 private archive 기준으로만 우선 반영 | 검토 필요 |
| raw source comments | 장문 학습 메모가 많을 수 있어 local-only 분리 필요 | 검토 필요 |
| texture/skybox assets | Step10 이후 외부 asset 출처 확인 필요 | 검토 필요 |
| Step14 구조 | nested project folder와 대량 asset 포함 | 별도 검토 |
| build/run | archive 이동 후 Debug/Release 실행 필요 | 미확인 |
| capture | 현재 촬영 보류 정책 적용 | 보류 |

## Next action

1. `03_Raytracing_Step4_DrawingSphere`부터 Step 단위로 code/project files를 선별 반영합니다.
2. source comments와 raw markdown notes를 `local/Part1_Chapter03/<Step>/`로 분리합니다.
3. tracked docs는 `Docs/Part1_Chapter03/<Step>/README.md`, `status.md`에 얇게 정리합니다.
4. Debug/Release 실행 확인 후 build-guide와 migration-board를 갱신합니다.
