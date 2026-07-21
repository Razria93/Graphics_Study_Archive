# 03 Raytracing Step13 Transparency

## Chapter purpose

Step13은 Step12의 recursive ray tracing 구조에 transparency/refraction을 추가하는 예제입니다. 투명 구체를 hit하면 surface normal과 ray direction을 기준으로 굴절 방향을 만들고, depth를 줄여가며 scene을 다시 추적합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Transparency | local shading 대신 뒤쪽 scene color를 일정 비율로 통과시키는 material property |
| Refraction | ray가 매질 경계를 지나며 방향이 바뀌는 현상 |
| Index of refraction | 매질별 굴절률. 예제에서는 glass sphere를 `1.5`로 둠 |
| Snell's law | 입사각과 굴절각의 관계를 정하는 법칙 |
| Total internal reflection | 굴절 방향이 성립하지 않을 때 reflection으로 처리되는 경우 |

## Core implementation

핵심 구현은 `Raytracer.h`의 `TraceRefraction()`과 `traceRay()`에 있습니다.

```cpp
const bool entering = glm::dot(ray.dir, hit.normal) < 0.0f;
const vec3 normal = entering ? hit.normal : -hit.normal;
const float eta = entering ? (1.0f / ior) : ior;
```

`glm::refract()`로 굴절 방향을 계산하고, total internal reflection이 발생하면 reflection path로 대체합니다.

```cpp
const vec3 refractedDir = glm::refract(ray.dir, normal, eta);

if (glm::dot(refractedDir, refractedDir) == 0.0f)
{
    return TraceReflection(hit, ray, depth);
}
```

최종 색은 local Phong, reflection, transparency contribution을 material weight로 섞습니다.

```cpp
color += TraceRefraction(hit, ray, depth) * hit.obj->transparency;
```

## Asset handling

| Asset | Status | Note |
| --- | --- | --- |
| `shadertoy_abstract1.jpg` | private archive 포함 | ground texture |
| `back.jpg` | private archive 포함 | background square texture |

두 asset 모두 private archive 실행을 위한 입력 자료로 포함합니다. public repo 공개 전에는 출처/라이선스 표기 가능 여부를 다시 확인합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Required texture asset | 포함 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 다음 코드 후보는 `03_Raytracing_Step14_CubeEnvironment`입니다.
