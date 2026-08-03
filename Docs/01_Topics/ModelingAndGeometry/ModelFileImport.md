# Model File Import

## 목적

Model file import는 외부 파일의 scene, node, mesh와 material 표현을 runtime의 geometry와 GPU resource 구조로 변환하는 과정이다.

## 책임 범위

- Scene graph, node transform, submesh와 material 변환의 일반 원리를 설명한다.
- Step9의 실제 Assimp 호출과 DirectX11 resource 구성은 Example README로 위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`의 [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)으로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos`의 [상세 Demo](../../03_Demos/Part2_Chapter05-08/07_09_ModelFiles.md)로 위임한다.

## 핵심 개념

### Scene과 node 계층

Model file은 하나의 mesh만 저장하지 않을 수 있다. Scene root 아래의 node는 여러 child와 mesh reference를 가지며, 각 node의 local transform은 부모에서 누적한 transform과 합성한다. 따라서 mesh vertex를 world 또는 model 기준으로 옮길 때 node tree의 순회 순서와 행렬 convention을 함께 확인한다.

### Mesh와 submesh

Importer가 반환한 mesh마다 position, normal, texture coordinate와 index를 runtime vertex 형식으로 변환한다. Material이 참조하는 diffuse texture는 mesh와 연결하되, 파일 누락과 decode 실패를 resource 생성 실패로 전파한다.

```cpp
// Pseudo C++: scene tree를 runtime mesh 목록으로 변환
ImportNode(node, parentTransform)
{
    transform = node.localTransform * parentTransform;

    for (meshReference : node.meshes)
    {
        meshes.push_back(ConvertMesh(meshReference, transform));
    }

    for (child : node.children)
    {
        ImportNode(child, transform);
    }
}
```

## 실패 경계

- Scene 또는 root node가 없으면 순회를 시작하지 않는다.
- Mesh 결과가 비어 있으면 첫 원소 접근과 빈 GPU buffer 생성을 막는다.
- Normal이나 texture coordinate가 없을 수 있으므로 attribute 존재를 확인한다.
- Texture 파일과 GPU resource 생성 결과를 검증한 뒤 draw 목록에 추가한다.

## 한계

- Importer가 지원하는 file format과 attribute는 library와 build 설정에 의존한다.
- Animation, skeletal skinning, PBR material과 runtime optimization은 별도 주제다.
- Model file을 읽을 수 있다는 사실만으로 asset의 공개 재배포 권리가 보장되지는 않는다.

## 관련 문서

- [Chapter07 Step9 ModelFiles Example](../../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/README.md)
- [Chapter07 Step9 ModelFiles Demo](../../03_Demos/Part2_Chapter05-08/07_09_ModelFiles.md)
- [Modeling And Geometry](README.md)
