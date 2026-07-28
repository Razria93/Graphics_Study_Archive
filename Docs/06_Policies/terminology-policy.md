# Terminology Policy

이 문서는 Graphics Study Archive 문서에서 반복 사용하는 표준 용어를 정의한다. 같은 의미를 여러 표현으로 섞어 쓰지 않는다.

## 표준 용어

| 표준 용어 | 의미 | 비표준 또는 주의 표현 |
| --- | --- | --- |
| 루트 코드 폴더 | repo root에 있는 `Part*_Chapter*`와 `Portfolio_RayTracer` 코드/build 기준 폴더 | root code folder, code folder 단독 표현 |
| 산출물 축 폴더 | `Docs/00_Index`부터 `Docs/05_Publication`까지의 문서 산출물 폴더 | Part 중심 문서 구조 |
| 정본 문서 | 최신 기준으로 유지하는 tracked Docs 문서 | tracked Docs 정본, 공식 문서 |
| Legacy 문서 | `Docs/99_Legacy` 아래의 과거 import 기록과 이전 문서 구조 | legacy docs, 이전 문서 |
| Legacy PartDocs | `Docs/99_Legacy/PartDocs` 아래의 이전 Part별 문서 | 기존 `Docs/Part*`, legacy Part docs |
| ImportHistory | `Docs/99_Legacy/ImportHistory` 아래의 과거 import 판단 기록 | ImportPhase, migration 기록 |
| local-only 자료 영역 | Git에 추적하지 않는 `local/` 자료 영역 | local cache, local-only docs, local-only 작업장 |
| raw/reference repo | 원본/미가공 자료를 읽기 전용으로 참고하는 저장소 | raw repo 단독 표현 |
| current code | 현재 archive repo의 루트 코드 폴더에 있는 작업 코드 | 현재 코드 단독 표현 |
| raw/reference code | raw/reference repo에 남아 있는 원본/미가공 기준 코드 | raw code 단독 표현 |
| origin 기준 | 사용자가 채우기 전 원본 예제 또는 `OriginalExamples` 기준점 | origin 단독 표현, 원본 단독 표현 |
| current/raw/origin 비교 | current code, raw/reference code, origin 기준의 차이를 확인하는 작업 | diff 단독 표현 |
| source comment inventory | 관련 source/header/shader 주석을 전수조사해 분류한 local-only 검토 기록 | 주석 삭제, 주석 정리 단독 표현 |
| capture/result | demo나 문서에서 보여줄 screenshot, video, result image 전체 | 이전 시각 결과/검증 자료 계열 표현 |
| 과거 확인 | 문서화 이전에 직접 확인한 build/run 성공의 provenance | 현재 재실행, 추정 성공 |
| 재검증 필요 | 과거 성공을 유지하되 현재 작업에서 다시 실행하지 않은 상태 | 실패, 미확인 |
| GitHub draft | 게시 전 Issue/PR/comment 초안 | PR draft, Issue draft 단독 표현 |
| Public subset | 공개 후보로 선별 가능한 결과물 묶음 | public repo 내용, 공개 자료 단독 표현 |

## 사용 기준

- 상위 README, AGENTS, 정책 문서는 표준 용어를 우선 사용한다.
- Legacy 문서 본문에 남아 있는 과거 표현은 즉시 대량 수정하지 않는다.
- 새 정본 문서를 작성할 때는 이 문서의 표준 용어를 따른다.
- 용어가 애매하면 `Terminology Policy`에 먼저 추가한 뒤 다른 문서에서 사용한다.

## 예외

- 파일명, 폴더명, API 이름, GitHub 명령, graphics technical keyword는 원문을 유지한다.
- 인용 또는 과거 기록을 설명할 때는 과거 용어를 쓸 수 있으나, 현재 기준 용어를 함께 명시한다.
