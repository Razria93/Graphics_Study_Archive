# Part1_Chapter01-02 Demo Index

이 문서는 `Part1_Chapter01-02`의 demo capture/result 후보와 capture/result 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: DX11 init, bloom
- 비고: minimum screenshot 중심

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [02_Bloom](02_Bloom.md) | [02_Bloom README](../../../Part1_Chapter01-02/02_Bloom/README.md) | [PostProcessingAndBloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md) | [Verification](../../02_Verification/Part1_Chapter01-02/verification-index.md) | [Result](../../_assets/captures/part1_chapter01-02_02_bloom_result.png) | [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9) | 확보 | 단일 결과 이미지로 효과 식별 |
| 대표 capture | [02_Bloom](02_Bloom.md) | [02_Bloom README](../../../Part1_Chapter01-02/02_Bloom/README.md) | [PostProcessingAndBloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md) | [Verification](../../02_Verification/Part1_Chapter01-02/verification-index.md) | [Input](../../_assets/captures/part1_chapter01-02_02_bloom_input.jpg), [Result](../../_assets/captures/part1_chapter01-02_02_bloom_result.png) | [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9) | 확보 | 대표 post-processing 비교 자료 |
| 최소 init capture | 없음 | [DX11 Init README](../../../Part1_Chapter01-02/01_DX11InitAndImGui/README.md) | 미확인 | [Verification](../../02_Verification/Part1_Chapter01-02/verification-index.md) | 없음 | 미게시 | 제외 | 기반 렌더 루프 설명용으로 별도 capture 제외 |
| video | [02_Bloom](02_Bloom.md) | [02_Bloom README](../../../Part1_Chapter01-02/02_Bloom/README.md) | [PostProcessingAndBloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md) | [Verification](../../02_Verification/Part1_Chapter01-02/verification-index.md) | 없음 | 미게시 | 제외 | 정적 input/result 비교로 목적 충족 |

## 갱신 기준

- 실제 capture/result가 확보되면 `Docs/_assets` 경로를 연결한다.
- `02_Bloom`의 최소 capture는 result 1장을 사용하고 대표 capture는 input/result 비교를 사용한다.
- build/run 상태가 확인되지 않은 demo는 `확보`로 바꾸지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
