# Ex1603 Cloud Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 반영 완료 |
| Build Debug x64 | 성공 |
| Run Debug x64 | 성공 |
| Build Release x64 | 성공 |
| Run Release x64 | 성공 |
| Runtime asset | 없음 |
| Public readiness | 검토 필요 |

## 확인한 내용

- `main.cpp`는 command argument `1603`을 `Ex1603_Cloud`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1603_Cloud.cpp/.h`, `CloudDensityCS.hlsl`, `CloudLightingCS.hlsl`이 등록되어 있습니다.
- `Ex1603_Cloud.cpp/.h`, `CloudDensityCS.hlsl`, `CloudLightingCS.hlsl`은 primary raw와 hash가 일치합니다.
- 현재 실행 경로에서는 별도 이미지, 모델, DDS, EXR, HDR asset을 요구하지 않습니다.
- 사용자 확인 기준으로 Debug/Release x64 모두 실행 확인 완료입니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1603`으로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. volume cloud가 렌더링되는지 확인합니다.
6. `LightAngle`, `LightAbsorption`, `DensityAbsorption`, `lightScale`, `Aniso` GUI 조작이 결과에 반영되는지 확인합니다.
