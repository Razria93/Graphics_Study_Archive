# Status: 06 GraphicsPipeline Step4 Shaders

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

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step4_Shaders`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders`
- 주요 구현: vertex/pixel shader data flow, texture coordinate semantic, pixel shader constant buffer
- dependency: D3D11, DXGI, D3DCompiler, ImGui, vcpkg app-local dependencies
- asset: 없음
- 제외: raw의 `ColorVertexShader.cso`, `ColorVertexShader.asm`는 archive에 포함하지 않음

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- 실행 확인: 사용자 Debug/Release 실행 확인 완료

## 후속 작업

- `06_GraphicsPipeline_Step5_Texturing`은 사용자 Debug/Release 실행 확인까지 완료했습니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
