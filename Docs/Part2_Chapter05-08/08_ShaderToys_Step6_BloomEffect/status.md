# Status: 08 ShaderToys Step6 BloomEffect

## Summary

- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step6_BloomEffect`
- Related raw notes:
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step6_BloomEffect.md`
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step6_BloomEffect 1.md`
- Reference-only raw variant: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step6-1_BloomEffect_Debug`
- Status: import 완료, build/run 미확인
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, post-processing filter, IBL/model/texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output, debug variant 제외 |
| Asset selection | 완료 | Stonewall IBL DDS, sphere texture, Zelda model/texture 선별 포함 |
| Project reference cleanup | 완료 | 실제 제외된 `.clang-format` project/filter 참조 제거 |
| Path cleanup | 완료 | raw 절대 경로 `c:/zelda/source/`를 archive 상대 경로 `f3d-data/zelda/`로 변경 |
| Source comment split | local note 생성 / source 정리 일부 완료 | raw 학습 메모와 bloom filter chain 내용을 local-only 문서에 분리 |
| Integrity check | 완료 | XML namespace 정상, HLSL/HLSLI BOM 없음, selected asset hash raw와 일치 |
| Build/run | 미확인 | 사용자 Visual Studio Debug/Release 실행 확인 필요 |
| Dependency | 미확인 | DirectXTK DDS loader, Assimp/vcpkg 환경에서 확인 필요 |
| Public readiness | 검토 필요 | Stonewall IBL DDS, Zelda model/texture, 외부 asset 공개 전 검토 필요 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/source-comments.md`
- `local/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/study-review.local.md`

## Execution Checklist

- Debug x64 build: 미확인
- Debug x64 run: 미확인
- Release x64 build: 미확인
- Release x64 run: 미확인
- Stonewall diffuse/specular IBL DDS load: 미확인
- Zelda model load: 미확인
- sphere/character 전환: 미확인
- bloom threshold/strength slider: 미확인
- threshold filter result: 미확인
- blur X/Y filter result: 미확인
- combine result: 미확인
- `Use Texture` toggle: 미확인
- `Wireframe` toggle: 미확인
- `Draw Normals` toggle: 미확인
- `m_viewRot` 조작: 미확인
