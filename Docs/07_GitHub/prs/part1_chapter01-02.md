# Part1 Chapter01-02 문서화 workflow 검증

## 요약

이 PR은 `Part1_Chapter01-02`의 `01_DX11InitAndImGui`와 `02_Bloom`을 기준으로 새 문서화 workflow를 검증한다.

예제 README는 코드 폴더에 두고, Topic, Verification, Demo, Publication 문서는 `Docs` 산출물 축으로 연결한다. `02_Bloom`은 original input과 bloom result를 함께 보여주어 capture/result가 README와 PR body에 어떻게 연결되는지 확인한다.

## 핵심 개념

| 개념 | 설명 | 문서 |
| --- | --- | --- |
| DirectX11 initialization | Win32 window, device, device context, swap chain, render target view를 구성하는 최소 렌더링 기반이다. | `Part1_Chapter01-02/01_DX11InitAndImGui/README.md` |
| Dynamic texture upload | CPU에서 만든 pixel buffer를 `Map` / `memcpy` / `Unmap`으로 GPU texture에 업로드하고 pixel shader에서 샘플링한다. | `Part1_Chapter01-02/01_DX11InitAndImGui/README.md` |
| Bloom post-processing | threshold로 밝은 영역을 분리하고 Gaussian blur를 적용한 뒤 원본 이미지에 더해 glow를 만든다. | `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md` |
| Capture/result 연결 | 실행 결과 이미지를 `Docs/_assets/captures`로 승격하고 README, Demo, Publication 후보와 연결한다. | `Docs/03_Demos/Part1_Chapter01-02/demo-index.md` |

## 대표 예제

| 예제 | 설명 | README | Demo |
| --- | --- | --- | --- |
| `01_DX11InitAndImGui` | DirectX11 device/swap chain/render target과 ImGui overlay를 구성하는 기반 예제다. | `Part1_Chapter01-02/01_DX11InitAndImGui/README.md` | 별도 capture/result 없음 |
| `02_Bloom` | CPU bloom 처리 결과를 DirectX11 dynamic texture로 업로드해 표시하는 post-processing 예제다. | `Part1_Chapter01-02/02_Bloom/README.md` | `Docs/03_Demos/Part1_Chapter01-02/demo-index.md` |

## 검증

- `01_DX11InitAndImGui` Debug x64 build/run을 확인했다.
- `01_DX11InitAndImGui` Release x64 build/run을 확인했다.
- `02_Bloom` Debug x64 build/run을 확인했다.
- `02_Bloom` Release x64 build/run을 확인했다.
- `02_Bloom`에서 ChatGPT 생성 입력 이미지 기반 `result.png` 생성을 확인했다.
- `git diff --check`를 통과했다.
- GitHub body validator를 통과했다.

## 스크린샷

### 02_Bloom Original Input

Bloom 처리 전 입력 이미지다. 밝은 구체와 어두운 배경 대비가 있어 bloom 전후 비교에 사용한다.

![02_Bloom Original Input](Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg?raw=true)

### 02_Bloom Bloom Result

CPU bloom 처리 후 생성된 result image다. 밝은 영역이 주변으로 확산된 결과를 보여준다.

![02_Bloom Bloom Result](Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png?raw=true)

## 미확인 / 제한

- `01_DX11InitAndImGui`는 기반 렌더 루프 설명용 예제로 별도 capture/result를 만들지 않는다.
- `02_Bloom`은 GPU multi-pass bloom pipeline이 아니라 CPU image processing 결과를 DirectX11 dynamic texture로 표시하는 예제다.
- public repo 게시 여부는 아직 확정하지 않는다.
- GitHub Issue/PR 번호는 아직 없다.

## 문서

- Example README: `Part1_Chapter01-02/01_DX11InitAndImGui/README.md`, `Part1_Chapter01-02/02_Bloom/README.md`
- Topic: `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`
- Verification: `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`
- Demo: `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`
- WorkLog: `Docs/04_WorkLogs/WU-Part1.md`
- Publication: `Docs/05_Publication/candidate-list.md`, `Docs/05_Publication/private-only.md`
- Policy: `Docs/06_Policies/demo-capture-policy.md`, `Docs/06_Policies/docs-authoring-flow-policy.md`, `Docs/06_Policies/work-unit-workflow-policy.md`

## 관련 이슈

- 없음

## 다음 단계

- 사용자 검토 후 Part1 Chapter01-02 PR 게시 여부를 결정한다.
- Part1의 다음 예제 또는 Part2 rasterization 예제에 같은 workflow를 적용한다.
- public subset 후보는 별도 공개 검수 후 확정한다.
