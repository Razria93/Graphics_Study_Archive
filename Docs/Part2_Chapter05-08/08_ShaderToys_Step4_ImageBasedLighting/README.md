# 08 ShaderToys Step4 ImageBasedLighting

## 목적

직접 조명을 매 frame 계산하는 대신, diffuse/specular lighting 결과가 미리 반영된 cubemap을 sampling해서 image-based lighting 효과를 확인하는 예제입니다. diffuse IBL은 normal 방향, specular IBL은 reflection 방향으로 cubemap을 읽습니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Image-based lighting | 환경 이미지를 조명 정보처럼 사용해서 물체의 diffuse/specular response를 근사하는 방식입니다. |
| Diffuse IBL | 표면 normal 방향으로 diffuse cubemap을 sampling해 넓게 퍼지는 환경광을 표현합니다. |
| Specular IBL | reflection vector 방향으로 specular cubemap을 sampling해 반사광을 표현합니다. |
| Prefiltered cubemap | 조명 효과를 미리 convolution/filtering한 cubemap입니다. |
| Material modulation | sampled IBL color에 material diffuse/specular 값을 곱해 표면 특성을 조절합니다. |

## 구현 흐름

1. `CubemapTextures/Atrium_diffuseIBL.dds`와 `CubemapTextures/Atrium_specularIBL.dds`를 cubemap shader resource view로 로드합니다.
2. skybox cube에는 specular cubemap을 표시합니다.
3. object mesh는 procedural sphere를 사용하고 `ojwD8.jpg` texture를 binding합니다.
4. pixel shader에서 normal 방향으로 diffuse IBL을 sampling합니다.
5. `reflect(-toEye, input.normalWorld)` 방향으로 specular IBL을 sampling합니다.
6. sampled diffuse/specular에 material 값을 곱하고 texture 사용 여부에 따라 object texture를 곱합니다.

## 핵심 코드

```cpp
CreateCubemapTexture(atribumDiffuseFilename, m_cubeMapping.diffuseResView);
CreateCubemapTexture(atribumSpecularFilename, m_cubeMapping.specularResView);

ID3D11ShaderResourceView *resViews[3] = {
    mesh->textureResourceView.Get(),
    m_cubeMapping.diffuseResView.Get(),
    m_cubeMapping.specularResView.Get()
};
m_context->PSSetShaderResources(0, 3, resViews);
```

```hlsl
Texture2D g_texture0 : register(t0);
TextureCube g_diffuseCube : register(t1);
TextureCube g_specularCube : register(t2);

float4 diffuse = g_diffuseCube.Sample(g_sampler, input.normalWorld);
float4 specular = g_specularCube.Sample(
    g_sampler, reflect(-toEye, input.normalWorld));
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step4_ImageBasedLighting`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step4_ImageBasedLighting.md`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting`
- Included assets:
  - `CubemapTextures/Atrium_diffuseIBL.dds`
  - `CubemapTextures/Atrium_specularIBL.dds`
  - `ojwD8.jpg`
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `stanford_dragon.stl`
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.3dcb2918/`
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
| Build Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Debug/Release | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 실행 확인 예정

Visual Studio에서 Debug x64와 Release x64 build/run을 확인합니다. 확인 범위에는 Atrium IBL cubemap load, sphere render, diffuse/specular IBL 표시, `Use Texture`, `Wireframe`, `Draw Normals`, material diffuse/specular/shininess slider, `m_viewRot` 조작을 포함합니다.
