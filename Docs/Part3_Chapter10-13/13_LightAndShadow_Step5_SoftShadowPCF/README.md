# 13 Light and Shadow Step5 Soft Shadow PCF

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step5_SoftShadowPCF`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step5_SoftShadowPCF`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step5_SoftShadowPCF`
- Reference-only snapshot: `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step5_SoftShadowPCF`
- Build/run status: 미확인
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 Step4의 hard shadow mapping을 확장해 PCF(Percentage Closer Filtering) 기반 soft shadow를 확인하는 단계입니다.

핵심 확인 지점은 다음과 같습니다.

- `SamplerComparisonState`와 `SampleCmpLevelZero`를 사용한 hardware depth compare
- shadow map 주변 sample을 여러 번 비교한 뒤 lit 비율 계산
- 3x3 offsets, poisson disk, 64 disk samples 같은 sample pattern 후보
- `shadowFactor = percentLit / sampleCount` 방식의 soft edge 구성
- light0 shadow 활성화와 light별 shadow pass 유지

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- origin과 `_2`는 기본 shadow compare 흐름에 가까우며, primary raw가 PCF sample pattern과 64-sample 구현을 포함합니다.
- `_Solution` project files, `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`, generated raw folders는 제외했습니다.
- Release build shader compile 재현성을 위해 `.clang-format` project reference를 제거하고, Release shader model 누락/`5.1` 설정을 `5.0` 기준으로 보정했습니다.
- 실행에 필요한 HDRI/cubemap/texture assets는 이전 Part3 import의 shared `Assets` 폴더를 재사용합니다.

## Next Check

- Visual Studio에서 Debug x64 build/run 확인
- Visual Studio에서 Release x64 build/run 확인
- PCF soft shadow가 hard shadow보다 부드러운 edge를 만드는지 확인
- light position/radius, wireframe, post effect GUI 동작 확인
