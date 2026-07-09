# 03 Raytracing Step12 Reflection

## Chapter purpose

Step12는 ray tracing의 recursive reflection을 구현하는 예제입니다. Step11의 supersampling 흐름과 달리, 이번 단계는 물체 표면에서 반사 ray를 새로 만들고 depth를 줄여가며 다시 scene을 추적합니다. local Phong shading과 reflected color를 material weight로 섞어 반사 표면의 색을 계산합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Reflection ray | 표면 법선과 incident direction으로 계산한 반사 방향 ray |
| Recursive ray tracing | hit point에서 새 ray를 만들고 depth를 줄여가며 반복 추적하는 방식 |
| Reflection weight | local shading과 reflected color를 섞는 material factor |
| Ray bias | 같은 표면을 다시 맞는 self-intersection을 피하기 위한 작은 offset |
| Recursion depth | 무한 반사를 막기 위한 최대 재귀 횟수 |

## Core implementation

핵심 구현은 `Object.h`의 material factor와 `Raytracer.h`의 `traceRay()`에 있습니다.

```cpp
float reflection = 0.0f;
float transparency = 0.0f;
```

반사 방향은 incoming ray를 hit normal 기준으로 반사시켜 계산합니다.

```cpp
const vec3 incident = -ray.dir;
const vec3 reflectedDir = glm::normalize(2.0f * dot(incident, hit.normal) * hit.normal - incident);
Ray reflectedRay{hit.point + reflectedDir * 1e-4f, reflectedDir};
```

local Phong color는 `1 - reflection - transparency` 비율만큼 반영하고, reflected color는 `reflection` 비율만큼 더합니다.

```cpp
const float localWeight = glm::clamp(1.0f - hit.obj->reflection - hit.obj->transparency, 0.0f, 1.0f);
vec3 color = ShadePhong(hit, ray) * localWeight;
color += traceRay(reflectedRay, depth - 1) * hit.obj->reflection;
```

## Asset handling

| Asset | Status | Note |
| --- | --- | --- |
| `shadertoy_abstract1.jpg` | private archive 포함 | ground texture로 코드에서 직접 사용 |
| `back.jpg` | private archive 포함 | raw project item에 포함되어 있으나 현재 `Raytracer.h`에서 직접 사용하지 않음 |

두 asset 모두 private archive 실행/프로젝트 구조 보존 목적으로 포함합니다. public repo 공개 전에는 출처/라이선스 표기 가능 여부를 다시 확인합니다.

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

- 사용자가 Debug/Release 실행을 확인하면 status와 tracking 문서를 갱신합니다.
- 다음 코드 후보는 `03_Raytracing_Step13_Transparency`입니다.
