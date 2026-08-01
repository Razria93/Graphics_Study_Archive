# Chapter05 Step1 Matrix(GLM)

이 예제는 GLM matrix의 column access, 곱셈 순서와 homogeneous coordinate를 console 출력으로 확인한다. Graphics pipeline에 좌표 변환을 적용하기 전에 affine transformation의 수치 관계를 분리해 다룬다.

## 실행 진입점

- Solution: `05_AffineTransformations_Step1_Matrix(GLM).sln`
- Project type: Console application
- Entry point: `main.cpp`
- External dependency: GLM headers

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Matrix 생성과 기본 연산](main.cpp#L22-L39) | Column 단위 초기화, transpose, 덧셈과 곱셈 순서 비교 |
| [Homogeneous translation](main.cpp#L41-L48) | `w=1` point와 `w=0` vector의 translation 차이, inverse 확인 |
| [Rotation과 transform order](main.cpp#L50-L62) | Orthogonal rotation과 `T * R`, `R * T` 적용 순서 비교 |
| [Non-uniform scale](main.cpp#L64-L64) | 축별 scale matrix 확인 |

## 구현 요약

GLM matrix 생성자는 column 단위로 값을 받으며 `matrix[index]`도 column을 반환한다. Matrix multiplication은 교환 법칙이 성립하지 않으므로 `A * B`와 `B * A`가 서로 다른 결과를 만든다.

Translation matrix는 homogeneous coordinate의 `w`를 이용해 point와 direction vector를 구분한다. Column-vector convention에서는 오른쪽 matrix가 먼저 적용되므로 `T * R`과 `R * T`가 서로 다른 위치를 만든다. Rotation matrix의 transpose와 원래 matrix를 곱한 결과는 identity가 되어 orthogonal 관계를 확인할 수 있다.

일반 개념은 [Matrix And Affine Transformations](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md)으로 위임하고, 출력값과 build/run 사실은 [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Debug/Release stdout | 일치 | 각 54줄의 결정적 console 출력 |
| Capture/Result | 제외 | 화면 변화가 없는 수치 확인 예제 |

## Capture/Result

이 예제는 interactive graphics output이 없는 console 프로그램이다. Screenshot이나 video보다 실제 matrix 출력과 source link가 구현을 더 정확하게 설명하므로 capture 대상에서 제외한다. Chapter 최소 visual은 후속 graphics Example에서 확보한다.

## 구현 범위와 한계

- Matrix storage/access와 multiplication convention을 구분해 해석해야 한다.
- Rotation의 transpose가 inverse와 같다는 관계는 orthogonal matrix에 한정된다.
- Non-uniform scale이 결합된 일반 affine matrix의 inverse나 decomposition은 다루지 않는다.
- Camera, projection, shader와 rasterization pipeline은 포함하지 않는다.
- Project가 GLM include path를 직접 선언하지 않아 개발 환경의 GLM 설정에 의존한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [Matrix And Affine Transformations Topic](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Step1 Matrix 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_MatrixGLM.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
