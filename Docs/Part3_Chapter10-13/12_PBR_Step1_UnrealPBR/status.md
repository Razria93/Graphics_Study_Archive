# Status: 12_PBR_Step1_UnrealPBR

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\12_PBR_Step1_UnrealPBR`를 기준으로 import했습니다.

이번 예제는 raw 코드가 `Sample*` HDRI DDS와 `worn-painted-metal-ue` PBR texture set을 직접 참조하므로, 코드 경로를 바꾸지 않고 필요한 runtime asset을 archive 공용 asset으로 포함했습니다.

## Example Focus

이 예제는 Unreal-style PBR material workflow를 확인합니다.

- `BasicPS.hlsl`에서 albedo, normal, AO, metallic, roughness texture를 sampling합니다.
- `SampleEnvHDR.dds`, `SampleSpecularHDR.dds`, `SampleDiffuseHDR.dds`, `SampleBrdf.dds`를 사용해 IBL lighting에 필요한 environment/specular/diffuse/BRDF lookup을 구성합니다.
- `TessellatedQuad` 경로는 height map 기반 displacement 흐름을 이어받습니다.

## Import Scope

Included:

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- source/header files
- HLSL/HLSLI shader files
- selected HDRI DDS runtime assets
- selected `worn-painted-metal-ue` PBR runtime textures

Excluded:

- `.vs/`
- `x64/`
- generated project/build output
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- `worn-painted-metal_preview.jpg`
- raw capture/result files

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed.
- Release x64 shader model settings were normalized to `5.0` for missing or inconsistent entries.
- Runtime asset selection was narrowed to files loaded by the example.

## Build/Run Verification

사용자 실행 확인 전입니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 미확인 | 사용자 실행 확인 필요 |
| Release x64 | 미확인 | 사용자 실행 확인 필요 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Selected asset check: 통과

## Follow-up

- Debug x64와 Release x64 실행 확인 후 status와 migration board를 갱신합니다.
- public repo로 옮기기 전 HDRI/PBR asset license/source를 별도 검토합니다.
