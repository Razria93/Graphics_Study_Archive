# Ex1801 Tree Status

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

- `main.cpp`는 command argument `1801`을 `Ex1801_Tree`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1801_Tree.cpp/.h`가 등록되어 있습니다.
- `Ex1801_Tree.cpp/.h`는 primary raw와 동일합니다.
- `Ex1801_Tree.cpp`는 `../Assets/Foliage/Gledista_Triacanthos_FBX/Gledista_Triacanthos_3.fbx`를 로드합니다.
- 필요한 foliage runtime asset만 선별 반영했습니다.
- raw result/capture/build output은 포함하지 않았습니다.
- foliage `.fbx`는 LFS 추적 대상입니다.
- foliage `.jpg` texture는 public 공개 전 license/source 검토가 필요합니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1801`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. tree model이 scene에 표시되는지 확인합니다.
6. ground, skybox/IBL, GUI가 정상 표시되는지 확인합니다.

## 보류 항목

- Debug/Release 실행 확인 결과는 사용자 확인 후 기록합니다.
- public 공개 가능 여부는 foliage FBX/JPG asset license/source 검토 후 판단합니다.
