# Ex1802 Grass Status

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

- `main.cpp`는 command argument `1802`를 `Ex1802_Grass`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1802_Grass.cpp/.h`, `Ex1802_GrassVS.hlsl`, `Ex1802_GrassPS.hlsl`이 등록되어 있습니다.
- `Ex1802_Grass.cpp/.h`와 전용 HLSL files는 primary raw와 동일합니다.
- `GraphicsCommon.*`의 grass shader/input layout/PSO 등록은 primary raw와 동일합니다.
- 이 예제는 기존 PBR ground textures와 HDRI cubemap을 재사용합니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1802`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. grass instances가 ground 위에 대량으로 표시되는지 확인합니다.
6. `Wind` GUI slider를 조작했을 때 grass deformation이 변하는지 확인합니다.

## 보류 항목

- Debug/Release 실행 확인 결과는 사용자 확인 후 기록합니다.
- public 공개 가능 여부는 기존 texture/HDRI asset license/source 검토 후 판단합니다.
