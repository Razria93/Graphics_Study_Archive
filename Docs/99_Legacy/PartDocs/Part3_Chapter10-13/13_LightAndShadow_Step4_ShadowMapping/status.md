# 13 Light and Shadow Step4 Shadow Mapping Status

## Import

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Raw basis | `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step4_ShadowMapping` |
| Origin reference | `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step4_ShadowMapping` |
| Reference-only snapshot | `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step4_ShadowMapping` |
| Build/run | 성공 |
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

- Debug x64: 성공
- Release x64: 성공
- Runtime behavior: 사용자 실행 확인

## Build Notes

- primary raw 기준으로 import했습니다.
- origin과 `_2`는 shadow lookup 구현부가 TODO/comment 형태에 가까워 reference-only로 유지합니다.
- `BasicPS.hlsl`의 light-space projection, shadow map sampling, bias 비교 코드가 이 예제의 핵심입니다.
- Release shader compile 재현성을 위해 project shader setting을 보정했습니다.
