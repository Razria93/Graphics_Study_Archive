# Ex1802 Grass Status

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

- `main.cpp`는 command argument `1802`를 `Ex1802_Grass`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1802_Grass.cpp/.h`, `Ex1802_GrassVS.hlsl`, `Ex1802_GrassPS.hlsl`이 등록되어 있습니다.
- `Ex1802_Grass.cpp/.h`와 전용 HLSL files는 primary raw와 동일합니다.
- `GraphicsCommon.*`의 grass shader/input layout/PSO 등록은 primary raw와 동일합니다.
- 이 예제는 기존 PBR ground textures와 HDRI cubemap을 재사용합니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 결과

- Debug x64 build/run: 사용자 확인 완료
- Release x64 build/run: 사용자 확인 완료
- Command arguments: `1802`
- 확인일: 2026-07-18

## 보류 항목

- public 공개 가능 여부는 기존 texture/HDRI asset license/source 검토 후 판단합니다.
