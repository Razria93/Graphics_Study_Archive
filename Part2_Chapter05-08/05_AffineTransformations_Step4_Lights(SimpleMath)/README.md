# Chapter05 Step4 Lights(SimpleMath)

이 예제는 Step2의 GLM 기반 CPU rasterizer와 lighting 경로를 DirectXTK SimpleMath로 옮긴다. 같은 cube, affine transform과 Directional·Point·Spot Light를 유지하면서 row-vector convention에 맞는 matrix composition과 inverse-transpose normal transform을 확인한다.

## 실행 진입점

- Solution: `05_AffineTransformations_Step4_Lights(SimpleMath).sln`
- Project type: Windows desktop application
- Entry point: `main.cpp`
- External dependency: DirectXTK SimpleMath, ImGui와 D3D11
- Runtime working directory: project 폴더

## Code Map

| 범위 | 책임 |
| --- | --- |
| [SimpleMath model·normal matrix](Rasterization.cpp#L157-L175) | Row-vector convention의 scale·rotation·translation 합성과 inverse transpose 구성 |
| [CPU rasterization과 normal 보간](Rasterization.cpp#L59-L149) | Triangle coverage, depth, perspective-correct interpolation과 보간 normal 정규화 |
| [SimpleMath vertex transform](MyShader.h#L104-L123) | Position `w=1`과 normal `w=0`을 model·normal matrix로 변환 |
| [CPU Blinn-Phong lighting](MyShader.h#L21-L88) | Directional·Point·Spot Light strength, attenuation과 cone factor 계산 |
| [Light type별 pixel shading](MyShader.h#L130-L149) | 선택된 Light type에 따라 pixel color 계산 |
| [Transform·material·light UI](main.cpp#L65-L151) | 실행 중 object transform, material과 Light parameter 조정 |
| [CPU result upload](Example.cpp#L17-L24) | CPU pixel buffer를 D3D11 dynamic texture로 복사 |

## 구현 요약

SimpleMath는 row-vector convention을 사용하므로 model matrix를 `S * Rx * Ry * Rz * T` 순서로 구성한다. GLM Step2의 `T * Rz * Ry * Rx * S`와 식의 표기는 반대지만 vertex에 적용되는 transform 순서는 scale, X·Y·Z rotation과 translation으로 같다.

Normal은 translation을 제거한 선형 transform의 inverse transpose로 변환한다. Vertex stage와 raster interpolation 이후에 각각 정규화해 non-uniform scale 상태에서도 lighting 입력 방향을 유지한다. Degenerate triangle은 area가 0일 때 coverage 계산 전에 제외한다.

일반 matrix와 convention 이론은 [Matrix And Affine Transformations](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md), 일반 lighting 이론은 [Phong And Blinn-Phong](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)과 [Light Types](../../Docs/01_Topics/LightingAndShading/LightTypes.md), 실제 비교 결과는 [Step4 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_LightsSimpleMath.md), build/run/capture 사실은 [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Runtime shader load | 성공 | `VS.hlsl`, `PS.hlsl` 확인 |
| Capture/Result | 확보 | Step2 GLM과 같은 transform 의도의 전체 창 screenshot |

## Capture/Result

![Chapter05 Step4 SimpleMath adjusted](../../Docs/_assets/captures/part2_chapter05_04_lights_simplemath_adjusted.png)

Step2와 같은 장면에서 Y rotation, translation과 non-uniform scale을 적용한 screenshot을 확보했다. Capture는 SimpleMath matrix 계산 자체를 증명하지 않고, 같은 적용 순서와 normal 처리 결과가 실행 화면에서 유지되는지 비교하는 시각 증거로 사용한다.

## 구현 범위와 한계

- 한 번에 하나의 Directional·Point·Spot Light만 처리한다.
- Point·Spot attenuation은 `fallOffStart`와 `fallOffEnd` 사이의 선형 모델이다.
- Shadow, multiple light accumulation, gamma correction과 tone mapping은 포함하지 않는다.
- HLSL은 CPU rasterization과 lighting을 수행하지 않고 texture presentation만 담당한다.
- Dynamic texture upload의 `RowPitch` 처리는 별도 portability 작업으로 둔다.
- DirectXTK SimpleMath와 ImGui include·library 설정은 개발 환경 integration에 의존한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Step3 DirectXMath](../05_AffineTransformations_Step3_DirectXMath/README.md)
- 다음 단계: Chapter06 Step1 COM 문서화 대기
- [Matrix And Affine Transformations Topic](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Phong And Blinn-Phong Topic](../../Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
- [Light Types Topic](../../Docs/01_Topics/LightingAndShading/LightTypes.md)
- [Step4 Lights(SimpleMath) 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_LightsSimpleMath.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
