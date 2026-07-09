# Status: 04 Rasterization Step8 PerspectiveProjection

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

- raw reference: `C:\ComputerGraphics\Part2_Chapter04\04_Rasterization_Step8_PerspectiveProjection`
- archive target: `Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection`
- 주요 구현: orthographic/perspective projection toggle, perspective-correct interpolation toggle, eye-to-screen distance slider, square z sliders
- source 주석 처리: 장문 학습 주석 제거, 짧은 기능 중심 코드로 재정리

## Build 기록

- Debug x64: 성공
- Release x64: 성공
- 실행 확인: 사용자 Debug/Release 실행 확인 완료

## 후속 작업

- 다음 import 후보는 `04_Rasterization_Step9_Shading`입니다.
- capture/video는 사용자 촬영 단계에서 별도로 기록합니다.
