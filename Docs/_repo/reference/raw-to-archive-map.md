# Raw to Archive Map

이 문서는 `C:\ComputerGraphics` raw/reference repo를 `C:\Graphics_Study_Archive` private archive에서 어떻게 참고할지 정리합니다.

실제 파일 복사 지시가 아닙니다. raw repo는 읽기 전용 참고 자료이며, archive로 옮길 수 있는 항목은 예제별 import manifest와 migration board에서 별도로 검토합니다.

## 운영 원칙

- 이동 흐름은 `raw -> private archive -> public` 순서입니다.
- `raw -> public` 직접 이동은 하지 않습니다.
- raw repo의 폴더를 archive repo로 통째로 복사하지 않습니다.
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 archive/public 후보로 확정하지 않습니다.
- 출처와 라이선스가 불명확한 asset은 `검토 필요`로 둡니다.
- 빌드/실행을 직접 확인하지 않은 항목은 `미확인`으로 기록합니다.

## Top-Level Map

| Raw reference | Archive target | 용도 | Import status | 비고 |
| --- | --- | --- | --- | --- |
| `C:\ComputerGraphics\Part1_Chapter01-02` | `Part1_Chapter01-02` | DirectX11 setup, ImGui, bloom 참고 | 반영 완료 | Debug/Release 실행 성공, 촬영 보류 |
| `C:\ComputerGraphics\Part1_Chapter03` | `Part1_Chapter03` | CPU ray tracing fundamentals 참고 | 반영 완료 | Step4-Step14 실행 확인 완료 |
| `C:\ComputerGraphics\Part2_Chapter04` | `Part2_Chapter04` | Software rasterization 참고 | 반영 완료 | Step1-Step10 Debug/Release 실행 성공 |
| `C:\ComputerGraphics\Part2_Chapter05-08` | `Part2_Chapter05-08` | D3D11 pipeline, modeling, shader toys 참고 | 진행 중 | `05_*`, `06_*`, `07_Modeling_Step1_DrawingWireFrames`-`Step3_Grid`, `07_Modeling_Step5_*`-`Step9` 실행 성공. `07_Modeling_Step4_Cylinder` import 완료/실행 미확인. `08_ShaderToys_Step1_RimLighting` import 완료/build-run 성공. `08_ShaderToys_Step2_Cubemapping` import 완료/build-run 성공 |
| `C:\ComputerGraphics\Docs_Graphics` | `Docs/`, `local/` | 학습 노트, 계획 문서 참고 | 진행 중 | private-only 메모는 local로 분리 |
| `C:\ComputerGraphics\Part3_Chapter09` | `Part3_Chapter09` | User interaction, picking 참고 | 검토 필요 | Part2 이후 진행 |
| `C:\ComputerGraphics\Part3_Chapter10_13` | `Part3_Chapter10-13` | Geometry pipeline, texturing, PBR, shadows 참고 | 검토 필요 | archive에서는 chapter-range 이름 사용 |
| `C:\ComputerGraphics\Part4_HongLabGraphics` | `Part4_Chapter14-20` | Compute shader, particles, fluids, smoke, cloud 참고 | 검토 필요 | archive에서는 chapter-range 이름 사용 |
| `C:\ComputerGraphics\_00_Graphics_Portfolio` | `Portfolio_RayTracer` | ray tracing portfolio extension 참고 | 검토 필요 | 대표 작업물 후보 |

## 다음 확인 순서

1. 현재 예제의 build/run 상태를 먼저 확정합니다.
2. 다음 raw 예제는 복사 전 파일/asset/result/capture를 분류합니다.
3. source 내부 학습 메모는 local-only 문서로 분리합니다.
4. archive 문서에는 실행 흐름, 핵심 코드, 검증 상태만 남깁니다.
5. public 가능성은 [public-readiness.md](../workflow/public-readiness.md) 기준으로 나중에 별도 판단합니다.
