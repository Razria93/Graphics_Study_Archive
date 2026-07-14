# 11_TexturingTechniques_Step3_HeightMapping

## Chapter Focus

이 예제는 height texture를 사용해 vertex shader 단계에서 표면 위치를 normal 방향으로 이동시키는 흐름을 확인하는 단계입니다.

핵심은 `useHeightMap` 옵션이 켜졌을 때 `g_heightTexture`에서 height 값을 읽고, `heightScale`과 world normal을 사용해 vertex position을 보정하는 것입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step3_HeightMapping`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step3_HeightMapping`
- Step2에서 값 전달만 확인되던 HeightMapping 경로가 이번 Step3에서 실제 위치 보정으로 연결됩니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

새로 추가한 asset은 없습니다. Step2에서 선별 포함한 PBR texture를 재사용합니다.

## Verification

- Static verification: 통과
- Debug x64 run: 성공
- Release x64 run: 성공
