# Status: 08 ShaderToys Step7 Shadertoy

## Summary

- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step7_Shadertoy`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\@ShaderToy.md`
- Status: import 완료, build/run 성공
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, Shadertoy texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 제외 |
| Asset selection | 완료 | 프로젝트 등록 이미지 `ojwD8.jpg`, `wall.jpg`와 코드 직접 로드 asset `shadertoytexture0.jpg` 포함 |
| Project reference cleanup | 완료 | 실제 제외된 `.clang-format` project/filter 참조 제거, `SeascapePixelShader.hlsl` / `StarPixelShader.hlsl` Release x64 shader profile 보정 |
| Path cleanup | 완료 | 비활성 주석의 `c:/zelda/` 절대 경로를 상대 경로 예시로 변경 |
| Source comment split | local note 생성 | raw 주석/관련 문서 맥락은 local-only 문서에 분리 |
| Integrity check | 완료 | XML namespace 정상, HLSL/HLSLI BOM 없음, selected asset hash raw와 일치 |
| Build/run | 성공 | 사용자 Visual Studio Debug/Release 실행 확인 |
| Dependency | 확인 완료 | Debug 실행 중 `assimp-vc143-mtd.dll` 탐색 오류가 있었으나 Clean/Rebuild 후 정상 동작 확인 |
| Public readiness | 검토 필요 | Shadertoy 기반 shader code와 texture asset 공개 전 license/attribution 확인 필요 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/source-comments.md`
- `local/Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/study-review.local.md`

## Execution Checklist

- Debug x64 build: 확인 완료
- Debug x64 run: 확인 완료
- Release x64 build: 확인 완료
- Release x64 run: 확인 완료
- `shadertoytexture0.jpg` load: 확인 완료
- fullscreen shader output: 확인 완료
- `iTime` animation: 확인 완료
- active `StarPixelShader` output: 확인 완료
- optional `SeascapePixelShader` switch: 미확인

## Issue Notes

- Release x64 build에서 `SeascapePixelShader.hlsl`이 기본 `vs_2_0` profile로 해석되어 `SV_TARGET` semantic 오류가 발생했습니다.
- raw와 `OriginalExamples`의 `.vcxproj` 모두 `SeascapePixelShader.hlsl` / `StarPixelShader.hlsl`에 Debug x64 shader profile만 있고 Release x64 설정이 누락되어 있었습니다.
- archive에서는 해당 두 shader에 Release x64 `ShaderType=Pixel`, `ShaderModel=5.0`을 추가했습니다.
- Debug 실행 시 `assimp-vc143-mtd.dll` 탐색 오류가 있었으나 Clean/Rebuild 후 app-local dependency가 정리되어 Debug/Release 모두 정상 동작을 확인했습니다.
