# Normal Mapping And Tangent Space

## 목적

Tangent-space normal texture를 surface basis로 world space에 변환해 geometry를 늘리지 않고 미세한 조명 변화를 만드는 원리를 설명한다.

## 책임 범위

이 문서는 tangent·bitangent·normal basis, normal decode와 space 변환을 다룬다. 개별 texture와 shader binding은 Example README, 시각 결과는 상세 Demo, 실행 사실은 Verification으로 위임한다.

## 핵심 개념

### Normal decode

Normal texture의 RGB는 일반적으로 `[0,1]` 범위이므로 먼저 `[-1,1]` 범위로 변환한다. 이 값은 tangent space 기준이므로 vertex tangent, bitangent와 normal로 만든 TBN basis를 사용해 shading space로 옮긴다.

```cpp
// Pseudo C++: tangent-space normal transform
float3 tangentNormal = normalize(encodedNormal * 2.0 - 1.0);
float3x3 tbn = float3x3(tangent, bitangent, normal);
float3 worldNormal = normalize(mul(tangentNormal, tbn));
```

### Basis 일관성

Texture 제작 도구와 renderer가 normal Y 방향, tangent handedness와 matrix convention을 다르게 사용하면 홈과 돌출이 반대로 보인다. `reverseNormalMapY` 같은 보정은 해당 asset convention을 명시적으로 맞추는 장치다.

## 한계

- Normal mapping은 surface silhouette을 바꾸지 않는다.
- Tangent가 불연속인 UV seam에서는 basis split이 필요하다.
- Non-uniform scale에서는 normal transform을 별도로 처리해야 한다.

## 관련 문서

- [Texture Sampling](TextureSampling.md)
- [Height Mapping](HeightMapping.md)
- [Example README](../../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/11_02_NormalMapping.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
