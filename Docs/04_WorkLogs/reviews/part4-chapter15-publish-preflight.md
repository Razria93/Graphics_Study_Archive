# Part4 Chapter15 원격 게시 승인안

이 문서는 Chapter15 Demo Issue, Progress 누적 댓글과 Phase 5-2 완료 댓글 remote 게시 전 필요한 push와 GitHub 게시 범위를 요약한 preflight snapshot이다. 실제 remote 변경은 사용자 승인 후에만 수행한다.

## 현재 로컬 상태

- 작업 branch는 `docs/part4-chapter14-20-workflow`다.
- 현재 branch는 `origin/docs/part4-chapter14-20-workflow`를 upstream으로 추적한다.
- Local HEAD는 `a73f54abe4a7c2e5e2f18294348e7d74292d2bb0`이다.
- Upstream HEAD는 `500d00691963b0a34fedc8e0a510670d78900333`이다.
- 현재 branch는 upstream 대비 6 commits ahead 상태다.
- Worktree는 clean이다.

## 게시 전 변경 범위

`origin/docs/part4-chapter14-20-workflow..HEAD` 범위는 Chapter15 smoke 확인, selected capture 승격, Ex1502 rendered visual 보정, Chapter15 Demo Issue body, Phase 5-2 progress comment와 capture tool argument 지원을 포함한다.

| Commit | 요약 |
| --- | --- |
| `4107c3c` | Part4 command argument capture 지원 |
| `53912bf` | Chapter15 smoke 결과와 evidence 후보 감사 기록 |
| `0c9238a` | Chapter15 selected capture 승격 |
| `b0c2add` | Chapter15 Demo 게시 후보 작성 |
| `b8ee9ce` | Chapter15 SpriteFireEffect Demo 보정 |
| `a73f54a` | Chapter15 SpriteFireEffect visual 승격 |

## 게시 후보

| 대상 | 후보 파일 | 상태 | 비고 |
| --- | --- | --- | --- |
| Demo Issue | [Chapter15 Demo Issue body](../../07_GitHub/issues/demo/demo_part4_chapter15.md) | ready | Ex1501, Ex1502, 10초 지연 Ex1503 visual 3개 포함 |
| Progress 누적 댓글 | [Progress body](../../07_GitHub/plan/plan-progress.md) | ready | Issue #7의 누적 진행 댓글 수정 후보 |
| Phase 5-2 완료 댓글 | [Phase 5-2 comment](../../07_GitHub/plan/comments/phase-5-2-plan-comment.md) | comment-ready | Issue #7 신규 댓글 후보 |

## Evidence 기준

| Example | Capture | SHA-256 | 비고 |
| --- | --- | --- | --- |
| `Ex1501_ParticleSystem` | [part4_chapter15_01_particle_system.png](../../_assets/captures/part4_chapter15_01_particle_system.png) | `454F79FD98C4AD1EE56EC7AA093D4335EFCBD104D64894BC21042868163DBF2A` | particle stream baseline |
| `Ex1502_SpriteFireEffect` | [part4_chapter15_02_sprite_fire_effect.png](../../_assets/captures/part4_chapter15_02_sprite_fire_effect.png) | `1609752870BA6BC77910B97A77BAFC058764F4CEB772284077BA3897431A5B19` | 원본 `flare0.dds`를 직접 링크하지 않고 rendered evidence로만 사용 |
| `Ex1503_SphWater` | [part4_chapter15_03_sph_water.png](../../_assets/captures/part4_chapter15_03_sph_water.png) | `5B627B289AC8FCC9A472133ECCF66B6FA7F6667DD4AF182C43D22A5406F6596A` | 10초 지연 selected capture |

## 승인 대상

### 1. Branch push

목적은 branch URL 기반 image와 문서 링크가 GitHub remote에서 렌더링되는지 확인할 수 있게 만드는 것이다.

```bash
git push origin docs/part4-chapter14-20-workflow
```

push 후에는 local HEAD, tracking ref와 remote branch head가 같은 commit인지 확인한다.

### 2. Demo Issue 생성

title source는 [Chapter15 Demo Issue 후보](../../07_GitHub/issues/demo/demo_part4_chapter15.md)의 첫 H1이다.

```text
Part4 Chapter15 Particle Simulation Demo
```

remote body는 첫 H1과 바로 뒤 빈 줄을 제거한 `## 요약`부터 사용한다.

```bash
gh issue create \
  --title "Part4 Chapter15 Particle Simulation Demo" \
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

### 4. Phase 5-2 완료 댓글 생성

본문은 [Phase 5-2 완료 기록](../../07_GitHub/plan/comments/phase-5-2-plan-comment.md)을 사용한다.

```bash
gh issue comment 7 \
  --body-file Docs/07_GitHub/plan/comments/phase-5-2-plan-comment.md
```

생성 후 comment permalink를 확인한다.

### 5. 게시 후 정본 동기화

Demo Issue와 Progress comment의 실제 URL을 확인한 뒤 영향 정본만 갱신한다.

- [Work Unit GitHub Index](../work-unit-github-index.md)
- [Part4 Chapter14-20 Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
- [WU-Part4](../work-units/WU-Part4.md)
- [Progress body](../../07_GitHub/plan/plan-progress.md)

동기화 후 validator를 실행하고 별도 commit을 만든 뒤 승인 후 다시 push한다.

## Remote 게시 전 감사 항목

- local HEAD, tracking ref와 remote branch head가 게시 전후로 의도한 commit인지 확인한다.
- worktree가 clean인지 확인한다.
- Demo Issue body의 image 3개가 branch ref에서 로드되는지 확인한다.
- Progress 누적 댓글과 Phase 5-2 완료 댓글이 tracked 후보와 일치하는지 확인한다.
- `Docs Validation` run이 생성되면 성공 여부를 확인한다.

## 검증 명령

```bash
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-table-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-render-quality.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-markdown-wrap-quality.ps1
git diff --check
```

## 승인안

Chapter15 remote 게시 전 로컬 문서와 capture evidence는 게시 후보로 정렬되어 있다. 사용자가 승인하면 다음 목표모드에서 branch push, Chapter15 Demo Issue 생성, Progress 누적 댓글 수정과 Phase 5-2 완료 댓글 생성을 순서대로 진행할 수 있다.

## 실행 결과

- Branch push: `origin/docs/part4-chapter14-20-workflow`를 `388d2b0c950d3d978179431b1006d8406ef391f4`까지 갱신했고 local HEAD, tracking ref와 remote branch head 일치를 확인했다.
- Demo Issue: [Issue #31](https://github.com/Razria93/Graphics_Study_Archive/issues/31) 생성 후 UTF-8 명시 읽기 방식으로 body를 교정했다.
- Progress 누적 진행 댓글: [댓글 5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)을 Phase 5-2 포함 body로 수정했다.
- Phase 5-2 완료 댓글: [댓글 5200004532](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5200004532)을 생성했다.
- 원격 body 검사: Issue #31은 `## 요약`으로 시작하고 Chapter15 한글 본문을 포함한다. Progress 누적 댓글과 Phase 5-2 완료 댓글도 대상 문구 포함을 확인했다.