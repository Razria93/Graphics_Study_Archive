# 09 UserInteraction Step4 QuaternianRotation

Quaternion을 이용해 sphere의 회전을 제어하는 예제입니다. Raw 폴더명은 `QuaternianRotation`으로 되어 있어 archive에서도 그대로 유지합니다.

## 핵심 주제

| 항목 | 내용 |
| --- | --- |
| Quaternion rotation | axis-angle 값을 quaternion으로 구성하고 회전 matrix로 변환 |
| Euler angle comparison | Euler angles 기반 회전과 quaternion 기반 회전 흐름 비교 |
| Model transform | sphere의 world transform을 quaternion rotation과 translation으로 구성 |
| Picking continuity | Step3의 ray-sphere collision 흐름을 유지 |
| Asset dependency | skybox cubemap과 `earth.jpg` sphere texture 재사용 |

## 포함한 파일

- Source/project: `Part3_Chapter09/09_UserInteraction_Step4_QuaternianRotation`
- Required assets:
  - Step1에서 포함한 skybox cubemap DDS assets
  - Step3에서 포함한 `Part3_Chapter09/Assets/Textures/earth.jpg`

## 제외한 항목

- `.vs/`, `x64/`, generated folder, `.vcxproj.user`, `imgui.ini`
- raw-local formatting file `.clang-format`
- raw output/capture files

## Archive Notes

- raw folder/project spelling은 `QuaternianRotation`으로 유지합니다.
- 문서 설명에서는 일반적인 용어인 quaternion rotation을 사용합니다.
- `.clang-format` 파일은 archive에 포함하지 않으므로 project/filter 참조에서도 제거했습니다.
- `earth.jpg`와 cubemap assets는 private archive 실행 재현용입니다. Public 공개 전에는 출처/라이선스 검토가 필요합니다.

