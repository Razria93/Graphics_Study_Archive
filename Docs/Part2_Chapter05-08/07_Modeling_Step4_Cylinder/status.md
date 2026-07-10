# Status: 07 Modeling Step4 Cylinder

## Summary

- Archive source: `Part2_Chapter05-08/07_Modeling_Step4_Cylinder`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step4_Cylinder`
- Excluded raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step4_Cylinder_Backup`
- Status: import 완료, build/run 미확인
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output, backup folder 제외 |
| Source comment split | 재검토 필요 | raw 재현성 복구 이후 source 주석 정리는 보류. local-only 문서에 위치와 정리 방향 기록 |
| Project asset setup | raw 기준으로 복구 | `crate2_diffuse.png`, `wall.jpg`는 raw project와 동일하게 `Image` item으로 유지. 자동 output 복사 설정은 제거 |
| Asset integrity | 완료 | texture asset은 raw 원본 binary와 동일하게 복구 |
| Related raw docs review | 완료 | Step4 전용 study note는 확인되지 않았고, portfolio planning 문서의 후보 언급만 확인 |
| Build/run | 미확인 | 사용자 Visual Studio 확인 필요 |
| Public readiness | 검토 필요 | texture asset과 강의 기반 구조 공개 전 별도 검토 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/07_Modeling_Step4_Cylinder/source-comments.md`
- `local/Part2_Chapter05-08/07_Modeling_Step4_Cylinder/study-review.local.md`

## Execution Checklist

- Debug x64 build
- Debug x64 run
- Release x64 build
- Release x64 run
- cylinder mesh가 정상 표시되는지 확인
- `Use Texture` toggle 확인
- `Wireframe` toggle 확인
- `Draw Normals` toggle 확인
- `Normal scale` slider 확인
