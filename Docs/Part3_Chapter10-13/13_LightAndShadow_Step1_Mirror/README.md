# 13 Light and Shadow Step1 Mirror

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step1_Mirror`
- Reference-only raw source: `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step1_Mirror`
- Build/run status: 미확인
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 stencil buffer를 이용해 mirror 영역을 마스킹하고, 반사된 장면을 해당 영역에만 다시 렌더링하는 흐름을 확인하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- mirror plane을 먼저 그려 stencil 값을 기록하는 단계
- stencil 값이 기록된 픽셀에만 reflected scene을 그리는 단계
- mirror surface, reflected object, 일반 scene을 그릴 때 depth/stencil state를 나누는 방식
- 이전 PBR/HDR pipeline에서 사용한 Sample HDRI cubemap과 UV grid texture를 재사용하는 방식

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- `_2` folder는 reference-only snapshot으로만 유지합니다.
- `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`는 archive 대상에서 제외했습니다.
- Release build shader compile 재현성을 위해 `CubeMappingPS.hlsl` Release shader model을 `5.0`으로 맞추고, 일부 shader의 Release shader model 누락을 보정했습니다.
- 실행에 필요한 HDRI DDS와 `blender_uv_grid_2k.png`는 이전 Part3 import에서 이미 archive에 포함된 asset을 재사용합니다.
- main object는 raw/origin 기본 활성 상태였던 box 대신, 주석으로 제공되어 있던 `armored-female-future-soldier` character asset 로딩 경로를 활성화했습니다.

## Next Check

- Visual Studio에서 Debug x64 build/run 확인
- Visual Studio에서 Release x64 build/run 확인
- mirror/stencil 동작이 화면에 정상적으로 나타나는지 확인
