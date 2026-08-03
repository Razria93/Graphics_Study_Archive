# Chapter07 Step7 FaceNormals Demo

## 목적

Triangle winding에서 face normal을 계산하고 surface mesh와 분리된 diagnostic line geometry로 방향을 확인한다.

## 책임 범위

- Step7의 triangle-local face normal 할당과 corner 기반 line 표시를 설명한다.
- 일반적인 normal 이론은 [Vertex And Face Normals](../../01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- Step6의 subdivision과 Step8의 spherical mapping 사이에서 winding과 surface direction을 확인한다.

## 결과 미리보기

![Chapter07 Step7 FaceNormals](../../_assets/captures/part2_chapter07_07_face_normals.png)

## 입력과 출력

| 단계 | Vertex | Triangle 또는 line | 설명 |
| --- | ---: | ---: | --- |
| Seed | 36 | 50 triangles | Radius 1.5, slices 5, stacks 5의 위도·경도 sphere |
| Surface | 600 | 200 triangles | 1회 subdivision과 triangle-local face normal |
| Diagnostic | 1,200 | 600 lines | Surface vertex마다 start·end 두 개를 생성 |

## 구현 흐름

1. 50-triangle sphere seed에 subdivision을 한 번 적용한다.
2. Child triangle의 두 edge를 winding 순서로 만든다.
3. 두 edge의 cross product를 세 triangle-local vertex에 같은 face normal로 할당한다.
4. Surface vertex마다 `texcoord.x=0` start와 `1` end를 만든다.
5. Surface는 `TRIANGLELIST`, normal은 별도 buffer의 `LINELIST`로 그린다.
6. Normal shader가 inverse-transpose로 방향을 변환하고 scale만큼 endpoint를 이동한다.

## 핵심 구현

### Winding과 face normal 할당

```cpp
// Pseudo C++: triangle-local face normal 복제
AssignFaceNormal(v0, v1, v2)
{
    edgeA = v1.position - v0.position;
    edgeB = v2.position - v0.position;
    faceNormal = Cross(edgeA, edgeB);

    v0.normal = faceNormal;
    v1.normal = faceNormal;
    v2.normal = faceNormal;
}
```

- [Cross product와 triangle-local face normal 할당](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/GeometryGenerator.cpp#L447-L487)

### Corner 기반 diagnostic line

```cpp
// Pseudo C++: surface vertex에서 face normal 방향 line 생성
AppendNormalLine(vertex)
{
    start = vertex;
    start.marker = 0;

    end = vertex;
    end.marker = 1;

    AppendLine(start, end);
}
```

- [Normal line vertex와 index buffer 생성](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/ExampleApp.cpp#L84-L104)
- [Surface triangle과 normal line topology 분리](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/ExampleApp.cpp#L219-L267)
- [Inverse-transpose와 line endpoint 이동](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/NormalVertexShader.hlsl#L22-L43)

## 시각 결과

Solid surface가 뒤쪽 line을 depth test로 가려 전면 face의 방향을 읽기 쉽게 만든다. Yellow start에서 red endpoint로 이어지는 세 line은 같은 triangle의 세 corner에서 같은 방향을 가리킨다. Silhouette 주변 line이 바깥쪽으로 향하며 일부 triangle만 반대로 뒤집힌 결과는 보이지 않는다.

## 구현 범위와 한계

- Step6의 2-pass 결과를 직접 확장하지 않고 같은 seed에 subdivision을 한 번만 적용한다.
- Face center에서 line 하나를 만들지 않고 triangle corner마다 같은 face normal line을 만든다.
- Step7 수치 검사는 non-degenerate 160개가 outward, inward 0개, degenerate 40개임을 확인했다.
- Degenerate face의 zero-length normal은 길이 0 line으로 남는다. Capture에서 NaN, infinite line과 clipping은 관찰되지 않았다.
- Step5 Sphere는 별도 geometry를 직접 검사해 380개 triangle이 모두 outward임을 확인했다.
- Normal line scale은 가독성을 위한 world-space 값이며 실제 geometry 크기를 뜻하지 않는다.
- Video는 정지 이미지에서 방향과 분포를 판독할 수 있어 제외한다.

## 검증

- Debug/Release x64 build/run 성공, 2026-08-02 현재 확인
- Project 폴더 CWD와 generated wood input load 확인
- Step7 winding: outward 160, inward 0, degenerate 40
- Step5 Sphere winding: outward 380, inward 0, degenerate 0
- Wide·compact resize, minimize/restore와 기본 크기 복원 확인
- 1282×992 PNG의 full decode, metadata와 시각 결과 확인
- Generated wood input은 이전 검증 asset과 같은 SHA-256

## 관련 코드

- [Sphere seed와 1회 subdivision](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/ExampleApp.cpp#L37-L47)
- [Face normal 계산과 child triangle 구성](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/GeometryGenerator.cpp#L415-L490)
- [Normal line buffer 생성](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/ExampleApp.cpp#L84-L104)
- [Surface와 normal draw 분리](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/ExampleApp.cpp#L219-L267)
- [Resize resource lifetime](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/AppBase.cpp#L531-L556)

## 관련 문서

- [Chapter07 Step7 FaceNormals Example](../../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/README.md)
- [이전 단계: Chapter07 Step6 Subdivision Demo](07_06_Subdivision.md)
- [다음 단계: Chapter07 Step8 SphereMapping Demo](07_08_SphereMapping.md)
- [Vertex And Face Normals](../../01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)
- [Procedural Primitive Generation](../../01_Topics/ModelingAndGeometry/ProceduralPrimitiveGeneration.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
