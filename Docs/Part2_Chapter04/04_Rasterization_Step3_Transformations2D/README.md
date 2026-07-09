# 04 Rasterization Step3 Transformations2D

## 목적

CPU에서 mesh vertex buffer에 2D transformation을 적용한 뒤, 변환된 geometry를 rasterize하는 예제입니다.

## 핵심 키워드

- Mesh
- Vertex buffer copy
- 2D translation
- 2D rotation
- Non-uniform scale
- Transform order
- CPU-side vertex transformation
- ImGui transform controls

## 구현 흐름

1. `Mesh::InitCircle()`이 원형 mesh의 원본 `vertices`, `colors`, `indices`를 생성합니다.
2. `Rasterization`은 원본 mesh를 `vertexBuffer`, `colorBuffer`, `indexBuffer`로 복사합니다.
3. ImGui slider가 rotation, scale, translation 값을 갱신합니다.
4. `Rasterization::Update()`에서 원본 `circle.vertices`를 기준으로 변환 결과를 새로 계산합니다.
5. 변환된 `vertexBuffer`를 indexed triangle list로 rasterize합니다.
6. CPU pixel buffer를 DirectX11 texture로 업로드해 화면에 표시합니다.

## 핵심 코드

```cpp
temp = RotateAboutZ(circle.vertices[i], this->rotation1);
temp = temp * vec3(scaleX, scaleY, 1.0f);
temp = temp + this->translation1;
temp = RotateAboutZ(temp, this->rotation2);
temp = temp + this->translation2;
```

변환 순서는 결과에 직접 영향을 줍니다. 이 예제는 원본 vertex에서 시작해 회전, 스케일, 이동, 추가 회전, 추가 이동을 순서대로 적용합니다.

```cpp
this->vertexBuffer = circle.vertices;
this->colorBuffer = circle.colors;
this->indexBuffer = circle.indices;
```

원본 mesh를 보존하고, 매 프레임 변환된 vertex buffer만 갱신하기 위한 구조입니다.

## 구현 메모

- `Mesh`는 geometry 데이터를 보관하고, `Rasterization`은 변환 및 rasterization을 담당합니다.
- 현재 변환은 GPU vertex shader가 아니라 CPU에서 수행합니다.
- source의 장문 학습 메모는 `local/Part2_Chapter04/04_Rasterization_Step3_Transformations2D/source-comments.md`에 분리했습니다.

## 실행 결과

- Build/run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive용 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 외부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
