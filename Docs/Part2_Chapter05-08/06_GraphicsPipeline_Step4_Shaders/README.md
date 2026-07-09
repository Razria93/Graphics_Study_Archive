# 06 GraphicsPipeline Step4 Shaders

## 목적

vertex shader와 pixel shader 사이에서 전달되는 data 흐름을 확장하는 예제입니다. Step3의 model/view/projection transform 위에 texture coordinate와 pixel shader constant buffer를 추가해, shader stage별 입력/출력과 register binding을 확인합니다.

## 핵심 키워드

- HLSL
- vertex shader
- pixel shader
- shader semantics
- `TEXCOORD`
- `cbuffer`
- shader register
- pixel shader constant buffer
- `PSSetConstantBuffers`
- input layout

## 구현 흐름

1. vertex 구조에 position, color, texture coordinate를 포함합니다.
2. input layout에 `POSITION`, `COLOR`, `TEXCOORD` semantic을 연결합니다.
3. vertex shader에서 model/view/projection 변환을 수행하고 color/texcoord를 pixel shader로 넘깁니다.
4. pixel shader는 `PSConstantBuffer`와 interpolated texcoord를 사용해 화면 영역별 색을 결정합니다.
5. CPU 쪽에서는 vertex shader constant buffer와 pixel shader constant buffer를 각각 갱신합니다.
6. draw 전에 `VSSetConstantBuffers()`와 `PSSetConstantBuffers()`로 shader stage별 constant buffer를 연결합니다.

## 핵심 코드

```hlsl
cbuffer PSConstantBuffer : register(b1)
{
    float4 leftColor;
    float4 rightColor;
    float xSplitPoint;
};
```

pixel shader 전용 constant buffer입니다. shader register를 명시해 vertex shader constant buffer와 별도의 binding slot을 사용합니다.

```cpp
m_context->PSSetConstantBuffers(1, 1, p_constantBuffer.GetAddressOf());
```

CPU에서 만든 constant buffer를 pixel shader stage에 연결합니다. 이 예제는 같은 draw call 안에서 vertex shader와 pixel shader가 서로 다른 constant buffer를 사용하는 흐름을 보여줍니다.

## Archive 반영 메모

- raw source의 장문 학습 주석과 TODO/link 메모는 source에서 제거하고 `local/Part2_Chapter05-08/06_GraphicsPipeline_Step4_Shaders/source-comments.md`로 분리했습니다.
- `.vs/`, `x64/`, 중간 build folder, `.user`, `imgui.ini`, `.clang-format`는 archive에 포함하지 않았습니다.
- raw의 `ColorVertexShader.cso`, `ColorVertexShader.asm`은 build 산출물/reference 파일로 보고 archive에 포함하지 않았습니다.
- shader 파일은 `fxc` 호환을 위해 UTF-8 no BOM으로 저장했습니다.
- 외부 asset은 없습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 source 구조, shader, ImGui/vcpkg dependency, 강의 기반 구조 재현 정도를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter05-08 manifest](../../_repo/manifests/Part2_Chapter05-08.md)
