# Part2 Step5 Sphere Tracking

## Scope

`07_Modeling_Step5` 계열은 사용자 풀이와 강의 reference solution을 함께 보관합니다.

| Archive target | Raw reference | Build/run | Note |
| --- | --- | --- | --- |
| `Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step5-3_Sphere_Complete` | 미확인 | 사용자 풀이. top/bottom half sphere를 합치는 방식 |
| `Part2_Chapter05-08/07_Modeling_Step5_Sphere_ReferenceSolution` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step5_Sphere_Lecture` | 미확인 | 강의 reference solution. stack/slice loop로 sphere 전체 생성 |

## Included Assets

- `crate2_diffuse.png`
- `wall.jpg`
- `ojwD8.jpg`

Asset hash는 raw와 archive가 일치함을 확인했습니다. Public 공개 전에는 asset source/license를 별도 검토합니다.

## Integrity Check

| 항목 | 상태 |
| --- | --- |
| XML namespace | 정상 |
| HLSL/HLSLI BOM | 없음 |
| Binary asset hash | raw와 일치 |
| `.clang-format` project reference | 제거 |
| Raw-only output folders | 제외 |

## Build/Run Checklist

- UserSolution Debug x64 build/run
- UserSolution Release x64 build/run
- ReferenceSolution Debug x64 build/run
- ReferenceSolution Release x64 build/run
- sphere mesh 표시 확인
- texture/lighting 확인
- `Wireframe`, `Draw Normals`, `Normal scale` 확인
