# Validators Guidelines

## 적용 범위

이 규칙은 `Docs/98_Tools/validators/` 아래 script와 사용법 문서에 적용한다.

## 책임

- 반복 실행 가능한 검수 script만 둔다.
- 정책 원문은 `Docs/07_Policies`로 연결한다.
- validator는 remote 상태를 바꾸지 않는다.
- validator는 local draft를 수정하지 않고 실패/경고만 보고한다.
- project-specific 경로는 현재 Docs 구조에 맞춘다.

## Script 기준

- 기본 입력은 `local/github/public` 또는 명시된 인자로 받는다.
- 출력은 실패와 경고를 구분한다.
- 실패 조건은 문서화된 GitHub 게시 기준과 연결한다.
- local-only 경로, stale `_repo` 경로, legacy PartDocs 경로를 public body에 허용하지 않는다.

## 문체

- 문서는 평서형 현재형을 사용한다.
- script 출력은 짧은 영어 메시지를 사용할 수 있다.
