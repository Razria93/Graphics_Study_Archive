# 06 GraphicsPipeline Step6 Lighting

## 목적

texture가 적용된 cube 예제에 여러 lighting model을 정리해서 연결하는 단계입니다. `Common.hlsli`에 material, light, Blinn-Phong 조명 함수와 directional/point/spot light 계산을 모으고, pixel shader에서는 현재 선택된 light type에 맞춰 조명 결과를 누적합니다.

이 archive에서는 실행 가능한 source/project/shader/asset만 포함하고, 원문 학습 주석은 source 밖으로 분리합니다.

## 핵심 키워드

- Blinn-Phong lighting
- directional light
- point light
- spot light
- material
- attenuation
- `Common.hlsli`
- vertex/pixel constant buffer
- normal transform
- texture toggle

## 구현 흐름

1. cube vertex data에 position, normal, texture coordinate를 구성합니다.
2. vertex shader에서 model space position/normal을 world space로 변환합니다.
3. `Common.hlsli`에 `Material`, `Light`, `BlinnPhong()`, `ComputeDirectionalLight()`, `ComputePointLight()`, `ComputeSpotLight()`를 정의합니다.
4. pixel shader에서 eye position, material, light array, texture toggle을 constant buffer로 받아 조명 결과를 계산합니다.
5. CPU 쪽에서는 ImGui로 light type과 material/light parameter를 조절합니다.
6. `crate2_diffuse.png`, `wall.jpg` texture resource를 pixel shader에 binding합니다.

## 핵심 코드

```cpp
AppBase::CreateTexture("crate2_diffuse.png", m_texture,
                       m_textureResourceView);
AppBase::CreateTexture("wall.jpg", m_texture2, m_textureResourceView2);
```

실행에 필요한 texture resource와 shader resource view를 준비합니다.

```cpp
m_context->PSSetShaderResources(0, 2, pixelResources);
m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
m_context->PSSetConstantBuffers(0, 1,
                                m_pixelConstantBuffer.GetAddressOf());
```

pixel shader가 texture와 lighting parameter를 함께 사용할 수 있도록 resource, sampler, constant buffer를 binding합니다.

```hlsl
color += ComputeDirectionalLight(lights[i], material, input.normalWorld, toEye);
color += ComputePointLight(lights[i], material, input.posWorld, input.normalWorld, toEye);
color += ComputeSpotLight(lights[i], material, input.posWorld, input.normalWorld, toEye);
```

light type별 계산을 `Common.hlsli`의 함수로 분리해 pixel shader 본문을 비교적 단순하게 유지합니다.

## Archive 반영 메모

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step6_Lighting`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting`
- 원문 학습 주석은 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/source-comments.md`에 분리했습니다.
- `.vs/`, `x64/`, `.user`, `imgui.ini`, `.clang-format`, raw build output은 archive에 포함하지 않았습니다.
- 실행에 필요한 `crate2_diffuse.png`, `wall.jpg`는 private archive asset으로 포함했습니다.
- texture asset은 public 공개 전 license/source 확인이 필요합니다.
- HLSL/HLSLI 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: Debug x64, Release x64 성공
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 이유: private archive 학습 예제이고 texture asset을 포함합니다. public subset으로 분리하기 전 asset license/source, 강의 기반 구조 표현 정도, dependency 재현성을 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../../ImportHistory/Manifests/Part2_Chapter05-08.md)
