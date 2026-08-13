# WU-A0 architecture closeout과 Work Unit 마감 정책

## 요약

이 PR은 WU-A0 architecture 작업 PR #41의 review와 merge 결과를 정본에 연결하고, 작업 PR과 Work Unit closeout PR을 분리하는 운영 정책을 정한다.

작업 PR이 review·merge되기 전에 Work Unit을 `마감`으로 표시하지 않는다. 관련 작업 PR이 merge된 뒤 별도 closeout PR에서 최종 상태를 검수하고, Ready for Review 이후 review와 merge 승인을 거쳐 finalization commit에서 `마감` 전환을 준비한다.

## 범위

- Work Unit 구현 완료와 운영 마감의 분리
- 작업 PR merge 이후 closeout branch와 maintenance PR을 사용하는 흐름
- `진행 중`, `검증 중`, `마감` 상태 전환 조건
- Closeout PR의 책임, 금지 범위와 terminal transition 정의
- PR #41 review 대응, Docs Validation과 일반 merge 결과 기록
- WU-A0 WorkLog, Work Unit Index와 GitHub Index 정합화
- 정책과 closeout 문서만 변경하며 source, project, asset과 capture/result 변경 제외

## 주요 변경

- 작업 PR에서는 Work Unit을 `진행 중`으로 유지하고 `검증 중`은 build/run/capture를 실제로 확인하는 기간에만 사용한다.
- 관련 작업 PR merge 후 최신 기본 branch에서 `docs/{work-unit}-closeout` branch를 만든다.
- Closeout PR은 WorkLog, Work Unit Index, GitHub Index와 필요한 Progress 게시 후보만 최종화한다.
- Draft closeout PR에서는 `진행 중`을 유지하고 사용자 검수 후 Ready for Review로 전환한다.
- Review 완료와 merge 승인 후 finalization commit에서 `마감` 전환, PR 연결과 Progress 게시 후보를 준비한다.
- Finalization commit의 Actions와 review 상태를 다시 확인한 뒤 일반 merge commit 방식으로 병합한다.
- Finalization commit을 포함한 closeout PR이 기본 branch에 merge되면 Work Unit의 `마감` 상태가 정본에 반영된다.
- Closeout PR은 별도 Work Unit으로 등록하지 않으며 추가 closeout PR을 만들지 않는다.
- WU-A0에 PR #41의 P2 review 대응 commit `e943237`, Docs Validation 2건과 일반 merge commit `9566afa`를 기록한다.
- Draft 사용자 검수를 완료했으며 WU-A0는 Ready review와 finalization이 남아 있어 `진행 중`을 유지한다.
- Closeout merge 이후 WU-R1 Window/Presentation 계획으로 전환한다.

## 검증

- 저장소 전체 문서 validator 18종 통과
- 변경 Markdown wrap, render와 table validator 통과
- 변경 문서 strict UTF-8과 상대 링크 검사 통과
- `git diff --check origin/main...HEAD` 통과
- source, project, tracked asset과 raw/reference 변경 없음 확인
- 새 build/run/capture는 수행하지 않으며 PR #41의 문서 검증 결과를 유지함

## 미확인 / 제한

- Ready for Review 직전 상태에서는 WU-A0를 `마감`으로 전환하지 않는다.
- Ready for Review, review 대응, merge 승인, finalization commit과 closeout PR merge는 후속 단계로 남긴다.
- Progress Issue #7 누적 진행판과 완료 댓글 후보는 finalization commit에서 확정하고 실제 원격 게시는 closeout merge 이후 별도 승인으로 수행한다.
- WU-R1 Window/Presentation 계획과 구현은 closeout merge 이후 별도 branch에서 진행한다.
- Renderer code, D3D11 presentation, RayTracing 기능과 asset은 변경하지 않는다.

## 문서

- Work Unit 흐름: [Work Unit Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/wu-a0-closeout/Docs/06_Policies/work-unit-workflow-policy.md)
- GitHub 운영: [GitHub Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/wu-a0-closeout/Docs/06_Policies/github-workflow-policy.md)
- Work Unit 상태: [Work Unit Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/wu-a0-closeout/Docs/04_WorkLogs/work-unit-index.md)
- GitHub 연결: [Work Unit GitHub Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/wu-a0-closeout/Docs/04_WorkLogs/work-unit-github-index.md)
- WU-A0 기록: [WU-GraphicsLab-Architecture](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/wu-a0-closeout/Docs/04_WorkLogs/work-units/WU-GraphicsLab-Architecture.md)
- Architecture 정본: [GraphicsLab Architecture](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/wu-a0-closeout/Portfolio_GraphicsLab/ARCHITECTURE.md)

## 관련 이슈

- [PR #41](https://github.com/Razria93/Graphics_Study_Archive/pull/41)
- [WU-R0 PR #40](https://github.com/Razria93/Graphics_Study_Archive/pull/40)
- [Progress Issue #7](https://github.com/Razria93/Graphics_Study_Archive/issues/7)

## 다음 단계

- Draft PR에서 closeout 정책, WU-A0 merge 증빙과 상태 전환 시점을 검수한다.
- Ready for Review 전환 후 review와 필요한 대응을 마친다.
- Merge 승인 후 finalization commit에서 closeout PR 번호, WU-A0 `마감` 상태와 Progress 게시 후보를 확정한다.
- Finalization commit의 Actions와 review 상태를 다시 확인한 뒤 일반 merge commit으로 병합한다.
- 일반 merge commit으로 closeout PR을 merge하고 기본 branch의 최종 상태를 확인한다.
- WU-R1에서 Win32 window lifecycle, resize, CPU framebuffer upload와 D3D11 presentation을 계획한다.
