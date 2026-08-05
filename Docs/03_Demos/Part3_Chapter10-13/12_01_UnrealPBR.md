# Chapter12 Step1 UnrealPBR Demo

## 목적

Metallic-roughness texture와 environment lighting을 결합한 PBR sphere를 보여준다.

## 책임 범위

- PBR resource binding과 shader flow를 설명한다.
- 일반 이론은 [PBR Material Model](../../01_Topics/PBRAndIBL/PBRMaterialModel.md)로 위임한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)으로 위임한다.

## 결과 미리보기

### PBR map Off

![Chapter12 Step1 UnrealPBR Off](../../_assets/captures/part3_chapter12_01_pbr_off.png)

### PBR map On + Height Scale 0.015

![Chapter12 Step1 UnrealPBR On](../../_assets/captures/part3_chapter12_01_pbr_on_height_0_015.png)

동일한 camera와 UI 기준에서 PBR map Off 대비 On 상태의 micro surface response와 IBL highlight 변화를 확인한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | PBR texture 5종, irradiance·specular cube, BRDF LUT, point light |
| 출력 | Direct BRDF와 IBL을 결합한 HDR material result |

## 구현 흐름

1. Sphere geometry와 PBR texture를 준비한다.
2. Environment cube와 BRDF LUT를 shader resource로 연결한다.
3. Tangent-space normal을 world normal로 변환한다.
4. Direct GGX BRDF와 diffuse·specular IBL을 계산한다.
5. HDR result를 post-process해 화면에 표시한다.

## 핵심 구현

```cpp
// Pseudo C++: metallic-roughness PBR
float3 F0 = Lerp(DielectricF0, albedo, metallic);
float3 direct = EvaluateGGX(F0, roughness, normal, light, view);
float3 ambient = EvaluateIBL(F0, albedo, metallic, roughness, normal, view);
return direct + ambient;
```

- [PBR texture와 environment 구성](../../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/ExampleApp.cpp#L29-L72)
- [Normal·IBL·GGX 계산](../../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/BasicPS.hlsl#L50-L181)

## 시각 결과

표면의 거칠기와 금속 영역에 따라 reflection의 선명도와 base color 기여가 달라진다. Normal map의 미세 굴곡은 environment highlight의 방향 변화로 드러난다.

## 구현 범위와 한계

- Clear coat, anisotropy와 layered material은 제외한다.
- 원본 PBR texture와 HDRI는 직접 공개 링크하지 않는다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter10-13/verification-index.md)

## 관련 코드

- [Example README](../../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/README.md)
- [Material UI](../../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/ExampleApp.cpp#L367-L405)

## 관련 문서

- [Metallic Roughness Workflow](../../01_Topics/PBRAndIBL/MetallicRoughnessWorkflow.md)
- [Demo Index](demo-index.md)
- [이전 Demo](11_05_HDRPipeline.md)
- [다음 Demo](12_02_PBRModels.md)
