# 09 UserInteraction Step6 MouseDragMove

Mouse drag 입력으로 선택된 sphere의 위치를 이동시키는 Chapter09 마지막 예제입니다.

## 핵심 주제

| 항목 | 내용 |
| --- | --- |
| Mouse drag movement | 이전/현재 picking 위치 차이를 translation으로 변환 |
| Object translation | drag delta를 sphere의 model transform에 누적 반영 |
| Bounding volume sync | 이동 후 `BoundingSphere.Center`를 model transform translation으로 갱신 |
| Picking continuity | ray-sphere collision과 cursor sphere 표시 흐름 유지 |
| Asset dependency | skybox cubemap과 `earth.jpg` sphere texture 재사용 |

## 포함한 파일

- Source/project: `Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove`
- Required assets:
  - Step1에서 포함한 skybox cubemap DDS assets
  - Step3에서 포함한 `Part3_Chapter09/Assets/Textures/earth.jpg`

## 제외한 항목

- `.vs/`, `x64/`, generated folder, `.vcxproj.user`, `imgui.ini`
- raw-local formatting file `.clang-format`
- raw output/capture files

## Archive Notes

- Step6는 Chapter09의 마지막 예제로, virtual trackball 이후 object drag translation 흐름을 확인합니다.
- `.clang-format` 파일은 archive에 포함하지 않으므로 project/filter 참조에서도 제거했습니다.
- `earth.jpg`와 cubemap assets는 private archive 실행 재현용입니다. Public 공개 전에는 출처/라이선스 검토가 필요합니다.

