# Part2 Chapter06 DirectX11 Graphics Pipeline Demo

## 요약

Chapter06은 COM 기반 resource ownership에서 시작해 swap chain과 첫 graphics frame, shader·texture·lighting, viewport와 window resize까지 DirectX11 pipeline을 단계적으로 확장한다. 세 결과는 pipeline 기준선, Spot Light의 cone 집중과 resize-dependent resource 재생성이라는 서로 다른 구현 축을 보여준다.

## 결과

### Step2 — First Direct3D Frame

Device·context, swap chain, render target, depth buffer와 viewport를 연결하고 indexed cube를 그린 첫 end-to-end graphics frame이다.

![Step2 Initializing D3D](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter06_02_initializing_d3d.png?raw=true)

### Step6 — Spot Light Cone

Point Light와 같은 위치·감쇠 조건에 spot cone factor를 추가해 illumination이 한 방향으로 응축되는 결과다. Directional·Point·Spot 전체 비교는 상세 Demo에서 확인한다.

![Step6 Spot Light](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter06_06_lighting_spot.png?raw=true)

### Step8 — Wide Window Resize

넓어진 client area에 맞춰 swap chain dependent resource와 projection aspect를 갱신한 결과다. Geometry 비율과 scene viewport를 유지하면서 UI와 render 영역이 확장된다.

![Step8 Wide Resize](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Docs/_assets/captures/part2_chapter06_08_resizing_window_wide.png?raw=true)

## 핵심 구현

### Device resource에서 indexed draw까지

Window 생성 뒤 device·context와 swap chain을 연결하고 back buffer, depth resource와 viewport를 만든다. Cube resource와 shader를 pipeline에 binding한 뒤 indexed draw로 첫 frame을 출력한다.

- [Swap chain·render target·depth 초기화](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/AppBase.cpp#L253-L382)
- [Scene pipeline binding과 indexed draw](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/ExampleApp.cpp#L206-L245)

### Light type별 shading

공통 material과 Blinn-Phong 항을 유지하고 Light type에 따라 surface-to-light 방향, distance attenuation과 spot cone factor를 선택한다. Spot branch는 방향 정렬에 따른 cone 집중을 최종 밝기에 반영한다.

- [Directional·Point·Spot Light 공통 계약](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L24-L120)
- [Light 누적과 texture 결합](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/BasicPixelShader.hlsl#L14-L36)

### Resize-dependent resource lifetime

Client size가 바뀌면 기존 render target과 depth resource를 해제하고 새 back buffer 크기로 재생성한다. Minimize 상태는 유효한 크기가 돌아올 때까지 건너뛰며 viewport와 projection aspect도 새 scene 영역에 맞춘다.

- [최소화와 client size 처리](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/AppBase.cpp#L132-L151)
- [Resize dependent resource 재생성](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/AppBase.cpp#L486-L518)
- [Projection aspect 갱신](https://github.com/Razria93/Graphics_Study_Archive/blob/e21200073e8c2cab2938b64f1deb4519c13ef185/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/ExampleApp.cpp#L223-L234)

## 처리 흐름

1. COM interface ownership과 D3D11 device·context를 준비한다.
2. Swap chain, render target, depth buffer와 viewport를 연결한다.
3. Model·View·Projection과 shader·texture resource를 pipeline에 binding한다.
4. Light type에 맞는 shading 결과를 계산한다.
5. Window size 변경 시 dependent resource와 projection을 갱신한다.
6. Indexed scene과 ImGui를 합성하고 frame을 present한다.

## 구현 범위와 한계

- 포함: DirectX11 초기화, MVP, shader·texture, Directional·Point·Spot lighting, viewport와 window resize
- 한계: 단일 Light와 선형 distance attenuation을 사용하며 PBR, shadow와 HDR pipeline은 포함하지 않는다.
- 한계: Resize interaction video는 후속 개선이며 현재 결과는 Compact·Default·Wide screenshot으로 검증한다.

## 검증

- Build/Run: Chapter06 Step1–9 Debug/Release x64 성공
- Capture/Result: graphics Example 전체 screenshot 확보, Step7–9 사용자 시각 확인 완료
- Resize: 반복 resize와 minimize/restore 후 geometry 비율과 resource 상태 확인

## 더 자세히 보기

### Chapter 안내

- [Part2 Chapter05-08 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/README.md)
- [Chapter05-08 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
- [Chapter05-08 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/02_Verification/Part2_Chapter05-08/verification-index.md)

### 대표 구현

- Step2 InitializingD3D: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/06_InitializingD3D.md)
- Step6 Lighting: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/06_Lighting.md)
- Step8 ResizingWindow: [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/README.md) · [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/08_ResizingWindow.md)

### 선택 Demo

- [Step9 PhongVsBlinnPhong 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/03_Demos/Part2_Chapter05-08/09_PhongVsBlinnPhong.md)

### 관련 개념

- [DirectX11 Pipeline Topics](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/DirectX11Pipeline/README.md)
- [Light Types](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part2-chapter05-08-workflow/Docs/01_Topics/LightingAndShading/LightTypes.md)
