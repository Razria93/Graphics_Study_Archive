# 08 ShaderToys Step1 RimLighting

## 목적

mesh 표면의 normal과 camera 방향의 관계를 이용해 외곽선을 밝게 강조하는 rim lighting 예제입니다. 기존 Blinn-Phong lighting 결과에 `NdotE` 기반의 가장자리 강조 값을 더해서 역광, 실드, 물광처럼 보이는 시각 효과를 만듭니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Rim lighting | object edge를 밝게 만들어 외곽 실루엣을 강조하는 shading effect |
| `NdotE` | surface normal과 eye direction의 dot product입니다. 1에 가까울수록 정면, 0에 가까울수록 외곽입니다. |
| Fresnel-like effect | grazing angle에서 강해지는 시각 효과를 근사하는 방식입니다. |
| `pow()` shaping | rim factor의 분포를 조절해서 좁고 강한 외곽선 또는 넓고 은은한 빛을 만듭니다. |
| `smoothstep` option | rim 값을 부드럽게 전환하는 shader shaping 옵션입니다. |

## 구현 흐름

1. `eyeWorld`와 `input.posWorld`로 pixel에서 camera로 향하는 `toEye` vector를 계산합니다.
2. `dot(input.normalWorld, toEye)`로 normal과 view direction의 정렬 정도를 구합니다.
3. 외곽일수록 값이 커지도록 `1.0 - NdotE`로 관계를 뒤집습니다.
4. `pow(rimBase, rimPower)`로 rim 분포를 조절합니다.
5. GUI에서 `Rim Strength`, `Rim Color`, `Rim Power`, `Use Smoothstep`을 바꿔 효과를 확인합니다.

## 핵심 코드

```hlsl
float3 toEye = normalize(eyeWorld - input.posWorld);
float NdotE = saturate(dot(input.normalWorld, toEye));
float rimBase = 1.0 - NdotE;

rimBase = max(rimBase, 1e-4);
float rimPow = max(rimPower, 0.0);

float rim = pow(rimBase, rimPow);

color = useSmoothstep ?
        color + rim * (rimColor * rimStrength) :
        color;
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step1_RimLighting`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step1_RimLighting.md`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting`
- Included assets:
  - `stanford_dragon.stl`
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.d92039cc/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
- Source cleanup:
  - project/filter에서 `.clang-format` 참조를 제거했습니다.
  - 실행에 필요 없는 개인 절대경로 기반 sample model 주석을 archive 기준 설명으로 교체했습니다.
- Asset public readiness: 검토 필요

## 확인 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Build Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Debug/Release | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 다음 확인

Visual Studio에서 Debug x64와 Release x64 build/run을 확인합니다. 실행 시 `Rim Strength`, `Rim Color`, `Rim Power`, `Use Smoothstep`, `Use Texture`, `Wireframe`, `Draw Normals` 동작을 함께 확인합니다.
