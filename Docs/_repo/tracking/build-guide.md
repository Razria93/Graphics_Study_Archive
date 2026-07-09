# Build Verification Table

이 문서는 예제별 build/run 확인 결과를 archive 경로 기준으로 기록합니다. 직접 확인하지 않은 항목은 `미확인`으로 둡니다.

## Status Values

| 값 | 의미 |
| --- | --- |
| 미확인 | 아직 빌드/실행하지 않음 |
| 성공 | 해당 항목 확인 완료 |
| 실패 | 실패 원인과 비고 기록 필요 |
| 보류 | 현재 정리 범위 밖이거나 촬영/사용 여부 확인 대기 |
| 해당 없음 | 해당 검증이 필요하지 않음 |

## Minimum Verification Targets

| Part | Example | Debug x64 | Release x64 | 실행 | 캡처 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| Part2 | `Part2_Chapter05-08/05_AffineTransformations_*` | 성공 | 성공 | 성공 | 보류 | Step1-Step4 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM`-`Step9_PhongVsBlinnPhong` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인 |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, solid/wireframe toggle |
| Part2 | `Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals` | 미확인 | 미확인 | 미확인 | 보류 | 다음 후보 |

## Raw Reference Links

| Archive target | Raw reference | 우선 확인 |
| --- | --- | --- |
| `Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames` | `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step1_DrawingWireFrames` | `MeshData`, `MakeBox()`, rasterizer solid/wire state, `crate2_diffuse.png`, `wall.jpg` |
