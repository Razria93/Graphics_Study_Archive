# 빌드 검증표

이 문서는 예제별 빌드/실행 확인 결과를 archive 경로 기준으로 기록합니다.

## 상태 값

| 값 | 의미 |
| --- | --- |
| 미확인 | 아직 빌드/실행하지 않음 |
| 성공 | 해당 항목 확인 완료 |
| 실패 | 실패 원인과 비고 기록 필요 |
| 보류 | 현재 정리 범위 밖이거나 촬영/사용자 확인 대기 |
| 해당 없음 | 해당 검증이 꼭 필요하지 않음 |

## 최소 검증 대상

| Part | 예제 | Debug x64 | Release x64 | 실행 | 캡처 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| Part1 | `Part1_Chapter01-02/01_DX11InitAndImGui` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인, 촬영 보류 |
| Part1 | `Part1_Chapter01-02/02_Bloom` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인, 촬영 보류 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step5_PhongShading` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step6_PerspectiveView` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step7_Triangle` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step8_Shadow` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step8_Shadow_Square` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step10_Texturing` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인, texture asset 포함 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step11_Supersampling` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인, texture asset 포함 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step12_Reflection` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인, `shadertoy_abstract1.jpg`, `back.jpg` 포함 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step13_Transparency` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 정상 확인, `shadertoy_abstract1.jpg`, `back.jpg` 포함 |
| Part1 | `Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, environment sampling 구현 |
| Part2 | `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer` | 미확인 | 미확인 | 미확인 | 미확인 | depth buffer |
| Part2 | `Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix(GLM)` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, GLM matrix transform console example |
| Part2 | `Part2_Chapter05-08/05_AffineTransformations_Step2_Lights(GLM)` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, GLM model/normal matrix lighting |
| Part2 | `Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, DirectXMath/SimpleMath |
| Part2 | `Part2_Chapter05-08/05_AffineTransformations_Step4_Lights(SimpleMath)` | 성공 | 성공 | 성공 | 보류 | 사용자 Debug/Release 실행 확인, SimpleMath lighting |
| Part2 | `Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting` | 미확인 | 미확인 | 미확인 | 미확인 | MVP and lighting |
| Part3 | `Part3_Chapter09/09_UserInteraction_Step2_MousePicking` | 미확인 | 미확인 | 미확인 | 미확인 | picking ray |
| Part3 | `Part3_Chapter10-13/12_PBR_Step2_PBRModels` | 미확인 | 미확인 | 미확인 | 미확인 | PBR models |
| Part4 | `Part4_Chapter14-20/Examples/Examples.sln` | 미확인 | 미확인 | 미확인 | 미확인 | Ex1402_Blur, Ex1501_ParticleSystem 우선 |
| Portfolio | `Portfolio_RayTracer/16-01_Sampling` | 미확인 | 미확인 | 미확인 | 미확인 | 대표 ray tracer |

## Raw reference 연결

| Archive 대상 | Raw reference | 우선 확인 |
| --- | --- | --- |
| `Portfolio_RayTracer/16-01_Sampling` | `C:\ComputerGraphics\_00_Graphics_Portfolio\16-01_Sampling` | `12_Raytracing_Refactoring.sln`, asset path, texture license |
| `Part1_Chapter01-02/01_DX11InitAndImGui` | `C:\ComputerGraphics\Part1_Chapter01-02` | `.sln` 위치, DX11/ImGui 실행 화면 |
| `Part1_Chapter01-02/02_Bloom` | `C:\ComputerGraphics\Part1_Chapter01-02\02_Bloom` | `image_1_360.JPG`, CPU bloom 처리 결과, raw result 제외 |
| `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step4_DrawingSphere` | ray-sphere intersection |
| `Part1_Chapter03/03_Raytracing_Step5_PhongShading` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step5_PhongShading` | Phong shading |
| `Part1_Chapter03/03_Raytracing_Step6_PerspectiveView` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step6_PerspectiveView` | perspective ray/camera |
| `Part1_Chapter03/03_Raytracing_Step7_Triangle` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step7_Triangle` | ray-triangle intersection |
| `Part1_Chapter03/03_Raytracing_Step8_Shadow` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step8_Shadow` | shadow ray, floor shadow |
| `Part1_Chapter03/03_Raytracing_Step8_Shadow_Square` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step8_Shadow_Square` | square primitive wrapper |
| `Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step9_BarycentricCordinates` | barycentric color interpolation |
| `Part1_Chapter03/03_Raytracing_Step10_Texturing` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step10_Texturing` | texture sampling, `shadertoy_abstract1.jpg` |
| `Part1_Chapter03/03_Raytracing_Step11_Supersampling` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step11_Supersampling` | recursive 2x2 supersampling, `shadertoy_abstract1.jpg` |
| `Part1_Chapter03/03_Raytracing_Step12_Reflection` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step12_Reflection` | recursive reflection, `shadertoy_abstract1.jpg`, `back.jpg` |
| `Part1_Chapter03/03_Raytracing_Step13_Transparency` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step13_Transparency` | transparency/refraction, `shadertoy_abstract1.jpg`, `back.jpg` |
| `Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment` | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment` | cube environment sampling, environment assets private archive 포함 |
| `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer` | `C:\ComputerGraphics\Part2_Chapter04` | depth buffer 예제 후보 |
| `Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix(GLM)` | `C:\ComputerGraphics\Part2_Chapter05-08\05_AffineTransformations_Step1_Matrix(GLM)` | GLM dependency, console output |
| `Part2_Chapter05-08/05_AffineTransformations_Step2_Lights(GLM)` | `C:\ComputerGraphics\Part2_Chapter05-08\05_AffineTransformations_Step2_Lights(GLM)` | DirectX11/ImGui, GLM model/normal matrix |
| `Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath` | `C:\ComputerGraphics\Part2_Chapter05-08\05_AffineTransformations_Step3_DirectXMath` | DirectXMath and SimpleMath dependency |
| `Part2_Chapter05-08/05_AffineTransformations_Step4_Lights(SimpleMath)` | `C:\ComputerGraphics\Part2_Chapter05-08\05_AffineTransformations_Step4_Lights(SimpleMath)` | DirectX11/ImGui, SimpleMath model/normal matrix |
| `Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting` | `C:\ComputerGraphics\Part2_Chapter05-08` | shader/model/texture 경로 |
| `Part3_Chapter09/09_UserInteraction_Step2_MousePicking` | `C:\ComputerGraphics\Part3_Chapter09` | picking 예제 후보 |
| `Part3_Chapter10-13/12_PBR_Step2_PBRModels` | `C:\ComputerGraphics\Part3_Chapter10_13`, `C:\ComputerGraphics\Part3_Chapter10_13_2` | PBR asset 출처와 중복/보존 관계 |
| `Part4_Chapter14-20/Examples/Examples.sln` | `C:\ComputerGraphics\Part4_HongLabGraphics`, `C:\ComputerGraphics\Part4_HongLabGraphics_2` | Ex1402_Blur, Ex1501_ParticleSystem 후보 |

## Archive 이름 재검증

Archive에서 chapter-range folder name을 적용한 예제는 정리 후 다시 확인합니다. 이때 `.sln`, `.vcxproj`, shader path, asset path가 기존 폴더 구조에 의존하는지 함께 확인합니다.
