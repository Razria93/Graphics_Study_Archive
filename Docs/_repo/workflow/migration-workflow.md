# Migration Workflow

이 문서는 Part1부터 Part4까지 빠르게 정리하기 위한 반복 작업 규격입니다. 현재 목표는 완성 문서를 먼저 만드는 것이 아니라, 코드와 문서를 분리하고 실행 가능한 archive 상태를 확보하는 것입니다.

## 전체 우선순위

1. 코드와 문서 분리
2. 코드 정상 작동 확인
3. raw/original 대비 차이 검토
4. 코드 품질 검토 및 필요한 리팩터링
5. 리팩터링 후 동작 확인
6. 사용자가 영상/사진 촬영 및 업로드

5번까지가 archive 정리의 1차 목표입니다. 6번은 사용자가 직접 수행하고, 이후 촬영 결과와 local-only 문서 재료를 바탕으로 최종 문서를 정리합니다.

## 예제별 상태 단계

각 예제는 아래 상태를 순서대로 통과합니다.

| 단계 | 의미 | 완료 기준 |
| --- | --- | --- |
| `1_code_split` | 코드와 메모/문서 분리 | 소스의 장문 메모를 제거하거나 local-only 문서로 분리 |
| `2_build_check` | archive 코드 실행 확인 | Debug x64 기준 build/run 결과 기록 |
| `3_diff_review` | raw/original 대비 차이 확인 | 사용자가 작성한 핵심 구현부와 변경 의도 기록 |
| `4_refactor_check` | 품질 검토 | 리팩터링 필요 여부와 범위 기록 |
| `5_ready_for_capture` | 촬영 준비 | 사용자가 실행해 영상/사진을 찍을 수 있는 상태 |

## Tracked 문서

git에 포함하는 문서는 최소 상태와 공개 가능한 설명을 중심으로 작성합니다.

```text
Docs/_repo/tracking/migration-board.md
Docs/_repo/templates/example-readme.md
Docs/_repo/templates/example-status.md
Docs/PartX_ChapterYY/ExampleName/README.md
Docs/PartX_ChapterYY/ExampleName/status.md
```

tracked 문서에는 다음을 둡니다.

- 예제 목적
- 핵심 키워드
- 관련 이론/원리
- 핵심 코드 흐름과 짧은 코드 조각
- build/run 상태
- capture 준비 상태
- 공개 가능성 상태

강의 원문, 장문 메모 원문, raw 문서 전문, private-only 판단 근거는 tracked 문서에 넣지 않습니다.

## Local-only 문서

git에 올리지 않는 작업 재료는 `local/` 아래에 둡니다.

```text
local/PartX_ChapterYY/ExampleName/
  source-comments.md
  raw-md-notes.md
  memo-review.md
  final-doc-plan.md
```

local-only 문서에는 다음을 둡니다.

- 소스코드에 있던 사용자 메모 원문
- raw repo의 관련 `.md` 문서 내용 또는 위치
- 이미지가 누락된 경우 이미지 파일명과 위치
- 메모의 의도, 오류 가능성, 보완점 검토
- 최종 문서 구성 제안

`local/`은 `.gitignore`에 포함되어 있으므로 private 작업 재료 보관용으로 사용합니다.

## 코드 분리 원칙

- 실행에 필요한 소스코드는 archive에 포함할 수 있습니다.
- 강의 기반 파일을 통째로 public 후보로 보지는 않습니다.
- 기존 장문 학습 주석은 제거하고, 필요한 내용은 local-only 문서로 분리합니다.
- 코드에 남길 주석은 섹션 구분, 구현 의도, lifetime/path 주의로 제한합니다.
- 리팩터링은 build/run 확인 단위와 분리해서 진행합니다.

## 문서화 원칙

- 1차 정리는 tracked 문서를 얇게 유지합니다.
- 핵심 코드 흐름은 짧은 코드 조각으로 설명합니다.
- 사용자가 작성한 원문 메모는 local-only에 보존합니다.
- 최종 문서는 영상 촬영 후 사용자가 raw 문맥과 기억을 확인하면서 보강합니다.

## 반복 작업 순서

1. raw/source 구조 확인
2. archive에 필요한 코드 파일만 선별
3. 소스 주석과 `.md` 메모 출처 확인
4. 사용자 메모 원문을 local-only 문서로 분리
5. 소스의 장문 주석 제거 및 필요한 짧은 주석 재작성
6. tracked README/status 작성 또는 갱신
7. build/run 확인
8. raw/original 대비 변경부 확인
9. 리팩터링 필요 여부 판단
10. capture ready 여부 기록

## Commit 기준

commit은 사용자가 명시적으로 요청할 때만 수행합니다. 단, 아래 단위가 끝나면 commit 타이밍으로 안내합니다.

- 예제 1개의 code split + tracked docs/status 갱신
- 예제 1개의 build/run 확인 기록
- Part 하나의 migration-board 상태 갱신
- 공통 workflow/template 변경
