# 08 ShaderToys Step5 FresnelEffect

## 목적

image-based lighting 위에 Schlick approximation 기반 Fresnel 효과를 더해, view angle에 따라 specular reflection이 달라지는 현상을 확인하는 예제입니다. surface normal과 view direction이 수직에 가까워질수록 specular contribution이 강해지고, 정면에 가까울수록 material의 `fresnelR0` 값에 가까워집니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Fresnel effect | 표면을 바라보는 각도에 따라 반사율이 달라지는 현상입니다. |
| Schlick approximation | Fresnel 항을 실시간 shader에서 저렴하게 근사하는 식입니다. |
| `fresnelR0` | 정면 입사에서의 기본 반사율입니다. material 고유 속성처럼 다룹니다. |
| Grazing angle | view direction과 normal이 거의 수직인 영역으로, 반사가 강해집니다. |
| Specular modulation | Fresnel 결과를 specular IBL에 곱해 각도별 반사 강도를 조절합니다. |

## 구현 흐름

1. `CubemapTextures/Stonewall_diffuseIBL.dds`와 `CubemapTextures/Stonewall_specularIBL.dds`를 cubemap shader resource view로 로드합니다.
2. procedural sphere에 `ojwD8.jpg` texture를 적용합니다.
3. diffuse IBL은 normal 방향으로, specular IBL은 reflection 방향으로 sampling합니다.
4. `SchlickFresnel(material.fresnelR0, input.normalWorld, toEye)`로 Fresnel factor를 계산합니다.
5. 계산된 Fresnel factor를 specular IBL에 곱합니다.
6. GUI의 `Material FresnelR0` slider로 정면 반사율을 조정합니다.

## 핵심 코드

```hlsl
float3 SchlickFresnel(float3 fresnelR0, float3 normal, float3 toEye)
{
    float normalDotView = saturate(dot(normal, toEye));
    float f0 = 1.0f - normalDotView;

    return fresnelR0 + (1.0f - fresnelR0) * pow(f0, 5.0);
}

float3 f = SchlickFresnel(material.fresnelR0, input.normalWorld, toEye);
specular.xyz *= f;
```

```cpp
ImGui::SliderFloat3("Material FresnelR0",
                    &m_BasicPixelConstantBufferData.material.fresnelR0.x,
                    0.0f, 1.0f);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step5_FresnelEffect`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step5_FresnelEffect.md`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect`
- Included assets:
  - `CubemapTextures/Stonewall_diffuseIBL.dds`
  - `CubemapTextures/Stonewall_specularIBL.dds`
  - `ojwD8.jpg`
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `stanford_dragon.stl`
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.a4b616bd/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
  - unused cubemap DDS files and source image folders
- Source cleanup:
  - raw의 private/sample absolute path comments를 source에서 제거했습니다.
- Asset public readiness: 검토 필요

## 확인 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Build Debug x64 | 성공 |
| Build Release x64 | 성공 |
| Run Debug/Release | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 실행 확인

사용자가 Visual Studio에서 Debug x64와 Release x64 build/run을 확인했습니다. Stonewall IBL cubemap load, sphere render, Fresnel specular 변화, `Material FresnelR0`, material diffuse/specular/shininess slider, `Use Texture`, `Wireframe`, `Draw Normals`, `m_viewRot` 조작 확인은 실행 확인 범위에 포함합니다.
