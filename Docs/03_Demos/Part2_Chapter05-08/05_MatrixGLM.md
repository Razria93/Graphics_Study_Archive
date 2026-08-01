# Chapter05 Step1 Matrix(GLM) Demo

## 목적

Step1은 graphics transform에 앞서 GLM matrix의 column access, 곱셈 순서, homogeneous point/vector와 affine composition을 결정적 console 출력으로 확인한다. 같은 matrix라도 적용 순서가 달라지면 결과가 바뀌는 이유를 실제 수치와 연결한다.

## 책임 범위

- Step1에서 직접 출력하는 matrix 연산과 transform order를 설명한다.
- Point의 `w=1`과 vector의 `w=0`이 translation에 미치는 영향을 설명한다.
- Rotation transpose와 orthogonal 관계를 실제 identity 결과로 설명한다.
- 일반 matrix와 affine transformation 이론은 [Matrix And Affine Transformations](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

| 확인 항목 | 대표 결과 |
| --- | --- |
| Matrix order | `A * B`와 `B * A`가 서로 다른 matrix를 출력 |
| Homogeneous translation | Point `(4, 5, 6, 1)`은 `(5, 7, 9, 1)`, vector `(4, 5, 6, 0)`은 불변 |
| Orthogonal rotation | `transpose(Rx) * Rx`가 identity matrix 출력 |
| Transform order | `(T * Rx) * p`와 `(Rx * T) * p`가 서로 다른 위치 출력 |

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | 코드에 선언한 `mat2`, `mat4`, point와 direction vector |
| 연산 | Transpose, addition, multiplication, inverse, translation, X rotation과 scale |
| 출력 | GLM `to_string()`으로 직렬화한 54줄 console text |
| 시각 자료 | Interactive graphics가 없어 screenshot과 video 제외 |

## 구현 흐름

1. 두 `mat2`를 column 단위로 구성하고 access와 기본 연산을 출력한다.
2. Translation matrix를 point와 direction vector에 각각 적용한다.
3. X축 60도 rotation과 transpose product를 출력한다.
4. `T * R`과 `R * T`를 같은 point에 적용해 composition order를 비교한다.
5. Row-vector 식에 transpose를 사용해 같은 결과로 변환한다.
6. Non-uniform scale matrix를 출력한다.

## 핵심 구현

### Matrix Storage And Multiplication

GLM constructor의 연속 값은 column 단위로 배치되고 `A[1]`도 두 번째 column을 반환한다. `A * B`와 `B * A`를 함께 출력해 matrix multiplication의 비가환성을 확인한다.

#### Matrix Order 의사코드

```cpp
// Pseudo C++: column access와 matrix 곱셈 순서 비교
Matrix2 A = Columns(Column(1, 2), Column(3, 4));
Matrix2 B = Columns(Column(5, 6), Column(7, 8));

Print(A.Column(1));
Print(A * B);
Print(B * A);
```

- [Matrix 구성과 곱셈 순서](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/main.cpp#L22-L32)

### Homogeneous Point And Vector

같은 XYZ 값을 가진 두 `vec4`에서 `w`만 다르게 두면 translation 결과가 달라진다. Point는 translation offset이 더해지고 direction vector는 원래 값을 유지한다.

#### Homogeneous Translation 의사코드

```cpp
// Pseudo C++: homogeneous w에 따른 translation 적용
Matrix4 T = Translation(1, 2, 3);
Vector4 point = Vector4(4, 5, 6, 1);
Vector4 direction = Vector4(4, 5, 6, 0);

Print(T * point);
Print(T * direction);
Print(Inverse(T));
```

- [Point·vector translation과 inverse](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/main.cpp#L41-L48)

### Rotation And Transform Order

`transpose(Rx) * Rx`가 identity를 만드는 출력으로 X rotation의 orthogonal 관계를 확인한다. 같은 point에 `T * Rx`와 `Rx * T`를 적용하면 오른쪽 transform이 먼저 적용되어 서로 다른 위치가 나온다.

#### Transform Composition 의사코드

```cpp
// Pseudo C++: rotation의 orthogonal 관계와 composition order 비교
Matrix4 R = RotationX(60Degrees);
Vector4 p = Point(1, 0, 0);

Print(Transpose(R) * R);
Print((T * R) * p);
Print((R * T) * p);
Print(p * Transpose(T * R));
```

- [Rotation transpose와 transform order](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/main.cpp#L50-L62)

## 시각 결과

이 예제의 결과는 정지된 console text이며 parameter 조작이나 frame 변화가 없다. Screenshot은 source와 실제 출력보다 정보 밀도가 낮고 video는 시간 변화를 설명하지 못하므로 둘 다 제외한다. Chapter 최소 visual은 Step2 Lights(GLM)에서 확보한다.

## 구현 범위와 한계

- GLM column access와 column-vector 식을 기준으로 설명한다.
- Code는 inverse translation을 출력하지만 일반 affine inverse와 decomposition은 다루지 않는다.
- Rotation transpose와 inverse의 동일성은 orthogonal rotation에 한정해 해석한다.
- Camera, projection, lighting, rasterization과 shader pipeline은 포함하지 않는다.
- Console 문자열의 소수 표시는 GLM 버전에 따라 달라질 수 있다.

## 검증

- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-02 현재 확인, exit code 0
- Release x64 build/run: 성공, 2026-08-02 현재 확인, exit code 0
- Debug/Release stdout: 각 54줄, 내용 일치
- Capture: 결정적 console 예제로 제외

## 관련 코드

- [Matrix 출력 helper와 entry point](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/main.cpp#L12-L21)
- [Matrix 연산과 non-uniform scale](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/main.cpp#L22-L64)

## 관련 문서

- [Step1 Matrix(GLM) Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/README.md)
- [Matrix And Affine Transformations Topic](../../01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
