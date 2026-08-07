# Part4 Chapter20 Gameplay Physics Demo

## 요약

Chapter20은 character fire animation notify frame에서 PhysX projectile과 fire billboard를 만들고, physics simulation pose를 render transform으로 동기화하는 gameplay integration evidence다. 대표 visual은 `Ex2001_GamePlay` 시연 video에서 선택한 timestamp frame 3개를 배치한 storyboard로 구성한다. character, animation, texture 원본 asset은 직접 게시하지 않고 rendered storyboard만 사용한다.

## 핵심 목표

- Fire input edge, cooldown, animation state와 notify frame 연결 기록
- Projectile actor와 fire billboard pair 생성 및 initial velocity 설정 확인
- PhysX scene simulation pose와 gameplay destruction render transform 동기화 기록

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | 없음 | 단일 screenshot 대신 timestamp storyboard를 사용함 |
| Result image | Chapter20 storyboard 1장 | 4.260s, 14.200s, 24.140s frame을 배치한 projectile destruction evidence |
| Video | 없음 | GitHub attachment URL을 아직 게시하지 않음 |

## 시각 정보

### Projectile-driven destruction

`Ex2001_GamePlay`은 fire animation notify frame에서 projectile actor와 fire billboard를 생성하고, dynamic object pose를 render world matrix에 반영한다. Storyboard는 4.260s, 14.200s, 24.140s frame을 순서대로 기록한다.

![Projectile-driven destruction](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter20_01_gameplay.png?raw=true)

## 구현 하이라이트

### Fire input, animation notify and projectile spawn

Fire input edge가 cooldown 조건을 만족하면 fire animation state와 frame index를 초기화한다. Animation frame이 notify frame에 도달하면 `FireProjectile`이 render position을 physics position으로 변환해 dynamic sphere actor와 fire billboard model을 생성한다.

- [PhysX scene, ground plane과 block stack 초기화](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex2001_GamePlay.cpp#L137-L168)
- [Projectile actor와 fire billboard 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex2001_GamePlay.cpp#L171-L214)
- [Fire animation notify와 projectile 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex2001_GamePlay.cpp#L239-L256)

### Physics pose to render transform sync

Character animation을 갱신한 뒤 PhysX scene을 fixed time step으로 simulate하고 result를 fetch한다. Projectile을 포함한 dynamic actor pose는 render scale로 변환되어 world matrix와 constant buffer에 반영된다.

- [Render position에서 PhysX position으로 변환하는 fire spawn](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex2001_GamePlay.cpp#L216-L237)
- [Physics pose를 render scale과 world transform으로 동기화](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex2001_GamePlay.cpp#L284-L313)

### 처리 흐름

1. `Examples.exe` command argument `2001`로 gameplay 예제를 선택한다.
2. PhysX scene, static plane과 dynamic stack을 구성한다.
3. Fire input edge가 cooldown을 통과하면 fire animation state를 시작한다.
4. Notify frame에서 projectile actor와 fire billboard model을 생성한다.
5. Physics simulation pose를 render world transform으로 동기화하고 destruction 진행을 표시한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void UpdateGameplayPhysicsPseudo(Input input)
{
	if (input.FirePressed() && CanStartFireAnimation()) {
		StartFireAnimation();
	}

	UpdateCharacterAnimationFrame();
	if (ReachedFireNotifyFrame()) {
		SpawnProjectileActorAndBillboard();
	}

	SimulatePhysXFixedStep();
	SyncDynamicActorPoseToRenderModels();
	RenderGameplayScene();
}
```

원본 코드: [Fire animation notify와 physics sync](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex2001_GamePlay.cpp#L239-L313)

## 검증 상태

- `Part4_Chapter14-20/Examples.sln` Debug x64 build/run/capture smoke 성공
- `Part4_Chapter14-20/Examples.sln` Release x64 build/run/capture smoke 성공
- Storyboard PNG는 `ComputerGraphics` title, 01부터 03까지 timestamp frame, full decode와 text metadata chunk 부재를 확인함

## 구현 범위와 한계

- Fire input은 `G` key와 cooldown으로 제한하며 general gameplay input mapping을 구현하지 않는다.
- Animation sampling은 frame index 기반이고 frame-rate independent time sampling을 구현하지 않는다.
- Projectile effect는 billboard와 PhysX sphere actor의 pair이며 impact event, damage system과 collision callback을 구현하지 않는다.
- Storyboard는 선택한 gameplay frame이며 interactive session 전체를 대체하지 않는다.
- Character, animation, texture 원본 asset은 첨부하거나 직접 링크하지 않는다.
- 원본 MP4와 raw preview는 Git에 추가하지 않는다.

## 관련 문서

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex2001 GamePlay 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/20_01_GamePlay.md)
- [Chapter20 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Animation Physics And Gameplay Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/AnimationAndPhysics/AnimationPhysicsAndGameplayIntegration.md)