# Ex1604 RealtimeSmoke Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 반영 완료 |
| Build Debug x64 | 미확인 |
| Run Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Release x64 | 미확인 |
| Runtime asset | 반영 완료 |
| Public readiness | 검토 필요 |

## 확인한 내용

- `main.cpp`는 command argument `1604`를 `Ex1604_RealtimeSmoke`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1604_RealtimeSmoke.cpp/.h`와 Ex1604 compute shaders가 등록되어 있습니다.
- `Ex1604_RealtimeSmoke.cpp/.h`, `Ex1604_SourcingCS.hlsl`, `Ex1604_AdvectionCS.hlsl`은 primary raw와 hash가 일치합니다.
- `Assets/Textures/Cubemaps/HDRI/Sample*.dds` 4개는 기존 Part3 archive asset을 root `Assets` 실행 경로로 재사용 복사했습니다.
- `.dds` asset은 Git LFS 대상입니다.
- Debug/Release x64 실행 확인 전까지 build/run은 `미확인`으로 유지합니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1604`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. volume smoke와 bounding box가 렌더링되는지 확인합니다.
6. `Turbulence`, `Source`, `Buoyancy` GUI 조작이 결과에 반영되는지 확인합니다.
