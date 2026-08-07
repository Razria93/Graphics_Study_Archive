# Part4 Chapter14-20 Demo closeout와 validator preflight 정리

## 요약

이 PR은 Part4 Chapter14부터 Chapter20까지의 advanced graphics 예제를 GitHub reviewer가 따라갈 수 있는 문서 흐름으로 정리한다. Compute shader, particle/fluid simulation, skeletal animation, foliage/landscape rendering, PhysX rigid body와 gameplay physics integration을 Demo, Topic, Verification, Publication 문서로 분리한다. 후속 validator cleanup은 Actions와 동일한 changed-file 조건까지 로컬에서 재현해 PR merge 전 실패 가능성을 줄이는 목적이다.

## 범위

- Chapter14: compute shader resource flow, structured buffer, indirect arguments, bitonic sort
- Chapter15: GPU particle system, sprite fire effect, SPH water
- Chapter16: stable fluids, curl noise, procedural cloud, realtime smoke, CPU smoke, hybrid water
- Chapter17: skeletal animation clip sampling, bone hierarchy update, skinned mesh render
- Chapter18: tree wind deformation, instanced grass, heightmap terrain과 procedural ocean
- Chapter19: PhysX rigid-body scene, fixed-step simulation, render transform synchronization
- Chapter20: fire animation notify, projectile actor spawn, gameplay destruction synchronization
- Validator cleanup: GitHub body warning, Demo detail/index link, Markdown wrap/render/table, Actions changed-file parity 기준 정리

## 핵심 개념

Chapter14부터 Chapter16까지는 compute shader resource flow와 GPU/CPU simulation 경계를 비교한다. Structured buffer, indirect arguments, particle trail, Texture3D volume density와 particle-to-grid conversion이 모두 rendering evidence로 연결된다.

Chapter17부터 Chapter20까지는 animation, physics와 gameplay integration을 다룬다. Bone transform upload, wind shader deformation, PhysX actor pose synchronization과 animation notify 기반 projectile spawn이 각 chapter의 중심 경로다. 상세 Demo 문서는 일반 이론을 Topic으로 위임하고, build/run/capture 사실은 Verification Index로 위임한다.

## 대표 예제

- `Ex1408_BitonicSort`: compute shader dispatch와 structured buffer 정렬 결과를 indirect/resource flow 관점에서 확인한다.
- `Ex1503_SphWater`: particle simulation과 density/pressure update를 GPU particle-fluid demo evidence로 연결한다.
- `Ex1606_HybridWater`: particle simulation과 grid velocity projection을 결합하고, density volume 또는 signed-distance raycasting으로 결과를 표시한다.
- `Ex1701_SkeletalAnimation`: animation clip key와 bone hierarchy를 갱신한 뒤 structured buffer를 skinned render path에 연결한다.
- `Ex1803_Landscape`: raw heightmap terrain과 procedural ocean pixel shader를 같은 scene에 구성한다.
- `Ex1901_PhysX`: rigid dynamic block stack pose를 render model transform에 동기화한다.
- `Ex2001_GamePlay`: fire animation notify frame에서 PhysX projectile과 fire billboard를 생성하고 destruction state를 표시한다.

## 검증

| 항목 | 결과 |
| --- | --- |
| Solution | `Part4_Chapter14-20/Examples.sln` |
| Debug x64 | Chapter14부터 Chapter20까지 build/run/capture smoke 성공 |
| Release x64 | Chapter14부터 Chapter20까지 build/run/capture smoke 성공 |
| Capture evidence | Chapter14부터 Chapter20까지 tracked storyboard PNG 확보 |
| Local full-scan | GitHub body, GitHub quality, visual fixture, Demo index/detail, video asset, window capture/input, Topic validator 통과 |
| Actions parity | `HEAD~5..HEAD` changed-file 기준 Demo scoped 38개, Markdown scoped 79개 통과 |
| Whitespace | `git diff --check HEAD~5 HEAD` 통과 |
| PR checks | Docs Validation 2개 success |

## 스크린샷

### Gameplay destruction storyboard

Chapter20 대표 visual은 fire animation notify frame에서 projectile actor가 생성되고, PhysX simulation pose가 render transform으로 동기화되어 block stack destruction이 진행되는 상태를 보여준다.

![Gameplay destruction storyboard](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter20_01_gameplay.png?raw=true)

### Hybrid water storyboard

Chapter16 대표 visual은 particle-to-grid density field와 signed-distance raycasting display를 같은 hybrid water 예제 안에서 비교할 수 있게 기록한다.

![Hybrid water storyboard](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter16_06_hybrid_water.png?raw=true)

## 미확인 / 제한

- Video attachment URL은 아직 없다. 현재 공개 evidence는 tracked storyboard image 기준이다.
- HDRI, character, foliage, terrain, texture와 raw runtime source asset은 직접 첨부하거나 링크하지 않는다.
- Storyboard는 local-only MP4에서 선별한 timestamp frame이며 interactive session 전체를 대체하지 않는다.
- Chapter14와 Chapter15의 GitHub body도 관련 문서에 포함하지만, representative visual은 Chapter16과 Chapter20 storyboard를 중심으로 둔다.

## 문서

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Part4 Verification Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Part4 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/demo-index.md)
- [Chapter14 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter14.md)
- [Chapter15 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter15.md)
- [Chapter16 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter16.md)
- [Chapter17 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter17.md)
- [Chapter18 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter18.md)
- [Chapter19 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter19.md)
- [Chapter20 Demo Issue Body](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/07_GitHub/issues/demo/demo_part4_chapter20.md)
- [Validator Operation Criteria](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/98_Tools/validation-tools.md)

## 관련 이슈

- Progress Issue: #7
- Chapter14 Demo Issue: #29
- Chapter15 Demo Issue: #31
- Chapter16 Demo Issue: #33
- Chapter17 Demo Issue: #34
- Chapter18 Demo Issue: #35
- Chapter19 Demo Issue: #36
- Chapter20 Demo Issue: #37

## 다음 단계

- Review comment가 있으면 관련 Demo, Topic, Verification 문서 중 정본 위치에 반영한다.
- Merge 후 base branch의 Docs Validation 결과를 확인한다.