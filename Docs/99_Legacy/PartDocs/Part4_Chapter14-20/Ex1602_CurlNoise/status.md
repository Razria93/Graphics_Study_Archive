# Ex1602 CurlNoise Status

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

- `main.cpp`는 command argument `1602`를 `Ex1602_CurlNoise`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1602_CurlNoise.cpp/.h`와 `Ex1602_CurlNoiseCS.hlsl`이 등록되어 있습니다.
- `Ex1602_CurlNoise.cpp/.h`, `Ex1602_CurlNoiseCS.hlsl`은 primary raw와 hash가 일치합니다.
- 별도 이미지, 모델, DDS, EXR, HDR asset은 필요하지 않습니다.
- 사용자 확인 기준으로 Debug/Release x64 모두 실행 확인 완료입니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1602`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. particle trail 또는 density 누적 결과가 시간에 따라 움직이는지 확인합니다.
