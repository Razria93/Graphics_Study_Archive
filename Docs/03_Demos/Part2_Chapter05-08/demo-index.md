# Part2_Chapter05-08 Demo Index

이 문서는 `Part2_Chapter05-08`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- Chapter05 bundle: Step1 Matrix(GLM) → Step2 Lights(GLM) → Step3 DirectXMath → Step4 Lights(SimpleMath)
- 주요 demo 후보: pipeline, modeling, cubemap, IBL, bloom
- 비고: Step1·3은 설명 중심 단계, Step2·4는 같은 transform 의도의 GLM·SimpleMath 대응 visual로 유지

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Chapter05 Step1 Matrix(GLM) | [상세 Demo](05_MatrixGLM.md) | [Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/README.md) | [Matrix And Affine Transformations](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | 없음 | 미게시 | 제외 | 결정적 console 출력으로 설명, screenshot·video 제외 |
| Chapter05 Step2 Lights(GLM) | [상세 Demo](05_LightsGLM.md) | [Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md) | [Matrix](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md), [Lighting](../../01_Topics/LightingAndShading/PhongAndBlinnPhong.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | [기본](../../_assets/captures/part2_chapter05_02_lights_glm_default.png), [조정](../../_assets/captures/part2_chapter05_02_lights_glm_adjusted.png) | 미게시 | 확보 | GLM model·normal transform과 CPU lighting 연결 |
| Chapter05 Step3 DirectXMath | [상세 Demo](05_DirectXMath.md) | [Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/README.md) | [Matrix And Affine Transformations](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | 없음 | 미게시 | 제외 | 결정적 console 출력으로 SIMD API와 translation convention 설명 |
| Chapter05 Step4 Lights(SimpleMath) | [상세 Demo](05_LightsSimpleMath.md) | [Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step4_Lights%28SimpleMath%29/README.md) | [Matrix](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md), [Lighting](../../01_Topics/LightingAndShading/PhongAndBlinnPhong.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | [조정](../../_assets/captures/part2_chapter05_04_lights_simplemath_adjusted.png) | 미게시 | 확보 | Step1~4 bundle의 결론으로 Step2 GLM과 SimpleMath convention 결과 비교 |
| 최소 capture | [Step2 상세 Demo](05_LightsGLM.md) | [Step2 Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md) | [Matrix](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | [기본](../../_assets/captures/part2_chapter05_02_lights_glm_default.png), [조정](../../_assets/captures/part2_chapter05_02_lights_glm_adjusted.png) | 미게시 | 확보 | Chapter 최초 graphics Example visual |
| 대표 capture | 없음 | 미확인 | 미확인 | `Docs/02_Verification` | 없음 | 미게시 | 후보 | 대표 예제 선정 후 갱신 |
| video | 없음 | Step1·2·3·4 | [Matrix](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md) | [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) | 없음 | 미게시 | 제외 | Step1·3 console과 Step2·4 정적 비교로 설명 가능 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
