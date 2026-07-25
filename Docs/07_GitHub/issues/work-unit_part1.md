# WU-Part1 문서화 workflow 추적

## 요약

이 Issue는 `WU-Part1`의 Part1 기초 예제 문서화 흐름을 추적한다. Chapter01-02 pilot 결과를 기준으로 Part1 후속 예제와 `Portfolio_RayTracer` 기초 연결 여부를 이어서 판단한다.

## 목표

Part1 범위의 예제를 코드 폴더 README, Topic, Verification, Demo, WorkLog, PR 후보로 연결하는 workflow를 안정화한다. `Part1_Chapter01-02`는 pilot으로 마감하고, `Part1_Chapter03`과 `Portfolio_RayTracer` 기초 연결은 후속 작업으로 분리해 진행한다.

## 범위

- Work Unit: `WU-Part1`
- 대상 Chapter 또는 Chapter 묶음: `Part1_Chapter01-02`, `Part1_Chapter03`
- 대표 예제: `01_DX11InitAndImGui`, `02_Bloom`, Part1 ray tracing step 후보
- 제외 범위: Part2 이후 예제, Part4 compute/simulation, public subset 게시 확정, GitHub remote 게시 실행

## 핵심 작업

- [x] `Part1_Chapter01-02` Chapter README를 정리한다.
- [x] `01_DX11InitAndImGui` README를 기반 렌더 루프 설명용 예제로 정리한다.
- [x] `02_Bloom` README를 code folder 정본 문서로 정리한다.
- [x] `02_Bloom` Topic, Verification, Demo, Publication 후보를 연결한다.
- [x] `Part1_Chapter01-02` PR body 후보를 작성한다.
- [ ] `Part1_Chapter03` ray tracing 예제 목록과 대표 demo 후보를 검토한다.
- [ ] `Portfolio_RayTracer`를 Part1 ray tracing 확장 작업으로 연결할지 판단한다.

## 검증 기준

- Debug x64 build/run: `Part1_Chapter01-02`의 `01_DX11InitAndImGui`, `02_Bloom` 성공 확인
- Release x64 build/run: `Part1_Chapter01-02`의 `01_DX11InitAndImGui`, `02_Bloom` 성공 확인
- capture/result: `02_Bloom` input/result image 확보, `01_DX11InitAndImGui`는 별도 capture 제외
- validator: `Docs/98_Tools/validators/validate-github-body.ps1` 통과 필요

## Demo/Capture 필요 여부

- screenshot: `02_Bloom`은 input/result 비교 이미지로 대체한다.
- video: Chapter01-02 범위에서는 제외한다.
- result image: `02_Bloom` result image를 사용한다.
- 제외 사유: `01_DX11InitAndImGui`는 기반 렌더 루프 설명용 예제라 별도 visual result보다 README와 build/run 검증이 더 적합하다.

## 완료 조건

- [x] `Part1_Chapter01-02` README 계층이 정리되어 있다.
- [x] `02_Bloom` capture/result가 Demo와 README에 연결되어 있다.
- [x] `Part1_Chapter01-02` build/run 상태가 Verification에 기록되어 있다.
- [x] `Part1_Chapter01-02` PR 후보가 `Docs/07_GitHub/prs`에 준비되어 있다.
- [ ] Part1 Chapter01-02 PR 게시 여부를 사용자 검토 후 결정한다.
- [ ] Part1 Chapter03 또는 다음 Work Unit 진행 방향을 결정한다.

## 관련 문서

- WorkLog: `Docs/04_WorkLogs/active/WU-Part1.md`
- Example README: `Part1_Chapter01-02/01_DX11InitAndImGui/README.md`, `Part1_Chapter01-02/02_Bloom/README.md`
- Topic: `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`
- Verification: `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`
- Demo: `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`
- Publication: `Docs/05_Publication/candidate-list.md`
- PR 후보: `Docs/07_GitHub/prs/part1_chapter01-02.md`

## 제외 범위

- GitHub Issue 생성 또는 원격 게시 실행은 이 파일 작성 범위에 포함하지 않는다.
- `Part1_Chapter03`의 build/run/capture 검증은 후속 작업에서 진행한다.
- public subset 게시 확정은 `Docs/05_Publication` 기준으로 별도 판단한다.