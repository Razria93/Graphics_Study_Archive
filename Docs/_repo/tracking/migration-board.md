# Migration Board

Part1부터 Part4까지 코드/문서 분리, 실행 확인, diff review, refactor 확인, capture 준비 상태를 추적합니다.

| Part | Example | Code split | Build/run | Diff review | Refactor | Capture ready | Note |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Part1 Ch01-02 | `01_DX11InitAndImGui` | 완료 | 성공 | 완료 | 불필요 | 보류 | Debug/Release 실행 성공, capture 보류 |
| Part1 Ch01-02 | `02_Bloom` | 완료 | 성공 | 완료 | 완료 | 보류 | Debug/Release 실행 성공, capture 보류 |
| Part1 Ch03 | `03_Raytracing_Step4_DrawingSphere` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 Ch03 | `03_Raytracing_Step5_PhongShading` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 Ch03 | `03_Raytracing_Step6_PerspectiveView` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 Ch03 | `03_Raytracing_Step7_Triangle` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 Ch03 | `03_Raytracing_Step8_Shadow` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 Ch03 | `03_Raytracing_Step8_Shadow_Square` | 완료 | 성공 | 진행 중 | 완료 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 Ch03 | `03_Raytracing_Step9_BarycentricCordinates` | 완료 | build 성공 / run 미확인 | 진행 중 | 완료 | 보류 | 사용자 실행 확인 대기 |
| Part1 Ch03 | `Step11` | 예정 | 미확인 | 미확인 | 미확인 | 보류 | 2차 후보 |
| Part1 Ch03 | `Step10, Step12-14` | 보류 | 미확인 | 미확인 | 미확인 | 보류 | asset 검토 필요 |
| Part2 Ch04 | `04_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 |  |
| Part2 Ch05-08 | `05_*` - `08_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 |  |
| Part3 Ch09 | `09_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 |  |
| Part3 Ch10-13 | `10_*` - `13_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 |  |
| Part4 Ch14-20 | `14_*` - `20_*` | 예정 | 미확인 | 미확인 | 미확인 | 아니오 |  |

## 상태값

| 필드 | 값 |
| --- | --- |
| Code split | 예정 / 진행 중 / 완료 / 보류 |
| Build/run | 미확인 / build 성공 / 성공 / 실패 |
| Diff review | 미확인 / 진행 중 / 완료 |
| Refactor | 미확인 / 불필요 / 필요 / 완료 |
| Capture ready | 아니오 / 예 / 보류 |
