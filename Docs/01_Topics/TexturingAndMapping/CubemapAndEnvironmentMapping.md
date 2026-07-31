# Cubemap And Environment Mapping

## 목적

Cubemap은 하나의 위치를 둘러싼 환경을 +X, -X, +Y, -Y, +Z, -Z의 여섯 2D image로 표현한다. Sampling할 때는 3D direction의 dominant axis로 face를 고르고, 나머지 두 성분을 해당 face의 2D UV로 투영한다.

Environment mapping은 이 direction lookup을 background, reflection, refraction 또는 image-based lighting에 활용하는 기법을 포괄한다. Cubemap sampling 자체와 그 결과를 어떤 lighting model에 사용하는지는 구분한다.

## 책임 범위

이 문서는 일반적인 cubemap direction-to-face mapping, face-local filtering과 environment mapping의 활용 범위를 다룬다. Step14의 실제 CPU 구현과 asset은 Example README로, 직접 확인한 실행 상태는 Verification으로, 시각 결과는 상세 Demo로 위임한다.

## 핵심 개념

### Direction To Face

Normalized direction `d = (x, y, z)`에서 `|x|`, `|y|`, `|z|` 중 가장 큰 값을 major axis로 선택한다. Major axis의 부호가 positive/negative face를 결정하고, 나머지 두 성분을 major component의 절댓값으로 나누어 face-local 좌표를 만든다.

```text
SampleCubemap(direction)
{
    axis = SelectDominantAxis(abs(direction));
    face = SelectFace(axis, Sign(direction[axis]));
    local = ProjectRemainingComponents(direction, axis);
    uv = local * 0.5 + 0.5;
    return SampleFace(face, uv);
}
```

각 face image의 저장 orientation에 따라 U/V 부호 규칙이 달라질 수 있다. 구현은 사용하는 cubemap asset의 convention과 일치해야 하며, face 중심뿐 아니라 경계와 위아래 방향도 확인해야 한다.

### Filtering And Seams

Face-local bilinear filtering은 선택한 한 face의 네 texel만 보간한다. UV를 face 내부로 clamp하면 구현은 단순하지만 경계에서 인접 face의 texel을 함께 사용하지 못해 seam이 나타날 수 있다.

GPU cubemap resource는 direction을 직접 받아 face 경계를 처리할 수 있다. CPU에서 여섯 개의 독립 2D image를 sampling하는 경우에는 orientation, edge filtering과 mip level 처리를 별도로 설계해야 한다.

### 활용 범위

- Scene background
- Reflective surface의 reflected direction lookup
- Refractive surface의 refracted direction lookup
- Diffuse irradiance와 specular prefiltered environment

단순 background lookup은 environment lighting과 같지 않다. Lighting에 사용하려면 radiance representation, roughness별 prefilter, BRDF 결합과 color-space 처리가 추가로 필요하다.

## 한계

- Cubemap asset마다 다른 face orientation과 파일명 convention을 하나로 고정하지 않는다.
- GPU API별 cubemap resource 생성과 sampler 세부 설정은 다루지 않는다.
- Diffuse irradiance, specular prefilter와 BRDF integration의 수식은 포함하지 않는다.
- HDR encoding, exposure와 tone mapping은 포함하지 않는다.

## 관련 문서

- Example: [Step14 CubeEnvironment README](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/14_CubeEnvironment.md`](../../03_Demos/Part1_Chapter03/14_CubeEnvironment.md)
- Related Topic: [Texture Sampling](TextureSampling.md)
