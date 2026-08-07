## Phase 5-2 완료 기록

## 완료 내용

- `Part4_Chapter14-20`의 Chapter15 `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater`를 Debug x64 기준으로 smoke 확인했다.
- `Ex1501` particle stream, `Ex1502` sprite fire와 `Ex1503` SPH water accumulation 시연 video의 timestamp storyboard를 tracked capture asset으로 승격했다.
- `Ex1501`, `Ex1502`와 `Ex1503` 상세 Demo를 작성하고 Chapter15 Demo Issue body에 연결했다.
- `Ex1502`는 원본 `Assets/Textures/flare0.dds`를 직접 링크하지 않고 직접 실행한 rendered evidence로만 다룬다.

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build: 경고 0개, 오류 0개
- `Ex1501`, `Ex1502`, `Ex1503` Debug x64 run/capture smoke: 성공
- `Ex1501`부터 `Ex1503`까지 PNG storyboard의 `ComputerGraphics` title, 01부터 03까지 timestamp frame과 text metadata chunk 부재: 확인
- Demo index, 상세 Demo, GitHub body와 Markdown validator: 통과

## 남은 제한

- `Ex1502_SpriteFireEffect`는 원본 `flare0.dds` 권리 확보를 주장하지 않으며, 공개 안전한 대체 texture 또는 provenance가 확인되면 visual 유지 범위를 다시 판단한다.
- Video attachment URL은 미게시이며 timestamp storyboard는 시연 video의 선택 frame만 기록한다.
- Release 현재 재검증과 Chapter16부터 Chapter20까지 재검증은 후속 범위로 둔다.

## Related PR

- [PR #32](https://github.com/Razria93/Graphics_Study_Archive/pull/32) - Part4 Chapter15 Particle Simulation evidence 문서화와 capture 승격