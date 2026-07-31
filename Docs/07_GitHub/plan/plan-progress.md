## Graphics Study 진행 요약

Graphics Study Archive의 Part/Chapter 진행 상태를 누적 기록한다. 상세 내용은 각 정본 문서와 Chapter PR에서 확인한다.

## 완료

### Phase 1. 문서 산출물 축 정리

Docs 구조를 Topic, Verification, Demo, WorkLog, Publication, GitHub body 축으로 재정렬했다. Legacy 문서와 Legacy PartDocs가 최신 정본이 아님을 명시하고, 새 문서화 workflow가 참조할 정책과 템플릿을 정리했다.

Related PR: 예정

### Phase 2-1. Part1 Chapter01-02 문서화 workflow 검증

`01_DX11InitAndImGui`와 `02_Bloom`을 기준으로 코드 폴더 README, Topic, Verification, Demo, Publication, PR body 연결 흐름을 검증했다. `02_Bloom`은 input/result 비교 자료를 README와 Demo 문서에 연결하고 [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9)에 대표 결과와 구현 요약을 게시했다.

Related PR: PR #8 (Merged) - Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom

### Phase 2-2. Part1 pilot 게시 모델 정리

Progress Issue, 누적 진행 댓글, Chapter/Bundle 완료 댓글, Chapter PR의 기본 게시 객체를 기준으로 Part1 pilot 본문 구성을 정리했다.

Related PR: 예정 - GitHub 게시 workflow 보완 PR

### Phase 2-3. Part1 Chapter01-02 PR 마감

PR #8 review 대응과 일반 merge commit 방식 병합을 완료했다. 관련 branch는 작업 이력 증빙을 위해 보존한다.

Related PR: PR #8 (Merged) - Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom

### Phase 2-4. Part1 Chapter03 Ray Tracing 예제 정리

Step4~14 CPU ray tracing 예제를 README, Topic, Verification과 독립 상세 Demo로 연결했다. Debug/Release x64 build/run과 전체 application window capture를 확인하고 Step4 DrawingSphere, Step8 Shadow와 Step13 Transparency를 Chapter 대표 흐름으로 확정했다. Step10 Texturing과 Step14 CubeEnvironment는 선택 Demo로 유지한다.

Related PR: [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11) (Draft) - Part1 Chapter03 CPU Ray Tracing 단계별 구현과 Demo

## 진행 예정

### Phase 2-5. Portfolio_RayTracer 연계 정리

Part1 ray tracing 범위와 Portfolio_RayTracer의 연결 범위, 검증 상태, PR 분할 단위를 정리한다.

Related PR: 예정

## Related PRs

- PR #8 (Merged): Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom
- [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11) (Draft): Part1 Chapter03 CPU Ray Tracing 단계별 구현과 Demo
