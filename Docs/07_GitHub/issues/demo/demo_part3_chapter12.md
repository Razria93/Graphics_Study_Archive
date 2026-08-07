# Part3 Chapter12 Physically Based Rendering Demo

## 요약

Metallic-roughness sphere에서 시작해 imported model의 submesh와 material texture binding으로 확장하는 PBR 흐름이다.

## 핵심 목표

- Metallic과 roughness가 GGX BRDF 및 environment sampling에 미치는 영향을 확인한다.
- PBR map Off/On 상태에서 height scale 변화가 만드는 surface 차이를 비교한다.
- Imported model의 submesh별 material texture binding을 같은 shading model에 연결한다.

## Demo Assets

| Type | Asset | Purpose |
| --- | --- | --- |
| Input screenshot | UnrealPBR Off, Imported PBR Model Off | PBR option을 끈 기준 장면을 제공한다. |
| Result screenshot | UnrealPBR On, Imported PBR Model On | PBR map과 imported material 적용 결과를 확인한다. |
| Result image | 없음 | 별도 합성 result image를 사용하지 않는다. |
| Video | 없음 | Off/On 정적 비교로 PBR 차이를 확인한다. |

## 시각 정보

### UnrealPBR Off

PBR map을 끈 기준 장면이다.

![UnrealPBR Off](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter12_01_pbr_off.png?raw=true)

### UnrealPBR On + Height 0.015

PBR map과 height scale 0.015를 적용한 장면이다.

![UnrealPBR On](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter12_01_pbr_on_height_0_015.png?raw=true)

### Imported PBR Model Off

Imported model에서 PBR option을 끈 기준 장면이다.

![PBR Models Off](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter12_02_pbr_models_off.png?raw=true)

### Imported PBR Model On

Imported model에서 PBR option을 켠 장면이다.

![PBR Models On](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter12_02_pbr_models_on.png?raw=true)

## 구현 하이라이트

### Metallic-roughness BRDF와 IBL

Metallic 값으로 dielectric F0와 albedo를 보간한다.

Roughness는 GGX distribution과 prefiltered environment sampling에 반영한다.

- [Normal·IBL·GGX 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/BasicPS.hlsl#L50-L181)

### Imported material resource binding

Assimp material에서 texture를 추출하고 각 mesh group의 shader resource로 연결한다.

- [Assimp material extraction](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step2_PBRModels/ModelLoader.cpp#L134-L208)
- [Mesh resource binding](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step2_PBRModels/BasicMeshGroup.cpp#L51-L106)

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void ShadePbrSurfacePseudo(const Material& material)
{
	Normal worldNormal = TransformTangentNormal(material.normalMap);
	if (!worldNormal.IsValid()) return WriteFallbackColor();

	Color direct = EvaluateGgxBrdf(material, worldNormal);
	Color ibl = SampleDiffuseAndSpecularIbl(material, worldNormal);
	return WriteColor(direct + ibl);
}
```

원본 코드: [Step1 normal, IBL, GGX 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/BasicPS.hlsl#L50-L181)

## 검증 상태

- Step1–2 Debug/Release x64 Clean/Rebuild와 run 성공을 확인한다.
- PBR map Off/On과 imported model PBR option Off/On 비교를 확인한다.
- 전체 창 PNG 4장의 full decode·metadata·공개 안전성과 validator 통과를 확인한다.

## 구현 범위와 한계

- Clear coat, anisotropy와 layered material은 포함하지 않는다.
- FBX·PBR texture·HDRI 원본은 직접 링크하지 않고 rendered evidence만 사용한다.
- Step2는 Assimp material 구조를 현재 예제의 texture slot에 맞춰 해석한다.

## 관련 문서

- [Part3 Chapter10-13 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- [Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Step1 UnrealPBR 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md)
- [Step2 PBRModels 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/12_02_PBRModels.md)
- [PBR Material Model](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/01_Topics/PBRAndIBL/PBRMaterialModel.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
