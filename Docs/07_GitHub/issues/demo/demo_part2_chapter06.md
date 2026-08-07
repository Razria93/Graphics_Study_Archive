# Part2 Chapter06 DirectX11 Graphics Pipeline Demo

## 요약

Chapter06은 COM 기반 resource ownership에서 시작한다.

DirectX11 pipeline은 swap chain, 첫 graphics frame, shader, texture와 lighting으로 확장된다.

후반 흐름은 viewport와 window resize 처리까지 이어진다.

세 결과는 pipeline 기준선, Spot Light cone 집중, resize-dependent resource 재생성을 보여준다.

## 핵심 목표

- DirectX11 device·context와 swap chain 기반의 첫 graphics frame 구성
- Directional·Point·Spot Light의 공통 shading과 spot cone factor 비교
- Window resize에 따른 dependent resource와 projection aspect 갱신

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | Step2·Step6·Step8 screenshot | 아래 시각 정보에서 pipeline 결과를 확인함 |
| Result image | Step2·Step6·Step8 rendered result | frame, spot cone, wide resize 결과를 기록함 |
| Video | 없음 | 정적 screenshot으로 구현 축을 비교함 |

## 시각 정보

### Step2 — First Direct3D Frame

Device, context, swap chain, render target, depth buffer와 viewport를 연결한다.

Indexed cube를 그린 첫 end-to-end graphics frame이다.

![Step2 Initializing D3D](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter06_02_initializing_d3d.png?raw=true)

### Step6 — Spot Light Cone

Point Light와 같은 위치, 감쇠 조건에 spot cone factor를 추가한 결과다.

Illumination이 한 방향으로 응축되는 차이를 확인한다.

Directional, Point, Spot 전체 비교는 상세 Demo에서 확인한다.

![Step6 Spot Light](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter06_06_lighting_spot.png?raw=true)

### Step8 — Wide Window Resize

넓어진 client area에 맞춰 swap chain dependent resource를 갱신한 결과다.

Projection aspect도 새 크기에 맞춰 갱신한다.

Geometry 비율과 scene viewport를 유지하면서 UI와 render 영역이 확장된다.

![Step8 Wide Resize](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter06_08_resizing_window_wide.png?raw=true)

## 구현 하이라이트

### Device resource에서 indexed draw까지

Window 생성 뒤 device, context와 swap chain을 연결한다.

Back buffer, depth resource와 viewport를 만든다.

Cube resource와 shader를 pipeline에 binding한다.

Indexed draw로 첫 frame을 출력한다.

- [Swap chain·render target·depth 초기화](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/AppBase.cpp#L253-L382)
- [Scene pipeline binding과 indexed draw](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/ExampleApp.cpp#L206-L245)

### Light type별 shading

공통 material과 Blinn-Phong 항을 유지한다.

Light type에 따라 surface-to-light 방향과 distance attenuation을 선택한다.

Spot branch는 spot cone factor와 방향 정렬을 최종 밝기에 반영한다.

- [Directional·Point·Spot Light 공통 계약](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L24-L120)
- [Light 누적과 texture 결합](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/BasicPixelShader.hlsl#L14-L36)

### Resize-dependent resource lifetime

Client size가 바뀌면 기존 render target과 depth resource를 해제한다.

새 back buffer 크기로 dependent resource를 재생성한다.

Minimize 상태는 유효한 크기가 돌아올 때까지 건너뛴다.

Viewport와 projection aspect도 새 scene 영역에 맞춘다.

- [최소화와 client size 처리](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/AppBase.cpp#L132-L151)
- [Resize dependent resource 재생성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/AppBase.cpp#L486-L518)
- [Projection aspect 갱신](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/ExampleApp.cpp#L223-L234)

### 처리 흐름

1. COM interface ownership과 D3D11 device·context를 준비한다.
2. Swap chain, render target, depth buffer와 viewport를 연결한다.
3. Model·View·Projection과 shader·texture resource를 pipeline에 binding한다.
4. Light type에 맞는 shading 결과를 계산한다.
5. Window size 변경 시 dependent resource와 projection을 갱신한다.
6. Indexed scene과 ImGui를 합성하고 frame을 present한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void RenderResizeAwareFramePseudo(Size clientSize)
{
	if (clientSize.IsEmpty()) {
		return;
	}

	if (clientSize != renderTargetSize) {
		RecreateDependentResources(clientSize);
		UpdateProjectionAspect(clientSize);
	}

	for (Light light : lights) {
		AccumulateBlinnPhong(light);
	}

	DrawIndexedScene();
	PresentFrame();
}
```

원본 코드: [Resize dependent resource 재생성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/AppBase.cpp#L486-L518)

## 검증 상태

- Build/Run: Chapter06 Step1–9 Debug/Release x64 성공
- Capture/Result: graphics Example 전체 screenshot 확보, Step7–9 사용자 시각 확인 완료
- Resize: 반복 resize와 minimize/restore 후 geometry 비율과 resource 상태 확인

## 구현 범위와 한계

- 포함: DirectX11 초기화, MVP, shader·texture, Directional·Point·Spot lighting, viewport와 window resize
- 한계: 단일 Light와 선형 distance attenuation을 사용하며 PBR, shadow와 HDR pipeline은 포함하지 않는다.
- 한계: 현재 resize 결과는 Compact·Default·Wide screenshot과 반복 resize로 검증한다.

## 관련 문서

### Chapter 안내

- [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Part2_Chapter05-08/README.md)
- [Chapter05-08 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
- [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### 대표 구현

- Step2 InitializingD3D: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)
- Step6 Lighting: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/06_Lighting.md)
- Step8 ResizingWindow: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/08_ResizingWindow.md)

### 선택 Demo

- [Step9 PhongVsBlinnPhong 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/09_PhongVsBlinnPhong.md)

### 관련 개념

- [DirectX11 Pipeline Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/01_Topics/DirectX11Pipeline/README.md)
- [Light Types](https://github.com/Razria93/Graphics_Study_Archive/blob/main/Docs/01_Topics/LightingAndShading/LightTypes.md)
