# Status: 11_TexturingTechniques_Step1_Mipmaps

## Current Status

- Code split: 완료
- Build/run: 성공
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 보류
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step1_Mipmaps`를 기준으로 import했습니다.

`C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step1_Mipmaps`는 reference-only snapshot으로 확인했습니다. 파일 목록은 거의 같지만 `BasicPixelShader.hlsl`, `D3D11Utils.cpp`, `ExampleApp.cpp`가 primary와 다릅니다.

## Example Focus

이 예제는 texture mipmap의 LOD를 pixel shader에서 직접 선택하는 흐름을 보여줍니다.

- `dist = length(input.posWorld - eyeWorld)`로 카메라와 fragment의 거리를 계산합니다.
- 거리값을 `lod`로 변환합니다.
- `g_texture0.SampleLevel(g_sampler, input.texcoord, lod)`를 사용해 자동 mip 선택 대신 지정한 mip level로 sampling합니다.
- 정수 사이의 `lod` 값은 인접 mip level 사이를 보간해서 sampling됩니다.

즉, 여기서 보여주는 것은 geometry나 tessellation의 LOD가 아니라 diffuse texture sampling에 사용할 mipmap LOD입니다.

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
- `BasicPixelShader.hlsl` line 57 had an extra `)` in primary raw. The archive copy keeps the primary LOD experiment but removes the syntax error.

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
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Source hash check: 통과, `.vcxproj`/`.filters`는 `.clang-format` 참조 제거와 Release shader setting 보정으로 제외
- Selected asset hash check: 새 asset 없음

## Follow-up

- 다음 import 대상은 `11_TexturingTechniques_Step2_NormalMapping`입니다.
