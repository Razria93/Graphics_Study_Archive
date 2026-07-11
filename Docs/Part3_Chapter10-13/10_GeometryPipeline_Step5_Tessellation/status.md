# Status: 10_GeometryPipeline_Step5_Tessellation

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\10_GeometryPipeline_Step5_Tessellation`를 기준으로 import했습니다.

`C:\ComputerGraphics\Part3_Chapter10_13_2\10_GeometryPipeline_Step5_Tessellation`는 reference-only snapshot으로 확인했습니다. 파일 목록은 같지만 `TessellatedQuadHS.hlsl`, `TessellatedQuadDS.hlsl`, `TessellatedQuad.h`가 primary와 다릅니다.

## Import Scope

Included:

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- source/header files
- HLSL/HLSLI shader files

Excluded:

- `.vs/`
- `x64/`
- `10_Geome.6c7355f6/`
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- generated shader objects and executable output
- raw capture/result files

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed to avoid dangling project items.
- Release x64 shader settings were added where raw project items only specified Debug x64 settings.
- The added Release settings cover billboard shaders, normal shaders, fireball shader, and TessellatedQuad VS/HS/DS/PS shader items.

## Build/Run Verification

사용자 확인 전까지 아래 항목은 `미확인`으로 유지합니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 미확인 | 사용자 실행 확인 필요 |
| Release x64 | 미확인 | 사용자 실행 확인 필요 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- HLSL/HLSLI BOM check: 통과
- Source hash check: 통과, `.vcxproj`/`.filters`는 `.clang-format` 참조 제거와 Release shader setting 보정으로 제외
- Selected asset hash check: 새 asset 없음

## Follow-up

- 사용자가 Debug x64와 Release x64 실행을 확인한 뒤 build/run 상태를 갱신합니다.
