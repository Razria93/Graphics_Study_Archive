# Part2 Chapter05-08

D3D11 graphics pipeline로 넘어가기 전후의 matrix transform, lighting, modeling, shader toy 예제를 정리하는 문서 공간입니다.

## 진행 방식

- raw reference는 `C:\ComputerGraphics\Part2_Chapter05-08`입니다.
- archive에는 예제별로 필요한 source/project/shader/asset만 선별 반영합니다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, raw capture/result는 포함하지 않습니다.
- source 안의 장문 학습 메모와 출력 결과 주석은 `local/`로 분리하고, source에는 실행 흐름 이해에 필요한 짧은 주석만 남깁니다.
- build/run을 직접 확인하지 않은 항목은 `미확인`으로 기록합니다.

## Examples

| Example | Code split | Build/run | Diff review | Capture | Note |
| --- | --- | --- | --- | --- | --- |
| [`05_AffineTransformations_Step1_Matrix(GLM)`](05_AffineTransformations_Step1_Matrix(GLM)/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, GLM column-major matrix |
| [`05_AffineTransformations_Step2_Lights(GLM)`](05_AffineTransformations_Step2_Lights(GLM)/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, GLM model/normal matrix |
| [`05_AffineTransformations_Step3_DirectXMath`](05_AffineTransformations_Step3_DirectXMath/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, DirectXMath/SimpleMath |
| [`05_AffineTransformations_Step4_Lights(SimpleMath)`](05_AffineTransformations_Step4_Lights(SimpleMath)/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, SimpleMath lighting |
| [`06_GraphicsPipeline_Step1_COM`](06_GraphicsPipeline_Step1_COM/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, D3D11 device creation and WRL ComPtr |
| [`06_GraphicsPipeline_Step2_InitializingD3D`](06_GraphicsPipeline_Step2_InitializingD3D/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, D3D11 initialization, swap chain, colored cube |
| [`06_GraphicsPipeline_Step3_ModelViewProj`](06_GraphicsPipeline_Step3_ModelViewProj/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, Model/View/Projection matrix and constant buffer |
| [`06_GraphicsPipeline_Step4_Shaders`](06_GraphicsPipeline_Step4_Shaders/README.md) | 완료 | 성공 | 진행 중 | 보류 | 사용자 Debug/Release 실행 확인, shader semantics and pixel shader constant buffer |
| [`06_GraphicsPipeline_Step5_Texturing`](06_GraphicsPipeline_Step5_Texturing/README.md) | 완료 | 빌드 성공 / 실행 미확인 | 진행 중 | 보류 | Texture sampling, `crate2_diffuse.png`, `wall.jpg` |

## Related Docs

- [Import manifest](../_repo/manifests/Part2_Chapter05-08.md)
- [Migration board](../_repo/tracking/migration-board.md)
