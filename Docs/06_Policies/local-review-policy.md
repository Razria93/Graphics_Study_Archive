# Local Review Policy

이 문서는 local-only 자료 영역과 raw/reference 검토 메모를 다루는 기준을 정의한다.

## 책임

`local/`은 Git에 올리지 않는 자료 영역이다. raw 문서 원문, source comment 분리 기록, 개인 검토 메모, GitHub draft를 먼저 이곳에 둔다. GitHub 게시 후보 정본은 `Docs/07_GitHub`에 둔다.

## Git 기준

- `.gitignore`는 `local/` 전체를 무시한다.
- `local/` 내부 파일은 commit 대상으로 보지 않는다.
- local 내용을 tracked Docs로 옮길 때는 원문 복사가 아니라 재작성과 요약을 기준으로 한다.
- local 상세 조사에서 재사용 가능한 결론만 `Docs/04_WorkLogs/reviews/`에 요약한다.
- tracked Docs에서 `local/` 파일로 직접 링크하지 않는다. local 문서에서 tracked 문서로 연결하는 것은 허용한다.
- 민감 판단, redaction log, 개인 메모, 계정/환경 정보는 tracked Docs로 승격하지 않는다.

## 권장 구조

새 작업은 다음 구조를 기준으로 둔다.

```text
local/
  mini-plans/
  source-comments/
  study-review/
  publication/
  github/
    draft/
      issues/
      prs/
      comments/
    snapshots/
  tools/
```

## 기존 local 구조 처리

현재 `local/Part*_Chapter*`, `local/pr`는 이전 import/documentation 흐름에서 생긴 legacy local 자료로 본다.

현재 legacy local 자료의 파일 수와 승격 후보는 `Docs/99_Legacy/local-inventory.md`를 기준으로 확인한다.

처리 기준:

- 기존 파일을 즉시 이동하지 않는다.
- 새 Work Unit에서 다시 읽을 때 필요한 내용만 `local/study-review` 또는 정본 문서로 재작성한다.
- 기존 `local/pr` 초안은 새 GitHub draft 구조로 복사하지 않고, 필요할 때 `local/github/draft` 형식으로 다시 작성한다.
- 삭제한 `local/prompts`와 `local/tools` 원본은 `Docs/99_Legacy/local-inventory.md`의 폐기 기록으로만 확인한다.
- legacy local 자료는 정리 대상이지만, 삭제는 별도 요청이 있을 때만 진행한다.

## 단계별 사용

| 단계 | local 위치 | 목적 |
| --- | --- | --- |
| 작업 시작 | `local/mini-plans/` | Work Unit 범위와 확인 대상 정리 |
| raw/source 검토 | `local/source-comments/` | source comment와 raw 원문 위치 보존 |
| 이해 정리 | `local/study-review/` | current/raw/origin 비교, source comment inventory, stale 판단 상세 보관 |
| tracked 요약 후보 | `local/study-review/` -> `Docs/04_WorkLogs/reviews/` | 반복 조사 방지를 위한 결론만 요약 |
| 공개 판단 | `local/publication/` | 후보, 제외 사유, redaction 근거 검토 |
| GitHub 초안 | `local/github/draft/` | Issue/PR/comment 게시 전 초안 |
| GitHub 게시 후보 | `Docs/07_GitHub/` | 게시 직전 최종 후보와 validator 검수 대상 |
| 게시 후 보존 | `local/github/snapshots/` | 실제 게시본 사본과 리뷰 대응 기록 |

## tracked review summary 기준

`Docs/04_WorkLogs/reviews/`로 옮길 수 있는 내용은 아래로 제한한다.

- 검토한 예제와 범위
- README, Topic, Verification, Demo로 승격한 항목
- 승격하지 않은 항목의 분류 결과
- 반복 적용할 판단 기준
- 후속 known issue

아래 내용은 `local/study-review/`에만 둔다.

- raw/reference 또는 origin 비교 원문
- source comment inventory 원문
- 기존 Docs stale 판단의 상세 근거
- 민감 판단, redaction 근거, 개인 메모

## 승격 기준

local 문서는 다음 조건을 만족할 때만 tracked Docs로 승격한다.

- 반복 참조 가치가 있다.
- 코드 폴더 README 또는 `Docs/01_Topics`부터 `Docs/05_Publication` 중 어느 정본에 들어갈지 명확하다.
- private-only 정보와 raw 원문 표현이 제거되어 있다.
- 직접 확인한 상태와 미확인 상태가 구분되어 있다.
- 강의 원문 구조나 표현을 그대로 옮기지 않는다.

## 금지사항

- `local/` 파일을 commit하지 않는다.
- raw 원문, 강의 표현, source comment 원문을 tracked Docs에 그대로 복사하지 않는다.
- GitHub draft 원문을 `Docs/04_WorkLogs`에 그대로 붙이지 않는다.
- public 후보 판단 근거 중 민감한 내용은 tracked Docs에 두지 않는다.
- tracked Docs에서 `local/` 파일로 직접 링크하지 않는다.
