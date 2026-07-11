# Status: 06 GraphicsPipeline Step1 COM

## 상태 요약

| 항목 | 상태 |
| --- | --- |
| Source split | 완료 |
| Long comments removed from source | 완료 |
| Local memo separated | 완료 |
| Raw diff review | 진행 중 |
| Debug build | 성공 |
| Release build | 성공 |
| Debug run | 성공 |
| Release run | 성공 |
| Capture/video | 보류 |
| Public readiness | 검토 필요 |

## 확인 내용

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step1_COM`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM`
- 주요 구현: D3D11 device creation, feature level selection, WRL ComPtr ownership/reset
- dependency: D3D11, WRL, Windows SDK
- asset: 없음

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- 실행 확인: 사용자 Debug/Release 실행 확인 완료

## 후속 작업

- `06_GraphicsPipeline_Step2_InitializingD3D`는 사용자 Debug/Release 실행 확인까지 완료했습니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
