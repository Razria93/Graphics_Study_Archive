# Part3 Chapter13 Light And Shadow Demo

## 요약

Stencil mirror와 pipeline state 정리에서 시작해 shadow prototype, depth fog, hard shadow, PCF, PCSS, halo와 sphere light로 확장되는 아홉 단계다.

## 결과

### Planar mirror

Stencil mask로 mirror 영역을 제한하고 reflection transform을 적용한 scene을 합성한다.

![Planar mirror](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter13_01_mirror_reflection.png?raw=true)

### Hard Shadow → PCF → PCSS

왼쪽에서 오른쪽으로 읽으면 단일 depth comparison의 hard edge, 고정 kernel PCF의 균일한 blur와 blocker 거리에 따라 penumbra 폭이 달라지는 PCSS를 비교할 수 있다.

![Shadow comparison](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter13_04_06_shadow_filtering_storyboard.png?raw=true)

### Sphere light radius

Radius 0.0, 0.2와 0.5를 비교해 representative point 보정과 highlight 폭 변화를 확인한다.

![Sphere light radius](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/_assets/captures/part3_chapter13_08_sphere_light_radius_storyboard.png?raw=true)

## 핵심 구현

### Stencil 기반 mirror pass

Mirror surface를 stencil에 기록하고 reflected scene draw를 해당 영역으로 제한한다.

- [Stencil mask와 reflection transform](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror/ExampleApp.cpp#L164-L181)

### Shadow filtering progression

Hard shadow의 light-space depth 비교에서 fixed-kernel PCF를 거쳐 blocker search와 penumbra 추정을 사용하는 PCSS로 확장한다.

- [Hard shadow depth comparison](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping/BasicPS.hlsl#L158-L180)
- [Fixed-kernel PCF](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/13_LightAndShadow_Step5_SoftShadowPCF/BasicPS.hlsl#L215-L275)
- [Blocker search와 variable penumbra](https://github.com/Razria93/Graphics_Study_Archive/blob/623cb8ccbc984584f47a7c68365d69840ed65c60/Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/BasicPS.hlsl#L146-L236)

## 처리 흐름

1. Step1에서 stencil mirror를 구성한다.
2. Step2에서 같은 결과를 PipelineStateObject abstraction으로 정리한다.
3. Step2B에서 독립 DepthPass와 MainPass shadow prototype을 확인한다.
4. Step3에서 depth reconstruction을 fog에 사용한다.
5. Step4→6에서 hard shadow, PCF와 PCSS를 비교한다.
6. Step7에서 depth-aware halo를 합성한다.
7. Step8에서 sphere light response를 근사한다.

## 구현 범위와 한계

- Raw 중복 Step2 경로는 보존하고 공개 표시만 Step2와 Step2B로 구분한다.
- PCSS는 고정된 light frustum과 near-plane 가정을 사용하는 approximation이다.
- Sphere light는 representative-point approximation이며 full Unreal Engine lighting parity를 의미하지 않는다.
- 원본 HDRI·texture·model을 직접 링크하지 않고 rendered evidence만 사용한다.

## 검증

- Step1–8와 Step2B Debug/Release x64 Clean/Rebuild와 run 성공
- 전체 창 PNG와 shadow filtering·sphere light radius storyboard full decode·metadata·공개 안전성 확인
- Shadow, Lighting, Pipeline Topic과 validator 통과

## 더 자세히 보기

- [Part3 Chapter10-13 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Part3_Chapter10-13/README.md)
- [Chapter10-13 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Step1 Mirror 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_01_Mirror.md)
- [Step4 ShadowMapping 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_04_ShadowMapping.md)
- [Step5 SoftShadowPCF 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_05_SoftShadowPCF.md)
- [Step6 SoftShadowPCSS 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_06_SoftShadowPCSS.md)
- [Step7 Halo 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_07_Halo.md)
- [Step8 UnrealSphereLight 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/03_Demos/Part3_Chapter10-13/13_08_UnrealSphereLight.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part3-chapter10-13-workflow/Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
