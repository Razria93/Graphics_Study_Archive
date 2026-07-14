# 13 Light and Shadow Step7 Halo

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step7_Halo`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step7_Halo`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step7_Halo`
- Reference-only snapshot: `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step7_Halo`
- Build/run status: 성공
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 depth buffer를 이용해 screen-space texcoord에서 view-space position을 복원하고, post effect 단계에서 light volume 기반 halo emission을 더하는 흐름을 확인하는 단계입니다.

중점 확인 지점은 다음과 같습니다.

- `depthOnlyTex`와 `invProj`를 이용한 view-space position reconstruction
- view ray와 light sphere의 ray-sphere intersection
- 교차 구간 `t1`-`t2`를 이용한 halo emission 계산
- occluder가 halo 앞에 있을 때 depth 기반으로 halo를 가리는 처리
- `Halo Radius`, `Halo Strength`, post effect mode/depth scale GUI 동작

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- raw/origin/`_2` 비교 결과 `PostEffectsPS.hlsl`만 primary raw가 다릅니다. primary raw의 halo 구현과 사용자가 남긴 메모를 유지했습니다.
- `_Solution` project files, `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`, generated raw folders는 제외했습니다.
- Release build shader compile 재현성을 위해 `.clang-format` project reference를 제거하고, Release shader model 누락/`5.1` 설정을 `5.0` 기준으로 보정했습니다.
- 실행에 필요한 HDRI/cubemap/texture assets는 이전 Part3 import의 shared `Assets` 폴더를 재사용합니다.

## Verification

- Debug x64 build/run: 성공
- Release x64 build/run: 성공
- Runtime behavior: 사용자 실행 확인
- Halo visibility, depth occlusion, light movement, `Halo Radius`, `Halo Strength`, post effect GUI 동작은 이후 문서 정리 단계에서 다시 세부 확인합니다.
