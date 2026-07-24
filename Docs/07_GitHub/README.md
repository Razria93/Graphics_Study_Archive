# GitHub Bodies

이 폴더는 GitHub Issue, PR, comment에 게시할 Markdown body의 tracked 정본을 둔다.

`Docs/05_Publication`은 public subset 공개 가능성 판단을 맡고, 이 폴더는 private archive repo의 GitHub 게시 후보를 맡는다. 두 책임은 분리한다.

## 책임

- GitHub 게시 후보 본문을 tracked 문서로 관리한다.
- PR, Issue, comment 본문은 게시 전 validator 검수 대상이 된다.
- Docs 정본의 상세 설명을 그대로 복제하지 않고 요약과 링크 중심으로 작성한다.
- GitHub remote 게시, 수정, Ready for Review, merge는 사용자 승인 후에만 진행한다.

## 폴더

| 폴더 | 책임 |
| --- | --- |
| [prs](prs/README.md) | Chapter 또는 Chapter 묶음 단위 PR body 후보 |
| [issues](issues/README.md) | Work Unit Issue와 필요한 보조 Issue body 후보 |
| [comments](comments/README.md) | Plan Issue 진행 댓글, WorkLog 댓글, PR comment 후보 |

## local과의 관계

```text
local/github/draft
-> Docs/07_GitHub
-> GitHub remote
-> local/github/snapshots
```

- `local/github/draft`는 임시 초안이며 언제 비워도 되는 공간이다.
- `Docs/07_GitHub`는 게시 후보 정본이다.
- `local/github/snapshots`는 게시 후 실제 본문 사본이 필요할 때만 둔다.
- `local/github/public`은 사용하지 않는다.

## PR 단위

PR 기본 단위는 Chapter 또는 Chapter 묶음이다. Part는 milestone, Plan Issue, WorkLog 묶음으로 다룬다.

Part 단위 PR은 예제가 적고 변경 범위가 작을 때만 예외로 허용한다. 예제가 많거나 demo/verification 범위가 큰 Part는 Chapter 또는 Topic/Demo cluster로 나눈다.
