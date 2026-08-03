# Spherical Texture Mapping

## 목적

Sphere surface의 3D 방향을 2D texture coordinate로 변환하고, 주기적인 longitude 경계와 pole이 mesh topology에 미치는 영향을 설명한다.

## 책임 범위

- 원점 중심 sphere의 longitude·latitude 기반 UV parameterization을 설명한다.
- U seam에서 같은 위치에 서로 다른 texture coordinate가 필요한 이유를 설명한다.
- Pole의 위치 중복과 U 선택이 만드는 한계를 설명한다.
- Texture filter·address mode와 GPU sampling은 [Texture Sampling](TextureSampling.md)으로 위임한다.
- 개별 mesh 생성과 seam vertex 복제 코드는 Example README와 `Docs/03_Demos` 상세 Demo로 위임한다.
- Build/run/capture 사실은 `Docs/02_Verification`으로 위임한다.

## 핵심 개념

### 방향에서 UV로 변환

원점 중심 sphere의 위치 `p=(x,y,z)`를 radius로 정규화하면 surface normal과 같은 방향 벡터를 얻는다. Longitude는 XZ plane의 방향을 구분해야 하므로 `atan2(z,x)`를 사용하고, latitude는 Y 성분과 radius의 비율에서 `acos(y/r)`로 구한다.

```text
theta = atan2(z, x)
if theta < 0:
    theta += 2π

phi = acos(y / r)

u = theta / 2π
v = phi / π
```

이 변환에서 U는 수평 방향으로 주기적이고 V는 north pole에서 south pole까지 단조롭게 변한다.

### Longitude seam

U=0과 U=1은 texture에서 서로 다른 좌표지만 sphere에서는 같은 longitude를 나타낸다. 하나의 triangle이 이 경계를 가로지르며 U 값을 그대로 보간하면 texture 중앙을 횡단하는 잘못된 gradient가 생긴다.

일반적인 해결은 seam을 공유하는 위치를 복제하고 한쪽 triangle에는 U=0, 반대쪽에는 U=1을 준다. Geometry position과 normal은 같아도 texture coordinate가 다르므로 seam에서는 vertex 공유보다 attribute 연속성이 우선한다.

### Pole과 parameterization 한계

Pole에서는 longitude가 하나로 정해지지 않는다. 같은 pole position이 주변 triangle의 U에 맞춰 여러 번 복제될 수 있으며, 별도 pole 보정이 없으면 triangle별 U 선택에 따라 압축이나 비틀림이 보일 수 있다.

Latitude·longitude mapping은 구현이 단순하고 2:1 equirectangular texture와 직접 대응하지만 면적과 shape distortion을 피할 수 없다. Equal-area mapping, cubemap과 tangent-space chart는 다른 목적의 parameterization이다.

## 한계

- 이 문서는 equirectangular spherical mapping의 기본 관계만 다룬다.
- Shared indexed mesh의 seam split algorithm과 vertex cache 최적화는 다루지 않는다.
- Tangent·bitangent 생성, normal mapping과 texture LOD는 다루지 않는다.
- Pole correction의 구체적인 정책은 mesh topology와 visual 요구에 따라 Example 책임으로 둔다.

## 관련 문서

- [Chapter07 Step8 SphereMapping Example](../../../Part2_Chapter05-08/07_Modeling_Step8_SphereMapping/README.md)
- [Chapter07 Step8 SphereMapping Demo](../../03_Demos/Part2_Chapter05-08/07_08_SphereMapping.md)
- [Texture Sampling](TextureSampling.md)
- [Procedural Primitive Generation](../ModelingAndGeometry/ProceduralPrimitiveGeneration.md)
- [Vertex And Face Normals](../ModelingAndGeometry/VertexAndFaceNormals.md)
- [Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
