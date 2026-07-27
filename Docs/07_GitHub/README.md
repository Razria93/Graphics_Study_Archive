# GitHub Bodies

이 폴더는 GitHub Issue, PR, comment에 게시할 Markdown body의 tracked 정본을 둔다. `Docs/00_Index`부터 `Docs/06_Policies`와 `Docs/_assets`는 source docs이고, 이 폴더는 source docs를 GitHub body로 요약/재구성하는 staging 공간이다.

`Docs/05_Publication`은 public subset 공개 가능성 판단을 맡고, 이 폴더는 private archive repo의 GitHub 게시 후보를 맡는다. 두 책임은 분리한다.

## 책임

- GitHub 게시 후보 본문을 tracked 문서로 관리한다.
- PR, Issue, comment 본문은 게시 전 validator 검수 대상이 된다.
- Docs 정본의 상세 설명을 그대로 복제하지 않고 요약과 링크 중심으로 작성한다.
- GitHub remote 게시, 수정, Ready for Review, merge는 사용자 승인 후에만 진행한다.

Issue/PR body 후보는 첫 H1을 title source로 유지한다. 실제 `gh issue create`/`gh pr create` 직전에는 첫 H1을 제외한 임시 body 파일을 `local/` 아래에 별도로 만들고, tracked `Docs/07_GitHub` 원본은 수정하지 않는다. comment body는 title이 없으므로 H1을 사용하지 않는다. 상세 기준은 `../06_Policies/github-workflow-policy.md`를 따른다.

## 기본 게시 객체

- Progress Issue 1개
- 누적 진행 댓글 1개
- Chapter/Bundle 완료 댓글 여러 개
- Chapter 또는 작은 Chapter 묶음 단위 PR 여러 개

선택 Issue는 Progress Issue 댓글과 Chapter PR만으로 추적하기 어려운 독립 작업, 장기 논의, 별도 승인 범위가 있을 때만 만든다.

## 폴더

| 폴더 | 책임 |
| --- | --- |
| [prs](prs/README.md) | Chapter 또는 Chapter 묶음 단위 PR body 후보 |
| [issues](issues/README.md) | Progress Issue와 필요한 선택 Issue body 후보 |
| [comments](comments/README.md) | 누적 진행 댓글, Chapter/Bundle 완료 댓글, PR comment 후보 |

## Source Docs와의 관계

```text
Docs/00_Index~06_Policies + Docs/_assets
-> source docs / archive 정본 / 상태 기록 / 근거 자료

Docs/07_GitHub
-> GitHub Issue / PR / comment body staging
```

`Docs/07_GitHub`는 source docs를 그대로 복제하지 않는다. GitHub body에는 핵심 요약, 검토 시점의 상태, 필요한 링크만 둔다. 상세 설명과 최신 상태는 README, Topic, Verification, Demo, Publication, WorkLog source docs를 기준으로 확인한다.

## local과의 관계

```text
local/ 임시 초안
-> Docs/07_GitHub 게시 후보
-> GitHub remote
-> local/ 게시 후 snapshot
```

- `local/`은 임시 초안, 게시 후 사본, 검토 메모를 둘 수 있는 작업 공간이며 언제 비워도 되는 공간이다.
- `Docs/07_GitHub`는 GitHub에 게시하기 직전 검수할 tracked 게시 후보 정본이다.
- GitHub remote에 게시한 뒤 실제 본문 사본이 필요하면 `local/` 하위 snapshot으로 남긴다.
- `Docs/05_Publication`은 public subset 판단 정본이며 GitHub body 저장소가 아니다.

## PR 단위

PR 기본 단위는 Chapter 또는 Chapter 묶음이다. Part는 milestone, Progress Issue, WorkLog 묶음으로 다룬다.

Part 단위 PR은 예제가 적고 변경 범위가 작을 때만 예외로 허용한다. 예제가 많거나 demo/verification 범위가 큰 Part는 Chapter 또는 Topic/Demo cluster로 나눈다.
