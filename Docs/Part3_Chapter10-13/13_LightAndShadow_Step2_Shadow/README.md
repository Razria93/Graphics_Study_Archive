# 13 Light and Shadow Step2 Shadow

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step2_Shadow`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step2_Shadow`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step2_Shadow`
- Build/run status: 미확인
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 shadow map을 만들고, 그 shadow map을 scene shading 단계에서 참조하는 기본 흐름을 확인하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- light view/projection 기준으로 scene depth를 shadow texture에 렌더링하는 단계
- shading 단계에서 shadow texture를 sampling해 light visibility를 판단하는 흐름
- shadow map용 `TextureBuffer`와 light-space matrix를 object shader에 전달하는 방식
- character main object와 보조 box들이 shadow를 주고받는지 확인하는 방식

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- raw/origin 모두 sphere main object가 활성화되어 있었지만, character loading code가 주석으로 준비되어 있었습니다.
- 이후 13장 예제에서 character 사용 여지가 있는 경우 character를 우선 사용하기로 한 작업 기준에 따라 `armored-female-future-soldier` asset 로딩을 활성화했습니다.
- 보조 box object는 shadow 확인용 추가 물체로 유지했습니다.
- `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`는 archive 대상에서 제외했습니다.
- Release build shader compile 재현성을 위해 `CubeMappingPS.hlsl` Release shader model을 `5.0`으로 맞추고, 일부 shader의 Release shader model 누락을 보정했습니다.

## Next Check

- Visual Studio에서 Debug x64 build/run 확인
- Visual Studio에서 Release x64 build/run 확인
- character와 보조 box 기준으로 shadow map 적용 여부 확인
