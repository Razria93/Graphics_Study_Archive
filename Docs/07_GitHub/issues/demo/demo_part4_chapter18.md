# Part4 Chapter18 Foliage And Landscape Demo

## 요약

Chapter18은 foliage mesh wind deformation, instanced grass field와 heightmap terrain plus procedural ocean rendering을 묶은 environment rendering evidence다. 대표 visual은 `Ex1801`부터 `Ex1803`까지 각 시연 video에서 선택한 timestamp frame 3개를 배치한 storyboard로 구성한다. foliage, terrain, texture와 HDRI 원본 asset은 직접 게시하지 않고 rendered storyboard만 사용한다.

## 핵심 목표

- Imported foliage mesh group을 trunk/branch와 leaves로 분리하고 wind parameter 적용
- 100,000개 grass instance와 per-frame wind strength buffer update 기록
- Raw heightmap terrain, normal generation과 procedural ocean shader display 연결

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | 없음 | 단일 screenshot 대신 timestamp storyboard 3개를 사용함 |
| Result image | Chapter18 storyboard 3장 | `Ex1801`부터 `Ex1803`까지 timestamp frame 3개를 배치한 rendered evidence |
| Video | 없음 | GitHub attachment URL을 아직 게시하지 않음 |

## 시각 정보

### Tree wind deformation

`Ex1801_Tree`는 imported foliage mesh를 leaves와 trunk/branches group으로 분리하고, `windTrunk`, `windLeaves`, `globalTime`을 vertex shader deformation에 연결한다. Storyboard는 1.140s, 3.800s, 6.460s frame을 순서대로 기록한다.

![Tree wind deformation](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter18_01_tree.png?raw=true)

### Instanced grass wind phase

`Ex1802_Grass`는 100,000개 grass instance를 instance buffer로 그리며, `globalTime`과 wind strength로 tip 쪽 deformation이 커지는 blade rotation을 계산한다. Storyboard는 1.190s, 3.967s, 6.743s frame을 순서대로 기록한다.

![Instanced grass wind phase](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter18_02_grass.png?raw=true)

### Terrain and procedural ocean

`Ex1803_Landscape`는 raw heightmap에서 terrain mesh와 normal을 생성하고, procedural ocean pixel shader를 같은 scene에 렌더링한다. Storyboard는 1.140s, 3.800s, 6.460s frame을 순서대로 기록한다.

![Terrain and procedural ocean](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter18_03_landscape.png?raw=true)

## 구현 하이라이트

### Foliage mesh group and wind parameters

`Ex1801`은 foliage FBX mesh를 leaves group과 trunk/branches group으로 나누고, 각 model의 mesh constant에 trunk wind와 leaf wind parameter를 설정한다. Wind deformation은 vertex shader procedural transform이며 branch physics 또는 leaf collision을 계산하지 않는다.

- [Foliage mesh group 분리와 wind parameter 설정](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1801_Tree.cpp#L58-L78)
- [Trunk rotation과 leaf displacement shader path](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/BasicVS.hlsl#L68-L103)

### Grass instancing and shader deformation

`Ex1802`는 seeded random distribution으로 grass instance transform을 만들고, blade vertex buffer와 instance buffer를 함께 input assembler에 연결한다. 매 frame UI wind value를 모든 instance의 wind strength에 반영한 뒤 `DrawIndexedInstanced`를 호출한다.

- [100,000개 grass instance 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1802_Grass.cpp#L54-L100)
- [Instance buffer binding과 instanced draw](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/GrassModel.h#L54-L82)
- [Time-based wind deformation](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1802_GrassVS.hlsl#L101-L117)

### Heightmap terrain and ocean shader

`Ex1803`은 `terrain.raw` sample을 fixed grid terrain으로 downsample하고, 이웃 height 차에서 normal을 만든다. Ocean path는 procedural pixel shader ray march이며 physical fluid simulation 또는 terrain-water interaction을 계산하지 않는다.

- [Heightmap sample, terrain vertex와 index 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1803_Landscape.cpp#L23-L112)
- [Time-varying ocean wave와 Fresnel composition](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1803_OceanPS.hlsl#L25-L151)

### 처리 흐름

1. `Examples.exe` command argument `1801`, `1802`, `1803`으로 Chapter18 예제를 선택한다.
2. Tree path는 foliage mesh group과 wind parameter를 standard model render path에 연결한다.
3. Grass path는 blade geometry와 instance buffer를 결합해 large field를 instanced draw로 렌더링한다.
4. Landscape path는 raw heightmap terrain과 procedural ocean surface를 같은 scene에 배치한다.
5. 시연 video에서 선택한 timestamp frame 3개를 01부터 03까지 순서와 함께 storyboard로 기록한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void RenderEnvironmentPseudo(float globalTime)
{
	UpdateTreeWindConstants(globalTime, windTrunk, windLeaves);
	UpdateGrassInstanceWindBuffer(windStrength);
	GenerateOrReuseTerrainFromHeightmap();

	RenderFoliageMeshesWithWindShader();
	DrawIndexedInstancedGrassField();
	RenderTerrainAndProceduralOcean(globalTime);
}
```

원본 코드: [Terrain 및 ocean scene 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1803_Landscape.cpp#L121-L168)

## 검증 상태

- `Part4_Chapter14-20/Examples.sln` Debug x64 build/run/capture smoke 성공
- `Part4_Chapter14-20/Examples.sln` Release x64 build/run/capture smoke 성공
- `Ex1801`부터 `Ex1803`까지 storyboard PNG는 timestamp frame, full decode와 text metadata chunk 부재를 확인함

## 구현 범위와 한계

- Tree와 grass wind는 shader deformation이며 physics simulation 또는 collision을 계산하지 않는다.
- Terrain은 raw heightmap fixed resolution grid이며 runtime terrain streaming이나 LOD를 구현하지 않는다.
- Ocean은 procedural pixel shader ray march이며 physical fluid simulation이 아니다.
- Foliage, terrain, texture와 HDRI 원본 asset은 첨부하거나 직접 링크하지 않는다.
- 원본 MP4와 raw preview는 Git에 추가하지 않는다.

## 관련 문서

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex1801 Tree 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/18_01_Tree.md)
- [Ex1802 Grass 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/18_02_Grass.md)
- [Ex1803 Landscape 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/18_03_Landscape.md)
- [Chapter18 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Foliage Terrain And Ocean Rendering Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/FoliageAndLandscape/FoliageTerrainAndOceanRendering.md)