# Legacy

이 폴더는 과거 import 기록, 이전 workflow, 기존 Part 문서 같은 legacy 구조를 보관한다. 새 정본 문서를 작성하는 위치가 아니며, 현재 문서화 작업의 source of truth로 사용하지 않는다.

## 책임

- 과거 import 판단, 이전 문서 구조, 당시 작업 맥락을 보존한다.
- 현재 정본 문서와 충돌하는 내용은 현재 정본 문서로 링크한다.
- legacy 문서의 build/run/capture 상태값은 과거 기록으로만 읽는다.
- PartDocs 전체를 최신 구조에 맞춰 대량 수정하지 않는다.

## 현재 정본 위치

| 목적 | 현재 정본 |
| --- | --- |
| 전체 진입점과 라우팅 | `Docs/00_Index/` |
| Topic 문서 | `Docs/01_Topics/` |
| Build/run/capture 검증 | `Docs/02_Verification/` |
| Demo capture/result 계획 | `Docs/03_Demos/` |
| Work Unit 진행 기록 | `Docs/04_WorkLogs/` |
| Publication 후보 판단 | `Docs/05_Publication/` |
| 운영 정책 | `Docs/06_Policies/` |
| GitHub Issue/PR 초안 | `Docs/07_GitHub/` |
| 템플릿과 validator | `Docs/98_Tools/` |

## 항목

- `ImportHistory/`: raw에서 archive로 옮길 때 사용한 과거 import 정책, 절차, manifest를 보관한다.
- `PartDocs/`: `Docs/Part*` 시절의 기존 Part별 문서를 보관한다.
- `raw-to-archive-map.md`: raw/reference repo와 archive repo의 대응 관계를 기록한 legacy snapshot이다.
- `local-inventory.md`: 특정 시점의 ignored `local/` 자료 영역 inventory다.
- `workflow-readme.md`: 과거 `_repo/workflow` 구조를 설명하던 안내문을 보존한다.

## 작성 기준

- 한국어 평서형으로 작성한다.
- Legacy 문서에는 현재 상태를 새로 확정하지 않는다.
- stale path를 발견하면 현재 정본 문서로 연결하되, 과거 기록의 의미를 바꾸지 않는다.
- 자세한 정책은 `Docs/06_Policies/`를 기준으로 한다.
