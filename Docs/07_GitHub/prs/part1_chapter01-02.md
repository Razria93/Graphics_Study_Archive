# Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom

## 요약

이 PR은 `Part1_Chapter01-02`의 DirectX11 initialization과 CPU bloom post-processing을 중심으로 정리한다. device/context/swap chain/render target 기반과 dynamic texture upload 흐름, original input 대비 bloom result를 함께 검토한다.

## 범위

- Chapter: `Part1_Chapter01-02`
- 대표 예제: `01_DX11InitAndImGui`, `02_Bloom`
- 문서 범위: Root README, Chapter README, Example README, Topic, Verification, Demo
- 제외 범위: Part1 Chapter03, `Portfolio_RayTracer`

## 핵심 개념

- DirectX11 initialization: Win32 window, device, device context, swap chain, render target view를 구성하는 최소 렌더링 기반이다. 자세한 흐름은 `01_DX11InitAndImGui` README에서 확인한다.
- Dynamic texture upload: CPU에서 만든 pixel buffer를 GPU texture에 업로드하고 pixel shader에서 샘플링하는 흐름이다. 두 예제 모두 CPU-side image data와 렌더링 파이프라인의 연결을 보여준다.
- Bloom post-processing: 밝은 영역을 분리하고 blur 후 원본에 더해 glow를 만드는 후처리 흐름이다. 자세한 개념은 `PostProcessingAndBloom` Topic으로 연결한다.
- Capture/result 연결: PR은 대표 result 하나를 보여주고 상세 비교는 Demo로 연결한다.

## 대표 예제

### 01_DX11InitAndImGui

이 예제는 이후 예제의 DirectX11 실행 기반을 만든다. device/swap chain/render target, dynamic texture upload, ImGui overlay 흐름을 확인하는 기반 예제이며, 별도 capture/result는 만들지 않는다.

- README: [01_DX11InitAndImGui README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/01_DX11InitAndImGui/README.md)
- Verification: [Part1_Chapter01-02 verification-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/02_Verification/Part1_Chapter01-02/verification-index.md)

### 02_Bloom

이 예제는 CPU에서 bloom 결과 이미지를 만든 뒤 DirectX11 dynamic texture로 표시한다. original input과 bloom result를 함께 보여주므로 Chapter01-02의 대표 demo로 사용한다.

- README: [02_Bloom README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/README.md)
- Topic: [PostProcessingAndBloom](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- Demo Issue: [02_Bloom CPU Bloom Demo #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9)

## 검증

- `01_DX11InitAndImGui` Debug x64 build/run은 성공했다.
- `01_DX11InitAndImGui` Release x64 build/run은 성공했다.
- `02_Bloom` Debug x64 build/run은 성공했다.
- `02_Bloom` Release x64 build/run은 성공했다.
- `02_Bloom`에서 입력 이미지 기반 `result.png`를 생성하고 original input/bloom result 비교를 확보했다.

## 대표 Visual

### 02_Bloom Result

CPU bloom 처리 후 생성된 result image다. 밝은 영역이 주변으로 확산된 결과를 보여준다.

![02_Bloom Bloom Result](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png?raw=true)

## 구현 범위와 한계

- `01_DX11InitAndImGui`는 기반 렌더 루프 설명용 예제로 별도 capture/result를 만들지 않는다.
- `02_Bloom`은 GPU multi-pass bloom pipeline이 아니라 CPU image processing 결과를 DirectX11 dynamic texture로 표시하는 예제다.
- 대표 visual은 검토된 tracked result asset을 사용한다.

## 문서

- Chapter README: [Part1_Chapter01-02 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/README.md)
- Root README: [Root README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/README.md)
- Example README:
	- [01_DX11InitAndImGui README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/01_DX11InitAndImGui/README.md)
	- [02_Bloom README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/README.md)
- Topic: [PostProcessingAndBloom](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- Verification: [Part1_Chapter01-02 verification-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/02_Verification/Part1_Chapter01-02/verification-index.md)
- Detailed Demo: [02_Bloom](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)

## 관련 이슈

- #7
