# Ex2001 GamePlay Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 보강 반영 |
| Build Debug x64 | 성공 |
| Run Debug x64 | 성공 |
| Build Release x64 | 성공 |
| Run Release x64 | 성공 |
| Runtime asset | 보강 반영 |
| Public readiness | 검토 필요 |

## 확인 내용

- `main.cpp`는 command argument `2001`을 `Ex2001_GamePlay`로 매핑합니다.
- `Examples.vcxproj`와 `Examples.vcxproj.filters`에는 `Ex2001_GamePlay.cpp/.h`가 등록되어 있습니다.
- archive의 `Ex2001_GamePlay.cpp/.h`는 primary raw를 기준으로 가져온 뒤, 강의 TODO였던 fireball gameplay input을 최소 범위로 보강했습니다.
- 최신 자료실본 `Part4_HongLabGraphics_v03`의 Ex2001은 주석/포맷 정리와 PhysX include path, `PX_RELEASE` 매크로 정의 차이가 있습니다.
- archive는 현재 vcpkg include 구조에 맞춰 `physx/PxPhysicsAPI.h`를 유지합니다.
- Release 실행 중 `FightingIdleOnMichelle2.fbx`, `Fireball.fbx` 누락을 확인했습니다.
- `Assets/Characters/Mixamo/FightingIdleOnMichelle2.fbx`와 `Assets/Characters/Mixamo/Fireball.fbx`를 primary raw에서 선별 반영했습니다.
- 두 FBX asset hash는 primary raw와 일치합니다.
- `G` 입력 시 Fireball animation clip으로 전환하고, GUI에서 지정한 notify frame에 PhysX dynamic fireball을 생성하도록 구현했습니다.
- `Fireball` GUI에서 캐릭터 기준 spawn offset, projectile velocity, notify frame을 조절할 수 있도록 했습니다.
- 사용자 실행 확인 결과, `Notify Frame = 120`, `Spawn Offset = (0.0, 0.0, -0.25)` 기준에서 위치와 타이밍이 의도와 유사하게 동작했습니다.
- Debug/Release x64 모두 build/run을 확인했습니다.
- PhysX actor와 render object가 순회 순서에 의존하지 않도록 직접 매핑 기반 pose sync로 보강했습니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `2001`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. character animation, PhysX box stack, PBR ground, HDRI lighting이 함께 표시되는지 확인합니다.
6. `G` 키 입력 시 fireball animation으로 전환되는지 확인합니다.
7. `Fireball > Notify Frame`에 도달했을 때 projectile spawn이 동작하는지 확인합니다.
8. `Fireball > Spawn Offset`, `Velocity` 조절이 발사 위치/방향에 반영되는지 확인합니다.
9. PhysX/Assimp/runtime DLL 오류가 없는지 확인합니다.

## 보류 항목

- public 공개 가능 여부는 Mixamo/PBR/HDRI/PhysX dependency와 asset license/source 검토 후 판단합니다.
