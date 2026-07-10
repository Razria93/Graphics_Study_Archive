# Status: 07 Modeling Step2 DrawingNormals

## Summary

- Archive source: `Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step2_DrawingNormals`
- Status: import 완료, build/run 미확인
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, 기본 texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 제외 |
| Source comment split | 완료 | raw 장문 주석 제거, local-only 문서 생성 |
| Related raw docs review | 부분 완료 | `무제 1.md`의 normal visualization memo 참고 |
| Build/run | 미확인 | 사용자 Visual Studio 확인 필요 |
| Public readiness | 검토 필요 | texture asset과 강의 기반 구조 공개 전 별도 검토 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/source-comments.md`
- `local/Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/study-review.local.md`

## Execution Checklist

- Debug x64 build
- Debug x64 run
- Release x64 build
- Release x64 run
- ImGui `Draw Normals` toggle 확인
- `Normal scale` slider 확인
- normal line mesh가 box 표면 normal 방향으로 표시되는지 확인
