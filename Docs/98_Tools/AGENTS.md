# Tools Guidelines

## 적용 범위

이 규칙은 `Docs/98_Tools/` 아래 문서에 적용한다.

## 책임

- template, validation 기준, troubleshooting 문서만 둔다.
- 반복 실행 가능한 validator script는 `validators/`에 둔다.
- 문서 감사 정책은 `Docs/06_Policies/document-system-audit-policy.md`에 두고,
  이 폴더에는 실행 가이드와 보고 template만 둔다.
- 정책 원문은 `Docs/06_Policies`로 링크한다.
- 산출물 정본은 `Docs/00_Index`부터 `Docs/05_Publication`에 둔다.
- GitHub draft, raw/reference 원문, 개인 메모는 이 폴더에 두지 않는다.
- local-only template은 정본 문서로 그대로 복사하지 않는다.

## Template 기준

- tracked 정본 문서용 template은 해당 산출물 폴더 책임만 담는다.
- local-only review template은 파일명에 `local-`을 붙인다.
- 상태를 여러 산출물에서 다시 모으는 template은 만들지 않는다.
- 감사 보고 template은 특정 시점 snapshot 형식만 제공하고 최신 정본을
  대체하지 않는다.
- 상세 정책은 각 정책 문서로 연결한다.

## Validator 기준

- tracked validator는 remote 상태를 바꾸지 않는다.
- local draft를 자동 수정하지 않고 실패와 경고만 보고한다.
- GitHub 게시 전 body 검수는 `validators/validate-github-body.ps1`를 기준으로 한다.

## 문체

- 평서형 현재형을 사용한다.
- 존댓말, 대화체, 감상문체를 사용하지 않는다.
- technical keywords, folder names, command names는 영어를 유지한다.
