# Part4 Chapter15 Particle Simulation Demo

## 요약

Chapter15는 CPU-side particle simulation 결과를 structured buffer와 geometry shader sprite draw로 표시하는 particle simulation evidence 묶음이다. 대표 visual은 `Ex1501_ParticleSystem`의 colored particle stream과 `Ex1503_SphWater`의 10초 지연 SPH particle accumulation으로 구성한다. `Ex1502_SpriteFireEffect`는 sprite fire visual을 확인했지만 `flare0.dds` provenance 확인 전까지 public 대표 visual에서 제외한다.

## 결과

### Particle stream baseline

`Ex1501_ParticleSystem`은 inactive particle pool에서 source particle을 활성화하고 gravity, wall collision과 life update를 적용한 뒤 sprite stream으로 그린다.

![Particle stream baseline](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter15_01_particle_system.png?raw=true)

### SPH water accumulation

`Ex1503_SphWater`는 좌우 source에서 유입된 particles에 SPH density/pressure/viscosity force와 boundary collision을 적용한다. 10초 지연 capture는 particles가 하단에 쌓이는 simulation 상태를 대표한다.

![SPH water accumulation](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter15_03_sph_water.png?raw=true)

## 핵심 구현

### Particle pool and sprite draw

`Ex1501`은 fixed-size CPU particle pool을 inactive 상태로 유지하다가 source와 input 조건에서 일부 particle을 활성화한다. 갱신된 CPU 배열은 staging buffer를 거쳐 structured buffer로 업로드되고, geometry shader가 point list를 screen-space sprite로 확장한다.

- [Particle pool update와 collision](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/Ex1501_ParticleSystem.cpp#L88)
- [Structured buffer sprite draw](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/Ex1501_ParticleSystem.cpp#L231)

### SPH update and accumulation evidence

`Ex1503`은 좌우 source에서 particles를 공급하고 `SphSimulation::Update`에서 density, pressure와 viscosity force를 계산한다. Screenshot은 immediate frame보다 10초 지연 frame을 선택해 particle cluster accumulation을 더 명확하게 보여 준다.

- [Dual source spawn과 SPH update 호출](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/Ex1503_SphWater.cpp#L80)
- [SPH density 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/SphSimulation.cpp#L31)
- [SPH force 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/SphSimulation.cpp#L78)

### Sprite fire hold

`Ex1502_SpriteFireEffect`는 Debug x64 run과 local screenshot 후보를 확인했지만 `Assets/Textures/flare0.dds`를 사용한다. Asset provenance와 공개 가능 범위가 확정되기 전에는 GitHub body 대표 visual로 사용하지 않는다.

## 처리 흐름

1. `Examples.exe` command argument `1501`, `1502`, `1503`으로 Chapter15 예제를 선택한다.
2. `Ex1501`과 `Ex1503`은 CPU particle state를 갱신하고 structured buffer로 업로드한다.
3. Geometry shader sprite draw와 accumulate blend가 particle state를 visual로 변환한다.
4. `Ex1503`은 SPH density/pressure/viscosity force를 계산한 뒤 gravity와 boundary collision을 적용한다.
5. Screenshot 후보는 collapsed capture UI, centered window와 taskbar-free visible client area 기준으로 검수한다.

## 구현 범위와 한계

- 현재 public 대표 visual 후보는 `Ex1501`과 10초 지연 `Ex1503` screenshot 2개다.
- `Ex1502`는 `flare0.dds` provenance 확인 전까지 local 후보와 보류 상태로 유지한다.
- `Ex1501`과 `Ex1503`의 simulation update는 CPU-side이며 GPU compute simulation으로 확장한 사례는 Chapter16 후속 범위에서 다룬다.
- Particle movement와 SPH stability는 video 후보지만, 이 본문은 static screenshot으로 읽히는 상태 증거를 우선한다.
- Release 현재 재검증과 Chapter16~20 재검증은 별도 범위다.

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build: 경고 0개, 오류 0개
- `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater` Debug x64 run/capture smoke 성공
- `Ex1501`과 10초 지연 `Ex1503` PNG는 taskbar-free centered client-visible capture이며 text metadata chunk가 없음

## 더 자세히 보기

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex1501 ParticleSystem 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md)
- [Ex1503 SphWater 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_03_SphWater.md)
- [Chapter15 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Compute And Simulation Topic Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/ComputeAndSimulation/topic-index.md)