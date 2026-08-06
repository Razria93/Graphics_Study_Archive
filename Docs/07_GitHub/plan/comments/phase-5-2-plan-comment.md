## Phase 5-2 완료 기록

## 완료 내용

- `Part4_Chapter14-20`의 Chapter15 `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater`를 Debug x64 기준으로 smoke 확인했다.
- `Ex1501` particle stream과 10초 지연 `Ex1503` SPH water accumulation screenshot을 tracked capture asset으로 승격했다.
- `Ex1501`과 `Ex1503` 상세 Demo를 작성하고 Chapter15 Demo Issue body에 연결했다.
- `Ex1502`는 `Assets/Textures/flare0.dds` provenance 확인 전까지 local 후보와 public 대표 visual 보류 상태로 유지한다.

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build: 경고 0개, 오류 0개
- `Ex1501`, `Ex1502`, `Ex1503` Debug x64 run/capture smoke: 성공
- `Ex1501`과 10초 지연 `Ex1503` PNG full format, taskbar-free centered client-visible capture와 text metadata chunk 없음: 확인
- Demo index, 상세 Demo, GitHub body와 Markdown validator: 통과

## 남은 제한

- `Ex1502_SpriteFireEffect`는 `flare0.dds` provenance 확인 전까지 GitHub 대표 visual로 게시하지 않는다.
- Particle movement와 SPH stability는 static screenshot만으로 모두 설명하지 않으므로 desktop video 후속 후보로 둔다.
- Release 현재 재검증과 Chapter16~20 재검증은 후속 범위로 둔다.

## Related PR

- 예정