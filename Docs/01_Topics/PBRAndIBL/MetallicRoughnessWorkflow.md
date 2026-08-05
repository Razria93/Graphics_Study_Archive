# Metallic Roughness Workflow

## 목적

Base color, metallic, roughness, normal과 AO texture가 PBR material에서 담당하는 역할을 정의한다.

## 책임 범위

- 실제 파일명과 binding은 Example README로 위임한다.
- Build/run 사실은 `Docs/02_Verification`으로 위임한다.
- 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Base color와 metallic

Base color는 dielectric의 diffuse color 또는 metal의 specular color로 사용한다. Metallic 값은 diffuse energy를 줄이고 F0를 base color 쪽으로 이동시킨다.

### Roughness와 filtered environment

Roughness는 microfacet 분포와 reflection blur를 제어한다. Prefiltered environment의 mip level은 roughness에 따라 선택한다.

### Normal과 AO

Normal map은 tangent-space shading normal을 바꾸고 AO는 간접광을 감쇠한다. Height map은 별도 geometry displacement 경로이므로 material map과 구분한다.

## 한계

- Channel packing과 authoring tool별 convention은 asset 계약에 따라 달라진다.
- 출처 불완전 원본 asset은 직접 공개 링크하지 않고 rendered evidence만 사용한다.

## 관련 문서

- [Chapter12 Step2 Example README](../../../Part3_Chapter10-13/12_PBR_Step2_PBRModels/README.md)
- [PBR Material Model](PBRMaterialModel.md)
- [Normal Mapping And Tangent Space](../TexturingAndMapping/NormalMappingAndTangentSpace.md)
- [Docs/03_Demos Step2](../../03_Demos/Part3_Chapter10-13/12_02_PBRModels.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
