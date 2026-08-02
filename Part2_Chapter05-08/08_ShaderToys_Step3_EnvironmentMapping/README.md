# Chapter08 Step3 EnvironmentMapping

## 목적

Step2의 cubemap을 배경에만 사용하지 않고 surface reflection direction으로 sampling한다.

## 구현 요약

- NightPath cubemap과 Zelda FBX scene을 로드한다.
- Pixel shader가 `reflect(-V, N)`으로 reflection direction을 계산한다.
- Reflection direction으로 `TextureCube`를 sampling하고 optional diffuse texture와 합성한다.
- 실제 shader에 연결되지 않던 `Use Reflection` checkbox를 제거해 UI와 결과 책임을 일치시킨다.

일반 이론은 [Cubemap And Environment Mapping](../../Docs/01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)으로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild와 runtime DLL 확인 |
| Release x64 build/run | 성공 | project 폴더 CWD |
| Resize | 성공 | minimize/restore 포함 |
| Capture | 확보 | NightPath reflection과 Zelda scene 확인 |

## Capture/Result

![Chapter08 Step3 EnvironmentMapping](../../Docs/_assets/captures/part2_chapter08_03_environment_mapping.png)

## 핵심 코드

- [NightPath cubemap과 scene 초기화](ExampleApp.cpp#L20-L105)
- [Reflection direction sampling](BasicPixelShader.hlsl#L55-L73)
- [Cubemap과 mesh resource binding](ExampleApp.cpp#L271-L311)

## 범위와 한계

- 단일 reflection sample이며 Fresnel, roughness LOD와 refraction은 아직 적용하지 않는다.
- NightPath는 Humus/Emil Persson의 CC BY 3.0 attribution을 유지한다.
- Zelda bundle의 공개 재배포 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 둔다.
- Camera 회전 video는 효과 설명에 유효하지만 이번 단계에서는 local 후보 없이 screenshot으로 마감한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/08_03_EnvironmentMapping.md)
- [Cubemap And Environment Mapping](../../Docs/01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)
- [Verification](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [이전 단계: Chapter08 Step2 Cubemapping](../08_ShaderToys_Step2_Cubemapping/README.md)
- [다음 단계: Chapter08 Step4 ImageBasedLighting](../08_ShaderToys_Step4_ImageBasedLighting/README.md)
