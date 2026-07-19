# Ex1406 DensityField

`Ex1406_DensityField`는 particle을 움직이면서 density texture에 색을 누적하고, 매 프레임 compute shader로 density를 감쇠시키는 예제입니다. `Ex1404`/`Ex1405`에서 다룬 structured buffer 기반 particle 데이터를 이어서 사용하되, 출력은 화면 크기의 `RWTexture2D<float4>`에 누적한 뒤 back buffer로 복사합니다.

## 목적

- compute shader가 particle position을 갱신하는 흐름을 확인합니다.
- compute shader가 `RWTexture2D`에 density 값을 쓰고 감쇠시키는 흐름을 확인합니다.
- geometry shader가 point particle을 작은 quad sprite로 확장하는 방식을 확인합니다.
- additive/accumulate blend state로 density field에 색이 누적되는 결과를 확인합니다.

## 핵심 흐름

1. CPU에서 256개의 particle position/color를 생성합니다.
2. `StructuredBuffer<Particle>`와 `Texture2D m_densityTex`를 초기화합니다.
3. `DissipateDensity()`에서 `Ex1406_DensityDissipationCS.hlsl`이 density texture의 기존 색을 줄입니다.
4. `AdvectParticles()`에서 `Ex1406_DensitySourcingCS.hlsl`이 particle position을 회전장 형태로 갱신합니다.
5. `DrawSprites()`에서 point list를 draw하고, geometry shader가 각 point를 quad sprite로 확장합니다.
6. pixel shader가 sprite 내부를 원형 falloff로 칠합니다.
7. density texture를 back buffer로 복사해 화면에 출력합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1406_DensityField.cpp` | particle/density texture 초기화, compute dispatch, sprite draw, back buffer copy |
| `Ex1406_DensityField.h` | particle buffer, density texture, shader 멤버 정의 |
| `Ex1406_DensitySourcingCS.hlsl` | particle position 갱신, density source 실험 코드 보관 |
| `Ex1406_DensityDissipationCS.hlsl` | density texture 감쇠 |
| `Ex1406_SpriteGS.hlsl` | point를 quad sprite로 확장 |
| `Ex1406_SpritePS.hlsl` | sprite 내부 원형 falloff 출력 |
| `Ex1404_StructuredBufferVS.hlsl` | particle structured buffer를 vertex shader에서 읽음 |
| `main.cpp` | command argument `1406`으로 `Ex1406_DensityField` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1406`을 지정해야 합니다.

```text
Examples.exe 1406
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 검은 배경 위에 색이 있는 particle sprite/density trail이 출력되는지 확인
- particle 색이 density texture에 누적되고 시간이 지나며 감쇠되는지 확인
- 별도 runtime asset 없이 실행되는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 성공
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
