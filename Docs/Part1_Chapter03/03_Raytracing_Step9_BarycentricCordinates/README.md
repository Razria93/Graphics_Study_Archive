# 03 Raytracing Step9 BarycentricCordinates

## Chapter purpose

Step9는 ray-triangle intersection에서 얻은 hit point가 triangle 내부에서 각 vertex에 얼마나 가까운지를 barycentric coordinate로 표현하고, 그 weight를 이용해 vertex color를 보간하는 예제입니다. 이후 texturing 단계에서 UV 좌표를 보간하는 기반이 됩니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Barycentric coordinate | triangle 내부의 한 점을 세 vertex의 가중치 합으로 표현하는 좌표 |
| Interpolation | vertex 속성을 surface point 위치에 맞춰 섞는 과정 |
| Area ratio | 작은 triangle 면적 비율로 barycentric weight를 계산하는 방식 |
| Vertex color | 각 vertex에 지정한 색을 barycentric weight로 보간한 색 |
| Attribute interpolation | color, UV, normal 같은 vertex attribute를 pixel/hit point로 전달하는 기초 |

## Core implementation

핵심 구현은 `Triangle.h`, `Hit.h`, `Raytracer.h`에 있습니다.

| File | Role |
| --- | --- |
| `Hit.h` | hit point의 `barycentric` weight 저장 |
| `Triangle.h` | ray-triangle hit 후 area ratio로 barycentric coordinate 계산 |
| `Raytracer.h` | triangle hit일 때 vertex color interpolation 적용 |
| `Square.h` | 다음 texturing 단계의 UV 확장을 위해 triangle UV 생성자 유지 |

`Triangle::IntersectRayTriangle()`은 hit point를 기준으로 세 개의 작은 triangle 면적을 구하고, 전체 triangle 면적으로 나누어 weight를 만듭니다.

```cpp
const float totalArea = glm::length(glm::cross(v1 - v0, v2 - v0));
const float w0 = glm::length(glm::cross(v1 - point, v2 - point)) / totalArea;
const float w1 = glm::length(glm::cross(v2 - point, v0 - point)) / totalArea;
const float w2 = 1.0f - w0 - w1;
```

`Raytracer::InterpolateVertexColor()`는 이 weight를 vertex color에 곱해서 surface color를 만듭니다.

```cpp
return color0 * hit.barycentric.x + color1 * hit.barycentric.y + color2 * hit.barycentric.z;
```

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 다음 후보는 `03_Raytracing_Step11_Supersampling`입니다.
- `Step10 Texturing`은 texture asset 검토가 필요하므로 별도 asset review 후 진행합니다.
