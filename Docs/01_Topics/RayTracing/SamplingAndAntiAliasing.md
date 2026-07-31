# Sampling And Anti Aliasing

## 목적

Raster pixel 하나를 한 지점의 값으로만 평가할 때 생기는 spatial aliasing과, pixel 영역 안의 여러 sample을 결합해 coverage와 signal 변화를 더 안정적으로 추정하는 supersampling의 기본 원리를 설명한다.

## 책임 범위

- Spatial aliasing, subpixel sample, sample pattern과 평균의 일반 개념을 다룬다.
- Step11의 재귀 함수, scene과 DirectX11 표시 경로는 [Step11 Example README](../../../Part1_Chapter03/03_Raytracing_Step11_Supersampling/README.md)와 [상세 Demo](../../03_Demos/Part1_Chapter03/11_Supersampling.md)로 위임한다.
- 실제 build/run/capture 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 핵심 개념

### Spatial aliasing

연속적인 geometry silhouette, texture와 shading signal을 유한한 pixel grid로 기록하면 pixel보다 빠르게 변하는 정보가 잘못된 계단이나 반복 pattern으로 나타날 수 있다. 한 pixel을 한 지점에서만 평가하면 작은 위치 변화가 hit와 miss 또는 서로 다른 surface sample 사이를 크게 오갈 수 있다.

### Pixel 영역과 subpixel sample

Pixel은 점이 아니라 화면의 일정 영역을 대표한다. Supersampling은 이 영역 안에서 여러 위치를 평가하고 결과를 결합해 pixel의 대표값을 구한다. Geometry 경계에서는 일부 sample이 object를 hit하고 나머지가 background를 hit하므로 평균 color가 coverage를 근사한다.

### Sample pattern과 reconstruction

규칙 grid는 구현과 재현이 쉽지만 scene의 반복 주기와 정렬되면 structured aliasing을 남길 수 있다. Jittered 또는 stratified pattern은 정렬 artifact를 분산할 수 있으며, sample을 결합하는 box, tent와 같은 reconstruction filter도 결과의 sharpness와 stability에 영향을 준다.

### 품질과 비용

한 축의 sample 수를 두 배로 늘리면 2D pixel당 sample 수는 네 배가 된다. Ray tracing에서는 각 sample이 intersection, shading과 texture lookup을 다시 수행하므로 sample 수가 계산 비용과 거의 직접 연결된다. Adaptive sampling은 변화가 큰 영역에 sample을 집중하지만 별도 오차 추정과 종료 조건이 필요하다.

### Supersampling과 MSAA

Full-scene supersampling은 각 subpixel에서 shader와 texture 결과까지 다시 평가한다. MSAA는 rasterization coverage를 여러 위치에서 평가하면서 일부 shading 계산을 공유하는 방식이므로 비용과 적용 범위가 다르다. CPU ray tracer의 여러 primary ray 평균은 DirectX11 swap-chain MSAA 설정과 독립된 spatial sampling이다.

## 한계

- 이 문서는 temporal aliasing과 motion blur sampling을 다루지 않는다.
- 특정 sample pattern이 모든 scene에서 최적이라고 가정하지 않는다.
- Step11 구현은 규칙적인 8×8 sample과 box average 사례이며 일반적인 adaptive 또는 stochastic sampling을 대표하지 않는다.

## 관련 문서

- Example: [Step11 Supersampling README](../../../Part1_Chapter03/03_Raytracing_Step11_Supersampling/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/11_Supersampling.md`](../../03_Demos/Part1_Chapter03/11_Supersampling.md)
- Related Topic: [Ray](Ray.md)
- Related Topic: [Intersection](Intersection.md)
- Related Topic: [Texture Sampling](../TexturingAndMapping/TextureSampling.md)
