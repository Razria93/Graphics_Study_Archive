# Status: 12_PBR_Step2_PBRModels

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\12_PBR_Step2_PBRModels`를 기준으로 import했습니다.

`Part3_Chapter10_13_2`는 reference-only snapshot으로 확인했으며, 이번 import 기준은 primary raw입니다.

## Example Focus

이 예제는 PBR material pipeline을 외부 model asset에 적용합니다.

- `GeometryGenerator::ReadFromFile(path, "angel_armor.fbx")`로 model mesh를 읽습니다.
- `meshes[0]`에 albedo, emissive, metallic, normal, roughness texture path를 직접 지정합니다.
- HDRI cubemap, BRDF lookup, post-processing, mouse picking/drag control 흐름은 이전 단계의 구조를 이어받습니다.

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
- raw capture/result files

## Asset Status

Already available from previous imports:

- `SampleEnvHDR.dds`
- `SampleSpecularHDR.dds`
- `SampleDiffuseHDR.dds`
- `SampleBrdf.dds`

Missing:

- `Assets/Characters/armored-female-future-soldier/angel_armor.fbx`
- `Assets/Characters/armored-female-future-soldier/angel_armor_albedo.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_e.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_metalness.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_normal.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_roughness.jpg`

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed.
- Release x64 shader model settings were normalized to `5.0` for missing or inconsistent entries.
- Missing character asset was recorded instead of replacing the model path during import.

## Build/Run Verification

사용자 실행 확인 전입니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 미확인 | character asset 누락 확인 필요 |
| Release x64 | 미확인 | character asset 누락 확인 필요 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Selected asset check: character asset 누락 기록

## Follow-up

- `armored-female-future-soldier` asset을 확보하거나, raw 의도와 비교해 대체 model path 사용 여부를 결정해야 합니다.
- public repo로 옮기기 전 model/texture asset license/source를 별도 검토합니다.
