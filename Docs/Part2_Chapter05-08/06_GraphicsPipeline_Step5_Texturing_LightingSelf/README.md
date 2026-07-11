# 06 GraphicsPipeline Step5 Texturing LightingSelf

## 목적

texture sampling 예제에 조명 계산을 결합한 변형입니다. CPU 쪽에서는 texture resource, shader resource view, sampler state, light constant buffer를 준비하고, shader 쪽에서는 texture color에 ambient, diffuse, specular lighting을 곱해 최종 pixel color를 만듭니다.

이 archive에서는 기존 학습용 장문 주석을 source에서 분리하고, 실행 가능한 코드와 필요한 입력 asset만 보존합니다.

## 핵심 키워드

- texture sampling
- shader resource view
- sampler state
- normal matrix
- light constant buffer
- ambient, diffuse, specular
- attenuation
- `Texture2D.Sample()`
- `PSSetShaderResources()`
- `PSSetConstantBuffers()`

## 구현 흐름

1. cube vertex data에 position, color, normal, texture coordinate를 포함합니다.
2. `crate2_diffuse.png`, `wall.jpg`를 읽어 `ID3D11Texture2D`와 `ID3D11ShaderResourceView`를 생성합니다.
3. pixel shader stage에 texture resource view와 sampler state를 binding합니다.
4. model/view/projection matrix와 normal matrix를 vertex shader constant buffer로 전달합니다.
5. light position, material, attenuation 값을 pixel shader constant buffer로 전달합니다.
6. pixel shader에서 texture color를 sample하고 lighting term과 결합합니다.

## 핵심 코드

```cpp
AppBase::CreateTexture("crate2_diffuse.png", m_texture_0,
                       m_textureResourceView_0);
AppBase::CreateTexture("wall.jpg", m_texture_1, m_textureResourceView_1);
```

runtime에 필요한 image file을 texture resource와 shader resource view로 준비합니다.

```cpp
m_context->PSSetShaderResources(0, 1, pixelResources_0);
m_context->PSSetShaderResources(1, 1, pixelResources_1);
m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
m_context->PSSetConstantBuffers(0, 1, m_lightConstantBuffer.GetAddressOf());
```

pixel shader가 texture와 lighting parameter를 함께 사용할 수 있도록 resource와 constant buffer를 binding합니다.

```hlsl
float4 text = g_texture0.Sample(g_sampler, input.texcoord);
float4 ambient = float4(lightAmbient, 1.0) * float4(matAmbient, 1.0) * text;
float diffuseRatio = max(0.0, dot(normalDir, lightDir));
float4 diffuse = float4(lightDiffuse, 1.0) * float4(matDiffuse, 1.0) * diffuseRatio * text;
float4 color = ambient + (diffuse + specular) * attenuation;
```

texture sample 결과를 단순 색상으로 끝내지 않고, 조명 성분과 결합해 재질이 빛을 받는 형태를 확인합니다.

## Archive 반영 메모

- raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\06_GraphicsPipeline_Step5_Texturing_LightingSelf`
- archive target: `Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing_LightingSelf`
- raw 내부 solution/project filename은 `06_GraphicsPipeline_Step5_Texturing.*`를 재사용합니다.
- 원문 학습 주석은 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing_LightingSelf/source-comments.md`에 분리했습니다.
- `.vs/`, `x64/`, `.user`, `imgui.ini`, `.clang-format`, raw build output은 archive에 포함하지 않았습니다.
- 실행에 필요한 `crate2_diffuse.png`, `wall.jpg`는 private archive asset으로 포함했습니다.
- texture asset은 public 공개 전 license/source 확인이 필요합니다.
- HLSL 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: Debug x64, Release x64 성공
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 이유: private archive 학습 예제이고 texture asset을 포함합니다. public subset으로 분리하기 전 asset license/source, 강의 기반 구조 표현 정도, dependency 재현성을 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
