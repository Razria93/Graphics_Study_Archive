# 04 Rasterization Step5 DepthBuffer

## 목적

겹쳐 그려지는 rasterized primitives에 대해, 픽셀별 depth 값을 비교해 더 가까운 fragment만 남기는 depth buffer 예제입니다.

## 핵심 키워드

- Depth buffer
- Z-buffer test
- Barycentric interpolation
- Orthographic projection
- Fragment visibility
- Draw order independence
- ImGui z-position controls

## 구현 흐름

1. 세 개의 circle mesh를 만들고 서로 다른 z 위치에 배치합니다.
2. 매 frame마다 `depthBuffer`를 화면 픽셀 수만큼 준비하고 `FLT_MAX`로 초기화합니다.
3. 각 triangle의 bounding box를 돌며 edge function으로 내부 픽셀을 판정합니다.
4. barycentric weight로 color와 depth를 보간합니다.
5. 현재 fragment의 depth가 저장된 depth보다 작으면 color와 depth buffer를 함께 갱신합니다.
6. ImGui slider로 각 circle의 z값을 바꾸며 depth ordering 변화를 확인합니다.

## 핵심 코드

```cpp
this->depthBuffer.resize(pixels.size());
std::fill(depthBuffer.begin(), depthBuffer.end(), FLT_MAX);
```

매 frame depth buffer를 가장 먼 값으로 초기화합니다.

```cpp
const float depth =
    (alpha0 * this->vertexBuffer[i0].z +
     alpha1 * this->vertexBuffer[i1].z +
     alpha2 * this->vertexBuffer[i2].z) /
    area;

const size_t pixelIndex = i + width * j;
if (depth >= 0.0f && depth < depthBuffer[pixelIndex]) {
    depthBuffer[pixelIndex] = depth;
    pixels[pixelIndex] = vec4(color, 1.0f);
}
```

현재 fragment가 기존에 저장된 fragment보다 가까울 때만 color buffer를 갱신합니다. 이 예제는 orthographic projection 흐름이므로 z값을 barycentric weight로 직접 보간해 depth test에 사용합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/source-comments.md`에 분리했습니다.
- `FLT_MAX` 사용이 명확하도록 `Rasterization.cpp`에 `<cfloat>` include를 추가했습니다.
- 실행 중 z값을 바꿔 depth test 결과를 확인할 수 있도록 ImGui slider를 유지했습니다.

## 실행 결과

- Build/run status: 성공
- 확인 내용: MSBuild Debug x64, Release x64 성공. 사용자 Debug/Release 실행 확인 완료
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 내부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
