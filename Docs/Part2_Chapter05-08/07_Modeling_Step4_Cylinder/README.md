# 07 Modeling Step4 Cylinder

## 목적

`MakeCylinder()`로 원기둥 mesh를 절차적으로 생성하고, texture, lighting, normal debug view가 함께 동작하는지 확인하는 예제입니다. Step3 Grid가 평면의 반복 구조를 다뤘다면, 이 예제는 원주 방향 `sliceCount`를 기준으로 위/아래 ring vertex와 side face index를 구성하는 데 초점을 둡니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Cylinder mesh | 원주를 `sliceCount`만큼 나누어 만든 입체 mesh입니다. |
| Ring vertices | 위/아래 원 둘레에 각각 `sliceCount + 1`개의 vertex를 둡니다. |
| `dTheta` | 한 slice가 차지하는 각도이며 `XM_2PI / sliceCount`로 계산합니다. |
| Side indices | 인접한 위/아래 ring vertex 네 개를 두 개의 triangle로 연결합니다. |
| Surface normal | 원주 방향 위치에 맞춰 측면 normal을 회전시켜 계산합니다. |
| Normal debug view | 각 vertex의 normal 방향을 line mesh로 시각화합니다. |

## 구현 흐름

1. `GeometryGenerator::MakeCylinder(bottomRadius, topRadius, height, sliceCount)`를 호출합니다.
2. `dTheta`로 slice 간 각도 간격을 계산합니다.
3. 위쪽 ring과 아래쪽 ring vertex를 각각 생성합니다.
4. 각 vertex에 position, normal, texcoord를 채웁니다.
5. 인접 slice를 두 triangle로 연결해 side index를 구성합니다.
6. 생성한 mesh를 vertex/index buffer로 올립니다.
7. `Draw Normals`와 `Normal scale`로 normal line overlay를 확인합니다.

## 핵심 코드

```cpp
MeshData meshData = GeometryGenerator::MakeCylinder(1.0f, 1.0f, 2.0f, 40);
```

```cpp
const float dTheta = XM_2PI / float(sliceCount);
```

```cpp
indices.push_back(i);
indices.push_back(i + offset);
indices.push_back(i + 1 + offset);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step4_Cylinder`
- Excluded raw reference:
  - `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step4_Cylinder_Backup`
- Related raw docs: Step4 전용 study note는 확인되지 않았고, portfolio planning 문서에서 후보로만 언급됨
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.a6bd8741/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
- Asset public readiness: 검토 필요
- Source comments: raw 장문 학습 주석은 source에서 제거하고 local-only 문서로 분리했습니다.

## 확인 상태

| 항목 | 상태 |
| --- | --- |
| Code split | 완료 |
| Build Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Debug/Release | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 다음 확인

Visual Studio에서 Debug x64와 Release x64를 각각 빌드/실행하고, cylinder mesh, texture, lighting, `Wireframe`, `Draw Normals`, `Normal scale` 동작을 확인합니다.
