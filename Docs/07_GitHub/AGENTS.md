# Repository Guidelines

## 책임

이 폴더는 GitHub Issue, PR, comment body 후보를 둔다. 문서는 한국어 평서형으로 작성한다.

## 작성 기준

- GitHub 게시 후보만 둔다.
- 내부 조사 메모, draft 문구, local-only 경로, 민감 정보는 남기지 않는다.
- 상세 설명은 Example README, Topic, Verification, Demo, Publication 정본으로 링크한다.
- Demo Issue는 독립적으로 읽히는 curated publication view로 작성한다.
- Demo Issue는 대표 visual과 핵심 구현 요약을 자체 포함하고 상세 Demo 전체를 복제하지 않는다.
- PR body는 README를 미러링하지 않고 GitHub review용 요약과 링크 허브로 작성한다.
- PR 기본 단위는 Chapter 또는 Chapter 묶음이며, Part 단위 PR은 예외로만 사용한다.
- `핵심 개념`과 `대표 예제`는 표보다 문단과 짧은 리스트를 기본으로 한다.
- `Docs/05_Publication`을 PR body 저장소처럼 사용하지 않는다.

## 승인 기준

- 이 폴더의 문서를 GitHub remote에 게시하거나 수정하려면 사용자 승인을 먼저 받는다.
- `gh issue create`, `gh pr create`, `gh issue comment`, `gh pr comment`, Ready for Review, merge는 임의로 실행하지 않는다.
- 게시 전 validator 결과와 변경 범위를 보고한다.
