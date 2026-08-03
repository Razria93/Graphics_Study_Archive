# Chapter11 Step2 NormalMapping Demo

## 목적

Tangent-space normal texture가 낮은 polygon 수를 유지하면서 표면의 조명 방향 변화를 만드는 경로를 보여준다.

## 책임 범위

- TBN basis와 normal decode의 실제 구현을 설명한다.
- 일반 이론은 [Normal Mapping And Tangent Space](../../01_Topics/TexturingAndMapping/NormalMappingAndTangentSpace.md)로 위임한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)으로 위임한다.

## 결과 미리보기

![Chapter11 Step2 NormalMapping](../../_assets/captures/part3_chapter11_02_normal_mapping.png)

석재 평면의 silhouette은 유지되지만 각 돌의 요철 방향에 따라 조명 반응이 달라진다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Vertex normal·tangent, UV, tangent-space normal texture |
| 출력 | World-space shading normal과 조명 결과 |

## 구현 흐름

1. Vertex shader가 tangent·bitangent·normal basis를 만든다.
2. Pixel shader가 normal texture를 `[0,1]`에서 `[-1,1]`로 decode한다.
3. TBN으로 tangent normal을 world space에 변환한다.
4. 변환한 normal을 lighting에 사용한다.

## 핵심 구현

```cpp
// Pseudo C++: tangent normal to world normal
float3 tangentNormal = Decode(normalTexture.Sample(sampler, uv));
float3x3 tbn = BuildTBN(tangent, bitangent, normal);
float3 worldNormal = normalize(mul(tangentNormal, tbn));
```

- [TBN 전달](../../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/BasicVertexShader.hlsl#L30-L56)
- [Normal texture decode와 변환](../../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/BasicPixelShader.hlsl#L61-L82)

## 시각 결과

Stone pattern의 작은 경계와 홈이 실제 geometry 변화 없이 조명으로 드러난다. 검은 배경은 material plane 외부이며 clipping 오류가 아니다.

## 구현 범위와 한계

- Surface silhouette은 변하지 않는다.
- Texture의 실제 재배포는 rendered evidence와 분리한다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter10-13/verification-index.md)

## 관련 코드

- [Example README](../../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/README.md)
- [Material texture 구성](../../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/ExampleApp.cpp#L61-L103)

## 관련 문서

- [Normal Mapping And Tangent Space](../../01_Topics/TexturingAndMapping/NormalMappingAndTangentSpace.md)
- [Demo Index](demo-index.md)
- [이전 Demo](11_01_Mipmaps.md)
- [다음 Demo](11_03_HeightMapping.md)
