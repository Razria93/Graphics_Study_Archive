# Ex1901 Physics Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 반영 완료 |
| Build Debug x64 | 확인 완료 |
| Run Debug x64 | 확인 완료 |
| Build Release x64 | 확인 완료 |
| Run Release x64 | 확인 완료 |
| Runtime asset | 기존 asset 재사용 |
| Public readiness | 검토 필요 |

## 확인 내용

- `main.cpp`는 command argument `1901`을 `Ex1901_PhysX`로 매핑합니다.
- `Examples.vcxproj`와 `Examples.vcxproj.filters`에는 `Ex1901_Physx.cpp/.h`가 등록되어 있습니다.
- archive의 `Ex1901_Physx.cpp/.h`는 primary raw와 동일합니다.
- 최신 자료실본 `Part4_HongLabGraphics_v03`의 Ex1901은 주석/포맷 정리와 PhysX include path, `PX_RELEASE` 매크로 정의 차이가 있습니다.
- archive는 현재 vcpkg include 구조에 맞춰 `physx/PxPhysicsAPI.h`를 유지합니다.
- 별도 신규 runtime asset copy는 없습니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 결과

- Debug x64 build/run: 사용자 확인 완료
- Release x64 build/run: 사용자 확인 완료
- Command arguments: `1901`
- 확인일: 2026-07-18

## 보류 항목

- public 공개 가능 여부는 PhysX/vcpkg dependency와 기존 asset license/source 검토 후 판단합니다.
