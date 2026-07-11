# 09 UserInteraction Step2 MousePicking

Mouse click 위치를 scene object 선택 정보로 변환하는 mouse picking 예제입니다.

## 핵심 주제

| 항목 | 내용 |
| --- | --- |
| Mouse picking | screen-space mouse position을 picking 정보로 변환 |
| Object id color | render target의 object index color를 읽어 선택 대상을 판별 |
| Camera interaction | Step1 first-person camera 흐름 위에 picking 입력을 추가 |
| CPU/GPU readback | GPU texture 결과를 CPU에서 읽을 수 있는 staging/readback 흐름 확인 |
| Asset dependency | Step1과 같은 skybox cubemap, ground texture를 사용 |

## 포함한 파일

- Source/project: `Part3_Chapter09/09_UserInteraction_Step2_MousePicking`
- Required assets: Step1에서 포함한 `Part3_Chapter09/Assets` selected assets 재사용

## 제외한 항목

- `.vs/`, `x64/`, generated folder, `.vcxproj.user`, `imgui.ini`
- raw-local formatting file `.clang-format`
- `_Debug` variant와 `memo.txt`
- raw output/capture files

## Archive Notes

- `09_UserInteraction_Step2_MousePicking_Debug`는 실험/메모 흔적이 섞여 있어 reference-only로 두고 archive에는 mainline만 반영했습니다.
- `.clang-format` 파일은 archive에 포함하지 않으므로 project/filter 참조에서도 제거했습니다.
- `Common.hlsli`는 shader compile 대상이 아니라 include/reference file로 유지합니다.
- `D3D11Utils.cpp`가 `stb_image.h`를 include하므로 Step1에서 추가한 `Part3_Chapter09/Directory.Build.props`를 그대로 사용합니다.

