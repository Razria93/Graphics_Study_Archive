# 08 ShaderToys Step7 Shadertoy

## 목적

Shadertoy 스타일의 fragment shader를 D3D11 pixel shader로 옮겨 fullscreen pass에서 실행하는 예제입니다. scene mesh 렌더링보다 post-processing quad와 shader constant/resource binding에 초점을 둡니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Shadertoy porting | Shadertoy의 `mainImage`, `iTime`, `iResolution`, `iChannel0` 같은 관례를 D3D11 shader/resource 구조로 바꿉니다. |
| Fullscreen pass | 화면 전체를 덮는 square mesh를 그리고 pixel shader에서 procedural effect를 계산합니다. |
| Pixel shader constant buffer | `iTime`, `dx`, `dy` 같은 shader parameter를 CPU에서 갱신해 GPU로 보냅니다. |
| Shader resource texture | `shadertoytexture0.jpg`를 `t0` texture로 bind해서 shader 내부 sample source로 사용합니다. |
| Procedural shader | mesh나 material보다 noise, ray marching, texture sampling, time 변화로 이미지를 만듭니다. |

## 구현 흐름

1. `BuildFilters()`에서 `shadertoytexture0.jpg`를 `ID3D11ShaderResourceView`로 생성합니다.
2. `ImageFilter`가 fullscreen square mesh와 `SamplingVertexShader`를 준비합니다.
3. `StarPixelShader`를 pixel shader로 연결해 화면 전체에 Shadertoy effect를 그립니다.
4. `Update()`에서 누적 시간 값을 `m_pixelConstData.iTime`에 기록하고 constant buffer를 갱신합니다.
5. `Render()`는 scene pass 없이 `m_filters`를 순회하며 render target에 바로 shader 결과를 출력합니다.

## 핵심 코드

```cpp
D3D11Utils::CreateTexture(m_device, "shadertoytexture0.jpg", texture,
                          textureResourceView);

auto shaderToy =
    make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Star",
                             m_screenWidth, m_screenHeight);

shaderToy->SetShaderResources({textureResourceView});
shaderToy->SetRenderTargets({m_renderTargetView});
m_filters.push_back(shaderToy);
```

```cpp
static float time = 0.0f;

m_filters.back()->m_pixelConstData.iTime = time;
m_filters.back()->UpdateConstantBuffers(m_device, m_context);

time += dt;
```

```hlsl
Texture2D g_texture0 : register(t0);
SamplerState g_sampler : register(s0);

cbuffer SamplingPixelConstantData : register(b0)
{
    float dx;
    float dy;
    float threshold;
    float strength;
    float iTime;
    float dummy[3];
};
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step7_Shadertoy`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\@ShaderToy.md`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy`
- Included assets:
  - `ojwD8.jpg`
  - `wall.jpg`
  - `shadertoytexture0.jpg`
- Included shader variants:
  - `SeascapePixelShader.hlsl`
  - `StarPixelShader.hlsl`
  - `EnergeticFlybyPixelShader.hlsl`
- Active shader path:
  - `BuildFilters()` currently creates `ImageFilter(..., L"Sampling", L"Star", ...)`.
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.24211f82/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
- Project cleanup:
  - archive에 포함하지 않는 `.clang-format` project/filter 참조를 제거했습니다.
  - 비활성 예시 주석의 `c:/zelda/` 절대 경로를 archive 상대 경로 예시로 바꿨습니다.
- Asset/shader public readiness: 검토 필요

## 확인 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 완료 |
| Build Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Debug/Release | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Public Readiness Notes

`SeascapePixelShader.hlsl`에는 Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License 표기가 포함되어 있고, `StarPixelShader.hlsl`도 Shadertoy 원본 링크 기반 코드입니다. private archive에는 학습/검토 목적으로 보관하되, public repo 후보로 확정하기 전에는 shader 원 저작권, license compatibility, attribution 방식, texture asset 출처를 따로 확인해야 합니다.
