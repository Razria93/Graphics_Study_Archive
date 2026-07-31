# Part2 Chapter04

CPU software rasterization에서 triangle coverage와 attribute interpolation을 시작으로 2D primitive, transform, depth, culling, perspective projection과 lighting까지 확장하는 예제 묶음이다. 각 Step의 CPU 결과는 DirectX11 texture를 통해 화면에 표시한다.

## 상태

- 학습 코드 정리: 전체 예제 보관 완료
- 순차 문서화: Step1 Triangle과 Step1A Personal Extension 완료
- Build/run: Step1·Step1A 현재 확인, 나머지 예제 과거 확인
- Capture: Step1과 Step1A 전체 창 screenshot 확보
- Public readiness: 검토 필요

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P2-C04`](../Docs/99_Legacy/source-registry.md) |
| Import status | 코드 보관 완료 |
| Public readiness | Step별 검토 필요 |
| Build/run status | Step1·Step1A Debug/Release x64 현재 확인, 나머지 과거 확인 |
| Next action | Step2 Circle 정규화 |

## 학습 순서

1. [Step1 Triangle](04_Rasterization_Step1_Triangle/README.md)
2. [Step1A Triangle To Circle](04_Rasterization_Step1_TriangleToCircle/README.md)
3. Step2 Circle
4. Step3 Transformations2D
5. Step4 Animation2D
6. Step5 DepthBuffer
7. Step6 ShadersConcept
8. Step7 BackfaceCulling
9. Step8 PerspectiveProjection
10. Step9 Shading
11. Step10 Lights

`04_Rasterization_Step1_TriangleToCircle`은 강의 단계가 아니라 사용자가 Step1 triangle rasterization을 triangle fan 기반 circle approximation으로 확장한 Personal Extension이다. Step2와 합치지 않고 독립 Example과 상세 Demo로 유지한다.

## 현재 Example

### Step1 Triangle

- [Example README](04_Rasterization_Step1_Triangle/README.md)
- [Triangle Rasterization Topic](../Docs/01_Topics/Rasterization/TriangleRasterization.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/01_Triangle.md)

Step1은 raster 좌표 변환, triangle bounding box, edge function과 barycentric RGB interpolation을 구성한다. CPU pixel buffer와 DirectX11 presentation 경계를 이후 Step에서도 공통 기반으로 사용한다.

### Step1A Triangle To Circle

- [Example README](04_Rasterization_Step1_TriangleToCircle/README.md)
- [Triangle Rasterization Topic](../Docs/01_Topics/Rasterization/TriangleRasterization.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/01_TriangleToCircle.md)

Step1A는 Step1을 여러 독립 triangle로 구성한 fan으로 확장한다. Slider에서 segment 수를 바꾸면 fan을 재생성하며, 3개와 기본값 32개의 비교로 polygon이 circle에 가까워지는 변화를 확인한다.

## 후속 예제

| Example | 책임 | 현재 상태 |
| --- | --- | --- |
| `04_Rasterization_Step2_Circle` | indexed triangle 기반 circle 구성 | 정규화 대기, 사용자 시험값 local 보존 |
| `04_Rasterization_Step3_Transformations2D` | 2D transform | 정규화 대기 |
| `04_Rasterization_Step4_Animation2D` | 시간 기반 2D animation | 정규화 대기 |
| `04_Rasterization_Step5_DepthBuffer` | depth test와 visibility | 정규화 대기 |
| `04_Rasterization_Step6_ShadersConcept` | CPU shader abstraction | 정규화 대기 |
| `04_Rasterization_Step7_BackfaceCulling` | triangle winding과 culling | 정규화 대기 |
| `04_Rasterization_Step8_PerspectiveProjection` | perspective projection | 정규화 대기 |
| `04_Rasterization_Step9_Shading` | surface shading | 정규화 대기 |
| `04_Rasterization_Step10_Lights` | light 구성 | 정규화 대기 |

존재하지 않는 Example README와 상세 Demo는 미리 연결하지 않는다. 각 Step을 현재 build/run과 capture로 확인한 뒤 순서대로 추가한다.

## 문서 진입점

- [Rasterization Topics](../Docs/01_Topics/Rasterization/README.md)
- [Verification Index](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Demo Index](../Docs/03_Demos/Part2_Chapter04/demo-index.md)
- [Demo Priority](../Docs/03_Demos/demo-priority.md)
