# Migration Board

Part1부터 Part4까지 코드/문서 분리, 실행 확인, diff review, refactor 확인, capture 준비 상태를 추적합니다.

## Status Values

| Field | Values |
| --- | --- |
| Code split | 예정 / 진행 중 / 완료 / 보류 |
| Build/run | 미확인 / 빌드 성공 / 성공 / 실패 |
| Diff review | 미확인 / 진행 중 / 완료 |
| Refactor | 미확인 / 불필요 / 필요 / 완료 |
| Capture ready | 아니오 / 예 / 보류 |

## Current Board

| Part | Example | Code split | Build/run | Diff review | Refactor | Capture ready | Note |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Part2 Ch05-08 | `05_AffineTransformations_*` | 완료 | 성공 | 진행 중 | 완료 | 보류 | Step1-Step4 사용자 Debug/Release 실행 확인 |
| Part2 Ch05-08 | `06_GraphicsPipeline_Step1_COM`-`Step9_PhongVsBlinnPhong` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, texture asset public readiness 검토 필요 |
| Part2 Ch05-08 | `07_Modeling_Step1_DrawingWireFrames` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 확인, procedural box mesh, solid/wireframe rasterizer state |
| Part2 Ch05-08 | `07_Modeling_Step2_DrawingNormals` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | 다음 후보 |
| Part2 Ch05-08 | `07_Modeling_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | mesh generation/modeling |
| Part2 Ch05-08 | `08_ShaderToys_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | shader toy effects |
| Part3 Ch09 | `09_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | Part2 이후 진행 |
| Part3 Ch10-13 | `10_*`-`13_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | Part2 이후 진행 |
| Part4 Ch14-20 | `14_*`-`20_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 | Part2 이후 진행 |
