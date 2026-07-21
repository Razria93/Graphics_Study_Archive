# 03 Raytracing Step5 PhongShading

## Chapter purpose

Step5는 Step4의 ray-sphere intersection 결과에 Phong reflection model을 적용해 sphere에 lighting을 입히는 예제입니다. Ray가 sphere와 만나는 지점의 surface normal, light direction, view direction을 이용해 ambient, diffuse, specular 항을 계산합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Phong reflection model | ambient, diffuse, specular 항을 더해 표면 조명 결과를 만드는 local illumination model |
| Ambient | 직접 조명 계산 없이 기본적으로 더하는 색 |
| Diffuse | surface normal과 light direction의 내적으로 계산하는 난반사 항 |
| Specular | reflection direction과 view direction의 내적으로 계산하는 정반사 항 |
| Shininess / alpha | specular highlight의 좁고 날카로운 정도를 조절하는 지수 |
| Light position | hit point에서 light를 향하는 방향을 계산하기 위한 위치 |
| Surface normal | hit point에서 sphere 중심을 뺀 뒤 normalize한 표면 법선 |

## Core implementation

핵심 구현은 다음 파일에 있습니다.

| File | Role |
| --- | --- |
| `Raytracer.h` | hit point에서 Phong lighting 계산 |
| `Sphere.h` | material fields와 ray-sphere intersection 계산 |
| `Light.h` | point light position |
| `main.cpp` | ImGui material/light controls |
| `Example.h` | CPU pixel buffer를 D3D11 dynamic texture로 upload |

대표 흐름은 다음과 같습니다.

```cpp
const vec3 dirToLight = glm::normalize(light.pos - hit.point);
const float diffuse = glm::max(dot(hit.normal, dirToLight), 0.0f);

const vec3 reflectDir = glm::normalize(2.0f * dot(hit.normal, dirToLight) * hit.normal - dirToLight);
const vec3 viewDir = -ray.dir;
const float specular = glm::pow(glm::max(dot(reflectDir, viewDir), 0.0f), sphere->alpha);

return sphere->amb + sphere->diff * diffuse + sphere->spec * specular * sphere->ks;
```

Step4에서는 hit 여부와 distance 중심으로 sphere를 표현했다면, Step5에서는 hit point의 normal과 light/view direction이 최종 색을 결정합니다.

## Notes handling

- raw source에 있던 장문 학습 주석은 archive source에 그대로 유지하지 않습니다.
- 원문 메모와 검토 메모는 git에 올리지 않는 `local/Part1_Chapter03/03_Raytracing_Step5_PhongShading/`에 보존합니다.
- raw markdown note는 terminal에서 인코딩이 깨져 보여, 최종 문서 정리 시 editor에서 원문을 직접 확인하는 편이 안전합니다.

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
- 촬영 단계에서 light position, diffuse color, specular power, specular coeff 조절 결과를 남깁니다.
- Step6 PerspectiveView import 전에 Step5와 비교해 camera ray가 어떻게 달라지는지 기록합니다.
