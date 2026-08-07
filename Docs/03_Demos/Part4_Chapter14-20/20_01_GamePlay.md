# Chapter20 Ex2001 GamePlay Demo

## 목적

Character fire animation의 notify frame에서 PhysX projectile과 fire billboard를 생성하고, physics simulation pose를 render transform으로 동기화해 gameplay destruction 진행을 표시한다.

## 책임 범위

- `Ex2001_GamePlay`의 fire input, animation state, projectile spawn, PhysX update와 render synchronization을 설명한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)으로 위임한다.
- public 후보 판단은 [Publication Candidate List](../../05_Publication/candidate-list.md)로 위임한다.

## 결과 미리보기

![Chapter20 GamePlay storyboard](../../_assets/captures/part4_chapter20_01_gameplay.png)

시연 video에서 선택한 4.260s, 14.200s, 24.140s frame을 순서대로 배치한다. 상단 `01`부터 `03`까지와 timestamp는 gameplay destruction 진행 순서를 기록한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | command argument `2001`, fire input `G`, character animation state, projectile spawn offset와 velocity |
| 출력 | 4.260s, 14.200s, 24.140s timestamp frame으로 구성한 fire projectile과 destruction storyboard |

## 구현 흐름

1. `InitPhysics`가 gravity scene, static ground plane과 dynamic stack을 구성한다.
2. input edge가 fire cooldown 조건을 만족하면 fire animation state와 frame index를 초기화한다.
3. animation frame이 notify frame에 도달하면 `FireProjectile`이 render position을 physics position으로 변환해 dynamic sphere를 생성한다.
4. `CreateDynamic`이 projectile actor와 fire billboard model을 만들고 velocity를 actor에 설정한다.
5. character animation을 갱신한 뒤 PhysX scene을 fixed time step으로 simulate하고 result를 fetch한다.
6. projectile을 포함한 dynamic actor pose를 render scale로 변환해 world matrix와 constant buffer에 반영한다.

## 핵심 구현

- [PhysX scene, ground plane과 block stack 초기화](../../../Part4_Chapter14-20/Ex2001_GamePlay.cpp#L137)
- [Projectile actor와 fire billboard 생성](../../../Part4_Chapter14-20/Ex2001_GamePlay.cpp#L171)
- [Render position에서 PhysX position으로 변환하는 fire spawn](../../../Part4_Chapter14-20/Ex2001_GamePlay.cpp#L216)
- [Fire animation notify와 projectile 생성](../../../Part4_Chapter14-20/Ex2001_GamePlay.cpp#L239)
- [Physics pose를 render scale과 world transform으로 동기화](../../../Part4_Chapter14-20/Ex2001_GamePlay.cpp#L284)

## 시각 결과

Storyboard는 fire animation 이후 projectile이 block stack과 상호작용하며 destruction state가 진행되는 구간을 기록한다. 세 frame은 animation state, projectile actor와 dynamic object transform이 같은 frame update에 결합된 rendered evidence다.

## 구현 범위와 한계

- fire input은 `G` key와 cooldown으로 제한하며 general gameplay input mapping을 구현하지 않는다.
- animation sampling은 frame index 기반이고 frame-rate independent time sampling을 구현하지 않는다.
- projectile effect는 billboard와 PhysX sphere actor의 쌍이며 impact event, damage system과 collision callback을 구현하지 않는다.
- Storyboard는 선택한 gameplay frame이며 interactive session 전체를 대체하지 않는다.
- character, animation, texture 원본 asset은 첨부하거나 직접 링크하지 않고 rendered storyboard evidence만 사용한다.
- 원본 MP4와 raw preview는 Git에 추가하지 않는다.

## 검증

- 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공
- Storyboard PNG는 `1880x444` RGBA, non-interlaced이며 full decode와 metadata chunk 부재를 확인함

## 관련 코드

- [ExampleDocs](../../../Part4_Chapter14-20/ExampleDocs/20_01_GamePlay.md)
- [Example selection entry point](../../../Part4_Chapter14-20/main.cpp)

## 관련 문서

- [Demo Index](demo-index.md)
- [Animation Physics And Gameplay Integration](../../01_Topics/AnimationAndPhysics/AnimationPhysicsAndGameplayIntegration.md)
- [WorkLog WU-Part4](../../04_WorkLogs/work-units/WU-Part4.md)