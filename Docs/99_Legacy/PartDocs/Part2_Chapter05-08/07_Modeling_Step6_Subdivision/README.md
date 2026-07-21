# 07 Modeling Step6 Subdivision

## 목적

기존 sphere mesh를 subdivision으로 더 촘촘하게 만든 뒤, 각 vertex를 sphere surface로 다시 projection하는 예제입니다. 낮은 분할 수의 sphere나 icosahedron 같은 거친 mesh를 시작점으로 삼고, triangle을 반복적으로 나누어 더 부드러운 구면을 구성합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Subdivision | triangle을 더 작은 triangle들로 나누어 mesh 밀도를 높입니다. |
| Sphere projection | subdivide 후 vertex normal 방향에 radius를 곱해 구 표면으로 다시 이동시킵니다. |
| Icosahedron | subdivision sphere의 시작점으로 자주 쓰이는 20면체입니다. |
| Midpoint vertex | triangle edge의 중간점을 새 vertex로 추가합니다. |
| Normal recalculation | 새 vertex 위치를 기준으로 normal을 다시 normalize합니다. |
| Normal debug view | subdivision 후 normal 방향을 line mesh로 확인합니다. |

## 구현 흐름

1. `GeometryGenerator::MakeSphere()` 또는 `MakeIcosahedron()`으로 초기 mesh를 만듭니다.
2. `GeometryGenerator::SubdivideToSphere(radius, meshData)`를 호출합니다.
3. 각 triangle의 edge midpoint를 새 vertex로 만듭니다.
4. 기존 triangle을 더 작은 triangle들로 재구성합니다.
5. 모든 vertex의 normal을 다시 계산하고, `normal * radius`로 position을 sphere surface에 projection합니다.
6. subdivision된 mesh를 vertex/index buffer로 올려 렌더링합니다.

## 핵심 코드

```cpp
MeshData meshData = GeometryGenerator::MakeSphere(1.5f, 5, 5);
meshData = GeometryGenerator::SubdivideToSphere(1.5f, meshData);
meshData = GeometryGenerator::SubdivideToSphere(1.5f, meshData);
```

```cpp
v.normal = v.position;
v.normal.Normalize();
v.position = v.normal * radius;
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step6_Subdivision`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step6_Subdivision`
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.564f0086/`
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

사용자가 Visual Studio에서 Debug x64와 Release x64 빌드/실행을 확인했습니다. subdivision sphere, texture/lighting, `Wireframe`, `Draw Normals`, `Normal scale` 확인 완료.
