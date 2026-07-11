# 08 ShaderToys Step6 BloomEffect

## 목적

scene을 바로 back buffer에만 그리지 않고, 렌더링 결과를 texture로 복사한 뒤 post-processing filter chain을 통과시켜 bloom 효과를 만드는 예제입니다. 밝은 영역만 threshold로 남기고, downsample/upsample 과정과 blur를 거쳐 원본 scene에 다시 combine합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Render target texture | 화면 결과를 후처리 shader에서 다시 읽을 수 있도록 별도 texture/RTV/SRV로 관리합니다. |
| Shader resource view | filter shader가 이전 단계의 렌더링 결과를 texture로 sampling할 수 있게 합니다. |
| Threshold filter | 일정 밝기 이상인 pixel만 bloom 후보로 남깁니다. |
| Downsample / upsample | 낮은 해상도에서 blur를 적용해 bloom이 넓게 퍼지는 효과를 만듭니다. |
| Blur X/Y | separable blur처럼 X, Y 방향을 나눠 처리합니다. |
| Combine pass | blur된 bloom texture와 원본 scene texture를 합성합니다. |

## 구현 흐름

1. `Stonewall_diffuseIBL.dds` / `Stonewall_specularIBL.dds`로 IBL cubemap을 초기화합니다.
2. sphere와 Zelda character mesh 중 하나를 선택해 scene을 렌더링합니다.
3. back buffer의 MSAA render result를 `ResolveSubresource()`로 `Texture2D`에 복사합니다.
4. `ImageFilter` chain에서 sampling, threshold, downsample, blur X/Y, upsample을 순서대로 실행합니다.
5. 마지막 `CombinePixelShader`에서 bloom texture와 원본 scene texture를 더합니다.
6. GUI에서 `Bloom Threshold`, `Bloom Strength`, mesh selection, material controls를 조작합니다.

## 핵심 코드

```cpp
m_context->ResolveSubresource(
    m_tempTexture.Get(), 0,
    backBuffer.Get(), 0,
    DXGI_FORMAT_R8G8B8A8_UNORM);

for (auto &f : m_filters)
{
    f->Render(m_context);
}
```

```cpp
auto thresholdFilter = std::make_shared<ImageFilter>(
    m_device, m_context, L"Sampling", L"Threshold", width, height);
thresholdFilter->SetShaderResources({m_filters.back()->m_shaderResourceView});

auto combineFilter = std::make_shared<ImageFilter>(
    m_device, m_context, L"Sampling", L"Combine",
    this->m_screenWidth, this->m_screenHeight);
combineFilter->SetShaderResources(
    {m_filters.back()->m_shaderResourceView, this->m_shaderResourceView});
combineFilter->SetRenderTargets({this->m_renderTargetView});
```

```hlsl
float4 sampling = g_texture0.Sample(g_sampler, input.texcoord);

return ((sampling.x + sampling.y + sampling.z) / 3) > threshold
    ? sampling
    : float4(0.0, 0.0, 0.0, 1.0);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step6_BloomEffect`
- Related raw notes:
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step6_BloomEffect.md`
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step6_BloomEffect 1.md`
- Reference-only raw variant:
  - `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step6-1_BloomEffect_Debug`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect`
- Included assets:
  - `CubemapTextures/Stonewall_diffuseIBL.dds`
  - `CubemapTextures/Stonewall_specularIBL.dds`
  - `ojwD8.jpg`
  - `wall.jpg`
  - `f3d-data/zelda/zeldaPosed001.fbx`
  - `f3d-data/zelda/*_diff.png`
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.0a4efec0/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
  - unused cubemap DDS files and source image folders
  - debug variant folder `08_ShaderToys_Step6-1_BloomEffect_Debug`
- Path adjustment:
  - raw의 `c:/zelda/source/` 절대 경로를 archive 상대 경로 `f3d-data/zelda/`로 변경했습니다.
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

Visual Studio에서 Debug x64와 Release x64 build/run을 확인합니다. 확인 범위에는 sphere/character 전환, Zelda model load, Stonewall IBL load, bloom threshold/strength slider, filter chain 적용, blur/combine 결과, `Use Texture`, `Wireframe`, `Draw Normals`, `m_viewRot` 조작을 포함합니다.
