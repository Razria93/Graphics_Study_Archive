# Chapter07 Step9 ModelFiles Demo

## 목적

Procedural geometry 단계에서 확장해 FBX scene의 node, submesh와 diffuse texture를
읽고 DirectX11 draw resource로 변환하는 흐름을 설명한다.

## 책임 범위

- Assimp scene 검증과 recursive node traversal을 설명한다.
- Node transform을 적용한 vertex와 submesh 단위 resource 구성을 설명한다.
- Model import 일반 이론은 [Model File Import](../../01_Topics/ModelingAndGeometry/ModelFileImport.md)로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

![Chapter07 Step9 ModelFiles](../../_assets/captures/part2_chapter07_09_model_files.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Zelda FBX, node hierarchy, submesh와 diffuse texture |
| CPU 출력 | Transform이 적용된 vertex/index와 material texture 경로 |
| GPU 출력 | Submesh별 vertex/index buffer, texture SRV와 draw call |

## 구현 흐름

1. Assimp가 FBX scene을 읽고 scene과 root node 유효성을 검사한다.
2. Root에서 child node까지 transform을 누적하며 재귀 순회한다.
3. 각 mesh의 vertex attribute와 index를 runtime 형식으로 변환한다.
4. Material diffuse texture를 읽어 submesh의 SRV에 연결한다.
5. Shared constant buffer와 submesh별 buffer·texture를 묶어 draw한다.

## 핵심 구현

### Scene 검증과 node 순회

```cpp
// Pseudo C++: 유효한 scene만 node tree 순회를 시작
LoadModel(path)
{
    scene = importer.ReadFile(path);
    if (scene == null || scene.root == null)
    {
        return Failure;
    }

    ProcessNode(scene.root, Identity);
}
```

- [Assimp scene 검증과 root 순회](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/ModelLoader.cpp#L69-L90)

### Submesh resource 구성

```cpp
// Pseudo C++: mesh마다 독립 draw resource 구성
CreateSubmesh(meshData)
{
    vertexBuffer = CreateVertexBuffer(meshData.vertices);
    indexBuffer = CreateIndexBuffer(meshData.indices);
    texture = LoadDiffuseTexture(meshData.textureFilename);
    return Submesh(vertexBuffer, indexBuffer, texture);
}
```

- [FBX 입력과 submesh resource 구성](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/ExampleApp.cpp#L47-L87)
- [Mesh vertex와 index 변환](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/ModelLoader.cpp#L187-L270)

## 시각 결과

Texture가 적용된 여러 submesh가 하나의 character와 base scene을 구성한다. UI의
`Use Texture`가 켜진 기본 상태에서 material 경계와 각 submesh의 texture binding을
한 frame에서 확인한다.

## 구현 범위와 한계

- Static FBX mesh와 diffuse texture import만 다룬다.
- Skeletal animation, PBR material과 scene optimization은 포함하지 않는다.
- Zelda bundle의 공개 재배포 권리 근거가 충분하지 않아 공개 후보로 확정하지 않는다.
- Video는 정적 import 결과에 새로운 증거를 추가하지 않아 제외한다.

## 검증

- Debug/Release x64 build/run 성공, 2026-08-03 현재 확인
- Project 폴더 CWD에서 FBX와 diffuse texture load 확인
- Load 실패와 빈 mesh 결과의 오류 전파 확인
- Resize·minimize/restore resource 재생성 경로 확인
- 1282×992 전체 창 screenshot과 공개 title 확인

## 관련 코드

- [Model file 진입점](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/GeometryGenerator.cpp#L513-L530)
- [Node transform 누적과 recursive traversal](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/ModelLoader.cpp#L130-L182)
- [Submesh별 texture binding과 draw](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/ExampleApp.cpp#L282-L300)
- [Resize resource lifetime](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/AppBase.cpp#L572-L610)

## 관련 문서

- [Chapter07 Step9 ModelFiles Example](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/README.md)
- [이전 단계: Chapter07 Step8 SphereMapping UserSolution Demo](07_08_SphereMappingUserSolution.md)
- 다음 단계: Chapter08 Step1 RimLighting
- [Model File Import](../../01_Topics/ModelingAndGeometry/ModelFileImport.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
