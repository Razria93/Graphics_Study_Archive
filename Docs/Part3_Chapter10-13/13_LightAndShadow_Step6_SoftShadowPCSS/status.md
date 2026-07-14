# 13 Light and Shadow Step6 Soft Shadow PCSS Status

## Import

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Raw basis | `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step6_SoftShadowPCSS` |
| Origin reference | `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step6_SoftShadowPCSS` |
| Reference-only snapshot | `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step6_SoftShadowPCSS` |
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

## Asset Notes

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

- primary raw 기준으로 import했습니다.
- `BasicPS.hlsl`의 `FindBlocker`, `PCSS`, `PCF_Filter`, `penumbraRatio`, `filterRadiusUV` 흐름이 핵심입니다.
- primary raw와 origin/_2의 기능 흐름은 거의 같고, primary raw에는 PCSS 계산 관련 사용자 메모가 추가되어 있습니다.
- Release shader compile 재현성을 위해 project shader setting을 보정했습니다.
