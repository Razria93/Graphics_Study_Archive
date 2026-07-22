# WU Structure Cleanup

## 범위

- Work Unit: `WU-StructureCleanup`
- 대상 코드: 없음
- 대상 문서: `Docs`, `AGENTS.md`, `README.md`, `BUILD.md`, `DEMOS.md`, `NOTICE.md`, `TOPICS.md`

## 변경 요약

- `Docs/_repo` 중심 운영 문서를 산출물 축 구조로 재배치했다.
- `Docs/00_Index`부터 `Docs/06_Publication`까지 산출물 기준 폴더를 만들고, 각 폴더의 `README.md`와 `AGENTS.md`를 두었다.
- `Docs/07_Policies`에 문서 작성, GitHub workflow, 검증, publication, 용어, 문체 정책을 모았다.
- `Docs/98_Tools`에 템플릿과 validation 기준을 모았다.
- import 단계 기록은 `Docs/99_Legacy/ImportHistory`와 `Docs/99_Legacy/PartDocs`로 격하했다.
- `_repo` 내부 안내 문서는 정본 역할을 잃은 항목부터 제거했다.

## 갱신한 정본 문서

| 산출물 | 문서 | 상태 |
| --- | --- | --- |
| Index | `Docs/00_Index` | 생성 |
| Example | `Docs/01_Examples` | 골격 생성 |
| Topic | `Docs/02_Topics` | 골격 생성 |
| Verification | `Docs/03_Verification` | 골격 생성 |
| Demo | `Docs/04_Demos` | 골격 생성 |
| WorkLog | `Docs/05_WorkLogs` | 골격 생성 |
| Publication | `Docs/06_Publication` | 골격 생성 |
| Policy | `Docs/07_Policies` | 정리 |
| Tools | `Docs/98_Tools` | 정리 |
| Legacy | `Docs/99_Legacy` | 정리 |

## 검증 요약

- Debug x64 build: 대상 없음
- Debug x64 run: 대상 없음
- Release x64 build: 대상 없음
- Release x64 run: 대상 없음
- Capture: 대상 없음
- 문서 구조 검증: 완료
- stale path 검사: 완료
- 문체 검사: 완료
- 빈 링크/placeholder 검사: 완료
- `git diff --cached --check`: 완료

## Issue/PR 연결

- Issue: 예정
- PR: 예정
- Draft: 없음
- Snapshot: 없음

## Known Issue

- `Docs/99_Legacy`에는 import 당시 기록과 과거 경로 표현이 일부 남아 있을 수 있다. Legacy 기록은 정본 경로가 아니라 과거 판단 근거로 읽는다.
- 실제 예제 build/run/capture 검증은 아직 시작하지 않았다. 이 Work Unit은 문서 구조 정리만 다룬다.

## Follow-up

- 구조 정리 브랜치를 push할지, PR로 열지, main에 병합할지 사용자 승인 후 결정한다.
- 다음 실작업은 Part 단위 Work Unit 중 하나를 pilot으로 선택한다.
- pilot 진행 전 `Docs/01_Examples`, `Docs/02_Topics`, `Docs/03_Verification`, `Docs/04_Demos`의 양식이 과하지 않은지 다시 확인한다.
