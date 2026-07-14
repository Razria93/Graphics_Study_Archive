# 13 Light and Shadow Step4 Shadow Mapping

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step4_ShadowMapping`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step4_ShadowMapping`
- Reference-only snapshot: `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step4_ShadowMapping`
- Build/run status: 성공
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 light 시점에서 만든 depth map을 shadow map으로 사용하고, main pass의 pixel shader에서 현재 픽셀의 light-space depth와 shadow map depth를 비교해 직접광을 차단하는 기본 shadow mapping 흐름을 확인하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- light별 shadow depth buffer와 shadow viewport 생성
- `LIGHT_SHADOW` flag가 있는 light에 대해 shadow pass 수행
- light view/projection matrix를 `GlobalConstants`에 반영
- pixel shader에서 world position을 light clip/NDC space로 투영
- shadow map depth와 현재 light-space depth 비교
- bias를 이용한 shadow acne 완화

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- origin과 `_2`는 shadow lookup 핵심부가 TODO/comment 형태에 가까워 reference-only로 유지합니다.
- `_Solution` project files, `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`, generated raw folders는 제외했습니다.
- Release build shader compile 재현성을 위해 `.clang-format` project reference를 제거하고, Release shader model 누락/`5.1` 설정을 `5.0` 기준으로 보정했습니다.
- 실행에 필요한 HDRI/cubemap/texture assets는 이전 Part3 import의 shared `Assets` 폴더를 재사용합니다.

## Verification

- Debug x64 build/run: 성공
- Release x64 build/run: 성공
- Runtime behavior: 사용자 실행 확인
- shadow map, Light position/radius, wireframe, post effect GUI 세부 동작은 후속 문서 정리 단계에서 다시 확인합니다.
