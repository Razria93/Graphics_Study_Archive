# Ex1402 Blur

`Ex1402_Blur`는 compute shader로 separable blur를 수행하는 예제입니다. `Ex1401_Basic`에서 back buffer에 직접 쓰는 기본 compute shader 흐름을 확인했다면, 이 예제는 intermediate texture, SRV/UAV, barrier, X/Y pass를 이용해 post-processing blur를 구성합니다.

## 목적

- compute shader 기반 blur pass를 확인합니다.
- horizontal X blur와 vertical Y blur를 분리한 separable Gaussian blur 흐름을 확인합니다.
- SRV로 읽고 UAV로 쓰는 texture ping-pong 구조를 확인합니다.
- 기본 compute shader blur, groupshared cache compute shader blur, pixel shader blur 비교 경로를 확인합니다.

## 핵심 흐름

1. back buffer format을 `DXGI_FORMAT_R16G16B16A16_FLOAT`로 설정합니다.
2. 화면 크기를 `1280 x 768`로 고정하고 MSAA를 끕니다.
3. blur 입력 확인용 staging texture를 생성합니다.
4. `m_texA`, `m_texB` 두 개의 unordered access texture를 생성합니다.
5. `m_texA`를 입력, `m_texB`를 출력으로 X blur를 수행합니다.
6. `m_texB`를 입력, `m_texA`를 출력으로 Y blur를 수행합니다.
7. 각 pass 사이에 `ComputeShaderBarrier()`로 SRV/UAV binding을 정리합니다.
8. 최종 `m_texA`를 back buffer로 복사합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1402_Blur.cpp` | staging texture 생성, compute/pixel blur path, texture ping-pong |
| `Ex1402_Blur.h` | blur shader, texture/view, PSO 멤버 정의 |
| `Ex1402_BlurXCS.hlsl` | compute shader horizontal blur |
| `Ex1402_BlurYCS.hlsl` | compute shader vertical blur |
| `Ex1402_BlurXGroupCacheCS.hlsl` | groupshared cache horizontal blur |
| `Ex1402_BlurYGroupCacheCS.hlsl` | groupshared cache vertical blur |
| `Ex1402_BlurXPS.hlsl` | pixel shader horizontal blur 비교 경로 |
| `Ex1402_BlurYPS.hlsl` | pixel shader vertical blur 비교 경로 |
| `main.cpp` | command argument `1402`로 `Ex1402_Blur` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1402`를 지정해야 합니다.

```text
Examples.exe 1402
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 화면 중앙 부근의 RGB 고강도 점들이 반복 blur pass를 거쳐 넓게 퍼지는지 확인
- 현재 활성 경로는 `ComputeShaderBlur(false)`입니다.
- `ComputeShaderBlur(true)`와 `PixelShaderBlur()`는 비교용 경로로 남아 있지만 현재는 주석 처리되어 있습니다.

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
