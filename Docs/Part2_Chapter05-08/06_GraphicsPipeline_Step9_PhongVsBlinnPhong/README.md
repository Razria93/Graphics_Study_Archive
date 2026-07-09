# 06 GraphicsPipeline Step9 PhongVsBlinnPhong

## 목적

Phong specular와 Blinn-Phong specular를 같은 scene에서 전환하며 비교하는 예제입니다. 이전 lighting/window resize 기반은 유지하고, pixel shader에서 specular highlight 계산 방식만 선택할 수 있도록 `useBlinnPhong` toggle을 추가합니다.

이 archive에서는 실행 가능한 source/project/shader/asset만 포함하고, 원문 학습 주석은 source 밖으로 분리합니다.

## 핵심 키워드

- Phong shading
- Blinn-Phong shading
- specular highlight
- reflection vector
- half vector
- material shininess
- `reflect()`
- ImGui toggle

## 구현 흐름

1. CPU constant buffer에 `useBlinnPhong` flag를 추가합니다.
2. ImGui checkbox로 Phong과 Blinn-Phong specular 계산을 전환합니다.
3. Blinn-Phong에서는 light direction과 view direction의 half vector를 사용합니다.
4. Phong에서는 light reflection vector와 view direction의 dot product를 사용합니다.
5. 같은 material shininess와 light setup에서 highlight 차이를 비교합니다.

## 핵심 코드

```cpp
ImGui::Checkbox("Use BlinnPhong", &m_pixelConstantBufferData.useBlinnPhong);
```

runtime에서 specular 계산 방식을 전환할 수 있게 합니다.

```hlsl
float3 halfway = normalize(toEye + lightVec);
float hdotn = dot(halfway, normal);
float3 specular = mat.specular * pow(max(hdotn, 0.0f), mat.shininess * 2.0);
```

Blinn-Phong은 half vector와 normal의 각도를 사용합니다.

```hlsl
float3 r = -reflect(lightVec, normal);
float3 specular = mat.specular * pow(max(dot(toEye, r), 0.0f), mat.shininess);
```

Phong은 reflected light vector와 view direction의 각도를 사용합니다.

## Archive 반영 메모

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step9_PhongVsBlinnPhong`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step9_PhongVsBlinnPhong`
- 원문 학습 주석은 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step9_PhongVsBlinnPhong/source-comments.md`에 분리했습니다.
- `.vs/`, `x64/`, `.user`, `imgui.ini`, `.clang-format`, raw build output은 archive에 포함하지 않았습니다.
- 실행에 필요한 `crate2_diffuse.png`, `wall.jpg`는 private archive asset으로 포함했습니다.
- texture asset은 public 공개 전 license/source 확인이 필요합니다.
- HLSL/HLSLI 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.
- raw project의 Release HLSL 설정에 shader type 누락이 있어 archive project에서 Release용 pixel/vertex shader 설정을 보강했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 이유: private archive 학습 예제이고 texture asset을 포함합니다. public subset으로 분리하기 전 asset license/source, 강의 기반 구조 표현 정도, dependency 재현성을 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
