# Part2 Chapter04

CPU software rasterization에서 triangle coverage와 attribute interpolation을 시작으로 2D primitive, transform, depth, culling, perspective projection과 lighting까지 확장하는 예제 묶음이다. 각 Step의 CPU 결과는 DirectX11 texture를 통해 화면에 표시한다.

## 상태

- 학습 코드 정리: 전체 예제 보관 완료
- 순차 문서화: Step1 Triangle부터 Step6 ShadersConcept까지 작성
- Build/run: Step1·Step1A·Step2·Step3·Step4·Step5·Step6 현재 확인, 나머지 예제 과거 확인
- Capture: Step1부터 Step6까지 screenshot 확보, Step1A·Step4·Step5·Step6 selected video 검수 완료
- Public readiness: 검토 필요

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P2-C04`](../Docs/99_Legacy/source-registry.md) |
| Import status | 코드 보관 완료 |
| Public readiness | Step별 검토 필요 |
| Build/run status | Step1·Step1A·Step2·Step3·Step4·Step5·Step6 Debug/Release x64 현재 확인, 나머지 과거 확인 |
| Next action | Step7 BackfaceCulling 정규화 |

## 학습 순서

1. [Step1 Triangle](04_Rasterization_Step1_Triangle/README.md)
2. [Step1A Triangle To Circle](04_Rasterization_Step1_TriangleToCircle/README.md)
3. [Step2 Circle](04_Rasterization_Step2_Circle/README.md)
4. [Step3 Transformations2D](04_Rasterization_Step3_Transformations2D/README.md)
5. [Step4 Animation2D](04_Rasterization_Step4_Animation2D/README.md)
6. [Step5 DepthBuffer](04_Rasterization_Step5_DepthBuffer/README.md)
7. [Step6 ShadersConcept](04_Rasterization_Step6_ShadersConcept/README.md)
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

### Step2 Circle

- [Example README](04_Rasterization_Step2_Circle/README.md)
- [Triangle Rasterization Topic](../Docs/01_Topics/Rasterization/TriangleRasterization.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/02_Circle.md)

Step2는 center와 outer-ring position/color를 공유 CPU 배열에 저장하고 index 세 개로 triangle을 조립한다. 고정된 32-triangle fan과 per-indexed-triangle rasterization을 다루며 Step1A의 runtime slider와 독립 triangle 목록을 포함하지 않는다.

### Step3 Transformations2D

- [Example README](04_Rasterization_Step3_Transformations2D/README.md)
- [2D Transformations Topic](../Docs/01_Topics/Rasterization/Transformations2D.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/03_Transformations2D.md)

Step3은 원본 5-segment polygonal fan을 유지하고 `Rotation1 → Scale → Translation1 → Rotation2 → Translation2` 순서로 derived vertex를 매 frame 계산한다. 낮은 segment 수로 orientation과 non-uniform scale을 식별하고 두 번째 rotation이 이동 offset까지 원점 기준으로 회전시키는 결과를 보여준다.

### Step4 Animation2D

- [Example README](04_Rasterization_Step4_Animation2D/README.md)
- [2D Animation Topic](../Docs/01_Topics/AnimationAndPhysics/Animation2D.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/04_Animation2D.md)

Step4는 Sun, Earth와 Moon의 angle을 매 frame 갱신한다. Earth는 Sun 원점을 기준으로 공전하고 Moon은 Earth 주변 local orbit에 Earth의 parent orbit을 조합해 계층적 2D animation을 구성한다.

### Step5 DepthBuffer

- [Example README](04_Rasterization_Step5_DepthBuffer/README.md)
- [Depth Buffer Topic](../Docs/01_Topics/Rasterization/DepthBuffer.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/05_DepthBuffer.md)

Step5는 frame마다 per-pixel depth buffer를 초기화하고 barycentric Z를 기존 값과 비교한다. 기본과 반전 상태는 geometry와 draw order를 유지한 채 center Z만 바꿔 red, blue와 yellow circle의 visibility가 depth로 결정되는 결과를 보여준다.

### Step6 ShadersConcept

- [Example README](04_Rasterization_Step6_ShadersConcept/README.md)
- [Shader Stage Topic](../Docs/01_Topics/DirectX11Pipeline/ShaderStage.md)
- [Verification](../Docs/02_Verification/Part2_Chapter04/verification-index.md)
- [Detailed Demo](../Docs/03_Demos/Part2_Chapter04/06_ShadersConcept.md)

Step6는 CPU software rasterizer의 transform과 fragment color 계산을 `MyVertexShader()`와 `MyPixelShader()` 입출력 계약으로 분리한다. DirectX11 HLSL은 CPU framebuffer texture를 full-screen quad로 표시하는 presentation 경로이며 학습용 CPU shader stage와 별도 책임을 가진다.

## 후속 예제

| Example | 책임 | 현재 상태 |
| --- | --- | --- |
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
