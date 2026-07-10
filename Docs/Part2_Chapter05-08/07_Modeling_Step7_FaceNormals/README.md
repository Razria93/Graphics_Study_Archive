# 07 Modeling Step7 FaceNormals

## 목적

subdivision sphere에서 vertex normal 대신 face normal을 사용해 flat shading에 가까운 표면 표현을 확인하는 예제입니다. 각 triangle의 edge vector cross product로 face normal을 계산하고, 해당 triangle을 이루는 vertex들에 같은 normal을 부여합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Face normal | triangle 한 면을 대표하는 normal입니다. |
| Vertex normal | vertex별로 저장되는 normal입니다. smooth shading에 자주 사용됩니다. |
| Flat shading | 한 face 안에서 같은 normal을 사용해 면 단위 경계가 드러나는 shading입니다. |
| Cross product | 두 edge vector의 외적으로 face normal 방향을 계산합니다. |
| Subdivision sphere | triangle subdivision 후 sphere surface로 vertex를 projection한 mesh입니다. |
| Normal debug view | face normal 결과를 line mesh로 확인합니다. |

## 구현 흐름

1. `GeometryGenerator::MakeSphere()`로 초기 sphere mesh를 만듭니다.
2. `GeometryGenerator::SubdivideToSphere()`로 mesh를 subdivision합니다.
3. subdivision 과정에서 새 triangle을 구성합니다.
4. 각 triangle마다 `(v1.position - v0.position).Cross(v2.position - v0.position)`로 face normal을 계산합니다.
5. 계산한 face normal을 해당 triangle의 세 vertex normal에 동일하게 저장합니다.
6. normal line overlay와 lighting 결과로 vertex normal/smooth shading과의 차이를 확인합니다.

## 핵심 코드

```cpp
auto faceNormal = (v1.position - v0.position).Cross(v2.position - v0.position);
v0.normal = faceNormal;
v1.normal = faceNormal;
v2.normal = faceNormal;
```

```cpp
UpdateFaceNormal(v4, v1, v5);
UpdateFaceNormal(v0, v4, v3);
UpdateFaceNormal(v3, v4, v5);
UpdateFaceNormal(v3, v5, v2);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step7_FaceNormals`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step7_FaceNormals`
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.7a62f24d/`
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

사용자가 Visual Studio에서 Debug x64와 Release x64 빌드/실행을 확인했습니다. face normal 기반 shading, texture/lighting, `Wireframe`, `Draw Normals`, `Normal scale` 확인 완료.
