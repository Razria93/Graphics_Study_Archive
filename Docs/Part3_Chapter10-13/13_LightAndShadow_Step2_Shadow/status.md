# 13 Light and Shadow Step2 Shadow Status

## Import

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Raw basis | `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step2_Shadow` |
| Origin reference | `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step2_Shadow` |
| Build/run | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Static Checks

| 항목 | 상태 |
| --- | --- |
| Generated output excluded | 확인 |
| `.clang-format` project reference removed | 확인 |
| Release shader model normalized | 확인 |
| HLSL/HLSLI BOM check | 확인 |
| XML parse | 확인 |
| `git diff --check` | 확인 |

## Assets

| Asset | 상태 | Note |
| --- | --- | --- |
| `Assets/Textures/Cubemaps/HDRI/SampleEnvHDR.dds` | 재사용 | previous Part3 import |
| `Assets/Textures/Cubemaps/HDRI/SampleSpecularHDR.dds` | 재사용 | previous Part3 import |
| `Assets/Textures/Cubemaps/HDRI/SampleDiffuseHDR.dds` | 재사용 | previous Part3 import |
| `Assets/Textures/Cubemaps/HDRI/SampleBrdf.dds` | 재사용 | previous Part3 import |
| `Assets/Characters/armored-female-future-soldier/angel_armor.fbx` | 보류 | character main object 전환 시도 후 sphere baseline 복구 |
| `Assets/Characters/armored-female-future-soldier/angel_armor_*.jpg` | 보류 | PBR texture set |

## User Verification

- Debug x64: 미확인
- Release x64: 미확인
- Runtime behavior: 미확인

## Build Notes

- Debug rebuild failed once during character conversion because this example's `GeometryGenerator::ReadFromFile` declaration requires `(basePath, filename, invertNormals)`.
- The character conversion was reverted, and `ExampleApp.cpp` now matches the raw/origin sphere baseline.
- Debug runtime showed an all-red result and Release did not make the shadow baseline clear with the character material set.
- Main object was restored to the raw/origin sphere baseline so this example can focus on basic shadow mapping.
- Raw/origin `Render()` is currently configured as a camera depth debug view: `DepthPass(m_mainBuffer, m_depthEyeViewProjConstBuffer)` is active and `MainPass()` is commented.
- The red depth-style screen matches that raw/origin render path.
- Archive render path was switched to `DepthPass(m_shadowBuffer, m_lightEyeViewProjConstBuffer)` plus `MainPass()` so Debug/Release can verify the final shadow scene.
- Raw/origin `UseShadow` and point-light position GUI were not fully connected to the final scene path; archive keeps `UseShadow` at the raw/origin behavior level and only keeps the point-light position slider from being overwritten every frame.
