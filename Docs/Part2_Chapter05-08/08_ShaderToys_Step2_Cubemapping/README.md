# 08 ShaderToys Step2 Cubemapping

## 목적

cube texture를 방향 vector로 sampling해서 skybox를 렌더링하는 예제입니다. 일반 2D texture가 UV coordinate로 색을 읽는다면, cubemap은 `float3` 방향을 이용해 여섯 면 중 하나에서 색을 읽습니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Cubemap | 6면 texture를 하나의 cube texture로 다루는 GPU resource입니다. |
| Skybox | scene을 큰 cube 내부에 넣고 cube 안쪽 면에 환경 texture를 그리는 방식입니다. |
| `TextureCube` | HLSL에서 cubemap을 sampling하는 texture type입니다. |
| DDS | DirectX에서 cubemap 같은 texture resource를 저장하고 로드할 때 자주 쓰는 형식입니다. |
| Inside-facing cube | camera가 cube 내부에 있으므로 cube index 순서를 뒤집어 안쪽 면을 보이게 합니다. |

## 구현 흐름

1. `CreateDDSTextureFromFileEx()`로 `skybox/skybox.dds`를 cubemap shader resource view로 로드합니다.
2. `GeometryGenerator::MakeBox(20.0f)`로 큰 cube mesh를 만듭니다.
3. cube 내부가 보이도록 `std::reverse(cubeMeshData.indices.begin(), cubeMeshData.indices.end())`로 winding을 뒤집습니다.
4. cubemap 전용 vertex/pixel shader를 생성합니다.
5. render 단계에서 skybox cube를 먼저 그리고, 이후 Zelda mesh를 일반 lighting shader로 렌더링합니다.

## 핵심 코드

```cpp
auto hr = CreateDDSTextureFromFileEx(
    this->m_device.Get(), L"./skybox/skybox.dds",
    0, D3D11_USAGE_DEFAULT,
    D3D11_BIND_SHADER_RESOURCE, 0,
    D3D11_RESOURCE_MISC_TEXTURECUBE,
    DDS_LOADER_FLAGS(false),
    (ID3D11Resource **)texture.GetAddressOf(),
    this->m_cubeMapping.cubemapResourceView.GetAddressOf(),
    nullptr);

MeshData cubeMeshData = GeometryGenerator::MakeBox(20.0f);
std::reverse(cubeMeshData.indices.begin(), cubeMeshData.indices.end());
```

```hlsl
TextureCube g_textureCube0 : register(t0);
SamplerState g_sampler : register(s0);

float4 main(PixelShaderInput input) : SV_TARGET
{
    return g_textureCube0.Sample(g_sampler, input.posWorld.xyz);
}
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step2_Cubemapping`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step2_Cubemapping.md`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping`
- Included assets:
  - `skybox/skybox.dds`
  - `f3d-data/zelda/zeldaPosed001.fbx`
  - `f3d-data/zelda/*_diff.png`
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
  - `stanford_dragon.stl`
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.80199106/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
  - `skybox/texassemble.exe`
  - unused skybox source images and IBL DDS files
  - `SaintPetersBasilica/`
- Path adjustment:
  - raw의 `C:/zelda/source/` 절대 경로를 archive 상대 경로 `f3d-data/zelda/`로 변경했습니다.
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

사용자가 Visual Studio에서 Debug x64와 Release x64 build/run을 확인했습니다. skybox cubemap 표시, Zelda model load, texture binding, `Use Texture`, `Wireframe`, `Draw Normals`, `m_viewRot` 조작 확인은 실행 확인 범위에 포함합니다.
