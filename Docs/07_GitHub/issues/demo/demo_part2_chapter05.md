# Part2 Chapter05 Affine Transformations API 비교 Demo

## 요약

`Part2_Chapter05-08` Chapter05는 GLM으로 확인한 matrix와 affine transformation을
DirectXMath·SimpleMath 환경으로 옮기는 학습 흐름이다.
서로 다른 vector convention에 맞춰 matrix composition 순서를 구성하면 같은 transform
의도와 lighting 결과를 만들 수 있음을 Step2와 Step4의 대응 결과로 확인한다.

## 핵심 목표

- GLM column-vector와 SimpleMath row-vector convention의 composition 순서 비교
- Position과 normal의 변환을 분리하고 inverse-transpose normal matrix 적용
- Step2와 Step4에서 대응하는 silhouette와 lighting 결과 확인

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | Step2·Step4 screenshot | 아래 시각 정보에서 GLM과 SimpleMath 결과를 비교함 |
| Result image | Step2·Step4 rendered result | 조정된 transform과 lighting 결과를 기록함 |
| Video | 없음 | 정적 screenshot으로 API 대응 결과를 확인함 |

## 시각 정보

### Step2 — GLM Transform

GLM column-vector convention으로 Y rotation과 non-uniform scale을 적용한 cube다.
Inverse-transpose normal matrix를 분리해 변형된 geometry의 면별 Directional Light 결과를 유지한다.

![Step2 GLM Transform](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter05_02_lights_glm_adjusted.png?raw=true)

### Step4 — SimpleMath Transform

SimpleMath row-vector convention으로 같은 적용 순서를 다시 구성한 결과다.
API와 multiplication 표기는 달라지지만 대응하는 silhouette와 lighting 의도를 유지한다.

![Step4 SimpleMath Transform](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter05_04_lights_simplemath_adjusted.png?raw=true)

## 구현 하이라이트

### Convention에 맞춘 model matrix

GLM은 column-vector convention에 맞춰 오른쪽 matrix부터 적용한다.
SimpleMath는 row-vector convention에 맞춰 반대 방향으로 composition을 구성한다.
이 선택은 같은 transform 적용 순서를 서로 다른 API 표현으로 연결한다.

- [GLM model과 inverse-transpose normal matrix 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/Rasterization.cpp#L140-L160)
- [SimpleMath model과 inverse-transpose normal matrix 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/05_AffineTransformations_Step4_Lights%28SimpleMath%29/Rasterization.cpp#L157-L175)

### Position과 normal의 분리

Position은 translation의 영향을 받는 homogeneous coordinate로 변환한다.
Normal은 방향 vector로 변환한다.
Non-uniform scale에서는 model matrix 대신 inverse transpose를 normal에 적용해
surface와의 직교 관계를 보존한다.

- [GLM position과 normal 변환](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/MyShader.h#L90-L110)
- [SimpleMath position과 normal 변환](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/05_AffineTransformations_Step4_Lights%28SimpleMath%29/MyShader.h#L104-L123)

### 처리 흐름

1. Scale, rotation과 translation parameter를 읽는다.
2. API의 vector convention에 맞춰 model matrix를 구성한다.
3. Inverse-transpose normal matrix를 별도로 계산한다.
4. CPU vertex stage에서 position과 normal을 변환한다.
5. Rasterization과 Blinn-Phong shading 결과를 DirectX11 texture로 표시한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void BuildAffineLightingPseudo(const Transform& transform, bool usesColumnVector)
{
    if (!transform.IsValid()) {
        return;
    }

    Matrix model = usesColumnVector
        ? ComposeColumnVector(transform)
        : ComposeRowVector(transform);
    Matrix normalMatrix = InverseTranspose(model);

    for (Vertex& vertex : vertices) {
        vertex.position = TransformPosition(model, vertex.position);
        vertex.normal = TransformDirection(normalMatrix, vertex.normal);
    }

    RenderBlinnPhong(vertices);
}
```

원본 코드: [GLM model과 inverse-transpose normal matrix 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/Rasterization.cpp#L140-L160)

## 검증 상태

- Build/Run: Chapter05 Step1–4 Debug/Release x64 성공
- Capture/Result: Step2 GLM과 Step4 SimpleMath 대응 screenshot의 기술·시각 검수 완료
- Documentation: 문서 validator와 GitHub Actions `Docs Validation` 검사 대상

## 구현 범위와 한계

- 포함: GLM과 DirectXMath·SimpleMath의 affine transform API 전환, normal transform과 CPU lighting 결과 비교
- 한계: 좌표계·memory layout·vector convention은 서로 다른 개념이며 두 API가 같은 내부 표현을 사용한다는 의미가 아니다.
- 한계: 한 번에 하나의 Directional·Point·Spot Light만 처리하며 PBR과 gamma correction은 포함하지 않는다.

## 관련 문서

### Chapter 안내

- [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/README.md)
- [Chapter05-08 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
- [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### 대표 구현

- Step2 Lights(GLM): [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/05_LightsGLM.md)
- Step4 Lights(SimpleMath): [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/05_AffineTransformations_Step4_Lights%28SimpleMath%29/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/05_LightsSimpleMath.md)

### 관련 개념

- [Matrix And Affine Transformations](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Phong And Blinn-Phong](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
