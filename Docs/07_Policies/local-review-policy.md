# Local Review Policy

이 문서는 local-only 검토 메모와 raw/reference 문서를 다루는 기준을 정의한다.

## 책임

`local/`은 Git에 올리지 않는 작업장이다. raw 문서 원문, source comment 분리 기록, 개인 검토 메모, GitHub draft를 먼저 이곳에 둔다.

## 권장 구조

```text
local/
  mini-plans/
  source-comments/
  study-review/
  github/
    draft/
    public/
    snapshots/
```

## 운영 기준

- raw/reference 문서는 필요한 부분만 읽는다.
- 강의 원문 구조나 표현을 그대로 tracked Docs로 옮기지 않는다.
- source comment 원문은 필요하면 local에 보관한다.
- tracked Docs에는 직접 이해한 설명과 검토된 요약만 반영한다.
- 민감 판단, redaction log, 개인 메모는 local-only로 유지한다.

## 승격 기준

local 문서는 다음 조건을 만족할 때만 tracked Docs로 승격한다.

- 반복 참조 가치가 있다.
- 예제 설명, Topic, Verification, Demo, Publication 정본 중 하나에 들어갈 책임이 명확하다.
- private-only 정보와 raw 원문 표현이 제거되어 있다.
- 직접 확인한 상태와 미확인 상태가 구분되어 있다.