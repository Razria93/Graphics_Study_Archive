# Light Types

## 목적

Directional, Point와 Spot Light가 surface-to-light vector와 세기 범위를 어떻게 정의하는지 설명한다. 같은 shading model을 사용해도 Light의 위치, 방향, 거리 감쇠와 cone factor에 따라 fragment에 도달하는 Light strength가 달라지는 구조를 구분한다.

## 책임 범위

- 위치가 없는 Directional Light와 위치를 가진 Point·Spot Light의 차이를 설명한다.
- Point·Spot Light의 distance attenuation을 설명한다.
- Spot Light의 방향 convention과 cone factor를 설명한다.
- Ambient·diffuse·specular 및 half-vector 계산은 [Phong And Blinn-Phong](PhongAndBlinnPhong.md)으로 위임한다.
- Step10 고유 함수, parameter와 UI는 [Step10 Example](../../../Part2_Chapter04/04_Rasterization_Step10_Lights/README.md)으로 위임한다.
- 구현 흐름과 시각 비교는 [Step10 상세 Demo](../../03_Demos/Part2_Chapter04/10_Lights.md)로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.
- GLM transform과 결합한 CPU Light 구현은 [Chapter05 Step2 Example](../../../Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md)과 [상세 Demo](../../03_Demos/Part2_Chapter05-08/05_LightsGLM.md)로 위임한다.

## 핵심 개념

### Directional Light

Directional Light는 모든 surface에 같은 방향에서 평행하게 도달하는 원거리 광원을 근사한다. 위치와 거리를 사용하지 않고 저장된 Light 진행 방향의 반대를 surface-to-light vector로 사용하므로 같은 normal을 가진 surface는 world position과 관계없이 같은 입사 방향을 받는다.

Directional Light의 세기는 거리에 따라 줄어들지 않는다. 태양처럼 scene 크기에 비해 매우 먼 광원을 단순화할 때 유용하지만 실제 면적, angular size와 shadow softness는 별도 모델이 필요하다.

### Point Light And Distance Attenuation

Point Light는 world position을 가지며 각 fragment에서 Light position으로 향하는 vector를 새로 계산한다. 이 vector의 길이가 거리이고 정규화한 결과가 surface-to-light 방향이므로 같은 face 안에서도 입사 방향과 highlight 위치가 변한다.

Distance attenuation은 거리가 증가할수록 Light strength를 줄인다. 물리 기반 inverse-square attenuation을 사용할 수도 있지만 학습 예제는 `fallOffStart`까지 세기를 유지하고 `fallOffEnd`에서 0이 되는 선형 구간을 사용할 수 있다. 시작과 끝이 같거나 순서가 뒤집힌 경우를 피하도록 parameter invariant를 별도로 관리한다.

### Spot Light And Cone Factor

Spot Light는 Point Light의 위치와 distance attenuation에 방향성 cone을 추가한다. Light에서 surface로 향하는 방향과 저장된 Light 진행 방향의 내적이 cone 중심 정렬도를 나타내며, 음수 영역을 제한한 뒤 거듭제곱하면 중심은 밝고 바깥쪽은 빠르게 어두워지는 factor를 얻는다.

`spotPower`가 커질수록 밝은 중심이 좁고 집중된다. 값이 0이면 0이 아닌 내적의 거듭제곱 결과가 1에 가까워져 Spot이 Point와 구분되지 않을 수 있다. 방향 vector의 의미가 light-to-surface인지 surface-to-light인지 구현 전반에서 같은 convention을 유지해야 한다.

## 한계

- Light type 분류만으로 물리적인 area light, emissive geometry와 indirect lighting을 표현하지 않는다.
- 선형 distance attenuation은 inverse-square energy falloff를 근사하지 않는다.
- 단일 `spotPower`는 명시적인 inner·outer cone angle과 smooth transition을 제공하지 않는다.
- Shadow, multiple light accumulation, gamma correction, tone mapping과 physically based BRDF는 별도 문제로 다룬다.

## 관련 문서

- Example: [Step10 Lights README](../../../Part2_Chapter04/04_Rasterization_Step10_Lights/README.md)
- Example: [Chapter05 Step2 Lights(GLM) README](../../../Part2_Chapter05-08/05_AffineTransformations_Step2_Lights%28GLM%29/README.md)
- Related Topic: [Phong And Blinn-Phong](PhongAndBlinnPhong.md)
- Verification: [`Docs/02_Verification/Part2_Chapter04/verification-index.md`](../../02_Verification/Part2_Chapter04/verification-index.md)
- Demo: [`Docs/03_Demos/Part2_Chapter04/10_Lights.md`](../../03_Demos/Part2_Chapter04/10_Lights.md)
- Demo: [Chapter05 Step2 Lights(GLM) Demo](../../03_Demos/Part2_Chapter05-08/05_LightsGLM.md)
