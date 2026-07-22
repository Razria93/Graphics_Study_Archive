# Status: 11_TexturingTechniques_Step3_HeightMapping

## Current Status

- Code split: 완료
- Build/run: 성공
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step3_HeightMapping`를 기준으로 import했습니다.

이번 예제는 Step2 NormalMapping에서 준비되어 있던 `useHeightMap` / `heightScale` 경로가 실제 vertex position 변형으로 이어지는 단계입니다. 따라서 primary raw 기준의 구현을 유지했습니다.

## Example Focus

이 예제는 height map을 사용해 texture 기반 표면 높이 차이를 geometry 위치에 반영하는 흐름을 보여줍니다.

- `BasicVertexShader.hlsl`에서 `g_heightTexture.SampleLevel(...)`로 height 값을 읽습니다.
- `useHeightMap`이 켜져 있으면 `pos += float4(output.normalWorld * height * heightScale, 0.0)`로 vertex position을 이동합니다.
- GUI의 `Use HeightMapping2`와 `HeightScale2`가 ground mesh의 height path를 조절합니다.
- NormalMapping, AO, mip LOD sampling 흐름은 Step2 기반을 유지합니다.

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
- generated project/build output
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- `captured.png`
- raw capture/result files

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed to avoid dangling project items.
- Release x64 shader settings were added where raw project items only specified Debug x64 settings.
- No new runtime asset was added; Step2 PBR textures are reused.

## Build/Run Verification

사용자가 Debug/Release 실행을 확인했습니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 성공 | 사용자 실행 확인 |
| Release x64 | 성공 | 사용자 실행 확인 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Selected asset check: 새 asset 없음

## Follow-up

- 다음 import 대상은 `11_TexturingTechniques_Step4_HDRI`입니다.
