# Ex1803 Landscape Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 보정 반영 |
| Build Debug x64 | 미확인 |
| Run Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Release x64 | 미확인 |
| Runtime asset | 반영 완료 |
| Public readiness | 검토 필요 |

## 확인 내용

- `main.cpp`는 command argument `1803`을 `Ex1803_Landscape`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1803_Landscape.cpp/.h`, `Ex1803_OceanPS.hlsl`이 등록되어 있습니다.
- `Ex1803_Landscape.h`, `Ex1803_OceanPS.hlsl`, `OceanModel.h`는 primary raw와 동일합니다.
- primary raw의 terrain FBX runtime asset은 현재 raw/reference repo에 없습니다.
- archive는 `Assets/Textures/terrain.raw`를 사용해 height-field terrain mesh를 생성하도록 `Ex1803_Landscape.cpp`를 보정했습니다.
- `terrain.raw` hash는 primary raw asset과 일치합니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1803`으로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. terrain height field와 ocean plane이 표시되는지 확인합니다.
6. `OceanHeight` GUI slider 조작 시 ocean plane 높이가 변하는지 확인합니다.

## 보류 항목

- Debug/Release 실행 확인 결과는 사용자 확인 후 기록합니다.
- public 공개 가능 여부는 `terrain.raw`와 HDRI asset license/source 검토 후 판단합니다.
