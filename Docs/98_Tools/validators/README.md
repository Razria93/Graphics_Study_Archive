# Validators

이 폴더는 반복 실행 가능한 tracked validator script를 둔다. 정책 정본은 `Docs/07_Policies`에 두고, 이 폴더에는 실행 파일과 사용법만 둔다.

## Script 목록

| Script | 목적 | 입력 |
| --- | --- | --- |
| `validate-github-body.ps1` | GitHub Issue/PR/comment 게시 전 Markdown body 검사 | `local/github/public` |

## 사용법

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1
```

기본 입력 위치는 `local/github/public`이다. 다른 위치를 검사할 때는 `-PublicRoot`를 지정한다.

```powershell
powershell -ExecutionPolicy Bypass -File Docs/98_Tools/validators/validate-github-body.ps1 -PublicRoot local/github/public
```

## 검사 기준

- GitHub 게시 전 body에 draft/local-only 경로가 남아 있지 않은지 확인한다.
- 필수 섹션이 빠지지 않았는지 확인한다.
- GitHub body가 한국어 섹션 기준을 따르는지 확인한다.
- screenshot Markdown이 `Docs/_assets/captures`를 가리키는지 확인한다.
- template에 특정 Issue 번호가 하드코딩되어 있지 않은지 확인한다.

## 주의

- validator 통과는 GitHub 게시 승인이 아니다.
- `git push`, `gh issue create`, `gh pr create`, Ready for Review 전환은 사용자 승인 후 진행한다.
- local draft 원문은 이 폴더에 두지 않는다.
