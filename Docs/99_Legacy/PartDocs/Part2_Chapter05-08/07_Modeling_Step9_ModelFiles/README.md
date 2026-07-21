# 07 Modeling Step9 ModelFiles

## 목적

Assimp를 사용해 외부 model file을 읽고, 여러 mesh와 texture를 D3D11 buffer/resource로 올려 렌더링하는 예제입니다. 이전 단계까지는 procedural mesh를 직접 생성했다면, 이 단계는 file 기반 scene data를 archive에서 재현 가능한 상대 경로 asset으로 관리하는 데 초점을 둡니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Assimp | 여러 3D model format을 읽어 `aiScene`, `aiNode`, `aiMesh`, `aiMaterial` 구조로 제공합니다. |
| Model file loading | FBX 같은 외부 파일에서 vertex, index, material, texture 정보를 읽습니다. |
| Scene graph | node transform과 parent/child 관계를 따라 mesh transform을 누적합니다. |
| MeshData | loader가 읽은 vertex/index/texture filename을 archive rendering 구조로 옮기는 중간 데이터입니다. |
| Texture asset path | material의 diffuse texture filename을 archive 상대 경로로 다시 연결합니다. |
| vcpkg dependency | Assimp header/library/runtime dependency가 필요합니다. |

## 구현 흐름

1. `GeometryGenerator::ReadFromFile()`이 base path와 model filename을 받습니다.
2. `ModelLoader::Load()`가 Assimp `Importer::ReadFile()`로 scene을 읽습니다.
3. scene root node부터 `ProcessNode()`를 재귀적으로 순회합니다.
4. node transform을 누적해 mesh vertex position에 반영합니다.
5. `ProcessMesh()`에서 vertex, normal, texcoord, index를 `MeshData`로 변환합니다.
6. material의 diffuse texture filename을 읽어 texture resource를 생성합니다.
7. 생성된 mesh마다 vertex/index buffer, texture resource, constant buffer를 연결합니다.

## 핵심 코드

```cpp
auto meshes =
    GeometryGenerator::ReadFromFile("f3d-data/zelda/", "zeldaPosed001.fbx");
```

```cpp
const aiScene *pScene = importer.ReadFile(
    this->basePath + filename,
    aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step9_ModelFiles`
- Archive source: `Part2_Chapter05-08/07_Modeling_Step9_ModelFiles`
- Included model assets:
  - `f3d-data/zelda/zeldaPosed001.fbx`
  - `f3d-data/zelda/*_diff.png`
- Included texture assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.bb08b627/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
  - unused `f3d-data` sample models
- Path adjustment:
  - raw의 `c:/zelda/source/` 절대 경로를 archive 상대 경로 `f3d-data/zelda/`로 변경했습니다.
  - Zelda source texture 전체를 통째로 복사하지 않고 raw의 `f3d-data/zelda/textures`에 있는 diffuse texture 세트를 실행용 asset으로 선별했습니다.
- Asset public readiness: 검토 필요
- Source comments: raw 재현성을 우선하여 현재 source 주석은 대부분 유지했습니다. 메모 위치와 최종 정리 방향은 local-only 문서에 기록했습니다.

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

사용자가 Visual Studio에서 Debug x64와 Release x64 빌드/실행을 확인했습니다. Assimp dependency, Zelda model load, texture binding, `Use Texture`, `Wireframe`, `Draw Normals`, `Normal scale` 확인 완료.
