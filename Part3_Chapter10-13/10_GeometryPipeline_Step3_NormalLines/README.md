# Chapter10 Step3 NormalLines

## Overview

Mesh vertex의 position과 normal을 geometry shader의 line primitive로 시각화한다. 기본 실행 상태에서 diagnostic normal을 함께 표시해 vertex normal의 방향과 분포를 바로 확인한다.

## 실행 진입점

- Solution: `10_GeometryPipeline_Step3_NormalLines.sln`
- Application entry: `main.cpp`
- 주요 source: `BasicMeshGroup.cpp`, `ExampleApp.cpp`
- Shader: `NormalVertexShader.hlsl`, `NormalGeometryShader.hlsl`, `NormalPixelShader.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [BasicMeshGroup.cpp](BasicMeshGroup.cpp#L100-L143) | normal shader와 diagnostic geometry 준비 |
| [BasicMeshGroup.cpp](BasicMeshGroup.cpp#L174-L202) | surface 이후 normal line draw |
| [NormalGeometryShader.hlsl](NormalGeometryShader.hlsl#L29-L66) | position에서 normal 방향 line 생성 |
| [ExampleApp.cpp](ExampleApp.cpp#L420-L436) | normal과 wireframe UI 상태 |

## Capture/Result

![Chapter10 Step3 NormalLines](../../Docs/_assets/captures/part3_chapter10_03_normal_lines.png)

구 표면의 vertex에서 바깥쪽으로 뻗는 normal line이 surface와 함께 표시된다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-04 현재 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD |
| Capture/Result | 완료 | Draw Normals 기본 On |

## Limitations

- Normal line은 diagnostic geometry이며 실제 lighting 결과가 아니다.
- Dense mesh에서는 line overlap이 증가한다.

## Related Docs

- [Vertex And Face Normals](../../Docs/01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/10_03_NormalLines.md)
- [이전 단계](../10_GeometryPipeline_Step2_Billboards/README.md)
- [다음 단계](../10_GeometryPipeline_Step4_Fireball/README.md)
