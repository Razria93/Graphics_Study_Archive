# Chapter08 Step1 RimLighting Demo

## 목적

Dragon surface의 normal과 eye direction으로 silhouette rim을 만들고 power·smoothstep shaping 차이를 설명한다.

## 책임 범위

- 실제 pixel shader의 rim mask와 가산 합성을 설명한다.
- 일반 이론은 [Rim Lighting](../../01_Topics/LightingAndShading/RimLighting.md)으로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

![Chapter08 Step1 RimLighting](../../_assets/captures/part2_chapter08_01_rim_lighting.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | World normal, eye direction, rim color·power·strength |
| 중간값 | `1 - saturate(dot(N, V))` rim base |
| 출력 | Base lighting에 가산한 stylized silhouette rim |

## 구현 흐름

1. Vertex shader가 world position과 inverse-transpose normal을 전달한다.
2. Pixel shader가 surface에서 eye로 향하는 vector를 정규화한다.
3. Normal·view dot product를 뒤집어 grazing-angle rim base를 만든다.
4. Power 또는 smoothstep으로 mask를 shaping한다.
5. Rim color와 strength를 곱해 base lighting에 더한다.

## 핵심 구현

### Rim mask

```cpp
// Pseudo C++: silhouette에서 강해지는 rim mask
ComputeRim(normal, toEye)
{
    base = 1.0 - Saturate(Dot(normal, toEye));
    mask = useSmoothstep ? Smoothstep(0.0, 1.0, base)
                         : Pow(Max(base, Epsilon), power);
    return mask * rimColor * rimStrength;
}
```

- [Rim base, shaping과 가산 합성](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/BasicPixelShader.hlsl#L59-L68)
- [Rim parameter UI](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/ExampleApp.cpp#L289-L299)

## 시각 결과

검은 Dragon body의 외곽과 camera에 비스듬한 surface에 파란 rim이 집중된다. 흰 specular highlight와 rim color가 구분되어 angle 기반 silhouette 강조를 확인할 수 있다.

## 구현 범위와 한계

- Stylized rim이며 물리 기반 Fresnel reflection은 아니다.
- Default power 2.5와 strength 1.25는 효과 판독을 위한 예제 값이다.
- Stanford Dragon 원본은 비공개로 유지하고 직접 실행한 rendered evidence만 공개한다.
- Video는 정적 결과와 UI parameter를 한 frame에서 확인할 수 있어 제외한다.

## 검증

- Debug/Release x64 build/run 성공, 2026-08-03 현재 확인
- Assimp runtime dependency를 Clean/Rebuild로 복원한 뒤 실행 확인
- Power와 smoothstep branch가 모두 rim contribution을 유지하는지 확인
- Resize·minimize/restore resource 재생성 경로 확인
- 1282×992 전체 창 screenshot과 공개 title 확인

## 관련 코드

- [Dragon model 입력](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/ExampleApp.cpp#L28-L43)
- [Rim lighting shader](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/BasicPixelShader.hlsl#L47-L70)
- [Resize resource lifetime](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/AppBase.cpp#L525-L552)

## 관련 문서

- [Chapter08 Step1 RimLighting Example](../../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/README.md)
- [이전 단계: Chapter07 Step9 ModelFiles Demo](07_09_ModelFiles.md)
- [다음 단계: Chapter08 Step2 Cubemapping](08_02_Cubemapping.md)
- [Rim Lighting](../../01_Topics/LightingAndShading/RimLighting.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
