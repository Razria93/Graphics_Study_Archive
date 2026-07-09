# 04 Rasterization Step8 PerspectiveProjection

## 목적

software rasterizer에서 orthographic projection과 perspective projection의 차이를 비교하고, 원근 투영 후 UV가 왜곡되는 이유와 perspective-correct interpolation의 필요성을 확인하는 예제입니다.

## 핵심 키워드

- Orthographic projection
- Perspective projection
- Eye-to-screen distance
- Depth
- Barycentric interpolation
- Perspective-correct interpolation
- UV interpolation

## 구현 흐름

1. 두 square를 생성하고 같은 X축 회전을 적용합니다.
2. 각 square의 z 위치를 ImGui slider로 조절할 수 있게 합니다.
3. `ProjectWorldToRaster()`에서 `usePerspectiveProjection`이 꺼져 있으면 x/y를 그대로 투영합니다.
4. `usePerspectiveProjection`이 켜져 있으면 `distEyeToScreen / (distEyeToScreen + z)` 비율로 x/y를 축소합니다.
5. triangle 내부의 color, UV, depth는 barycentric weight로 보간합니다.
6. perspective projection과 perspective-correct interpolation이 모두 켜져 있으면 `w / z` 기반으로 보간 weight를 보정합니다.
7. ImGui checkbox와 slider로 정투영/원근투영/원근 보정 보간의 차이를 실행 중 비교합니다.

## 핵심 코드

```cpp
if (this->usePerspectiveProjection) {
    const float ratio = distEyeToScreen / (distEyeToScreen + pointWorld.z);
    pointProjected = vec2(ratio * pointWorld.x, ratio * pointWorld.y);
}
```

z가 커질수록 projection ratio가 작아져 화면상의 x/y 크기가 줄어듭니다. 이것이 가까운 물체가 크게, 먼 물체가 작게 보이는 원근감의 기본입니다.

```cpp
const float ratio0 = w0 / z0;
const float ratio1 = w1 / z1;
const float ratio2 = w2 / z2;
const float ratioTotal = ratio0 + ratio1 + ratio2;

w0 = ratio0 / ratioTotal;
w1 = ratio1 / ratioTotal;
w2 = ratio2 / ratioTotal;
```

화면 공간에서 구한 barycentric weight를 그대로 UV에 쓰면 perspective projection에서 텍스처가 선형으로 늘어지는 문제가 생깁니다. `1/z` 계열 보정을 거쳐 weight를 다시 정규화하면 원근에 맞는 보간으로 가까워집니다.

```cpp
ImGui::Checkbox("usePerspectiveProjection",
                &example->rasterization.usePerspectiveProjection);
ImGui::Checkbox("usePerspectiveCorrectInterpolation",
                &example->rasterization.usePerspectiveCorrectInterpolation);
```

실행 중 projection과 interpolation 보정 여부를 토글해 차이를 확인합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/source-comments.md`로 분리했습니다.
- Step7의 archive 정리 흐름을 이어 받아 `scale`, `rotationX`, `rotationZ`, `translation`을 vertex shader transform에 모두 반영했습니다.
- raw의 핵심 UI인 projection toggle, perspective-correct interpolation toggle, `distEyeToScreen`, square z sliders는 유지했습니다.
- depth buffer 초기값은 원근 투영 예제의 z 범위를 고려해 `10.0f`로 유지했습니다.

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
