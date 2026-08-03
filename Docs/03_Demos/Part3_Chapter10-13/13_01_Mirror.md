# Chapter13 Step1 Mirror Demo

## 목적

Stencil mask와 reflection matrix로 planar mirror를 그린다.

## 책임 범위

- Scene을 stencil에 제한해 반사 geometry를 별도 pass로 렌더링한다.
- 일반 이론은 [Topic](../../01_Topics/DirectX11Pipeline/StencilBufferAndMirrorRendering.md)으로 위임한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)으로 위임한다.

## 결과 미리보기

![Chapter13 Step1 Mirror](../../_assets/captures/part3_chapter13_01_mirror.png)

Mirror 영역에 제한된 reflected scene 결과를 확인한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Scene geometry, mirror plane, stencil state |
| 출력 | Mirror 영역에 제한된 reflected scene |

## 구현 흐름

1. 필요한 scene resource와 pipeline state를 준비한다.
2. Scene을 stencil에 제한해 반사 geometry를 별도 pass로 렌더링한다.
3. 결과를 HDR target과 post-process를 거쳐 표시한다.

## 핵심 구현

- [Stencil mask와 reflection matrix 기반 planar mirror](../../../Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror/ExampleApp.cpp#L164-L181)

## 시각 결과

전체 창 capture에서 UI 기본값과 Mirror 영역에 제한된 reflected scene의 대응을 확인한다.

## 구현 범위와 한계

- Planar mirror만 다루며 recursive reflection은 제외한다.
- 출처 불완전 runtime asset은 직접 공개 링크하지 않는다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter10-13/verification-index.md)

## 관련 코드

- [Example README](../../../Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror/README.md)

## 관련 문서

- [Demo Index](demo-index.md)
- [이전 Demo](12_02_PBRModels.md)
- [다음 Demo](13_02_PipelineStateObject.md)
