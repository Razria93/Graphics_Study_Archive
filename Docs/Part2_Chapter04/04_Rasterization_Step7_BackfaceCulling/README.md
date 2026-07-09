# 04 Rasterization Step7 BackfaceCulling

## 목적

software rasterizer에서 triangle winding을 이용해 back-facing triangle을 제외하는 흐름을 확인하는 예제입니다. 두 개의 square를 나란히 배치하고, 한쪽은 X축으로 뒤집어 같은 geometry라도 정점 순서가 화면에서 어떻게 달라지는지 비교합니다.

## 핵심 키워드

- Backface culling
- Triangle winding
- Front face / back face
- Edge function signed area
- Barycentric interpolation
- UV based pixel shader
- ImGui runtime toggle

## 구현 흐름

1. `Mesh::InitSquare_Normalized()`가 normalized square geometry와 UV를 생성합니다.
2. `Rasterization` 생성자에서 두 square를 만들고, 두 번째 square는 `rotationX = pi`로 뒤집습니다.
3. `MyVertexShader()`가 mesh별 `scale`, `rotationX`, `rotationZ`, `translation`을 적용합니다.
4. `DrawIndexedTriangle()`이 raster 좌표에서 triangle area를 계산합니다.
5. `cullBackface`가 켜져 있고 signed area가 뒤쪽 방향이면 해당 triangle을 그리지 않습니다.
6. 남은 triangle만 barycentric weight로 color, UV, depth를 보간하고 pixel shader 결과를 기록합니다.
7. ImGui checkbox로 `cullBackface`를 실행 중 on/off 하며 결과를 비교합니다.

## 핵심 코드

```cpp
const float area = EdgeFunction(v0, v1, v2);
if (area == 0.0f || (cullBackface && area <= 0.0f)) {
    return;
}
```

이 예제는 `FrontCounterClockwise = false`, 즉 clockwise를 front face로 보는 전제를 둡니다. 따라서 raster 좌표에서 계산한 signed area가 back-facing으로 판단되면 triangle 단위로 조기에 제외합니다.

```cpp
float alpha0 = EdgeFunction(v1, v2, point) / area;
float alpha1 = EdgeFunction(v2, v0, point) / area;
float alpha2 = EdgeFunction(v0, v1, point) / area;
```

triangle 내부 픽셀 후보는 normalized barycentric weight로 색, UV, depth를 보간합니다.

```cpp
ImGui::Checkbox("cullBackface", &example->rasterization.cullBackface);
```

실행 중 culling 여부를 바꿔 두 square의 차이를 확인합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling/source-comments.md`로 분리했습니다.
- raw 흐름의 핵심인 `cullBackface`, X축 회전 square, UV checker pixel shader는 유지했습니다.
- archive source에서는 `scale`, `rotationX`, `rotationZ`, `translation`이 모두 vertex shader transform에 적용되도록 정리했습니다.
- raw의 Step7 depth 계산은 이미 normalized된 barycentric weight를 다시 `area`로 나누는 형태였으므로, archive에서는 `alpha0*z0 + alpha1*z1 + alpha2*z2` 형태로 정리했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 강의 기반 구조, 주석, 문서, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
