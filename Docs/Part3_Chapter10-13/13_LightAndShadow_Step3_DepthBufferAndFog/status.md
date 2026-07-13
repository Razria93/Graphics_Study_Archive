# 13 Light and Shadow Step3 Depth Buffer and Fog Status

## Import

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Raw basis | `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step3_DepthBufferAndFog` |
| Origin reference | `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step3_DepthBufferAndFog` |
| Build/run | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Static Checks

| 항목 | 상태 |
| --- | --- |
| Generated output excluded | 확인 |
| `_Solution` project files excluded | 확인 |
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
| `Assets/Textures/blender_uv_grid_2k.png` | 재사용 | previous Part3 import |

## User Verification

- Debug x64: 미확인
- Release x64: 미확인
- Runtime behavior: 미확인

## Build Notes

- Primary raw 기준으로 import했습니다.
- raw/origin 모두 sphere main object를 사용하므로 character conversion은 적용하지 않았습니다.
- raw의 `Fog` slider range는 origin보다 낮은 `0.0` to `1.0`이며, 사용자 작업본 기준으로 유지합니다.
- Release shader compile 재현성을 위해 project shader setting을 보정했습니다.
