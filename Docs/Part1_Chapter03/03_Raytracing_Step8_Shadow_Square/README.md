# 03 Raytracing Step8 Shadow Square

## Chapter purpose

`Shadow_Square`는 기본 Step8 Shadow의 scene 구조를 조금 정리해서, 바닥을 두 개의 triangle로 직접 관리하지 않고 `Square` primitive wrapper로 표현하는 변형입니다. 렌더링 결과의 핵심은 동일하게 shadow ray이며, 차이는 scene authoring 관점에서 사각형 surface를 하나의 object처럼 다루는 데 있습니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Square primitive | 4개 vertex로 정의하고 내부적으로 두 triangle collision을 검사하는 wrapper |
| Primitive abstraction | scene 구성 코드를 더 높은 수준의 object 단위로 정리하는 방식 |
| Shadow ray | hit point에서 light 방향 visibility를 확인하는 ray |
| Closest hit reuse | primary ray와 shadow ray가 같은 collision 탐색 함수를 재사용하는 구조 |
| Public readiness | 코드 공개 전 강의 원문 구조/주석/자료 포함 여부를 다시 확인해야 하는 상태 |

## Core implementation

핵심 차이는 `Raytracer.h`의 floor 구성입니다. 기본 Step8은 floor를 두 개의 `Triangle`로 직접 추가했지만, 이 변형은 `Square` 하나를 scene에 추가합니다.

```cpp
auto floor = std::make_shared<Square>(
    vec3(-2.0f, -1.0f, 0.0f),
    vec3(-2.0f, -1.0f, 4.0f),
    vec3(2.0f, -1.0f, 4.0f),
    vec3(2.0f, -1.0f, 0.0f));
```

`Square::CheckRayCollision()`은 내부 triangle 두 개의 hit를 비교해서 더 가까운 hit를 반환합니다. `Raytracer::FindClosestCollision()`은 object 단위로 `hit.obj`를 다시 설정하므로 shading material은 `Square`에 지정된 값을 사용합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 사용자가 Debug/Release 실행 화면을 확인하면 run status를 성공으로 갱신합니다.
- 다음 후보는 `03_Raytracing_Step9_BarycentricCordinates`입니다.
