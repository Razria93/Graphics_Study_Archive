# Status: 06 GraphicsPipeline Step5 Texturing LightingSelf

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

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step5_Texturing_LightingSelf`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing_LightingSelf`
- raw project filename: `06_GraphicsPipeline_Step5_Texturing.sln`, `06_GraphicsPipeline_Step5_Texturing.vcxproj`
- 주요 구현: texture sampling, normal matrix, light constant buffer, ambient/diffuse/specular lighting, attenuation
- dependency: D3D11, DXGI, D3DCompiler, ImGui, stb_image, vcpkg app-local dependencies
- asset: `crate2_diffuse.png`, `wall.jpg`
- asset public readiness: 검토 필요

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- MSBuild note: `pwsh.exe` 미탐지 후 Windows PowerShell fallback이 발생했지만 최종 빌드는 경고 0개, 오류 0개로 완료되었습니다.
- 실행 확인: 사용자 Debug/Release 실행 확인 완료

## 후속 작업

- 다음 후보는 `06_GraphicsPipeline_Step6_Lighting`입니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
