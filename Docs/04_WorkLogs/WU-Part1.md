# WU-Part1 WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-Part1` |
| 코드 범위 | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_RayTracer` |
| pilot 완료 대상 | `Part1_Chapter01-02/02_Bloom` |
| 주요 문서 축 | 코드 폴더 README, `01_Topics`, `02_Verification`, `03_Demos`, `05_Publication` |

## 현재 상태

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| workflow 검증 | 확인 | `02_Bloom`으로 README, Topic, Verification, Demo, Publication 연결을 검증했다. |
| code 조사 | 확인 | current code, raw/reference, origin 기준을 비교했다. |
| source comment inventory | 확인 | raw/reference의 학습 주석을 분류했다. |
| 기존 Docs stale 검토 | 확인 | pilot 초안과 Legacy PartDocs는 참고 전용으로 둔다. |
| README 이관 | 확인 | `02_Bloom` README 정본을 코드 폴더로 이동했다. |
| build/run | 확인 | Debug/Release x64 build와 run을 확인했다. |
| capture/result | 확인 | ChatGPT 생성 입력 이미지로 `result.png` 재생성 확인. input/result 비교 이미지를 `Docs/_assets/captures`에 승격했다. |
| README 계층 | 확인 | Root README는 portfolio archive 첫 화면으로, Chapter/Example README는 각 계층 정본으로 정리했다. |
| Issue/PR | ready | `Docs/07_GitHub/prs/part1_chapter01-02.md` 게시 후보를 준비했다. 실제 게시 여부는 사용자 승인 후 결정한다. |

## 02_Bloom 작업 요약

- archive current code를 문서화 대상 코드로 둔다.
- raw/reference code와 docs는 학습 흔적 확인용으로만 읽고 tracked 문서에는 직접 이해한 설명으로 재작성한다.
- origin은 수정 전 기준점으로 사용한다.
- 기존 `Docs/01_Examples` 파일럿 README는 stale 초안으로 판단하고 정본 위치에서 내린다.
- 예제 README 정본은 `Part1_Chapter01-02/02_Bloom/README.md`로 이동한다.
- `PostProcessingAndBloom` topic은 CPU bloom 처리와 DirectX11 dynamic texture upload 중심으로 정리한다.

## 산출물 상태

| 산출물 | 문서 | 상태 |
| --- | --- | --- |
| Example README | `Part1_Chapter01-02/02_Bloom/README.md` | 작성 |
| Example redirect | 제거 완료 | `Docs/01_Examples` 폐기에 따라 삭제 |
| Verification | `Docs/02_Verification/Part1_Chapter01-02/verification-index.md` | Debug/Release x64 build/run 확인 |
| Topic | `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md` | 작성 |
| Demo | `Docs/03_Demos/Part1_Chapter01-02/demo-index.md` | input/result 비교 이미지 승격 완료 |
| Publication | `Docs/05_Publication/candidate-list.md` | README/Topic/capture result 후보 유지 |

## README 갱신 판단

| README | 갱신 여부 | 이유 |
| --- | --- | --- |
| Root README | 갱신 | 부분 공개 가능한 portfolio archive 첫 화면으로 대표 Topic, current pilot, featured result를 보여주도록 정리했다. |
| Chapter README | 갱신 | `Part1_Chapter01-02`의 목표, 예제 구성, 핵심 Topic, 대표 Demo, 검증 상태를 연결했다. |
| Example README | 갱신 | `01_DX11InitAndImGui`, `02_Bloom` 설명 정본을 코드 폴더에 두고, `02_Bloom` input/result를 연결했다. |
| Docs/Folder README | 부분 갱신 | 산출물 축과 template 안내는 기존 구조를 유지하고, README 계층/갱신 기준은 정책과 template에 반영했다. |

## Pilot 마감 판단

- `02_Bloom`은 새 문서화 workflow의 pilot으로 마감한다.
- README, Topic, Verification, Demo, Publication 연결은 확인했다.
- Debug/Release x64 build/run과 `result.png` 생성은 확인했다.
- `result.png`는 ChatGPT 생성 입력 이미지로 재생성했고 육안상 식별자는 보이지 않는다. input/result 비교 이미지를 `Docs/_assets/captures`에 승격했다.
- Part1 Work Unit 자체는 아직 진행 중이다.
- GitHub PR body 후보는 `Docs/07_GitHub/prs/part1_chapter01-02.md`에 준비했다.

## 다음 작업

1. Part1의 다음 예제에 같은 workflow를 적용한다.
2. `02_Bloom` result image의 public 후보 여부를 `Docs/05_Publication` 기준으로 검토한다.
3. Part1 Chapter01-02 PR 게시 여부를 사용자 검토 후 결정한다.
