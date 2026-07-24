# Topic Docs

이 폴더는 여러 예제를 관통하는 graphics concept와 rendering pipeline 설명의 정본 위치다. 예제 하나의 구현 설명은 코드 폴더 README에 두고, Topic 문서는 개념과 여러 예제의 연결을 설명한다.

## Topic Groups

| 그룹 | 위치 | 상태 |
| --- | --- | --- |
| Ray Tracing | [RayTracing](RayTracing/README.md) | 골격 작성 |
| Rasterization | [Rasterization](Rasterization/README.md) | 골격 작성 |
| DirectX11 Pipeline | [DirectX11Pipeline](DirectX11Pipeline/README.md) | 진행 중 |
| Texturing And Mapping | [TexturingAndMapping](TexturingAndMapping/README.md) | 골격 작성 |
| Lighting And Shading | [LightingAndShading](LightingAndShading/README.md) | 골격 작성 |
| PBR And IBL | [PBRAndIBL](PBRAndIBL/README.md) | 골격 작성 |
| Shadows | [Shadows](Shadows/README.md) | 골격 작성 |
| Compute And Simulation | [ComputeAndSimulation](ComputeAndSimulation/README.md) | 골격 작성 |
| Animation And Physics | [AnimationAndPhysics](AnimationAndPhysics/README.md) | 골격 작성 |

## 작성 기준

- Topic 문서는 특정 예제의 README를 복제하지 않는다.
- 예제별 구현 세부사항은 코드 폴더 README로 링크한다.
- 직접 확인하지 않은 build/run/capture 결과는 `Docs/02_Verification`에 남긴다.
- public 후보 여부는 `Docs/05_Publication` 기준을 따른다.
