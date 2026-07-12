# 12_PBR_Step2_PBRModels

## Chapter Focus

이 예제는 Unreal-style PBR shader workflow를 procedural mesh가 아니라 외부 model asset에 적용하는 단계입니다.

핵심은 `GeometryGenerator::ReadFromFile()`로 FBX model을 읽고, model mesh에 albedo, emissive, metallic, normal, roughness texture 경로를 직접 연결한 뒤 HDRI 기반 IBL과 PBR material controls를 함께 확인하는 흐름입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\12_PBR_Step2_PBRModels`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\12_PBR_Step2_PBRModels`
- Primary raw의 solution/project/source를 기준으로 import했습니다.
- HDRI DDS runtime assets는 `12_PBR_Step1_UnrealPBR`에서 이미 archive 공용 asset으로 포함되어 있어 재추가하지 않았습니다.
- raw의 `.vs/`, `x64/`, generated project output, `.vcxproj.user`, `.clang-format`, `imgui.ini`는 제외했습니다.
- 장문 학습 주석과 문서 정리는 2차 문서 정리 단계에서 별도로 처리합니다.

## Runtime Assets

Reused from previous archive imports:

- `Assets/Textures/Cubemaps/HDRI/SampleEnvHDR.dds`
- `Assets/Textures/Cubemaps/HDRI/SampleSpecularHDR.dds`
- `Assets/Textures/Cubemaps/HDRI/SampleDiffuseHDR.dds`
- `Assets/Textures/Cubemaps/HDRI/SampleBrdf.dds`

Referenced but currently missing in raw/archive:

- `Assets/Characters/armored-female-future-soldier/angel_armor.fbx`
- `Assets/Characters/armored-female-future-soldier/angel_armor_albedo.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_e.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_metalness.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_normal.jpg`
- `Assets/Characters/armored-female-future-soldier/angel_armor_roughness.jpg`

The missing character asset is not present in `C:\ComputerGraphics` at the time of import. It must be supplied or the example path must be intentionally changed before runtime verification.

## Verification

- Static verification: 통과
- Debug x64 run: 미확인
- Release x64 run: 미확인

## Notes

- `.clang-format` project reference was removed because the file is not archived.
- Release x64 shader model settings were normalized to `5.0` for `CubeMappingPS`, `CubeMappingVS`, `NormalPS`, and `NormalVS`.
- The code currently keeps the raw `armored-female-future-soldier` path unchanged. No fallback model path was introduced in this import.
