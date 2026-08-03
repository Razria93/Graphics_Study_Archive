# Chapter08 Step7 Shadertoy

## 예제 목적

Step6의 scene 기반 post-processing에서 벗어나 full-screen quad의 pixel shader만으로 시간에 따라 움직이는 star surface와 corona를 만든다. Shadertoy 계열 shader가 사용하는 time, resolution과 texture channel 입력을 DirectX11 constant buffer와 shader resource로 연결한다.

## 구현 요약

- `shadertoytexture0.jpg`를 texture channel 0에 연결한다.
- 매 frame 누적한 시간을 `iTime`으로 전달한다.
- 현재 render target 크기를 `iResolution`으로 전달해 aspect ratio를 계산한다.
- 3D noise를 여러 주파수로 합성해 star surface와 corona를 만든다.
- Window resize 후 full-screen filter와 constant buffer를 현재 크기로 다시 만든다.

## 핵심 코드

- [시간 입력 갱신](ExampleApp.cpp#L101-L109)
- [Texture channel과 Star filter 구성](ExampleApp.cpp#L152-L172)
- [Resize 후 filter 재생성](ExampleApp.cpp#L175-L178)
- [Resolution constant 구성](ImageFilter.h#L109-L116)
- [Noise 기반 star와 corona 합성](StarPixelShader.hlsl#L58-L127)

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Release x64 build/run | 성공 | Clean/Rebuild, project 폴더 CWD |
| Resize·minimize/restore | 성공 | filter와 resolution 입력 재생성 |
| Capture | 확보 | 1282×992 전체 창 screenshot |
| Video | 확보 | 9.83초, 30 FPS selected local video |

## Capture/Result

![Chapter08 Step7 Shadertoy](../../Docs/_assets/captures/part2_chapter08_07_shadertoy.png)

시간에 따라 star 표면의 noise와 바깥 corona가 연속적으로 변한다. Video는 이 시간 변화를 검증하는 local evidence로 유지한다.

## 구현 범위와 한계

- 활성 결과는 `StarPixelShader.hlsl`과 `shadertoytexture0.jpg`만 사용한다.
- `SeascapePixelShader.hlsl`은 별도 연구 자료로 보존하지만 build와 runtime에서 제외한다.
- `EnergeticFlybyPixelShader.hlsl`도 활성 pipeline에 연결하지 않는다.
- Star shader 원문 링크와 작성자 표기는 남아 있지만 명시적 license와 texture 출처 근거가 충분하지 않아 Publication은 `검토 필요`다.
- Shadertoy의 전체 uniform 계약이나 web runtime을 구현하지 않고 현재 예제에 필요한 최소 입력만 연결한다.

## 관련 문서

- [상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md)
- [Shadertoy Runtime Inputs](../../Docs/01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md)
- [Verification](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [이전 단계: Chapter08 Step6 BloomEffect](../08_ShaderToys_Step6_BloomEffect/README.md)
