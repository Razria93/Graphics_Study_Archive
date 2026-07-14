# 13 Light and Shadow Step6 Soft Shadow PCSS

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step6_SoftShadowPCSS`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step6_SoftShadowPCSS`
- Reference-only snapshot: `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step6_SoftShadowPCSS`
- Build/run status: 성공
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 Step5의 고정 반경 PCF를 확장해 PCSS(Percentage-Closer Soft Shadows)를 확인하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- shadow map에서 receiver 주변 blocker를 검색하는 `FindBlocker`
- blocker 평균 depth와 receiver depth를 이용한 penumbra size 계산
- light radius와 frustum width를 이용한 filter radius 산출
- 계산된 filter radius를 PCF filtering에 전달해 거리 기반 soft shadow edge 구성
- PCF와 달리 occluder/receiver 거리 차이에 따라 그림자 경계가 달라지는지 확인

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- origin과 `_2`는 PCSS 구현 흐름은 동일하지만, primary raw에는 blocker search와 penumbra/filter radius 관련 사용자 메모가 추가되어 있습니다.
- `_Solution` project files, `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`, generated raw folders는 제외했습니다.
- Release build shader compile 재현성을 위해 `.clang-format` project reference를 제거하고, Release shader model 누락/`5.1` 설정을 `5.0` 기준으로 보정했습니다.
- 실행에 필요한 HDRI/cubemap/texture assets는 이전 Part3 import의 shared `Assets` 폴더를 재사용합니다.

## Verification

- Debug x64 build/run: 성공
- Release x64 build/run: 성공
- Runtime behavior: 사용자 실행 확인
- PCSS soft shadow, light radius, light position, wireframe, post effect GUI 세부 동작은 후속 문서 정리 단계에서 다시 확인합니다.
