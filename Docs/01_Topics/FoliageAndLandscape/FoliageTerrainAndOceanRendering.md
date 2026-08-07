# Foliage Terrain And Ocean Rendering

## 목적

Foliage와 landscape scene은 같은 mesh를 반복 배치하고 wind parameter 또는 height field를 사용해 넓은 scene 변화를 만든다. 이 Topic은 tree와 grass instance, terrain mesh, animated ocean surface가 render scene을 구성하는 공통 방식을 설명한다.

## 책임 범위

- repeated foliage instance와 shared mesh/material 사용의 의미를 설명한다.
- wind-driven parameter update, terrain height field, ocean surface transform의 역할을 설명한다.
- asset import, grass placement 상수, terrain source data와 post-process 구현은 상세 Demo로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification/Part4_Chapter14-20`의 [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos/Part4_Chapter14-20`의 상세 Demo로 위임한다.

## 핵심 개념

### Instance Placement And Shared Resources

Foliage scene은 많은 object가 비슷한 geometry와 material을 공유하므로 per-instance transform과 variation data를 분리한다. `Ex1802_Grass`는 instance 목록을 만들고 GPU buffer를 갱신해 반복된 grass field를 render한다. shared resource는 draw submission과 memory 사용을 줄일 수 있지만 instance 수와 update frequency가 증가하면 buffer update 비용도 고려한다.

### Wind Driven Deformation

Wind는 branch, leaf, grass blade의 transform 또는 shader parameter에 time-varying offset을 적용하는 visual control이다. wind strength가 바뀌어도 scene geometry의 ownership은 유지되며 simulation 정확도보다 반복 foliage의 motion cue를 만드는 데 초점을 둔다.

### Terrain Height Field And Ocean Surface

Terrain은 height field 또는 imported mesh에서 surface topology를 만들고 world transform으로 scene에 배치한다. ocean은 terrain과 별도의 surface model로 두어 height와 transform parameter를 갱신할 수 있다. `Ex1803_Landscape`는 terrain mesh와 `OceanModel`을 함께 사용하므로 terrain elevation과 ocean animation을 한 resource로 혼동하지 않는다.

## 한계

- vegetation scattering, LOD, culling, shadowing과 biome generation을 다루지 않는다.
- terrain source data와 foliage runtime asset은 직접 게시 대상으로 다루지 않는다.
- storyboard는 rendered scene evidence이며 wind model이나 ocean model의 물리적 정확도를 보장하지 않는다.

## 관련 문서

- [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md)
- [Chapter18 Tree Demo](../../03_Demos/Part4_Chapter14-20/18_01_Tree.md)
- [Chapter18 Grass Demo](../../03_Demos/Part4_Chapter14-20/18_02_Grass.md)
- [Chapter18 Landscape Demo](../../03_Demos/Part4_Chapter14-20/18_03_Landscape.md)
- [Part4 Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)