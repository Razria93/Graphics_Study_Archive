# Part2 Chapter07 Procedural Modeling Demo

## 요약

Chapter07은 indexed box와 wireframe rasterizer state에서 시작한다.

흐름은 procedural primitive, subdivision과 spherical texture mapping으로 확장한다.

Step1, Step5와 Step8은 mesh 표현 기준선, Sphere topology, planet texture milestone이다.

마지막 milestone은 spherical UV와 seam 보정을 함께 보여준다.

## 핵심 목표

- Indexed triangle mesh와 wireframe state로 surface topology 확인
- Hemisphere ring과 pole fan으로 procedural Sphere topology 구성
- Subdivision, spherical UV와 triangle-local U seam 보정 적용

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | Step1·Step5·Step8 screenshot | 아래 시각 정보에서 topology와 mapping을 확인함 |
| Result image | Step1·Step5·Step8 rendered result | wireframe, Sphere, mapping 결과를 기록함 |
| Video | 없음 | 정적 screenshot으로 mesh 변화를 비교함 |

## 시각 정보

### Step1 — Wireframe Mesh

Triangle-list box의 fill mode만 wireframe으로 바꾼다.

Face별 triangle diagonal과 indexed surface topology를 확인한다.

![Step1 Wireframe](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter07_01_drawing_wireframes.png?raw=true)

### Step5 — Procedural Sphere

두 반구의 latitude ring을 equator에서 연결한다.

Pole fan으로 닫은 사용자 Sphere 구현이다.

Wireframe은 longitude slice가 pole로 수렴하는 topology를 드러낸다.

![Step5 Sphere](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter07_05_sphere.png?raw=true)

### Step8 — Sphere Mapping

Icosahedron을 세 번 subdivision하고 sphere에 투영한다.

Generated fictional planet texture는 spherical UV로 sampling한다.

비대칭 대륙과 극지방이 방향과 U seam 결과를 구분한다.

![Step8 Sphere Mapping](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter07_08_sphere_mapping.png?raw=true)

## 구현 하이라이트

### Indexed mesh와 wireframe state

Box는 triangle-list surface mesh를 유지한다.

Rasterizer fill mode만 wireframe으로 전환한다.

따라서 보이는 diagonal은 별도 line geometry가 아니다.

실제 triangle topology의 edge가 그대로 드러난다.

- [Box mesh 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/GeometryGenerator.cpp#L55-L188)
- [Fill mode 선택과 indexed draw](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/ExampleApp.cpp#L203-L231)

### Hemisphere와 pole topology

Sphere는 위와 아래 반구의 ring을 따로 만든다.

두 ring은 offset index로 연결한다.

Pole band에는 하나의 triangle만 생성한다.

이 방식은 중복된 면적 0 triangle을 피한다.

- [위쪽 반구 vertex와 triangle 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step5_Sphere/GeometryGenerator.cpp#L279-L371)
- [아래쪽 반구 vertex와 triangle 생성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step5_Sphere/GeometryGenerator.cpp#L377-L468)

### Subdivision과 spherical UV seam

Icosahedron triangle의 midpoint를 sphere에 다시 투영한다.

각 triangle은 네 child triangle로 나눈다.

U=0 또는 U=1 경계를 가로지르는 triangle은 outlier vertex를 복제한다.

복제는 triangle-local로 수행해 중앙을 가로지르는 잘못된 interpolation을 막는다.

- [Sphere projection과 spherical UV 계산](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/GeometryGenerator.cpp#L416-L445)
- [Triangle-local U seam 보정](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/GeometryGenerator.cpp#L448-L530)
- [반복 subdivision과 child triangle 구성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/GeometryGenerator.cpp#L532-L572)

### 처리 흐름

1. Vertex와 index로 triangle surface mesh를 구성한다.
2. Rasterizer state 또는 diagnostic line으로 topology와 normal을 확인한다.
3. Grid, Cylinder와 Sphere primitive를 procedural geometry로 확장한다.
4. Triangle midpoint를 sphere에 투영하며 subdivision을 반복한다.
5. Radial normal과 spherical UV를 계산하고 seam triangle을 보정한다.
6. Generated texture를 sampling해 mapped sphere를 표시한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void BuildMappedSpherePseudo(int subdivisionCount)
{
	if (subdivisionCount < 0) {
		return;
	}

	for (int level = 0; level < subdivisionCount; ++level) {
		SubdivideEachTriangle();
	}

	for (Triangle& triangle : triangles) {
		ProjectVerticesToSphere(triangle);
		if (CrossesUSeam(triangle)) {
			DuplicateTriangleLocalVertices(triangle);
		}
		CalculateSphericalUv(triangle);
	}

	DrawTexturedSphere();
}
```

원본 코드: [Triangle-local U seam 보정](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/GeometryGenerator.cpp#L448-L530)

## 검증 상태

- Build/Run: Chapter07 Step1–9 Debug/Release x64 성공
- Capture/Result: Step1–9 전체 application window screenshot 확보
- Asset: Step5는 검증된 generated wood, Step8은 공개 안전성을 확인한 generated fictional planet texture 사용

## 구현 범위와 한계

- 포함: indexed triangle mesh, wireframe, vertex normal과 face normal을 다룬다.
- 포함: Grid, Cylinder, Sphere, subdivision과 spherical UV를 다룬다.
- 한계: SphereMapping은 shared indexed mesh가 아닌 triangle-local vertex 구조를 사용한다.
- 한계: Spherical UV는 U seam을 보정하지만 별도의 pole correction과 tangent-space normal mapping은 포함하지 않는다.

## 관련 문서

### Chapter 안내

- [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/README.md)
- [Chapter05-08 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
- [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### 대표 구현

- Step1 DrawingWireFrames: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/07_01_DrawingWireFrames.md)
- Step5 Sphere: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/07_Modeling_Step5_Sphere/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/07_05_Sphere.md)
- Step8 SphereMapping: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/07_08_SphereMapping.md)

### 관련 개념

- [Modeling And Geometry Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/ModelingAndGeometry/README.md)
- [Spherical Texture Mapping](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/TexturingAndMapping/SphericalTextureMapping.md)
