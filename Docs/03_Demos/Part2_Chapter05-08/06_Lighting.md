# Chapter06 Step6 Lighting Demo

## 목적

Step6는 Step5A의 단일 textured point light를 Directional·Point·Spot Light 비교로 확장한다. 같은 geometry·texture·model·camera·material을 유지한 상태에서 Light type과 해당 고유 parameter만 바꿔 방향, 거리 감쇠와 cone factor의 차이를 확인한다.

## 책임 범위

- 세 Light type이 공유하는 Material·Light constant buffer와 Blinn-Phong 흐름을 설명한다.
- Directional의 일정한 방향, Point의 위치·거리 감쇠와 Spot의 추가 cone factor를 구분한다.
- Step5A의 단일 point-light 결과와 Step6의 Light type 비교 책임을 구분한다.
- 일반 texture sampling은 [Texture Sampling](../../01_Topics/TexturingAndMapping/TextureSampling.md)으로 위임한다.
- 일반 조명 이론은 [Phong And Blinn-Phong](../../01_Topics/LightingAndShading/PhongAndBlinnPhong.md)과 [Light Types](../../01_Topics/LightingAndShading/LightTypes.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

### Directional Light

![Chapter06 Step6 Directional Light](../../_assets/captures/part2_chapter06_06_lighting_directional.png)

### Point Light

![Chapter06 Step6 Point Light](../../_assets/captures/part2_chapter06_06_lighting_point.png)

### Spot Light

![Chapter06 Step6 Spot Light](../../_assets/captures/part2_chapter06_06_lighting_spot.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 공통 입력 | Generated 목재 PNG, box position·normal·UV, model·view·projection, material parameter |
| Directional | `direction=(0, 0, 1)`, 위치와 거리 감쇠 없음 |
| Point | `position=(0.75, 0.5, -1)`, `fallOffStart=0.5`, `fallOffEnd=4.0` |
| Spot | Point와 같은 위치·falloff, `direction=(-0.557, -0.371, 0.743)`, `spotPower=16` |
| Vertex stage | World position, inverse-transpose normal과 UV 전달 |
| Pixel stage | Ambient, Light type별 diffuse·Blinn-Phong specular, texture sample 결합 |
| 출력 | Directional의 넓은 방향 조명, Point의 위치 중심 조명, Spot의 응축된 cone 조명 |

## 구현 흐름

1. Face별 normal과 UV를 가진 indexed box와 generated 목재 texture를 준비한다.
2. Model matrix와 inverse-transpose normal matrix를 갱신한다.
3. 선택한 Light type의 공통 parameter를 pixel constant buffer에 기록하고 나머지 Light strength를 0으로 만든다.
4. Vertex shader가 projected position, world position, transformed normal과 UV를 전달한다.
5. Pixel shader가 ambient를 한 번 적용하고 Directional·Point·Spot 함수를 각각 호출한다.
6. 활성 Light 결과에 texture sample을 곱해 최종 color를 만든다.
7. 같은 scene에서 Light type만 전환해 방향·거리·cone 차이를 비교한다.

## 핵심 구현

### Light Type Selection And Buffer Update

CPU는 세 Light slot 중 선택한 type에만 UI 값을 복사하고 나머지 slot의 strength를 0으로 만든다. Point와 Spot의 falloff range는 끝값이 시작값보다 최소 `0.01` 크게 유지되도록 제한한다.

#### Light 선택 의사코드

```cpp
// Pseudo C++: 활성 Light 하나만 constant buffer에 반영
Light selected = ReadLightParametersFromUI();
selected.fallOffEnd = Max(selected.fallOffEnd,
                          selected.fallOffStart + 0.01);

for (int index = 0; index < LightTypeCount; ++index)
{
    lights[index] = index == selectedType ? selected : DisabledLight();
}
```

- [Light type 선택과 buffer 갱신](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/ExampleApp.cpp#L235-L250)
- [Light type과 parameter UI](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/ExampleApp.cpp#L294-L335)

### Directional·Point·Spot Shading

세 Light는 같은 Blinn-Phong material 함수를 공유한다. Directional은 저장된 진행 방향의 반대를 surface-to-light vector로 사용한다. Point는 Light position까지의 거리로 선형 attenuation을 계산한다. Spot은 같은 거리 감쇠에 Light 진행 방향과 surface 방향의 정렬도를 거듭제곱한 cone factor를 추가한다.

#### Light 계산 의사코드

```cpp
// Pseudo C++: Light type별 strength 계산
Color EvaluateLight(Light light, Surface surface)
{
    if (light.type == Directional)
    {
        return BlinnPhong(-light.direction, surface);
    }

    Vector toLight = light.position - surface.position;
    float distance = Length(toLight);
    float attenuation = LinearFalloff(distance,
                                      light.fallOffStart,
                                      light.fallOffEnd);
    Color result = BlinnPhong(Normalize(toLight), surface) * attenuation;

    if (light.type == Spot)
    {
        float alignment = Dot(-Normalize(toLight), light.direction);
        result *= Pow(Max(alignment, 0), light.spotPower);
    }
    return result;
}
```

- [Material·Light 계약과 공통 Blinn-Phong](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L24-L58)
- [Directional Light 계산](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L60-L68)
- [Point Light와 distance attenuation](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L71-L93)
- [Spot Light와 cone factor](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L96-L120)

### Ambient And Texture Composition

Ambient는 Light 함수마다 반복하지 않고 pixel마다 한 번만 더한다. 활성 Light의 diffuse·specular 결과를 합산한 뒤 generated 목재 texture sample을 곱한다.

#### Pixel composition 의사코드

```cpp
// Pseudo C++: ambient 중복 없이 Light와 texture 결합
Color color = material.ambient;
color += EvaluateDirectionalLight();
color += EvaluatePointLight();
color += EvaluateSpotLight();
return useTexture ? color * Sample(texture, uv) : color;
```

- [Light 누적과 texture 결합](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/BasicPixelShader.hlsl#L14-L36)
- [Texture·sampler·constant buffer binding](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/ExampleApp.cpp#L268-L291)

## 시각 결과

Directional 상태는 위치와 무관한 일정한 입사 방향으로 box의 오른쪽 face를 넓게 밝힌다. Point 상태는 오른쪽 위의 Light position에 가까운 face가 넓게 밝아져 fragment별 방향과 거리 감쇠가 드러난다. Spot 상태는 Point와 같은 위치·falloff를 유지하면서 `spotPower=16`의 cone factor가 box 중심 주변의 조명 영역을 좁힌다.

Point와 Spot의 공통 parameter를 유지했기 때문에 넓은 위치 중심 조명과 응축된 cone 조명의 차이를 직접 비교할 수 있다. 세 상태는 연속 animation이 아니라 Light type별 이산 결과이므로 screenshot 3장을 사용하고 video는 추가하지 않는다.

## 구현 범위와 한계

- Light type 하나만 활성화하며 여러 Light의 실제 동시 누적은 검증하지 않는다.
- Point·Spot은 학습용 선형 falloff를 사용한다.
- Spot은 단일 exponent로 cone을 만들며 inner·outer angle과 smooth edge를 제공하지 않는다.
- Texture color를 최종 ambient·diffuse·specular 결과 전체에 곱한다.
- Shadow, gamma correction, normal mapping과 physically based BRDF는 포함하지 않는다.
- Runtime shader와 texture load는 project 폴더 CWD에 의존한다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 다루지 않는다.

## 검증

- [Part2 Chapter05-08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-02 현재 확인, project 폴더 CWD
- Release x64 build/run: 성공, 2026-08-02 현재 확인, project 폴더 CWD
- Application title: `ComputerGraphics - Chapter06 Step6 Lighting`
- Resource: Generated 목재 PNG load, `t0`·`s0`, transform·Light·material buffer binding 확인
- 실패 경로: 잘못된 CWD에서 texture load 실패 보고와 exit code `-1` 확인
- UI: Directional·Point·Spot 전환과 position·falloff·spotPower·direction 반영 확인
- Capture: PNG 1282×992 3장, 자동 기술 검수와 사용자 시각 승인 완료
- Video: 제외, 같은 구도의 세 정적 상태가 방향·거리·cone 차이를 직접 설명함

## 관련 코드

- [Box geometry와 GPU resource 초기화](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/ExampleApp.cpp#L10-L192)
- [Transform·Light constant buffer 갱신](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/ExampleApp.cpp#L195-L250)
- [Texture·shader binding과 draw](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/ExampleApp.cpp#L253-L291)
- [Light 공통 계산](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/Common.hlsli#L24-L120)
- [Pixel shader Light 누적](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/BasicPixelShader.hlsl#L1-L38)

## 관련 문서

- [Chapter06 Step6 Lighting Example](../../../Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting/README.md)
- [이전 단계: Chapter06 Step5A Texturing LightingSelf Demo](06_TexturingLightingSelf.md)
- [Light Types Topic](../../01_Topics/LightingAndShading/LightTypes.md)
- [Phong And Blinn-Phong Topic](../../01_Topics/LightingAndShading/PhongAndBlinnPhong.md)
- [Texture Sampling Topic](../../01_Topics/TexturingAndMapping/TextureSampling.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
