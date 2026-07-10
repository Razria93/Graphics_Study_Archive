# 07 Modeling Step5 Sphere UserSolution

## 목적

`MakeSphere()`를 직접 구성한 사용자 풀이 버전입니다. sphere를 위쪽 half sphere와 아래쪽 half sphere로 나누어 vertex/index를 만든 뒤 하나의 mesh로 합치는 방식입니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Sphere mesh | 구면을 slice/stack 단위의 vertex/index mesh로 근사합니다. |
| Half sphere composition | top half와 bottom half를 따로 만든 뒤 offset으로 index를 이어 붙입니다. |
| Slice | Y축 둘레 방향 분할입니다. |
| Stack | 위아래 방향 분할입니다. |
| Pole vertex | sphere의 위/아래 극점에서 여러 triangle이 만나는 vertex입니다. |
| Normal | 구 중심에서 vertex position으로 향하는 방향을 normalize해 사용합니다. |
| Texture coordinate | slice/stack 비율로 texture sampling 좌표를 만듭니다. |

## 구현 흐름

1. `GeometryGenerator::MakeSphere(radius, numSlices, numStacks)`를 호출합니다.
2. top half sphere를 먼저 생성하고, stack/slice loop로 vertex를 채웁니다.
3. top half index를 구성하면서 pole 근처 triangle을 별도 처리합니다.
4. bottom half sphere를 같은 구조로 생성합니다.
5. bottom half index에는 top half vertex 수를 offset으로 더합니다.
6. 생성된 sphere mesh를 vertex/index buffer로 올려 렌더링합니다.

## 핵심 코드

```cpp
MeshData meshData = GeometryGenerator::MakeSphere(1.0f, 40, 20);
```

```cpp
const float dTheta = -XM_2PI / numSlices_float * sign;
const float dPhi = XM_PI * 0.5f / numStacks_float * sign;
```

```cpp
int offset_half = int(vertices.size());
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step5-3_Sphere_Complete`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution`
- Pair reference: `Part2_Chapter05-08/07_Modeling_Step5_Sphere_ReferenceSolution`
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

사용자가 Visual Studio에서 Debug x64와 Release x64 빌드/실행을 확인했습니다. sphere mesh, texture, lighting, `Wireframe`, `Draw Normals`, `Normal scale` 확인 완료.
