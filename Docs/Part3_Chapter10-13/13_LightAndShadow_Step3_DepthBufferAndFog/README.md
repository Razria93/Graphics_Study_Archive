# 13 Light and Shadow Step3 Depth Buffer and Fog

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step3_DepthBufferAndFog`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step3_DepthBufferAndFog`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step3_DepthBufferAndFog`
- Build/run status: 성공
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 depth buffer를 texture로 해석해 화면 후처리에 사용하고, camera depth 기반 fog를 적용하는 흐름을 확인하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- scene color/depth를 offscreen buffer에 렌더링한 뒤 후처리 단계에서 조합하는 흐름
- depth texture를 sampling해 화면 공간 depth visualization과 fog strength를 조절하는 방식
- `DepthScale`과 `Fog` GUI가 후처리 constant buffer에 반영되는지 확인
- mirror/stencil, skybox, post-process pipeline state가 함께 동작하는지 확인

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- `_Solution` project files, `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`, generated raw folders는 제외했습니다.
- raw와 origin은 같은 프로젝트 구성을 공유하지만 `ExampleApp.cpp`와 일부 graphics helper 구현에 차이가 있습니다.
- primary raw에는 `Fog` slider range가 `0.0` to `1.0`로 조정되어 있어 사용자 작업본 기준으로 유지했습니다.
- Release build shader compile 재현성을 위해 `.clang-format` project reference를 제거하고, Release shader model 누락/`5.1` 설정을 `5.0` 기준으로 보정했습니다.
- 실행에 필요한 HDRI/cubemap/texture assets는 이전 Part3 import의 shared `Assets` 폴더를 재사용합니다.

## Verification

- Debug x64 build/run: 성공
- Release x64 build/run: 성공
- Runtime behavior: 사용자 실행 확인
- `DepthScale`/`Fog` GUI는 후속 문서 정리 단계에서 세부 동작을 다시 확인합니다.
