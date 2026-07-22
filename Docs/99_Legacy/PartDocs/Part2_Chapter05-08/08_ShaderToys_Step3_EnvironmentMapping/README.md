# 08 ShaderToys Step3 EnvironmentMapping

## 목적

cubemap을 skybox 배경뿐 아니라 object 표면 반사에도 사용하는 예제입니다. camera에서 표면을 바라보는 방향과 normal을 이용해 reflection vector를 만들고, 그 방향으로 `TextureCube`를 sampling해서 주변 환경이 물체에 비치는 효과를 확인합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Environment mapping | 주변 환경 cubemap을 object 표면에 반사된 것처럼 sampling하는 기법입니다. |
| Reflection vector | view direction과 surface normal로 만든 반사 방향입니다. |
| `reflect()` | HLSL에서 incident vector와 normal을 받아 reflection vector를 계산하는 함수입니다. |
| `TextureCube` | 3D direction vector로 cubemap을 sampling하는 HLSL texture type입니다. |
| Shader resource slot | object texture는 `t0`, cubemap은 `t1`처럼 shader resource view slot을 나눠 binding합니다. |

## 구현 흐름

1. `CubemapTextures/HumusTextures/NightPath.dds`를 cubemap shader resource view로 로드합니다.
2. skybox cube는 cubemap shader로 먼저 렌더링합니다.
3. Zelda mesh를 렌더링할 때 object texture와 cubemap SRV를 함께 pixel shader에 binding합니다.
4. pixel shader에서 `toEye`와 `normalWorld`를 이용해 reflection direction을 계산합니다.
5. `Use Reflection` toggle이 켜져 있으면 object base color 대신 cubemap reflection color를 사용합니다.

## 핵심 코드

```cpp
ID3D11ShaderResourceView *resViews[2] = {
    mesh->textureResourceView.Get(),
    m_cubeMapping.cubemapResourceView.Get()
};
m_context->PSSetShaderResources(0, 2, resViews);
```

```hlsl
Texture2D g_texture0 : register(t0);
TextureCube g_textureCube0 : register(t1);

color = g_textureCube0.Sample(g_sampler, reflect(-toEye, input.normalWorld));
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\08_ShaderToys_Step3_EnvironmentMapping`
- Related raw note: `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter08_ShaderToys_Step3_EnvironmentMapping.md`
- Archive source: `Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping`
- Included assets:
  - `CubemapTextures/HumusTextures/NightPath.dds`
  - `CubemapTextures/HumusTextures/readme.txt`
  - `f3d-data/zelda/zeldaPosed001.fbx`
  - `f3d-data/zelda/*_diff.png`
  - `crate2_diffuse.png`
  - `wall.jpg`
  - `ojwD8.jpg`
  - `stanford_dragon.stl`
- Excluded:
  - `.vs/`
  - generated folder `08_Shade.7e02b128/`
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
  - unused `CubemapTextures/*.dds`
  - unused source image folders and other cubemap folders
- Path adjustment:
  - raw의 `c:/zelda/source/` 절대 경로를 archive 상대 경로 `f3d-data/zelda/`로 변경했습니다.
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

사용자가 Visual Studio에서 Debug x64와 Release x64 build/run을 확인했습니다. skybox cubemap 표시, Zelda model load, object texture 표시, environment reflection 표시, `Use Reflection`, `Use Texture`, `Wireframe`, `Draw Normals`, `m_viewRot` 조작 확인은 실행 확인 범위에 포함합니다.
