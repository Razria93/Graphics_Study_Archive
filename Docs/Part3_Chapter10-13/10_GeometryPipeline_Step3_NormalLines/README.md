# 10_GeometryPipeline_Step3_NormalLines

Geometry shader로 mesh normal line을 시각화하는 예제입니다.

## Archive Status

| 항목 | 상태 |
| --- | --- |
| Raw source | `C:\ComputerGraphics\Part3_Chapter10_13\10_GeometryPipeline_Step3_NormalLines` |
| Archive source | `Part3_Chapter10-13/10_GeometryPipeline_Step3_NormalLines` |
| Import status | 반영 완료 |
| Build/run | 미확인 |
| Public readiness | 검토 필요 |
| Capture | 보류 |

## Import Notes

- primary raw의 Step3 기본 작업본을 반영했습니다.
- `.vs/`, `x64/`, generated project folder, `.vcxproj.user`, `imgui.ini`, `.clang-format`은 제외했습니다.
- `.clang-format`은 archive에 포함하지 않기 때문에 `.vcxproj`와 `.vcxproj.filters`의 참조도 제거했습니다.
- Step1/Step2와 같은 Release x64 shader setting 누락을 보정했습니다.
- `NormalGeometryShader.hlsl`은 raw project에도 Release x64 Geometry/4.0 설정이 있으므로 유지했습니다.
- `NormalPixelShader.hlsl`와 `NormalVertexShader.hlsl`에는 Release x64 `ShaderType`/`ShaderModel 5.0`을 명시했습니다.

## Selected Assets

Step1/Step2에서 포함한 shared assets를 재사용합니다.

| Asset | Usage |
| --- | --- |
| `Assets/Textures/earth.jpg` | sphere texture |
| `Assets/Textures/blender_uv_grid_2k.png` | ground texture |
| `Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds` | skybox environment |
| `Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds` | diffuse cubemap |
| `Assets/Textures/Cubemaps/skybox/cubemap_specular.dds` | specular cubemap |
| `Assets/Textures/TreeBillboards/1.png` - `5.png` | billboard texture |

## Key Files

- `BasicMeshGroup.cpp`
- `NormalVertexShader.hlsl`
- `NormalGeometryShader.hlsl`
- `NormalPixelShader.hlsl`
- `ExampleApp.cpp`

## Verification

- Static import check: completed
- Debug x64 build/run: 미확인
- Release x64 build/run: 미확인
