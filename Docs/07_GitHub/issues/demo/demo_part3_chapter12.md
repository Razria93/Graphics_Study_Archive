# Part3 Chapter12 Physically Based Rendering Demo

## 요약

Metallic-roughness sphere에서 시작해 imported model의 submesh와 material texture binding으로 확장하는 PBR 흐름이다.

## 결과

### UnrealPBR material sphere

Albedo, normal, AO, metallic과 roughness map을 direct GGX BRDF와 IBL에 결합한다.

![UnrealPBR](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter12_01_unreal_pbr.png?raw=true)

### Imported PBR model

Assimp가 읽은 model의 submesh와 material map을 mesh별 resource binding으로 연결한다.

![PBR Models](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Docs/_assets/captures/part3_chapter12_02_pbr_models.png?raw=true)

## 핵심 구현

### Metallic-roughness BRDF와 IBL

Metallic 값으로 dielectric F0와 albedo를 보간하고 roughness를 GGX distribution과 prefiltered environment sampling에 반영한다.

- [Normal·IBL·GGX 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/BasicPS.hlsl#L50-L181)

### Imported material resource binding

Assimp material에서 texture를 추출하고 각 mesh group의 shader resource로 연결한다.

- [Assimp material extraction](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step2_PBRModels/ModelLoader.cpp#L134-L208)
- [Mesh resource binding](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step2_PBRModels/BasicMeshGroup.cpp#L51-L106)

## 처리 흐름

1. PBR material map과 environment resource를 준비한다.
2. Tangent-space normal을 world normal로 변환한다.
3. Direct GGX BRDF와 diffuse·specular IBL을 결합한다.
4. Imported model의 submesh와 material texture를 순회한다.
5. Mesh별 PBR resource를 binding해 같은 shading model로 표시한다.

## 구현 범위와 한계

- Clear coat, anisotropy와 layered material은 포함하지 않는다.
- FBX·PBR texture·HDRI 원본은 직접 링크하지 않고 rendered evidence만 사용한다.
- Step2는 Assimp material 구조를 현재 예제의 texture slot에 맞춰 해석한다.

## 검증

- Step1–2 Debug/Release x64 Clean/Rebuild와 run 성공
- PBR map 5종과 imported model material binding 확인
- 전체 창 PNG 2장 full decode·metadata·공개 안전성과 validator 통과

## 더 자세히 보기

- [Part3 Chapter10-13 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- [Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Step1 UnrealPBR 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md)
- [Step2 PBRModels 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/12_02_PBRModels.md)
- [PBR Material Model](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/01_Topics/PBRAndIBL/PBRMaterialModel.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
