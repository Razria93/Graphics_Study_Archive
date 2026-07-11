# 04 Rasterization Step6 ShadersConcept

## 목적

software rasterizer 안에서 vertex shader와 pixel shader 역할을 함수로 분리해, programmable graphics pipeline의 기본 구조를 이해하기 위한 예제입니다.

## 핵심 키워드

- Vertex shader
- Pixel shader
- Shader constants
- Vertex attributes
- Shader input/output
- UV interpolation
- Barycentric interpolation
- Depth buffer

## 구현 흐름

1. `Mesh`가 square geometry, color, UV를 생성하고 buffer로 복사합니다.
2. `Rasterization::Render()`가 mesh별 `scale`, `rotationZ`, `translation`을 shader constants에 설정합니다.
3. 각 vertex는 `VSInput`으로 묶여 `MyVertexShader()`를 통과합니다.
4. vertex shader output의 position, color, UV가 rasterization stage로 전달됩니다.
5. triangle 내부 픽셀 후보마다 color, UV, depth를 barycentric weight로 보간합니다.
6. depth test를 통과한 fragment만 `MyPixelShader()`로 color를 결정합니다.

## 핵심 코드

```cpp
struct Constants {
    vec3 scale = vec3(1.0f);
    vec3 translation = vec3(0.0f);
    float rotationZ = 0.0f;
} constants;
```

mesh마다 공통으로 적용되는 변환 값을 shader constants처럼 다룹니다.

```cpp
VSOutput MyVertexShader(const VSInput vsInput) {
    VSOutput vsOutput;

    vec3 transformed = vsInput.position * constants.scale;
    transformed = RotateAboutZ(transformed, constants.rotationZ);
    transformed += constants.translation;

    vsOutput.position = transformed;
    vsOutput.color = vsInput.color;
    vsOutput.uv = vsInput.uv;

    return vsOutput;
}
```

vertex shader 역할을 하는 함수입니다. archive에서는 raw의 constants가 실제 vertex transform에 연결되도록 정리했습니다.

```cpp
PSInput psInput;
psInput.color = color;
psInput.uv = uv;

pixels[pixelIndex] = MyPixelShader(psInput);
```

pixel shader 역할을 하는 함수로 fragment color 결정을 분리합니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/source-comments.md`에 분리했습니다.
- raw의 `Constants`는 mesh별로 설정되지만 `MyVertexShader()`에서 사용되지 않아 회전 animation이 결과에 반영되지 않았습니다.
- archive에서는 shader concept 설명 목적에 맞게 `scale`, `rotationZ`, `translation`을 vertex shader 단계에 적용했습니다.
- ImGui frame 관련 주석 처리 코드는 제거하고 기본 실행 루프만 유지했습니다.

## 실행 결과

- Build/run status: 성공
- 확인 내용: MSBuild Debug x64, Release x64 성공. 사용자 Debug/Release 실행 확인 완료
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 내부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
