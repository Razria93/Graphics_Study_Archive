# Ex1605 SmokeCpu Status

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

- `main.cpp`는 command argument `1605`를 `Ex1605_SmokeCpu`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1605_SmokeCpu.cpp/.h`, `FluidSimulationCPU.cpp/.h`, `Texture3D.h`, `VolumeSmokePS.hlsl`이 등록되어 있습니다.
- `Ex1605_SmokeCpu.cpp/.h`, `FluidSimulationCPU.cpp/.h`, `VolumeSmokePS.hlsl`, `Texture3D.h`, `main.cpp`는 primary raw와 hash가 일치합니다.
- `Assets/Textures/Cubemaps/HDRI/Sample*.dds` 4개는 Ex1604 기준 기록에서 root `Assets` 실행 경로에 반영되어 있습니다.
- `Examples.vcxproj`는 archive 환경 보정 때문에 primary raw와 hash가 다릅니다. 차이는 개인 vcpkg include path 제거, `VCPKG_ROOT` 조건부 include path, `.clang-format` project item 제거입니다.
- HLSL/HLSLI BOM 확인 결과 `VolumeSmokePS.hlsl`, `Common.hlsli`는 `EF BB BF`로 시작하지 않습니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1605`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. volume smoke와 bounding box가 렌더링되는지 확인합니다.
6. CPU simulation density가 화면에서 시간에 따라 갱신되는지 확인합니다.
