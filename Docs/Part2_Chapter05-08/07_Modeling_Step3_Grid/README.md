# 07 Modeling Step3 Grid

## 목적

`MakeGrid()`로 규칙적인 격자 mesh를 생성하고, grid에 texture와 normal debug view를 함께 적용하는 예제입니다. Step1/Step2에서 box와 normal line을 다뤘다면, 이 예제는 slice/stack 개수를 입력받아 반복문으로 vertex/index를 구성하는 procedural grid generation에 초점을 둡니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Grid mesh | 일정한 간격의 rows/stacks와 columns/slices로 구성한 평면 mesh입니다. |
| `numSlices` / `numStacks` | grid를 가로/세로 방향으로 몇 개의 사각 cell로 나눌지 결정합니다. |
| Vertex count | `(numSlices + 1) * (numStacks + 1)` 형태로 cell 수보다 한 줄씩 더 필요합니다. |
| Index generation | 각 cell을 두 개의 triangle로 나누어 index buffer를 구성합니다. |
| Texture coordinate | grid 전체 폭/높이에 대한 상대 위치를 `u/v`로 계산합니다. |
| Normal debug view | Step2와 같은 normal line mesh로 grid normal 방향을 확인합니다. |

## 구현 흐름

1. `GeometryGenerator::MakeGrid(width, height, numSlices, numStacks)`를 호출합니다.
2. `dx = width / numSlices`, `dy = height / numStacks`로 vertex 간격을 계산합니다.
3. 이중 반복문으로 x-y 평면 위의 grid vertex를 생성합니다.
4. 각 vertex에 position, normal, texcoord를 채웁니다.
5. 각 cell마다 두 개의 triangle을 만들도록 index를 추가합니다.
6. `ojwD8.jpg` texture와 `Use Texture` toggle로 texture 적용 여부를 확인합니다.
7. `Draw Normals`와 `Normal scale`로 normal line overlay를 확인합니다.

## 핵심 코드

```cpp
MeshData meshData = GeometryGenerator::MakeGrid(2.0f, 1.7f, 5, 3);
```

```cpp
const float dx = width / numSlices;
const float dy = height / numStacks;
```

```cpp
v.texcoord.x = dx * i / width;
v.texcoord.y = 1 - (dy * j / height);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step3_Grid`
- Excluded raw reference:
  - `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step3_Grid_Backup`
- Related raw docs:
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter07_Modeling_Step3_Grid.md`
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter07_Modeling_Step3_Grid_2.md`
- Included assets:
  - `ojwD8.jpg`
  - `crate2_diffuse.png`
  - `wall.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.d96a91f4/`
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

Visual Studio에서 Debug x64와 Release x64를 각각 빌드/실행하고, textured grid, `Use Texture`, `Draw Normals`, `Normal scale` 동작을 확인합니다.
