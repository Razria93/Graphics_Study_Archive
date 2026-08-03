# Chapter10 Step4 Fireball Demo

## 목적

Geometry shader billboard 위에서 time 기반 procedural fireball을 출력하고 primitive마다 다른 animation phase를 부여한다.

## 책임 범위

- Billboard geometry와 procedural pixel shading의 연결을 설명한다.
- Runtime input 일반론은 [Shadertoy Runtime Inputs](../../01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md)로 위임한다.
- 검증 사실은 [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)으로 위임한다.

## 결과 미리보기

![Chapter10 Step4 Fireball](../../_assets/captures/part3_chapter10_04_fireball.png)

세 billboard가 구형 fire surface처럼 보이며 서로 다른 procedural phase를 가진다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Billboard position, time, primitive ID |
| 출력 | Animated procedural fireball color |

## 구현 흐름

1. CPU가 frame time을 누적한다.
2. Geometry shader가 point를 camera-facing quad로 확장한다.
3. Pixel shader가 ray-marched fireball과 primitive별 phase offset을 계산한다.

## 핵심 구현

- [Frame time 누적](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/ExampleApp.cpp#L276-L284)
- [Billboard quad와 primitive ID 전달](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/BillboardPointsGeometryShader.hlsl#L30-L92)
- [Procedural fireball과 phase offset](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/FireballPixelShader.hlsl#L29-L110)

## 시각 결과

정지 화면은 형태와 instance 차이를 증명한다. 연속 motion은 구현 이해에 보조적이므로 video는 local evidence 후보로만 둔다.

## 구현 범위와 한계

- 실제 sphere mesh가 아니라 quad 내부의 shader illusion이다.
- Shader 원형과 asset 출처는 Publication에서 기록하고 raw 원문을 복제하지 않는다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter10-13/verification-index.md)

## 관련 코드

- [Example README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/README.md)
- [Fireball instance 구성](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/ExampleApp.cpp#L26-L52)

## 관련 문서

- [Geometry Shader And Billboards](../../01_Topics/ModelingAndGeometry/GeometryShaderAndBillboards.md)
- [Shadertoy Runtime Inputs](../../01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md)
- [Demo Index](demo-index.md)
- [이전 Demo](10_03_NormalLines.md)
- [다음 Demo](10_05_Tessellation.md)
