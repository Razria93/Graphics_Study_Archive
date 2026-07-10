# 07 Modeling Step5 Sphere ReferenceSolution

## 목적

강의에서 제안한 reference solution 버전의 sphere mesh 생성 예제입니다. 하나의 stack/slice loop로 구 전체의 vertex를 만들고, 인접 stack 사이를 triangle index로 연결합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Parametric sphere | `theta`, `phi` 각도 변화로 구 표면 좌표를 생성합니다. |
| Slice | Y축 둘레 방향 분할입니다. |
| Stack | 위아래 방향 분할입니다. |
| `dTheta` | 둘레 방향 각도 간격입니다. |
| `dPhi` | 위아래 방향 각도 간격입니다. |
| Triangle strip style indexing | 인접 stack ring을 두 triangle씩 연결합니다. |
| Normal | sphere 중심에서 vertex position으로 향하는 방향을 normalize합니다. |

## 구현 흐름

1. `GeometryGenerator::MakeSphere(radius, numSlices, numStacks)`를 호출합니다.
2. `dTheta`, `dPhi`로 slice/stack 각도 간격을 계산합니다.
3. 각 stack에서 시작점을 만들고 Y축으로 회전시키며 ring vertex를 생성합니다.
4. position, normal, texcoord를 채웁니다.
5. 인접 stack의 vertex ring을 두 triangle로 연결합니다.
6. 생성된 sphere mesh를 vertex/index buffer로 올려 렌더링합니다.

## 핵심 코드

```cpp
const float dTheta = -XM_2PI / float(numSlices);
const float dPhi = -XM_PI / float(numStacks);
```

```cpp
Vector3 stackStartPoint =
    Vector3::Transform(Vector3(0.0f, -radius, 0.0f),
                       Matrix::CreateRotationZ(dPhi * j));
```

```cpp
indices.push_back(offset + i);
indices.push_back(offset + i + numSlices + 1);
indices.push_back(offset + i + 1 + numSlices + 1);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step5_Sphere_Lecture`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step5_Sphere_ReferenceSolution`
- Pair user solution: `Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution`
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.87748219/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
- Asset public readiness: 검토 필요
- Source comments: raw 재현성을 우선하여 현재 source 주석은 유지했습니다. 마지막 정리 단계에서 local-only note로 분리할 수 있습니다.

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

Visual Studio에서 Debug x64와 Release x64를 각각 빌드/실행하고, sphere mesh, texture, lighting, `Wireframe`, `Draw Normals`, `Normal scale` 동작을 확인합니다.
