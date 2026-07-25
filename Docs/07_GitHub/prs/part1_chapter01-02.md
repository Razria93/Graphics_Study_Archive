# Part1 Chapter01-02 문서화 workflow 검증

## 요약

이 PR은 `Part1_Chapter01-02`의 DirectX11 초기화와 CPU bloom 예제를 문서화한다. Chapter README를 장 단위 지도 역할로 정리하고, 예제별 상세 설명은 각 코드 폴더 README에 둔다.

`02_Bloom`은 original input과 bloom result를 함께 보여주어 capture/result가 README, Demo, Verification, PR body로 연결되는 흐름을 검증한다. Root README는 portfolio archive 첫 화면으로 정리하고, Chapter/Example README는 각 계층의 정본 역할을 나눴다. 이 PR body는 상세 설명을 복제하지 않고 reviewer가 볼 핵심 요약과 링크만 제공한다.

## 범위

- Chapter: `Part1_Chapter01-02`
- 대표 예제: `01_DX11InitAndImGui`, `02_Bloom`
- 문서 범위: Root README, Chapter README, Example README, Topic, Verification, Demo, Publication 후보, README 정책, PR body 후보
- 제외 범위: Part1 Chapter03, `Portfolio_RayTracer`, public repo 게시 확정

## 핵심 개념

- DirectX11 initialization: Win32 window, device, device context, swap chain, render target view를 구성하는 최소 렌더링 기반이다. 자세한 흐름은 `01_DX11InitAndImGui` README에서 확인한다.
- Dynamic texture upload: CPU에서 만든 pixel buffer를 GPU texture에 업로드하고 pixel shader에서 샘플링하는 흐름이다. 두 예제 모두 CPU-side image data와 렌더링 파이프라인의 연결을 보여준다.
- Bloom post-processing: 밝은 영역을 분리하고 blur 후 원본에 더해 glow를 만드는 후처리 흐름이다. 자세한 개념은 `PostProcessingAndBloom` Topic으로 연결한다.
- Capture/result 연결: `02_Bloom`의 input/result 이미지를 `Docs/_assets/captures`로 승격하고 Demo, Verification, Publication 후보와 연결한다.
- README 계층 분리: Root README는 portfolio archive 소개, Chapter README는 장 단위 지도, Example README는 예제 설명 정본으로 분리한다.

## 대표 예제

### 01_DX11InitAndImGui

이 예제는 이후 예제의 DirectX11 실행 기반을 만든다. device/swap chain/render target, dynamic texture upload, ImGui overlay 흐름을 확인하는 기반 예제이며, 별도 capture/result는 만들지 않는다.

- README: `Part1_Chapter01-02/01_DX11InitAndImGui/README.md`
- Verification: `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`

### 02_Bloom

이 예제는 CPU에서 bloom 결과 이미지를 만든 뒤 DirectX11 dynamic texture로 표시한다. original input과 bloom result를 함께 보여주므로 Chapter01-02의 대표 demo로 사용한다.

- README: `Part1_Chapter01-02/02_Bloom/README.md`
- Topic: `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`
- Demo: `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`

## 검증

- `01_DX11InitAndImGui` Debug x64 build/run은 성공했다.
- `01_DX11InitAndImGui` Release x64 build/run은 성공했다.
- `02_Bloom` Debug x64 build/run은 성공했다.
- `02_Bloom` Release x64 build/run은 성공했다.
- `02_Bloom`에서 ChatGPT 생성 입력 이미지 기반 `result.png`를 생성하고 capture/result를 확보했다.
- `git diff --check`를 통과했다.
- GitHub body validator를 통과했다.

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
- public repo 게시 여부는 아직 확정하지 않는다.
- GitHub Issue/PR 번호는 아직 없다.

## 문서

- Chapter README: `Part1_Chapter01-02/README.md`
- Root README: `README.md`
- Example README: `Part1_Chapter01-02/01_DX11InitAndImGui/README.md`, `Part1_Chapter01-02/02_Bloom/README.md`
- Topic: `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`
- Verification: `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`
- Demo: `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`
- WorkLog: `Docs/04_WorkLogs/active/WU-Part1.md`
- Publication: `Docs/05_Publication/candidate-list.md`, `Docs/05_Publication/private-only.md`
- Policy: `Docs/06_Policies/canonical-docs-policy.md`, `Docs/06_Policies/demo-capture-policy.md`, `Docs/06_Policies/docs-authoring-flow-policy.md`, `Docs/06_Policies/work-unit-workflow-policy.md`

## 관련 이슈

- 없음

## 다음 단계

- 사용자 검토 후 Part1 Chapter01-02 PR 게시 여부를 결정한다.
- Part1의 다음 예제 또는 Part2 rasterization 예제에 같은 workflow를 적용한다.
- public subset 후보는 별도 공개 검수 후 확정한다.
