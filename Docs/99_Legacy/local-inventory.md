# Local Inventory

이 문서는 Git에 추적하지 않는 `local/` 작업장의 현재 구성을 기록한다. 실제 파일을 이동하거나 승격하지 않고, 다음 문서화 단계에서 어떤 자료를 참고할지 판단하는 inventory로 사용한다.

## 기준

- `local/` 파일은 commit 대상으로 보지 않는다.
- tracked Docs로 옮길 때는 원문 복사가 아니라 재작성과 요약을 기준으로 한다.
- private-only 정보, raw 원문 표현, 강의 표현, 개인 환경 정보는 승격하지 않는다.
- 삭제 또는 이동은 별도 사용자 승인 후 진행한다.

## 전체 규모

| 항목 | 값 |
| --- | --- |
| 전체 파일 수 | 99 |
| Markdown 파일 | 98 |
| PowerShell 파일 | 1 |
| 전체 크기 | 약 553 KB |
| 최대 파일 크기 | 약 49 KB |

## 상위 폴더별 현황

| 폴더 | 파일 수 | 성격 | 처리 판단 |
| --- | ---: | --- | --- |
| `local/Part1_Chapter01-02` | 8 | Part1 초기 예제 검토 메모 | 필요 시 Example/Topic 작성 참고 |
| `local/Part1_Chapter03` | 24 | Ray tracing 단계별 검토 메모 | 필요 시 `Portfolio_RayTracer`와 Topic 작성 참고 |
| `local/Part2_Chapter04` | 11 | Software rasterization source comment cache | raw/source 원문 성격이 강해 직접 승격 금지 |
| `local/Part2_Chapter05-08` | 51 | Pipeline, modeling, ShaderToys 검토 메모 | `study-review.local.md`만 우선 참고 후보 |
| `local/Part4_Chapter14-20` | 1 | Assimp/SkeletalAnimation 재현 메모 | tracked 문서와 대조 후 보완 후보 |
| `local/pr` | 1 | 과거 PR draft | 새 GitHub draft 구조로 재작성할 때만 참고 |
| `local/prompts` | 2 | 과거 세션 prompt | 현행 `AGENTS.md`와 정책 문서로 대체 |
| `local/tools` | 1 | GitHub body validator | tracked tool 승격 후보 |

## 파일 패턴별 현황

| 파일 패턴 | 수 | 성격 | 처리 판단 |
| --- | ---: | --- | --- |
| `source-comments.md` | 53 | source comment와 raw 검토 흔적 | local-only 유지, 직접 승격 금지 |
| `study-review.local.md` | 19 | 예제 이해 재작성 메모 | Example/Topic 작성 시 우선 참고 후보 |
| `final-doc-plan.md` | 10 | import 당시 문서화 계획 | WorkLog/Example 작성 시 참고 가능 |
| `memo-review.md` | 10 | 메모 검토 결과 | 필요한 내용만 재작성 후보 |
| `raw-md-notes.md` | 2 | raw markdown note cache | tracked Docs 직접 승격 금지 |
| `part1-archive-migration.md` | 1 | 과거 PR draft | `Docs/05_WorkLogs` 작성 시 요약 참고 |
| `archive-migration-session-prompt.md` | 1 | 과거 세션 prompt | 보존만 하고 새 기준으로 사용하지 않음 |
| `quick-start-prompt.md` | 1 | 과거 quick start prompt | 현행 workflow와 맞지 않아 참고 전용 |
| `assimp-5.2.5-repro.local.md` | 1 | Assimp 5.2.5 재현 시도 기록 | `Ex1701_SkeletalAnimation` 보완 후보 |
| `validate-github-body.ps1` | 1 | GitHub body validator | `Docs/98_Tools` 승격 후보 |

## 승격 후보

| 후보 | 대상 정본 | 판단 |
| --- | --- | --- |
| `local/tools/validate-github-body.ps1` | `Docs/98_Tools` 또는 tracked script 위치 | 반복 사용 가치가 있으므로 별도 검토 후 승격 가능 |
| `local/Part4_Chapter14-20/Ex1701_SkeletalAnimation/assimp-5.2.5-repro.local.md` | `Docs/99_Legacy/PartDocs/Part4_Chapter14-20/Ex1701_SkeletalAnimation/assimp-6x-fbx-pivot.md` 또는 새 Example/Verification 문서 | Assimp 6.x compatibility 설명 보완 후보 |
| `local/Part2_Chapter05-08/**/study-review.local.md` | `Docs/01_Examples`, `Docs/02_Topics` | Part2 문서화 Work Unit에서 필요한 내용만 재작성 후보 |
| `local/pr/part1-archive-migration.md` | `Docs/05_WorkLogs/WU-Part1.md` | 과거 PR 요약 참고용, 원문 승격 금지 |

## local-only 유지

| 대상 | 이유 |
| --- | --- |
| `source-comments.md` 전체 | source comment 원문과 raw 검토 흔적이므로 tracked Docs로 직접 옮기지 않는다. |
| `raw-md-notes.md` 전체 | raw markdown note cache 성격이 강하므로 필요한 개념만 재작성한다. |
| `local/prompts/*` | 과거 import 세션 기준이며 현행 정책과 어긋나는 stale 경로가 있다. |
| `memo-review.md` 전체 | 개인 검토 메모 성격이 강하므로 필요한 내용만 선별한다. |

## 폐기 후보

현재 즉시 삭제할 파일은 없다. 다만 다음 조건을 만족하면 폐기 후보로 본다.

- tracked Docs에 이미 재작성되어 반복 참조 가치가 없다.
- stale workflow, stale path, 과거 import 절차만 담고 있다.
- 개인 환경 정보나 절대 경로가 많아 재사용 가치보다 관리 부담이 크다.

## 다음 작업 연결

- Work Unit을 시작할 때 관련 `local/Part*_Chapter*/.../study-review.local.md`를 먼저 확인한다.
- `source-comments.md`는 코드 위치 확인용으로만 읽고 tracked Docs에 복사하지 않는다.
- validator 승격은 `Docs/98_Tools/validation-tools.md` 기준으로 별도 작업에서 판단한다.
- 이 inventory는 `local/` 파일을 실제 삭제하거나 이동하기 전에 다시 갱신한다.
