# Part4 Branch Closeout Approval

## 목적

이 문서는 `docs/part4-chapter14-20-workflow` 브랜치의 Part4 local source docs 마감 상태를 최종 검수하고, GitHub body 작성과 원격 게시 단계로 넘어가기 전 승인 범위를 기록한다. 실제 push, Issue/PR 생성, Ready for Review, merge는 사용자 승인 후에만 수행한다.

## 감사 기준선

| 항목 | 확인 결과 |
| --- | --- |
| Branch | `docs/part4-chapter14-20-workflow` |
| Local HEAD | `bf72f0b83d3caca9f5a079cbe1c43ac1d14384c5` |
| Upstream HEAD | `e6fa323238bd808de84d3b1642118595ef8c9a0b` |
| Ahead 범위 | 23 commits |
| Worktree | content diff 1개와 CRLF 표시 파일 다수 |
| 실제 content diff | `Docs/02_Verification/Part3_Chapter10-13/verification-index.md` |
| Part4 GitHub body | Chapter14, Chapter15만 존재. Chapter16부터 Chapter20까지 후보 없음 |
| Remote 변경 | 수행하지 않음 |

## Ahead commit 요약

| 구간 | Commit | 책임 |
| --- | --- | --- |
| Chapter16부터 Chapter20 smoke와 evidence | `60d0cc6`부터 `017c927`까지 | Debug/Release smoke, storyboard 승격 |
| Chapter16부터 Chapter20 Demo/Topic | `4228664`부터 `7892147`까지 | 상세 Demo, Topic 연결, Chapter19·20 Demo 완결 |
| Part4 감사와 상태 정합화 | `069dc2b`부터 `a4686cc`까지 | 감사 기준, storyboard 통일, 상태 문서 정합화 |
| Part4 Topic/ExampleDocs | `ddd2be8`부터 `19a38f9`까지 | Topic 정본, ExampleDocs 전수 작성과 정합화 |
| Closeout | `80b1e25`, `bf72f0b` | 정본 index 동기화, Publication/Topic/WorkLog 마감 문서 정리 |

## Source docs 감사

| 축 | 판정 | 근거 |
| --- | --- | --- |
| Chapter README | 통과 | Chapter14부터 Chapter20까지 Demo와 capture/storyboard 완료 상태를 기록함 |
| ExampleDocs | 통과 | 23개 ExampleDocs가 command argument, Verification, Demo, Topic 연결을 유지함 |
| Verification | 통과 | Part4 verification index와 matrix가 Debug/Release 확인 범위를 분리함 |
| Demo | 통과 | Chapter14부터 Chapter20까지 상세 Demo와 demo-index가 tracked evidence를 연결함 |
| Topic | 통과 | compute/simulation, animation/physics/gameplay, foliage/landscape Topic 연결을 정리함 |
| Publication | 통과 | Chapter16부터 Chapter20까지 storyboard evidence를 검토 필요 후보로 유지하고 원본 asset 직접 게시를 금지함 |
| WorkLog | 통과 | Chapter14·15 remote 마감과 Chapter16부터 Chapter20까지 미게시 상태를 분리함 |
| GitHub body | 후속 필요 | Chapter16부터 Chapter20까지 Demo Issue, Progress comment, PR body 후보가 아직 없음 |

## 검증 결과

| 검증 | 결과 |
| --- | --- |
| Topic document quality validator | 통과, 52 files |
| ExampleDocs quality validator | 통과, 23 files |
| Demo index quality validator | 통과 |
| Part4 closeout Markdown table quality | 통과, 11 files, 22 tables |
| Part4 closeout Markdown render quality | 통과, 11 files |
| Part4 closeout Markdown wrap quality | 통과, 11 files |
| Stale Part4 closeout 문구 검색 | 통과, 추가 match 없음 |

## 승인 전 분리 항목

- `Docs/02_Verification/Part3_Chapter10-13/verification-index.md`에는 Part4 목표모드와 다른 실제 content diff가 남아 있다. 이 변경은 Part4 branch closeout commit에 포함하지 않는다.
- `git status`에는 여러 문서의 CRLF 표시가 남아 있다. content diff 기준으로는 위 Part3 verification 파일만 확인된다.
- 원격 게시 전에는 사용자 변경을 별도 커밋, 보류 또는 제외로 결정해야 한다.

## 승인 대상

### 1. Part4 closeout 감사 문서 commit

이 문서를 추가하고 validator를 통과한 뒤 local commit으로 닫는다.

```bash
git add Docs/04_WorkLogs/reviews/part4-branch-closeout-approval.md
git diff --cached --check
git commit -m "docs: Part4 브랜치 마감 승인안 작성"
```

### 2. GitHub body 후보 작성

원격 게시 전 다음 후보를 `Docs/07_GitHub`에 작성한다.

- Chapter16부터 Chapter20까지 Demo Issue 후보
- Progress 누적 댓글 갱신 후보
- Phase 5-3 또는 Part4 closeout 완료 댓글 후보
- Chapter16부터 Chapter20까지 또는 Part4 closeout PR body 후보

작성 후에는 GitHub body validator, GitHub quality validator, Markdown validator를 실행한다.

### 3. 원격 게시 승인안

GitHub body 후보가 준비되면 별도 preflight에서 다음 원격 변경을 승인받는다.

```bash
git push origin docs/part4-chapter14-20-workflow
gh issue create --title "<Demo Issue title>" --body-file <h1-removed-demo-issue-body>
gh api --method PATCH repos/{owner}/{repo}/issues/comments/5091068690 -F body=@Docs/07_GitHub/plan/plan-progress.md
gh issue comment 7 --body-file Docs/07_GitHub/plan/comments/<part4-closeout-comment>.md
gh pr create --base main --head docs/part4-chapter14-20-workflow --draft --title "<PR title>" --body-file <h1-removed-pr-body>
```

### 4. Ready, review, merge

Draft PR 생성 이후에는 기존 정책 순서를 유지한다.

```text
Ready for Review 감사
-> 사용자 승인 후 gh pr ready
-> review 확인과 대응
-> merge 전 최종 감사
-> 사용자 승인 후 gh pr merge --merge
-> branch 보존 상태 확인
```

## 판정

Part4 local source docs는 GitHub body 후보 작성 전 기준선으로 정렬되어 있다. 현재 branch는 원격보다 23 commits ahead 상태이며, remote 변경은 수행하지 않았다. 다음 단계는 사용자 변경 분리 여부를 확인한 뒤 `Docs/07_GitHub` 후보를 작성하고, 별도 원격 게시 preflight를 만드는 것이다.