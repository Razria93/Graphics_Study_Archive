# Ex1604 RealtimeSmoke

## 목적

`Ex1604_RealtimeSmoke`는 3D grid 기반 realtime smoke simulation 예제입니다. 저해상도 grid에서 sourcing, pressure projection, boundary condition을 처리하고, 고해상도 grid로 차분 업샘플링한 뒤 advection과 volume rendering으로 연기 흐름을 보여줍니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1604` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | `Assets/Textures/Cubemaps/HDRI/Sample*.dds` |
| Build/run status | 미확인 |

확인할 동작:

- 화면에 volume smoke가 렌더링됩니다.
- bounding box가 함께 표시됩니다.
- GUI의 `Turbulence`, `Source`, `Buoyancy` 조작이 smoke motion/source에 반영되는지 확인합니다.
- Debug/Release x64 모두 command argument `1604`로 확인합니다.

## 핵심 흐름

1. `InitScene()`에서 HDRI cubemap, fluid constant buffer, low/high resolution `Texture3D`들을 초기화합니다.
2. low resolution grid는 pressure projection과 boundary condition 계산에 사용합니다.
3. high resolution grid는 advection과 최종 density rendering에 사용합니다.
4. `DownSample()`은 high resolution velocity/density를 low resolution grid로 내리고, vorticity confinement를 적용합니다.
5. `Sourcing()`은 velocity, density, boundary condition을 생성합니다.
6. `Projection()`은 divergence, Jacobi pressure solve, pressure application으로 divergence-free velocity field를 만듭니다.
7. `DiffUpSample()`은 low resolution 변화량을 high resolution grid에 더합니다.
8. `Advection()`은 high resolution velocity/density를 이동시킵니다.
9. `Render()`는 기본 scene 이후 `volumeSmokePSO`로 volume smoke를 렌더링하고 bounding box를 덧그립니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1604_RealtimeSmoke.cpp/.h` | 예제 entry, simulation pass orchestration, GUI |
| `Ex1604_SourcingCS.hlsl` | source, boundary condition, buoyancy |
| `Ex1604_DownSampleCS.hlsl` | high -> low grid downsample |
| `Ex1604_DiffUpSampleCS.hlsl` | low grid 변화량을 high grid에 반영 |
| `Ex1604_DivergenceCS.hlsl` | velocity divergence 계산 |
| `Ex1604_JacobiCS.hlsl` | pressure solve iteration |
| `Ex1604_ApplyPressureCS.hlsl` | pressure gradient 적용 |
| `Ex1604_AdvectionCS.hlsl` | high resolution advection |
| `Ex1604_VorticityConfinementCS.hlsl` | vorticity confinement |
| `VolumeSmokePS.hlsl` | volume smoke rendering |
| `Texture3D.h` | 3D texture SRV/UAV wrapper |
| `main.cpp` | command argument `1604` mapping |
| `Examples.vcxproj` | source/shader build registration |

## Asset 메모

- `InitCubemaps()`가 `../Assets/Textures/Cubemaps/HDRI/Sample*.dds`를 읽으므로 root `Assets/Textures/Cubemaps/HDRI`에 runtime asset이 필요합니다.
- archive에서는 이미 검토/사용 중인 `Part3_Chapter10-13/Assets/Textures/Cubemaps/HDRI/Sample*.dds` 4개를 root `Assets` 경로에 재사용 복사했습니다.
- 복사된 `.dds` 파일들은 `.gitattributes` 기준으로 Git LFS 대상입니다.
- raw Part4의 `SampleEnvHDR.dds`는 더 큰 원본 asset이므로, archive 기준은 기존 replacement/sample HDRI asset 재사용입니다.

## Import 메모

- `Ex1604_RealtimeSmoke.cpp/.h`, `Ex1604_SourcingCS.hlsl`, `Ex1604_AdvectionCS.hlsl`은 primary raw와 hash가 일치합니다.
- Ex1604 compute shaders와 `VolumeSmokePS.hlsl`은 Debug/Release x64에서 shader model `5.0`으로 등록되어 있습니다.
- Debug/Release x64 실행 확인 전까지 build/run은 `미확인`으로 둡니다.
