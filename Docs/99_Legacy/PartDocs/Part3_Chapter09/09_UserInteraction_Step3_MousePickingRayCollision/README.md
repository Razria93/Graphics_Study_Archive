# 09 UserInteraction Step3 MousePickingRayCollision

Mouse picking ray와 scene의 bounding volume 충돌을 계산해 hit point를 확인하는 예제입니다.

## 핵심 주제

| 항목 | 내용 |
| --- | --- |
| Picking ray | screen-space mouse position에서 world-space ray를 구성 |
| Ray collision | `DirectXCollision`의 `Ray`와 `BoundingSphere` 충돌 판정 |
| Hit visualization | 충돌 위치에 cursor sphere를 표시하는 흐름 |
| Coordinate spaces | screen, view, projection, world 좌표 변환 확인 |
| Asset dependency | skybox cubemap과 `earth.jpg` sphere texture 사용 |

## 포함한 파일

- Source/project: `Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision`
- Required assets:
  - Step1에서 포함한 skybox cubemap DDS assets
  - `Part3_Chapter09/Assets/Textures/earth.jpg`

## 제외한 항목

- `.vs/`, `x64/`, generated folder, `.vcxproj.user`, `imgui.ini`
- raw-local formatting file `.clang-format`
- mainline variant
- `_Debug` variant
- raw output/capture files

## Archive Notes

- mainline과 `_Debug` variant는 완성되지 않은 작업본이므로 이번 archive 실행 기준에서 제외했습니다.
- archive code는 raw `_Solution` variant 기준으로 반영했습니다.
- mainline `ExampleApp.cpp`에 남아 있는 시행착오성 주석과 TODO는 이후 문서 정리 단계에서 참고할 source memo 후보입니다.
- `.clang-format` 파일은 archive에 포함하지 않으므로 project/filter 참조에서도 제거했습니다.
- `earth.jpg`는 private archive 실행 재현용입니다. Public 공개 전에는 출처/라이선스 검토가 필요합니다.
