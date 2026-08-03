# Chapter13 Step8 UnrealSphereLight

Sphere 위 representative point로 area-light response를 근사한다.

## 구현 요약

- Point light 위치를 sphere radius와 reflection 방향에 따라 보정한다.
- Chapter13 공통 scene, HDR post-process와 UI 구조를 유지한다.
- 일반 이론은 Topic으로, build/run/capture 사실은 Verification으로 위임한다.

## 핵심 코드

- [Sphere representative point 기반 area-light response](./BasicPS.hlsl#L293-L333)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Capture | 완료 | 전체 application window |

## Capture/Result

![Chapter13 Step8 UnrealSphereLight](../../Docs/_assets/captures/part3_chapter13_08_unreal_sphere_light.png)

원본 runtime asset은 직접 연결하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part3_Chapter10-13/13_08_UnrealSphereLight.md)
- [Topic](../../Docs/01_Topics/LightingAndShading/AreaLightApproximation.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
