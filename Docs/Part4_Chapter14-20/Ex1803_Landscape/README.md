# Ex1803 Landscape

## 목적

`Ex1803_Landscape`는 Chapter 18 자연물 렌더링 흐름의 세 번째 예제로, terrain과 ocean plane을 함께 배치해 landscape/ocean scene을 확인하는 예제입니다.

이 단계의 핵심은 terrain surface, skybox/IBL, ocean alpha blending, post effects를 한 장면에서 함께 구성하는 것입니다.

## 실행 정보

| 항목 | 값 |
| --- | --- |
| Solution | `Part4_Chapter14-20/Examples.sln` |
| Project | `Examples` |
| Command argument | `1803` |
| Primary source | `C:\ComputerGraphics\Part4_HongLabGraphics\Examples` |
| Runtime asset | `Assets/Textures/terrain.raw`, HDRI cubemap |

Part4는 단일 `Examples.exe`에서 command argument로 예제를 선택합니다. Debug/Release x64 모두 command argument `1803`으로 확인합니다.

## 핵심 구성

| 파일 | 역할 |
| --- | --- |
| `Ex1803_Landscape.cpp/.h` | terrain/ocean scene setup, GUI |
| `OceanModel.h` | ocean render path용 model wrapper |
| `Ex1803_OceanPS.hlsl` | ocean pixel shader |
| `GeometryGenerator.*` | raw asset fallback 이전에는 FBX mesh loading path 사용 |
| `main.cpp` | command argument `1803` mapping |

## Archive 보정

primary raw의 `Ex1803_Landscape.cpp`는 `../Assets/Terrain/snowy_mountain_with_slopes/uploads_files_4497957_untitled.fbx`와 `Texture.png`를 요구합니다. 하지만 현재 raw/reference repo에는 해당 terrain FBX asset folder가 없습니다.

archive에서는 실행 재현성을 위해 raw에 실제로 포함된 `../Assets/Textures/terrain.raw`를 선별 반영하고, 이 heightmap을 257x257 grid로 샘플링해서 terrain mesh를 생성하는 최소 fallback path를 추가했습니다.

이 변경은 강의 원본 구조를 확장하려는 목적이 아니라, private archive에서 예제 실행 확인이 가능하도록 missing runtime asset을 대체한 것입니다.

## Runtime Asset

- `Assets/Textures/terrain.raw`
- `Assets/Textures/Cubemaps/HDRI/clear_puresky*.dds`

`terrain.raw`는 binary runtime asset이므로 LFS 추적 대상으로 추가했습니다. raw result/capture/build output은 포함하지 않습니다.

## 확인 포인트

- terrain height field가 화면에 표시되는지 확인합니다.
- ocean plane이 terrain 주변에 표시되는지 확인합니다.
- `OceanHeight` GUI slider 조작 시 ocean plane 높이가 변하는지 확인합니다.
- post effect, skybox/IBL, material GUI가 기존 Part4 흐름과 충돌하지 않는지 확인합니다.
