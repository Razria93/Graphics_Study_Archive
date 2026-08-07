# Chapter18 Ex1803 Landscape

## Overview

`Ex1803_Landscape`는 raw heightmap을 fixed grid terrain mesh로 변환하고, procedural ocean model을 같은 scene에 렌더링하는 예제다. `Examples.exe 1803`은 `terrain.raw`, material texture와 HDRI runtime asset을 필요로 하며 rendered storyboard만 evidence로 사용한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1803`
- Working directory: `Part4_Chapter14-20` source root
- Runtime assets: `Assets/Textures/terrain.raw`, terrain material texture와 HDRI files
- 주요 source: `Ex1803_Landscape.cpp`, `OceanModel.h`
- Shader: `Ex1803_OceanPS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L98) | command argument `1803`을 `Ex1803_Landscape` instance에 연결 |
| [Ex1803_Landscape.cpp](../Ex1803_Landscape.cpp#L23) | raw heightmap을 fixed grid vertex, normal과 index로 변환 |
| [Ex1803_Landscape.cpp](../Ex1803_Landscape.cpp#L121) | terrain model과 ocean model을 scene에 구성 |
| [Ex1803_Landscape.cpp](../Ex1803_Landscape.cpp#L160) | `OceanHeight` UI로 ocean world transform을 갱신 |
| [Ex1803_OceanPS.hlsl](../Ex1803_OceanPS.hlsl#L25) | time-varying wave와 ocean surface shading을 계산 |

## Capture/Result

![Chapter18 Landscape storyboard](../../Docs/_assets/captures/part4_chapter18_03_landscape.png)

대표 storyboard는 fixed terrain과 animated ocean surface가 함께 그려진 결과다. timestamp, asset provenance와 motion 해석은 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | rendered evidence만 사용 |

## Limitations

- terrain은 fixed resolution heightmap grid이며 streaming, LOD 또는 runtime terrain editing을 구현하지 않는다.
- ocean은 procedural shader surface이며 physical fluid simulation이나 terrain-water interaction을 계산하지 않는다.

## Related Docs

- [Foliage Terrain And Ocean Rendering](../../Docs/01_Topics/FoliageAndLandscape/FoliageTerrainAndOceanRendering.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter18 Ex1803 Landscape Demo](../../Docs/03_Demos/Part4_Chapter14-20/18_03_Landscape.md)