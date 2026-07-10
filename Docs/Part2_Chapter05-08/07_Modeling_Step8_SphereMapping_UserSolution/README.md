# 07 Modeling Step8 SphereMapping UserSolution

## 목적

subdivision sphere에 texture coordinate를 계산하고, seam/pole 근처에서 texture가 끊기거나 늘어나는 문제를 직접 보정해 본 사용자 풀이입니다. Step6의 sphere projection과 Step7의 face normal 흐름 위에 sphere mapping 문제를 추가로 다룹니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Sphere mapping | sphere 표면의 3D 방향을 2D texture coordinate로 변환합니다. |
| `atan2` | XZ 평면의 방향각을 계산해 longitude 성격의 U coordinate를 만듭니다. |
| `acos` | Y축 위치로 latitude 성격의 V coordinate를 만듭니다. |
| Texture seam | U coordinate가 0과 1 사이에서 끊기는 경계입니다. |
| Seam correction | seam을 가로지르는 triangle에서 vertex를 복제하거나 coordinate를 보정합니다. |
| User solution | 사용자가 직접 작성한 seam 보정 시도와 디버깅 흔적을 보존하는 풀이입니다. |

## 구현 흐름

1. subdivision sphere를 생성합니다.
2. 각 vertex를 sphere radius로 projection합니다.
3. vertex position에서 `theta`, `phi`를 계산합니다.
4. `theta / XM_2PI`, `phi / XM_PI`로 texture coordinate를 만듭니다.
5. seam을 가로지르는 triangle을 감지합니다.
6. 필요한 경우 vertex를 추가해 seam 근처 texture coordinate를 보정합니다.
7. `ojwD8.jpg`와 `wall.jpg` texture를 사용해 mapping 결과를 확인합니다.

## 핵심 코드

```cpp
float theta = atan2f(v.position.z, v.position.x);
if (theta < 0.0f)
    theta += XM_2PI;

const float phi = acosf(v.position.y / radius);

v.texcoord.x = theta / XM_2PI;
v.texcoord.y = phi / XM_PI;
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step8-2_SphereMapping_Complete`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_UserSolution`
- Pair reference: `Part2_Chapter05-08/07_Modeling_Step8_SphereMapping_ReferenceSolution`
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
| Build Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Debug/Release | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 다음 확인

Visual Studio에서 Debug x64와 Release x64를 각각 빌드/실행하고, sphere texture mapping, seam 보정, `Use Texture`, `Wireframe`, `Draw Normals`, `Normal scale` 동작을 확인합니다.

