# Status: 08 ShaderToys Step3 EnvironmentMapping

## Summary

- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step3_EnvironmentMapping`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step3_EnvironmentMapping.md`
- Status: import 완료, build/run 미확인
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, cubemap/model/texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 제외 |
| Asset selection | 완료 | 실행 경로의 `NightPath.dds`, Humus readme, Zelda model/texture 선별 포함 |
| Project reference cleanup | 완료 | 실제 제외된 `.clang-format` project/filter 참조 제거 |
| Path cleanup | 완료 | raw 절대 경로 `c:/zelda/source/`를 archive 상대 경로 `f3d-data/zelda/`로 변경 |
| Source comment split | local note 생성 / source 정리 일부 완료 | raw 학습 메모와 environment mapping 핵심 구현 내용을 local-only 문서에 분리 |
| Integrity check | 완료 | XML namespace 정상, HLSL/HLSLI BOM 없음, selected asset hash raw와 일치 |
| Build/run | 미확인 | 사용자 Visual Studio Debug/Release 실행 확인 필요 |
| Dependency | 미확인 | DirectXTK DDS loader, Assimp/vcpkg 환경에서 확인 필요 |
| Public readiness | 검토 필요 | `NightPath.dds`, Zelda model/texture, 외부 asset 공개 전 검토 필요 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping/source-comments.md`
- `local/Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping/study-review.local.md`

## Execution Checklist

- Debug x64 build: 미확인
- Debug x64 run: 미확인
- Release x64 build: 미확인
- Release x64 run: 미확인
- `CubemapTextures/HumusTextures/NightPath.dds` load: 미확인
- skybox cubemap 표시: 미확인
- Zelda model load: 미확인
- model texture 표시: 미확인
- environment reflection 표시: 미확인
- `Use Reflection` toggle: 미확인
- `Use Texture` toggle: 미확인
- `Wireframe` toggle: 미확인
- `Draw Normals` toggle: 미확인
- `m_viewRot` 조작: 미확인
