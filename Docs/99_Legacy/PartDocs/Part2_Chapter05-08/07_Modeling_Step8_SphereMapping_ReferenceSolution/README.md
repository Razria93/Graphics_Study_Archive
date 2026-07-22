# 07 Modeling Step8 SphereMapping ReferenceSolution

## 목적

subdivision sphere에 sphere mapping texture coordinate를 적용하는 reference solution입니다. 사용자 풀이와 비교할 기준 구현으로 보존하며, longitude/latitude 기반 coordinate 계산과 face normal 흐름을 함께 확인합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Reference solution | 사용자 풀이와 비교할 기준 구현입니다. |
| Sphere mapping | sphere 표면의 방향을 2D texture coordinate로 변환합니다. |
| Longitude/latitude | `theta`, `phi`로 sphere 위 위치를 표현합니다. |
| Texture seam | U coordinate가 0과 1로 갈라지는 경계입니다. |
| Subdivision sphere | 세분화된 triangle mesh를 sphere surface로 projection한 결과입니다. |

## 구현 흐름

1. subdivision sphere를 생성합니다.
2. vertex position을 normalize하고 radius를 곱해 sphere 표면으로 보냅니다.
3. `atan2f()`와 `acosf()`로 `theta`, `phi`를 계산합니다.
4. 계산한 각도를 texture coordinate로 변환합니다.
5. face normal을 계산해 triangle 단위 shading을 확인합니다.
6. texture와 normal debug view로 mapping 결과를 확인합니다.

## 핵심 코드

```cpp
const float theta = atan2f(v.position.z, v.position.x);
const float phi = acosf(v.position.y / radius);

v.texcoord.x = theta / XM_2PI;
v.texcoord.y = phi / XM_PI;
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step8_SphereMapping_Lecture`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_ReferenceSolution`
- Pair user solution: `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_UserSolution`
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.5ae59ab1/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
- Asset public readiness: 검토 필요
- Source comments: raw 재현성을 우선하여 현재 source 주석은 유지했습니다. 메모 위치와 최종 정리 방향은 local-only 문서에 기록했습니다.

## 확인 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Build Debug x64 | 성공 |
| Build Release x64 | 성공 |
| Run Debug/Release | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 다음 확인

사용자가 Visual Studio에서 Debug x64와 Release x64 빌드/실행을 확인했습니다. sphere texture mapping, `Use Texture`, `Wireframe`, `Draw Normals`, `Normal scale` 확인 완료.
