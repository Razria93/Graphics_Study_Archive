# Ex1605 SmokeCpu

## 목적

`Ex1605_SmokeCpu`는 CPU에서 3D fluid density field를 갱신하고, 그 결과를 3D texture로 업로드해 volume smoke로 렌더링하는 예제입니다. `Ex1604_RealtimeSmoke`가 compute shader 기반 smoke simulation을 보여줬다면, 이 예제는 `FluidSimulationCPU`를 통해 CPU simulation 결과를 GPU volume rendering 경로에 연결하는 흐름을 확인합니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1605` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | `Assets/Textures/Cubemaps/HDRI/Sample*.dds` |
| Build/run status | 미확인 |

확인할 동작:

- 화면에 volume smoke와 bounding box가 렌더링되는지 확인합니다.
- CPU simulation density가 매 프레임 `Texture3D`로 업로드되어 smoke 형태가 갱신되는지 확인합니다.
- Debug/Release x64 모두 command argument `1605`로 확인합니다.

## 핵심 흐름

1. `InitScene()`에서 HDRI cubemap, volume shader, volume constant buffer를 초기화합니다.
2. `FluidSimulationCPU::Initialize(64, 64, 64)`로 64^3 CPU simulation grid를 만듭니다.
3. box mesh에 `DXGI_FORMAT_R32_FLOAT` 3D density texture를 연결합니다.
4. `Update()`에서 CPU fluid simulation을 갱신합니다.
5. 갱신된 `m_fluid.m_density`를 `densityTex.Upload()`로 GPU 3D texture에 업로드합니다.
6. `Render()`에서 `volumeSmokePSO`로 density volume을 렌더링하고 bounding box를 함께 표시합니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1605_SmokeCpu.cpp/.h` | 예제 entry, CPU smoke update, volume rendering |
| `FluidSimulationCPU.cpp/.h` | CPU 3D fluid simulation grid/update |
| `Texture3D.h` | 3D texture SRV/UAV/upload wrapper |
| `VolumeSmokePS.hlsl` | volume smoke rendering pixel shader |
| `main.cpp` | command argument `1605` mapping |
| `Examples.vcxproj` | source/shader build registration |

## Asset 메모

- `InitCubemaps()`가 `../Assets/Textures/Cubemaps/HDRI/Sample*.dds`를 읽으므로 root `Assets/Textures/Cubemaps/HDRI` runtime asset이 필요합니다.
- 이 asset은 Ex1604 기준 기록 때 이미 archive root `Assets` 경로에 반영되어 있습니다.
- `.dds` 파일은 `.gitattributes` 기준으로 Git LFS 대상입니다.

## Import 메모

- `Ex1605_SmokeCpu.cpp/.h`, `FluidSimulationCPU.cpp/.h`, `VolumeSmokePS.hlsl`, `Texture3D.h`, `main.cpp`는 primary raw와 hash가 일치합니다.
- `Examples.vcxproj`는 archive 환경 보정을 위해 raw의 개인 vcpkg include 경로와 `.clang-format` project item을 조정한 상태입니다.
- `Examples.vcxproj`와 `Examples.vcxproj.filters`의 XML namespace는 정상입니다.
- `VolumeSmokePS.hlsl`, `Common.hlsli`는 UTF-8 BOM 없이 정상 코드 문자로 시작합니다.
- Debug/Release x64 실행 확인 전까지 build/run은 미확인 상태입니다.
