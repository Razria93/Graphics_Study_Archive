# 10_GeometryPipeline_Step1_GeometryShader

Geometry shader를 사용해 point primitive에서 billboard quad를 생성하는 예제입니다.

## Archive Status

| 항목 | 상태 |
| --- | --- |
| Raw source | `C:\ComputerGraphics\Part3_Chapter10_13\10_GeometryPipeline_Step1_GeometryShader` |
| Archive source | `Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader` |
| Import status | 반영 완료 |
| Build/run | 미확인 |
| Public readiness | 검토 필요 |
| Capture | 보류 |

## Import Notes

- 기본 작업본 `10_GeometryPipeline_Step1_GeometryShader`만 반영했습니다.
- `_Solution` variant는 아직 섞지 않았고, 필요 시 reference solution으로 별도 분리합니다.
- `.vs/`, `x64/`, generated project folder, `.vcxproj.user`, `imgui.ini`, `.clang-format`은 제외했습니다.
- `.clang-format`은 archive에 포함하지 않기 때문에 `.vcxproj`와 `.vcxproj.filters`의 참조도 제거했습니다.
- 실행에 필요한 selected texture/cubemap asset만 `Part3_Chapter10-13/Assets` 아래에 포함했습니다.

## Selected Assets

| Asset | Usage |
| --- | --- |
| `Assets/Textures/earth.jpg` | sphere texture |
| `Assets/Textures/blender_uv_grid_2k.png` | ground texture |
| `Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds` | skybox environment |
| `Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds` | diffuse cubemap |
| `Assets/Textures/Cubemaps/skybox/cubemap_specular.dds` | specular cubemap |

## Key Files

- `BillboardPoints.cpp`, `BillboardPoints.h`
- `BillboardPointsVertexShader.hlsl`
- `BillboardPointsGeometryShader.hlsl`
- `BillboardPointsPixelShader.hlsl`
- `ExampleApp.cpp`

## Verification

- Static import check: completed
- Debug x64 build/run: 미확인
- Release x64 build/run: 미확인
