# 11_TexturingTechniques_Step5_HDRPipeline

## Chapter Focus

이 예제는 HDR cubemap 기반 image-based lighting과 후처리 HDR pipeline을 연결하는 단계입니다.

핵심은 skybox/IBL용 HDR DDS cubemap을 읽고, scene render target을 거친 뒤 post-process pass에서 exposure/gamma/bloom 계열 처리를 적용하는 흐름입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step5_HDRPipeline`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step5_HDRPipeline`
- OriginalExamples도 같은 `OutdoorEnvHDR.dds`, `OutdoorDiffuseHDR.dds`, `OutdoorSpecularHDR.dds` 경로를 참조합니다.
- raw repo에는 `Outdoor*` 파일이 없고 `Sample*` HDR DDS asset만 있어서, 코드 경로는 유지하고 expected filename으로 replacement DDS를 배치했습니다.
- `Bricks075A_4K_Color.png`도 raw asset에 없어서, 기존 1K color texture를 expected filename으로 배치했습니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

Step5 실행 확인을 위해 replacement/compatibility asset을 추가했습니다.

| Archive path | Source file | Size | SHA256 |
| --- | --- | --- | --- |
| `Assets/Textures/Cubemaps/HDRI/OutdoorEnvHDR.dds` | `SampleEnvHDR.dds` | 33,554,624 bytes | `CA45C68191680911A70185F2C61C5293133EA1C48D732ECEFE9795F7D5C63816` |
| `Assets/Textures/Cubemaps/HDRI/OutdoorDiffuseHDR.dds` | `SampleDiffuseHDR.dds` | 1,966,208 bytes | `76556B8348097DB86136FB44A5DB1CB306E730FDAF80B08B73637F0843FD970B` |
| `Assets/Textures/Cubemaps/HDRI/OutdoorSpecularHDR.dds` | `SampleSpecularHDR.dds` | 33,554,624 bytes | `CC7A7EFE133C87EDA754342648A6A17AEC3C5CA8397648CA473A7549FD7BD7D5` |
| `Assets/Textures/PBR/Bricks075A_4K-PNG/Bricks075A_4K_Color.png` | `Bricks075A_1K-PNG/Bricks075A_1K-PNG_Color.png` | 1,095,119 bytes | `F639C0BE30C4675E57B2A2BB705D1755EFB04DE7B2F8BF7997E192E605C751FB` |

All replacement assets are private archive material and require license/source review before any public subset is prepared.

## Verification

- Static verification: 통과
- Debug x64 run: 성공
- Release x64 run: 성공

## Notes

- `.clang-format` project reference was removed because the file is not archived.
- Release x64 shader model settings were normalized to `5.0` for `CubeMappingPS`, `CubeMappingVS`, `NormalPS`, and `NormalVS`.
- Generated build output was removed after import.
