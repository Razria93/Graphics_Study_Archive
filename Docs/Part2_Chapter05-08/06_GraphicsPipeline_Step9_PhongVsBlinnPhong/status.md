# Status: 06 GraphicsPipeline Step9 PhongVsBlinnPhong

## 상태 요약

| 항목 | 상태 |
| --- | --- |
| Source split | 완료 |
| Long comments removed from source | 완료 |
| Local memo separated | 완료 |
| Raw diff review | 진행 중 |
| Debug build | 성공 |
| Release build | 성공 |
| Debug run | 미확인 |
| Release run | 미확인 |
| Capture/video | 보류 |
| Public readiness | 검토 필요 |

## 확인 내용

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step9_PhongVsBlinnPhong`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step9_PhongVsBlinnPhong`
- 주요 구현: Phong specular, Blinn-Phong specular, `useBlinnPhong`, half vector, reflection vector, material shininess
- dependency: D3D11, DXGI, D3DCompiler, ImGui, stb_image, vcpkg app-local dependencies
- asset: `crate2_diffuse.png`, `wall.jpg`
- asset public readiness: 검토 필요

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- Release build note: raw project의 HLSL Release shader type 설정이 Step7/Step8과 같은 형태로 누락되어 있었고, archive `.vcxproj`에 Release `ShaderType`과 필요한 `ShaderModel` 설정을 추가했습니다.
- MSBuild note: `pwsh.exe` 미탐지 후 Windows PowerShell fallback이 발생했지만 최종 빌드는 경고 0개, 오류 0개로 완료되었습니다.
- 실행 확인: 사용자 확인 대기

## 후속 작업

- 사용자가 Debug/Release 실행을 확인하면 run status를 성공으로 갱신합니다.
- 06 GraphicsPipeline series는 이 예제까지 반영 완료 상태입니다.
- 다음 후보는 `07_Modeling_*`입니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
