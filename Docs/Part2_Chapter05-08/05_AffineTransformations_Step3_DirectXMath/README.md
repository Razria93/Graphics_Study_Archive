# 05 AffineTransformations Step3 DirectXMath

## 목적

DirectXMath와 DirectXTK SimpleMath의 벡터/행렬 사용 방식을 확인하는 콘솔 예제입니다. Step1의 GLM matrix 실험과 대응되며, DirectX 계열에서 `XMVECTOR`, `XMFLOAT4`, `XMMATRIX`, `SimpleMath::Matrix`를 어떤 용도로 쓰는지 정리합니다.

## 핵심 키워드

- DirectXMath
- DirectXTK SimpleMath
- XMVECTOR
- XMFLOAT4
- XMMATRIX
- XMStore / XMLoad
- TransformCoord
- TransformNormal

## 구현 흐름

1. `XMVerifyCPUSupport()`로 DirectXMath 사용 가능 여부를 확인합니다.
2. 저장용 타입 `XMFLOAT4`를 `XMLoadFloat4()`로 연산용 `XMVECTOR`에 올립니다.
3. `XMVector3Length()`로 SIMD vector 연산 결과를 확인합니다.
4. `XMMatrixTranslation()`으로 translation matrix를 만들고 `XMFLOAT4X4`에 저장해 출력합니다.
5. point는 `XMVector3TransformCoord()`, direction은 `XMVector3TransformNormal()`로 변환해 차이를 확인합니다.
6. 같은 translation 흐름을 `DirectX::SimpleMath` API로 다시 확인합니다.

## 핵심 코드

```cpp
XMStoreFloat4(&point,
              XMVector3TransformCoord(XMLoadFloat4(&point), translation));
XMStoreFloat4(&direction,
              XMVector3TransformNormal(XMLoadFloat4(&direction), translation));
```

`TransformCoord()`는 위치 좌표처럼 translation을 적용하고, `TransformNormal()`은 방향 벡터처럼 translation을 무시합니다.

```cpp
XMVECTOR simdVector = XMLoadFloat4(&sourceVector);
simdVector = XMVector3Length(simdVector);
XMStoreFloat(&length, simdVector);
```

DirectXMath에서는 저장용 타입과 연산용 SIMD 타입을 구분합니다. 일반적으로 멤버 저장에는 `XMFLOAT*`, 계산에는 `XMVECTOR`/`XMMATRIX`를 사용합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 출력 결과 예시는 source에서 제거하고 `local/Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/source-comments.md`로 분리했습니다.
- `.clang-format`, `.vcxproj.user`, `.vs/`, `x64/`는 archive에 포함하지 않았습니다.
- project file에서 `.clang-format` 참조를 제거했습니다.
- dependency는 DirectXMath와 vcpkg `directxtk:x64-windows`입니다.
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
