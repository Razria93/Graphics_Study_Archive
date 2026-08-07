# Chapter18 Ex1802 Grass

## Overview

`Ex1802_Grass`는 seeded random transform과 wind strength를 담은 100000개 grass instance를 GPU buffer로 upload하고 instanced draw와 vertex shader deformation으로 grass field를 그리는 예제다. `Examples.exe 1802`는 foliage, PBR texture와 HDRI runtime asset을 필요로 하며 rendered storyboard만 evidence로 사용한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1802`
- Working directory: `Part4_Chapter14-20` source root
- Runtime assets: foliage, PBR texture와 HDRI files
- 주요 source: `Ex1802_Grass.cpp`, `GrassModel.h`
- Shader: `Ex1802_GrassVS.hlsl`, `Ex1802_GrassPS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L95) | command argument `1802`를 `Ex1802_Grass` instance에 연결 |
| [Ex1802_Grass.cpp](../Ex1802_Grass.cpp#L54) | seeded random transform을 가진 100000개 instance를 생성 |
| [Ex1802_Grass.cpp](../Ex1802_Grass.cpp#L109) | UI wind 값을 각 instance buffer에 반영 |
| [GrassModel.h](../GrassModel.h#L54) | blade와 instance buffer를 bind하고 instanced draw를 수행 |
| [Ex1802_GrassVS.hlsl](../Ex1802_GrassVS.hlsl#L101) | `globalTime`과 wind strength로 blade deformation을 계산 |

## Capture/Result

![Chapter18 Grass storyboard](../../Docs/_assets/captures/part4_chapter18_02_grass.png)

대표 storyboard는 time-varying wind deformation이 적용된 instanced grass field를 보여 준다. timestamp와 asset provenance는 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | rendered evidence만 사용 |

## Limitations

- wind strength는 모든 instance에 공통 값으로 upload하며 spatial wind field나 per-instance phase offset을 구현하지 않는다.
- blade deformation은 procedural vertex rotation이며 collision 또는 foliage physics를 수행하지 않는다.

## Related Docs

- [Foliage Terrain And Ocean Rendering](../../Docs/01_Topics/FoliageAndLandscape/FoliageTerrainAndOceanRendering.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter18 Ex1802 Grass Demo](../../Docs/03_Demos/Part4_Chapter14-20/18_02_Grass.md)