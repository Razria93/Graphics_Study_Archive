# Chapter07 Step6 Subdivision

위도·경도 sphere를 seed mesh로 만든 뒤 각 triangle을 4개로 분할하고 새 midpoint를 sphere 표면에 투영해 topology를 세밀하게 만드는 예제다. Step5의 두 반구 UserSolution을 직접 확장하지 않고 별도의 subdivision 기반 refinement 경로를 보여준다.

## 실행 진입점

- Solution: `07_Modeling_Step6_Subdivision.sln`
- 주요 source: `GeometryGenerator.cpp`, `AppBase.cpp`, `ExampleApp.cpp`
- Shader: `BasicVertexShader.hlsl`, `BasicPixelShader.hlsl`, `NormalVertexShader.hlsl`, `NormalPixelShader.hlsl`
- Runtime input: `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter07 Step6 Subdivision`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [GeometryGenerator.cpp](GeometryGenerator.cpp#L262-L330) | 5×5 위도·경도 sphere seed 생성 |
| [GeometryGenerator.cpp](GeometryGenerator.cpp#L416-L482) | 입력 vertex와 edge midpoint의 sphere surface projection |
| [GeometryGenerator.cpp](GeometryGenerator.cpp#L484-L508) | Parent triangle당 child triangle 4개와 순차 index 생성 |
| [ExampleApp.cpp](ExampleApp.cpp#L40-L51) | Subdivision 2회 적용과 GPU buffer 연결 |
| [ExampleApp.cpp](ExampleApp.cpp#L238-L266) | Surface `TRIANGLELIST`와 optional normal `LINELIST` draw |

## Capture/Result

![Chapter07 Step6 Subdivision](../../Docs/_assets/captures/part2_chapter07_06_subdivision.png)

`Wireframe=On`, `Use Texture=Off`, `Draw Normals=Off` 상태에서 두 번 세분화한 sphere의 child triangle 분포와 topology를 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, Shader Model 5.0 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD |
| Resize | 성공 | Wide·compact·반복 resize, minimize/restore와 기본 크기 복원 |
| Capture/Result | 확보 | 전체 창 PNG 1282×992, 기술·시각 검수 완료 |
| Video | 제외 | 고정 2-pass 결과를 wireframe과 수치 표로 설명 가능 |

## 구현 범위와 한계

- Seed는 36 vertices와 50 triangles이며 2회 subdivision 후 2,400 vertices와 800 triangles가 된다.
- 각 parent triangle이 midpoint를 독립 생성하므로 shared edge vertex를 재사용하지 않는 triangle-soup 구조다.
- 이 중복 구조는 다음 Step7에서 child triangle별 face normal을 계산하는 학습 흐름으로 이어진다.
- Seed sphere의 pole band에 있던 면적 0 triangle은 subdivision 후에도 남아 최종 800개 중 160개가 degenerate다.
- UV는 edge endpoint의 산술 평균만 사용하므로 seam을 가로지르는 edge에서 texture 좌표가 어긋날 수 있다.
- 현재 고정 2회는 16-bit index 범위 안이다. 4회에서는 normal line index가 먼저 범위를 넘고 5회에서는 surface mesh도 범위를 넘는다.
- Pole topology 정리, shared midpoint cache, UV seam 재계산과 32-bit index 전환은 범위 밖이다.

## Related Docs

- [Procedural Primitive Generation](../../Docs/01_Topics/ModelingAndGeometry/ProceduralPrimitiveGeneration.md)
- [Vertex And Face Normals](../../Docs/01_Topics/ModelingAndGeometry/VertexAndFaceNormals.md)
- [Verification](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/07_06_Subdivision.md)
- [이전 단계: Chapter07 Step5 Sphere UserSolution](../07_Modeling_Step5_Sphere_UserSolution/README.md)
- 다음 단계: `07_Modeling_Step7_FaceNormals`
