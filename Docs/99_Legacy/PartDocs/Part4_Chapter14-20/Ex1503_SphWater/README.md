# Ex1503 SphWater

`Ex1503_SphWater`는 CPU에서 SPH(smoothed-particle hydrodynamics) 방식의 간단한 물 입자 시뮬레이션을 수행하고, GPU structured buffer와 sprite rendering으로 결과를 출력하는 예제입니다. `Ex1501`의 particle rendering 구조를 유지하면서 density, pressure, force 계산을 분리한 `SphSimulation` helper를 사용합니다.

## 목적

- SPH particle의 density, pressure, force 계산 흐름을 확인합니다.
- kernel function(`CubicSpline`, `CubicSplineGrad`)이 주변 particle 영향도를 계산하는 방식을 확인합니다.
- 양쪽 source에서 생성된 particle이 서로 밀고 충돌하며 움직이는지 확인합니다.
- CPU simulation 결과를 GPU structured buffer로 업로드해 sprite로 렌더링하는 흐름을 확인합니다.

## 핵심 흐름

1. `SphSimulation::Particle` slot을 `1024 * 2`개 확보합니다.
2. 비활성 particle은 `life = -1.0f`로 둡니다.
3. 매 프레임 좌우 source에서 particle을 하나씩 생성합니다.
4. `SphSimulation::Update()`에서 density와 force를 계산합니다.
5. gravity와 wall/ground collision을 적용합니다.
6. CPU particle 데이터를 staging buffer를 통해 GPU structured buffer로 복사합니다.
7. vertex shader는 `SV_VertexID`로 SPH particle buffer를 읽습니다.
8. geometry shader는 point particle을 quad sprite로 확장합니다.
9. pixel shader는 cubic spline falloff로 물 입자 sprite를 출력합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1503_SphWater.cpp` | SPH particle 초기화, source 생성, collision, sprite draw |
| `Ex1503_SphWater.h` | `SphSimulation` 멤버와 rendering buffer 멤버 정의 |
| `SphSimulation.cpp` | density, pressure, pressure force, viscosity force 계산 |
| `SphSimulation.h` | SPH particle 구조체와 simulation parameter 정의 |
| `SphKernels.h` | cubic spline kernel과 gradient 함수 |
| `Ex1503_SphWaterVS.hlsl` | SPH particle structured buffer 읽기 |
| `Ex1501_ParticleSystemGS.hlsl` | point particle을 quad sprite로 확장 |
| `Ex1503_SphWaterPS.hlsl` | cubic spline falloff sprite 출력 |
| `main.cpp` | command argument `1503`으로 `Ex1503_SphWater` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1503`을 지정해야 합니다.

```text
Examples.exe 1503
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 좌우 source에서 물 입자들이 생성되는지 확인
- 입자들이 서로 밀고 모이며 유체처럼 움직이는지 확인
- wall/ground collision이 적용되는지 확인
- 별도 runtime asset 없이 실행되는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
