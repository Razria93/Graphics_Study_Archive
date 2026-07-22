# Topics

이 폴더는 여러 예제를 관통하는 graphics concept와 rendering pipeline 설명의 정본 위치다. 예제 하나의 구현 설명은 `Docs/01_Examples`에 두고, Topic 문서는 개념과 여러 예제의 연결을 설명한다.

## 책임

- 반복 설명되는 그래픽스 원리와 DirectX11 pipeline 개념을 모은다.
- 예제별 구현 세부사항은 복제하지 않고 `Docs/01_Examples`로 링크한다.
- build/run/capture 결과는 `Docs/03_Verification`, `Docs/04_Demos`로 링크한다.
- public 후보 문장으로 재사용할 수 있는 설명은 강의 원문이 아니라 직접 이해한 문장으로 작성한다.

## Topic Groups

| 그룹 | 위치 | 상태 |
| --- | --- | --- |
| Ray Tracing | [RayTracing](RayTracing/README.md) | 골격 작성 |
| Rasterization | [Rasterization](Rasterization/README.md) | 골격 작성 |
| DirectX11 Pipeline | [DirectX11Pipeline](DirectX11Pipeline/README.md) | 골격 작성 |
| Texturing And Mapping | [TexturingAndMapping](TexturingAndMapping/README.md) | 골격 작성 |
| Lighting And Shading | [LightingAndShading](LightingAndShading/README.md) | 골격 작성 |
| PBR And IBL | [PBRAndIBL](PBRAndIBL/README.md) | 골격 작성 |
| Shadows | [Shadows](Shadows/README.md) | 골격 작성 |
| Compute And Simulation | [ComputeAndSimulation](ComputeAndSimulation/README.md) | 골격 작성 |
| Animation And Physics | [AnimationAndPhysics](AnimationAndPhysics/README.md) | 골격 작성 |

## 작성 기준

- 평서형 현재형을 사용한다.
- 코드 확인 전 항목은 `미확인`으로 둔다.
- Topic 문서에는 개념, pipeline 위치, 관련 예제, 코드 확인 포인트, 시연 포인트를 둔다.
- 강의 원문 구조와 표현을 그대로 옮기지 않는다.
