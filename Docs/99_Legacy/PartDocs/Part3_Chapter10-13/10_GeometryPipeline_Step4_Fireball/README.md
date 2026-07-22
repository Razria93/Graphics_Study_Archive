# 10_GeometryPipeline_Step4_Fireball

Billboard/geometry shader 흐름 위에 Shadertoy 스타일 fireball pixel shader를 적용하는 예제입니다.

## Archive Status

| 항목 | 상태 |
| --- | --- |
| Raw source | `C:\ComputerGraphics\Part3_Chapter10_13\10_GeometryPipeline_Step4_Fireball` |
| Archive source | `Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball` |
| Import status | 반영 완료 |
| Build/run | 미확인 |
| Public readiness | 검토 필요 |
| Capture | 보류 |

## Import Notes

- primary raw의 Step4 기본 작업본을 반영했습니다.
- `.vs/`, `x64/`, generated project folder, `.vcxproj.user`, `imgui.ini`, `.clang-format`은 제외했습니다.
- `.clang-format`은 archive에 포함하지 않기 때문에 `.vcxproj`와 `.vcxproj.filters`의 참조도 제거했습니다.
- Release x64 shader setting 누락을 보정했습니다.
- Step4에서 추가로 필요한 `shadertoy_fireball.jpg`만 selected asset으로 포함했습니다.

## Selected Assets

Step1-Step3 shared assets를 재사용하고, fireball texture를 추가합니다.

| Asset | Usage |
| --- | --- |
| `Assets/Textures/shadertoy_fireball.jpg` | fireball shader input texture |
| `Assets/Textures/TreeBillboards/1.png` - `5.png` | billboard texture |
| `Assets/Textures/earth.jpg` | sphere texture |
| `Assets/Textures/blender_uv_grid_2k.png` | ground texture |
| `Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds` | skybox environment |
| `Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds` | diffuse cubemap |
| `Assets/Textures/Cubemaps/skybox/cubemap_specular.dds` | specular cubemap |

## Key Files

- `ExampleApp.cpp`
- `BillboardPoints.cpp`, `BillboardPoints.h`
- `BillboardPointsVertexShader.hlsl`
- `BillboardPointsGeometryShader.hlsl`
- `FireballPixelShader.hlsl`

## Verification

- Static import check: completed
- Debug x64 build/run: 미확인
- Release x64 build/run: 미확인
