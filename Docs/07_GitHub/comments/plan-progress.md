# Plan Progress Comment

이 문서는 상위 `[Plan]` Issue의 첫 누적 진행 댓글 후보 본문이다. 실제 GitHub Issue comment를 생성하거나 수정하기 전에는 대상 Issue, 사용할 본문, 실행할 `gh` 명령, 예상 변경 요약을 사용자에게 보고하고 승인받는다.

## MVP 진행 요약

이 댓글은 Graphics Study Archive의 문서화 Work Unit과 Chapter PR 진행 상태를 누적 요약한다. 각 Work Unit의 상세 설명, Topic, Demo capture/result, Verification 기록은 별도 WorkLog, PR, Docs 정본에서 관리한다.

## 완료

### Phase 1. 문서 산출물 축 정리

Docs 구조를 Topic, Verification, Demo, WorkLog, Publication, GitHub body 축으로 재정렬했다. Legacy 문서와 Legacy PartDocs가 최신 정본이 아님을 명시하고, 새 문서화 workflow가 참조할 정책과 템플릿을 정리했다.

Related PR: PR #6

### Phase 2-1. Part1 Chapter01-02 문서화 workflow 검증

`01_DX11InitAndImGui`와 `02_Bloom`을 기준으로 코드 폴더 README, Topic, Verification, Demo, Publication, PR body 연결 흐름을 검증했다. `02_Bloom`은 input/result 비교 자료를 README와 Demo 문서에 연결해 visual result 승격 흐름을 확인했다.

Related PR: 예정 - `Docs/07_GitHub/prs/part1_chapter01-02.md`

### Phase 2-2. Part1 Work Unit Issue 후보 준비

`WU-Part1`의 범위, 완료 조건, 후속 판단 항목을 GitHub Issue 후보로 정리했다. 이 Issue는 WorkLog와 PR body를 대체하지 않고 Part1 흐름을 추적하는 상위 작업 단위로 사용한다.

Related Issue: 예정 - `Docs/07_GitHub/issues/work-unit_part1.md`

## 진행 예정

### Phase 2-3. Part1 Chapter01-02 GitHub 게시 여부 결정

준비된 Work Unit Issue 후보와 Chapter01-02 PR 후보를 사용자 검토 후 GitHub에 게시할지 결정한다. 게시하는 경우 gh 실행 계획, 대상 파일, 예상 변경을 먼저 보고한다.

Related PR: 예정 - `Docs/07_GitHub/prs/part1_chapter01-02.md`

### Phase 2-4. Part1 Chapter03 Ray Tracing 예제 정리

ray tracing 단계별 예제를 코드 폴더 README, Topic, Verification, Demo 기준으로 정리한다. 대표 visual result 후보와 `Portfolio_RayTracer` 연결 여부를 함께 판단한다.

Related PR: 예정

## Related PRs

- PR #6: Structure cleanup workflow 정리
- 예정: Part1 Chapter01-02 문서화 workflow 검증 PR