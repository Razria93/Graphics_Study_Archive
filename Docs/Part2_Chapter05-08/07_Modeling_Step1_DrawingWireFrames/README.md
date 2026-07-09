# 07 Modeling Step1 DrawingWireFrames

## 목적

`GeometryGenerator`로 절차적 mesh 데이터를 만들고, 동일한 box mesh를 solid/wireframe rasterizer state로 전환해 그리는 예제입니다. Part2의 이전 pipeline 예제에서 다룬 texture, lighting, constant buffer 흐름을 유지하면서 modeling 단계의 첫 단추로 `MeshData`, vertex/index buffer, rasterizer state 전환을 확인합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| `MeshData` | `vertices`와 `indices`를 묶어 mesh 생성 결과를 전달하는 구조 |
| `GeometryGenerator::MakeBox()` | box의 위치, normal, texcoord, index 데이터를 생성하는 함수 |
| Vertex/Index Buffer | `MeshData`를 GPU input assembler가 읽을 수 있는 buffer로 업로드 |
| Rasterizer State | triangle을 pixel 후보로 변환할 때 fill/cull/depth clip 방식을 결정 |
| `D3D11_FILL_SOLID` / `D3D11_FILL_WIREFRAME` | solid 면 렌더링과 wireframe 렌더링 모드 |
| `RSSetState()` | 현재 draw call에 사용할 rasterizer state를 context에 바인딩 |
| ImGui toggle | `Wireframe` checkbox로 solid/wireframe 상태를 즉시 전환 |

## 구현 흐름

1. `GeometryGenerator::MakeBox()`가 box mesh의 vertex/index 데이터를 생성합니다.
2. `ExampleApp::Initialize()`가 `MeshData`를 이용해 vertex buffer와 index buffer를 만듭니다.
3. `AppBase::Initialize()`가 solid용 rasterizer state와 wireframe용 rasterizer state를 각각 생성합니다.
4. `ExampleApp::Render()`가 `m_drawAsWire` 값에 따라 `RSSetState()`로 사용할 rasterizer state를 선택합니다.
5. `UpdateGUI()`의 `Wireframe` checkbox로 runtime에서 렌더링 모드를 바꿉니다.

## 핵심 코드

```cpp
rastDesc_Fill.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
rastDesc_Wire.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
```

```cpp
if (m_drawAsWire)
{
    m_context->RSSetState(m_wireRasterizerSate.Get());
}
else
{
    m_context->RSSetState(m_solidRasterizerSate.Get());
}
```

```cpp
MeshData meshData = GeometryGenerator::MakeBox();
ImGui::Checkbox("Wireframe", &m_drawAsWire);
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step1_DrawingWireFrames`
- Related raw memo:
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\무제 1.md`
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
- Excluded:
  - `.clang-format`
  - `.vcxproj.user`
  - `imgui.ini`
  - `x64/`, build output
- Asset public readiness: 검토 필요
- Source comments: raw 장문 학습 주석은 source에서 제거하고 local-only 문서로 분리했습니다.

## 확인 상태

| 항목 | 상태 |
| --- | --- |
| Code split | 완료 |
| Build Debug x64 | 미확인 |
| Build Release x64 | 미확인 |
| Run Debug/Release | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## 다음 확인

Visual Studio에서 Debug x64와 Release x64를 각각 빌드/실행하고, solid/wireframe 전환이 정상적으로 보이는지 확인합니다.
