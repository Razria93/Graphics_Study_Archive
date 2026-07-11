# Status: 11_TexturingTechniques_Step4_HDRI

## Current Status

- Code split: 완료
- Build/run: 미확인
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step4_HDRI`를 기준으로 import했습니다.

`Part3_Chapter10_13`, `Part3_Chapter10_13_2`, `OriginalExamples` 모두 `OutdoorHDRI024_4K-HDR.exr`를 참조하지만, raw repo 안에서는 해당 EXR 파일을 찾지 못했습니다. 원본 코드의 학습 의도를 유지하기 위해 경로를 임의로 바꾸지 않았고, 실행 확인 단계에서 asset 누락 여부를 확인하도록 기록합니다.

## Example Focus

이 예제는 EXR/HDRI image를 읽어서 Direct3D texture로 올리는 흐름을 보여줍니다.

- `D3D11Utils.cpp`에서 `DirectXTexEXR.h`를 사용합니다.
- `.exr` 확장자를 감지하면 `ReadEXRImage()`가 `GetMetadataFromEXRFile()`과 `LoadFromEXRFile()`을 호출합니다.
- EXR의 floating-point pixel format을 유지해 staging texture와 shader resource view를 생성합니다.
- GUI에서는 exposure/gamma 계열 조절이 이어지는 HDR pipeline의 준비 단계로 볼 수 있습니다.

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
- No new runtime asset was added because the referenced EXR file was not found in raw.

## Build/Run Verification

사용자 실행 확인 전입니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 미확인 | `OutdoorHDRI024_4K-HDR.exr` 누락 여부 확인 필요 |
| Release x64 | 미확인 | `OutdoorHDRI024_4K-HDR.exr` 누락 여부 확인 필요 |

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Selected asset check: referenced EXR asset not found in raw

## Follow-up

- 사용자가 Debug x64와 Release x64 실행을 확인합니다.
- 실행 실패 시 `OutdoorHDRI024_4K-HDR.exr`의 원본 위치나 대체 asset 기준을 먼저 확인합니다.
