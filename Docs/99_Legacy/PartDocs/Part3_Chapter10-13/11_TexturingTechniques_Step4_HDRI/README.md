# 11_TexturingTechniques_Step4_HDRI

## Chapter Focus

이 예제는 HDRI/EXR texture를 DirectX texture로 읽어 shader resource로 사용하는 흐름을 확인하는 단계입니다.

핵심은 `D3D11Utils::CreateTexture()`가 `.exr` 확장자를 감지하면 `DirectXTexEXR` 기반 `LoadFromEXRFile()` 경로를 사용하고, 일반 LDR image와 다른 floating-point texture format을 유지한다는 점입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step4_HDRI`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step4_HDRI`
- OriginalExamples도 같은 `OutdoorHDRI024_4K-HDR.exr` 경로를 참조합니다.
- raw repo 안에서는 해당 EXR asset을 찾지 못했습니다.
- 코드 경로는 바꾸지 않고, replacement HDRI asset을 expected filename으로 배치했습니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

Step4 실행 확인을 위해 replacement EXR asset을 추가했습니다.

| Item | Value |
| --- | --- |
| Source file | `DaySkyHDRI015A_1K/DaySkyHDRI015A_1K_HDR.exr` |
| Archive path | `Part3_Chapter10-13/Assets/Textures/Cubemaps/HDRI/OutdoorHDRI024_4K-HDR.exr` |
| Size | 1,857,902 bytes |
| SHA256 | `214A51568B3D9F00C2582B3156F3B00AA43409BC1EAF4BBA06019D4E3964E712` |
| Public readiness | 검토 필요 |

임시 source folder `DaySkyHDRI015A_1K/`는 archive에 섞이지 않도록 제거했고, 실행에 필요한 EXR만 선별 반영했습니다.

## Verification

- Static verification: 통과
- Debug x64 run: 성공
- Release x64 run: 성공

## Previous Debug Failure

replacement EXR을 추가하기 전에는 Debug 실행에서 `can't dereference value-initialized vector iterator` assertion이 발생했습니다.

- 추정 원인: `ReadEXRImage()`에서 `LoadFromEXRFile()` 실패 후 빈 pixel buffer를 처리
- raw 비교: archive와 raw 코드 구조는 동일하며, raw에도 참조 EXR asset은 없음
- 현재 조치: expected filename으로 replacement EXR을 추가한 뒤 사용자 Debug/Release 실행 확인 완료
