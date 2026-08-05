# Tessellation Pipeline

## 목적

DirectX11의 hull shader, fixed-function tessellator와 domain shader가 control point patch를 세분하는 책임을 설명한다.

## 책임 범위

Patch factor와 stage 흐름을 다룬다. Chapter10 Step5의 mode UI와 코드는 Example README로, 구현 결과는 상세 Demo로, 실행 사실은 Verification으로 위임한다.

## 개념 흐름

1. Input assembler가 control point patch를 전달한다.
2. Hull shader가 control point와 patch constant를 출력한다.
3. Tessellator가 partitioning 규칙과 factor로 domain sample을 생성한다.
4. Domain shader가 sample을 world·view·projection 공간으로 변환한다.

## 핵심 개념

### Manual과 Distance Adaptive

Manual mode는 UI의 edge와 inside factor를 hull shader에 직접 전달한다. Distance Adaptive mode는 patch center와 camera distance를 정규화해 가까울수록 큰 factor를 선택한다.

```cpp
// Pseudo C++: distance adaptive factor
auto range = Max(distanceMax - distanceMin, epsilon);
auto ratio = Saturate((distanceMax - distance) / range);
auto factor = Lerp(minFactor, maxFactor, ratio);
```

두 mode는 같은 tessellation pipeline을 사용하지만 factor의 source가 다르므로 UI와 문서에서 명시적으로 구분한다.

### Partitioning과 domain evaluation

Partitioning mode는 factor에서 실제 domain sample을 만드는 규칙을 정한다. Domain shader는 생성된 UV domain 좌표로 control point를 보간하고 최종 transform을 적용한다.

## 데모 연결

Chapter10 Step5는 Manual factor 8의 wireframe 결과와 Distance Adaptive 사용자 확장을 분리해 연결한다.

## 한계

- Factor가 클수록 primitive 수와 rasterization 비용이 증가한다.
- Integer partitioning은 factor 변화가 단계적으로 보일 수 있다.
- Distance만 사용하는 adaptive 방식은 screen-space error나 silhouette 복잡도를 고려하지 않는다.

## 관련 문서

- [Shader Stage](../DirectX11Pipeline/ShaderStage.md)
- [Example README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/README.md)
- [Verification](../../../Docs/02_Verification/Part3_Chapter10-13/verification-index.md)
- [Detailed Demo](../../../Docs/03_Demos/Part3_Chapter10-13/10_05_Tessellation.md)
