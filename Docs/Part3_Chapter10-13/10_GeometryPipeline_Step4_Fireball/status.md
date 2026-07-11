# Status: 10_GeometryPipeline_Step4_Fireball

## Current Status

- Code split: 완료
- Build/run: 성공
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 보류
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\10_GeometryPipeline_Step4_Fireball`를 기준으로 import했습니다.

## Import Scope

Included:

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- source/header files
- HLSL/HLSLI shader files
- `Assets/Textures/shadertoy_fireball.jpg`

Excluded:

- `.vs/`
- `x64/`
- `10_Geome.e90734f0/`
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- generated shader objects and executable output
- raw capture/result files

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed to avoid dangling project items.
- Release x64 billboard shader project items only specified Debug x64 shader settings. Added Release x64 `ShaderType`/`ShaderModel 5.0` for `BillboardPointsVertexShader.hlsl`, `BillboardPointsPixelShader.hlsl`, and `BillboardPointsGeometryShader.hlsl`.
- `FireballPixelShader.hlsl` only specified Debug x64 shader settings. Added Release x64 `ShaderType`/`ShaderModel 5.0`.
- `NormalGeometryShader.hlsl`, `NormalPixelShader.hlsl`, and `NormalVertexShader.hlsl` had incomplete Release x64 shader settings. Added missing Release x64 `ShaderType`/`ShaderModel 5.0`.

## Build/Run Verification

사용자가 Debug x64와 Release x64 실행을 모두 확인했습니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 성공 | 사용자 실행 확인 |
| Release x64 | 성공 | 사용자 실행 확인 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- HLSL/HLSLI BOM check: 통과
- Source hash check: 통과, `.vcxproj`/`.filters`는 `.clang-format` 참조 제거와 Release shader setting 보정으로 제외
- Selected asset hash check: 통과

## Follow-up

- 다음 import 대상은 `10_GeometryPipeline_Step5_Tessellation`입니다.
