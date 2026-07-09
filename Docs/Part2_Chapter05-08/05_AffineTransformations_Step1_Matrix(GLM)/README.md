# 05 AffineTransformations Step1 Matrix(GLM)

## 목적

GLM의 matrix/vector 표현과 affine transformation의 기본 계산 흐름을 콘솔 출력으로 확인하는 예제입니다. 이후 D3D11 graphics pipeline에서 model/view/projection matrix를 다루기 전에 column-major 저장 방식, point/vector의 `w` 차이, transform composition order를 먼저 확인합니다.

## 핵심 키워드

- GLM
- Column-major matrix
- Matrix transpose
- Matrix multiplication order
- Translation matrix
- Rotation matrix
- Scale matrix
- Point/vector homogeneous coordinate

## 구현 흐름

1. `glm::mat2`, `glm::mat4`를 생성하고 GLM의 column-major 표현을 출력합니다.
2. `transpose`, column access, matrix addition/multiplication 결과를 비교합니다.
3. translation matrix가 `w = 1`인 point에는 이동을 적용하고, `w = 0`인 vector에는 이동을 적용하지 않는 차이를 확인합니다.
4. rotation matrix의 transpose가 inverse와 같은 성질을 출력으로 확인합니다.
5. `translation * rotation`과 `rotation * translation`의 결과 차이를 비교합니다.
6. row-vector 스타일로 해석해야 하는 경우 transpose를 사용해 같은 결과를 얻는 흐름을 확인합니다.

## 핵심 코드

```cpp
Print("translation * point: w = 1 applies translation", translation * point);
Print("translation * vector: w = 0 ignores translation", translation * vector);
```

homogeneous coordinate에서 `w`는 위치와 방향을 구분합니다. point는 translation 영향을 받고, direction vector는 이동 성분을 무시합니다.

```cpp
Print("(translation * rotationX) * point: rotate first, then translate",
      (translation * rotationX) * originOffset);
Print("(rotationX * translation) * point: translate first, then rotate",
      (rotationX * translation) * originOffset);
```

matrix multiplication은 교환법칙이 성립하지 않으므로 transform을 곱하는 순서가 최종 위치를 바꿉니다.

## Archive 반영 메모

- raw source의 장문 출력 결과 주석과 학습 메모는 source에서 제거하고 `local/Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix(GLM)/source-comments.md`로 분리했습니다.
- `.clang-format`, `.vcxproj.user`, `.vs/`, `x64/`는 archive에 포함하지 않았습니다.
- project file에서 `.clang-format` 참조를 제거했습니다.
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
