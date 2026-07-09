# 03 Raytracing Step8 Shadow

## Chapter purpose

Step8은 Step7에서 만든 closest hit, surface normal, Phong shading 흐름 위에 shadow ray를 추가하는 예제입니다. Camera ray가 처음 만난 표면 지점에서 light 방향으로 보조 ray를 한 번 더 쏘고, 그 경로에 다른 object가 있으면 diffuse/specular를 생략해서 그림자 영역을 표현합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Shadow ray | hit point에서 light 방향으로 쏘는 visibility test ray |
| Shadow bias | 자기 자신과 다시 충돌하는 self-intersection을 피하기 위한 작은 offset |
| Visibility test | light까지 가는 경로가 다른 object에 막히는지 확인하는 과정 |
| Ambient-only shadow | 가려진 지점에서는 ambient term만 남기는 단순 shadow 처리 |
| Two-triangle floor | 바닥 평면을 두 개의 triangle primitive로 구성하는 방식 |

## Core implementation

핵심 구현은 `Raytracer.h`에 있습니다.

| File | Role |
| --- | --- |
| `Raytracer.h` | sphere + two-triangle floor scene, closest hit, shadow ray, Phong shading |
| `Triangle.h` | floor triangle intersection |
| `Sphere.h` | sphere intersection |
| `Object.h` | shared collision interface |
| `Square.h` | 다음 `Shadow_Square` 변형에서 사용할 수 있는 square wrapper |

`IsInShadow()`는 surface point에서 light까지의 구간만 검사합니다. hit point에 normal 방향 bias를 더해 같은 표면을 다시 맞는 self-shadow artifact를 줄입니다.

```cpp
const vec3 dirToLight = glm::normalize(light.pos - hit.point);
const float distanceToLight = glm::length(light.pos - hit.point);
Ray shadowRay{hit.point + hit.normal * 1e-4f, dirToLight};

const auto shadowHit = FindClosestCollision(shadowRay);
return shadowHit.d >= 0.0f && shadowHit.d < distanceToLight;
```

그림자에 들어간 지점은 ambient만 반환하고, 그렇지 않은 지점만 diffuse/specular를 계산합니다.

```cpp
if (IsInShadow(hit))
{
    return hit.obj->amb;
}
```

## Notes handling

- raw source의 학습용 장문 주석은 archive source에서 제거했습니다.
- 원문 메모 성격의 내용은 git에 올리지 않는 `local/Part1_Chapter03/03_Raytracing_Step8_Shadow/` 아래에 분리 대상으로 둡니다.
- raw result/capture/output 이미지는 가져오지 않았습니다.

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

- 다음 작업 후보는 `03_Raytracing_Step8_Shadow_Square` 또는 `03_Raytracing_Step9_BarycentricCordinates`입니다.
