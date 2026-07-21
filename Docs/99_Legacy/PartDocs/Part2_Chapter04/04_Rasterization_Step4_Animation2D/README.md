# 04 Rasterization Step4 Animation2D

## 목적

Step3의 2D transformation을 시간 기반 update로 확장해, sun-earth-moon 형태의 계층적 orbit animation을 구성하는 예제입니다.

## 핵심 키워드

- CPU-side animation
- Orbit transform
- Hierarchical transform
- Angular velocity
- Per-frame update
- ImGui runtime controls
- Indexed triangle rasterization

## 구현 흐름

1. `Mesh::InitCircle()`로 sun, earth, moon 원형 mesh를 각각 생성합니다.
2. 각 mesh의 원본 geometry를 `vertexBuffer`, `indexBuffer`, `colorBuffer`로 복사합니다.
3. `Rasterization::Update()`에서 `earthAngle`, `moonAngle`을 angular velocity와 `dt`로 누적합니다.
4. `Rasterization::Render()`에서 sun을 먼저 그리고, earth와 moon은 현재 angle과 position으로 변환한 뒤 그립니다.
5. moon은 자체 orbit 변환 후 earth orbit 변환을 한 번 더 적용해 계층적 움직임처럼 보이게 구성합니다.
6. ImGui slider로 위치, 각도, 각속도를 런타임에 조절합니다.

## 핵심 코드

```cpp
void Rasterization::Update() {
    const float dt = 1.0f / 30.0f;

    this->earthAngle += this->earthAngularVelocity * dt;
    this->moonAngle += this->moonAngularVelocity * dt;
}
```

매 프레임 angle을 누적해 animation 상태를 갱신합니다.

```cpp
glm::vec3 temp = moon.vertexBuffer[i] + moonPosition;
temp = RotateAboutZ(temp, moonAngle);

temp = temp + earthPosition;
temp = RotateAboutZ(temp, earthAngle);
```

moon의 local orbit을 먼저 만든 뒤 earth orbit 변환을 합성합니다. 실제 좌표계 객체를 따로 만들지는 않지만, 변환 순서 때문에 계층적 orbit처럼 보입니다.

## Archive 반영 메모

- raw source의 장문 학습 주석은 source에서 제거하고 `local/Part2_Chapter04/04_Rasterization_Step4_Animation2D/source-comments.md`에 분리했습니다.
- raw의 `earthAngle`, `moonAngle` 갱신 코드는 주석 처리되어 있었지만, animation 예제 목적에 맞게 archive에서는 실제 update 코드로 반영했습니다.
- `distSunToEarth`, `distEarthToMoon`은 기본 orbit 위치 초기화에 연결했습니다.

## 실행 결과

- Build/run status: 성공
- 확인 내용: MSBuild Debug x64, Release x64 성공. 사용자 Debug/Release 실행 확인 완료
- Capture status: 보류

## 공개 가능성

- 상태: 검토 필요
- 근거: private archive 학습 예제입니다. public subset으로 옮기기 전에는 강의 기반 구조, 주석, 내부 reference, asset 포함 여부를 다시 확인해야 합니다.

## 관련 문서

- [Status](status.md)
- [Part2 Chapter04 manifest](../../_repo/manifests/Part2_Chapter04.md)
