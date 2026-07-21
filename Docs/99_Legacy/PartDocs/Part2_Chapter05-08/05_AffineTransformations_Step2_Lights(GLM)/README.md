# 05 AffineTransformations Step2 Lights(GLM)

## 목적

Step1에서 확인한 GLM matrix 표현을 software rasterizer의 vertex transform에 적용하는 예제입니다. Step10 lighting 예제의 directional/point/spot light 흐름은 유지하면서, scale/rotation/translation을 개별 함수가 아니라 `modelMatrix`와 `normalMatrix`로 전달합니다.

## 핵심 키워드

- Model matrix
- Normal matrix
- GLM transform composition
- Column-major matrix
- Blinn-Phong lighting
- Directional light
- Point light
- Spot light

## 구현 흐름

1. mesh의 scale, rotation, translation 값을 GLM transform matrix로 구성합니다.
2. `modelMatrix = translation * rotation * scale` 순서로 object transform을 합성합니다.
3. normal 변환에는 `inverseTranspose(modelMatrix)`를 사용합니다.
4. vertex shader 단계에서 position은 `w = 1`, normal은 `w = 0`으로 matrix를 곱합니다.
5. pixel shader 단계에서는 Step10과 같은 Blinn-Phong lighting 경로를 사용합니다.
6. ImGui에서 material, light type, light strength, direction, position, falloff, spot power를 조절합니다.

## 핵심 코드

```cpp
constants.modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
constants.normalMatrix = glm::inverseTranspose(constants.modelMatrix);
```

non-uniform scale이 들어갈 수 있는 object transform에서는 normal을 position과 같은 matrix로만 변환하면 방향이 왜곡될 수 있습니다. 그래서 normal에는 inverse transpose matrix를 사용합니다.

```cpp
const vec4 point = constants.modelMatrix * vec4(vsInput.position, 1.0f);
const vec4 normal = constants.normalMatrix * vec4(vsInput.normal, 0.0f);
```

position은 위치이므로 translation 영향을 받도록 `w = 1`을 사용하고, normal은 방향이므로 translation을 무시하도록 `w = 0`을 사용합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 matrix transpose 관련 메모는 source에서 제거하고 `local/Part2_Chapter05-08/05_AffineTransformations_Step2_Lights(GLM)/source-comments.md`로 분리했습니다.
- `.clang-format`, `.vcxproj.user`, `.vs/`, `x64/`, `imgui.ini`는 archive에 포함하지 않았습니다.
- 외부 asset은 없습니다.
- source는 Step10 lighting archive 구조를 기반으로 정리하고, Step2의 GLM matrix transform 차이를 반영했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: Debug x64, Release x64 성공
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 source 주석, 문서, dependency 설명, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
