# 06 GraphicsPipeline Step5 Texturing

## 목적

D3D11 pixel shader에서 texture resource를 sampling하는 예제입니다. vertex data에 texture coordinate를 포함하고, CPU에서 image file을 texture resource와 shader resource view로 만들어 pixel shader에 연결합니다.

## 핵심 키워드

- texture coordinate
- `Texture2D`
- `SamplerState`
- shader resource view
- `PSSetShaderResources`
- `PSSetSamplers`
- `stbi_load`
- `D3D11_TEXTURE2D_DESC`
- sampler address mode

## 구현 흐름

1. cube vertex data에 texture coordinate를 포함합니다.
2. `crate2_diffuse.png`, `wall.jpg`를 CPU에서 읽어 texture data로 준비합니다.
3. `ID3D11Texture2D`와 `ID3D11ShaderResourceView`를 생성합니다.
4. sampler state를 만들어 pixel shader stage에 연결합니다.
5. pixel shader에서 `Texture2D.Sample()`로 두 texture를 sampling합니다.
6. draw 전에 texture resource view와 sampler를 `PSSetShaderResources()`, `PSSetSamplers()`로 binding합니다.

## 핵심 코드

```cpp
AppBase::CreateTexture("crate2_diffuse.png", m_texture_0,
                       m_textureResourceView_0);
AppBase::CreateTexture("wall.jpg", m_texture_1, m_textureResourceView_1);
```

runtime에 필요한 texture file을 읽어 D3D11 texture resource와 shader resource view로 만듭니다.

```cpp
m_context->PSSetShaderResources(0, 1, pixelResources_0);
m_context->PSSetShaderResources(1, 1, pixelResources_1);
m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
```

pixel shader stage에 texture resource와 sampler를 연결합니다. 이 예제의 핵심은 texture coordinate가 rasterization을 거쳐 보간되고, pixel shader에서 그 좌표로 texture를 sampling하는 흐름입니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 texture 실험 메모는 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing/source-comments.md`로 분리했습니다.
- `.vs/`, `x64/`, 중간 build folder, `.user`, `imgui.ini`, `.clang-format`는 archive에 포함하지 않았습니다.
- 실행에 필요한 `crate2_diffuse.png`, `wall.jpg`는 private archive asset으로 포함했습니다.
- texture asset의 public readiness는 별도 라이선스/출처 검토 전까지 `검토 필요`입니다.
- shader 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제이며 texture asset을 포함합니다. public subset으로 분리하기 전 asset license/source, shader, ImGui/vcpkg dependency, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
