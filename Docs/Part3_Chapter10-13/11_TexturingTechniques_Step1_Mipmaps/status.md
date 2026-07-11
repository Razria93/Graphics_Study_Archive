# Status: 11_TexturingTechniques_Step1_Mipmaps

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step1_Mipmaps`를 기준으로 import했습니다.

이후 예제 의도를 확인하기 위해 `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\11_TexturingTechniques_Step1_Mipmaps`도 비교했습니다. OriginalExamples 기준으로 Step1 Mipmaps의 핵심은 GUI의 `Mipmaps Level` slider로 `mipmapLevel`을 조절하고, pixel shader에서 `SampleLevel(..., mipmapLevel)`로 직접 mip level을 선택하는 것입니다.

## Example Focus

이 예제는 texture mipmap의 LOD를 GUI에서 직접 선택하는 흐름을 보여줍니다.

- `ExampleApp::UpdateGUI()`에서 `Mipmaps Level` slider가 `m_mainSphere.m_basicPixelConstantData.mipmapLevel`을 조절합니다.
- `BasicPixelShader.hlsl`에서 `g_texture0.SampleLevel(g_sampler, input.texcoord, mipmapLevel)`을 사용합니다.
- 즉, 여기서 보여주는 것은 geometry나 tessellation LOD가 아니라 diffuse texture sampling에 사용할 mipmap LOD입니다.

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
- `11_Textu.a4a576ca/`
- `.vcxproj.user`
- `.clang-format`
- `imgui.ini`
- `captured.png`
- generated shader objects and executable output
- raw capture/result files

## Changes From Raw

- `.clang-format` file was excluded.
- `captured.png` was excluded as a raw execution/capture output.
- `.vcxproj` and `.vcxproj.filters` references to `.clang-format` were removed to avoid dangling project items.
- Release x64 shader settings were added where raw project items only specified Debug x64 settings.
- The added Release settings cover billboard shaders, normal shaders, fireball shader, TessellatedQuad VS/HS/DS/PS shader items, and missing vertex shader model entries.
- Primary raw had a distance-based `lod` experiment and a disabled mipmap GUI slider. To match the Step1 Mipmaps example intent, `ExampleApp.cpp` and `BasicPixelShader.hlsl` were restored to the OriginalExamples behavior.

## Build/Run Verification

The source behavior changed after the previous Debug/Release confirmation. Re-run is required.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 미확인 | OriginalExamples 의도 복구 후 사용자 실행 확인 필요 |
| Release x64 | 미확인 | OriginalExamples 의도 복구 후 사용자 실행 확인 필요 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 확인 필요
- Source hash check: `ExampleApp.cpp` and `BasicPixelShader.hlsl` now match OriginalExamples behavior
- Selected asset hash check: 새 asset 없음

## Follow-up

- 사용자가 Debug x64와 Release x64 실행을 다시 확인한 뒤 build/run 상태를 갱신합니다.
