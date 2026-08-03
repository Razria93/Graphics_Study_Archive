# Geometry Shader And Billboards

## 목적

Geometry shader가 input primitive를 새로운 primitive stream으로 확장하는 구조와 camera-facing billboard 연결을 설명한다.

## 책임 범위

Primitive amplification, strip 경계와 billboard orientation을 다룬다. 예제 고유 코드는 Example README로, 구현 흐름과 visual은 상세 Demo로, 검증 사실은 Verification으로 위임한다.

## 개념 흐름

Point input을 geometry shader가 quad로 확장하고 pixel shader가 texture array를 sampling한다.

## 핵심 개념

### Primitive 확장

`POINTLIST`의 각 point는 geometry shader invocation 하나가 된다. Shader는 view 공간에서 네 corner를 만들고 `TriangleStream`에 strip 순서로 append한 뒤 `RestartStrip()`으로 다음 primitive와 경계를 분리한다.

```cpp
// Pseudo C++: point를 quad strip으로 확장
for (auto corner : StripOrderedCorners)
{
    stream.Append(Project(point + corner));
}

stream.RestartStrip();
```

### Billboard orientation

Billboard는 camera의 right와 up basis를 사용하거나 view transform 이후의 평면에서 corner를 확장한다. 두 방식 모두 camera 방향 변화에도 quad가 화면을 향하게 만드는 것이 목적이다.

### Texture array와 primitive ID

여러 billboard variant는 `Texture2DArray`에 묶을 수 있다. Geometry shader가 전달한 primitive ID를 array slice index로 사용하면 draw call을 나누지 않고 다른 texture를 선택한다.

## 데모 연결

Chapter10 Step1은 최소 quad strip, Step2는 camera-facing texture billboard, Step4는 procedural animated billboard를 보여준다.

## 한계

- Geometry shader 확장은 구현이 단순하지만 대량 particle에서는 compute 또는 instancing 방식과 비교가 필요하다.
- Transparent billboard는 별도의 depth sorting과 blend 정책이 필요하다.
- Fireball처럼 shader 내부 animation을 사용하는 경우 time과 primitive ID가 동적 차이를 만든다.

## 관련 문서

- [Shader Stage](../DirectX11Pipeline/ShaderStage.md)
- [Vertex And Face Normals](VertexAndFaceNormals.md)
- [Example README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/README.md)
- [Verification](../../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [Detailed Demo](../../../Docs/03_Demos/Part3_Chapter10-13/10_01_GeometryShader.md)
