# Work Unit 마감 lifecycle 단순화

## 요약

이 PR은 Work Unit 마감을 하나의 작업 branch와 하나의 목표 안에서 끝내도록 GitHub workflow를 6단계로 단순화한다. WU-A0 정본을 PR #42 merge 결과에 맞추고, merge 후 tracked 역동기화와 반복 closeout을 만들던 책임 중복을 제거한다.

## 범위

- Review 전 검사부터 일반 merge와 Progress 동기화까지의 단일 lifecycle
- WorkLog, Work Unit Index, GitHub Index, PR body와 Progress payload 책임 분리
- Pre-merge finalization의 merge 후 관점 작성 기준
- Terminal merge와 조건부 Progress 동기화 승인 기준
- WU-A0 PR #42 merge 결과와 WU-R1 다음 작업 정합화
- 정책, WorkLog와 GitHub body 문서만 변경하며 source, project, asset과 capture/result 제외

## Work Contract

- Work type: `Maintenance`
- Work Unit: `WU-GraphicsLab-Architecture`
- Closes Work Unit: `Yes`
- Progress impact: `Required`
- Required artifacts: maintenance change, rationale, impact, regression verification, PR body, WorkLog, Index와 Progress payload

## 주요 변경

- Workflow를 Review 전 검사, Ready, Review 대응, pre-merge finalization, merge 전 검사와 terminal execution으로 고정한다.
- Finalization에서 tracked 마감 snapshot과 Progress payload를 같은 branch 안에서 완성한다.
- Merge 전 검사는 고정 SHA, Actions, review, conflict와 remote body만 확인하는 read-only gate로 제한한다.
- 일반 merge와 merge 성공을 조건으로 한 Progress 동기화를 하나의 terminal 승인으로 수행할 수 있게 한다.
- GitHub Index에서 live remote 상태를 제거하고 안정적인 PR·Issue와 payload 연결만 유지한다.
- Merge SHA, posted 상태와 comment ID·URL을 tracked 문서에 역동기화하지 않는다.
- PR마다 완료 댓글을 강제하지 않고 의미 있는 Phase, Chapter 묶음 또는 Work Unit당 최대 1개를 사용한다.
- WU-A0의 미래형 merge 대기 문구를 제거하고 PR #42 merge와 WU-R1 진입 상태를 기록한다.

## 검증

- 변경 Markdown wrap·render·table validator 통과
- GitHub body, strict UTF-8와 상대 링크 검사 통과
- 저장소 전체 validator 18종 통과
- WorkLog, Work Unit Index, GitHub Index, PR body와 Progress payload lifecycle 수동 대조
- `git diff --check`
- 새 build/run/capture는 수행하지 않음

## Review와 finalization

- 상위 GitHub body 안내에 남아 있던 PR별 완료 댓글 cadence를 `d808856`에서 의미 있는 마감 단위 기준으로 교정했다.
- Review 대응 댓글에 원인, 대응, 검증과 반영 commit을 기록하고 actionable thread를 resolve했다.
- Finalization에서 WU-A0 WorkLog, Index, PR #43 연결과 Phase 2-5 Progress payload를 같은 snapshot으로 확정했다.

## 미확인 / 제한

- 기존 GitHub comment ID·URL과 posted 이력은 GitHub remote를 정본으로 유지한다.
- 정책 도입 전 Work Unit 기록은 현재 작업과 직접 충돌하는 WU-A0 외에는 소급 재작성하지 않는다.
- GraphicsLab renderer, D3D11 presentation과 RayTracing 기능은 변경하지 않는다.

## 문서

- [Work Unit Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/work-unit-lifecycle-simplification/Docs/06_Policies/work-unit-workflow-policy.md)
- [GitHub Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/work-unit-lifecycle-simplification/Docs/06_Policies/github-workflow-policy.md)
- [Work Session Quickstart](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/work-unit-lifecycle-simplification/Docs/98_Tools/work-session-quickstart.md)
- [Work Unit Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/work-unit-lifecycle-simplification/Docs/04_WorkLogs/work-unit-index.md)
- [Work Unit GitHub Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/work-unit-lifecycle-simplification/Docs/04_WorkLogs/work-unit-github-index.md)
- [WU-A0 WorkLog](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/work-unit-lifecycle-simplification/Docs/04_WorkLogs/work-units/WU-GraphicsLab-Architecture.md)

## 관련 이슈

- [PR #43](https://github.com/Razria93/Graphics_Study_Archive/pull/43)
- [PR #42](https://github.com/Razria93/Graphics_Study_Archive/pull/42)
- [Progress Issue #7](https://github.com/Razria93/Graphics_Study_Archive/issues/7)

## 다음 단계

- 고정된 finalization HEAD를 일반 merge하고 준비된 Phase 2-5 Progress payload를 연속 동기화한다.
- 추가 tracked 마감 작업 없이 WU-R1 Window/Presentation 계획으로 전환한다.
