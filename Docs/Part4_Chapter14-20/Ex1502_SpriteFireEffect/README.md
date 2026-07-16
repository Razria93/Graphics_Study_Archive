# Ex1502 SpriteFireEffect

`Ex1502_SpriteFireEffect`는 `Ex1501_ParticleSystem`의 particle pool/update 구조를 바탕으로, sprite texture를 입힌 fire-like particle effect를 출력하는 예제입니다. CPU에서 particle을 생성/갱신하고, geometry shader가 point particle을 quad sprite로 확장하며, pixel shader가 `flare0.dds` texture를 샘플링해 불꽃 형태를 만듭니다.

## 목적

- particle sprite에 texture를 적용하는 흐름을 확인합니다.
- particle life에 따라 색과 밝기가 변하는 방식을 확인합니다.
- fire-like effect를 위해 additive/accumulate blend를 사용하는 방식을 확인합니다.
- 자동 source와 mouse click source를 함께 사용하는 particle emission 흐름을 확인합니다.

## 핵심 흐름

1. `1024`개의 particle slot을 CPU vector에 확보합니다.
2. 초기 particle은 `life = -1.0f`로 비활성 상태로 둡니다.
3. 매 프레임 중심 위치에서 fire particle을 자동 생성합니다.
4. 마우스 왼쪽 클릭 시 클릭 위치에서도 particle을 추가 생성합니다.
5. CPU에서 buoyancy, velocity, life를 갱신합니다.
6. staging buffer를 통해 CPU particle 데이터를 GPU structured buffer로 복사합니다.
7. vertex shader는 `SV_VertexID`로 particle buffer를 읽고 life 기반 color를 계산합니다.
8. `Ex1501_ParticleSystemGS.hlsl`가 point particle을 quad sprite로 확장합니다.
9. pixel shader는 `flare0.dds`를 샘플링하고 color와 alpha를 곱해 fire sprite를 출력합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1502_SpriteFireEffect.cpp` | particle source/update, texture load, sprite draw |
| `Ex1502_SpriteFireEffect.h` | `Particle` 구조체, particle buffer, sprite texture SRV 멤버 정의 |
| `Ex1502_SpriteFireEffectVS.hlsl` | particle life 기반 color/fade 계산 |
| `Ex1501_ParticleSystemGS.hlsl` | point particle을 quad sprite로 확장 |
| `Ex1502_SpriteFireEffectPS.hlsl` | `flare0.dds` sprite texture 샘플링 |
| `Assets/Textures/flare0.dds` | fire sprite runtime texture |
| `main.cpp` | command argument `1502`로 `Ex1502_SpriteFireEffect` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1502`를 지정해야 합니다.

```text
Examples.exe 1502
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 검은 배경 위에 fire-like sprite particle이 자동 생성되는지 확인
- particle이 위로 떠오르며 사라지는지 확인
- 마우스 왼쪽 클릭 시 클릭 위치에서 작은 fire particle이 추가 생성되는지 확인
- `flare0.dds` texture가 정상 적용되는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: `Assets/Textures/flare0.dds` 포함
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
