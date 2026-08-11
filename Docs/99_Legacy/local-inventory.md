# Local Inventory

이 문서는 Git이 추적하지 않는 `local/` 자료 영역을 특정 시점에 조사한 legacy inventory다. 최신 local 상태의 정본이 아니며, 실제 파일 이동이나 삭제 전에는 반드시 현재 `local/`을 다시 확인한다.

## 기준

- `local/` 파일은 commit 대상으로 보지 않는다.
- tracked Docs로 옮길 때는 원문 복사가 아니라 재작성과 요약을 기준으로 한다.
- private-only 정보, raw 원문 표현, 강의 표현, 개인 환경 정보는 승격하지 않는다.
- 삭제 또는 이동은 별도 사용자 승인 후 진행한다.

## 당시 확인된 성격

| 영역 | 성격 | 처리 판단 |
| --- | --- | --- |
| `local/Part1_Chapter01-02` | Part1 초기 예제 검토 메모 | 필요한 내용만 코드 폴더 README, Topic, Verification 작성 시 참고 |
| `local/Part1_Chapter03` | Ray tracing 단계별 검토 메모 | 필요한 내용만 `Portfolio_GraphicsLab/Rendering/RayTracing`과 RayTracing Topic 작성 시 참고 |
| `local/Part2_Chapter04` | Software rasterization source comment cache | raw/source 원문 성격이 강하므로 직접 승격 금지 |
| `local/Part2_Chapter05-08` | Pipeline, modeling, ShaderToys 검토 메모 | `study-review.local.md`만 우선 참고 후보 |
| `local/Part4_Chapter14-20` | Assimp/SkeletalAnimation 재현 메모 | 필요한 경우 현재 Example/Verification 문서로 재작성 |
| 과거 `local/pr` | Part1 전용 과거 PR draft | `Docs/07_GitHub/` 작성 시 형식 참고만 가능 |
| 과거 `local/prompts` | archive 세션 시작 프롬프트 | 현재 정책과 AGENTS에 흡수된 legacy 자료 |

## 파일 패턴별 판단

| 파일 패턴 | 성격 | 처리 판단 |
| --- | --- | --- |
| `source-comments.md` | source comment와 raw 검토 흔적 | local-only 유지, 직접 승격 금지 |
| `study-review.local.md` | 예제 이해 과정 메모 | 코드 폴더 README, `Docs/01_Topics/`, `Docs/02_Verification/` 작성 전 참고 후보 |
| `final-doc-plan.md` | import 당시 문서화 계획 | `Docs/04_WorkLogs/` 작성 시 참고 가능 |
| `memo-review.md` | 메모 검토 결과 | 필요한 내용만 재작성 후보 |
| `raw-md-notes.md` | raw markdown note cache | tracked Docs 직접 승격 금지 |
| `part1-archive-migration.md` | 과거 PR draft | `Docs/07_GitHub/` 문서 작성 전 참고 후보 |
| `assimp-5.2.5-repro.local.md` | Assimp 5.2.5 재현 시도 기록 | `Part4_Chapter14-20` 후속 작업에서 재확인 후보 |

## 승격 후보

| 후보 | 현재 대응 위치 | 판단 |
| --- | --- | --- |
| `local/Part4_Chapter14-20/Ex1701_SkeletalAnimation/assimp-5.2.5-repro.local.md` | 현재 Example README 또는 `Docs/02_Verification/` | Assimp compatibility 설명 보완 후보 |
| `local/Part2_Chapter05-08/**/study-review.local.md` | 코드 폴더 README, `Docs/01_Topics/` | Part2 Work Unit에서 필요한 내용만 재작성 후보 |
| 과거 `local/pr/part1-archive-migration.md` | `Docs/07_GitHub/`, `Docs/04_WorkLogs/active/WU-Part1.md` | PR 형식과 리뷰 범위만 참고, 원문 승격 금지 |

## local-only 유지

| 대상 | 이유 |
| --- | --- |
| `source-comments.md` 전체 | source comment 원문과 raw 검토 흔적이므로 tracked Docs로 직접 옮기지 않는다 |
| `raw-md-notes.md` 전체 | raw markdown note cache 성격이 강하므로 필요한 개념만 재작성한다 |
| `memo-review.md` 전체 | 개인 검토 메모 성격이 강하므로 필요한 내용만 선별한다 |

## 다음 작업 연결

- Work Unit을 시작할 때 관련 `local/Part*_Chapter*/.../study-review.local.md`를 먼저 확인한다.
- `source-comments.md`는 코드 위치 확인용으로만 읽고 tracked Docs에 복사하지 않는다.
- GitHub body validator는 `Docs/98_Tools/validators/validate-github-body.ps1`를 사용한다.
- 이 inventory는 `local/` 파일을 실제 삭제하거나 이동하기 전에 다시 갱신한다.
