# Ex1603 Cloud

## 목적

`Ex1603_Cloud`는 compute shader로 3D density texture와 lighting texture를 생성하고, volume pixel shader로 박스 내부를 구름처럼 렌더링하는 예제입니다. 외부 이미지 asset을 불러오는 방식이 아니라, procedural noise와 volume lighting 계산으로 cloud volume을 만듭니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1603` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | 없음 |
| Build/run status | 미확인 |

확인할 동작:

- 화면에 volume box 내부의 cloud density가 반투명하게 렌더링됩니다.
- GUI의 `LightAngle`, `LightAbsorption`, `DensityAbsorption`, `lightScale`, `Aniso` 값을 조정해 조명/흡수/산란 변화가 보이는지 확인합니다.
- 시간이 지나며 density texture의 uvw offset이 변해 구름 내부 패턴이 이동하는지 확인합니다.
- Debug/Release x64 모두 command argument `1603`으로 확인합니다.

## 핵심 흐름

1. `Ex1603_Cloud::InitScene()`에서 volume box model을 만들고 density/lighting `Texture3D`를 초기화합니다.
2. `CloudDensityCS.hlsl`이 procedural perlin-worley noise로 3D density field를 생성합니다.
3. `CloudLightingCS.hlsl`이 density texture를 샘플링하면서 light ray visibility를 계산해 lighting texture를 만듭니다.
4. `Update()`는 `uvwOffset.z`를 증가시켜 density noise sampling 좌표를 이동시키고, density/lighting compute pass를 다시 dispatch합니다.
5. `Render()`는 기본 scene render 뒤 `Graphics::volumeSmokePSO`로 volume box를 alpha blending합니다.
6. GUI 조작은 `VolumeConsts`를 바꾸고 compute/pixel shader에서 cloud lighting과 absorption 결과에 반영됩니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1603_Cloud.cpp/.h` | 예제 entry, volume texture 초기화, compute dispatch, GUI |
| `CloudDensityCS.hlsl` | procedural cloud density volume 생성 |
| `CloudLightingCS.hlsl` | density field 기반 light visibility volume 생성 |
| `Texture3D.h` | 3D texture SRV/UAV/RTV wrapper |
| `TileableNoise.hlsli` | tileable noise helper include |
| `VolumeSmokePS.hlsl` | volume rendering pixel shader |
| `GraphicsCommon.*` | volume smoke PSO/shader 초기화 |
| `main.cpp` | command argument `1603` mapping |
| `Examples.vcxproj` | source/shader build registration |

## Import 메모

- `Ex1603_Cloud.cpp/.h`, `CloudDensityCS.hlsl`, `CloudLightingCS.hlsl`은 primary raw와 hash가 일치합니다.
- `CloudDensityCS.hlsl`, `CloudLightingCS.hlsl`은 Debug/Release x64에서 compute shader model `5.0`으로 등록되어 있습니다.
- 코드 안에 HDRI cubemap 초기화 주석이 남아 있지만 현재 실행 경로에서는 별도 runtime asset을 요구하지 않습니다.
- Debug/Release x64 실행 확인 전까지 build/run은 `미확인`으로 둡니다.
