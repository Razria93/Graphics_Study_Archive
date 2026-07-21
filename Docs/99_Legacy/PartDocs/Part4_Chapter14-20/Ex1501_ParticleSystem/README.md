# Ex1501 ParticleSystem

`Ex1501_ParticleSystem`은 CPU에서 particle의 생성, 수명, 속도, 충돌을 갱신하고 GPU structured buffer로 전달한 뒤, vertex/geometry/pixel shader로 sprite particle을 렌더링하는 예제입니다. Ch14의 density/indirect draw 흐름에서 벗어나, Ch15 particle system의 기본 구조를 보여주는 첫 예제입니다.

## 목적

- 고정 크기 particle pool을 만들고 `life` 값으로 활성/비활성을 관리하는 방식을 확인합니다.
- CPU에서 particle 위치, 속도, 수명, 충돌을 갱신한 뒤 GPU buffer로 복사하는 흐름을 확인합니다.
- vertex shader가 `SV_VertexID`로 structured buffer의 particle을 읽는 방식을 확인합니다.
- geometry shader가 point particle을 quad sprite로 확장하는 방식을 확인합니다.
- pixel shader가 sprite 내부를 원형 falloff로 출력하는 방식을 확인합니다.

## 핵심 흐름

1. `2048 * 2`개의 particle slot을 CPU vector에 확보합니다.
2. 초기 particle은 `life = -1.0f`로 비활성 상태로 둡니다.
3. 매 프레임 자동 source와 마우스 클릭 위치에서 비활성 particle을 다시 활성화합니다.
4. CPU에서 gravity, velocity, life, wall/ground collision을 갱신합니다.
5. staging buffer를 통해 CPU particle 데이터를 GPU structured buffer로 복사합니다.
6. vertex shader는 `SV_VertexID`로 particle buffer를 읽습니다.
7. geometry shader는 활성 particle만 quad sprite로 확장합니다.
8. pixel shader는 원형 falloff를 적용해 particle sprite를 출력합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1501_ParticleSystem.cpp` | particle pool 초기화, CPU update, staging upload, sprite draw |
| `Ex1501_ParticleSystem.h` | `Particle` 구조체와 GPU/staging buffer 멤버 정의 |
| `Ex1501_ParticleSystemVS.hlsl` | `SV_VertexID`로 structured buffer particle 읽기 |
| `Ex1501_ParticleSystemGS.hlsl` | point particle을 quad sprite로 확장 |
| `Ex1501_ParticleSystemPS.hlsl` | sprite 원형 falloff 출력 |
| `main.cpp` | command argument `1501`로 `Ex1501_ParticleSystem` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1501`을 지정해야 합니다.

```text
Examples.exe 1501
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 검은 배경 위에 색이 있는 particle sprite가 계속 생성/이동하는지 확인
- gravity와 wall/ground collision에 의해 particle 움직임이 바뀌는지 확인
- 마우스 왼쪽 클릭 시 클릭 위치에서 particle이 추가 생성되는지 확인
- 별도 runtime asset 없이 실행되는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
