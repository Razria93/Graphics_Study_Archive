# Chapter07 Step5 Sphere UserSolution Demo

## 목적

위·아래 반구를 독립적으로 생성하고 equator에서 결합하는 사용자 sphere 구현을 확인한다. 일반 stack·slice grid와 달리 pole band를 별도 triangle fan으로 처리해 면적 0 pole triangle을 피하는 선택을 설명한다.

## 책임 범위

- UserSolution의 반구 합성, pole 처리, UV와 index 구성을 설명한다.
- 일반적인 procedural primitive 이론은 [Procedural Primitive Generation](../../01_Topics/ModelingAndGeometry/ProceduralPrimitiveGeneration.md)으로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.
- ReferenceSolution은 private 비교 근거로만 사용하며 코드·capture를 공개하지 않는다.

## 결과 미리보기

![Chapter07 Step5 Sphere UserSolution](../../_assets/captures/part2_chapter07_05_sphere_user_solution.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 생성 입력 | Radius 1.0, slices 10, hemisphere stacks 10 |
| Vertex | `2 × 11 × 11 = 242`, position·radial normal·UV |
| Triangle | 반구당 190, 전체 380 |
| Index | 1,140, `DXGI_FORMAT_R16_UINT` |
| 기본 UI | `Wireframe=On`, `Use Texture=Off`, `Draw Normals=Off` |
| 출력 | Equator에서 결합한 두 반구와 pole fan의 wireframe sphere |

## 구현 흐름

1. +X 방향 equator vector를 회전해 위쪽 반구의 ring을 만든다.
2. Latitude마다 `slices + 1`개의 vertex를 만들어 UV seam을 분리한다.
3. 마지막 latitude는 north pole로 모으고 slice마다 triangle 하나만 연결한다.
4. 첫 반구 vertex 수를 half offset으로 기록한다.
5. -X 방향 equator에서 같은 절차로 아래쪽 반구를 만든다.
6. 아래쪽 index에 half offset을 더하고 south pole band를 별도로 마감한다.
7. 두 반구의 vertex·index를 GPU buffer로 옮겨 `TRIANGLELIST`로 그린다.

## 핵심 구현

### 반구별 ring과 pole vertex

```cpp
// Pseudo C++: equator에서 pole까지 반구별 latitude ring 생성
BuildHemisphere(sign, slices, stacks)
{
    for (stack = 0; stack <= stacks; ++stack)
    {
        for (slice = 0; slice <= slices; ++slice)
        {
            AppendRotatedVertex(sign, stack, slice);
        }
    }
}
```

- [위쪽 반구 vertex와 UV 생성](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/GeometryGenerator.cpp#L279-L339)
- [아래쪽 반구 vertex와 wrap UV 생성](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/GeometryGenerator.cpp#L377-L436)

### Pole fan과 half offset

```cpp
// Pseudo C++: 일반 band는 두 triangle, pole band는 한 triangle
BuildHemisphereIndices(offset, slices, stacks)
{
    for (stack = 0; stack < stacks; ++stack)
    {
        for (slice = 0; slice < slices; ++slice)
        {
            if (stack == stacks - 1)
            {
                AppendPoleTriangle(offset, stack, slice);
            }
            else
            {
                AppendQuadTriangles(offset, stack, slice);
            }
        }
    }
}
```

- [위쪽 반구 body와 pole triangle](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/GeometryGenerator.cpp#L342-L371)
- [아래쪽 반구 offset과 triangle](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/GeometryGenerator.cpp#L439-L468)
- [Sphere 파라미터와 GPU buffer 연결](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/ExampleApp.cpp#L42-L52)

## 시각 결과

Wireframe은 equator를 중심으로 위·아래 latitude ring이 이어지고, longitude 방향의 slice가 pole로 수렴하는 구조를 보여준다. Pole band가 triangle 한 개씩으로 닫혀 있어 ReferenceSolution의 일반 quad 분할에서 생기는 면적 0 triangle을 피한다.

## 구현 범위와 한계

- UserSolution은 242 vertices와 380 triangles를 사용한다.
- ReferenceSolution은 전구 단일 loop로 496 vertices와 900 triangles를 만들며 pole에 면적 0 triangle 30개를 포함한다.
- 비교 결과는 구현 선택을 검증하기 위한 private 근거이며 Reference 코드를 정본에 복제하지 않는다.
- Equator와 pole 위치에는 UV seam·반구 분리를 위한 중복 vertex가 존재한다.
- 아래쪽 U 범위는 `1.5`에서 `0.5`이며 wrap sampler가 필요하다.
- 380개 triangle의 winding을 radial direction과 수치 비교한 결과 모두 outward이며 inward·degenerate triangle은 없다.
- 입력 범위 guard와 runtime 분할 수 조정은 포함하지 않는다.
- Video는 정적 wireframe이 topology를 충분히 설명하므로 제외한다.

## 검증

- Debug/Release x64 build/run 성공, 2026-08-02 현재 확인
- Shader Model 5.0과 exact application title 확인
- Wide·compact resize, minimize/restore와 기본 크기 복원 확인
- 1282×992 PNG의 기술·시각·metadata 검수 완료
- Generated wood input은 이전 검증 asset과 같은 SHA-256

## 관련 코드

- [Sphere 호출과 GPU buffer 생성](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/ExampleApp.cpp#L42-L52)
- [위쪽 반구 생성](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/GeometryGenerator.cpp#L279-L371)
- [아래쪽 반구 생성](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/GeometryGenerator.cpp#L377-L468)
- [Surface와 optional normal draw](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/ExampleApp.cpp#L225-L281)
- [Resize resource lifetime](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/AppBase.cpp#L485-L529)

## 관련 문서

- [Chapter07 Step5 UserSolution Example](../../../Part2_Chapter05-08/07_Modeling_Step5_Sphere_UserSolution/README.md)
- [이전 단계: Chapter07 Step4 Demo](07_04_Cylinder.md)
- [다음 단계: Chapter07 Step6 Subdivision Demo](07_06_Subdivision.md)
- [Procedural Primitive Generation](../../01_Topics/ModelingAndGeometry/ProceduralPrimitiveGeneration.md)
- [Vertex And Face Normals](../../01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
