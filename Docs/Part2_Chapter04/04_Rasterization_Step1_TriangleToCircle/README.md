# 04 Rasterization Step1 TriangleToCircle

## 목적

Step1의 단일 삼각형 rasterization을 확장해, 여러 삼각형을 부채꼴로 배치하여 원에 가까운 형태를 만드는 예제입니다.

## 핵심 키워드

- Triangle fan
- Circle approximation
- Segment count
- Edge function
- Barycentric coordinates
- ImGui slider control
- Dynamic texture upload

## 구현 흐름

1. ImGui slider에서 `New_triangleNums` 값을 조절합니다.
2. 삼각형 개수가 바뀌면 `SetTriangleCount()`가 원을 구성할 triangle fan을 다시 생성합니다.
3. 각 삼각형은 중심점과 원 둘레의 인접한 두 점으로 구성됩니다.
4. 각 삼각형을 Step1과 같은 edge function / barycentric interpolation 방식으로 rasterize합니다.
5. CPU pixel buffer를 DirectX11 texture로 업로드해 화면에 표시합니다.

## 핵심 코드

```cpp
triangle.v0.pos = vec3(0.0f, 0.0f, 0.0f);
triangle.v1.pos = vec3(radius * glm::cos((2.0f * PI / triangleNums) * i),
                       radius * glm::sin((2.0f * PI / triangleNums) * i), 0.0f);
triangle.v2.pos = vec3(radius * glm::cos((2.0f * PI / triangleNums) * (i + 1)),
                       radius * glm::sin((2.0f * PI / triangleNums) * (i + 1)), 0.0f);
```

원 둘레를 일정 각도로 나누고, 중심점과 두 둘레 점을 묶어 삼각형 하나를 만듭니다. 삼각형 수가 늘어날수록 원에 가까워집니다.

```cpp
ImGui::SliderInt("Triangles Number", &example->rasterization.New_triangleNums, 3, 100);
```

실행 중 segment count를 바꾸는 조작부입니다.

## 구현 메모

- Step1의 단일 삼각형 내부 판정과 색상 보간 로직을 재사용합니다.
- 차이는 삼각형 하나가 아니라 `circle.triangles`에 저장된 여러 삼각형을 반복해서 그린다는 점입니다.
- `triangleNums`와 `New_triangleNums`를 비교해 값이 바뀐 경우에만 triangle fan을 재생성합니다.
- source의 장문 학습 메모는 `local/Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/source-comments.md`에 분리했습니다.

## 실행 결과

- Build/run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive용 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 외부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
