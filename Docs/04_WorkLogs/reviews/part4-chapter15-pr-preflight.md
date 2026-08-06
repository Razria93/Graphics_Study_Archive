# Part4 Chapter15 PR 생성 전 감사

## 목적

Chapter15 PR 생성 전 로컬 PR body 후보, remote 게시물, branch 상태와 validator 결과를 감사하고 Draft PR 생성 결과를 기록한다.

## 감사 기준선

| 항목 | 확인 결과 |
| --- | --- |
| Branch | `docs/part4-chapter14-20-workflow` |
| Local PR 후보 기준 | `a49af4e31bfe02ce06d05dd1ac338d29819a014c`에서 PR body 후보 작성과 local validation 통과 |
| Upstream HEAD | `813d57c89aba283ab40b45e2ed94dfce30866c9c` |
| Remote branch head | `813d57c89aba283ab40b45e2ed94dfce30866c9c` |
| Base | `main` |
| Open PR on branch | 없음 |
| Latest remote Docs Validation | success, run `31068322068`, head `813d57c89aba283ab40b45e2ed94dfce30866c9c` |
| Local validation | PR 후보 작성 후 GitHub body, GitHub quality, Demo index, Markdown table/render/wrap, `git diff --check` 통과 |
| Worktree | 감사 문서 커밋 후 재확인 대상 |

## PR 후보

| 항목 | 값 |
| --- | --- |
| 후보 파일 | [part4_chapter15.md](../../07_GitHub/prs/part4_chapter15.md) |
| PR title source | `Part4 Chapter15 Particle Simulation evidence 문서화와 capture 승격` |
| Remote body source | 첫 H1과 바로 뒤 빈 줄을 제거한 `## 요약`부터 사용 |
| Head branch | `docs/part4-chapter14-20-workflow` |
| Base branch | `main` |
| 권장 생성 상태 | Draft PR |
| Push 필요 여부 | PR 생성 직전 최신 local HEAD 확인 후 push 필요 |

## 원격 게시 연결

| Remote 객체 | 상태 |
| --- | --- |
| Demo Issue #31 | 생성 완료, body는 `## 요약` 시작·한글 본문·commit-pinned code link·image 3개 포함 확인 |
| Progress 누적 댓글 5091068690 | Phase 5-2와 Demo Issue #31 링크 포함 확인 |
| Phase 5-2 완료 댓글 5200004532 | 생성 완료, `Phase 5-2 완료 기록` 문구 포함 확인 |
| Chapter15 capture assets | remote branch ref에서 PNG 3개 존재 확인 |

## PR 생성 승인 대상

PR 생성 전 먼저 최신 local HEAD를 확인하고 remote branch에 push한다.

```bash
git rev-parse HEAD
git rev-parse @{u}
git status --short --branch
```

```bash
git push origin docs/part4-chapter14-20-workflow
```

push 후 local HEAD, upstream HEAD, remote branch head와 새 Docs Validation run을 확인한다.

```bash
gh pr create \
  --base main \
  --head docs/part4-chapter14-20-workflow \
  --draft \
  --title "Part4 Chapter15 Particle Simulation evidence 문서화와 capture 승격" \
  --body-file <h1-removed-pr-body>
```

PR 생성 후에는 PR URL, PR number, head ref, base ref와 PR head commit이 push 직전 확인한 local HEAD인지 확인한다.

## 생성 전 감사 항목

- PR body 후보가 Chapter15 범위, 대표 예제, 검증, 대표 visual, 한계와 관련 Issue를 포함하는지 확인한다.
- PR body의 source code link는 commit-pinned line range를 사용한다.
- 대표 visual은 1개만 사용하고 상세 visual은 Demo Issue #31로 위임한다.
- Ex1502는 원본 `flare0.dds`를 직접 링크하지 않고 rendered evidence로만 다룬다.
- 기존 open PR이 같은 head branch에 없는지 확인한다.
- PR 생성 전 PR 후보 작성 commit을 push하고 local HEAD, upstream HEAD와 remote branch head가 일치하는지 확인한다.

## 검증 명령

```bash
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-demo-index-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-table-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-render-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1
git diff --check
```

## 판정

Chapter15 PR body 후보와 remote 게시 연결은 PR 생성 전 감사 대상으로 정렬되어 있다. 현재 PR 후보 작성 commit은 local ahead 1 상태이므로, 사용자 승인 후 branch push와 Draft PR 생성을 순서대로 진행할 수 있다.

## 실행 결과

- Branch push: `origin/docs/part4-chapter14-20-workflow`를 `ce2645e5449a8d685926854e839f61126cbc8511`까지 갱신했고 local HEAD, tracking ref와 remote branch head 일치를 확인했다.
- Draft PR: [PR #32](https://github.com/Razria93/Graphics_Study_Archive/pull/32) 생성, base `main`, head `docs/part4-chapter14-20-workflow`, 생성 시점 head `ce2645e5449a8d685926854e839f61126cbc8511` 확인.
- PR body 검사: remote body는 `## 요약`으로 시작하고 한글 본문, 대표 visual 1개와 Chapter15 설명을 포함한다.
- 후속 동기화: PR #32 URL을 Work Unit, Progress와 preflight 정본에 반영한다.