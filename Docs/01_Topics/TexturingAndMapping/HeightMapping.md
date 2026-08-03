# Height Mapping

## 목적

Height texture의 scalar 값을 vertex displacement 또는 shading offset으로 해석하는 방식과 normal mapping과의 차이를 설명한다.

## 책임 범위

이 문서는 vertex displacement를 중심으로 height sample, scale과 geometry density의 관계를 다룬다. 개별 shader 구현은 Example README와 상세 Demo로 위임한다.

## 핵심 개념

### Normal-direction displacement

Vertex displacement는 UV에서 읽은 height를 surface normal 방향 이동량으로 바꾼다. 결과가 실제 clip-space position에 반영되므로 normal mapping과 달리 silhouette도 변할 수 있다.

```cpp
// Pseudo C++: normal-direction displacement
float height = heightTexture.SampleLevel(sampler, uv, 0).r;
position += normal * height * heightScale;
```

### Geometry density

Texture에 세밀한 값이 있어도 vertex가 충분하지 않으면 변형이 거칠게 보인다. Tessellation을 결합하면 camera distance나 height 변화에 맞춰 vertex density를 높일 수 있지만, 이 예제는 고정 mesh density만 사용한다.

## 한계

- Displacement 후 normal을 다시 계산하지 않으면 lighting과 geometry가 완전히 일치하지 않을 수 있다.
- Height scale이 지나치게 크면 self-intersection과 과도한 silhouette 변형이 발생한다.
- Parallax mapping과 ray marching은 별도 기법이다.

## 관련 문서

- [Normal Mapping And Tangent Space](NormalMappingAndTangentSpace.md)
- [Tessellation Pipeline](../ModelingAndGeometry/TessellationPipeline.md)
- [Example README](../../../Part3_Chapter10-13/11_TexturingTechniques_Step3_HeightMapping/README.md)
- [Docs/03_Demos](../../03_Demos/Part3_Chapter10-13/11_03_HeightMapping.md)
- [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
