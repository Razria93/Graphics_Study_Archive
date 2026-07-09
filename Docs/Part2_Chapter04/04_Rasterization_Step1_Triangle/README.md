# 04 Rasterization Step1 Triangle

## 목적

CPU에서 삼각형을 rasterize한 뒤, 계산된 pixel buffer를 DirectX11 texture로 업로드해 화면에 표시하는 기본 예제입니다.

## 핵심 키워드

- Orthographic projection
- NDC to raster coordinate mapping
- Bounding box
- Edge function
- Barycentric coordinates
- Color interpolation
- Dynamic texture upload

## 구현 흐름

1. `Rasterization` 객체가 삼각형의 정점 위치와 색상을 초기화합니다.
2. 각 정점을 raster 좌표로 변환합니다.
3. 삼각형을 포함하는 bounding box를 계산합니다.
4. 각 pixel 위치에서 edge function을 사용해 삼각형 내부 여부를 판정합니다.
5. barycentric coordinates로 정점 색상을 보간합니다.
6. CPU pixel buffer를 `D3D11_MAP_WRITE_DISCARD`로 DirectX11 texture에 업로드합니다.
7. fullscreen quad shader가 texture를 sampling해 결과를 표시합니다.

## 핵심 코드

```cpp
const float alpha0 = EdgeFunction(Rast_v1, Rast_v2, point) / area;
const float alpha1 = EdgeFunction(Rast_v2, Rast_v0, point) / area;
const float alpha2 = EdgeFunction(Rast_v0, Rast_v1, point) / area;
```

위 계산은 pixel이 삼각형 내부에 있는지 확인하고, 각 정점 색상을 어느 비율로 섞을지 결정합니다.

```cpp
deviceContext->Map(canvasTexture, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
memcpy(ms.pData, pixels.data(), pixels.size() * sizeof(glm::vec4));
deviceContext->Unmap(canvasTexture, NULL);
```

CPU에서 계산한 rasterization 결과를 GPU texture로 넘기는 부분입니다.

## 구현 메모

- 현재 Step1은 depth buffer가 없으므로 삼각형 하나의 내부 판정과 색상 보간에 집중합니다.
- projection은 perspective가 아니라 orthographic에 가까운 단순 mapping입니다.
- source의 장문 학습 메모는 `local/Part2_Chapter04/04_Rasterization_Step1_Triangle/source-comments.md`에 분리했습니다.

## 실행 결과

- Build/run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive용 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 외부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
