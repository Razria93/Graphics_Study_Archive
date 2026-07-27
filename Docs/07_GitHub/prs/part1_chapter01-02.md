# Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom

## 요약

이 PR은 `Part1_Chapter01-02`의 DirectX11 initialization과 CPU bloom post-processing을 중심으로 정리한다. device/context/swap chain/render target 기반과 dynamic texture upload 흐름, original input 대비 bloom result를 함께 검토한다.

## 범위

- Chapter: `Part1_Chapter01-02`
- 대표 예제: `01_DX11InitAndImGui`, `02_Bloom`
- 문서 범위: Root README, Chapter README, Example README, Topic, Verification, Demo, Publication 후보
- 제외 범위: Part1 Chapter03, `Portfolio_RayTracer`, public subset 게시 확정

## 핵심 개념

- DirectX11 initialization: Win32 window, device, device context, swap chain, render target view를 구성하는 최소 렌더링 기반이다. 자세한 흐름은 `01_DX11InitAndImGui` README에서 확인한다.
- Dynamic texture upload: CPU에서 만든 pixel buffer를 GPU texture에 업로드하고 pixel shader에서 샘플링하는 흐름이다. 두 예제 모두 CPU-side image data와 렌더링 파이프라인의 연결을 보여준다.
- Bloom post-processing: 밝은 영역을 분리하고 blur 후 원본에 더해 glow를 만드는 후처리 흐름이다. 자세한 개념은 `PostProcessingAndBloom` Topic으로 연결한다.
- Capture/result 연결: `02_Bloom`의 input/result 이미지를 Demo와 PR 본문에서 함께 확인한다.

## 대표 예제

### 01_DX11InitAndImGui

이 예제는 이후 예제의 DirectX11 실행 기반을 만든다. device/swap chain/render target, dynamic texture upload, ImGui overlay 흐름을 확인하는 기반 예제이며, 별도 capture/result는 만들지 않는다.

- README: [01_DX11InitAndImGui README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/01_DX11InitAndImGui/README.md)
- Verification: [Part1_Chapter01-02 verification-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/02_Verification/Part1_Chapter01-02/verification-index.md)

### 02_Bloom

이 예제는 CPU에서 bloom 결과 이미지를 만든 뒤 DirectX11 dynamic texture로 표시한다. original input과 bloom result를 함께 보여주므로 Chapter01-02의 대표 demo로 사용한다.

- README: [02_Bloom README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/README.md)
- Topic: [PostProcessingAndBloom](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- Demo: [Part1_Chapter01-02 demo-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/03_Demos/Part1_Chapter01-02/demo-index.md)

## 검증

- `01_DX11InitAndImGui` Debug x64 build/run은 성공했다.
- `01_DX11InitAndImGui` Release x64 build/run은 성공했다.
- `02_Bloom` Debug x64 build/run은 성공했다.
- `02_Bloom` Release x64 build/run은 성공했다.
- `02_Bloom`에서 입력 이미지 기반 `result.png`를 생성하고 original input/bloom result 비교를 확보했다.

## 스크린샷

### 02_Bloom Original Input

Bloom 처리 전 입력 이미지다. 밝은 구체와 어두운 배경 대비가 있어 bloom 전후 비교에 사용한다.

![02_Bloom Original Input](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg?raw=true)

### 02_Bloom Bloom Result

CPU bloom 처리 후 생성된 result image다. 밝은 영역이 주변으로 확산된 결과를 보여준다.

![02_Bloom Bloom Result](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png?raw=true)

## 미확인 / 제한

- `01_DX11InitAndImGui`는 기반 렌더 루프 설명용 예제로 별도 capture/result를 만들지 않는다.
- `02_Bloom`은 GPU multi-pass bloom pipeline이 아니라 CPU image processing 결과를 DirectX11 dynamic texture로 표시하는 예제다.
- `Docs/02_Verification/known-issues.md`의 VI-003 기준으로 build 성공과 별개로 `pwsh.exe` 경고가 관찰된다.
- input/result 이미지는 private archive PR 기준으로 사용 가능 상태다. public subset 승격 확정은 `Docs/05_Publication` 기준으로 별도 판단한다.
- public subset 게시 여부는 아직 확정하지 않는다.
- Progress Issue는 #7이고, 이 PR은 Draft PR #8이다.

## 문서

- Chapter README: [Part1_Chapter01-02 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/README.md)
- Root README: [Root README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/README.md)
- Example README:
	- [01_DX11InitAndImGui README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/01_DX11InitAndImGui/README.md)
	- [02_Bloom README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/README.md)
- Topic: [PostProcessingAndBloom](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- Verification: [Part1_Chapter01-02 verification-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/02_Verification/Part1_Chapter01-02/verification-index.md)
- Demo: [Part1_Chapter01-02 demo-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/03_Demos/Part1_Chapter01-02/demo-index.md)
- Publication:
	- [candidate-list](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/05_Publication/candidate-list.md)

## 관련 이슈

- #7

## 다음 단계

- 사용자 검토 후 Part1 Chapter01-02 PR 게시 여부를 결정한다.
- Part1의 다음 예제 또는 Part2 rasterization 예제에 같은 workflow를 적용한다.
- public subset 후보는 별도 공개 검수 후 확정한다.
