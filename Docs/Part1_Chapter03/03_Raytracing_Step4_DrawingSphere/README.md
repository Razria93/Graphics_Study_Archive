# 03 Raytracing Step4 DrawingSphere

## Chapter purpose

Step4는 모든 screen pixel에서 +z 방향 ray를 만들고, 그 ray가 3D world의 sphere와 만나는지 계산해서 CPU-side pixel buffer에 색을 채우는 예제입니다. DirectX11은 계산된 pixel buffer를 texture로 받아 화면 quad에 출력하는 표시 계층으로 사용됩니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Ray | `start` position과 `dir` direction으로 표현되는 반직선 |
| Orthographic ray | 각 pixel에서 같은 방향으로 나가는 ray |
| Screen to world | 2D screen coordinate를 z=0 camera plane의 world coordinate로 변환 |
| Ray-sphere intersection | ray와 sphere 방정식을 결합해 quadratic equation의 해를 찾는 과정 |
| Discriminant | 교차 없음/접함/두 교점 여부를 나누는 판별식 |
| Hit record | hit distance, hit point, normal 같은 교차 결과 묶음 |
| CPU render buffer | CPU에서 계산한 RGBA pixel array를 GPU texture로 복사해 표시하는 방식 |

## Core implementation

핵심 구현은 다음 파일에 있습니다.

| File | Role |
| --- | --- |
| `Raytracer.h` | pixel별 ray 생성, sphere hit 결과를 color로 변환 |
| `Sphere.h` | ray-sphere intersection 계산 |
| `Hit.h` | intersection result 구조 |
| `Example.h` | CPU pixel buffer를 D3D11 dynamic texture로 upload |
| `main.cpp` | window, ImGui control, frame loop |

대표 흐름은 다음과 같습니다.

```cpp
const vec3 pixelPosWorld = TransformScreenToWorld(vec2(i, j));
const auto rayDir = vec3(0.0f, 0.0f, 1.0f);
Ray pixelRay{pixelPosWorld, rayDir};

pixels[size_t(i + width * j)] = vec4(traceRay(pixelRay), 1.0f);
```

`Sphere::IntersectRayCollision()`은 `ray.start + t * ray.dir`를 sphere equation에 대입해 `t`를 구합니다. `t`가 양수이면 camera plane 앞쪽에서 sphere와 만난 것으로 보고, hit point와 normal을 계산합니다.

## Notes handling

- raw source에 있던 장문 학습 주석은 archive source에 그대로 유지하지 않습니다.
- 원문 메모와 검토 메모는 git에 올리지 않는 `local/Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/`에 보존합니다.
- 최종 제출/공개 문서는 이 tracked 문서를 기반으로 다시 정리합니다.

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
- 촬영 단계로 넘어가기 전 sphere 위치/radius/color 조작 결과를 확인합니다.
- Step5 PhongShading import 전에 Step4와의 코드 차이를 비교해 조명 계산이 추가되는 지점을 기록합니다.
