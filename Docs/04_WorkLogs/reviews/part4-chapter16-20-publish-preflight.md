# Part4 Chapter16-20 Publish Preflight

## 목적

이 문서는 `docs/part4-chapter14-20-workflow` 브랜치에서 Part4 Chapter16부터 Chapter20까지 GitHub body 후보를 게시하기 전 승인 범위와 실행 순서를 기록한다. 실제 `git push`, GitHub Issue 생성, Progress Issue comment 수정, PR 생성은 사용자 승인 후에만 수행한다.

## 기준선

| 항목 | 값 |
| --- | --- |
| Branch | `docs/part4-chapter14-20-workflow` |
| Local HEAD | `0ac58590cd5180b12c724830cd22e7abc4b7f54d` |
| Upstream HEAD | `e6fa323238bd808de84d3b1642118595ef8c9a0b` |
| Ahead 범위 | 26 commits |
| 최근 closeout commits | `3bf629c`, `0ac5859` |
| Worktree | 실제 content diff 1개 유지 |
| 사용자 변경 분리 | `Docs/02_Verification/Part3_Chapter10-13/verification-index.md`는 Part4 게시 commit에 포함하지 않음 |
| Remote 변경 | 수행하지 않음 |

## 작성 후보

| 게시 객체 | Local body | Title source |
| --- | --- | --- |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_part4_chapter16.md` | `Part4 Chapter16 Fluid Simulation Demo` |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_part4_chapter17.md` | `Part4 Chapter17 Skeletal Animation Demo` |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_part4_chapter18.md` | `Part4 Chapter18 Foliage And Landscape Demo` |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_part4_chapter19.md` | `Part4 Chapter19 PhysX Demo` |
| Demo Issue | `Docs/07_GitHub/issues/demo/demo_part4_chapter20.md` | `Part4 Chapter20 Gameplay Physics Demo` |
| Progress Issue body | `Docs/07_GitHub/plan/plan-progress.md` | 기존 Progress Issue 본문 갱신 |
| Progress Issue comment | `Docs/07_GitHub/plan/comments/phase-5-3-plan-comment.md` | `Phase 5-3 완료 기록` |
| Draft PR | `Docs/07_GitHub/prs/part4_chapter16-20.md` | `Part4 Chapter16-20 advanced graphics evidence 정리` |

## 검증 결과

| 범위 | 검증 | 결과 |
| --- | --- | --- |
| Chapter16부터 Chapter20까지 Demo Issue body | `validate-github-quality.ps1` | 통과 |
| Chapter16부터 Chapter20까지 Demo Issue body | Markdown table/render/wrap validators | 통과 |
| Progress body, Phase 5-3 comment, PR body | `validate-github-body.ps1` | 통과 |
| Progress body, Phase 5-3 comment, PR body | Markdown table/render/wrap validators | 통과 |
| Commit integrity | `git diff --cached --check` | 47, 48 commit 전 통과 |

## 승인 전 확인 항목

- `Docs/02_Verification/Part3_Chapter10-13/verification-index.md`의 남은 diff 처리 방식을 결정한다. 이 변경은 Part4 Chapter16부터 Chapter20까지 게시 body 범위 밖이다.
- GitHub Issue body는 첫 H1을 title source로 사용한다. 실제 생성 시 title에는 H1 텍스트를 사용하고 body에는 H1을 제외한 본문을 사용한다.
- Demo Issue number가 생성되면 PR body의 `관련 이슈` 항목을 실제 number로 동기화한다.
- Progress Issue body update와 Phase 5-3 comment 추가는 Issue #7 기준으로 수행한다.
- Draft PR 생성 뒤 Ready for Review, review 대응, merge는 별도 승인 gate를 유지한다.

## 승인 후 실행 순서

### 1. Branch push

```bash
git push origin docs/part4-chapter14-20-workflow
```

### 2. H1 제외 body 임시 파일 생성

```bash
mkdir -p local/github-body-out
for file in \
  Docs/07_GitHub/issues/demo/demo_part4_chapter16.md \
  Docs/07_GitHub/issues/demo/demo_part4_chapter17.md \
  Docs/07_GitHub/issues/demo/demo_part4_chapter18.md \
  Docs/07_GitHub/issues/demo/demo_part4_chapter19.md \
  Docs/07_GitHub/issues/demo/demo_part4_chapter20.md \
  Docs/07_GitHub/prs/part4_chapter16-20.md
do
  name=$(basename "$file")
  tail -n +2 "$file" > "local/github-body-out/$name"
done
```

### 3. Chapter Demo Issue 생성

```bash
gh issue create --title "Part4 Chapter16 Fluid Simulation Demo" --body-file local/github-body-out/demo_part4_chapter16.md
gh issue create --title "Part4 Chapter17 Skeletal Animation Demo" --body-file local/github-body-out/demo_part4_chapter17.md
gh issue create --title "Part4 Chapter18 Foliage And Landscape Demo" --body-file local/github-body-out/demo_part4_chapter18.md
gh issue create --title "Part4 Chapter19 PhysX Demo" --body-file local/github-body-out/demo_part4_chapter19.md
gh issue create --title "Part4 Chapter20 Gameplay Physics Demo" --body-file local/github-body-out/demo_part4_chapter20.md
```

### 4. Progress Issue 본문 갱신

```bash
gh api --method PATCH repos/Razria93/Graphics_Study_Archive/issues/comments/5091068690 -F body=@Docs/07_GitHub/plan/plan-progress.md
```

### 5. Phase 5-3 완료 comment 추가

```bash
gh issue comment 7 --body-file Docs/07_GitHub/plan/comments/phase-5-3-plan-comment.md
```

### 6. Draft PR 생성

```bash
gh pr create --base main --head docs/part4-chapter14-20-workflow --draft --title "Part4 Chapter16-20 advanced graphics evidence 정리" --body-file local/github-body-out/part4_chapter16-20.md
```

### 7. 게시 후 동기화

```text
Demo Issue number 확인
-> Docs/07_GitHub/prs/part4_chapter16-20.md 관련 이슈 갱신
-> 필요 시 Progress comment 또는 WorkLog에 실제 URL 기록
-> 별도 검증과 commit 후 Ready for Review 승인 대기
```

## Rollback 기준

- Issue 또는 PR body가 잘못 게시되면 원격 삭제보다 edit/comment 정정으로 수습한다.
- 잘못된 PR 생성은 close 전 사용자 승인을 다시 받는다.
- push 후 branch history rewrite는 수행하지 않는다.

## 판정

Part4 Chapter16부터 Chapter20까지의 GitHub body 후보와 Phase 5-3 진행 기록은 local 기준으로 준비되어 있다. 원격 변경은 아직 수행하지 않았으며, 다음 단계는 사용자 승인 후 branch push와 GitHub 게시 명령을 순서대로 실행하는 것이다.

## 실행 결과

- Branch push: `origin/docs/part4-chapter14-20-workflow`를 `6875fc0af5ee8c6c9e25bd7f92686bd9eb22b5a2`까지 갱신했다.
- Demo Issue: Chapter16 [#33](https://github.com/Razria93/Graphics_Study_Archive/issues/33), Chapter17 [#34](https://github.com/Razria93/Graphics_Study_Archive/issues/34), Chapter18 [#35](https://github.com/Razria93/Graphics_Study_Archive/issues/35), Chapter19 [#36](https://github.com/Razria93/Graphics_Study_Archive/issues/36), Chapter20 [#37](https://github.com/Razria93/Graphics_Study_Archive/issues/37)을 생성했다.
- Progress Issue: 누적 진행 댓글 [5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)을 갱신하고 Phase 5-3 완료 댓글 [5215315935](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5215315935)을 생성했다.
- Draft PR: [PR #38](https://github.com/Razria93/Graphics_Study_Archive/pull/38)을 생성했다. Base는 `main`, head는 `docs/part4-chapter14-20-workflow`, 생성 시점 head는 `6875fc0af5ee8c6c9e25bd7f92686bd9eb22b5a2`다.
- 후속 동기화: Issue number, Progress comment URL과 PR #38 URL을 WorkLog, GitHub index와 body 후보에 반영한다.