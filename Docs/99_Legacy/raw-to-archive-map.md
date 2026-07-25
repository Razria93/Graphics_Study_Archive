# Raw to Archive Map

이 문서는 `C:\ComputerGraphics` raw/reference repo를 `C:\Graphics_Study_Archive` private archive에서 어떻게 참조했는지 기록한 legacy snapshot이다.

실제 파일 복사 지시서가 아니다. raw repo는 읽기 전용 참고 자료이며, archive로 옮길 수 있는 항목은 예제별 import manifest와 현재 Work Unit 정책에서 별도로 판단한다.

## 운영 원칙

- 자료 이동 흐름은 `raw -> private archive -> public subset` 순서를 따른다.
- `raw -> public` 직접 이동은 하지 않는다.
- raw repo의 폴더를 archive repo로 통째로 복사하지 않는다.
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 archive/public 후보로 확정하지 않는다.
- 출처와 라이선스가 불명확한 asset은 `검토 필요`로 둔다.
- build/run/capture 최신 상태는 이 문서가 아니라 `Docs/02_Verification/`에서 확인한다.

## Top-Level Map

| Raw reference | Archive target | 용도 | Legacy import status | 비고 |
| --- | --- | --- | --- | --- |
| `C:\ComputerGraphics\Part1_Chapter01-02` | `Part1_Chapter01-02` | DirectX11 setup, ImGui, bloom 참고 | 반영 완료 | 최신 검증 상태는 Verification 기준 |
| `C:\ComputerGraphics\Part1_Chapter03` | `Part1_Chapter03` | CPU ray tracing fundamentals 참고 | 반영 완료 | 최신 검증 상태는 Verification 기준 |
| `C:\ComputerGraphics\Part2_Chapter04` | `Part2_Chapter04` | Software rasterization 참고 | 반영 완료 | 최신 검증 상태는 Verification 기준 |
| `C:\ComputerGraphics\Part2_Chapter05-08` | `Part2_Chapter05-08` | D3D11 pipeline, modeling, shader toys 참고 | 반영 완료 | 최신 검증 상태는 Verification 기준 |
| `C:\ComputerGraphics\Docs_Graphics` | `Docs/`, `local/` | 학습 노트, 계획 문서 참고 | 진행 기록 | private-only 메모는 tracked Docs로 직접 승격하지 않는다 |
| `C:\ComputerGraphics\Part3_Chapter09` | `Part3_Chapter09` | User interaction, picking 참고 | 반영 완료 | 최신 검증 상태는 Verification 기준 |
| `C:\ComputerGraphics\Part3_Chapter10_13` | `Part3_Chapter10-13` | Geometry pipeline, texturing, PBR, shadows 참고 | 반영 완료 | `_2`는 reference-only snapshot으로 본다 |
| `C:\ComputerGraphics\Part4_HongLabGraphics` | `Part4_Chapter14-20` | Compute shader, particles, fluids, animation, physics 참고 | 반영 완료 | `_2`와 `OriginalExamples`는 reference-only baseline으로 본다 |
| `C:\ComputerGraphics\_00_Graphics_Portfolio` | `Portfolio_RayTracer` | ray tracing portfolio extension 참고 | 검토 필요 | 포트폴리오 대표 작업물 후보 |

## 다음 확인 순서

1. 현재 archive의 build/run/capture 상태는 `Docs/02_Verification/`에서 확인한다.
2. raw 예제는 복사 전 파일, asset, result, capture 성격을 분류한다.
3. source 내부 학습 메모는 `local/` 검토 자료로 분리한다.
4. archive 문서에는 직접 이해한 실행 흐름, 핵심 코드, 검증 상태만 재작성한다.
5. public 가능성은 `Docs/05_Publication/`과 `Docs/06_Policies/publication-policy.md` 기준으로 나중에 별도 판단한다.
