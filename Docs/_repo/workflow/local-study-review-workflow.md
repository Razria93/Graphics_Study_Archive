# Local Study Review Workflow

이 문서는 source에서 분리한 학습 메모와 raw/reference 문서를 나중에 다시 읽을 수 있는 형태로 정리하는 기준입니다.

`local/` 문서는 git에 올리지 않는 작업용 자료입니다. 목적은 공개 문서를 바로 만드는 것이 아니라, 나중에 각 예제의 작업 의도, 헷갈렸던 부분, 구현 핵심, 보완할 이론을 빠르게 복원하는 것입니다.

## 기본 원칙

- raw source comment를 그대로 덤프하는 것으로 끝내지 않습니다.
- raw markdown 문서, source 내부 메모, archive 코드, 실행 확인 상태를 함께 봅니다.
- 강의 원문 구조나 표현을 그대로 옮기지 않고, 사용자가 이해한 내용과 archive 작업 판단으로 재정리합니다.
- 깨진 인코딩, 절대 경로, 개인 작업 메모는 tracked 문서로 옮기지 않습니다.
- public 후보가 될 수 있는 내용은 다시 쓸 수 있는 개념/구현 설명으로 분리하고, asset/license는 검토 필요로 둡니다.

## Local 문서 구성

각 예제의 local 작업 폴더는 다음 구성을 권장합니다.

```text
local/PartX_ChapterYY/ExampleName/
  source-comments.md
  study-review.local.md
```

`source-comments.md`는 원문 위치와 제거된 source comment를 보관하는 자료입니다. 원문 보존 목적이므로 다듬지 않아도 되지만, 이것만으로 작업을 끝내면 안 됩니다.

`study-review.local.md`는 나중에 README나 issue 문서를 작성할 때 보는 핵심 작업 문서입니다. raw 문서와 archive 코드를 다시 읽고, 무엇을 이해하려고 했는지와 무엇을 구현했는지를 정리합니다.

## Study Review 필수 항목

- 확인한 원본: raw code, archive code, related raw docs, local source comments
- 챕터 목적 추정
- 핵심 키워드
- 파일 내부 메모 요약
- 관련 raw 문서에서 가져올 내용
- 구현 핵심 코드 위치
- original/archive 차이
- 보완이 필요한 이론
- 최종 README에 반영할 내용
- 공개/비공개 주의

## 작성 순서

1. `Docs_Graphics/_00_StartHere/01_ChapterDocMapping.md`에서 관련 문서를 찾습니다.
2. raw 예제 폴더와 archive 예제 폴더의 파일 목록을 비교합니다.
3. source 내부 주석은 원문 위치와 함께 `source-comments.md`에 보관합니다.
4. raw markdown 문서와 source comment를 읽고 `study-review.local.md`에 재정리합니다.
5. archive README에는 `study-review.local.md`에서 검토된 내용 중 공개/공유 가능한 요약만 반영합니다.
6. build/run 상태는 `status.md`와 migration board에 기록하고, local 문서에는 판단 근거만 남깁니다.

## 판단 기준

`source-comments.md`에 남길 수 있는 것:

- 원문 위치 추적이 필요한 source comment
- 사용자가 작성한 질문, 시행착오, TODO, 비교 메모
- 나중에 다시 읽을 가능성이 있는 raw 설명 주석
- 인코딩이 깨졌지만 raw에서 복원할 필요가 있는 위치

`study-review.local.md`로 승격해야 하는 것:

- 이 예제가 무엇을 보여주는지에 대한 목적
- 구현을 이해하는 데 필요한 핵심 코드 흐름
- raw 문서와 source comment를 연결한 해석
- 사용자가 당시 헷갈린 것으로 보이는 부분
- 최종 문서에 들어갈 후보 문장과 코드 조각
- public 공개 전 제외하거나 다시 검토해야 할 항목

tracked README로 옮길 수 있는 것:

- 일반적인 graphics 개념 설명
- 실행 결과를 이해하는 데 필요한 구현 요약
- 전체 파일이 아닌 짧은 핵심 코드 조각
- build/run/capture 상태
- asset/license 검토 필요 상태

tracked README로 옮기면 안 되는 것:

- raw absolute path
- 강의 원문 문장이나 고유 진행 구조
- 긴 source dump
- 개인 메모, 계정/환경 정보
- 출처 불명 asset을 공개 가능하다고 단정하는 문장
