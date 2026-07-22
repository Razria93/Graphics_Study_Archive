# Ex1802 Grass

## 목적

`Ex1802_Grass`는 Chapter 18 자연물 렌더링 흐름의 두 번째 예제로, 대량의 grass blades를 instancing으로 렌더링하는 예제입니다.

이 단계의 핵심은 동일한 grass mesh를 매번 개별 draw call로 그리지 않고, per-instance transform과 wind strength를 instance buffer로 넘긴 뒤 `DrawIndexedInstanced`로 한 번에 렌더링하는 것입니다.

## 실행 정보

| 항목 | 값 |
| --- | --- |
| Solution | `Part4_Chapter14-20/Examples.sln` |
| Project | `Examples` |
| Command argument | `1802` |
| Primary source | `C:\ComputerGraphics\Part4_HongLabGraphics\Examples` |
| Runtime asset | PBR ground textures, HDRI cubemap |

Part4는 단일 `Examples.exe`에서 command argument로 예제를 선택합니다. Debug/Release x64 모두 command argument `1802`로 확인합니다.

## 핵심 구성

| 파일 | 역할 |
| --- | --- |
| `Ex1802_Grass.cpp/.h` | scene setup, grass instance generation, wind GUI |
| `GrassModel.h` | grass mesh/index/instance buffer setup, instanced draw call |
| `Ex1802_GrassVS.hlsl` | per-vertex/per-instance input processing, wind deformation |
| `Ex1802_GrassPS.hlsl` | simple two-sided grass shading |
| `GraphicsCommon.*` | grass input layout, shader objects, grass PSO |
| `Vertex.h` | `GrassVertex`, `GrassInstance` layout |
| `main.cpp` | command argument `1802` mapping |

## 구현 포인트

- `GrassModel`은 vertex buffer와 instance buffer를 함께 IA stage에 바인딩합니다.
- `GrassInstance`는 instance world matrix와 wind strength를 포함합니다.
- `Ex1802_Grass.cpp`는 100,000개의 grass instance transform을 생성합니다.
- `Ex1802_GrassVS.hlsl`은 instance transform을 적용한 뒤 wind deformation을 계산합니다.
- `GrassModel::Render()`는 `DrawIndexedInstanced`를 사용해 grass instances를 한 번의 instanced draw path로 렌더링합니다.

## Asset 기준

이 예제는 전용 grass texture file을 새로 요구하지 않습니다. 기존 Part4 archive에 포함된 PBR ground textures와 HDRI cubemap을 재사용합니다.

- `Assets/Textures/PBR/stringy-marble-ue/*`
- `Assets/Textures/Cubemaps/HDRI/clear_puresky*.dds`

raw result/capture/build output은 포함하지 않습니다.

## Import Notes

- `Ex1802_Grass.cpp/.h`, `Ex1802_GrassVS.hlsl`, `Ex1802_GrassPS.hlsl`은 primary raw와 동일합니다.
- `GraphicsCommon.*`의 grass shader/input layout/PSO 등록도 primary raw와 동일합니다.
- 별도 신규 asset copy는 없습니다.
- Debug/Release build/run 확인 전까지 status는 `미확인`으로 둡니다.
