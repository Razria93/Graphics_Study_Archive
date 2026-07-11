# 11_TexturingTechniques_Step2_NormalMapping

## Chapter Focus

이 예제는 normal texture를 사용해 pixel shader 단계에서 표면 법선을 바꾸는 흐름을 확인하는 단계입니다.

핵심은 `useNormalMap` 옵션이 켜졌을 때 `g_normalTexture`에서 읽은 RGB 값을 `[-1, 1]` 범위의 tangent-space normal로 변환하고, TBN 기준을 통해 world-space normal로 바꿔 조명 계산에 사용하는 것입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step2_NormalMapping`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step2_NormalMapping`
- Intent reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\11_TexturingTechniques_Step2_NormalMapping`
- 이번 예제는 primary raw에 실제 normal map sampling과 TBN 변환 구현이 들어 있어 primary raw를 import 기준으로 사용했습니다.
- `OriginalExamples`는 normal map sampling 일부가 비활성화된 중간 상태로 보여, 이번 archive 기준에서는 참고용으로만 둡니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

선별 포함한 asset:

- `Assets/Textures/PBR/cgaxis_grey_porous_rock_40_56_4K/*_diffuse.jpg`
- `Assets/Textures/PBR/cgaxis_grey_porous_rock_40_56_4K/*_normal.jpg`
- `Assets/Textures/PBR/cgaxis_grey_porous_rock_40_56_4K/*_height.jpg`
- `Assets/Textures/PBR/cgaxis_grey_porous_rock_40_56_4K/*_ao.jpg`
- `Assets/Textures/PBR/Bricks075A_1K-PNG/*_Color.png`
- `Assets/Textures/PBR/Bricks075A_1K-PNG/*_NormalDX.png`
- `Assets/Textures/PBR/Bricks075A_1K-PNG/*_Displacement.png`
- `Assets/Textures/PBR/Bricks075A_1K-PNG/*_AmbientOcclusion.png`

raw asset archive, generated output, capture image는 포함하지 않았습니다.

## Verification

- Static verification: 통과
- Debug x64 run: 미확인
- Release x64 run: 미확인
