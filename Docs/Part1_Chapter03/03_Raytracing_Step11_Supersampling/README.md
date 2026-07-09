# 03 Raytracing Step11 Supersampling

## Chapter purpose

Step11은 Step10의 texturing 예제를 바탕으로 pixel 하나를 여러 sub-sample로 나누어 추적하는 supersampling 예제입니다. 한 픽셀 중심에서 한 번만 ray를 쏘면 경계가 계단처럼 보일 수 있으므로, 픽셀 내부의 여러 위치를 샘플링하고 평균을 내서 aliasing을 줄입니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Aliasing | 연속적인 장면을 이산 pixel grid로 샘플링할 때 생기는 계단 현상 또는 왜곡 |
| Anti-aliasing | 추가 sampling과 filtering으로 aliasing을 줄이는 처리 |
| Supersampling | 한 pixel을 더 작은 sample 영역으로 나누어 여러 ray를 추적하고 평균을 내는 방식 |
| Recursive 2x2 sampling | pixel 영역을 2x2로 반복 분할하며 sample 수를 늘리는 구현 방식 |
| Sample average | 여러 sub-sample 색을 평균내 최종 pixel color로 사용하는 과정 |

## Core implementation

핵심 구현은 `Raytracer.h`의 `TraceRay2x2()`와 `Render()`에 있습니다.

```cpp
const vec3 pixelColor = TraceRay2x2(eyePos, pixelPosWorld, pixelSize, supersamplingDepth);
pixels[size_t(i + width * j)] = vec4(glm::clamp(pixelColor, 0.0f, 1.0f), 1.0f);
```

`TraceRay2x2()`는 depth가 0이면 해당 sample 위치에서 ray를 한 번 추적하고, depth가 남아 있으면 pixel 영역을 2x2로 나누어 네 sub-sample의 평균을 반환합니다.

```cpp
return color * 0.25f;
```

Step11에서는 내부 렌더 해상도를 `width / 8`, `height / 8`로 낮춘 뒤 supersampling을 적용합니다. 낮은 해상도에서 edge aliasing을 관찰하고, sub-sample 평균으로 경계가 완화되는 흐름을 확인하기 위한 구성입니다.

## Asset handling

| Asset | Status | Note |
| --- | --- | --- |
| `shadertoy_abstract1.jpg` | private archive 포함 | Step10과 동일한 texture input asset |

이 asset은 private archive 실행을 위한 입력 자료로 포함합니다. public repo 공개 전에는 출처/라이선스 표기 가능 여부를 다시 확인합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Required texture asset | 포함 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 다음 코드 후보는 `03_Raytracing_Step12_Reflection`입니다.
