# Ex1402 Blur Status

## Summary

| Item | Status | Note |
| --- | --- | --- |
| Source/project import | 완료 | 단일 `Examples` project 구조 기준으로 반영 |
| Required asset | 없음 | staging texture를 코드에서 생성 |
| Build/run | 미확인 | 사용자 Debug/Release 실행 확인 전 |
| Diff review | 진행 중 | `Part4_HongLabGraphics` main raw를 기준으로 사용 |
| Refactor | 미확인 | 1차 import에서는 raw 구조 유지 |
| Capture ready | 아니오 | build/run 확인 후 판단 |
| Public readiness | 검토 필요 | 강의 기반 학습 예제. public subset 전 별도 검토 |

## Raw Reference

- Primary source: `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`
- Reference-only:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2\Examples`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics\Examples`

## Imported Files

`Ex1402_Blur` 핵심 파일:

- `Ex1402_Blur.cpp`
- `Ex1402_Blur.h`
- `Ex1402_BlurXCS.hlsl`
- `Ex1402_BlurYCS.hlsl`
- `Ex1402_BlurXGroupCacheCS.hlsl`
- `Ex1402_BlurYGroupCacheCS.hlsl`
- `Ex1402_BlurXPS.hlsl`
- `Ex1402_BlurYPS.hlsl`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

## Static Checks

- Command argument: `1402`
- Required runtime asset: 없음
- Shader settings:
  - `Ex1402_BlurXCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1402_BlurYCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1402_BlurXGroupCacheCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1402_BlurYGroupCacheCS.hlsl`: Debug/Release x64 모두 Compute, shader model `5.0`
  - `Ex1402_BlurXPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
  - `Ex1402_BlurYPS.hlsl`: Debug/Release x64 모두 Pixel, shader model `5.0`
- Archive files match primary raw hash for all `Ex1402` core files checked.
- `Ex1402_Blur.cpp`, `Ex1402_Blur.h`, `Ex1402_BlurXCS.hlsl`, `Ex1402_BlurXGroupCacheCS.hlsl`, `Ex1402_BlurXPS.hlsl` differ from `_2`/`OriginalExamples`; archive 기준은 primary raw입니다.

## Build / Run

미확인.

실행 command argument:

```text
1402
```

확인 예정:

- Debug x64 build/run
- Release x64 build/run
- blur 결과가 back buffer에 표시되는지 확인

## Notes

- 현재 활성 경로는 `ComputeShaderBlur(false)`입니다.
- `Render()`에서 blur를 1000회 반복하므로 실행 환경에 따라 초기 응답이나 frame time이 무겁게 보일 수 있습니다.
- `m_useMSAA = false`는 compute shader가 사용하는 UAV/render texture 흐름과 맞추기 위한 설정입니다.
- `ComputeShaderBarrier()`가 X/Y pass 사이에서 SRV/UAV binding 충돌을 방지합니다.
- source 내부 장문 주석 정리는 2차 documentation/source cleanup 단계에서 진행합니다.
