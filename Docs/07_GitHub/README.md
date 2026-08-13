# GitHub Bodies

이 폴더는 GitHub Issue, PR, comment에 게시할 Markdown body의 tracked 정본을 둔다. `Docs/00_Index`부터 `Docs/06_Policies`와 `Docs/_assets`는 source docs이고, 이 폴더는 source docs를 GitHub body로 요약/재구성하는 staging 공간이다.

## 책임

- GitHub 게시 후보 본문을 tracked 문서로 관리한다.
- PR, Issue, comment 본문은 게시 전 validator 검수 대상이 된다.
- Docs 정본의 상세 설명을 그대로 복제하지 않고 요약과 링크 중심으로 작성한다.
- GitHub remote 게시, 수정, Ready for Review, merge는 사용자 승인 후에만 진행한다.

Issue/PR body 후보는 첫 H1을 title source로 유지한다. 실제 `gh issue create`와 `gh pr create`에서는 title을 H1에서 사용하고 body는 tracked 정본을 그대로 게시한다. comment body는 title이 없으므로 H1을 사용하지 않는다.

## 폴더

| 폴더 | 책임 |
| --- | --- |
| [plan](plan/README.md) | Progress Issue 본문, 누적 진행 댓글, Phase 완료 댓글 정본 |
| [prs](prs/README.md) | Chapter 또는 Chapter 묶음 단위 PR body 후보 |
| [issues](issues/README.md) | 선택 Issue body 후보 |

## 기본 운영 규칙

- Progress Issue 정본은 `plan/plan-body.md` 1개를 유지한다.
- 누적 진행 댓글 정본은 `plan/plan-progress.md` 1개를 유지한다.
- 의미 있는 Phase, Chapter 묶음 또는 Work Unit이 마감될 때 `plan/plan-progress.md`를 갱신한다.
- 같은 마감 단위에는 완료 댓글 payload를 최대 1개 작성하며 여러 관련 PR을 하나로 묶을 수 있다.
- 선택 Issue는 `issues/work-unit`, `issues/verification`, `issues/demo` 하위에서 필요할 때만 만든다.

## Source Docs와의 관계

```text
Docs/00_Index부터 Docs/06_Policies까지 + Docs/_assets
-> source docs / archive 정본 / 상태 기록 / 근거 자료

Docs/07_GitHub
-> GitHub Issue / PR / comment body staging
```

`Docs/07_GitHub`는 source docs를 그대로 복제하지 않는다. GitHub body에는 핵심 요약, 검토 시점의 상태, 필요한 링크만 둔다.

## local과의 관계

```text
local/ 임시 초안
-> Docs/07_GitHub 게시 후보
-> GitHub remote
-> local/ 게시 후 snapshot
```

- `local/`은 임시 초안, 게시 후 사본, 검토 메모를 둘 수 있는 작업 공간이다.
- `Docs/07_GitHub`는 GitHub에 게시하기 직전 검수할 tracked 게시 후보 정본이다.
- GitHub remote에 게시한 뒤 실제 본문 사본이 필요하면 `local/` 하위 snapshot으로 남긴다.
