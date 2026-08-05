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

Step4~14 CPU ray tracing 예제를 README, Topic, Verification과 독립 상세 Demo로 연결했다. Debug/Release x64 build/run과 전체 application window capture를 확인하고 Step4 DrawingSphere, Step8 Shadow와 Step13 Transparency를 Chapter 대표 흐름으로 확정해 [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)에 게시했다. Step10 Texturing과 Step14 CubeEnvironment는 선택 Demo로 유지한다.

Related PR: [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11) (Merged) - Part1 Chapter03 CPU Ray Tracing 단계별 구현과 Demo

### Phase 3-1. Part2 Chapter04 Software Rasterization

Step1 Triangle부터 Step10 Lights까지와 사용자 Personal Extension인 Step1A Triangle To Circle을 README, Topic, Verification과 독립 상세 Demo로 연결했다. Debug/Release x64 build/run과 전체 application window capture를 확인하고 Step8을 Chapter 대표, Step10을 기술 보조, Step1A를 사용자 확장, Step4를 시간 변화 Demo로 정리했다. Publication 판정을 완료하고 [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14)에 Step1A, Step8과 Step10 공개 구성을 게시했다.

Related PR: [PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15) (Merged) - Part2 Chapter04 CPU Software Rasterization 단계별 정규화와 Demo

### Phase 3-2. Part2 Chapter05-08

Chapter05–08의 30개 예제를 순서대로 재검증하고 Example README, Topic, Verification과 독립 상세 Demo로 연결했다. Chapter05는 affine transformation API 비교, Chapter06은 DirectX11 pipeline·lighting·resize, Chapter07은 procedural modeling과 SphereMapping 흐름으로 정리했다. 공개 안전한 대표 visual을 Chapter05 [Demo Issue #17](https://github.com/Razria93/Graphics_Study_Archive/issues/17), Chapter06 [Demo Issue #18](https://github.com/Razria93/Graphics_Study_Archive/issues/18), Chapter07 [Demo Issue #19](https://github.com/Razria93/Graphics_Study_Archive/issues/19)에 게시하고, 외부 asset 권리 근거가 충분하지 않은 Chapter08은 archive 검증 상태로 유지한다.

Related PR: [PR #20](https://github.com/Razria93/Graphics_Study_Archive/pull/20) (Merged) - Part2 Chapter05-08 DirectX11 Pipeline·Modeling·Shader 예제 정규화와 Demo

### Phase 4-1. Part3 Chapter09 User Interaction

Step1–6의 camera, GPU·CPU picking, quaternion rotation, VirtualTrackball과 MouseDragMove를 재검증하고 정적 storyboard와 상세 Demo로 연결했다. 대표 interaction은 [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21)에 게시했다.

Related PR: [PR #23](https://github.com/Razria93/Graphics_Study_Archive/pull/23) (Merged) - Part3 Chapter09 User Interaction 구현과 Demo

### Phase 4-2. Part3 Chapter10-13

Chapter10→13의 21개 예제를 Geometry Pipeline, Texturing Techniques, PBR와 Light/Shadow 흐름으로 재검증하고 Example README, Topic, Verification과 독립 상세 Demo로 연결했다. Chapter10 [Demo Issue #25](https://github.com/Razria93/Graphics_Study_Archive/issues/25), Chapter11 [Demo Issue #26](https://github.com/Razria93/Graphics_Study_Archive/issues/26), Chapter12 [Demo Issue #27](https://github.com/Razria93/Graphics_Study_Archive/issues/27), Chapter13 [Demo Issue #28](https://github.com/Razria93/Graphics_Study_Archive/issues/28)에 Chapter별 rendered evidence와 GitHub 본문을 게시했다.

Related PR: [PR #24](https://github.com/Razria93/Graphics_Study_Archive/pull/24) - Part3 Chapter10-13 Geometry·Texturing·PBR·Light/Shadow 단계별 구현과 Demo

## 진행 중

### Phase 5-1. Part4 Chapter14 Compute Shader Evidence

Chapter14 `Ex1401`~`Ex1408` compute shader 예제를 Debug x64 기준으로 재검증하고, `Ex1402`, `Ex1404`~`Ex1407`의 centered client-visible screenshot과 stdout/code evidence를 상세 Demo, [Demo Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29)와 PR body 후보로 연결했다. Phase 5-1 완료 댓글은 게시했고 PR remote 게시는 후속 승인 범위로 둔다.

Related PR: 예정 - Part4 Chapter14 Compute Shader evidence 문서화와 capture 승격

## 진행 예정

### Phase 2-5. Portfolio_RayTracer 연계 정리

Part1 ray tracing 범위와 Portfolio_RayTracer의 연결 범위, 검증 상태, PR 분할 단위를 정리한다.

Related PR: 예정

## Related PRs

- PR #8 (Merged): Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom
- [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11) (Merged): Part1 Chapter03 CPU Ray Tracing 단계별 구현과 Demo
- [PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15) (Merged): Part2 Chapter04 CPU Software Rasterization 단계별 정규화와 Demo
- [PR #20](https://github.com/Razria93/Graphics_Study_Archive/pull/20) (Merged): Part2 Chapter05-08 DirectX11 Pipeline·Modeling·Shader 예제 정규화와 Demo
- [PR #23](https://github.com/Razria93/Graphics_Study_Archive/pull/23) (Merged): Part3 Chapter09 User Interaction 구현과 Demo
- [PR #24](https://github.com/Razria93/Graphics_Study_Archive/pull/24): Part3 Chapter10-13 Geometry·Texturing·PBR·Light/Shadow 단계별 구현과 Demo
