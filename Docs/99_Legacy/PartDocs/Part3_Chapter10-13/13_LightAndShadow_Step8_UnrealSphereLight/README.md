# 13 Light and Shadow Step8 Unreal Sphere Light

## 작업 범위

- Archive example: `Part3_Chapter10-13/13_LightAndShadow_Step8_UnrealSphereLight`
- Primary raw source: `C:\ComputerGraphics\Part3_Chapter10_13\13_LightAndShadow_Step8_UnrealSphereLight`
- Origin reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\13_LightAndShadow_Step8_UnrealSphereLight`
- Reference-only snapshot: `C:\ComputerGraphics\Part3_Chapter10_13_2\13_LightAndShadow_Step8_UnrealSphereLight`
- Build/run status: 성공
- Capture status: 보류
- Public readiness: 검토 필요

## 예제 목적

이 예제는 point light를 점 광원으로만 보지 않고, 일정 반경을 가진 sphere light처럼 근사해 specular highlight와 lighting direction을 계산하는 흐름을 확인하는 단계입니다.

중점 확인 지점은 다음과 같습니다.

- pixel position에서 light center까지의 벡터 `L` 계산
- view/reflection 방향을 이용한 representative point 선택
- light radius에 따라 representative point를 sphere surface 안쪽으로 clamp하는 처리
- representative point 기준 light vector, radiance, shadow lookup 연결
- `Radius`, `Metallic`, `Roughness`, light position GUI가 highlight와 lighting에 미치는 영향

## Import Notes

- primary raw folder를 기준으로 import했습니다.
- raw/origin/`_2` 비교 결과 `BasicPS.hlsl`만 primary raw가 다릅니다. primary raw의 sphere light representative point 구현과 사용자가 남긴 메모를 유지했습니다.
- `_Solution` project files, `.vs/`, `x64/`, `.vcxproj.user`, `imgui.ini`, `.clang-format`, generated raw folders는 제외했습니다.
- Release build shader compile 재현성을 위해 `.clang-format` project reference를 제거하고, Release shader model 누락/`5.1` 설정을 `5.0` 기준으로 보정했습니다.
- 실행에 필요한 HDRI/cubemap/texture assets는 이전 Part3 import의 shared `Assets` 폴더를 재사용합니다.

## Verification

- Debug x64 build/run: 성공
- Release x64 build/run: 성공
- Runtime behavior: 사용자 실행 확인
- Sphere light radius, representative highlight, light movement, material roughness/metallic GUI 동작은 이후 문서 정리 단계에서 다시 세부 확인합니다.
