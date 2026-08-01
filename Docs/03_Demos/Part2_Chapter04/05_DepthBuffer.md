# Step5 DepthBuffer Demo

## 목적

Step5는 겹치는 세 circle의 fragment Z를 CPU depth buffer와 비교해 draw order와 분리된 visibility를 구성한다. 기본 screenshot과 depth 순서를 반전한 screenshot은 같은 geometry에서도 Z 값에 따라 앞뒤 관계가 바뀌는 결과를 보여준다.

## 책임 범위

- Frame마다 per-pixel depth buffer를 clear하고 갱신하는 구현을 설명한다.
- Barycentric color·depth 보간과 depth test의 연결을 설명한다.
- 세 circle의 UI Z 조작이 visibility에 미치는 결과를 설명한다.
- CPU rasterization과 DirectX11 presentation의 경계를 설명한다.
- 일반적인 depth buffer 원리는 [Depth Buffer](../../01_Topics/Rasterization/DepthBuffer.md)로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)로 위임한다.

## 결과 미리보기

기본 상태는 red `0.1`, blue `0.3`, yellow `0.7` 순으로 작은 depth가 앞에 놓인다.

![Step5 default depth order](../../_assets/captures/part2_chapter04_05_depth_buffer_default.png)

반전 상태는 red `0.7`, blue `0.3`, yellow `0.1` 순으로 yellow가 앞, blue가 중간, red가 뒤에 놓인다.

![Step5 reversed depth order](../../_assets/captures/part2_chapter04_05_depth_buffer_reordered.png)

Selected local video는 기본 → 반전 → 기본 복귀 흐름을 보여준다. 전환 중 같은 depth가 생기지 않도록 반전할 때는 red, 복귀할 때는 yellow를 임시 `0.9`로 이동한 뒤 나머지 값을 바꾼다. 검수 master는 게시 전까지 비추적 보관 영역에 유지한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| Red circle | Radius `0.3`, 30 triangles, 기본 Z `0.1` |
| Blue circle | Radius `0.5`, 30 triangles, X `-0.3`, 기본 Z `0.3` |
| Yellow circle | Radius `0.5`, 30 triangles, X `0.3`, 기본 Z `0.7` |
| UI 입력 | 각 center Z를 `-1.0`부터 `1.0`까지 조절 |
| Depth 초기값 | Frame마다 모든 pixel을 `FLT_MAX`로 clear |
| CPU 출력 | Depth test를 통과한 color를 기록한 1280×960 RGBA32F pixel buffer |
| 화면 출력 | Dynamic texture를 sampling한 full-screen quad와 Scene Control UI |

## 구현 흐름

1. Red, blue와 yellow indexed circle fan의 원본 data를 구성한다.
2. Frame 시작 시 color buffer를 지우고 depth buffer를 `FLT_MAX`로 초기화한다.
3. Circle local vertex에 해당 center position과 Z를 더한다.
4. Triangle bounding box에서 edge function으로 covered pixel을 찾는다.
5. Barycentric weight로 color와 depth를 보간한다.
6. Depth가 `0` 이상이고 저장값보다 작으면 depth와 color를 함께 기록한다.
7. 세 circle을 차례로 rasterize하지만 최종 visibility는 저장된 최소 depth가 결정한다.
8. CPU color buffer를 DirectX11 dynamic texture와 full-screen quad로 표시한다.

## 핵심 구현

### Depth Buffer Clear

`Render()`는 color pixel 수와 같은 크기로 depth buffer를 준비하고 모든 값을 `FLT_MAX`로 채운다. 이전 frame의 depth가 다음 frame에 남지 않으므로 UI에서 Z를 바꾼 결과가 매 frame 새로 평가된다.

- [Per-frame depth buffer 초기화](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L114-L116)
- [세 circle의 center 적용과 순차 rasterization](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L118-L152)

### Barycentric Depth Test

Color와 Z는 같은 barycentric weight를 사용한다. 새 depth가 nonnegative이고 현재 pixel의 저장값보다 작을 때만 depth와 color를 함께 갱신한다.

#### Depth Test 의사코드

```cpp
// Pseudo C++: covered pixel의 depth 비교와 color 갱신
void TestAndWritePixel(Fragment fragment, Pixel pixel)
{
    float depth = InterpolateDepth(fragment.barycentric);

    if (depth >= 0.0f && depth < depthBuffer[pixel])
    {
        depthBuffer[pixel] = depth;
        colorBuffer[pixel] = InterpolateColor(fragment.barycentric);
    }
}
```

- [Barycentric color와 depth 보간](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L87-L103)
- [Nonnegative depth test와 color·depth write](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L104-L108)

### Scene Depth Control

세 slider는 각 circle의 `center.z`를 직접 바꾼다. Default와 reordered capture는 geometry와 draw call 순서를 유지한 채 Z 값만 바꿔 depth test가 visibility를 결정한다는 점을 분리한다.

- [Circle geometry와 기본 center depth](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L11-L19)
- [Center Z slider와 범위](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/main.cpp#L63-L72)

### CPU Rasterization And Presentation

Depth test와 color 결정은 CPU `Rasterization`에서 수행한다. `Example::Update()`는 결과 pixel buffer를 dynamic texture로 복사하고 shader는 full-screen quad에서 texture를 표시한다. 이 예제는 DirectX11 depth-stencil state를 검증하는 Demo가 아니다.

- [CPU render와 dynamic texture upload](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Example.cpp#L10-L23)
- [RGBA32F dynamic texture 생성](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Example.cpp#L138-L153)
- [Full-screen quad presentation](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Example.cpp#L217-L235)

## 시각 결과

기본 상태에서는 red가 blue와 yellow의 겹침 영역을 덮고 blue는 yellow보다 앞에 놓인다. 반전 상태에서는 yellow가 blue와 red를 덮고 blue는 red보다 앞에 놓인다. Geometry와 rasterization 순서를 유지했으므로 두 screenshot의 차이는 center Z와 depth test에서 발생한다.

Selected video는 두 최종 상태 사이를 왕복한다. 동일 depth는 strict `<` 비교와 draw order에 의존하므로 전환용 임시값 `0.9`를 사용해 같은 depth에 머무는 구간을 제거한다.

## 구현 범위와 한계

- 현재 circle vertex의 local Z가 모두 `0`이므로 circle 내부 depth는 center Z와 같고 기울어진 surface depth 변화는 보여주지 않는다.
- Screen-space Z를 affine 보간하며 perspective-correct interpolation은 포함하지 않는다.
- Negative depth는 제외하지만 명시적인 far range와 upper clipping은 없다.
- 동일 depth는 먼저 기록된 fragment가 유지되어 draw order에 의존한다.
- CPU depth buffer만 사용하며 GPU depth-stencil state와 early-Z는 포함하지 않는다.
- Dynamic texture upload는 mapped `RowPitch`와 `Map()` 실패를 별도로 처리하지 않는다.

## 검증

- [Part2 Chapter04 Verification](../../02_Verification/Part2_Chapter04/verification-index.md)
- Debug x64 build/run: 성공, 2026-08-01 현재 확인
- Release x64 build/run: 성공, 2026-08-01 현재 확인
- Application title: `ComputerGraphics - Step5 DepthBuffer`
- Screenshot: 1282×992 기본·반전 capture, 기술·사용자 시각 검수 완료
- Selected video: H.264, 1282×992, CFR 30 FPS, 51.1초, audio 없음, 전체 decode와 사용자 시각 검수 완료

## 관련 코드

- [Circle과 기본 depth 상태](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L11-L19)
- [Barycentric depth test와 write](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L87-L108)
- [Depth clear와 세 circle rasterization](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Rasterization.cpp#L114-L152)
- [Scene Control UI](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/main.cpp#L63-L72)
- [CPU 결과 presentation](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/Example.cpp#L10-L23)

## 관련 문서

- [Step5 DepthBuffer Example](../../../Part2_Chapter04/04_Rasterization_Step5_DepthBuffer/README.md)
- [Depth Buffer](../../01_Topics/Rasterization/DepthBuffer.md)
- [Triangle Rasterization](../../01_Topics/Rasterization/TriangleRasterization.md)
- [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md)
- [Demo Index](demo-index.md)
