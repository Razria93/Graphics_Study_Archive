# Status: 11_TexturingTechniques_Step4_HDRI

## Current Status

- Code split: 완료
- Build/run: 성공
- Diff review: 진행 중
- Refactor: 미확인
- Capture ready: 아니오
- Public readiness: 검토 필요

## Source Decision

Primary raw folder `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step4_HDRI`를 기준으로 import했습니다.

`Part3_Chapter10_13`, `Part3_Chapter10_13_2`, `OriginalExamples` 모두 `OutdoorHDRI024_4K-HDR.exr`를 참조하지만, 현재 raw repo 안에서는 해당 EXR 파일을 찾지 못했습니다.

원본 코드의 학습 의도를 유지하기 위해 코드 경로는 바꾸지 않고, replacement HDRI asset을 같은 expected filename으로 배치했습니다.

- Source asset: `DaySkyHDRI015A_1K/DaySkyHDRI015A_1K_HDR.exr`
- Archive path: `Part3_Chapter10-13/Assets/Textures/Cubemaps/HDRI/OutdoorHDRI024_4K-HDR.exr`
- Size: 1,857,902 bytes
- SHA256: `214A51568B3D9F00C2582B3156F3B00AA43409BC1EAF4BBA06019D4E3964E712`
- Public readiness: 검토 필요

## Example Focus

이 예제는 EXR/HDRI image를 읽어 Direct3D texture로 올리는 흐름을 보여줍니다.

- `D3D11Utils.cpp`에서 `DirectXTexEXR.h`를 사용합니다.
- `.exr` 확장자를 감지하면 `ReadEXRImage()`가 `GetMetadataFromEXRFile()`과 `LoadFromEXRFile()`을 호출합니다.
- EXR의 floating-point pixel format을 유지한 뒤 staging texture와 shader resource view를 생성합니다.
- GUI의 exposure/gamma 계열 조절은 이후 HDR pipeline 단계로 이어지는 준비 성격입니다.

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
- Replacement runtime asset was added because the referenced EXR file was not found in raw.

## Build/Run Verification

사용자 실행 확인 기준입니다.

| Configuration | Status | Note |
| --- | --- | --- |
| Debug x64 | 성공 | 사용자 실행 확인 |
| Release x64 | 성공 | 사용자 실행 확인 |

## Observed Debug Failure

사용자 Debug 실행에서 프로그램은 필요한 DLL을 로드했지만, 실행 중 Debug Assertion으로 중단되었습니다.

- Assertion: `can't dereference value-initialized vector iterator`
- 추정 위치: `D3D11Utils::ReadEXRImage()`의 EXR 로딩 실패 이후 빈 `image`/`f32` buffer 처리 경로
- 직접 원인 후보: 코드가 참조하는 `../Assets/Textures/Cubemaps/HDRI/OutdoorHDRI024_4K-HDR.exr` 파일이 archive와 raw repo 모두에서 확인되지 않음
- raw 비교 결과: primary raw의 `ReadEXRImage()` 처리 구조도 archive와 동일하며, raw repo에도 해당 EXR 파일은 없음
- 현재 판단: code migration 자체보다는 runtime asset 누락 이슈였으며, replacement EXR 반영 후 Debug/Release 실행이 정상화됨

## Static Verification

- Excluded file scan: 통과
- `.vcxproj` XML parse: 통과
- `.vcxproj.filters` XML parse: 통과
- Release x64 shader setting check: 통과
- HLSL/HLSLI BOM check: 통과
- Selected asset check: replacement EXR present, SHA256 `214A51568B3D9F00C2582B3156F3B00AA43409BC1EAF4BBA06019D4E3964E712`

## Follow-up

- Debug x64와 Release x64 실행 확인이 완료되었습니다.
- public repo로 옮길 때는 replacement HDRI asset의 license/source를 별도 검토합니다.
