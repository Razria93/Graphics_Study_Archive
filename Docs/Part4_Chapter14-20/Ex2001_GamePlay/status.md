# Ex2001 GamePlay Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 반영 완료 |
| Build Debug x64 | 미확인 |
| Run Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Release x64 | 미확인 |
| Runtime asset | 기존 asset 재사용 |
| Public readiness | 검토 필요 |

## 확인 내용

- `main.cpp`는 command argument `2001`을 `Ex2001_GamePlay`로 매핑합니다.
- `Examples.vcxproj`와 `Examples.vcxproj.filters`에는 `Ex2001_GamePlay.cpp/.h`가 등록되어 있습니다.
- archive의 `Ex2001_GamePlay.cpp/.h`는 primary raw와 동일합니다.
- 최신 자료실본 `Part4_HongLabGraphics_v03`의 Ex2001은 주석/포맷 정리와 PhysX include path, `PX_RELEASE` 매크로 정의 차이가 있습니다.
- archive는 현재 vcpkg include 구조에 맞춰 `physx/PxPhysicsAPI.h`를 유지합니다.
- 별도 신규 runtime asset copy는 없습니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `2001`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. character animation, PhysX box stack, PBR ground, HDRI lighting이 함께 표시되는지 확인합니다.
6. PhysX/Assimp/runtime DLL 오류가 없는지 확인합니다.

## 보류 항목

- Debug/Release 실행 확인 결과는 사용자 확인 후 기록합니다.
- public 공개 가능 여부는 Mixamo/PBR/HDRI/PhysX dependency와 asset license/source 검토 후 판단합니다.
