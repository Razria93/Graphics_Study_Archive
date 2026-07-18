# Ex1801 Tree Status

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 반영 완료 |
| Build Debug x64 | 확인 완료 |
| Run Debug x64 | 확인 완료 |
| Build Release x64 | 확인 완료 |
| Run Release x64 | 확인 완료 |
| Runtime asset | 반영 완료 |
| Public readiness | 검토 필요 |

## 확인 내용

- `main.cpp`는 command argument `1801`을 `Ex1801_Tree`로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1801_Tree.cpp/.h`가 등록되어 있습니다.
- `Ex1801_Tree.cpp/.h`는 primary raw와 동일합니다.
- `Ex1801_Tree.cpp`는 `../Assets/Foliage/Gledista_Triacanthos_FBX/Gledista_Triacanthos_3.fbx`를 로드합니다.
- 필요한 foliage runtime asset만 선별 반영했습니다.
- raw result/capture/build output은 포함하지 않았습니다.
- foliage `.fbx`는 LFS 추적 대상입니다.
- foliage `.jpg` texture는 public 공개 전 license/source 검토가 필요합니다.

## 실행 확인 결과

- Debug x64 build/run: 사용자 확인 완료
- Release x64 build/run: 사용자 확인 완료
- Command arguments: `1801`
- 확인일: 2026-07-18

## 보류 항목

- public 공개 가능 여부는 foliage FBX/JPG asset license/source 검토 후 판단합니다.
