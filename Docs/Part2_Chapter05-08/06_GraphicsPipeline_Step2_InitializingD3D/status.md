# Status: 06 GraphicsPipeline Step2 InitializingD3D

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

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step2_InitializingD3D`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D`
- 주요 구현: D3D11 window initialization, swap chain, render target, depth stencil, shader compilation, colored cube rendering
- dependency: D3D11, DXGI, D3DCompiler, ImGui, vcpkg app-local dependencies
- asset: 없음

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- 실행 확인: 사용자 Debug/Release 실행 확인 완료
- 이슈: 첫 Debug build에서 HLSL 파일의 UTF-8 BOM 때문에 `fxc`가 `Illegal character in shader file`을 보고했습니다. shader 파일을 UTF-8 no BOM으로 다시 저장한 뒤 Debug/Release build 모두 성공했습니다.

## 후속 작업

- 다음 후보 `06_GraphicsPipeline_Step3_ConstantBuffer`의 raw 구조와 dependency를 확인합니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
