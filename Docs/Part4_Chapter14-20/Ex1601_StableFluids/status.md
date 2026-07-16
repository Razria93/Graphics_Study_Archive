# Ex1601 StableFluids Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 반영 완료 |
| Build Debug x64 | 미확인 |
| Run Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Release x64 | 미확인 |
| Runtime asset | 없음 |
| Public readiness | 검토 필요 |

## 확인한 내용

- `main.cpp`는 command argument `1601`을 `Ex1601_StableFluids`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1601_StableFluids.cpp`, `StableFluids.cpp`, 관련 headers와 Ex1601 compute shaders가 등록되어 있습니다.
- `Ex1601_StableFluids.cpp/.h`, `StableFluids.cpp/.h`는 primary raw와 hash가 일치합니다.
- 별도 이미지, 모델, DDS, EXR, HDR asset은 필요하지 않습니다.
- Debug/Release x64 실행 확인 전까지 build/run은 `미확인`으로 유지합니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1601`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. 화면에 density가 보이지 않으면 좌클릭 또는 좌클릭 드래그로 source를 주입합니다.
6. 좌클릭 드래그에 따라 색이 번지고 흐르는지 확인합니다.
