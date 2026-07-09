# 04 Rasterization Step9 Shading

## 목적

software rasterizer에서 cube mesh의 vertex normal을 보간하고, pixel shader 단계에서 directional light 기반 Blinn-Phong shading을 계산하는 예제입니다. 이전 Step의 projection, depth, backface culling 흐름 위에 material/light 개념을 추가합니다.

## 핵심 키워드

- Cube mesh
- Normal vector
- Material
- Directional light
- Ambient / diffuse / specular
- Blinn-Phong shading
- Per-pixel shading

## 구현 흐름

1. `Mesh::InitBox()`가 6면 cube geometry와 face normal을 생성합니다.
2. `Transformation`, `Material`, `Light` 구조체가 object transform, 재질, 조명 값을 관리합니다.
3. `MyVertexShader()`가 vertex position과 normal을 같은 회전 기준으로 변환합니다.
4. `DrawIndexedTriangle()`이 rasterized triangle 내부에서 position과 normal을 barycentric weight로 보간합니다.
5. `MyPixelShader()`가 보간된 position/normal을 사용해 eye 방향과 light 방향을 계산합니다.
6. ambient, diffuse, specular 항을 더해 최종 pixel color를 만듭니다.
7. ImGui slider로 object transform, material, light direction을 조절하며 shading 변화를 확인합니다.

## 핵심 코드

```cpp
psInput.position = w0 * p0 + w1 * p1 + w2 * p2;
psInput.normal = glm::normalize(w0 * n0 + w1 * n1 + w2 * n2);
```

triangle 내부의 fragment마다 position과 normal을 보간해 pixel shader로 넘깁니다.

```cpp
const vec3 lightDir = -light.direction;
return BlinnPhong(light, material, normalDir, toEyeDir, lightDir);
```

directional light의 방향은 빛이 향하는 방향이므로, 표면에서 빛을 향하는 방향으로 쓰기 위해 반대로 뒤집어 shading에 사용합니다.

```cpp
const glm::vec3 halfwayVector = glm::normalize(lightDir + viewDir);
const float specularRatio =
    glm::pow(glm::max(0.0f, glm::dot(normalDir, halfwayVector)),
             material.shininess);
```

Blinn-Phong 방식에서는 반사 벡터 대신 halfway vector와 normal의 유사도를 사용해 specular highlight를 계산합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step9_Shading/source-comments.md`로 분리했습니다.
- raw의 핵심 구조인 `Transformation`, `Material`, `Light`, `MyShader.h`, cube mesh, normal buffer, Blinn-Phong shading은 유지했습니다.
- normal도 object rotation과 같은 회전 순서를 적용하도록 유지했습니다.
- runtime control은 object transform, material, light direction을 조절하는 ImGui UI를 유지했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 강의 기반 구조, 주석, 문서, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
