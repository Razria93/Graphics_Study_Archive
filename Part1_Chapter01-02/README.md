# Part1 Chapter01-02

이 Chapter는 DirectX11 window/render loop를 구성하고, CPU에서 처리한 image post-processing 결과를 DirectX11 texture로 표시하는 흐름을 정리한다.

핵심은 DirectX11 초기화 자체와 CPU-side pixel buffer가 GPU shader resource로 연결되는 과정을 이해하는 것이다. `01_DX11InitAndImGui`는 이후 예제의 실행 기반을 만들고, `02_Bloom`은 그 기반 위에서 bloom 후처리 결과를 화면과 result image로 확인한다.

## 목표

- Win32 window 위에 DirectX11 device, device context, swap chain, render target view를 구성한다.
- CPU에서 만든 pixel buffer를 dynamic texture로 업로드하고 full-screen quad로 출력한다.
- 밝은 영역 분리, Gaussian blur, 원본 합성을 통한 기본 bloom 흐름을 확인한다.
- 예제 README, Topic, Verification, Demo, Publication, GitHub PR body가 어떻게 연결되는지 pilot으로 검증한다.

## 예제 구성

### 01_DX11InitAndImGui

DirectX11 device/swap chain/render target과 ImGui overlay를 구성하는 기반 예제다. CPU에서 갱신한 작은 canvas texture를 full-screen quad로 출력하며, 이후 image processing 예제의 최소 렌더링 흐름을 제공한다.

- README: [01_DX11InitAndImGui](01_DX11InitAndImGui/README.md)
- capture/result: 별도 생성하지 않는다.

### 02_Bloom

CPU에서 bloom 후처리를 계산하고, 처리된 pixel buffer를 DirectX11 dynamic texture로 업로드해 화면에 표시하는 예제다. original input과 bloom result를 함께 보여주어 bright-pass와 blur 합성 결과를 비교한다.

- README: [02_Bloom](02_Bloom/README.md)
- Topic: [PostProcessingAndBloom](../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- Demo: [Part1 Chapter01-02 Demo Index](../Docs/03_Demos/Part1_Chapter01-02/demo-index.md)

## 핵심 Topic

- DirectX11 initialization: device, device context, swap chain, render target view를 구성하는 최소 렌더링 기반이다.
- Dynamic texture upload: CPU pixel buffer를 GPU texture로 업로드하고 pixel shader에서 샘플링한다.
- Bloom post-processing: threshold로 밝은 영역을 분리하고 blur 후 원본에 더해 glow를 만든다.

자세한 개념 설명은 [Topics Guide](../TOPICS.md)와 [PostProcessingAndBloom](../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)을 기준으로 본다.

## 대표 Demo

대표 demo는 `02_Bloom`의 original input과 bloom result 비교다.

- Original input: [part1_chapter01-02_02_bloom_input.jpg](../Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg)
- Bloom result: [part1_chapter01-02_02_bloom_result.png](../Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png)
- Demo index: [Docs/03_Demos/Part1_Chapter01-02/demo-index.md](../Docs/03_Demos/Part1_Chapter01-02/demo-index.md)

## 검증 상태

| 예제 | Debug x64 | Release x64 | capture/result | 비고 |
| --- | --- | --- | --- | --- |
| `01_DX11InitAndImGui` | 확인 | 확인 | 제외 | 기반 렌더 루프 설명용 예제 |
| `02_Bloom` | 확인 | 확인 | 확인 | ChatGPT 생성 입력 이미지로 `result.png` 생성 확인 |

자세한 build/run 기록은 [Verification Index](../Docs/02_Verification/Part1_Chapter01-02/verification-index.md)를 기준으로 본다.

## 관련 문서

- Example README: [01_DX11InitAndImGui](01_DX11InitAndImGui/README.md), [02_Bloom](02_Bloom/README.md)
- Topic: [PostProcessingAndBloom](../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- Verification: [Part1 Chapter01-02 Verification Index](../Docs/02_Verification/Part1_Chapter01-02/verification-index.md)
- Demo: [Part1 Chapter01-02 Demo Index](../Docs/03_Demos/Part1_Chapter01-02/demo-index.md)
- WorkLog: [WU-Part1](../Docs/04_WorkLogs/active/WU-Part1.md)
- GitHub PR body candidate: [part1_chapter01-02](../Docs/07_GitHub/prs/part1_chapter01-02.md)
