# Chapter05 Step3 DirectXMath

이 예제는 Step1에서 확인한 affine transformation을 DirectXMath의 SIMD 연산형과 저장형으로 다시 구성한다. Native DirectXMath와 SimpleMath wrapper의 translation 결과를 비교해 다음 graphics 예제로 이어지는 math library 전환 지점을 설명한다.

## 실행 진입점

- Solution: `05_AffineTransformations_Step3_DirectXMath.sln`
- Project type: Console application
- Entry point: `main.cpp`
- External dependency: Windows SDK DirectXMath와 DirectXTK SimpleMath headers

## Code Map

| 범위 | 책임 |
| --- | --- |
| [SIMD load와 길이 계산](main.cpp#L37-L44) | `XMFLOAT4` 저장형을 `XMVECTOR`로 load하고 XYZ 길이를 scalar로 store |
| [DirectXMath translation matrix](main.cpp#L46-L51) | `XMMATRIX` 연산형을 `XMFLOAT4X4` 저장형으로 변환해 배치 확인 |
| [Point와 direction 변환](main.cpp#L53-L63) | `TransformCoord`와 `TransformNormal`의 semantic 차이 비교 |
| [SimpleMath translation](main.cpp#L65-L81) | `Vector4`의 `w=1/0`에 따른 translation 적용 차이 확인 |
| [Translation component reset](main.cpp#L83-L89) | SimpleMath translation property를 0으로 바꿔 identity 확인 |

## 구현 요약

DirectXMath는 `XMFLOAT` 계열을 memory storage에 두고, `XMLoad`로 `XMVECTOR`나 `XMMATRIX` 연산형에 올린 뒤 `XMStore`로 결과를 회수한다. 이 예제의 `XMVector3Length()`는 XYZ만 사용해 `(1, 2, 3)`의 길이 `3.74166`을 출력한다.

Native API에서는 point에 `XMVector3TransformCoord()`, direction에 `XMVector3TransformNormal()`을 사용한다. Affine translation에서 point는 `(5, 7, 9, 1)`로 이동하고 direction은 `(4, 5, 6, 0)`을 유지한다. `TransformNormal()`은 inverse transpose를 자동으로 만들지 않으므로 non-uniform scale의 surface normal 처리로 일반화하지 않는다.

SimpleMath 비교에서는 같은 translation matrix에 `w=1` point와 `w=0` direction을 전달한다. Native API와 동일한 결과를 얻은 뒤 translation component를 0으로 바꿔 identity matrix를 출력한다. 일반 원리는 [Matrix And Affine Transformations](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md), 실제 출력 해석은 [Step3 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_DirectXMath.md), build/run 사실은 [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, exit code 0 |
| Debug/Release stdout | 일치 | 각 24줄의 결정적 console 출력 |
| Capture/Result | 제외 | 화면 변화가 없는 math API 확인 예제 |

## Capture/Result

이 예제는 interactive graphics output이 없는 console 프로그램이다. Screenshot이나 video보다 실제 stdout과 source link가 구현을 더 정확하게 설명하므로 capture 대상에서 제외한다. Chapter 최소 visual은 Step2 Lights(GLM)에서 유지한다.

## 구현 범위와 한계

- Vector length와 translation만 다루며 rotation, scale, inverse와 projection은 포함하지 않는다.
- `XMVector3TransformNormal()`은 translation을 제외하지만 inverse-transpose matrix를 자동으로 계산하지 않는다.
- Native DirectXMath와 SimpleMath의 일부 API만 비교하며 성능을 측정하지 않는다.
- DirectXTK SimpleMath include는 개발 환경 integration에 의존한다.
- Windows SDK와 DirectXMath SIMD 지원 환경을 전제로 한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Step2 Lights(GLM)](../05_AffineTransformations_Step2_Lights%28GLM%29/README.md)
- 다음 단계: Step4 Lights(SimpleMath) 문서화 대기
- [Matrix And Affine Transformations Topic](../../Docs/01_Topics/Rasterization/MatrixAndAffineTransformations.md)
- [Step3 DirectXMath 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/05_DirectXMath.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
