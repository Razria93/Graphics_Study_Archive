# 04 Rasterization Step2 Circle

## 목적

원형에 가까운 도형을 indexed triangle list로 구성하고, 각 삼각형을 CPU rasterizer로 그리는 예제입니다.

## 핵심 키워드

- Indexed triangle list
- Vertex buffer concept
- Index buffer concept
- Circle approximation
- Orthographic projection
- Edge function
- Barycentric coordinates

## 구현 흐름

1. 중심 vertex를 먼저 추가합니다.
2. 원 둘레를 일정 각도로 나누어 outer ring vertices를 만듭니다.
3. `indices`에 중심점과 인접한 둘레 vertex를 묶어 삼각형 목록을 구성합니다.
4. `Render()`에서 `indices`를 3개씩 읽어 `DrawIndexedTriangle()`을 호출합니다.
5. 각 삼각형은 bounding box, edge function, barycentric interpolation을 사용해 pixel buffer에 그려집니다.
6. CPU pixel buffer를 DirectX11 texture로 업로드해 화면에 표시합니다.

## 핵심 코드

```cpp
this->indices.push_back(indice_0);
this->indices.push_back(indice_1);
this->indices.push_back(indice_2);
```

삼각형 하나를 세 개의 index로 표현합니다.

```cpp
for (size_t i = 0; i < this->indices.size(); i += 3)
{
    DrawIndexedTriangle(i, pixels);
}
```

index 세 개를 한 묶음으로 읽어 삼각형을 그립니다.

## 구현 메모

- `TriangleToCircle`이 triangle fan 구조를 직접 저장했다면, Step2는 vertex/color/index 배열을 분리해 indexed draw 흐름을 보여줍니다.
- 현재 `numTriangles`는 3으로 고정되어 있어 원 근사보다는 indexed triangle list 구조 학습에 초점이 있습니다.
- source의 장문 학습 메모는 `local/Part2_Chapter04/04_Rasterization_Step2_Circle/source-comments.md`에 분리했습니다.

## 실행 결과

- Build/run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive용 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 외부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../../ImportHistory/Manifests/Part2_Chapter04.md)
