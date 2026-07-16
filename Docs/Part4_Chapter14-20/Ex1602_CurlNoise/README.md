# Ex1602 CurlNoise

## 목적

`Ex1602_CurlNoise`는 compute shader에서 curl noise를 계산해 particle 위치를 갱신하고, sprite/density rendering으로 흐름을 누적해서 보여주는 예제입니다. `Ex1406_DensityField`의 density texture와 sprite rendering 흐름을 재사용하면서, particle motion을 procedural noise field로 움직이는 부분이 핵심입니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1602` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | 없음 |
| Build/run status | 미확인 |

확인할 동작:

- 화면에 여러 색의 particle trail 또는 density 누적 결과가 보입니다.
- 시간이 지나며 particle position이 curl noise field에 의해 움직입니다.
- Debug/Release x64 모두 command argument `1602`로 확인합니다.

## 핵심 흐름

1. `Ex1602_CurlNoise::Initialize()`에서 particle buffer와 density texture를 생성합니다.
2. particle 초기 위치와 색상은 CPU에서 생성한 뒤 structured buffer/UAV/SRV로 GPU에 올립니다.
3. `Update()`는 density dissipation compute shader를 먼저 실행해 이전 density를 완만히 감쇠시킵니다.
4. 이어서 `Ex1602_CurlNoiseCS.hlsl`이 density texture와 particle UAV를 받아 particle position을 curl noise 방향으로 이동시킵니다.
5. `Render()`는 particle structured buffer를 vertex shader resource로 넘기고 geometry shader sprite rendering으로 density texture에 누적합니다.
6. 최종 density texture를 back buffer에 복사합니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1602_CurlNoise.cpp/.h` | 예제 entry, particle buffer, update/render flow |
| `Ex1602_CurlNoiseCS.hlsl` | curl noise 기반 particle position update |
| `TileableNoise.hlsli` | tileable noise helper include |
| `Ex1404_StructuredBufferVS.hlsl` | structured buffer particle vertex fetch |
| `Ex1406_SpriteGS.hlsl` | point particle을 sprite quad로 확장 |
| `Ex1406_SpritePS.hlsl` | sprite color 출력 |
| `Ex1406_DensityDissipationCS.hlsl` | density texture 감쇠 |
| `main.cpp` | command argument `1602` mapping |
| `Examples.vcxproj` | source/shader build registration |

## Import 메모

- `Ex1602_CurlNoise.cpp/.h`, `Ex1602_CurlNoiseCS.hlsl`은 primary raw와 hash가 일치합니다.
- 별도 runtime asset은 요구하지 않습니다.
- `Ex1602_CurlNoiseCS.hlsl`은 Debug/Release x64에서 compute shader model `5.0`으로 등록되어 있습니다.
- Debug/Release x64 실행 확인 전까지 build/run은 `미확인`으로 둡니다.
