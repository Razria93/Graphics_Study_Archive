# 03 Raytracing Step6 PerspectiveView

## Chapter purpose

Step6는 Step5의 Phong shaded sphere 렌더링을 여러 object scene으로 확장하고, orthographic ray 대신 perspective ray를 사용해 깊이에 따른 크기 차이를 보여주는 예제입니다. 각 pixel의 world position과 eye position을 이용해 ray direction을 만들고, 여러 object 중 가장 가까운 hit를 찾아 색을 계산합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Perspective ray | eye position에서 screen pixel을 향해 나가는 ray |
| Orthographic ray | 모든 pixel에서 같은 방향으로 나가는 parallel ray |
| Eye position | perspective ray의 기준이 되는 camera 위치 |
| Closest hit | 여러 object와의 intersection 중 가장 작은 positive distance |
| Object abstraction | sphere 외 object가 같은 collision interface를 갖도록 분리한 base class |
| Depth ordering | 그리기 순서가 아니라 ray hit distance로 앞 object를 결정하는 방식 |

## Core implementation

핵심 구현은 다음 파일에 있습니다.

| File | Role |
| --- | --- |
| `Raytracer.h` | scene object 구성, closest hit 탐색, perspective ray 생성 |
| `Object.h` | shared material fields와 `CheckRayCollision()` interface |
| `Sphere.h` | sphere intersection 구현 |
| `Hit.h` | hit distance, point, normal, object pointer 저장 |
| `main.cpp` | preview window와 ImGui frame |

대표 흐름은 다음과 같습니다.

```cpp
const vec3 eyePos(0.0f, 0.0f, -1.5f);
const vec3 pixelPosWorld = TransformScreenToWorld(vec2(i, j));
const auto rayDir = glm::normalize(pixelPosWorld - eyePos);
Ray pixelRay{pixelPosWorld, rayDir};
```

Step5는 한 sphere만 대상으로 lighting을 계산했습니다. Step6는 `objects` 배열의 모든 object에 대해 intersection을 검사하고, 가장 가까운 hit만 shading에 사용합니다.

```cpp
if (hit.d >= 0.0f && (closestHit.d < 0.0f || closestHit.d > hit.d))
{
    hit.obj = object;
    closestHit = hit;
}
```

## Notes handling

- raw source의 projection 장문 설명은 archive source에서 제거하고 local-only 문서에 요약 보존했습니다.
- 원문 메모와 검토 메모는 git에 올리지 않는 `local/Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/`에 둡니다.
- raw markdown note는 terminal에서 인코딩이 깨져 보여, 최종 문서 정리 시 editor에서 원문 확인이 필요합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 핵심 구현부 정리 완료 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 사용자가 Debug/Release 실행 화면 정상 동작을 확인했습니다.
- 촬영 단계에서 가까운 sphere와 먼 sphere의 크기 차이가 보이는 구도를 확인합니다.
- Step7 Triangle import 전에 `Object` abstraction이 triangle intersection으로 확장되는 지점을 비교합니다.
