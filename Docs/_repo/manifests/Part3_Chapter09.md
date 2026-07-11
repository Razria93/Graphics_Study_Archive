# Import Manifest: Part3 Chapter09

## Source / Target

- Source: `C:\ComputerGraphics\Part3_Chapter09`
- Target: `Part3_Chapter09`
- Docs target: `Docs/Part3_Chapter09`
- Scope: user interaction, first-person camera, mouse picking, ray collision, quaternion/trackball controls
- Import status: Step1 imported
- Build/run status: 미확인
- Public readiness: 검토 필요

## Raw Inventory

| Raw folder/file | Import decision | Archive name | Note |
| --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | 반영 완료 | same | first-person camera, skybox cubemap, ground texture, selected assets 포함 |
| `09_UserInteraction_Step2_MousePicking` | archive 후보 | same | mainline mouse picking 작업본 |
| `09_UserInteraction_Step2_MousePicking_Debug` | 제외 / reference-only | none | debug/memo 실험 흔적, `memo.txt` 포함 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | archive 후보 | same | 사용자 작업본, source memo 분리 필요 |
| `09_UserInteraction_Step3_MousePickingRayCollision_Debug` | 제외 / reference-only | none | debug variant |
| `09_UserInteraction_Step3_MousePickingRayCollision_Solution` | reference solution 후보 | `09_UserInteraction_Step3_MousePickingRayCollision_ReferenceSolution` | public 후보 아님 |
| `09_UserInteraction_Step4_QuaternianRotation` | archive 후보 | same | raw spelling 유지 여부는 import 시 확인 |
| `09_UserInteraction_Step5_VirtualTrackball` | archive 후보 | same | mainline virtual trackball 작업본 |
| `09_UserInteraction_Step5_VirtualTrackball_Debug` | 제외 / reference-only | none | 회전 벡터 계산 실험, debug 출력 흔적 |
| `09_UserInteraction_Step6_MouseDragMove` | archive 후보 | same | mouse drag movement |
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
- Build/run remains `미확인` until user verifies Debug/Release.

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

Build/run remains `미확인` until user verifies Debug/Release.

## Current Next Action

1. User verifies `09_UserInteraction_Step1_FirstPersonView` Debug/Release build/run.
2. Record the verification result in Step1 `status.md` and tracking docs.
3. Continue to `09_UserInteraction_Step2_MousePicking`.
