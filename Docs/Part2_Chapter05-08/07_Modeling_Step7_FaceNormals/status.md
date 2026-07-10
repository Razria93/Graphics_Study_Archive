# Status: 07 Modeling Step7 FaceNormals

## Summary

- Archive source: `Part2_Chapter05-08/07_Modeling_Step7_FaceNormals`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step7_FaceNormals`
- Status: import 완료, build/run 성공
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 제외 |
| Project reference cleanup | 완료 | 실제 제외한 `.clang-format`의 project/filter 참조 제거 |
| Source comment split | local note 생성 / source 정리 보류 | raw 재현성을 우선해 source comment는 유지. local-only 문서에 위치와 정리 방향 기록 |
| Integrity check | 완료 | XML namespace 정상, HLSL/HLSLI BOM 없음, texture asset hash raw와 일치 |
| Build/run | 성공 | 사용자 Visual Studio Debug/Release 실행 확인 |
| Public readiness | 검토 필요 | texture asset과 강의 기반 구조 공개 전 별도 검토 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/source-comments.md`
- `local/Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/study-review.local.md`

## Execution Checklist

- Debug x64 build: 확인 완료
- Debug x64 run: 확인 완료
- Release x64 build: 확인 완료
- Release x64 run: 확인 완료
- face normal shading 정상 표시: 확인 완료
- `Use Texture` toggle: 확인 완료
- `Wireframe` toggle: 확인 완료
- `Draw Normals` toggle: 확인 완료
- `Normal scale` slider: 확인 완료
