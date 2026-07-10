# Status: 08 ShaderToys Step1 RimLighting

## Summary

- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step1_RimLighting`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step1_RimLighting.md`
- Status: import 완료, build/run 성공
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, texture/model asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 제외 |
| Asset selection | 완료 | `stanford_dragon.stl`, root texture 3개 포함 |
| Project reference cleanup | 완료 | 실제 제외된 `.clang-format` project/filter 참조 제거 |
| Path cleanup | 완료 | 실행에 필요 없는 개인 절대경로 sample model 주석 제거 |
| Source comment split | local note 생성 / source 정리 일부 완료 | raw 학습 메모와 shader 핵심 내용을 local-only 문서에 분리 |
| Integrity check | 완료 | XML namespace 정상, HLSL/HLSLI BOM 없음, selected asset hash raw와 일치 |
| Build/run | 성공 | 사용자 Visual Studio Debug/Release 실행 확인 |
| Dependency | 확인 완료 | Assimp/vcpkg 환경에서 사용자 Debug/Release 실행 확인 |
| Public readiness | 검토 필요 | model/texture asset과 외부 링크 공개 전 검토 필요 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/source-comments.md`
- `local/Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/study-review.local.md`

## Execution Checklist

- Debug x64 build: 확인 완료
- Debug x64 run: 확인 완료
- Release x64 build: 확인 완료
- Release x64 run: 확인 완료
- `stanford_dragon.stl` load: 확인 완료
- rim lighting 표시: 확인 완료
- `Rim Strength` slider: 확인 완료
- `Rim Color` slider: 확인 완료
- `Rim Power` slider: 확인 완료
- `Use Smoothstep` toggle: 확인 완료
- `Use Texture` toggle: 확인 완료
- `Wireframe` toggle: 확인 완료
- `Draw Normals` toggle: 확인 완료