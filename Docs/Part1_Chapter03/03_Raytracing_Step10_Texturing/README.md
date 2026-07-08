# 03 Raytracing Step10 Texturing

## Chapter purpose

Step10은 Step9의 barycentric interpolation을 UV interpolation으로 확장하고, texture image에서 sampling한 색을 surface shading에 적용하는 예제입니다. 각 vertex에 UV coordinate를 지정하고, hit point에서 보간된 UV로 texture color를 읽어 diffuse term에 곱합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Texture coordinate | texture image의 위치를 정규화된 `(u, v)` 값으로 표현한 좌표 |
| Texel | texture image 안의 pixel 단위 |
| UV interpolation | triangle hit point의 barycentric weight로 vertex UV를 보간하는 과정 |
| Point sampling | 가장 가까운 texel 하나를 읽는 sampling 방식 |
| Linear sampling | 주변 texel을 bilinear interpolation으로 섞어 읽는 방식 |
| Wrap / Clamp | texture 범위 밖 UV를 처리하는 방식 |

## Core implementation

핵심 구현은 `Texture.h/.cpp`, `Triangle.h`, `Square.h`, `Raytracer.h`에 있습니다.

| File | Role |
| --- | --- |
| `Texture.h`, `Texture.cpp` | image load, point/linear sampling, wrap/clamp |
| `Hit.h` | hit point에서 보간된 `uv` 저장 |
| `Triangle.h` | barycentric weight로 vertex UV interpolation |
| `Square.h` | 4개 vertex/UV를 두 triangle에 전달 |
| `Raytracer.h` | `shadertoy_abstract1.jpg` texture를 square diffuse term에 적용 |

`Triangle::CheckRayCollision()`은 hit point의 barycentric coordinate로 UV를 보간합니다.

```cpp
hit.uv = uv0 * barycentric.x + uv1 * barycentric.y + uv2 * barycentric.z;
```

`Texture::SampleLinear()`는 UV를 image 좌표로 변환하고, 네 주변 texel을 bilinear interpolation으로 섞습니다.

```cpp
const vec2 xy = uv * vec2(width, height) - vec2(0.5f);
return InterpolateBilinear(dx, dy, c00, c10, c01, c11);
```

## Asset handling

| Asset | Status | Note |
| --- | --- | --- |
| `shadertoy_abstract1.jpg` | private archive 반영 | 강의용으로 제공된 open-source 성격의 입력 texture로 판단 |

이 asset은 Step10 실행에 필요한 입력 자료이므로 private archive에 포함합니다. 다만 public repo로 공개하기 전에는 출처/라이선스 표기 가능 여부를 별도로 확인합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Required texture asset | 포함 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 사용자가 Debug/Release 실행 화면을 확인하면 run status를 성공으로 갱신합니다.
- 다음 코드 후보는 `03_Raytracing_Step11_Supersampling`입니다.
