# 11_TexturingTechniques_Step4_HDRI

## Chapter Focus

이 예제는 HDRI/EXR texture를 DirectX texture로 읽어 shader resource로 사용하는 흐름을 확인하는 단계입니다.

핵심은 `D3D11Utils::CreateTexture()`가 `.exr` 확장자를 감지하면 `DirectXTexEXR` 기반의 `LoadFromEXRFile()` 경로를 사용하고, 일반 LDR image와 다른 floating-point texture format을 다루는 것입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step4_HDRI`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step4_HDRI`
- OriginalExamples도 같은 `OutdoorHDRI024_4K-HDR.exr` 경로를 참조합니다.
- raw repo 안에서는 해당 EXR asset을 찾지 못했습니다. 따라서 build는 가능할 수 있으나, 실행 시 texture loading 실패 여부를 별도로 확인해야 합니다.
- 원본 코드 경로를 임의로 다른 DDS cubemap asset으로 바꾸지 않았습니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

새로 추가한 asset은 없습니다.

주의:

- 코드 참조: `Assets/Textures/Cubemaps/HDRI/OutdoorHDRI024_4K-HDR.exr`
- raw asset 상태: 현재 raw repo에서 파일 미발견
- 실행 확인 시 EXR 파일 누락으로 실패하면 raw asset 출처/대체 기준을 먼저 확인해야 합니다.

## Verification

- Static verification: 통과
- Debug x64 run: 미확인
- Release x64 run: 미확인
