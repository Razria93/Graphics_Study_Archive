# Raw to Archive 대응표

이 문서는 `C:\ComputerGraphics` raw/reference repo를 `C:\Graphics_Study_Archive` private archive에서 어떻게 참고할지 정리합니다.

실제 파일 복사 지시가 아닙니다. raw repo는 읽기 전용 참고 자료이며, archive로 옮길 수 있는 항목은 예제별 import manifest와 [migration-board.md](../tracking/migration-board.md)에서 별도로 검토합니다.

## 운영 원칙

- 이동 흐름은 `raw -> private archive -> public` 순서입니다.
- `raw -> public` 직접 이동은 하지 않습니다.
- raw repo의 폴더를 archive repo로 통째로 복사하지 않습니다.
- 강의 원본 코드, 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 archive/public 후보로 확정하지 않습니다.
- 출처나 라이선스가 불명확한 asset은 `검토 필요`로 둡니다.
- 빌드/실행을 직접 확인하지 않은 항목은 `미확인`으로 기록합니다.

## 최상위 대응

| Raw reference | Archive target | 용도 | Import status | 비고 |
| --- | --- | --- | --- | --- |
| `C:\ComputerGraphics\Part1_Chapter01-02` | `Part1_Chapter01-02` | DirectX11 setup, ImGui, bloom 참고 | 반영 완료 | Debug/Release 실행 성공, 촬영 보류 |
| `C:\ComputerGraphics\Part1_Chapter03` | `Part1_Chapter03` | CPU ray tracing fundamentals 참고 | scaffold 작성 | Step별 import 예정 |
| `C:\ComputerGraphics\Part2_Chapter04` | `Part2_Chapter04` | Software rasterization 참고 | 반영 완료 | Step1-Step10 Debug/Release 실행 성공, 촬영 보류 |
| `C:\ComputerGraphics\Part2_Chapter05-08` | `Part2_Chapter05-08` | D3D11 pipeline, modeling, shader toys 참고 | 진행 중 | Step1-Step3 실행 성공 / Step4 SimpleMath 빌드 성공, 실행 미확인 |
| `C:\ComputerGraphics\Part3_Chapter09` | `Part3_Chapter09` | User interaction, picking 참고 | 검토 필요 | build/run 미확인 |
| `C:\ComputerGraphics\Part3_Chapter10_13` | `Part3_Chapter10-13` | Geometry pipeline, texturing, PBR, shadows 참고 | 검토 필요 | archive에서는 chapter-range 이름 사용 |
| `C:\ComputerGraphics\Part3_Chapter10_13_2` | `Part3_Chapter10-13` | Part3 후속/중복 가능 자료 참고 | 검토 필요 | 중복/대체 관계 확인 필요 |
| `C:\ComputerGraphics\Part4_HongLabGraphics` | `Part4_Chapter14-20` | Compute shader, particles, fluids, smoke, cloud 참고 | 검토 필요 | archive에서는 Part4 chapter-range 이름 사용 |
| `C:\ComputerGraphics\Part4_HongLabGraphics_2` | `Part4_Chapter14-20` | Part4 후속/중복 가능 자료 참고 | 검토 필요 | 중복/대체 관계 확인 필요 |
| `C:\ComputerGraphics\_00_Graphics_Portfolio` | `Portfolio_RayTracer` | ray tracing portfolio extension 참고 | 검토 필요 | 대표 작업물 우선 검토 후보 |
| `C:\ComputerGraphics\Docs_Graphics` | `Docs/` | 학습 노트, 계획 문서 참고 | 검토 필요 | private-only 메모와 경로 정보 확인 필요 |
| `C:\ComputerGraphics\export-candidates` | `Docs/_repo/tracking/migration-board.md` | 후보 목록과 검토 메모 참고 | archive 후보 | 실제 파일 복사 공간 아님 |
| `C:\ComputerGraphics\OriginalExamples` | 없음 | 원본 기준점 참고 | 제외 | 통째 이동 금지 |
| `C:\ComputerGraphics\ignore` | 없음 | raw local/private 자료 참고 | 제외 | archive/public 이동 대상 아님 |
| `C:\ComputerGraphics\_clang-format` | 필요 시 별도 검토 | formatting reference | 검토 필요 | 현재 archive 우선순위 아님 |
| `C:\ComputerGraphics\_IBLBaker` | 필요 시 별도 검토 | tool/reference | 검토 필요 | 외부 asset/license 확인 필요 |
| `C:\ComputerGraphics\_Texassemble` | 필요 시 별도 검토 | tool/reference | 검토 필요 | 외부 asset/license 확인 필요 |

## 다음 확인 순서

1. `Portfolio_RayTracer`와 `_00_Graphics_Portfolio`의 대응 관계를 먼저 확인합니다.
2. Part별 대표 P0 예제만 후보로 좁혀 [migration-board.md](../tracking/migration-board.md)에 기록합니다.
3. `.sln`, `.vcxproj`, shader path, asset path가 raw 경로에 의존하는지 확인합니다.
4. 직접 빌드/실행 전까지 build/run 상태는 `미확인`으로 둡니다.
5. archive로 이동한 뒤에도 public 공개 가능성은 [public-readiness.md](../workflow/public-readiness.md)의 체크리스트를 통과한 뒤에만 판단합니다.
