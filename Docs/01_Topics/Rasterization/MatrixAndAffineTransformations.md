# Matrix And Affine Transformations

## 목적

Graphics 좌표 변환에 사용하는 matrix, homogeneous coordinate와 affine transform composition의 공통 원리를 설명한다. 특정 math library의 API보다 storage, vector convention과 적용 순서를 구분해 해석하는 데 초점을 둔다.

## 책임 범위

- Matrix storage/access 방식과 수학적 multiplication convention을 구분한다.
- Point와 direction vector를 구분하는 homogeneous coordinate를 설명한다.
- Translation, rotation과 scale의 조합 순서가 결과에 미치는 영향을 설명한다.
- 2D geometry의 실제 변환 흐름은 [2D Transformations](Transformations2D.md)으로 위임한다.
- GLM API와 실제 출력은 [Step1 Matrix(GLM) Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/README.md)과 [상세 Demo](../../03_Demos/Part2_Chapter05-08/05_MatrixGLM.md)로 위임한다.
- build/run 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- 결과 해석은 `Docs/03_Demos`, 검증 사실은 `Docs/02_Verification` 정본으로 위임한다.

## 핵심 개념

### Storage And Convention

Matrix가 memory에서 row-major 또는 column-major로 저장되는 방식과 vector를 matrix의 왼쪽 또는 오른쪽에 두는 multiplication convention은 별개의 선택이다. GLM은 column 단위 constructor와 index access를 제공하며 일반적인 column-vector 식 `M * v`를 사용한다.

Storage 설명만 보고 transform 적용 순서를 추론하면 안 된다. 실제 식에서 vector가 놓인 위치와 library가 정의한 연산을 함께 확인해야 한다.

### Homogeneous Coordinates

3D affine transform은 4차원 homogeneous coordinate로 translation을 matrix multiplication에 포함한다. Point는 `w=1`이므로 translation column의 영향을 받고, direction vector는 `w=0`이므로 rotation과 scale만 적용된다.

이 구분은 위치와 방향을 같은 `vec4`로 표현할 때 의도를 보존한다. Normal은 non-uniform scale이 포함되면 일반 direction과 동일하게 변환할 수 없으며 inverse transpose가 필요하다.

### Composition And Order

Matrix multiplication은 일반적으로 교환 법칙이 성립하지 않는다. Column-vector convention에서 `T * R * p`는 point에 rotation을 먼저 적용한 뒤 translation을 적용한다. 반대로 `R * T * p`는 translation으로 생긴 offset까지 원점 주위로 회전한다.

복합 transform은 코드를 읽는 순서가 아니라 vector에 가까운 오른쪽 matrix부터 해석한다. 다른 convention으로 옮길 때는 matrix transpose만이 아니라 multiplication order와 vector 방향을 함께 맞춰야 한다.

### Inverse And Orthogonal Rotation

Inverse transform은 적용한 변환을 반대 순서로 되돌린다. Translation의 inverse는 offset의 부호를 반전한다. Orthogonal rotation matrix는 축이 서로 직교하고 길이가 1이므로 transpose가 inverse와 같다.

이 관계는 rotation에 유효하지만 non-uniform scale이나 shear가 섞인 일반 affine matrix에는 그대로 적용할 수 없다. 이런 경우에는 전체 inverse 또는 normal matrix를 별도로 계산해야 한다.

## 한계

- Matrix decomposition, quaternion, camera view/projection과 hierarchy transform은 포함하지 않는다.
- Coordinate handedness와 clip-space 규칙은 graphics API별 문서로 분리한다.
- Floating-point 오차와 singular matrix 판정은 개념 범위에서만 언급한다.
- 특정 GLM 또는 DirectXMath 호출 규약은 연결된 Example 책임으로 둔다.

## 관련 문서

- [Step1 Matrix(GLM) Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/README.md)
- [Step1 Matrix(GLM) Demo](../../03_Demos/Part2_Chapter05-08/05_MatrixGLM.md)
- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [2D Transformations](Transformations2D.md)
- [Rasterization Topic Index](topic-index.md)
