# 그래픽스 전체 예제·실행 결과

[프로젝트 README](../../README.md) · [문서 탐색](README.md) · [포트폴리오 선정 주제](../../PORTFOLIO.md#graphics)

학습 예제 104개를 코드 순서로 찾는 목록이다. 예제 안내 104개와 상세 Demo 103개를 연결한다. DX11 초기화 예제는 별도 Demo 없이 구현·실행 안내로 연결한다.

상세 Demo에는 결과 이미지뿐 아니라 입출력, 구현 흐름, 핵심 코드와 한계가 함께 있다. 계산·콘솔 예제는 화면 대신 출력 결과를 사용한다. 각 결과의 조건과 확인 범위는 연결 문서를 기준으로 읽는다.

## 바로 찾기

- [Part 1 · Chapter 01–02 · DirectX11 초기화·CPU Bloom](#part1-ch01-02) — 2개
- [Part 1 · Chapter 03 · CPU Ray Tracing](#part1-ch03) — 11개
- [Part 2 · Chapter 04 · CPU 래스터화·입력 보간](#part2-ch04) — 11개
- [Part 2 · Chapter 05–08 · 변환·D3D11 파이프라인·메시·조명](#part2-ch05-08) — 30개
- [Part 3 · Chapter 09 · 카메라·선택·드래그](#part3-ch09) — 6개
- [Part 3 · Chapter 10–13 · 기하 처리·재질·HDR·그림자](#part3-ch10-13) — 21개
- [Part 4 · Chapter 14–20 · GPU 연산·시뮬레이션·애니메이션·지형](#part4-ch14-20) — 23개

개념으로 찾으려면 [개념 목록](../01_Topics/README.md), 포트폴리오에 선정된 13개 주제는 [주제별 안내](../../PORTFOLIO.md#graphics)를 사용한다.

공개 시연은 [포트폴리오 실행 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-demos/index.html)과 [GitHub 게시 영상](../_assets/videos/README.md)에서 찾을 수 있다. 모든 예제에 영상이 있는 것은 아니며, 정지 비교·storyboard·콘솔 출력으로 설명하는 사례도 포함한다.

<a id="part1-ch01-02"></a>

## Part 1 · Chapter 01–02 · DirectX11 초기화·CPU Bloom

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| 01<br>DX11InitAndImGui | CPU 픽셀을 동적 텍스처로 올리는 기본 렌더링 루프 | 별도 Demo 없음 | [예제 README](../../Part1_Chapter01-02/01_DX11InitAndImGui/README.md) |
| 02<br>Bloom | CPU의 밝은 영역 분리·블러·합성과 GPU 화면 표시 | [결과·Demo](../03_Demos/Part1_Chapter01-02/02_Bloom.md) | [예제 README](../../Part1_Chapter01-02/02_Bloom/README.md) |

[Part 안내](../../Part1_Chapter01-02/README.md) · [상세 Demo 인덱스](../03_Demos/Part1_Chapter01-02/demo-index.md) · [목록 위로](#바로-찾기)

<a id="part1-ch03"></a>

## Part 1 · Chapter 03 · CPU Ray Tracing

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| Step4<br>DrawingSphere | 직교 광선과 구 교차로 시작하는 CPU 레이 트레이싱 | [결과·Demo](../03_Demos/Part1_Chapter03/03_04_DrawingSphere.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md) |
| Step5<br>PhongShading | 교차점·법선에 Phong 조명을 적용하는 흐름 | [결과·Demo](../03_Demos/Part1_Chapter03/03_05_PhongShading.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step5_PhongShading/README.md) |
| Step6<br>PerspectiveView | 원근 광선과 가장 가까운 교차 선택 | [결과·Demo](../03_Demos/Part1_Chapter03/03_06_PerspectiveView.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step6_PerspectiveView/README.md) |
| Step7<br>Triangle | 삼각형 교차와 내부 판정을 기존 장면에 추가 | [결과·Demo](../03_Demos/Part1_Chapter03/03_07_Triangle.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step7_Triangle/README.md) |
| Step8<br>Shadow | 빛까지의 가림 여부를 검사하는 그림자 광선 | [결과·Demo](../03_Demos/Part1_Chapter03/03_08_Shadow.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step8_Shadow/README.md) |
| Step9<br>Barycentric Coordinates | 삼각형 내부 위치에 따른 정점 색 보간 | [결과·Demo](../03_Demos/Part1_Chapter03/03_09_BarycentricCoordinates.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates/README.md) |
| Step10<br>Texturing | 무게중심 좌표의 UV 보간과 CPU 텍스처 샘플링 | [결과·Demo](../03_Demos/Part1_Chapter03/03_10_Texturing.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step10_Texturing/README.md) |
| Step11<br>Supersampling | 여러 광선의 평균으로 완화하는 경계 계단 현상 | [결과·Demo](../03_Demos/Part1_Chapter03/03_11_Supersampling.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step11_Supersampling/README.md) |
| Step12<br>Reflection | 재귀 반사 광선과 표면 조명 결과의 합성 | [결과·Demo](../03_Demos/Part1_Chapter03/03_12_Reflection.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step12_Reflection/README.md) |
| Step13<br>Transparency | 굴절률과 경계 방향에 따른 투명체 굴절 | [결과·Demo](../03_Demos/Part1_Chapter03/03_13_Transparency.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step13_Transparency/README.md) |
| Step14<br>CubeEnvironment | 광선 방향을 큐브맵의 면과 UV로 변환 | [결과·Demo](../03_Demos/Part1_Chapter03/03_14_CubeEnvironment.md) | [예제 README](../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/README.md) |

[Part 안내](../../Part1_Chapter03/README.md) · [상세 Demo 인덱스](../03_Demos/Part1_Chapter03/demo-index.md) · [목록 위로](#바로-찾기)

<a id="part2-ch04"></a>

## Part 2 · Chapter 04 · CPU 래스터화·입력 보간

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| Step1<br>Triangle | 삼각형을 픽셀로 변환하고 정점 색을 보간 | [결과·Demo](../03_Demos/Part2_Chapter04/01_Triangle.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step1_Triangle/README.md) |
| Step1A<br>Triangle To Circle | 삼각형 팬의 분할 수를 조절하는 개인 확장 | [결과·Demo](../03_Demos/Part2_Chapter04/01_TriangleToCircle.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step1_TriangleToCircle/README.md) |
| Step2<br>Circle | 공유 정점과 인덱스로 구성한 원의 래스터화 | [결과·Demo](../03_Demos/Part2_Chapter04/02_Circle.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step2_Circle/README.md) |
| Step3<br>Transformations2D | 이동·회전·크기 변환의 적용 순서 비교 | [결과·Demo](../03_Demos/Part2_Chapter04/03_Transformations2D.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step3_Transformations2D/README.md) |
| Step4<br>Animation2D | 시간과 부모·자식 변환을 연결한 2D 공전 | [결과·Demo](../03_Demos/Part2_Chapter04/04_Animation2D.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step4_Animation2D/README.md) |
| Step5<br>DepthBuffer | 깊이 비교로 결정하는 겹친 도형의 앞뒤 관계 | [결과·Demo](../03_Demos/Part2_Chapter04/05_DepthBuffer.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/README.md) |
| Step6<br>ShadersConcept | CPU 정점·픽셀 단계의 입출력 분리 | [결과·Demo](../03_Demos/Part2_Chapter04/06_ShadersConcept.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/README.md) |
| Step7<br>BackfaceCulling | 화면에서의 정점 순서에 따른 뒷면 제거 | [결과·Demo](../03_Demos/Part2_Chapter04/07_BackfaceCulling.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step7_BackfaceCulling/README.md) |
| Step8<br>PerspectiveProjection | 원근 투영과 UV 보간 보정의 차이 비교 | [결과·Demo](../03_Demos/Part2_Chapter04/08_PerspectiveProjection.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step8_PerspectiveProjection/README.md) |
| Step9<br>Shading | 법선·재질·조명이 최종 픽셀 색을 만드는 흐름 | [결과·Demo](../03_Demos/Part2_Chapter04/09_Shading.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step9_Shading/README.md) |
| Step10<br>Lights | 방향광·점광원·스포트라이트의 결과 비교 | [결과·Demo](../03_Demos/Part2_Chapter04/10_Lights.md) | [예제 README](../../Part2_Chapter04/04_Rasterization_Step10_Lights/README.md) |

[Part 안내](../../Part2_Chapter04/README.md) · [상세 Demo 인덱스](../03_Demos/Part2_Chapter04/demo-index.md) · [목록 위로](#바로-찾기)

<a id="part2-ch05-08"></a>

## Part 2 · Chapter 05–08 · 변환·D3D11 파이프라인·메시·조명

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| Chapter05 Step1<br>Matrix(GLM) | 행렬 곱 순서와 점·방향 변환의 수치 확인 | [결과·Demo](../03_Demos/Part2_Chapter05-08/05_MatrixGLM.md) | [예제 README](../../Part2_Chapter05-08/05_AffineTransformations_Step1_Matrix%28GLM%29/README.md) |
| Chapter05 Step2<br>Lights(GLM) | GLM 위치·법선 변환과 CPU 조명 계산 | [결과·Demo](../03_Demos/Part2_Chapter05-08/05_LightsGLM.md) | [예제 README](../../Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md) |
| Chapter05 Step3<br>DirectXMath | DirectXMath·SimpleMath의 점·방향 변환 비교 | [결과·Demo](../03_Demos/Part2_Chapter05-08/05_DirectXMath.md) | [예제 README](../../Part2_Chapter05-08/05_AffineTransformations_Step3_DirectXMath/README.md) |
| Chapter05 Step4<br>Lights(SimpleMath) | GLM 장면을 SimpleMath로 옮긴 변환·조명 비교 | [결과·Demo](../03_Demos/Part2_Chapter05-08/05_LightsSimpleMath.md) | [예제 README](../../Part2_Chapter05-08/05_AffineTransformations_Step4_Lights%28SimpleMath%29/README.md) |
| Chapter06 Step1<br>COM | D3D11 장치 생성과 COM 참조의 소유·해제 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_COM.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step1_COM/README.md) |
| Chapter06 Step2<br>InitializingD3D | Win32 창과 D3D11 출력 자원을 연결한 첫 프레임 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_InitializingD3D.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step2_InitializingD3D/README.md) |
| Chapter06 Step3<br>ModelViewProj | 모델·카메라·투영 파라미터의 화면 변화 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_ModelViewProj.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step3_ModelViewProj/README.md) |
| Chapter06 Step4<br>Shaders | CPU UI 값이 GPU 픽셀 셰이더에 반영되는 흐름 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_Shaders.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders/README.md) |
| Chapter06 Step5<br>Texturing | 텍스처·SRV·샘플러 생성과 GPU 샘플링 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_Texturing.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing/README.md) |
| Chapter06 Step5A<br>Texturing LightingSelf | 텍스처·법선·점광원 조명 결합과 위치 비교 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_TexturingLightingSelf.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing_LightingSelf/README.md) |
| Chapter06 Step6<br>Lighting | 같은 장면에서 광원 종류와 고유 파라미터 비교 | [결과·Demo](../03_Demos/Part2_Chapter05-08/06_Lighting.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/README.md) |
| Chapter06 Step7<br>ResizingViewport | UI 폭에 맞춘 장면 영역과 투영 비율 조정 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_ResizingViewport.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step7_ResizingViewport/README.md) |
| Chapter06 Step8<br>ResizingWindow | 창 크기에 따른 출력 자원·뷰포트 재구성 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_ResizingWindow.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step8_ResizingWindow/README.md) |
| Chapter06 Step9<br>PhongVsBlinnPhong | 반사 벡터·하프 벡터에 따른 하이라이트 비교 | [결과·Demo](../03_Demos/Part2_Chapter05-08/09_PhongVsBlinnPhong.md) | [예제 README](../../Part2_Chapter05-08/06_GraphicsPipeline_Step9_PhongVsBlinnPhong/README.md) |
| Chapter07 Step1<br>DrawingWireFrames | 인덱스 박스 메시의 채움·와이어프레임 표시 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_01_DrawingWireFrames.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step1_DrawingWireFrames/README.md) |
| Chapter07 Step2<br>DrawingNormals | 표면과 법선 진단선을 분리한 렌더링 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_02_DrawingNormals.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step2_DrawingNormals/README.md) |
| Chapter07 Step3<br>Grid | 격자 정점·UV·인덱스의 절차적 생성 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_03_Grid.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step3_Grid/README.md) |
| Chapter07 Step4<br>Cylinder | 두 링을 삼각형으로 연결한 원기둥 측면 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_04_Cylinder.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step4_Cylinder/README.md) |
| Chapter07 Step5<br>Sphere | 반구와 극점 삼각형 팬을 조합한 구 생성 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_05_Sphere.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step5_Sphere/README.md) |
| Chapter07 Step6<br>Subdivision | 삼각형 분할과 구 표면으로의 정점 투영 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_06_Subdivision.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step6_Subdivision/README.md) |
| Chapter07 Step7<br>FaceNormals | 삼각형 정점 순서에서 계산한 면 법선 표시 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_07_FaceNormals.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step7_FaceNormals/README.md) |
| Chapter07 Step8<br>SphereMapping | 구면 UV와 경계 이음매 보정 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_08_SphereMapping.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/README.md) |
| Chapter07 Step9<br>ModelFiles | FBX 노드·메시·텍스처를 D3D11 자원으로 변환 | [결과·Demo](../03_Demos/Part2_Chapter05-08/07_09_ModelFiles.md) | [예제 README](../../Part2_Chapter05-08/07_Modeling_Step9_ModelFiles/README.md) |
| Chapter08 Step1<br>RimLighting | 법선과 시선으로 계산하는 실루엣 조명 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_01_RimLighting.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step1_RimLighting/README.md) |
| Chapter08 Step2<br>Cubemapping | 방향 벡터로 샘플링하는 큐브맵 배경 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_02_Cubemapping.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/README.md) |
| Chapter08 Step3<br>EnvironmentMapping | 반사 벡터에 따른 환경색 선택 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_03_EnvironmentMapping.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step3_EnvironmentMapping/README.md) |
| Chapter08 Step4<br>ImageBasedLighting | 환경 큐브맵을 확산·반사 조명에 사용 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_04_ImageBasedLighting.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step4_ImageBasedLighting/README.md) |
| Chapter08 Step5<br>FresnelEffect | 시선 각도에 따라 달라지는 환경 반사 비중 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_05_FresnelEffect.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step5_FresnelEffect/README.md) |
| Chapter08 Step6<br>BloomEffect | GPU의 밝은 영역 분리·블러·원본 합성 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_06_BloomEffect.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/README.md) |
| Chapter08 Step7<br>Shadertoy | 시간·해상도·텍스처 입력과 절차적 별 표현 | [결과·Demo](../03_Demos/Part2_Chapter05-08/08_07_Shadertoy.md) | [예제 README](../../Part2_Chapter05-08/08_ShaderToys_Step7_Shadertoy/README.md) |

[Part 안내](../../Part2_Chapter05-08/README.md) · [상세 Demo 인덱스](../03_Demos/Part2_Chapter05-08/demo-index.md) · [목록 위로](#바로-찾기)

<a id="part3-ch09"></a>

## Part 3 · Chapter 09 · 카메라·선택·드래그

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| Chapter09 Step1<br>FirstPersonView | 키보드·마우스 입력에 따른 카메라 이동 | [결과·Demo](../03_Demos/Part3_Chapter09/09_01_FirstPersonView.md) | [예제 README](../../Part3_Chapter09/09_UserInteraction_Step1_FirstPersonView/README.md) |
| Chapter09 Step2<br>MousePicking | GPU 오브젝트 ID를 읽어 커서 대상을 식별 | [결과·Demo](../03_Demos/Part3_Chapter09/09_02_MousePicking.md) | [예제 README](../../Part3_Chapter09/09_UserInteraction_Step2_MousePicking/README.md) |
| Chapter09 Step3<br>MousePickingRayCollision | 화면 광선과 경계 구의 CPU 충돌 선택 | [결과·Demo](../03_Demos/Part3_Chapter09/09_03_MousePickingRayCollision.md) | [예제 README](../../Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision/README.md) |
| Chapter09 Step4<br>QuaternionRotation | 축·각도를 쿼터니언과 회전 행렬로 변환 | [결과·Demo](../03_Demos/Part3_Chapter09/09_04_QuaternionRotation.md) | [예제 README](../../Part3_Chapter09/09_UserInteraction_Step4_QuaternianRotation/README.md) |
| Chapter09 Step5<br>VirtualTrackball | 구 표면 드래그를 오브젝트 회전으로 변환 | [결과·Demo](../03_Demos/Part3_Chapter09/09_05_VirtualTrackball.md) | [예제 README](../../Part3_Chapter09/09_UserInteraction_Step5_VirtualTrackball/README.md) |
| Chapter09 Step6<br>MouseDragMove | 선택 깊이를 유지하는 3D 드래그 이동 | [결과·Demo](../03_Demos/Part3_Chapter09/09_06_MouseDragMove.md) | [예제 README](../../Part3_Chapter09/09_UserInteraction_Step6_MouseDragMove/README.md) |

[Part 안내](../../Part3_Chapter09/README.md) · [상세 Demo 인덱스](../03_Demos/Part3_Chapter09/demo-index.md) · [목록 위로](#바로-찾기)

<a id="part3-ch10-13"></a>

## Part 3 · Chapter 10–13 · 기하 처리·재질·HDR·그림자

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| Chapter10 Step1<br>GeometryShader | 점 하나를 사각형으로 확장하는 기하 셰이더 | [결과·Demo](../03_Demos/Part3_Chapter10-13/10_01_GeometryShader.md) | [예제 README](../../Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/README.md) |
| Chapter10 Step2<br>Billboards | 카메라를 향하는 나무 빌보드 생성 | [결과·Demo](../03_Demos/Part3_Chapter10-13/10_02_Billboards.md) | [예제 README](../../Part3_Chapter10-13/10_GeometryPipeline_Step2_Billboards/README.md) |
| Chapter10 Step3<br>NormalLines | 기하 셰이더로 정점 법선 진단선 표시 | [결과·Demo](../03_Demos/Part3_Chapter10-13/10_03_NormalLines.md) | [예제 README](../../Part3_Chapter10-13/10_GeometryPipeline_Step3_NormalLines/README.md) |
| Chapter10 Step4<br>Fireball | 빌보드와 시간 기반 절차적 화염구 표현 | [결과·Demo](../03_Demos/Part3_Chapter10-13/10_04_Fireball.md) | [예제 README](../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/README.md) |
| Chapter10 Step5<br>Tessellation | 패치 분할 밀도 조절과 거리 기반 개인 확장 | [결과·Demo](../03_Demos/Part3_Chapter10-13/10_05_Tessellation.md) | [예제 README](../../Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/README.md) |
| Chapter11 Step1<br>Mipmaps | 밉 레벨에 따른 세부 표현과 축소 필터링 | [결과·Demo](../03_Demos/Part3_Chapter10-13/11_01_Mipmaps.md) | [예제 README](../../Part3_Chapter10-13/11_TexturingTechniques_Step1_Mipmaps/README.md) |
| Chapter11 Step2<br>NormalMapping | 노멀 텍스처로 바꾸는 표면의 조명 방향 | [결과·Demo](../03_Demos/Part3_Chapter10-13/11_02_NormalMapping.md) | [예제 README](../../Part3_Chapter10-13/11_TexturingTechniques_Step2_NormalMapping/README.md) |
| Chapter11 Step3<br>HeightMapping | 높이 텍스처로 이동하는 정점과 실루엣 | [결과·Demo](../03_Demos/Part3_Chapter10-13/11_03_HeightMapping.md) | [예제 README](../../Part3_Chapter10-13/11_TexturingTechniques_Step3_HeightMapping/README.md) |
| Chapter11 Step4<br>HDRI | EXR 입력의 노출·감마 변환 | [결과·Demo](../03_Demos/Part3_Chapter10-13/11_04_HDRI.md) | [예제 README](../../Part3_Chapter10-13/11_TexturingTechniques_Step4_HDRI/README.md) |
| Chapter11 Step5<br>HDRPipeline | HDR 버퍼·Bloom·노출을 연결한 후처리 | [결과·Demo](../03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md) | [예제 README](../../Part3_Chapter10-13/11_TexturingTechniques_Step5_HDRPipeline/README.md) |
| Chapter12 Step1<br>UnrealPBR | 금속성·거칠기 텍스처와 환경 조명 결합 | [결과·Demo](../03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md) | [예제 README](../../Part3_Chapter10-13/12_PBR_Step1_UnrealPBR/README.md) |
| Chapter12 Step2<br>PBRModels | 불러온 캐릭터와 여러 재질에 PBR 적용 | [결과·Demo](../03_Demos/Part3_Chapter10-13/12_02_PBRModels.md) | [예제 README](../../Part3_Chapter10-13/12_PBR_Step2_PBRModels/README.md) |
| Chapter13 Step1<br>Mirror | 스텐실 마스크와 반사 행렬의 평면 거울 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_01_Mirror.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step1_Mirror/README.md) |
| Chapter13 Step2<br>PipelineStateObject | 셰이더·고정 기능 상태의 묶음 관리 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_02_PipelineStateObject.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step2_PipelineStateObject/README.md) |
| Chapter13 Step2B<br>Shadow Prototype | 깊이 패스와 본 패스를 나눈 그림자 프로토타입 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_02B_ShadowPrototype.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step2_Shadow/README.md) |
| Chapter13 Step3<br>DepthBufferAndFog | 깊이 버퍼 복원과 거리 기반 안개 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_03_DepthBufferAndFog.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step3_DepthBufferAndFog/README.md) |
| Chapter13 Step4<br>ShadowMapping | 광원 공간의 깊이를 비교하는 그림자 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_04_ShadowMapping.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step4_ShadowMapping/README.md) |
| Chapter13 Step5<br>SoftShadowPCF | 여러 깊이 비교 결과로 완화한 그림자 경계 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_05_SoftShadowPCF.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step5_SoftShadowPCF/README.md) |
| Chapter13 Step6<br>SoftShadowPCSS | 가림 물체 탐색과 가변 폭 그림자 필터링 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_06_SoftShadowPCSS.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step6_SoftShadowPCSS/README.md) |
| Chapter13 Step7<br>Halo | 깊이를 고려한 광원 주변 Halo 합성 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_07_Halo.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step7_Halo/README.md) |
| Chapter13 Step8<br>UnrealSphereLight | 대표점을 이용한 구형 면광원 반응 근사 | [결과·Demo](../03_Demos/Part3_Chapter10-13/13_08_UnrealSphereLight.md) | [예제 README](../../Part3_Chapter10-13/13_LightAndShadow_Step8_UnrealSphereLight/README.md) |

[Part 안내](../../Part3_Chapter10-13/README.md) · [상세 Demo 인덱스](../03_Demos/Part3_Chapter10-13/demo-index.md) · [목록 위로](#바로-찾기)

<a id="part4-ch14-20"></a>

## Part 4 · Chapter 14–20 · GPU 연산·시뮬레이션·애니메이션·지형

| 예제 | 확인할 내용 | 실행 결과·Demo | 구현·실행 |
| --- | --- | --- | --- |
| Chapter14 Ex1401<br>Basic | 백 버퍼를 계산 셰이더의 출력으로 연결 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_01_Basic.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_01_Basic.md) |
| Chapter14 Ex1402<br>Blur | SRV·UAV를 교대하는 두 텍스처의 GPU 블러 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_02_Blur.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_02_Blur.md) |
| Chapter14 Ex1403<br>MatVecMult | 행렬·벡터 곱의 CPU·GPU 결과 비교 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_03_MatVecMult.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_03_MatVecMult.md) |
| Chapter14 Ex1404<br>StructuredBuffer | 구조화 버퍼 갱신과 점 구름 렌더링 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_04_StructuredBuffer.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_04_StructuredBuffer.md) |
| Chapter14 Ex1405<br>ConsumeAppendBuffer | 버퍼 카운터와 그리기 수량의 연결 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_05_ConsumeAppendBuffer.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_05_ConsumeAppendBuffer.md) |
| Chapter14 Ex1406<br>DensityField | 입자 공급·밀도 감쇠를 결합한 색상 궤적 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_06_DensityField.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_06_DensityField.md) |
| Chapter14 Ex1407<br>IndirectArguments | GPU 버퍼에 저장된 인수로 간접 그리기 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_07_IndirectArguments.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_07_IndirectArguments.md) |
| Chapter14 Ex1408<br>BitonicSort | GPU Bitonic 정렬과 CPU 결과 비교 | [결과·Demo](../03_Demos/Part4_Chapter14-20/14_08_BitonicSort.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/14_08_BitonicSort.md) |
| Chapter15 Ex1501<br>ParticleSystem | CPU 입자 수명·충돌 갱신과 스프라이트 출력 | [결과·Demo](../03_Demos/Part4_Chapter14-20/15_01_ParticleSystem.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/15_01_ParticleSystem.md) |
| Chapter15 Ex1502<br>SpriteFireEffect | 텍스처 입자와 부력 갱신의 화염 표현 | [결과·Demo](../03_Demos/Part4_Chapter14-20/15_02_SpriteFireEffect.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/15_02_SpriteFireEffect.md) |
| Chapter15 Ex1503<br>SphWater | SPH 압력·점성·경계 충돌에 따른 입자 운동 | [결과·Demo](../03_Demos/Part4_Chapter14-20/15_03_SphWater.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/15_03_SphWater.md) |
| Chapter16 Ex1601<br>StableFluids | 마우스 입력과 2D 속도·밀도장 갱신 | [결과·Demo](../03_Demos/Part4_Chapter14-20/16_01_StableFluids.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/16_01_StableFluids.md) |
| Chapter16 Ex1602<br>CurlNoise | Curl 속도장과 입자 밀도 궤적 | [결과·Demo](../03_Demos/Part4_Chapter14-20/16_02_CurlNoise.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/16_02_CurlNoise.md) |
| Chapter16 Ex1603<br>Cloud | 절차적 3D 밀도·조명장과 구름 볼륨 렌더링 | [결과·Demo](../03_Demos/Part4_Chapter14-20/16_03_Cloud.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/16_03_Cloud.md) |
| Chapter16 Ex1604<br>RealtimeSmoke | GPU 3D 유체 갱신과 연기 볼륨 렌더링 | [결과·Demo](../03_Demos/Part4_Chapter14-20/16_04_RealtimeSmoke.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/16_04_RealtimeSmoke.md) |
| Chapter16 Ex1605<br>SmokeCpu | CPU 밀도장을 Texture3D로 전달한 연기 표현 | [결과·Demo](../03_Demos/Part4_Chapter14-20/16_05_SmokeCpu.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/16_05_SmokeCpu.md) |
| Chapter16 Ex1606<br>HybridWater | 입자·격자 결합과 수면 밀도장 표시 | [결과·Demo](../03_Demos/Part4_Chapter14-20/16_06_HybridWater.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/16_06_HybridWater.md) |
| Chapter17 Ex1701<br>SkeletalAnimation | 클립별 뼈 변환을 전달하는 스키닝 | [결과·Demo](../03_Demos/Part4_Chapter14-20/17_01_SkeletalAnimation.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/17_01_SkeletalAnimation.md) |
| Chapter18 Ex1801<br>Tree | 줄기·잎 파라미터에 따른 셰이더 바람 변형 | [결과·Demo](../03_Demos/Part4_Chapter14-20/18_01_Tree.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/18_01_Tree.md) |
| Chapter18 Ex1802<br>Grass | 잔디 인스턴싱과 시간에 따른 바람 변형 | [결과·Demo](../03_Demos/Part4_Chapter14-20/18_02_Grass.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/18_02_Grass.md) |
| Chapter18 Ex1803<br>Landscape | 높이맵 지형과 절차적 바다 렌더링 | [결과·Demo](../03_Demos/Part4_Chapter14-20/18_03_Landscape.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/18_03_Landscape.md) |
| Chapter19 Ex1901<br>PhysX | 고정 시간 간격의 강체 계산과 블록 붕괴 | [결과·Demo](../03_Demos/Part4_Chapter14-20/19_01_PhysX.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/19_01_PhysX.md) |
| Chapter20 Ex2001<br>GamePlay | 애니메이션 알림·발사체·물리·표시의 연결 | [결과·Demo](../03_Demos/Part4_Chapter14-20/20_01_GamePlay.md) | [ExampleDocs](../../Part4_Chapter14-20/ExampleDocs/20_01_GamePlay.md) |

[Part 안내](../../Part4_Chapter14-20/README.md) · [상세 Demo 인덱스](../03_Demos/Part4_Chapter14-20/demo-index.md) · [목록 위로](#바로-찾기)

## 별도 개인 확장 프로젝트

[Portfolio GraphicsLab](../../Portfolio_GraphicsLab/README.md)은 위 학습 예제 목록과 구분한다. 현재 문서는 WU-R0 기반 구성과 이후 렌더러 재구성 계획을 안내하며, 계획한 폴더 구조를 완료된 구현으로 세지 않는다.

## 자료를 읽는 순서

1. **결과·Demo:** 이미지·출력 결과와 구현 흐름을 함께 확인한다.
2. **예제 README·ExampleDocs:** 실행 진입점과 코드 위치를 확인한다.
3. **Topic·검증 기록:** 상세 문서에 연결된 개념 설명과 실제 확인 조건을 확인한다.

문서 종류별 전체 경로는 [문서 탐색](README.md)에서 찾는다. 기존 운영 인덱스와 검증 상태는 이 목록에 복제하지 않는다.

[프로젝트 README로 돌아가기](../../README.md) · [목록 위로](#바로-찾기)
