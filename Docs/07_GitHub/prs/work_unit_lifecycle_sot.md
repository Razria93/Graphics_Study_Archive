# Work Unit lifecycle 단계 정의 단일 정본화

## 요약

이 PR은 여러 정책과 실행 문서에 중복되어 있던 Work Unit lifecycle의 단계 순서, 상태 전환, 실패 시 복귀와 종료 조건을 하나의 정책으로 통합한다. 다른 문서는 각자의 산출물·검증·GitHub 실행 책임만 유지하고 lifecycle 정책을 참조하도록 정리한다.

## 범위

- 대상: Work Unit lifecycle 정책과 이를 참조하는 live 정책·router·상태 문서
- 포함 범위: 단계별 진입·완료 조건, 상태 전환, 복귀 조건, finalization과 종료 기준의 단일 정본화
- 제외 범위: WU-A0 기록, Progress payload, 기존 PR body, graphics source·project·asset·capture와 legacy 문서

## Work Contract

- Work type: `Maintenance Work`
- Work Unit: `없음`
- Closes Work Unit: `No`
- Progress impact: `Not required`
- Required artifacts: 정책 변경, 책임 경계, 영향 설명, regression 검증과 PR body

## 주요 변경

- `work-unit-workflow-policy.md`를 lifecycle 단계 순서, 진입·완료 조건, Work Unit 상태 전환, 실패·변경 시 복귀와 종료 조건의 단일 정본으로 확정한다.
- 공통 lifecycle을 Contract, Profile 작업, 사용자 검수, Review, Finalization, Merge gate, Terminal execution과 Handoff의 0단계부터 7단계로 명시한다.
- Finalization 이후 HEAD 변경, actionable review, merge gate 불일치와 remote 동기화 실패가 발생했을 때 돌아갈 단계를 한곳에서 정의한다.
- `work-profile-policy.md`는 Graphics Work와 Maintenance Work의 산출물, profile 내부 작업 순서와 검증 후보 조건만 담당하도록 축소한다.
- `github-workflow-policy.md`는 승인 게이트, branch 보존, 일반 merge와 GitHub remote 실행 방법만 담당하도록 분리한다.
- `work-session-quickstart.md`는 정책을 복제하지 않고 작업 profile과 현재 lifecycle 단계의 정본을 안내하는 실행 router로 정리한다.
- WorkLog 지침과 Work Unit Index는 lifecycle을 재정의하지 않고 당시 기록과 현재 상태 snapshot만 제공하도록 교정한다.
- 예외 closeout의 허용 조건과 금지 범위도 lifecycle 정본에서만 관리한다.

## 검증

- 변경 Markdown 9개 wrap·render·table validator 통과
- 저장소 전체 validator 18종 통과
- 전체 Markdown 475개, table 543개, Demo 문서 103개와 Topic 문서 52개 검사 통과
- 변경 문서 strict UTF-8과 상대 링크 검사 통과
- lifecycle 단계·상태·복귀·종료 정의의 책임 위치 수동 감사 통과
- 제외 범위 변경 없음과 `git diff --check` 통과
- source 변경이 없어 build/run/capture는 수행하지 않음

## 미확인 / 제한

- 기존 WU-A0 WorkLog와 Phase 2-5 Progress payload는 완료 당시 snapshot으로 유지하며 소급 수정하지 않는다.
- 기존 PR body와 review 기록은 당시 상태를 보존하므로 새 책임 경계를 소급 적용하지 않는다.
- 이번 변경은 lifecycle 정책의 책임 위치를 정리하며 GraphicsLab 구현과 graphics 산출물에는 영향을 주지 않는다.

## 문서

- [Work Unit Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/workflow-lifecycle-sot/Docs/06_Policies/work-unit-workflow-policy.md)
- [Work Profile Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/workflow-lifecycle-sot/Docs/06_Policies/work-profile-policy.md)
- [GitHub Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/workflow-lifecycle-sot/Docs/06_Policies/github-workflow-policy.md)
- [Work Session Quickstart](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/workflow-lifecycle-sot/Docs/98_Tools/work-session-quickstart.md)
- [Work Unit Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/workflow-lifecycle-sot/Docs/04_WorkLogs/work-unit-index.md)

## 관련 이슈

- [PR #43](https://github.com/Razria93/Graphics_Study_Archive/pull/43)

## 다음 단계

- Review와 merge를 완료한 뒤 추가 closeout이나 Progress 동기화 없이 WU-R1 계획으로 전환한다.
