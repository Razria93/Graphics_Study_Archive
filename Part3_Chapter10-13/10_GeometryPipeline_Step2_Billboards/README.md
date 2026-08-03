# Chapter10 Step2 Billboards

## Overview

Step1의 geometry shader quad를 camera-facing billboard와 texture array로 확장한다. 각 point는 camera 방향 변화에도 정면을 유지하며 primitive ID로 서로 다른 tree texture를 선택한다.

## 실행 진입점

- Solution: `10_GeometryPipeline_Step2_Billboards.sln`
- Application entry: `main.cpp`
- 주요 source: `ExampleApp.cpp`, `BillboardPoints.cpp`, `Camera.cpp`
- Shader: `BillboardPointsGeometryShader.hlsl`, `BillboardPointsPixelShader.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [Camera.cpp](Camera.cpp#L18-L31) | camera-facing model basis 생성 |
| [ExampleApp.cpp](ExampleApp.cpp#L186-L194) | billboard constant data 갱신 |
| [BillboardPoints.cpp](BillboardPoints.cpp#L8-L88) | texture array와 point draw 구성 |
| [BillboardPointsPixelShader.hlsl](BillboardPointsPixelShader.hlsl#L1-L25) | primitive별 texture slice sampling |

## Capture/Result

![Chapter10 Step2 Billboards](../../Docs/_assets/captures/part3_chapter10_02_billboards.png)

서로 다른 tree texture가 같은 draw 경로에서 camera를 향하는 평면으로 출력된다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-04 현재 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD |
| Capture/Result | 완료 | 전체 창 1282×752 PNG |

## Limitations

- Alpha object의 정렬과 overdraw 최적화는 다루지 않는다.
- Tree texture는 강의 제공 runtime dependency로 유지한다.

## Related Docs

- [Geometry Shader And Billboards](../../Docs/01_Topics/ModelingAndGeometry/GeometryShaderAndBillboards.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/10_02_Billboards.md)
- [이전 단계](../10_GeometryPipeline_Step1_GeometryShader/README.md)
- [다음 단계](../10_GeometryPipeline_Step3_NormalLines/README.md)
