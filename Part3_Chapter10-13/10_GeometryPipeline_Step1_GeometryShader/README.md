# Chapter10 Step1 GeometryShader

## Overview

하나의 point primitive를 geometry shader에서 네 vertex의 quad strip으로 확장한다. 수정된 구현은 `TriangleStream`의 연결 규칙을 명확히 지키면서 기존 사각형 결과를 유지한다.

## 실행 진입점

- Solution: `10_GeometryPipeline_Step1_GeometryShader.sln`
- Application entry: `main.cpp`
- 주요 source: `ExampleApp.cpp`, `BillboardPoints.cpp`
- Shader: `BillboardPointsVertexShader.hlsl`, `BillboardPointsGeometryShader.hlsl`, `BillboardPointsPixelShader.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [BillboardPoints.cpp](BillboardPoints.cpp#L50-L76) | `POINTLIST` draw와 shader binding |
| [BillboardPointsGeometryShader.hlsl](BillboardPointsGeometryShader.hlsl#L29-L53) | point에서 네 corner의 quad strip 생성 |
| [BillboardPointsVertexShader.hlsl](BillboardPointsVertexShader.hlsl#L1-L30) | point position과 constant data 전달 |

## Capture/Result

![Chapter10 Step1 GeometryShader](../../Docs/_assets/captures/part3_chapter10_01_geometry_shader.png)

흰색과 검은색 point가 각각 하나의 화면 정렬 quad로 확장된다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-04 현재 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD |
| Capture/Result | 완료 | 전체 창 1282×752 PNG |

## Limitations

- 고정 크기 quad 확장만 다룬다.
- Transparent sorting과 대량 particle 성능 비교는 범위 밖이다.

## Related Docs

- [Geometry Shader And Billboards](../../Docs/01_Topics/ModelingAndGeometry/GeometryShaderAndBillboards.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/10_01_GeometryShader.md)
- [다음 단계](../10_GeometryPipeline_Step2_Billboards/README.md)
