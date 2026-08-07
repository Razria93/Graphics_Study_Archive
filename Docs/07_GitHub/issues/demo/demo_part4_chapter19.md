# Part4 Chapter19 PhysX Demo

## 요약

Chapter19는 PhysX rigid-body scene을 fixed time step으로 갱신하고, actor shape pose를 render model world transform에 반영하는 physics integration evidence다. 대표 visual은 `Ex1901_PhysX` 시연 video에서 선택한 timestamp frame 3개를 배치한 storyboard로 구성한다.

## 핵심 목표

- PhysX foundation, dispatcher, gravity scene과 material 초기화 기록
- Static ground plane과 rigid dynamic block stack 구성 확인
- Fixed-step simulation 결과를 render world transform에 동기화한 collapse evidence 확보

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | 없음 | 단일 screenshot 대신 timestamp storyboard를 사용함 |
| Result image | Chapter19 storyboard 1장 | 1.415s, 4.717s, 8.018s frame을 배치한 block wall collapse evidence |
| Video | 없음 | GitHub attachment URL을 아직 게시하지 않음 |

## 시각 정보

### Rigid-body block collapse

`Ex1901_PhysX`는 static ground와 rigid dynamic block wall을 PhysX scene에 추가하고, simulation result의 actor pose를 render model world matrix에 반영한다. Storyboard는 1.415s, 4.717s, 8.018s frame을 순서대로 기록한다.

![Rigid-body block collapse](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter19_01_physx.png?raw=true)

## 구현 하이라이트

### PhysX scene construction

`InitPhysics`는 foundation, physics instance, dispatcher, gravity scene과 material을 만들고 default simulation filter를 설정한다. Scene에는 static ground plane과 `createStack`으로 만든 rigid dynamic block wall이 배치된다.

- [PhysX foundation, gravity scene과 material 초기화](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1901_Physx.cpp#L13-L55)
- [Ground plane과 rigid dynamic stack 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1901_Physx.cpp#L57-L78)

### Fixed-step simulation and render synchronization

Frame update는 `simulate(1.0f / 60.0f)`와 `fetchResults(true)`로 fixed time step 결과를 확보한다. 그 뒤 scene actor와 shape를 순회해 dynamic actor global pose를 읽고 render model world matrix와 constant buffer에 반영한다.

- [Fixed-step simulation과 result fetch](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1901_Physx.cpp#L85-L93)
- [Actor shape pose를 render world transform으로 동기화](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1901_Physx.cpp#L99-L123)

### 처리 흐름

1. `Examples.exe` command argument `1901`로 PhysX 예제를 선택한다.
2. PhysX scene, static plane, dynamic block stack을 초기화한다.
3. 매 frame fixed time step으로 scene simulation을 수행하고 result를 fetch한다.
4. Actor pose를 render model world transform과 constant buffer에 반영한다.
5. 시연 video에서 선택한 collapse frame 3개를 storyboard로 기록한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void UpdatePhysXScenePseudo()
{
	physicsScene->simulate(1.0f / 60.0f);
	physicsScene->fetchResults(true);

	for (PhysicsActor actor : physicsScene->GetActors()) {
		Transform pose = actor.GetGlobalPose();
		UpdateRenderModelWorldMatrix(actor, pose);
	}

	RenderSynchronizedScene();
}
```

원본 코드: [PhysX update와 render transform sync](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1901_Physx.cpp#L85-L123)

## 검증 상태

- `Part4_Chapter14-20/Examples.sln` Debug x64 build/run/capture smoke 성공
- `Part4_Chapter14-20/Examples.sln` Release x64 build/run/capture smoke 성공
- Storyboard PNG는 `ComputerGraphics` title, 01부터 03까지 timestamp frame, full decode와 text metadata chunk 부재를 확인함

## 구현 범위와 한계

- Simulation step은 `1.0f / 60.0f` fixed value이며 frame time accumulator를 구현하지 않는다.
- Actor pose와 render transform은 같은 scale을 사용하므로 별도 unit conversion을 적용하지 않는다.
- Collision event callback과 contact impulse 분석은 실행 경로가 아니다.
- Storyboard는 선택한 collapse frame이며 연속 collision dynamics 전체를 대체하지 않는다.
- 원본 MP4와 raw preview는 Git에 추가하지 않는다.

## 관련 문서

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex1901 PhysX 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/19_01_PhysX.md)
- [Chapter19 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Animation Physics And Gameplay Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/AnimationAndPhysics/AnimationPhysicsAndGameplayIntegration.md)