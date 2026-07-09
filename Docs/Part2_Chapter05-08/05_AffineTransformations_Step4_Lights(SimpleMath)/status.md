# Status: 05 AffineTransformations Step4 Lights(SimpleMath)

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

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\05_AffineTransformations_Step4_Lights(SimpleMath)`
- archive target: `Part2_Chapter05-08/05_AffineTransformations_Step4_Lights(SimpleMath)`
- 주요 구현: SimpleMath model matrix, inverse-transpose normal matrix, Blinn-Phong lighting, directional/point/spot light
- dependency: DirectX11, ImGui, DirectXTK SimpleMath, vcpkg integration
- asset: 없음

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- 실행 확인: 사용자 확인 전까지 미확인

## 후속 작업

- MSBuild로 Debug/Release build를 확인합니다.
- 사용자가 Debug/Release 실행을 확인하면 이 문서와 Part2 README의 run status를 성공으로 갱신합니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
