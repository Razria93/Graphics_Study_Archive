# Status: 08 ShaderToys Step5 FresnelEffect

## Summary

- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect`
- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step5_FresnelEffect`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step5_FresnelEffect.md`
- Status: import 완료, build/run 미확인
- Capture: 보류

## Migration

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Source/project import | 완료 | `.sln`, `.vcxproj`, `.filters`, source, shader, IBL cubemap/texture asset 반영 |
| Raw-only exclusion | 완료 | `.vs/`, generated folder, `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 제외 |
| Asset selection | 완료 | 실행 경로의 Stonewall diffuse/specular IBL DDS와 sphere texture 선별 포함 |
| Project reference cleanup | 완료 | 실제 제외된 `.clang-format` project/filter 참조 제거 |
| Path cleanup | 완료 | raw source의 private/sample absolute path comments 제거 |
| Source comment split | local note 생성 / source 정리 일부 완료 | raw 학습 메모와 Fresnel 핵심 구현 내용을 local-only 문서에 분리 |
| Integrity check | 완료 | XML namespace 정상, HLSL/HLSLI BOM 없음, selected asset hash raw와 일치 |
| Build/run | 미확인 | 사용자 Visual Studio Debug/Release 실행 확인 필요 |
| Dependency | 미확인 | DirectXTK DDS loader 환경에서 확인 필요 |
| Public readiness | 검토 필요 | Stonewall IBL DDS와 texture asset 공개 전 검토 필요 |

## Local-only Notes

아래 문서는 `.gitignore` 대상이며 commit하지 않습니다.

- `local/Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/source-comments.md`
- `local/Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/study-review.local.md`

## Execution Checklist

- Debug x64 build: 미확인
- Debug x64 run: 미확인
- Release x64 build: 미확인
- Release x64 run: 미확인
- `CubemapTextures/Stonewall_diffuseIBL.dds` load: 미확인
- `CubemapTextures/Stonewall_specularIBL.dds` load: 미확인
- sphere render: 미확인
- Fresnel specular 변화: 미확인
- `Material FresnelR0` slider: 미확인
- material diffuse/specular/shininess slider: 미확인
- `Use Texture` toggle: 미확인
- `Wireframe` toggle: 미확인
- `Draw Normals` toggle: 미확인
- `m_viewRot` 조작: 미확인
