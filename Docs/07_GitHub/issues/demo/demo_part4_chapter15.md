# Part4 Chapter15 Particle Simulation Demo

## 요약

Chapter15는 CPU-side particle simulation 결과를 structured buffer와 geometry shader sprite draw로 표시하는 particle simulation evidence 묶음이다. 대표 visual은 각 시연 video에서 선택한 timestamp frame 3개를 배치한 storyboard로 구성한다. `Ex1502`는 원본 `flare0.dds`를 직접 링크하지 않고 직접 실행한 rendered evidence만 사용한다.

## 결과

### Particle stream baseline

`Ex1501_ParticleSystem`은 inactive particle pool에서 source particle을 활성화하고 gravity, wall collision과 life update를 적용한 뒤 sprite stream으로 그린다. Storyboard는 1.163s, 3.878s, 6.593s frame을 순서대로 기록한다.

![Particle stream baseline](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter15_01_particle_system.png?raw=true)

### Textured sprite fire

`Ex1502_SpriteFireEffect`는 source에서 활성화한 particles에 buoyancy를 적용하고 `flare0.dds` sprite texture를 pixel shader에 바인딩해 fire-like particles를 표시한다. Storyboard는 1.695s, 5.650s, 9.605s frame을 순서대로 기록하며 원본 texture를 직접 공개하지 않는다.

![Textured sprite fire](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter15_02_sprite_fire_effect.png?raw=true)

### SPH water accumulation

`Ex1503_SphWater`는 좌우 source에서 유입된 particles에 SPH density/pressure/viscosity force와 boundary collision을 적용한다. Storyboard는 2.200s, 4.600s, 12.467s frame을 순서대로 기록한다.

![SPH water accumulation](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter15_03_sph_water.png?raw=true)

## 핵심 구현

### Particle pool and sprite draw

`Ex1501`은 fixed-size CPU particle pool을 inactive 상태로 유지하다가 source와 input 조건에서 일부 particle을 활성화한다. 갱신된 CPU 배열은 staging buffer를 거쳐 structured buffer로 업로드되고, geometry shader가 point list를 screen-space sprite로 확장한다.

- [Particle pool update와 collision](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/Ex1501_ParticleSystem.cpp#L88-L155)
- [Structured buffer sprite draw](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/Ex1501_ParticleSystem.cpp#L231-L247)

### SPH update and accumulation evidence

`Ex1503`은 좌우 source에서 particles를 공급하고 `SphSimulation::Update`에서 density, pressure와 viscosity force를 계산한다. Storyboard는 source와 particle accumulation이 함께 보이는 시연 구간을 기록한다.

- [Dual source spawn과 SPH update 호출](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/Ex1503_SphWater.cpp#L80-L151)
- [SPH density 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/SphSimulation.cpp#L31-L73)
- [SPH force 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/SphSimulation.cpp#L78-L139)

### Sprite fire texture path

`Ex1502_SpriteFireEffect`는 source에서 활성화한 particles에 buoyancy를 적용하고 `flare0.dds` sprite texture를 pixel shader에 바인딩해 fire-like particles를 표시한다. 원본 texture의 권리 확보를 주장하지 않으며, 공개 안전한 대체 texture로 교체하거나 provenance가 확인되면 visual 유지 범위를 다시 판단한다.

- [Particle spawn/update와 buoyancy](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/Ex1502_SpriteFireEffect.cpp#L72-L128)
- [Sprite texture load](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/Ex1502_SpriteFireEffect.cpp#L66-L68)
- [Textured sprite draw](https://github.com/Razria93/Graphics_Study_Archive/blob/388d2b0c950d3d978179431b1006d8406ef391f4/Part4_Chapter14-20/Ex1502_SpriteFireEffect.cpp#L155-L174)

## 처리 흐름

1. `Examples.exe` command argument `1501`, `1502`, `1503`으로 Chapter15 예제를 선택한다.
2. `Ex1501`, `Ex1502`와 `Ex1503`은 CPU particle state를 갱신하고 structured buffer로 업로드한다.
3. Geometry shader sprite draw와 accumulate blend가 particle state를 visual로 변환한다.
4. `Ex1503`은 SPH density/pressure/viscosity force를 계산한 뒤 gravity와 boundary collision을 적용한다.
5. 시연 video에서 선택한 timestamp frame 3개를 01부터 03까지 순서와 함께 storyboard로 기록한다.

## 구현 범위와 한계

- 현재 public 대표 visual 후보는 `Ex1501`부터 `Ex1503`까지 timestamp storyboard 3개다.
- `Ex1502`는 원본 `flare0.dds`를 직접 링크하지 않고 직접 실행한 rendered evidence로만 다룬다. 공개 안전한 대체 texture 또는 provenance가 확인되면 visual 유지 범위를 다시 판단한다.
- 명확한 제한 근거, 삭제 요청 또는 사용 중단 요청이 확인되면 관련 visual은 교체하거나 비공개로 전환한다.
- `Ex1501`, `Ex1502`와 `Ex1503`의 simulation update는 CPU-side이며 GPU compute simulation으로 확장한 사례는 Chapter16 후속 범위에서 다룬다.
- Video attachment URL은 미게시이며, storyboard는 시연 video의 선택 frame만 기록한다.
- Release 현재 재검증과 Chapter16부터 Chapter20까지 재검증은 별도 범위다.

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build: 경고 0개, 오류 0개
- `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater` Debug x64 run/capture smoke 성공
- `Ex1501`부터 `Ex1503`까지 storyboard PNG는 `ComputerGraphics` title, 01부터 03까지 timestamp frame과 text metadata chunk 부재를 확인함

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | 없음 | 단일 screenshot 대신 timestamp storyboard를 사용함 |
| Result image | Chapter15 storyboard 3장 | 각 시연 video에서 선택한 timestamp frame 3개를 배치한 rendered evidence |
| Video | 없음 | GitHub attachment URL을 아직 게시하지 않음 |

## 더 자세히 보기

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex1501 ParticleSystem 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md)
- [Ex1502 SpriteFireEffect 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_02_SpriteFireEffect.md)
- [Ex1503 SphWater 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_03_SphWater.md)
- [Chapter15 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Compute And Simulation Topic Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/ComputeAndSimulation/topic-index.md)