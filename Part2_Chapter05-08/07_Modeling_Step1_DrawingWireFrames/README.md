# Chapter07 Step1 DrawingWireFrames

이 예제는 절차적으로 생성한 box mesh를 triangle list로 전달하고 rasterizer의 fill mode를 wireframe으로 전환한다. 별도 line geometry를 만들지 않으므로 각 사각 face를 나눈 triangle diagonal도 결과에 나타난다.

## 실행 진입점

- Solution: `07_Modeling_Step1_DrawingWireFrames.sln`
- Application entry: `main.cpp`
- 주요 source: `GeometryGenerator.cpp`, `AppBase.cpp`, `ExampleApp.cpp`
- Shader: `BasicVertexShader.hlsl`, `BasicPixelShader.hlsl`, `Common.hlsli`
- Runtime input: `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter07 Step1 DrawingWireFrames`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [GeometryGenerator.cpp](GeometryGenerator.cpp#L55-L188) | 24개 face vertex와 36개 triangle index로 box mesh 생성 |
| [AppBase.cpp](AppBase.cpp#L357-L389) | solid와 wireframe rasterizer state 생성 |
| [ExampleApp.cpp](ExampleApp.cpp#L203-L231) | fill mode 선택, triangle list binding과 indexed draw |
| [ExampleApp.cpp](ExampleApp.cpp#L234-L247) | wireframe과 model transform UI |

## Capture/Result

![Chapter07 Step1 DrawingWireFrames](../../Docs/_assets/captures/part2_chapter07_01_drawing_wireframes.png)

`Wireframe=On`, `Use Texture=Off`와 비스듬한 model rotation을 기본값으로 사용한다. Box의 세 면과 triangle diagonal을 한 화면에서 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Resize | 성공 | wide·compact·minimize/restore 후 정상 frame과 clean exit |
| Capture/Result | 확보 | 전체 창 PNG 1282×992, 기술·시각 검수 완료 |
| Video | 제외 | 고정 wireframe 결과를 screenshot 한 장으로 설명 가능 |

## Limitations

- Wireframe은 `D3D11_FILL_WIREFRAME` 결과이며 box edge만 따로 만든 `LINELIST`가 아니다.
- Face마다 vertex를 분리해 normal과 UV를 유지하므로 shared vertex 8개 구조가 아니다.
- 다음 Step2의 normal line geometry와 이후 modeling primitive는 포함하지 않는다.
- Generated wood texture는 solid mode 비교를 위한 보조 input이며 기본 capture에서는 사용하지 않는다.

## Related Docs

- [Mesh Topology And Wireframe Rasterization](../../Docs/01_Topics/ModelingAndGeometry/MeshTopologyAndWireframeRasterization.md)
- [Verification](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/07_01_DrawingWireFrames.md)
- [Publication](../../Docs/05_Publication/candidate-list.md)
- [이전 단계: Chapter06 Step9](../06_GraphicsPipeline_Step9_PhongVsBlinnPhong/README.md)
- [다음 단계: Chapter07 Step2 DrawingNormals](../07_Modeling_Step2_DrawingNormals/README.md)
