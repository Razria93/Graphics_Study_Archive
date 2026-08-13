# WU-A0 architecture closeout과 Work Unit 마감 정책

## 요약

이 PR은 WU-A0 architecture 작업 PR #41의 review와 merge 결과를 정본에 연결하고, 같은 작업 PR에서 Work Unit finalization을 완료하는 기본 정책을 정한다.

작업 PR review가 끝나기 전에는 Work Unit을 `마감`으로 표시하지 않는다. Review 완료와 finalization 진행 승인 후 같은 작업 branch의 finalization commit에서 최종 상태와 Progress 게시 후보를 확정한다. Finalization이 포함된 최신 PR HEAD를 재검증하고 merge 실행 승인을 다시 받은 뒤 merge해 `마감` 상태를 기본 branch에 반영한다.

PR #41은 이 정책 확정 전에 이미 merge됐으므로 PR #42를 누락된 마감 기록과 정책 교정을 위한 전환기 예외 closeout PR로 사용한다.

## 범위

- Work Unit 구현 완료와 운영 마감 시점의 구분
- 같은 작업 branch와 PR에서 review 이후 finalization을 완료하는 기본 흐름
- `진행 중`, `검증 중`, `마감` 상태 전환 조건
- 별도 closeout branch와 PR을 허용하는 예외 조건
- 예외 closeout PR의 책임, 금지 범위와 terminal transition 정의
- PR #41 review 대응, Docs Validation과 일반 merge 결과 기록
- WU-A0를 전환기 closeout 예외로 기록하고 WorkLog와 Index 정합화
- 정책과 closeout 문서만 변경하며 source, project, asset과 capture/result 변경 제외

## 주요 변경

- 작업 PR에서는 review와 finalization 전까지 Work Unit을 `진행 중`으로 유지하고 `검증 중`은 build/run/capture를 실제로 확인하는 기간에만 사용한다.
- Review 완료와 finalization 진행 승인 후 같은 작업 branch의 finalization commit에서 `마감` 전환, WorkLog, Index, PR 연결과 Progress 게시 후보를 확정한다.
- Finalization commit의 Actions와 review 상태를 다시 확인하고 최신 PR HEAD의 merge 실행 승인을 다시 받은 뒤 작업 PR을 일반 merge commit 방식으로 병합한다.
- 별도 closeout branch는 여러 작업 PR 종합, post-merge 사실 기록, 누락된 finalization 복구 또는 광범위한 정책·Index 정리에만 사용한다.
- 예외 closeout PR은 새로운 기능을 포함하지 않는 terminal maintenance PR이며 별도 Work Unit이나 추가 closeout PR을 만들지 않는다.
- WU-A0에 PR #41의 P2 review 대응 commit `e943237`, Docs Validation 2건과 일반 merge commit `9566afa`를 기록한다.
- PR #41이 이미 merge되어 PR #42를 전환기 예외 closeout PR로 사용한다.
- PR #42 Draft 사용자 검수, Ready 전환과 P2 review 2건 대응을 완료했다.
- `92581d3`에서 finalization 이후 최신 PR HEAD의 merge 실행 승인을 다시 받도록 승인 게이트를 분리하고, Progress 원격 댓글을 merge 후 동기화하도록 quickstart를 교정했다.
- Finalization 진행 승인에 따라 WU-A0 `마감`, PR #42 연결과 Phase 2-5 Progress 게시 후보를 확정했다.
- WU-R1부터는 예외 조건이 없으면 같은 작업 PR finalization을 기본으로 사용한다.
- Closeout merge 이후 WU-R1 Window/Presentation 계획으로 전환한다.

## 검증

- 저장소 전체 문서 validator 18종 통과
- Markdown 472개와 table 536개 wrap, render와 table validator 통과
- 변경 문서 strict UTF-8과 상대 링크 검사 통과
- `git diff --check` 통과
- Review 대응 commit `92581d3`의 Docs Validation 2건 통과
- PR #42 review thread 2건 대응 댓글과 resolve 완료
- source, project, tracked asset과 raw/reference 변경 없음 확인
- 새 build/run/capture는 수행하지 않으며 PR #41의 문서 검증 결과를 유지함

## 미확인 / 제한

- Finalization commit을 포함한 최신 PR HEAD의 Actions와 review 상태 확인, merge 실행 승인과 merge는 후속 단계로 남긴다.
- Progress Issue #7 누적 진행판과 Phase 2-5 완료 댓글의 실제 원격 게시는 closeout merge 이후 별도 승인으로 수행한다.
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

- Finalization commit의 Actions와 review 상태를 확인한다.
- 최신 PR HEAD와 최종 변경 범위를 보고하고 merge 실행 승인을 받은 뒤 일반 merge commit으로 병합한다.
- 기본 branch의 최종 상태를 확인하고 Progress Issue #7을 merge된 tracked 후보와 동기화한다.
- WU-R1에서 Win32 window lifecycle, resize, CPU framebuffer upload와 D3D11 presentation을 계획한다.
