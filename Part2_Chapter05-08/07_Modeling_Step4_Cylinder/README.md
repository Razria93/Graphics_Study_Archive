# Chapter07 Step4 Cylinder

두 개의 Y축 ring을 40개 slice로 sample하고 인접 vertex를 triangle로 연결해 cap이 없는 cylinder side surface를 절차적으로 생성한다. Step3의 평면 Grid에서 각도 기반 곡면 sampling으로 확장되는 과정을 확인한다.

## 실행 진입점

- Solution: `07_Modeling_Step4_Cylinder.sln`
- 주요 source: `GeometryGenerator.cpp`, `AppBase.cpp`, `ExampleApp.cpp`
- Shader: `BasicVertexShader.hlsl`, `BasicPixelShader.hlsl`, `NormalVertexShader.hlsl`, `NormalPixelShader.hlsl`
- Runtime input: `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter07 Step4 Cylinder`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [GeometryGenerator.cpp](GeometryGenerator.cpp#L200-L271) | Bottom·top ring의 position·radial normal·UV 생성 |
| [GeometryGenerator.cpp](GeometryGenerator.cpp#L273-L290) | 두 ring 사이의 triangle index 구성 |
| [ExampleApp.cpp](ExampleApp.cpp#L46-L55) | Cylinder 생성과 GPU buffer 연결 |
| [ExampleApp.cpp](ExampleApp.cpp#L230-L286) | Viewport, surface와 optional normal draw |

## Capture/Result

![Chapter07 Step4 Cylinder](../../Docs/_assets/captures/part2_chapter07_04_cylinder.png)

`Wireframe=On`, `Use Texture=Off`, `Draw Normals=Off` 상태에서 40개 slice와 열린 상단을 함께 표시한다. 원주 방향 edge와 각 quad를 나누는 triangle 대각선으로 side surface topology를 읽는다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, Shader Model 5.0 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Resize | 성공 | wide·compact·반복 resize와 minimize/restore 후 정상 frame |
| Capture/Result | 확보 | 전체 창 PNG 1282×992, 기술·시각 검수 완료 |
| Video | 제외 | 정적 wireframe 한 장으로 ring·slice·triangle topology 확인 가능 |

## Limitations

- 현재 mesh는 bottom·top cap을 만들지 않는 side surface 전용 구현이다.
- 높이 방향 stack은 한 구간이며 runtime UI에서 slice 수를 바꾸지 않는다.
- `sliceCount + 1` vertex로 위치가 같은 seam을 중복하고 UV의 `u=0`, `u=1`을 분리한다.
- 서로 다른 bottom·top radius를 받지만 normal은 taper를 반영하지 않은 radial normal이다.
- 현재 index winding과 outward radial normal의 방향 정합은 후속 검토 대상으로 남기며 rasterizer는 culling을 사용하지 않는다.

## Related Docs

- [Procedural Primitive Generation](../../Docs/01_Topics/ModelingAndGeometry/ProceduralPrimitiveGeneration.md)
- [Verification](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/07_04_Cylinder.md)
- [이전 단계: Chapter07 Step3](../07_Modeling_Step3_Grid/README.md)
- [다음 단계: Chapter07 Step5 Sphere UserSolution](../07_Modeling_Step5_Sphere_UserSolution/README.md)
