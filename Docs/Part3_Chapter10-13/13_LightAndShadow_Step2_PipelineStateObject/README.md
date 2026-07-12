# 13 Light and Shadow Step2 PipelineStateObject

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step2_PipelineStateObject`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step2_PipelineStateObject`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step2_PipelineStateObject`
- Build/run status: 미확인
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 이전 mirror/stencil 흐름을 유지하면서 depth/stencil, blend, rasterizer state 같은 pipeline state 설정을 `GraphicsPSO`/`GraphicsCommon` 쪽으로 분리하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- pipeline state object 형태로 render state 설정을 관리하는 방식
- skybox, main object, mirror, reflected object가 서로 다른 state 조합을 사용하는 흐름
- Mirror Step1과 같은 character main object를 사용해 stencil/mirror 동작을 더 잘 확인하는 방식

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- raw primary는 box main object가 활성화되어 있었지만, origin reference에는 character main object가 활성화되어 있었습니다.
- 이후 13장 예제에서 character 사용 여지가 있는 경우 character를 우선 사용하기로 한 작업 기준에 따라 `armored-female-future-soldier` asset 로딩을 활성화했습니다.
- `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`는 archive 대상에서 제외했습니다.
- Release build shader compile 재현성을 위해 `SkyboxPS.hlsl` Release shader model을 `5.0`으로 맞추고, 일부 shader의 Release shader model 누락을 보정했습니다.

## Next Check

- Visual Studio에서 Debug x64 build/run 확인
- Visual Studio에서 Release x64 build/run 확인
- character main object 기준으로 mirror/pipeline state 동작 확인
