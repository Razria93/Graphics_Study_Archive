# Local Review Policy

이 문서는 local-only 작업장과 raw/reference 검토 메모를 다루는 기준을 정의한다.

## 책임

`local/`은 Git에 올리지 않는 작업장이다. raw 문서 원문, source comment 분리 기록, 개인 검토 메모, GitHub draft, 게시 전 public body 후보를 먼저 이곳에 둔다.

## Git 기준

- `.gitignore`는 `local/` 전체를 무시한다.
- `local/` 내부 파일은 commit 대상으로 보지 않는다.
- local 내용을 tracked Docs로 옮길 때는 원문 복사가 아니라 재작성과 요약을 기준으로 한다.
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
    public/
      issues/
      prs/
      comments/
    snapshots/
  tools/
```

## 기존 local 구조 처리

현재 `local/Part*_Chapter*`, `local/pr`, `local/prompts`는 이전 import/documentation 흐름에서 생긴 legacy local cache로 본다.

처리 기준:

- 기존 파일을 즉시 이동하지 않는다.
- 새 Work Unit에서 다시 읽을 때 필요한 내용만 `local/study-review` 또는 tracked Docs 정본으로 재작성한다.
- 기존 `local/pr` 초안은 새 GitHub draft 구조로 복사하지 않고, 필요할 때 `local/github/draft` 형식으로 다시 작성한다.
- 기존 `local/prompts`는 새 세션 기준을 만들 때만 참고하고, 정본은 tracked policy 또는 root/AGENTS 문서에 둔다.
- legacy local cache는 정리 대상이지만, 삭제는 별도 요청이 있을 때만 진행한다.

## 단계별 사용

| 단계 | local 위치 | 목적 |
| --- | --- | --- |
| 작업 시작 | `local/mini-plans/` | Work Unit 범위와 확인 대상 정리 |
| raw/source 검토 | `local/source-comments/` | source comment와 raw 원문 위치 보존 |
| 이해 정리 | `local/study-review/` | tracked Docs로 옮기기 전 재작성 메모 |
| 공개 판단 | `local/publication/` | 후보, 제외 사유, redaction 근거 검토 |
| GitHub 초안 | `local/github/draft/` | Issue/PR/comment 게시 전 초안 |
| GitHub 게시 후보 | `local/github/public/` | 게시 직전 문체와 섹션 검수 대상 |
| 게시 후 보존 | `local/github/snapshots/` | 게시 후 사본 또는 리뷰 대응 기록 |

## 승격 기준

local 문서는 다음 조건을 만족할 때만 tracked Docs로 승격한다.

- 반복 참조 가치가 있다.
- `Docs/01_Examples`부터 `Docs/06_Publication` 중 어느 정본에 들어갈지 명확하다.
- private-only 정보와 raw 원문 표현이 제거되어 있다.
- 직접 확인한 상태와 미확인 상태가 구분되어 있다.
- 강의 원문 구조나 표현을 그대로 옮기지 않는다.

## 금지사항

- `local/` 파일을 commit하지 않는다.
- raw 원문, 강의 표현, source comment 원문을 tracked Docs에 그대로 복사하지 않는다.
- GitHub draft 원문을 `Docs/05_WorkLogs`에 그대로 붙이지 않는다.
- public 후보 판단 근거 중 민감한 내용은 tracked Docs에 두지 않는다.