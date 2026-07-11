# Status: 11_TexturingTechniques_Step5_HDRPipeline

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step5_HDRPipeline`를 기준으로 import했습니다.

`Part3_Chapter10_13`, `Part3_Chapter10_13_2`, `OriginalExamples` 모두 `OutdoorEnvHDR.dds`, `OutdoorDiffuseHDR.dds`, `OutdoorSpecularHDR.dds`를 참조하지만, 현재 raw repo 안에서는 해당 `Outdoor*` 파일을 찾지 못했습니다.

원본 코드의 학습 의도를 유지하기 위해 코드 경로는 바꾸지 않고, raw에 존재하는 `Sample*` HDR DDS asset을 expected filename으로 배치했습니다.

## Example Focus

이 예제는 HDR environment map과 post-process pipeline을 연결하는 흐름을 보여줍니다.

- `CubeMapping`은 HDR DDS cubemap을 skybox/environment map으로 사용합니다.
- `PostProcess` 계열 pass는 render target 결과를 받아 exposure/gamma/bloom 처리를 적용합니다.
- `D3D11Utils::CreateDDSTexture()`는 `CreateDDSTextureFromFileEx()` 경로로 DDS texture를 읽습니다.
- `CombinePS.hlsl`, `BloomDownPS.hlsl`, `BloomUpPS.hlsl`이 post-process 조합에 사용됩니다.

## Import Scope

Included:

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- source/header files
- HLSL/HLSLI shader files
- selected HDR DDS replacement assets
- selected ground color compatibility asset

Excluded:

- `.vs/`
- `x64/`
- generated project/build output
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- raw capture/result files

## Changes From Raw

- `.clang-format` file was excluded.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed.
- Release x64 shader model settings were normalized to `5.0` for missing or inconsistent entries.
- `SampleEnvHDR.dds`, `SampleDiffuseHDR.dds`, and `SampleSpecularHDR.dds` were copied under the `Outdoor*` filenames used by the code.
- `Bricks075A_1K-PNG_Color.png` was copied under the `Bricks075A_4K_Color.png` filename used by the code.

## Build/Run Verification

사용자 실행 확인 전입니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 미확인 | replacement DDS/PBR asset 반영 후 실행 확인 필요 |
| Release x64 | 미확인 | replacement DDS/PBR asset 반영 후 실행 확인 필요 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Selected asset check: 통과

## Follow-up

- 사용자가 Debug x64와 Release x64 실행을 확인합니다.
- public repo로 옮길 때는 replacement HDR/PBR asset의 license/source를 별도 검토합니다.
