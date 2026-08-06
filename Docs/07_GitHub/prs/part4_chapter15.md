# Part4 Chapter15 Particle Simulation evidence 문서화와 capture 승격

## 요약

이 PR은 `Part4_Chapter14-20` 중 Chapter15 particle simulation slice를 Debug x64 기준으로 재검증하고, `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater`의 rendered evidence를 상세 Demo, Demo Issue와 Progress 기록으로 연결한다. 단일 `Examples.exe` command argument 구조에 맞춰 capture helper의 argument 전달을 보강하고, Ex1502의 원본 `flare0.dds`는 직접 링크하지 않는 rendered-only evidence 기준을 함께 기록한다.

## 범위

- Chapter15 `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater` Debug x64 build/run/capture smoke 정리
- `Ex1501`부터 `Ex1503`까지 시연 video의 timestamp frame 3개로 구성한 storyboard 3개를 `Docs/_assets/captures`로 승격
- `Examples.exe 1501`, `1502`, `1503` 실행을 지원하도록 capture helper `ArgumentList` option 문서화와 contract test 반영
- Chapter15 상세 Demo, Demo Issue #31, Phase 5-2 Progress comment와 PR body 후보 작성
- Chapter16부터 Chapter20까지 재검증, Release 현재 재검증, desktop video capture는 제외

## 핵심 개념

- CPU particle update: particle activation, life, gravity, buoyancy, boundary collision과 SPH force를 CPU-side state에서 갱신한다.
- Structured buffer sprite draw: CPU에서 갱신한 particle 배열을 structured buffer로 업로드하고 geometry shader가 point를 screen-space sprite로 확장한다.
- SPH storyboard evidence: 2.200s, 4.600s, 12.467s frame이 source와 particle cluster accumulation이 보이는 시연 구간을 기록한다.
- Rendered-only asset boundary: `Ex1502`의 원본 `flare0.dds`는 직접 링크하지 않고, 직접 실행한 storyboard만 evidence로 사용한다.

## 대표 예제

### Ex1501 ParticleSystem

Inactive particle pool에서 source particle을 활성화하고 gravity, wall collision과 life update를 적용한 뒤 structured buffer sprite stream으로 그린다.

- [Ex1501 ParticleSystem 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md)
- [Particle pool update와 collision](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/Ex1501_ParticleSystem.cpp#L88-L155)
- [Structured buffer sprite draw](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/Ex1501_ParticleSystem.cpp#L231-L247)

### Ex1502 SpriteFireEffect

Source에서 활성화한 particles에 buoyancy를 적용하고 `flare0.dds` sprite texture를 pixel shader에 바인딩해 fire-like particles를 표시한다. 원본 texture는 직접 공개하지 않고 rendered storyboard로만 결과를 설명한다.

- [Ex1502 SpriteFireEffect 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_02_SpriteFireEffect.md)
- [Particle spawn/update와 buoyancy](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/Ex1502_SpriteFireEffect.cpp#L72-L128)
- [Sprite texture load](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/Ex1502_SpriteFireEffect.cpp#L66-L68)
- [Textured sprite draw](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/Ex1502_SpriteFireEffect.cpp#L155-L174)

### Ex1503 SphWater

좌우 source에서 particles를 공급하고 `SphSimulation::Update`에서 density, pressure와 viscosity force를 계산한다. timestamp storyboard를 selected evidence로 사용해 particle accumulation이 보이는 시연 구간을 기록한다.

- [Ex1503 SphWater 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_03_SphWater.md)
- [Dual source spawn과 SPH update 호출](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/Ex1503_SphWater.cpp#L80-L151)
- [SPH density 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/SphSimulation.cpp#L31-L73)
- [SPH force 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/813d57c89aba283ab40b45e2ed94dfce30866c9c/Part4_Chapter14-20/SphSimulation.cpp#L78-L139)

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build 경고 0개, 오류 0개 확인
- `Ex1501`, `Ex1502`, `Ex1503` Debug x64 run/capture smoke 성공
- `Ex1501`부터 `Ex1503`까지 PNG storyboard에 `ComputerGraphics` title, 01부터 03까지 timestamp frame과 text metadata chunk 부재 확인
- Demo index, 상세 Demo, GitHub body, GitHub quality와 Markdown validator 통과 대상
- 최신 branch push 기준 `Docs Validation` run success 확인

## 대표 Visual

### Chapter15 SPH water accumulation

`Ex1503_SphWater`는 좌우 source에서 공급된 particles에 SPH density/pressure/viscosity force와 boundary collision을 적용한다. 2.200s, 4.600s, 12.467s timestamp storyboard는 particle accumulation이 보이는 시연 구간을 기록한다.

![Chapter15 SPH water accumulation](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter15_03_sph_water.png?raw=true)

## 구현 범위와 한계

- 이 PR의 현재 재검증 범위는 Chapter15 Debug x64다.
- Release 현재 재검증은 과거 확인 상태와 분리하고 후속 범위로 둔다.
- `Ex1501`, `Ex1502`와 `Ex1503`의 simulation update는 CPU-side이며 GPU compute simulation으로 확장한 사례는 Chapter16 후속 범위에서 다룬다.
- `Ex1502`는 원본 `flare0.dds`를 직접 링크하지 않고 직접 실행한 rendered evidence로만 다룬다. 명확한 제한 근거, 삭제 요청 또는 사용 중단 요청이 확인되면 관련 visual은 교체하거나 비공개로 전환한다.
- video attachment URL은 미게시이며 현재 PR은 timestamp storyboard evidence 중심으로 정리한다.
- Ready for Review 전환은 PR 생성 이후 별도 승인 후 수행한다.

## 문서

- Chapter README: [Part4 Chapter14-20](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- Verification: [Part4 Chapter14-20 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- Demo: [Part4 Chapter14-20 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/demo-index.md)
- 상세 Demo: [Ex1501 ParticleSystem](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md), [Ex1502 SpriteFireEffect](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_02_SpriteFireEffect.md), [Ex1503 SphWater](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/15_03_SphWater.md)
- Topic: [Compute And Simulation Topic Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/ComputeAndSimulation/topic-index.md)
- WorkLog: [WU-Part4](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/04_WorkLogs/work-units/WU-Part4.md)

## 관련 이슈

- Demo Issue: [Part4 Chapter15 Particle Simulation Demo #31](https://github.com/Razria93/Graphics_Study_Archive/issues/31)
- Progress 완료 댓글: [Phase 5-2 완료 기록](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5200004532)