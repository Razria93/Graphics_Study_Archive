# 12_PBR_Step1_UnrealPBR

## Chapter Focus

이 예제는 Unreal-style PBR workflow를 DirectX11 shader pipeline에서 확인하는 단계입니다.

핵심은 material texture set에서 albedo, normal, height, ambient occlusion, metallic, roughness 값을 읽고, HDR environment map과 BRDF lookup texture를 함께 사용해 image-based lighting 기반 PBR shading을 구성하는 흐름입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\12_PBR_Step1_UnrealPBR`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\12_PBR_Step1_UnrealPBR`
- 이번 단계에서는 primary raw의 solution/project/source를 기준으로 import했습니다.
- 실행에 필요한 HDRI DDS와 `worn-painted-metal-ue` PBR texture set만 공용 asset으로 선별 포함했습니다.
- raw의 `.vs/`, `x64/`, generated project output, `.vcxproj.user`, `.clang-format`, `imgui.ini`는 제외했습니다.
- 장문 학습 주석과 문서 정리는 2차 문서 정리 단계에서 별도로 처리합니다.

## Runtime Assets

| Archive path | Source file | Size | SHA256 |
| --- | --- | --- | --- |
| `Assets/Textures/Cubemaps/HDRI/SampleEnvHDR.dds` | `SampleEnvHDR.dds` | 33,554,624 bytes | `CA45C68191680911A70185F2C61C5293133EA1C48D732ECEFE9795F7D5C63816` |
| `Assets/Textures/Cubemaps/HDRI/SampleSpecularHDR.dds` | `SampleSpecularHDR.dds` | 33,554,624 bytes | `CC7A7EFE133C87EDA754342648A6A17AEC3C5CA8397648CA473A7549FD7BD7D5` |
| `Assets/Textures/Cubemaps/HDRI/SampleDiffuseHDR.dds` | `SampleDiffuseHDR.dds` | 1,966,208 bytes | `76556B8348097DB86136FB44A5DB1CB306E730FDAF80B08B73637F0843FD970B` |
| `Assets/Textures/Cubemaps/HDRI/SampleBrdf.dds` | `SampleBrdf.dds` | 1,310,848 bytes | `A1E4C4251D828BE94327D188435743650AEADB3E8681E608B9337100A688C943` |
| `Assets/Textures/PBR/worn-painted-metal-ue/worn-painted-metal_albedo.png` | same | 5,151,527 bytes | `1E665407C89D1B2EFAAC067BBB2EA409EB5F9B89EB3E8D0C2400238A32137BA6` |
| `Assets/Textures/PBR/worn-painted-metal-ue/worn-painted-metal_normal-dx.png` | same | 6,780,516 bytes | `9641865826E859E36EA3E6444719AAC8833C943311FDD80BFA03D46CAB64D30E` |
| `Assets/Textures/PBR/worn-painted-metal-ue/worn-painted-metal_height.png` | same | 64,781 bytes | `C24E51ACE1300836B27B8B20EC9EA7C331B5E13A6E7C832680BA3377751E7940` |
| `Assets/Textures/PBR/worn-painted-metal-ue/worn-painted-metal_ao.png` | same | 1,108,975 bytes | `363AF5EACAE2273C62C90A703653216907312939BABBDB9D5412B8AEEB8342C3` |
| `Assets/Textures/PBR/worn-painted-metal-ue/worn-painted-metal_metallic.png` | same | 499,812 bytes | `570225527E08423C56C7FFF988ADC062845BCE0D4A518AB745E9DDDC76C4938A` |
| `Assets/Textures/PBR/worn-painted-metal-ue/worn-painted-metal_roughness.png` | same | 2,652,104 bytes | `A68B2D9906C4527B81BB1DCDA617C2349CAB5F1D999F1F89C4B665811A6DFD85` |

All selected assets are private archive material and require license/source review before any public subset is prepared.

## Verification

- Static verification: 통과
- Debug x64 run: 미확인
- Release x64 run: 미확인

## Notes

- `.clang-format` project reference was removed because the file is not archived.
- Release x64 shader model settings were normalized to `5.0` for `CubeMappingPS`, `CubeMappingVS`, `NormalPS`, and `NormalVS`.
- `worn-painted-metal_preview.jpg` was excluded because the example does not load it at runtime.
