# 09 UserInteraction Step5 VirtualTrackball

Mouse drag 입력을 sphere 위의 두 방향 벡터 변화로 해석하고, `Quaternion::FromToRotation()`으로 virtual trackball 회전을 적용하는 예제입니다.

## 핵심 주제

| 항목 | 내용 |
| --- | --- |
| Virtual trackball | mouse drag를 sphere 표면 방향 벡터 변화로 변환 |
| Quaternion from-to rotation | 이전 벡터와 현재 벡터 사이 회전을 quaternion으로 계산 |
| Accumulated rotation | drag 중 계산한 회전을 model transform에 반영 |
| Ray-sphere picking | Step3의 picking ray와 sphere collision 흐름 재사용 |
| Asset dependency | skybox cubemap과 `earth.jpg` sphere texture 재사용 |

## 포함한 파일

- Source/project: `Part3_Chapter09/09_UserInteraction_Step5_VirtualTrackball`
- Required assets:
  - Step1에서 포함한 skybox cubemap DDS assets
  - Step3에서 포함한 `Part3_Chapter09/Assets/Textures/earth.jpg`

## 제외한 항목

- `.vs/`, `x64/`, generated folder, `.vcxproj.user`, `imgui.ini`
- raw-local formatting file `.clang-format`
- `_Debug` variant
- raw output/capture files

## Archive Notes

- mainline `09_UserInteraction_Step5_VirtualTrackball`을 archive 실행 기준으로 반영했습니다.
- `_Debug` variant는 중간 벡터 출력과 실험 흔적이 더 강해 reference-only로 제외했습니다.
- `.clang-format` 파일은 archive에 포함하지 않으므로 project/filter 참조에서도 제거했습니다.
- `earth.jpg`와 cubemap assets는 private archive 실행 재현용입니다. Public 공개 전에는 출처/라이선스 검토가 필요합니다.

