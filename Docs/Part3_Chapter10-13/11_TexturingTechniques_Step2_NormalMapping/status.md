# Status: 11_TexturingTechniques_Step2_NormalMapping

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step2_NormalMapping`를 기준으로 import했습니다.

`OriginalExamples`와 비교했을 때 primary raw의 `BasicPixelShader.hlsl`에는 normal texture sampling, tangent-space normal 변환, TBN 적용 실험이 더 진행되어 있습니다. 이 예제의 archive 목적은 사용자가 실제로 구현한 Normal Mapping 흐름을 실행 가능한 코드로 보관하는 것이므로 primary raw를 기준으로 삼았습니다.

## Example Focus

이 예제는 diffuse texture만으로 표현하기 어려운 표면 디테일을 normal map으로 보강하는 흐름을 보여줍니다.

- `BasicPixelShader.hlsl`에서 `g_normalTexture.SampleLevel(...)`로 normal map을 읽습니다.
- texture RGB를 `2.0 * normalTex - 1.0`으로 변환해 signed normal 범위로 바꿉니다.
- TBN basis를 사용해 texture-space normal을 world-space lighting normal로 변환합니다.
- `useNormalMap`, `useAOMap`, `useHeightMap` GUI toggle로 normal/AO/height 관련 경로를 확인합니다.

## Import Scope

Included:

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- source/header files
- HLSL/HLSLI shader files
- runtime에 필요한 PBR texture 8개

Excluded:

- `.vs/`
- `x64/`
- generated project/build output
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- `captured.png`
- raw capture/result files
- 사용하지 않는 PBR texture와 asset metadata files

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed to avoid dangling project items.
- Release x64 shader settings were added where raw project items only specified Debug x64 settings.
- Runtime PBR textures were selected by direct source references instead of copying the whole raw asset folder.

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
- Selected asset check: PBR texture 8개 포함

## Follow-up

- 사용자가 Debug x64와 Release x64 실행을 확인한 뒤 build/run 상태를 갱신합니다.
