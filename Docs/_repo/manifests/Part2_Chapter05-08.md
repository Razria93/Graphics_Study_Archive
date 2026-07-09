# Import Manifest: Part2 Chapter05-08

## Source / Target

- Source: `C:\ComputerGraphics\Part2_Chapter05-08`
- Target: `Part2_Chapter05-08`
- Scope: affine transformations, D3D11 graphics pipeline, modeling, shader toys
- Import status: 吏꾪뻾 以?- Public readiness: 寃???꾩슂
- Build/run status: Step1 Matrix(GLM), Step2 Lights(GLM), Step3 DirectXMath, Step4 Lights(SimpleMath), Pipeline Step1 COM, Pipeline Step2 InitializingD3D, Pipeline Step3 ModelViewProj, Pipeline Step4 Shaders, Pipeline Step5 Texturing ?깃났

## Step Inventory

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `05_AffineTransformations_Step1_Matrix(GLM)` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, GLM column-major matrix |
| `05_AffineTransformations_Step2_Lights(GLM)` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, GLM model/normal matrix |
| `05_AffineTransformations_Step3_DirectXMath` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, DirectXMath/SimpleMath |
| `05_AffineTransformations_Step4_Lights(SimpleMath)` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, SimpleMath lighting |
| `06_GraphicsPipeline_Step1_COM` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, D3D11 device creation, WRL ComPtr |
| `06_GraphicsPipeline_Step2_InitializingD3D` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, D3D11 initialization, swap chain, colored cube |
| `06_GraphicsPipeline_Step3_ModelViewProj` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, Model/View/Projection matrix and constant buffer |
| `06_GraphicsPipeline_Step4_Shaders` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, shader semantics and pixel shader constant buffer |
| `06_GraphicsPipeline_Step5_Texturing` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, texture sampling, `crate2_diffuse.png`, `wall.jpg` |
| `06_GraphicsPipeline_Step5_Texturing_LightingSelf` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, texture sampling with lighting, raw project filename? `06_GraphicsPipeline_Step5_Texturing.*` ?ъ궗??|
| `06_GraphicsPipeline_*` | ?덉젙 | 誘명솗??| 寃???꾩슂 | Step5 Texturing_LightingSelf ?댄썑 D3D11 pipeline |
| `07_Modeling_*` | ?덉젙 | 誘명솗??| 寃???꾩슂 | mesh generation/modeling |
| `08_ShaderToys_*` | ?덉젙 | 誘명솗??| 寃???꾩슂 | shader toy effects |

## Include Candidates

- `.sln`
- `.vcxproj`
- `.vcxproj.filters`
- `*.cpp`
- `*.h`
- `*.hlsl`
- ?ㅽ뻾???꾩닔??asset???덈뒗 寃쎌슦 蹂꾨룄 寃????諛섏쁺

## Exclude Patterns

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- `.clang-format` ?덉젣蹂??щ낯
- raw result/capture/video
- 媛뺤쓽 ?먮낯 ?곸긽, ?щ씪?대뱶, ?댁쫰, ?뺣떟, ?좊즺 ?먮즺

## Comment / Memo Handling

- source ?덉쓽 ?λЦ 異쒕젰 寃곌낵 二쇱꽍怨??숈뒿 硫붾え??archive source??洹몃?濡??좎??섏? ?딆뒿?덈떎.
- ?ㅽ뻾 ?먮쫫 ?댄빐???꾩슂??吏㏃? 二쇱꽍留??덈줈 ?④퉩?덈떎.
- ?먮Ц 硫붾え???꾩튂? ?붿???`local/Part2_Chapter05-08/<ExampleName>/` ?꾨옒??湲곕줉?⑸땲??

## Recent Import Notes

| Raw example | Archive status | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `06_GraphicsPipeline_Step6_Lighting` | 諛섏쁺 ?꾨즺 | ?깃났 | 寃???꾩슂 | ?ъ슜??Debug/Release ?ㅽ뻾 ?뺤씤, Blinn-Phong, directional/point/spot light, `Common.hlsli`, texture asset public readiness 寃???꾩슂 |
| `06_GraphicsPipeline_Step7_ResizingViewport` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, viewport resizing, Release HLSL shader type 설정 보강 후 성공, texture asset public readiness 검토 필요 |
| `06_GraphicsPipeline_Step8_ResizingWindow` | 반영 완료 | 성공 | 검토 필요 | 사용자 Debug/Release 실행 확인, window resize, swap chain `ResizeBuffers()`, render target/depth stencil 재생성, texture asset public readiness 검토 필요 |
| `06_GraphicsPipeline_Step9_PhongVsBlinnPhong` | 반영 완료 | build 성공 / run 미확인 | 검토 필요 | Phong vs Blinn-Phong specular, `useBlinnPhong`, texture asset public readiness 검토 필요 |

## Modeling Variant Import Rule

- `*_Lecture`는 강의에서 제안한 reference solution으로 보고 제외하지 않습니다.
- `*_Complete`는 사용자 풀이 또는 사용자 완성본으로 보고 제외하지 않습니다.
- archive 이름은 제출물 관점에서 `Lecture` / `Complete` 대신 `ReferenceSolution` / `UserSolution`처럼 의미가 드러나는 이름으로 바꿀 수 있습니다.
- backup, debug, 중간 실험 폴더는 기본 제외 후보로 둡니다.
- 현재 확인된 쌍:
  - `07_Modeling_Step5_Sphere_Lecture` -> `07_Modeling_Step5_Sphere_ReferenceSolution`
  - `07_Modeling_Step5-3_Sphere_Complete` -> `07_Modeling_Step5_Sphere_UserSolution`
  - `07_Modeling_Step8_SphereMapping_Lecture` -> `07_Modeling_Step8_SphereMapping_ReferenceSolution`
  - `07_Modeling_Step8-2_SphereMapping_Complete` -> `07_Modeling_Step8_SphereMapping_UserSolution`

## Current Next Action

1. ?댄썑 `07_Modeling_*` ?먮뒗 `06_GraphicsPipeline`???⑥? ?꾨낫瑜??뺤씤?⑸땲??
