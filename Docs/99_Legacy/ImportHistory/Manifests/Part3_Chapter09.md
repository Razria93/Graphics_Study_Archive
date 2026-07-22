# Import Manifest: Part3 Chapter09

> 이 문서는 import 당시 포함/제외 판단 기록입니다.
> 최신 build/run/capture 상태의 기준 문서가 아닙니다.


## Source / Target

- Source: `C:\ComputerGraphics\Part3_Chapter09`
- Target: `Part3_Chapter09`
- Legacy docs target: `Docs/99_Legacy/PartDocs/Part3_Chapter09`
- Scope: user interaction, first-person camera, mouse picking, ray collision, quaternion/trackball controls
- Import status: Step1-Step6 imported
- Build/run status: Step1-Step6 성공
- Public readiness: 검토 필요

## Raw Inventory

| Raw folder/file | Import decision | Archive name | Note |
| --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | 반영 완료 | same | first-person camera, skybox cubemap, ground texture, selected assets 포함 |
| `09_UserInteraction_Step2_MousePicking` | 반영 완료 | same | mainline mouse picking 작업본, `_Debug` 제외 |
| `09_UserInteraction_Step2_MousePicking_Debug` | 제외 / reference-only | none | debug/memo 실험 흔적, `memo.txt` 포함 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | 제외 / reference-only | none | 미완성 작업본, source memo 분리 후보 |
| `09_UserInteraction_Step3_MousePickingRayCollision_Debug` | 제외 / reference-only | none | debug variant |
| `09_UserInteraction_Step3_MousePickingRayCollision_Solution` | 반영 완료 | `09_UserInteraction_Step3_MousePickingRayCollision` | archive 실행 기준, public 후보 아님 |
| `09_UserInteraction_Step4_QuaternianRotation` | 반영 완료 | same | raw spelling 유지, quaternion rotation |
| `09_UserInteraction_Step5_VirtualTrackball` | 반영 완료 | same | mainline virtual trackball 작업본 |
| `09_UserInteraction_Step5_VirtualTrackball_Debug` | 제외 / reference-only | none | 회전 벡터 계산 실험, debug 출력 흔적 |
| `09_UserInteraction_Step6_MouseDragMove` | 반영 완료 | same | mouse drag movement |
| `Assets` | 선별 포함 | `Part3_Chapter09/Assets` | 실행에 필요한 asset만 포함 |
| `copy_dlls.py` | 검토 필요 | none | 실행에 필요할 때만 포함 |

## Step1 Candidate: FirstPersonView

Raw path:

- `C:\ComputerGraphics\Part3_Chapter09\09_UserInteraction_Step1_FirstPersonView`

Include candidates:

- `09_UserInteraction_Step1_FirstPersonView.sln`
- `09_UserInteraction_Step1_FirstPersonView.vcxproj`
- `09_UserInteraction_Step1_FirstPersonView.vcxproj.filters`
- `*.cpp`, `*.h`
- `*.hlsl`, `*.hlsli`

Exclude from Step1:

- `.vs/`
- generated folder `09_UserI.15e78e61/`
- `x64/`
- `.clang-format`
- `09_UserInteraction_Step1_FirstPersonView.vcxproj.user`
- `imgui.ini`

Selected asset candidates:

- `Assets/Textures/blender_uv_grid_2k.png`
- `Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds`
- `Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds`
- `Assets/Textures/Cubemaps/skybox/cubemap_specular.dds`

Asset references found in source:

- `ExampleApp.cpp`
  - `../Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds`
  - `../Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds`
  - `../Assets/Textures/Cubemaps/skybox/cubemap_specular.dds`
  - `../Assets/Textures/blender_uv_grid_2k.png`

Dependency notes:

- `Common.hlsli` is included as a non-build item in the raw project.
- Raw project uses C++17.
- Shader profile settings exist for Debug/Release x64 and should be preserved.
- Build/run was verified by user for Debug/Release.

## Variant Rules

- `_Debug` folders are excluded by default and kept as reference-only.
- `_Solution` folders may be imported as `ReferenceSolution` only when useful for comparison.
- `ReferenceSolution` is private archive comparison material, not a public-ready candidate.
- Source comments are not fully cleaned in phase 1 unless they contradict current code behavior.

## Step1 Import Result

Imported:

- `09_UserInteraction_Step1_FirstPersonView` source/project/shader files
- selected skybox cubemap DDS assets
- selected ground texture asset

Adjusted:

- Removed `.clang-format` from archive project/filter references because the file is intentionally excluded.
- Added `Part3_Chapter09/Directory.Build.props` for repo-local `ThirdParty/stb` include path.

Build/run was verified by user for Debug/Release.

## Step2 Import Result

Imported:

- `09_UserInteraction_Step2_MousePicking` source/project/shader files
- existing selected Step1 assets reused

Excluded:

- `09_UserInteraction_Step2_MousePicking_Debug`
- `memo.txt`
- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`

Adjusted:

- Removed `.clang-format` from archive project/filter references because the file is intentionally excluded.

Build/run was verified by user for Debug/Release.

## Step3 Import Result

Imported:

- `09_UserInteraction_Step3_MousePickingRayCollision_Solution` source/project/shader files as archive `09_UserInteraction_Step3_MousePickingRayCollision`
- existing selected Step1 skybox assets reused
- `Assets/Textures/earth.jpg`

Excluded:

- `09_UserInteraction_Step3_MousePickingRayCollision` mainline incomplete work variant
- `09_UserInteraction_Step3_MousePickingRayCollision_Debug`
- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`

Adjusted:

- Removed `.clang-format` from archive project/filter references because the file is intentionally excluded.

Notes:

- mainline `ExampleApp.cpp` contains source comments/TODOs that should be separated or rewritten during the later documentation cleanup pass.
- `_Solution` is used as the archive runnable code because the other two variants were not complete.

Build/run was verified by user for Debug/Release.

## Step4 Import Result

Imported:

- `09_UserInteraction_Step4_QuaternianRotation` source/project/shader files
- existing selected Step1 skybox assets reused
- existing Step3 `Assets/Textures/earth.jpg` reused

Excluded:

- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`

Adjusted:

- Removed `.clang-format` from archive project/filter references because the file is intentionally excluded.

Notes:

- Raw spelling `QuaternianRotation` is preserved for folder/project consistency.
- Documentation uses the standard term quaternion rotation.

Build/run was verified by user for Debug/Release.

## Step5 Import Result

Imported:

- `09_UserInteraction_Step5_VirtualTrackball` source/project/shader files
- existing selected Step1 skybox assets reused
- existing Step3 `Assets/Textures/earth.jpg` reused

Excluded:

- `09_UserInteraction_Step5_VirtualTrackball_Debug`
- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`

Adjusted:

- Removed `.clang-format` from archive project/filter references because the file is intentionally excluded.

Notes:

- `_Debug` differs only in `ExampleApp.cpp` and contains extra intermediate vector/debug output flow, so mainline is used as the archive runnable code.

Build/run was verified by user for Debug/Release.

## Step6 Import Result

Imported:

- `09_UserInteraction_Step6_MouseDragMove` source/project/shader files
- existing selected Step1 skybox assets reused
- existing Step3 `Assets/Textures/earth.jpg` reused

Excluded:

- `.vs/`, generated folder, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`

Adjusted:

- Removed `.clang-format` from archive project/filter references because the file is intentionally excluded.

Build/run was verified by user for Debug/Release.

## Current Next Action

1. Chapter09 import completion status is recorded in this manifest.
2. Chapter10-13 primary/reference source decisions are maintained in `Part3_Chapter10-13.md`.
3. 최신 build/run/capture 상태는 `Docs/03_Verification/build-run-matrix.md`에서 관리한다.
