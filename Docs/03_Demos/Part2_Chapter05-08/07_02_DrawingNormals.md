# Chapter07 Step2 DrawingNormals Demo

## 목적

Indexed box surface와 vertex normal 방향의 별도 line geometry를 함께 그려 mesh attribute와 diagnostic geometry가 서로 다른 topology와 draw 경로를 사용하는 과정을 확인한다.

## 책임 범위

- Surface mesh와 normal line buffer의 분리, normal endpoint 계산과 draw 순서를 설명한다.
- 일반 normal 이론은 [Vertex And Face Normals](../../01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

![Chapter07 Step2 DrawingNormals](../../_assets/captures/part2_chapter07_02_drawing_normals.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| Geometry | Face별 vertex를 가진 indexed box surface |
| Surface path | Vertex/index buffer, `TRIANGLELIST`, solid rasterizer |
| Normal path | Position마다 두 endpoint를 가진 별도 buffer, `LINELIST` |
| 기본 UI | `Draw Normals=On`, `Use Texture=Off`, `Wireframe=Off`, normal scale 0.4 |
| 출력 | Gray box surface와 yellow-to-red vertex normal line |

## 구현 흐름

1. `GeometryGenerator::MakeBox()`로 surface mesh를 만든다.
2. Surface vertex마다 start와 end 역할의 vertex 두 개를 복제한다.
3. Surface와 normal line의 buffer와 shader를 별도로 만든다.
4. Surface를 `TRIANGLELIST`로 먼저 그린다.
5. Normal vertex shader가 inverse-transpose normal과 scale로 endpoint를 만든다.
6. Normal geometry를 `LINELIST`로 그린다.

## 핵심 구현

### Normal line buffer 구성

```cpp
// Pseudo C++: surface vertex마다 normal line endpoint 구성
BuildNormalLines(surfaceVertices)
{
    for (vertex : surfaceVertices)
    {
        Append(vertex, StartPoint);
        Append(vertex, EndPoint);
    }
}
```

- [Normal line vertex와 index 구성](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L93-L121)
- [Normal shader와 constant buffer 생성](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L123-L143)

### Surface와 normal draw 분리

```cpp
// Pseudo C++: 서로 다른 topology로 surface와 normal 표시
RenderScene(drawNormals)
{
    DrawIndexed(surface, TriangleList);

    if (drawNormals)
    {
        DrawIndexed(normalLines, LineList);
    }
}
```

- [Surface triangle-list draw](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L301-L315)
- [Normal line-list draw](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L319-L329)
- [Normal endpoint 변환](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/NormalVertexShader.hlsl)

## 시각 결과

비스듬한 box에서 앞·옆·윗면의 normal 분포가 함께 보인다. 각 line은 surface vertex에서 시작하고 yellow에서 red로 변해 방향을 읽을 수 있다. Wide와 compact resize, minimize/restore 뒤에도 surface와 normal line의 위치 관계가 유지된다.

## 구현 범위와 한계

- Face별 vertex를 사용하므로 box 모서리에서 normal을 공유하지 않는다.
- Normal line은 vertex normal의 진단 표현이며 face normal 비교는 Step7에서 다룬다.
- Hidden line 제거와 line anti-aliasing은 구현하지 않는다.
- Video는 정적 결과에 추가 정보를 주지 않아 제외한다.

## 검증

- Debug/Release x64 build/run 성공, 2026-08-02 현재 확인
- Debug shader profile을 Shader Model 5.0으로 명시해 FXC level9 내부 오류 제거
- Exact title, shader와 generated wood load, clean exit 확인
- Wide·compact·minimize/restore 후 viewport와 surface/normal 정합 확인
- 1282×992 PNG의 기술·시각·metadata 검수 완료

## 관련 코드

- [Box surface buffer 생성](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L45-L57)
- [Normal line buffer 생성](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L93-L143)
- [Viewport binding과 render path](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/ExampleApp.cpp#L271-L329)
- [Resize resource lifetime](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/AppBase.cpp#L487-L516)

## 관련 문서

- [Chapter07 Step2 Example README](../../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/README.md)
- [이전 단계: Chapter07 Step1 Demo](07_01_DrawingWireFrames.md)
- 다음 단계: Chapter07 Step3 Grid 문서화 대기
- [Vertex And Face Normals](../../01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
