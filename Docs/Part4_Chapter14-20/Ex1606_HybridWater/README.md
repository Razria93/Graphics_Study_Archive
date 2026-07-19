# Ex1606 HybridWater

## 목적

`Ex1606_HybridWater`는 particle 기반 water simulation과 grid 기반 projection을 함께 사용하는 hybrid water 예제입니다. 입자는 `StructuredBuffer`로 관리하고, grid texture는 velocity, pressure, divergence, density, signed distance field를 담습니다. 렌더링은 particle, density volume, marching cubes, SDF raycasting 경로를 선택해서 확인할 수 있습니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1606` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | 없음 |
| Build/run status | Debug/Release 확인 완료 |
| Archive perf profile | 64^3 grid, 256K max particles, 1024 new particles, 1 substep |

확인할 동작:

- 기본 화면에서 SDF raycasting 결과와 bounding box가 렌더링되는지 확인합니다.
- `Source`, `NumNewPts` 값을 조절했을 때 particle sourcing 양상이 바뀌는지 확인합니다.
- `RenderParticles`, `RenderDensity`, `RenderMarchingCubes`, `RenderWired`, `RenderRaycasting` 토글이 표시 모드를 바꾸는지 확인합니다.
- Debug/Release x64 모두 command argument `1606`으로 확인합니다.

## 핵심 흐름

1. `InitScene()`에서 64^3 grid texture를 velocity, pressure, divergence, density, boundary condition, signed distance 용도로 초기화합니다.
2. `Texture3D::InitNoiseF16()`으로 procedural noise texture를 생성합니다.
3. 최대 256 * 1024개 particle buffer와 active particle counter를 초기화합니다.
4. `BitonicSort` buffer를 이용해 particle을 grid index 기준으로 정렬합니다.
5. `Update()`에서 projection pass와 particle step을 substep 단위로 실행합니다.
6. `Projection()`은 divergence, Jacobi pressure solve, pressure application을 수행합니다.
7. `ParticleStep()`은 particle velocity update, particle spawn/advection, sorting, first index update, particle-to-grid sampling을 수행합니다.
8. `Render()`에서 GUI 토글에 따라 volume density, particle points, marching cubes mesh, SDF raycasting을 선택적으로 렌더링합니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1606_HybridWater.cpp/.h` | 예제 entry, hybrid simulation orchestration, GUI |
| `Ex1606_Common.hlsli` | Ex1606 compute/render shader 공통 상수와 helper |
| `Ex1606_ApplyPressureCS.hlsl` | pressure gradient 적용 |
| `Ex1606_DivergenceCS.hlsl` | velocity divergence와 boundary condition 계산 |
| `Ex1606_JacobiCS.hlsl` | pressure solve iteration |
| `Ex1606_DiffUpSampleCS.hlsl` | grid velocity change를 particle에 반영 |
| `Ex1606_ParticleStepCS.hlsl` | particle spawn/advection |
| `Ex1606_FirstIndexCS.hlsl` | sorted particle의 cell별 first index 계산 |
| `Ex1606_ParticleToGridCS.hlsl` | particle data를 grid velocity/density/SDF로 샘플링 |
| `Ex1606_StructuredBufferVS/PS.hlsl` | particle point rendering |
| `Ex1606_MarchingCubesVS/GS.hlsl` | SDF 기반 marching cubes 렌더링 |
| `Ex1606_SignedDistancePS.hlsl` | signed distance field raycasting |
| `MarchingCubes.h` | marching cubes triangle table |
| `BitonicSort.*`, `BitonicSortCS.hlsl` | GPU sorting helper |
| `Texture3D.h` | 3D texture SRV/UAV wrapper와 procedural noise 생성 |
| `main.cpp` | command argument `1606` mapping |
| `Examples.vcxproj` | source/shader build registration |

## Asset 메모

- `InitCubemaps()` 호출은 주석 처리되어 있어 현재 실행 경로에서 외부 cubemap asset을 요구하지 않습니다.
- noise texture는 `Texture3D::InitNoiseF16()`에서 코드로 생성합니다.
- raw result/capture/build output은 포함하지 않습니다.

## Import 메모

- Ex1606 shader files, `MarchingCubes.h`, `main.cpp`는 primary raw와 hash가 일치합니다.
- `Ex1606_HybridWater.cpp`는 primary raw 대비 실행 확인용 성능 profile을 낮춘 상태입니다. raw 기본값은 128^3 grid, 1024 * 1024 max particles, 3096 new particles, 2 substeps이며 archive 기준은 64^3 grid, 256 * 1024 max particles, 1024 new particles, 1 substep입니다.
- `Ex1606_HybridWater.h`는 primary raw와 hash가 일치합니다.
- `Examples.vcxproj`와 `Examples.vcxproj.filters`에는 Ex1606 source/shader/filter 항목이 등록되어 있습니다.
- Ex1606 shader files는 Debug/Release x64에서 shader model `5.0`으로 등록되어 있습니다.
- `Ex1606_Common.hlsli`는 `None` item으로 등록되어 shader include file로 사용됩니다.
- Ex1606 HLSL/HLSLI 파일은 UTF-8 BOM 없이 정상 코드 문자로 시작합니다.
- 사용자 확인 기준으로 Debug/Release x64 모두 실행 확인 완료 상태입니다.
