# Step6 ShadersConcept Demo

## 목적

Step6는 CPU software rasterizer의 transform과 fragment color 계산을 vertex stage와 pixel stage의 입출력 계약으로 분리한다. 회전하는 white square는 CPU vertex stage가 position을 갱신하고 rasterizer와 CPU pixel stage를 거쳐 framebuffer를 만드는 end-to-end 결과를 보여준다.

## 책임 범위

- CPU `VSInput`·`VSOutput`과 `MyVertexShader()`의 transform 책임을 설명한다.
- Vertex output을 buffer에 기록하고 triangle rasterization으로 전달하는 흐름을 설명한다.
- Barycentric attribute 보간과 CPU `MyPixelShader()` 호출을 연결한다.
- CPU framebuffer와 DirectX11 HLSL presentation 경계를 설명한다.
- 매 frame rotation 갱신이 결과 화면에 미치는 영향을 설명한다.
- 일반적인 shader stage 계약은 [Shader Stage](../../01_Topics/DirectX11Pipeline/ShaderStage.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 결과 미리보기

![Step6 ShadersConcept 전체 창 capture](../../_assets/captures/part2_chapter04_06_shaders_concept.png)

전체 창 screenshot은 vertex stage rotation이 적용된 대각선 상태의 white square를 보여준다. Tracked capture와 selected local video는 기술 검수와 사용자 시각 검수를 완료했다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| Mesh 입력 | 네 position, white color, UV와 두 indexed triangle로 구성한 square |
| Vertex stage 입력 | Position, color와 UV |
| Vertex stage 출력 | Scale·rotation·translation이 적용된 position, 전달된 color와 UV |
| Rasterizer 출력 | Covered pixel별 affine color, UV와 depth |
| Pixel stage 출력 | 보간된 color를 alpha `1.0`과 결합한 RGBA |
| CPU framebuffer | 1280×960 RGBA32F pixel buffer |
| 화면 출력 | CPU framebuffer texture를 sampling한 DirectX11 full-screen quad |

## 구현 흐름

1. Square의 position, index, white color와 UV를 mesh buffer에 저장한다.
2. Frame마다 mesh rotation을 `0.005` radian 증가시킨다.
3. Mesh transform을 CPU vertex stage가 참조하는 `Constants`에 복사한다.
4. 각 vertex의 position을 scale, Z rotation과 translation 순서로 변환한다.
5. Vertex output position, color와 UV를 rasterizer buffer에 기록한다.
6. Triangle coverage를 계산하고 color, UV와 depth를 barycentric weight로 보간한다.
7. Depth test를 통과한 fragment input을 CPU pixel stage에 전달한다.
8. CPU pixel stage가 반환한 color를 framebuffer에 기록한다.
9. CPU framebuffer를 dynamic texture로 upload하고 HLSL presentation quad로 표시한다.

## 핵심 구현

### CPU Vertex Shader Contract

CPU vertex stage는 position, color와 UV를 구조화된 입력으로 받는다. Position에는 scale, Z rotation과 translation을 적용하고 color와 UV는 다음 단계로 전달한다.

#### Vertex Stage 의사코드

```cpp
// Pseudo C++: per-vertex transform과 attribute 전달
VertexOutput RunVertexStage(VertexInput input, Constants constants)
{
    VertexOutput output;
    output.position = ScaleRotateTranslate(input.position, constants);
    output.color = input.color;
    output.uv = input.uv;
    return output;
}
```

- [CPU vertex shader 입출력 계약과 transform](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L21-L45)
- [Mesh transform constant 전달](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L151-L154)

### Rasterizer Stage Handoff

각 mesh vertex는 CPU vertex stage를 통과한 뒤 position, color와 UV buffer에 기록된다. Triangle 조립은 이 post-stage buffer와 index buffer를 사용하므로 원본 mesh data와 transformed data의 책임이 분리된다.

- [Vertex input 조립과 output buffer 기록](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L156-L173)
- [Post-stage index 기반 triangle rasterization](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L175-L177)

### CPU Pixel Shader Contract

Rasterizer는 covered pixel마다 color, UV와 depth를 affine 보간한다. Depth test를 통과하면 color와 UV로 `PSInput`을 만들고 CPU pixel stage가 최종 RGBA를 반환한다. 현재 구현은 UV를 전달하지만 color만 사용한다.

#### Pixel Stage 의사코드

```cpp
// Pseudo C++: interpolated fragment의 pixel stage 호출
void ShadeCoveredPixel(Barycentric weights, Pixel pixel)
{
    FragmentInput input;
    input.color = InterpolateColor(weights);
    input.uv = InterpolateUv(weights);

    if (InterpolateDepth(weights) < depthBuffer[pixel])
    {
        colorBuffer[pixel] = RunPixelStage(input);
    }
}
```

- [Barycentric color·UV·depth 보간](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L121-L130)
- [보간된 attribute의 pixel shader 입력 변환](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L132-L140)
- [CPU pixel shader color 출력](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L47-L54)

### CPU Framebuffer Presentation

Step6의 학습용 vertex와 pixel stage는 C++에서 실행된다. `Example::Update()`는 CPU framebuffer를 RGBA32F dynamic texture에 복사한다. 실제 HLSL vertex shader는 full-screen quad position과 UV를 전달하고 pixel shader는 CPU 결과 texture만 sampling한다.

- [CPU framebuffer와 dynamic texture upload](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Example.cpp#L10-L21)
- [Presentation HLSL runtime compile](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Example.cpp#L24-L77)
- [Full-screen presentation draw](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Example.cpp#L217-L235)
- [Full-screen quad position과 UV 전달](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/VertexShader.hlsl#L1-L18)
- [CPU 결과 texture sampling](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/PixelShader.hlsl#L1-L10)

### Per-Frame Transform Update

`Update()`는 frame마다 square의 `rotationZ`를 `0.005` radian 증가시킨다. Video 후보는 이 변화가 CPU vertex stage를 통해 연속적인 square 회전으로 나타나는 결과를 보여준다.

- [Per-frame mesh rotation 갱신](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L181-L184)
- [Update·render·present loop](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/main.cpp#L54-L62)

## 시각 결과

Screenshot 후보의 white square는 원본 axis-aligned vertex가 CPU vertex stage의 Z rotation을 통과한 결과다. Black background와 단일 white mesh만 사용하므로 stage 분리 자체를 화면 색상으로 구분하지는 않지만 transformed geometry와 최종 framebuffer 출력이 정상임을 확인한다.

7.8초 selected local video는 square가 끊김 없이 연속 회전하는 결과를 보여준다. 이 영상은 per-frame transform update의 증거이며 CPU/GPU stage 책임은 코드와 문서 설명으로 보완한다.

## 구현 범위와 한계

- CPU stage는 고정 C++ 함수이며 실제 GPU shader binary 또는 runtime binding을 모사하지 않는다.
- `Constants`는 전역 mutable state라서 일반적인 constant buffer lifetime을 재현하지 않는다.
- UV를 보간하지만 현재 CPU pixel stage에서 texture sampling에 사용하지 않는다.
- 모든 vertex color가 white라서 color interpolation 변화가 화면에서 드러나지 않는다.
- Attribute와 depth는 screen space에서 affine 보간하며 perspective correction은 포함하지 않는다.
- Rotation은 delta time과 분리되지 않아 frame rate에 따라 속도가 달라진다.
- Dynamic texture upload는 `Map()` 결과와 mapped `RowPitch` 차이를 별도로 처리하지 않는다.
- Shader file runtime load는 example working directory에 의존한다.

## 검증

- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-01 현재 확인
- Release x64 build/run: 성공, 2026-08-01 현재 확인
- Application title: `ComputerGraphics - Step6 ShadersConcept`
- Runtime shader compile: 성공
- Screenshot: 1282×992, 기술·사용자 시각 검수 완료
- Selected video: H.264 High, yuv420p, 1282×992, CFR 30 FPS, 7.8초, audio 없음, 전체 decode와 사용자 시각 검수 완료

## 관련 코드

- [CPU vertex shader 입출력 계약과 transform](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L21-L45)
- [Vertex output buffer와 triangle 조립](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L151-L177)
- [보간된 attribute의 pixel shader 입력 변환](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Rasterization.cpp#L121-L140)
- [CPU framebuffer의 dynamic texture upload](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Example.cpp#L10-L21)
- [Full-screen presentation shader 경로](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/Example.cpp#L217-L235)

## 관련 문서

- [Step6 ShadersConcept Example](../../../Part2_Chapter04/04_Rasterization_Step6_ShadersConcept/README.md)
- [Shader Stage](../../01_Topics/DirectX11Pipeline/ShaderStage.md)
- [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md)
- [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Demo Index](demo-index.md)
