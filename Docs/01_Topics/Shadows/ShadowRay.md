# Shadow Ray

## 목적

Surface point와 light 사이의 visibility를 별도 ray query로 판정하는 원리를 설명한다.

## 책임 범위

- Shadow ray의 역할과 구간을 설명한다.
- self-intersection을 줄이는 origin offset을 설명한다.
- point light까지의 거리와 blocker hit 거리를 비교하는 이유를 설명한다.
- 구체적인 예제 코드와 실행 결과는 Example README와 상세 Demo로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification`으로 위임한다.
- 구현 선택과 시각 결과는 `Docs/03_Demos`로 위임한다.

## 핵심 개념

### Light visibility

Primary ray가 surface를 찾은 뒤 hit point에서 light 방향으로 secondary ray를 보낸다. 이 shadow ray가 light에 도달하기 전에 다른 surface와 만나면 light는 가려지고, blocker가 없으면 직접광을 계산한다.

Point light의 shadow ray는 무한한 ray가 아니라 surface와 light 사이의 유한 구간을 검사해야 한다. 교점 거리가 light까지의 거리보다 짧을 때만 blocker로 인정해야 light 뒤의 object가 잘못 shadow를 만들지 않는다.

### Origin offset

부동소수점 오차 때문에 surface hit point에서 바로 시작한 shadow ray가 원래 surface와 다시 만날 수 있다. Hit point를 geometric normal 방향으로 작은 epsilon만큼 이동하면 이러한 self-intersection과 shadow acne를 줄일 수 있다.

고정 epsilon은 scene scale에 의존한다. 너무 작으면 acne가 남고 너무 크면 shadow가 object에서 떨어지는 peter-panning이 생길 수 있으므로 실제 장면에서 함께 검증한다.

### Lighting separation

Visibility는 light에서 직접 도달하는 diffuse와 specular 항에 적용한다. Ambient처럼 직접 light path를 사용하지 않는 근사 항은 별도로 유지할 수 있다.

## 한계

- Shadow ray 하나는 point light의 hard shadow를 만든다.
- Area light의 penumbra에는 여러 visibility sample이 필요하다.
- Geometric normal 기반 offset은 얇은 surface, back face와 큰 scale 차이에서 추가 처리가 필요할 수 있다.
- Ray-traced shadow와 rasterization의 shadow map은 visibility를 구하는 저장 공간과 오차 원인이 다르다.

## 관련 문서

- [Step8 Shadow Example](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow/README.md)
- [Step8 Shadow Demo](../../03_Demos/Part1_Chapter03/08_Shadow.md)
- [Step8 Shadow Square Example](../../../Part1_Chapter03/03_Raytracing_Step8_Shadow_Square/README.md)
- [Step8 Shadow Square Demo](../../03_Demos/Part1_Chapter03/08_ShadowSquare.md)
- [Part1 Chapter03 Verification](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Ray](../RayTracing/Ray.md)
- [Intersection](../RayTracing/Intersection.md)
- [Phong Shading](../LightingAndShading/PhongShading.md)
