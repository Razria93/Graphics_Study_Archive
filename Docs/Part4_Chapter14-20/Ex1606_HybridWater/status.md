# Ex1606 HybridWater Status

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

- `main.cpp`는 command argument `1606`을 `Ex1606_HybridWater`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1606_HybridWater.cpp/.h`와 Ex1606 shader files가 등록되어 있습니다.
- `Ex1606_HybridWater.cpp/.h`, Ex1606 shader files, `MarchingCubes.h`, `main.cpp`는 primary raw와 hash가 일치합니다.
- `Ex1606_Common.hlsli`는 shader include file이므로 `None` item으로 등록되어 있습니다.
- Ex1606 shader files는 Debug/Release x64에서 shader model `5.0`입니다.
- Ex1606 HLSL/HLSLI BOM 확인 결과 `EF BB BF`로 시작하지 않습니다.
- 외부 runtime asset은 현재 필요하지 않습니다. `InitCubemaps()`는 주석 처리되어 있고 noise texture는 코드에서 생성합니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1606`으로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. 기본 SDF raycasting 결과와 bounding box가 렌더링되는지 확인합니다.
6. `RenderParticles`, `RenderDensity`, `RenderMarchingCubes`, `RenderWired`, `RenderRaycasting` GUI 토글을 확인합니다.
