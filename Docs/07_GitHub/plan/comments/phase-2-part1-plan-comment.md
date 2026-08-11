## Phase 2-1부터 Phase 2-4까지 완료 기록

## 완료 내용

### Phase 2-1. Part1 Chapter01-02 문서화 workflow 검증

- `Part1_Chapter01-02`의 README, Topic, Verification, Demo와 PR 연결 흐름을 검증했다.
- `02_Bloom` input/result 비교 이미지와 구현 요약을 [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9)에 게시했다.

### Phase 2-2. Part1 pilot 게시 모델 정리

- Progress Issue, 누적 진행 댓글, Chapter/Bundle 완료 댓글과 Chapter PR을 기본 GitHub 게시 객체로 정리했다.
- PR #8 merge 이후 완료 상태와 공개 탐색 링크를 [PR #10](https://github.com/Razria93/Graphics_Study_Archive/pull/10)에서 현재 저장소 상태에 맞췄다.

### Phase 2-3. Part1 Chapter01-02 PR 마감

- PR #8 review 대응과 일반 merge commit 방식 병합을 완료했다.
- 관련 branch는 작업 이력 증빙을 위해 보존했다.

### Phase 2-4. Part1 Chapter03 Ray Tracing 예제 정리

- `Part1_Chapter03` Step4부터 Step14까지의 README, Topic, Verification과 독립 상세 Demo를 연결했다.
- Step4 DrawingSphere, Step8 Shadow와 Step13 Transparency를 대표 흐름으로 확정해 [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)에 게시했다.
- Step10 Texturing과 Step14 CubeEnvironment를 선택 Demo로 유지하고 Step14 CC BY 3.0 attribution을 보존했다.

## 검증

### Phase 2-1

- `01_DX11InitAndImGui`와 `02_Bloom` Debug/Release x64 build/run: 확인
- `02_Bloom` input/result image의 README, Demo와 PR 본문 연결: 확인

### Phase 2-2부터 Phase 2-3까지

- GitHub body, Demo index, Demo document와 Topic validator: 통과
- PR #8 merge 상태, main 대상 공개 링크와 branch 보존 상태: 확인

### Phase 2-4

- Step4부터 Step14까지 Debug/Release x64 build/run: 확인
- 전체 application window capture와 공개 안전성: 확인
- 필수 문서 validator, fixture와 GitHub Actions `Docs Validation`: 통과

## 남은 제한

### Phase 2-1부터 Phase 2-3까지

- `01_DX11InitAndImGui`는 기반 렌더 루프 설명용이라 별도 capture/result를 만들지 않는다.
- `02_Bloom`은 GPU multi-pass pipeline이 아니라 CPU image processing 결과를 dynamic texture로 표시한다.
- 이 기록은 WU-Part1 전체 완료가 아니며 `Portfolio_RayTracer` 범위는 남아 있다.

### Phase 2-4

- 대표 visual은 동일 scene의 단일 변수 A/B가 아니라 순차 구현 milestone이다.
- CPU ray tracing 결과를 DirectX11 dynamic texture로 표시하며 GPU ray tracing pipeline은 포함하지 않는다.
- Step14는 geometry와 recursive ray tracing의 누적판이 아닌 독립 environment sampling 변형이다.

## Related PR

- [PR #8](https://github.com/Razria93/Graphics_Study_Archive/pull/8) - Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom
- [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9) - Part1 Chapter01-02 Bloom Demo
- [PR #10](https://github.com/Razria93/Graphics_Study_Archive/pull/10) - Part1 pilot GitHub 본문과 원격 상태 동기화
- [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11) - Part1 Chapter03 CPU Ray Tracing 단계별 구현과 Demo
- [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12) - Part1 Chapter03 CPU Ray Tracing Demo
