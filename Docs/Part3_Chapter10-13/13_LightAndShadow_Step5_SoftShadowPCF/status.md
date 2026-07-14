# 13 Light and Shadow Step5 Soft Shadow PCF Status

## Import

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Raw basis | `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step5_SoftShadowPCF` |
| Origin reference | `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step5_SoftShadowPCF` |
| Reference-only snapshot | `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step5_SoftShadowPCF` |
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
- `BasicPS.hlsl`의 `SampleCmpLevelZero`, `diskSamples64`, `percentLit / 64.0` 흐름이 PCF soft shadow의 핵심입니다.
- `ExampleApp.cpp`에서는 light0 shadow가 활성화되어 Step4보다 PCF 비교가 더 명확하게 보일 수 있습니다.
- Release shader compile 재현성을 위해 project shader setting을 보정했습니다.
