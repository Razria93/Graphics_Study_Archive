# Part4 Chapter14 Ready 전 원격 게시 승인안

이 문서는 Chapter14 `Ready for Review` 전 단계에서 필요한 push, GitHub Issue, Progress comment와 PR 생성 범위를 요약한 preflight snapshot이다. 실제 remote 변경은 사용자 승인 후에만 수행한다.

## 현재 로컬 상태

- 작업 branch는 `docs/part4-chapter14-20-workflow`다.
- 현재 branch는 `origin/docs/part4-chapter14-20-workflow`를 upstream으로 추적한다.
- `origin/main..HEAD` 대상 커밋은 Chapter14 baseline, evidence, capture UI, Demo/GitHub 후보, Progress 후보 정렬과 게시 URL 동기화 커밋이다.
- 원격 branch `origin/docs/part4-chapter14-20-workflow`가 생성되어 있다.
- 현재 branch head 기준 Draft PR #30이 있다.
- [Docs/07_GitHub/issues/demo/demo_part3_chapter10.md](../../07_GitHub/issues/demo/demo_part3_chapter10.md)는 content diff 없이 LF/CRLF working copy 표시만 남아 있다.

## 승인 대상

### 1. Branch push

목적은 branch URL 기반 이미지와 문서 링크가 GitHub remote에서 렌더링되는지 확인할 수 있게 만드는 것이다.

```bash
git push -u origin docs/part4-chapter14-20-workflow
```

push 후에는 local HEAD, tracking ref와 remote branch head가 같은 commit인지 확인한다.

### 2. Demo Issue 생성

title source는 [Chapter14 Demo Issue 후보](../../07_GitHub/issues/demo/demo_part4_chapter14.md)의 첫 H1이다.

```text
Part4 Chapter14 Compute Shader Evidence Demo
```

remote body는 첫 H1과 바로 뒤 빈 줄을 제거한 `## 요약`부터 사용한다.

```bash
gh issue create \
  --title "Part4 Chapter14 Compute Shader Evidence Demo" \
  --body-file <h1-removed-demo-issue-body>
```

Issue 생성 후 실제 Issue 번호와 URL을 확인한다.

### 3. Progress 누적 진행 댓글 수정

대상은 Progress Issue [#7](https://github.com/Razria93/Graphics_Study_Archive/issues/7)의 누적 진행 댓글이다.

```bash
gh api \
  --method PATCH \
  repos/{owner}/{repo}/issues/comments/5091068690 \
  -F body=@Docs/07_GitHub/plan/plan-progress.md
```

수정 후 comment permalink와 원격 렌더링을 확인한다.

### 4. Phase 5-1 완료 댓글 생성

본문은 [Phase 5-1 완료 기록](../../07_GitHub/plan/comments/phase-5-1-plan-comment.md)을 사용한다.

```bash
gh issue comment 7 \
  --body-file Docs/07_GitHub/plan/comments/phase-5-1-plan-comment.md
```

생성 후 comment permalink를 확인한다.

### 5. 게시 후 정본 동기화

Demo Issue와 Progress comment의 실제 URL을 확인한 뒤 영향 정본만 갱신한다.

- [Work Unit GitHub Index](../work-unit-github-index.md)
- [Chapter14 Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
- [Chapter14 PR body 후보](../../07_GitHub/prs/part4_chapter14.md)
- [WU-Part4](../work-units/WU-Part4.md)

동기화 후 validator를 실행하고 별도 commit을 만든 뒤 승인 후 다시 push한다.

### 6. PR 생성

title source는 [Chapter14 PR body 후보](../../07_GitHub/prs/part4_chapter14.md)의 첫 H1이다.

```text
Part4 Chapter14 Compute Shader evidence 문서화와 capture 승격
```

remote body는 첫 H1과 바로 뒤 빈 줄을 제거한 `## 요약`부터 사용한다.

```bash
gh pr create \
  --base main \
  --head docs/part4-chapter14-20-workflow \
  --title "Part4 Chapter14 Compute Shader evidence 문서화와 capture 승격" \
  --body-file <h1-removed-pr-body>
```

PR 생성 후 PR URL, head ref, base ref와 PR head commit을 확인한다.

## Ready 직전 감사

- local HEAD, tracking ref, remote branch head와 PR head가 일치하는지 확인한다.
- worktree가 clean인지 확인한다. LF/CRLF 표시만 남는 경우 content diff 없음으로 별도 보고한다.
- Demo Issue, Progress 누적 댓글, Phase 5-1 완료 댓글과 PR body가 tracked 후보 변환본과 일치하는지 확인한다.
- GitHub UI에서 Demo Issue 대표 visual, Progress comment와 PR body 링크가 렌더링되는지 표본 확인한다.
- `Docs Validation` run이 생성되면 성공 여부를 확인한다.
- 위 항목을 통과한 뒤 `gh pr ready` 실행 여부를 별도 승인받는다.

## 실행 결과

- Branch push: `origin/docs/part4-chapter14-20-workflow` 생성, 게시 URL 동기화 시점의 local HEAD·tracking ref·remote branch head 일치 확인
- Demo Issue: [Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29) 생성
- Progress 누적 진행 댓글: [댓글 5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690) 수정
- Phase 5-1 완료 댓글: [댓글 5196232081](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5196232081) 생성
- Draft PR: [PR #30](https://github.com/Razria93/Graphics_Study_Archive/pull/30) 생성, head ref `docs/part4-chapter14-20-workflow`, base ref `main`, PR 생성 시점 head 확인
- Ready for Review 전환은 후속 승인 범위로 남긴다.

## 검증 명령

```bash
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-index-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-table-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-render-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1
git diff --cached --check
```
