# Chapter03 게시 마감과 Markdown 렌더링 교정

## 요약

이 PR은 PR #11 병합 후 확인된 Chapter03 Verification의 의도하지 않은 취소선을 교정하고, Chapter03 Demo Issue와 Progress 게시 상태를 실제 URL 기준으로 마감한다. 같은 문제가 반복되지 않도록 Markdown render validator와 Chapter PR의 pre-merge publication closeout 기준을 추가한다.

## 범위

- 대상: Chapter03 Verification 범위 표기, Demo Issue #12, Progress Issue #7 게시 상태, GitHub workflow 정책과 문서 validator
- 관련 Chapter: `Part1_Chapter03`
- 제외 범위: Verification 표 재설계, Chapter03 예제 코드와 capture 변경, PR #11 수정

## 핵심 개념

- Markdown 렌더링 안전성: 한 줄에 있는 복수 단일-tilde 숫자 범위는 GitHub에서 취소선 delimiter 쌍이 될 수 있으므로 en dash로 표기하고 fixture 기반 validator로 검사한다.
- Publication closeout: Chapter에서 게시하기로 결정한 Demo Issue와 Progress comment는 실제 URL·상태 정본 동기화, 최종 push, Actions와 Browser 검수까지 merge 전에 완료한다.

## 대표 예제

### Part1 Chapter03 게시 마감

Step4 DrawingSphere, Step8 Shadow와 Step13 Transparency의 대표 결과를 [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)에 게시하고 PR #11, Progress Issue #7과 source docs를 연결한다.

- Verification: [Part1 Chapter03 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/fix/chapter03-publication-closeout/Docs/02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [Chapter03 Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/fix/chapter03-publication-closeout/Docs/03_Demos/Part1_Chapter03/demo-index.md)
- Publication: [Candidate List](https://github.com/Razria93/Graphics_Study_Archive/blob/fix/chapter03-publication-closeout/Docs/05_Publication/candidate-list.md)

## 검증

- 기존 문서 validator와 fixture: 통과
- Markdown render validator와 PASS/FAIL fixture: 통과
- GitHub Actions `Docs Validation`: 통과
- Browser: Verification 취소선 제거와 table 렌더링, Demo Issue #12의 heading·링크·대표 visual 확인
- Remote body: Demo Issue #12, 누적 Progress 댓글과 Phase 2-4 완료 댓글의 tracked 후보 일치 확인

## 구현 범위와 한계

- 현재 확인된 같은 root cause의 두 범위 표기만 en dash로 교정하며 Verification 표의 열 구성은 바꾸지 않는다.
- Render validator는 code span, fenced code, escaped tilde, link destination과 의도한 취소선을 제외하고 한 줄의 복수 숫자 범위만 검사한다.
- Chapter03 코드, shader, asset과 capture는 PR #11에서 검증된 상태를 유지한다.

## 문서

- 정책: [GitHub Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/fix/chapter03-publication-closeout/Docs/06_Policies/github-workflow-policy.md)
- 실행 안내: [Work Session Quickstart](https://github.com/Razria93/Graphics_Study_Archive/blob/fix/chapter03-publication-closeout/Docs/98_Tools/work-session-quickstart.md)
- Validator: [Validators](https://github.com/Razria93/Graphics_Study_Archive/blob/fix/chapter03-publication-closeout/Docs/98_Tools/validators/README.md)
- 이전 Chapter PR: [PR #11](https://github.com/Razria93/Graphics_Study_Archive/pull/11)
- Demo Issue: [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)

## 관련 이슈

- [Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)
- [Progress Issue #7 누적 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)
- [Progress Issue #7 Phase 2-4 완료 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5142322616)
