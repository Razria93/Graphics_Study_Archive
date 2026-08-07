# GPU Particle And Fluid Simulation

## 목적

Particle, SPH water, stable fluids, smoke와 hybrid water 예제는 시간에 따라 변하는 simulation state를 update하고 render 단계에서 그 state를 읽는다. 이 Topic은 CPU update와 GPU compute update를 구분하고 particle 또는 grid state를 visual output으로 연결하는 공통 구조를 설명한다.

## 책임 범위

- simulation state, time step, particle와 grid representation의 관계를 설명한다.
- CPU simulation과 GPU compute simulation의 data ownership 차이를 설명한다.
- force model과 volume rendering 구현은 상세 Demo로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification/Part4_Chapter14-20`의 [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos/Part4_Chapter14-20`의 상세 Demo로 위임한다.

## 핵심 개념

### Simulation State And Time Step

Simulation은 position, velocity, density처럼 다음 frame을 계산하는 state를 유지한다. update는 time step을 입력으로 state를 전진시키고 render는 update 결과를 buffer 또는 texture로 읽는다. time step이 커질수록 안정성 조건과 integration error가 달라지므로 visual 변화만으로 물리적 정확도를 단정하지 않는다.

### Particle And Grid Representation

Particle representation은 개별 입자의 position과 velocity를 저장해 sprite 또는 point rendering에 연결한다. Grid representation은 texture 또는 volume cell에 density, velocity, pressure를 저장해 field 연산에 연결한다. hybrid 방식은 particle state와 grid field를 함께 사용하므로 변환 비용과 해상도 선택을 함께 고려한다.

### CPU And GPU Update Boundary

`Ex1501_ParticleSystem`과 `Ex1503_SphWater`는 CPU-side update 결과를 GPU buffer로 upload해 render한다. Chapter16 예제는 compute shader로 texture 또는 buffer state를 갱신하고 render 단계에서 결과를 읽는다. 두 방식은 같은 visual category를 만들 수 있지만 simulation ownership과 CPU-GPU data transfer 방향이 다르다.

## 한계

- Navier-Stokes와 SPH의 완전한 수치 해석 유도는 다루지 않는다.
- storyboard는 motion evidence이며 solver convergence를 증명하지 않는다.
- GPU 성능과 memory bandwidth profile은 현재 검증 범위가 아니다.

## 관련 문서

- [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md)
- [Chapter15 ParticleSystem Demo](../../03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md)
- [Chapter15 SphWater Demo](../../03_Demos/Part4_Chapter14-20/15_03_SphWater.md)
- [Chapter16 StableFluids Demo](../../03_Demos/Part4_Chapter14-20/16_01_StableFluids.md)
- [Chapter16 HybridWater Demo](../../03_Demos/Part4_Chapter14-20/16_06_HybridWater.md)
- [Part4 Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- [Compute And Simulation Topic Index](topic-index.md)