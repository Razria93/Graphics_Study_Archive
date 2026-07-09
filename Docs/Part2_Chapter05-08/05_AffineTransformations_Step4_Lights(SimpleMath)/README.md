# 05 AffineTransformations Step4 Lights(SimpleMath)

## 목적

Step2의 GLM 기반 lighting 예제를 DirectXTK SimpleMath 타입과 API로 옮긴 예제입니다. `Vector3`, `Vector4`, `Matrix`를 사용해 model matrix와 inverse-transpose normal matrix를 만들고, software rasterizer의 vertex/pixel shader 흐름에 적용합니다.

## 핵심 키워드

- DirectXTK SimpleMath
- Matrix::CreateScale
- Matrix::CreateRotationX/Y/Z
- Matrix::CreateTranslation
- Model matrix
- Inverse transpose normal matrix
- Blinn-Phong lighting

## 구현 흐름

1. mesh transform을 SimpleMath `Matrix` API로 구성합니다.
2. `scale * rotation * translation` 순서로 model matrix를 합성합니다.
3. normal 변환에는 translation을 제거한 뒤 inverse transpose matrix를 사용합니다.
4. vertex shader 단계에서 position은 `w = 1`, normal은 `w = 0`으로 변환합니다.
5. pixel shader 단계에서 directional/point/spot light 중 선택된 경로로 Blinn-Phong lighting을 계산합니다.
6. ImGui에서 object transform, material, light type, light parameters를 조절합니다.

## 핵심 코드

```cpp
Matrix scale = Matrix::CreateScale(object->transformation.scale);
Matrix rotation = Matrix::CreateRotationX(object->transformation.rotationX) *
                  Matrix::CreateRotationY(object->transformation.rotationY) *
                  Matrix::CreateRotationZ(object->transformation.rotationZ);
Matrix translation = Matrix::CreateTranslation(object->transformation.translation);
```

SimpleMath는 DirectXMath보다 읽기 쉬운 wrapper API를 제공합니다. 이 예제에서는 GLM helper 함수 대신 SimpleMath의 static factory를 사용해 transform matrix를 구성합니다.

```cpp
transMatrix.Translation(Vector3(0.0f));
transMatrix.Invert().Transpose();
constants.invTranspose = transMatrix;
```

normal matrix는 translation 성분을 제거한 뒤 inverse transpose를 적용합니다. non-uniform scale이 들어갈 때 normal 방향을 안정적으로 유지하기 위한 단계입니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 SimpleMath 전환 메모는 source에서 제거하고 `local/Part2_Chapter05-08/05_AffineTransformations_Step4_Lights(SimpleMath)/source-comments.md`로 분리했습니다.
- `.clang-format`, `.vcxproj.user`, `.vs/`, `x64/`, `imgui.ini`는 archive에 포함하지 않았습니다.
- raw의 specular 계산에서 쉼표 연산자로 인해 `pow(0, shininess)`가 되는 표현을 `max(dot, 0)` 형태로 수정했습니다.
- 외부 asset은 없습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 source 주석, 문서, dependency 설명, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
