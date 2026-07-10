# 07 Modeling Step2 DrawingNormals

## 목적

box mesh의 vertex normal을 별도 line mesh로 시각화하는 예제입니다. Step1의 solid/wireframe 전환 위에 normal debug view를 추가해서, mesh가 가진 surface normal이 lighting과 geometry 이해에 어떤 역할을 하는지 확인합니다.

## 핵심 키워드

| Keyword | 설명 |
| --- | --- |
| Normal vector | 표면의 방향을 나타내는 벡터이며 lighting 계산과 debug visualization의 기준입니다. |
| Normal line mesh | 원래 mesh와 별도로 normal 방향을 선분으로 그리기 위한 보조 mesh입니다. |
| `Mesh` | vertex/index buffer, constant buffer, index count를 묶어 draw 대상 단위로 관리하는 구조입니다. |
| `texcoord.x` flag | normal line의 시작점과 끝점을 구분하기 위해 `0` 또는 `1`로 사용합니다. |
| `NormalVertexShader` | 시작점은 그대로 두고 끝점은 normal 방향으로 `scale`만큼 이동시킵니다. |
| `Draw Normals` toggle | ImGui에서 normal line 표시 여부를 전환합니다. |

## 구현 흐름

1. `GeometryGenerator::MakeBox()`로 box mesh 데이터를 만듭니다.
2. 원래 box 렌더링용 `m_mesh`를 생성하고 vertex/index buffer를 연결합니다.
3. 각 vertex를 두 번 복제해 normal line의 시작점과 끝점을 구성합니다.
4. 시작점 vertex는 `texcoord.x = 0`, 끝점 vertex는 `texcoord.x = 1`로 표시합니다.
5. `NormalVertexShader`가 `texcoord.x`와 `scale`을 이용해 끝점을 normal 방향으로 이동시킵니다.
6. 기본 mesh를 먼저 그리고, `m_drawNormals`가 켜져 있으면 normal line mesh를 추가로 그립니다.

## 핵심 코드

```cpp
v.texcoord.x = 0.0f;
normalVertices.push_back(v);

v.texcoord.x = 1.0f;
normalVertices.push_back(v);
```

```hlsl
float t = input.texcoord.x;
pos.xyz += output.normalWorld * t * scale;
```

```cpp
if (m_drawNormals)
{
    m_context->VSSetShader(m_normalVertexShader.Get(), 0, 0);
    m_context->PSSetShader(m_normalPixelShader.Get(), 0, 0);
    m_context->DrawIndexed(m_normalLines->m_indexCount, 0, 0);
}
```

## Archive Notes

- Raw reference: `C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step2_DrawingNormals`
- Related raw memo:
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\무제 1.md`
- Included assets:
  - `crate2_diffuse.png`
  - `wall.jpg`
- Included new files:
  - `Mesh.h`
  - `NormalVertexShader.hlsl`
  - `NormalPixelShader.hlsl`
- Excluded:
  - `.vs/`
  - generated folder `07_Model.d96a91f4/`
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

Visual Studio에서 Debug x64와 Release x64를 각각 빌드/실행하고, box 위에 normal line이 표시되는지와 `Draw Normals`, `Normal scale` UI가 동작하는지 확인합니다.
