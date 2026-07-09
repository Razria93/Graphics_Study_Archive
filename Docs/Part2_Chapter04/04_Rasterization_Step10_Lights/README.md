# 04 Rasterization Step10 Lights

## 목적

software rasterizer에서 Blinn-Phong shading을 directional light, point light, spot light로 확장하는 예제입니다. Step9의 material/light shading 흐름 위에 light type 선택, 거리 감쇠, spotlight cone을 추가합니다.

## 핵심 키워드

- Directional light
- Point light
- Spot light
- Light strength
- Distance attenuation
- Falloff range
- Spot power
- Blinn-Phong shading

## 구현 흐름

1. `Light` 구조체가 `strength`, `direction`, `position`, `fallOffStart`, `fallOffEnd`, `spotPower`를 가집니다.
2. ImGui radio button으로 directional, point, spot light를 선택합니다.
3. directional light는 일정한 방향의 빛으로 계산합니다.
4. point light는 fragment 위치에서 light position까지의 거리와 방향을 사용합니다.
5. point/spot light는 falloff range를 이용해 거리 감쇠를 적용합니다.
6. spot light는 light direction과 fragment 방향의 dot product에 `spotPower`를 적용해 cone 집중도를 조절합니다.
7. 모든 light type은 최종적으로 Blinn-Phong 함수로 ambient/diffuse/specular를 계산합니다.

## 핵심 코드

```cpp
if (constants.lightType == 0) {
    color = ComputeDirectionalLight(constants.light, constants.material,
                                    psInput.normal, toEye);
} else if (constants.lightType == 1) {
    color = ComputePointLight(constants.light, constants.material,
                              psInput.position, psInput.normal, toEye);
} else {
    color = ComputeSpotLight(constants.light, constants.material,
                             psInput.position, psInput.normal, toEye);
}
```

pixel shader 단계에서 현재 light type에 따라 계산 경로를 바꿉니다.

```cpp
float CalcAttenuation(float distance, float fallOffStart, float fallOffEnd) {
    return Saturate((fallOffEnd - distance) / (fallOffEnd - fallOffStart));
}
```

point/spot light는 거리에 따라 light strength를 줄입니다. `Saturate()`로 감쇠값을 `[0, 1]` 범위에 고정합니다.

```cpp
const float spotFactor =
    glm::pow(glm::max(0.0f, glm::dot(-lightVec, light.direction)),
             light.spotPower);
lightStrength *= spotFactor;
```

spot light는 빛의 방향과 fragment 방향이 가까울수록 강해지며, `spotPower`가 클수록 빛이 더 좁게 집중됩니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step10_Lights/source-comments.md`로 분리했습니다.
- raw의 핵심 구조인 light type radio button, light strength, direction, position, falloff, spot power control은 유지했습니다.
- Step9의 Blinn-Phong shading 흐름을 유지하면서 directional/point/spot light 분기를 추가했습니다.
- source에는 실행 흐름 이해에 필요한 짧은 함수 구조만 남겼습니다.

## 실행 결과

- Build status: Debug x64, Release x64 성공
- Run status: 미확인
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 분리하기 전 강의 기반 구조, 주석, 문서, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
