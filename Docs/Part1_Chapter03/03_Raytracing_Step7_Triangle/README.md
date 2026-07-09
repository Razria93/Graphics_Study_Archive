# 03 Raytracing Step7 Triangle

## Chapter purpose

Step7은 Step6의 object abstraction에 `Triangle` primitive를 추가하고, ray가 triangle이 놓인 plane과 만난 뒤 그 교점이 triangle 내부에 있는지 검사하는 예제입니다. 이 단계부터 sphere 외의 polygon primitive를 ray tracing scene에 포함할 수 있습니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Triangle primitive | 세 vertex로 정의되는 가장 기본적인 polygon primitive |
| Face normal | `cross(v1 - v0, v2 - v0)`로 계산하는 triangle plane normal |
| Backface culling | camera를 향하지 않는 triangle face를 제외하는 처리 |
| Ray-plane intersection | ray와 triangle이 놓인 plane의 교점 `t`를 찾는 과정 |
| Inside test | 교점이 triangle 세 edge 안쪽에 있는지 확인하는 과정 |
| Closest hit | sphere와 triangle 모두 같은 object list에서 가장 가까운 hit만 shading |

## Core implementation

핵심 구현은 다음 파일에 있습니다.

| File | Role |
| --- | --- |
| `Triangle.h` | ray-triangle intersection, backface culling, inside test |
| `Raytracer.h` | sphere와 triangle scene 구성, closest hit 탐색 |
| `Object.h` | sphere/triangle 공통 collision interface |
| `Sphere.h` | sphere intersection 유지 |
| `Hit.h` | hit distance, point, normal, object pointer 저장 |

대표 흐름은 다음과 같습니다.

```cpp
faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
const float denom = dot(dir, faceNormal);
t = (dot(v0, faceNormal) - dot(origin, faceNormal)) / denom;
point = origin + t * dir;
```

교점이 triangle 내부인지 확인할 때는 각 edge와 교점으로 만든 작은 triangle의 normal 방향이 face normal과 같은 쪽인지 검사합니다.

```cpp
if (dot(normal0, faceNormal) < 0.0f) return false;
if (dot(normal1, faceNormal) < 0.0f) return false;
if (dot(normal2, faceNormal) < 0.0f) return false;
```

## Notes handling

- raw source의 backface culling, cross product, inside-test 장문 설명은 archive source에서 제거하고 local-only 문서에 요약 보존했습니다.
- 원문 메모와 검토 메모는 git에 올리지 않는 `local/Part1_Chapter03/03_Raytracing_Step7_Triangle/`에 둡니다.
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
- Step8 Shadow import 전에 Step7의 closest hit와 surface normal이 shadow ray 계산에 어떻게 쓰일지 비교합니다.
