# Chapter05 Step3 DirectXMath Demo

## 목적

Step3은 Step1의 affine transformation 개념을 DirectXMath의 storage type과 SIMD 연산형으로 옮긴다. Native DirectXMath와 SimpleMath wrapper가 point와 direction의 translation 의미를 표현하는 방식을 결정적 console 출력으로 비교한다.

## 책임 범위

- `XMFLOAT4`와 `XMVECTOR` 사이의 load·compute·store 흐름을 설명한다.
- DirectXMath translation matrix의 저장 결과와 row-vector convention을 설명한다.
- Native semantic transform API와 SimpleMath homogeneous `w`의 차이를 설명한다.
- 일반 matrix 이론은 [Matrix And Affine Transformations](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

| 확인 항목 | 대표 결과 |
| --- | --- |
| XYZ length | `(1, 2, 3)`에서 `3.74166` |
| DirectXMath translation storage | 마지막 row에 `(1, 2, 3, 1)` 출력 |
| Point transform | `(4, 5, 6, 1)`에서 `(5, 7, 9, 1)` |
| Direction transform | `(4, 5, 6, 0)` 유지 |
| SimpleMath reset | Translation component 제거 후 identity 출력 |

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | 코드에 선언한 vector, point, direction과 translation `(1, 2, 3)` |
| Native 연산 | `XMLoad`, `XMVector3Length`, `XMMatrixTranslation`, semantic transform API |
| Wrapper 연산 | SimpleMath `Matrix`, `Vector4::Transform`, translation property setter |
| 출력 | Debug와 Release에서 일치하는 24줄 console text |
| 시각 자료 | Interactive graphics가 없어 screenshot과 video 제외 |

## 구현 흐름

1. `XMFLOAT4`를 `XMVECTOR`에 load하고 XYZ 길이를 scalar로 store한다.
2. Native DirectXMath translation matrix를 저장형에 옮겨 출력한다.
3. Point에는 `TransformCoord`, direction에는 `TransformNormal`을 적용한다.
4. SimpleMath translation matrix에 `w=1` point와 `w=0` direction을 적용한다.
5. Translation component를 0으로 바꿔 identity matrix를 확인한다.

## 핵심 구현

### DirectXMath Load And Semantic Transform

DirectXMath는 memory에 둘 저장형과 SIMD 계산에 사용할 연산형을 구분한다. `XMVector3Length()`는 XYZ 길이를 계산하고, translation에서는 함수 선택으로 point와 direction 의미를 구분한다. `TransformCoord()`는 coordinate transform과 homogeneous divide를 수행하고 `TransformNormal()`은 translation을 제외한 선형 부분을 적용한다.

#### Native DirectXMath 의사코드

```cpp
// Pseudo C++: storage와 SIMD 연산형을 오가는 semantic transform
StorageVector source = StorageVector(1, 2, 3, 1);
SimdVector value = Load(source);
float length = StoreScalar(Length3(value));

Matrix translation = Translation(1, 2, 3);
Vector point = TransformCoord(Vector(4, 5, 6), translation);
Vector direction = TransformNormal(Vector(4, 5, 6), translation);

Print(length, translation, point, direction);
```

- [SIMD load·길이 계산과 translation 저장](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/main.cpp#L37-L51)
- [DirectXMath point·direction semantic transform](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/main.cpp#L53-L63)

### SimpleMath Homogeneous Transform

SimpleMath `Vector4::Transform()`은 point와 direction에 같은 API를 사용한다. 이 경로에서는 vector의 `w=1`과 `w=0`이 translation 적용 여부를 직접 구분한다. Translation property를 0으로 바꾸면 나머지 component가 identity인 현재 matrix도 identity가 된다.

#### SimpleMath Translation 의사코드

```cpp
// Pseudo C++: homogeneous w와 translation component reset
Matrix translation = CreateTranslation(1, 2, 3);
Vector4 point = Vector4(4, 5, 6, 1);
Vector4 direction = Vector4(4, 5, 6, 0);

point = Transform(point, translation);
direction = Transform(direction, translation);
translation.SetTranslation(Vector3(0, 0, 0));

Print(point, direction, translation);
```

- [SimpleMath homogeneous translation과 reset](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/main.cpp#L65-L89)

## 시각 결과

이 예제의 결과는 입력에 따라 항상 같은 console text다. Screenshot은 source와 stdout보다 정보 밀도가 낮고 video는 시간 변화를 설명하지 못하므로 둘 다 제외한다. Chapter 최소 visual은 Step2 Lights(GLM)의 기본·조정 screenshot을 유지한다.

## 구현 범위와 한계

- DirectXMath의 vector length와 translation API만 다룬다.
- `TransformNormal()`은 inverse-transpose matrix를 자동으로 계산하지 않는다.
- Non-uniform scale의 surface normal correctness는 이 console 출력으로 검증하지 않는다.
- DirectXMath와 GLM은 서로 다른 vector convention을 사용하므로 행렬 배치를 그대로 비교하지 않는다.
- Rotation, scale, camera, projection, rasterization과 shader는 포함하지 않는다.
- DirectXTK SimpleMath include는 개발 환경 integration에 의존한다.

## 검증

- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-02 현재 확인, exit code 0
- Release x64 build/run: 성공, 2026-08-02 현재 확인, exit code 0
- Debug/Release stdout: 각 24줄, 내용 일치
- Capture: 결정적 console 예제로 제외

## 관련 코드

- [CPU support 확인과 출력 helper](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/main.cpp#L7-L35)
- [Native DirectXMath 연산](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/main.cpp#L37-L63)
- [SimpleMath wrapper 비교](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/main.cpp#L65-L89)

## 관련 문서

- [Step3 DirectXMath Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/README.md)
- [이전 단계: Step2 Lights(GLM) Demo](05_LightsGLM.md)
- [다음 단계: Step4 Lights(SimpleMath) Demo](05_LightsSimpleMath.md)
- [Matrix And Affine Transformations Topic](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
