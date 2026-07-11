# 09 UserInteraction Step1 FirstPersonView

First-person camera 조작과 cubemap skybox, textured ground를 함께 확인하는 Part3 Chapter09의 첫 번째 예제입니다.

## 핵심 주제

| 항목 | 내용 |
| --- | --- |
| Camera control | keyboard/mouse 입력으로 camera position과 view direction 갱신 |
| View/projection | camera matrix를 constant buffer로 전달 |
| Cubemap skybox | DDS cubemap을 사용해 배경 environment 렌더링 |
| Texture loading | `stb_image.h`와 DDS loader를 함께 사용하는 texture path 확인 |
| Asset dependency | skybox DDS 3개와 ground texture 1개가 실행에 필요 |

## 포함한 파일

- Source/project: `Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView`
- Required assets:
  - `Part3_Chapter09/Assets/Textures/blender_uv_grid_2k.png`
  - `Part3_Chapter09/Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds`
  - `Part3_Chapter09/Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds`
  - `Part3_Chapter09/Assets/Textures/Cubemaps/skybox/cubemap_specular.dds`

## 제외한 항목

- `.vs/`, `x64/`, generated folder, `.vcxproj.user`, `imgui.ini`
- raw-local formatting file `.clang-format`
- raw output/capture files

## Archive Notes

- `Common.hlsli`는 shader compile 대상이 아니라 include/reference file로 유지합니다.
- `.clang-format` 파일은 archive에 포함하지 않으므로 project/filter 참조에서도 제거했습니다.
- `D3D11Utils.cpp`가 `stb_image.h`를 include하므로 `Part3_Chapter09/Directory.Build.props`에서 repo-local `ThirdParty/stb` include path를 제공합니다.
- 포함된 texture/cubemap asset은 private archive 실행 재현용입니다. Public 공개 전에는 출처/라이선스 검토가 필요합니다.

